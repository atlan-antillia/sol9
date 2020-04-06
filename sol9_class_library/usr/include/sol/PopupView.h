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
 *  PopupView.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.10.09 Added a layout method.
// 2000.02.18
// 2001.03.11 Added a create method.
#pragma once

#include <sol\Composite.h>

namespace SOL {

class PopupView  :public Composite {
private:
  int  focusId;
  View*  owner;
  View*  parent;
  
protected:
  virtual LRESULT defaultProc(Event& event) 
  {
    return FALSE;
  }

protected:
  void disableOwner()
  {
    if(owner) {
      owner ->enableWindow(FALSE);
    }
  }

protected:
  void enableOwner()
  {
    if(owner) {
      owner -> enableWindow(TRUE);
    }
  }

protected:
  long close(Event& event)
  {
    Action action(NULL, event);
    popdown(action);
    return 0L;
  }

protected:
  long command(Event& event) 
  {
    WORD controlId = event.getControlId();
// PopupView has no menuCallbacks.
    HWND child     = event.getChild();
    if(controlId > 0) {
      HWND item = getItem(controlId);
      if(::IsWindow(item))
        child = item;
    }

    UINT notify = event.getNotification();
    const TCHAR* name = findCallbackName(event, child);

    WPARAM wParam = event.getWParam();
    if(name == XmNactivateCallback  && wParam ==IDOK) {
      child = ::GetFocus();
    }
    callCallback(name, (Key)child, NULL, event);

    return 0;
  }

protected:
  void resize()
  {
    RECT r;
    getClientRect(&r);
    int w = r.right-r.left;
    int h = r.bottom-r.top;
    send(WM_SIZE, 0, MAKELONG(w, h));
  }

// 1999.10.09 Added the following method to fix a problem on Layoutmanager.
protected:
  virtual void layout(int x, int y, int w, int h)
  {
    /*if (getParent() != NULL) {
      reshape(x, y, w, h);
    }*/
    LayoutManager* layoutManager = getLayoutManager();
    if (layoutManager) {
      layoutManager->layout(0, 0, w, h);
    }
  }

public:
  PopupView() :Composite() { }

public:
  PopupView(View* parent)
    :Composite(parent),
  parent(parent)
  { 
   
    owner = NULL;
    focusId = 0;
  }

public:
// 2001/03/11
  virtual Boolean create(View* parent)
  {
    Boolean rc = Composite::create(parent) ;
 
    owner = NULL;
    focusId = 0;
    return rc;
  }

public:
  //2012/06/22
  PopupView(View* parent, const TCHAR* name, Args& args)
  :Composite(),
  parent(parent)
  {
    create(parent, name, args);
    
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name,
         args.set(XmNstyle, 
            (LONG_PTR)(WS_POPUP|WS_SYSMENU|WS_CAPTION))
           .set(XmNpredefined, TRUE)
             .set(XmNclassName, (LONG_PTR)WC_DIALOG));

    owner  = NULL;
    
    focusId = 0;

    addEventHandler(WM_CLOSE, this,
      (Handler)&PopupView::close, NULL);

    setWindowLongPtr(DWLP_DLGPROC, (LONG_PTR)PopupView::procedure);
    LONG_PTR val;
    if (args.get(XmNfocusId, &val)) {
      focusId = (int)val;
    }
    return rc;
  }


  void  setFocusId(int id) { focusId = id; }

  void  setOwner(View* view) { owner = view; }

public:
  virtual void popup(Action& action)
  {
    RECT rect;
    getWindowRect(&rect);
    int x      = 0;
    int y      = 0;
    int width  = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int scWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    int scHeight = ::GetSystemMetrics(SM_CYSCREEN);
  
    View* parent = getParent();
    if(parent) {
    // Move to the center of a parent.
      RECT pr;
      parent -> getWindowRect(&pr);
      x = pr.left + (pr.right - pr.left - width)/2;
      y = pr.top  + (pr.bottom - pr.top - height)/2;
    }
    if((x+width) >scWidth) x = scWidth - width;
    if(x <0 ) x = 0;

    if((y+height) >scHeight) y = scHeight - height;
    if(y < 0) y = 0;

    disableOwner();
    reshape(x, y, width, height);
    raise();
    show(SW_SHOWNORMAL);
  }

public:
  void setPopupFocus()
  {
    if(focusId) {
      HWND child = getItem(focusId);
      if(child) {
        ::SetFocus(child);
      }
    }
  }

public:
  virtual void popdown(Action& action)
  {
    enableOwner();
    show(SW_HIDE);
  }

public:
  void popupAt(Action& action)
  {
    RECT rect;
    getWindowRect(&rect);
    int w   = rect.right - rect.left;
    int h   = rect.bottom - rect.top;
    int x = (::GetSystemMetrics(SM_CXSCREEN) - w)/2;
    int y = (::GetSystemMetrics(SM_CYSCREEN) - h)/2;
    reshape(x, y,  w, h);
    disableOwner();
    raise();
    show(SW_SHOWNORMAL);
  }

public:
  void popupAsItIs(Action& action)
  {
    disableOwner();
    raise();
    show(SW_SHOWNORMAL);
  }

public:
  static BOOL CALLBACK procedure(HWND hwnd, 
    UINT message, WPARAM wParam, LPARAM lParam)
  {
    Event event(message, wParam, lParam);

    View* view = Application::lookup(hwnd);
    BOOL result = FALSE;
    if (view) {
      result = (BOOL) view -> dispatch(event);
    }
    return result;
  }

public:
  void setViewId(int vid)
  {
    setId(vid);
  }

public:
  void centerOn()
  {
    RECT rect;
    getWindowRect(&rect);
    int x      = 0;
    int y      = 0;
    int width  = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int scWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    int scHeight = ::GetSystemMetrics(SM_CYSCREEN);
  
    View* parent = getParent();
    if(parent) {
      RECT pr;
      parent -> getWindowRect(&pr);
      x = pr.left + (pr.right - pr.left - width)/2;
      y = pr.top  + (pr.bottom - pr.top - height)/2;
    }
    if((x+width) >scWidth) {
      x = scWidth - width;
    }
    if(x <0 ) { 
      x = 0;
    }
    if((y+height) >scHeight){
      y = scHeight - height;
    }
    if(y < 0) { 
      y = 0;
    }

    reshape(x, y, width, height);
  }  

  /*
  */
};

}


