/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *  
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  ModalDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

#include <sol\Application.h>
#include <sol\PopupView.h>
//#include <sol/Stdio.h>

namespace SOL {

class ModalDialog :public PopupView {
private:
  BOOL   centering;
  TCHAR*  templateName;

  static BOOL CALLBACK procedure(HWND hwnd, 
    UINT message, WPARAM wParam, LPARAM lParam)
  {
    if (message == WM_INITDIALOG) {
      ModalDialog* dialog = (ModalDialog*)lParam;
      if (dialog) {
        //Printf("ModalDialog::procedure, WM_INITDIALOG\n");
        Application::add(hwnd, dialog);
        dialog -> setWindow(hwnd);
      }
    }
    ModalDialog* dlg = (ModalDialog*)Application::lookup(hwnd);
    if(dlg == NULL) { 
      return FALSE;
    }

    Event event(message, wParam, lParam);
    if(message == WM_DESTROY) {
      Application::remove(hwnd);
      return FALSE;
    }
    else {
      return (BOOL)dlg -> dispatch(event);
    }
  }


protected:

  virtual long initDialog(Event& event)
  {
    //2008/07/12
    setup();

    setPopupFocus();
    if(centering) {
      centerOn();  
    }
    return NULL;
  }

  virtual long command(Event& event) 
  {
    HWND child  = event.getChild();
    const TCHAR* name = findCallbackName(event, child);

    WPARAM wParam = event.getWParam();
    if(name == XmNactivateCallback && wParam == IDOK) {
      child = ::GetFocus();
    }

    if(child) {
      callCallback(name, (Key)child, NULL, event);
    }
    // ESC key
    if(child == NULL && wParam == IDCANCEL) {
      end(0);
    }
    return TRUE;
  }

public:
  ModalDialog():PopupView() { }


public:
  //2012/06/22
  ModalDialog(View* owner, const TCHAR* name, Args& args)
  :PopupView()
  {
    create(owner, name, args);
  }


public:
  virtual Boolean create(View* owner, const TCHAR* name, Args& args)
  {
  // 2001/03/11
    Boolean rc = PopupView::create(owner);

    setOwner(owner);

    centering = (int) args.get(XmNcentering);

    templateName = (TCHAR*) args.get(XmNtemplateName);
    addEventHandler(WM_INITDIALOG, this,
      (Handler)&ModalDialog::initDialog, NULL);

    int focusId = IDOK;
    LONG_PTR val;
    if (args.get(XmNfocusId, &val)) {
      focusId = (int)val;
    }
    setFocusId(focusId);

  // Use a virtual effect!
    addCallback(XmNactivateCallback, IDCANCEL, this,
      (Callback)&ModalDialog::popdown, NULL);
    return rc;
  }

public:
  void popup(Action& action)
  {
    View* owner    = getParent();
    HWND howner    = NULL;
    HINSTANCE hins = NULL;

    if(owner) {
      howner = owner -> getWindow();
      hins   = owner -> getInstanceHandle();
    }
  
  // 2009/07/06
    ::DialogBoxParam(hins, templateName, howner, 
        (DLGPROC)ModalDialog::procedure, (LPARAM)this);

  }

public:
  void  end(BOOL flag) {
      ::EndDialog(getWindow(), flag);
  }

public:
  void  popdown(Action& action) {
      ::EndDialog(getWindow(), TRUE);
  }

  //2008/07/12 
public:
  virtual void setup() { 
    // Copy initial data to items(control) of dialog.
    // Will be called automaticall initiDialog.
    InitCommonControls();  

  }
};

}


