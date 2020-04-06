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
 *  MdiFrame.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Application.h>
#include <sol\Composite.h>
#include <sol\Menubar.h>
#include <sol\MdiClient.h>
#include <sol\accelerator.h>
#include <sol\Toolbar.h>
#include <sol\Statusbar.h>

//2009/10/11
#include <sol/AppEntry.h>


namespace SOL {

class MdiFrame :public Composite {
private:
  SmartPtr<MenuBar>     menuBar;
  int                  subMenuId;
  SmartPtr<MdiClient>  mdiClient;
  Application&          application;
  SmartPtr<Accelerator> accel;
  SmartPtr<ToolBar>     toolBar;
  SmartPtr<StatusBar>   statusBar;

  static const long STYLE = (WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
  
protected:
  long size(Event& event)
  {
    int toolBarHeight = 0;
    RECT r;
    if(toolBar) {
      toolBar -> send(event.getMessage(), 
      event.getWParam(), event.getLParam());
      toolBar -> getClientRect(&r);
      toolBarHeight = r.bottom - r.top;
    }
    int statusBarHeight = 0;
    if(statusBar) {
      statusBar -> send(event.getMessage(),
        event.getWParam(), event.getLParam());
      statusBar -> getClientRect(&r);
      statusBarHeight = r.bottom - r.top;
    }
    if(mdiClient) {
      getClientRect(&r);
      int w = r.right - r.left;
      int h = r.bottom - toolBarHeight - statusBarHeight - r.top;
      mdiClient -> reshape(0, toolBarHeight, 
        w,  h);
      
    }
    return 1;
  }

protected:
  long  command(Event& event)
  {
    if(event.isMenuSelected() == TRUE ||
     event.fromAccelerator() == TRUE) {
      int key = event.getMenuId();
      callCallback(XmNmenuCallback, key, NULL, event);
      return defaultProc(event);
    }
    else {
      HWND child = event.getChild();
      View* view = (View*)Application::lookup(child);
      const TCHAR* name = XmNactivateCallback;
      if(view) {
        name = view -> getCallbackName(event);
      }
      callCallback(name, (Key)child, NULL, event);
    }

    HWND child = mdiClient->getActiveWindow();

    if(::IsWindow(child)) {
      return ::SendMessage(child, WM_COMMAND,
          event.getWParam(),
          event.getLParam());
    }
    return defaultProc(event);
  }

public:
  void  cascade(Action& action) {
      mdiClient -> cascade();
  }

public:
  void  iconArrange(Action& action) {
      mdiClient -> iconArrange();
  }

public:
  void  tile(Action& action) {
      mdiClient -> tile();
  }

protected:
  virtual LRESULT defaultProc(Event& event)
  {
    HWND hclient = NULL;
    if(mdiClient) {
      hclient = mdiClient->getWindow();
    }

    if(::IsWindow(hclient)) {
      return ::DefFrameProc(getWindow(), hclient,
        event.getMessage(), 
        event.getWParam(),
        event.getLParam());
    }
    else { 
      return View::defaultProc(event);
    }
  }

public:
  /**
   * Constructor
   */
  MdiFrame(Application& applet, const TCHAR* caption, Args& args)
  :Composite(NULL, caption, 
    args.set(XmNx,      (LONG_PTR)CW_USEDEFAULT)
        .set(XmNy,      (LONG_PTR)CW_USEDEFAULT)
        .set(XmNwidth,  (LONG_PTR)CW_USEDEFAULT)
        .set(XmNheight, (LONG_PTR)CW_USEDEFAULT)
        .set(XmNstyle,  (LONG_PTR)STYLE)
        .set(XmNclassName, _T("MdiFrame"))),

      application(applet),
      mdiClient(NULL),
      menuBar(NULL),
      toolBar(NULL),
      statusBar(NULL),
      accel(NULL)
  {
    applet.setToplevel(this);

    LONG_PTR val;

    const TCHAR* menuName = caption;
    if(args.has(XmNmenuName)) {
      menuName = (const TCHAR*)args.get(XmNmenuName);
    }
    
    menuBar   = new MenuBar(this, menuName);
    if (menuBar == nullptr) {
      throw TException(_T("Failed to create MenuBar:%s"), menuName);
    }
  
    const TCHAR* accelName = caption;
    if (args.get(XmNacceleratorName, &val)) {
      accelName = (TCHAR*)val;
    }
    accel =  new Accelerator(accelName);
  
    int firstChildId = 1000;
    subMenuId = 0;

    if (args.get(XmNchildId, &val))  {
      firstChildId = (int)val;
    }
    if (args.get(XmNmenuId, &val)) {
      subMenuId = (int)val;
    }

    CLIENTCREATESTRUCT cs;
    memset(&cs, 0, sizeof(cs));

    cs.idFirstChild = firstChildId;
    cs.hWindowMenu  = ::GetSubMenu(menuBar->get(), subMenuId);

    DWORD style = WS_VSCROLL|WS_HSCROLL;
    style |= args.get(XmNmdiClientStyle);
    Args ar;
    ar.set(XmNparam, &cs);
    ar.set(XmNstyle, style);
    mdiClient   = new MdiClient(this, _T("mdi"), ar);
    if (mdiClient == nullptr) {
      throw TException(_T("Failed to create MdiClient"));
    }
    addEventHandler(WM_SIZE, this,
      (Handler)&MdiFrame::size, NULL);
    postResizeRequest();
  }

public:
  ~MdiFrame()
  {
  }

  
public:
  void exit(Action& action)
  {
    send(WM_CLOSE, 0, 0L);
  }

  
public:
  MenuBar*    getMenuBar()   { return menuBar; }

public:
  int         getSubMenuId() { return subMenuId; }

public:
  MdiClient*  getClient() { return mdiClient; }


public:  
  void    setToolBar(ToolBar* bar) { toolBar = bar; }

public:
  void    setStatusBar(StatusBar* bar) { statusBar = bar; }

public:
  void realize()
  {
    int cmdShow = application.getShowCommand();
    show(cmdShow);
  }

public:
  BOOL translate(MSG* msg)
  {
    HACCEL haccel = accel->get();

    if(mdiClient &&  ::TranslateMDISysAccel(mdiClient->getWindow(), msg) ) {
      return TRUE;
    }

    if (haccel && ::TranslateAccelerator(getWindow(), haccel, msg)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }


public:
  void setViewId(int vid)
  {
    setId(vid);
  }


public:
  virtual void childActivated(View* child)
  {
    // Do nothing here.
  }
};

}


