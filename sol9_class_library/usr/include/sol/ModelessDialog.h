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
 *  ModelessDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\PopupView.h>
#include <sol\InvalidArgumentException.h>
#include <sol\InvalidWindowException.h>


namespace SOL {

class ModelessDialog :public PopupView {

protected:
  virtual long command(Event& event) 
  {
    HWND child   = event.getChild();
    const char* name = findCallbackName(event, child);

    WPARAM wParam = event.getWParam();
    // If it was a OK button, then ...
    if(name == XmNactivateCallback &&  wParam == 1) {
      child = ::GetFocus();
    }
    callCallback(name, (Key)child, NULL, event);
    return TRUE;
  }
  

public:
  ModelessDialog():PopupView() { }

public:
  //2012/06/23
  ModelessDialog(View* owner, const TCHAR* name, Args& args)
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

    HWND howner    = NULL; 
    HINSTANCE hins = NULL;
    if (owner) {
      howner = owner -> getWindow();
      hins   = owner -> getInstanceHandle();
    }

    const char* templateName = (const char*) args.get(XmNtemplateName);

    if (templateName == NULL || *templateName == ZERO) {
      throw InvalidArgumentException("Dialog template-name is missing");
    }

    HWND hwnd = ::CreateDialog(hins, templateName, 
              howner, 
              (DLGPROC)PopupView::procedure);

    if (hwnd == NULL) {
      throw InvalidWindowException("Failed to create a modeless dialog");
    }
    setWindow(hwnd);
  
    int focusId = IDOK;
    LONG_PTR val;
    if (args.get(XmNfocusId, &val)){
      focusId = (int)val;    
    }
    setFocusId(focusId);
    setPopupFocus();

    Application::add(hwnd, this);
  
    addCallback(XmNactivateCallback, IDCANCEL, this,
      (Callback)&ModelessDialog::popdown, NULL);

    return rc;
  }


public:
  void popup(Action& action)
  {
    raise();
    show(SW_NORMAL);  
  }
};

}


