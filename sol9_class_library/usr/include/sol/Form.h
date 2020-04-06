/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Form.h
 *
 *****************************************************************************/

// SOL9

// 2009/09/29
// Windows WC_DIALOG class wrapper class.
// 
// This class can be used to give a simple user interface to support a keyboard navigation.
// For example, you can paste a instance of this class in the client area of SOL Application Window.

#pragma once

#include <sol\Composite.h>

namespace SOL {

class Form :public Composite {

private:
  LRESULT defaultProc(Event& event) 
  {
    return FALSE;
  }


public:
  long close(Event& event)
  {
    return 0L;
  }

private:
  //2009/09/25
  // WM_COMMAND message handler.
  long Form::command(Event& event) 
  {
    //<added date="2009/09/25">
    WORD menuId = (WORD)event.getMenuId();

    //For the case of menu item selection for a menuBar or contextMenu 
    if(event.isMenuSelected() == TRUE ||
      event.fromAccelerator() == TRUE) {
      // menu or accelarator has been selected. 
      callCallback(XmNmenuCallback, (Key)menuId,
        NULL,event);
      return 0L;

    }
    //</added>

    //From the case of command message from a child control.
    WORD controlId = event.getControlId();

    HWND child     = event.getChild();
    if(controlId > 0) {
      HWND item = getItem(controlId);
      if(::IsWindow(item))
        child = item;
    }

    //Find and call a callback fuction for this command message
    View* view = (View*)Application::lookup(child);
    const TCHAR* name = XmNactivateCallback;
    if(view) {  
      name = view->getCallbackName(event);
    }
    callCallback(name, (Key)child, NULL, event);

    return 0L;
  }

private:
  // Dialog Procedure
  static BOOL FAR PASCAL procedure(HWND hwnd, 
    UINT message, WPARAM wParam, LPARAM lParam)
  {
    Event event(message, wParam, lParam);

    View* view = Application::lookup(hwnd);
    if(view == NULL) {
      return FALSE;
    }
    return (BOOL) view -> dispatch(event);
  }


public:
  Form(): Composite() { }

public:
  // WS_EX_CONTROLPARENT enables a keyboard interface 
  //2012/06/22
  Form(View* parent, const TCHAR* name, Args& args)
  :Composite()
  {
    create(parent, name, args);
  }  

public:
  ~Form()
  {
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name,
        args.set(XmNstyle, (LONG_PTR)WS_CHILD)
           .set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
           .set(XmNpredefined, TRUE)
             .set(XmNclassName, (LONG_PTR)WC_DIALOG));

    addEventHandler(WM_CLOSE, this,
      (Handler)&Form::close, NULL);
    setWindowLongPtr(DWLP_DLGPROC, (LONG_PTR)Form::procedure); //2017/09/10
  
    setValues(args);

    return rc;
  }  

};

}

