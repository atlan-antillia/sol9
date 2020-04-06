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
 *  MdiChild.h
 *
 *****************************************************************************/

// SOL9
// 
#pragma once

#include <sol/Composite.h>
#include <sol/PaintDC.h>
#include <sol/Menubar.h>
#include <sol/MdiFrame.h>
#include <sol/MdiClient.h>


namespace SOL {

class MdiChild :public Composite {
private:
  SmartPtr<MenuBar>  menuBar;
  int      subMenuId;
  
protected:
  virtual long eraseBackground(Event& event)
  {
    return 1;  //Don't erase the background of the client area of this window
  }
  
  virtual long size(Event& event)
  {
    int w, h;
    getClientSize(w, h);
    
    resize(w, h);
    
    invalidateAll();
   // update();
    invalidate((RECT*)nullptr, FALSE);

    postRenderRequest();
    return 1;
  }
  
  virtual void resize(int w, int h)
  {
    
  }

protected:
  virtual long paint(Event& event)
  {
    PaintDC pdc(this);
    
    RECT r;
    getClientRect(&r);
    HBRUSH hbr = (HBRUSH)GetStockObject(GRAY_BRUSH);
    pdc.fillRect(&r, hbr);

    display(pdc);
    return 1;
  }

  virtual void display(PaintDC& pdc)
  {
  }
  
protected:
  virtual long mdiActivate(Event& event)
  {
    MdiClient* mdiClient = (MdiClient*)getParent();
    MdiFrame*  mdiFrame  = (MdiFrame*)mdiClient->getParent();

    HMENU  hmenu   = NULL;
    HMENU  subMenu = NULL;
    WPARAM wParam  = event.getWParam();
    HWND   active  = (HWND)event.getLParam();
    if(active == getWindow()) {
      hmenu   = menuBar -> get();
      subMenu = ::GetSubMenu(hmenu, subMenuId);
    }
    else {
      hmenu   = mdiFrame-> getMenuBar() -> get();
      subMenu = ::GetSubMenu(hmenu, mdiFrame -> getSubMenuId());
    }
    mdiClient -> setMenu(hmenu, subMenu);
    ::DrawMenuBar(mdiFrame->getWindow());
    return NULL;
  }


protected:
  long destroy(Event& event)
  {
    MdiClient*  mdiClient = (MdiClient*)getParent();
    if(mdiClient) {
      mdiClient -> destroy(event);
    }
    return NULL;
  }


  LRESULT defaultProc(Event& event)
  {
    return ::DefMDIChildProc(getWindow(),
        event.getMessage(),
        event.getWParam(),
        event.getLParam());
  }


public:
  MdiChild(): Composite() { }

public:
  //2012/06/23
  MdiChild(MdiClient* parent, const TCHAR* title, Args& args)
  :Composite()
  {
    try {
      create(parent, title, args);
    } catch (Exception ex) {
      caught(ex);
    }
  }


public:
  Boolean create(MdiClient* parent, const TCHAR* title, Args& args)
  {
    Boolean rc = False;
    View::setParent(parent);

    const TCHAR* className = (const TCHAR*)args.get(XmNclassName);
    if(className == nullptr) {
      className = _T("MdiChild");
      args.set(XmNclassName, className);
    }
        
    registerClass(args);

    MDICREATESTRUCT cs;
    memset(&cs, 0, sizeof(cs));
    cs.szClass = className;
    cs.szTitle = title;
    cs.hOwner  = GetModuleHandle(NULL);//Application::getInstance();
    cs.x       = (int) args.get(XmNx),
    cs.y       = (int) args.get(XmNy),
    cs.cx      = (int) args.get(XmNwidth),
    cs.cy      = (int) args.get(XmNheight),
    cs.style   = args.get(XmNstyle);
    cs.lParam  = NULL;
    HWND  hwnd = (HWND)parent -> send(WM_MDICREATE, 0, (LPARAM)&cs);
    //MessageBox(NULL, className, _T("MdiCreate"), MB_OK);
  
    if (hwnd) {
      rc = True;
      setWindow(hwnd);
      Application::add(hwnd, this);

      const TCHAR* menuName = (TCHAR*) args.get(XmNmenuName);
      if(!menuName) {
        menuName = title;
      }
      
      menuBar   = new MenuBar(this, menuName);
      subMenuId = (int) args.get(XmNmenuId);

      setValues(args);

      addEventHandler(WM_ERASEBKGND, this,
        (Handler)&MdiChild::eraseBackground, NULL);

      addEventHandler(WM_PAINT, this,
        (Handler)&MdiChild::paint, NULL);

      addEventHandler(WM_MDIACTIVATE, this,
        (Handler)&MdiChild::mdiActivate, NULL);

      addEventHandler(WM_MDIDESTROY, this,
        (Handler)&MdiChild::destroy, NULL);
      addEventHandler(WM_SIZE, this, 
        (Handler)&MdiChild::size, NULL); 

      addCallback(XmNhorizScrollCallback, (Key)hwnd, this,
        (Callback)&Composite::doHorizScroll, NULL);
      addCallback(XmNvertScrollCallback, (Key)hwnd, this,
        (Callback)&Composite::doVertScroll,  NULL);

      parent -> activate(this);
    } else {
      throw TException(_T("Failed to create MdiChild"));
    }
    return rc;
  }

public:
  MenuBar*  getMenuBar()  { return menuBar; }

public:
  void  setViewId(int vid)
  {
    LONG  id = (LONG)getWindowLongPtr(GWLP_ID);
    setId(id);
  }



public:
  MdiFrame* getMdiFrame()
  {
    View* parent = getParent();
    MdiFrame* frame = NULL;
    if(parent) {
      frame = (MdiFrame*)(parent->getParent());
    }
    return frame;
  }

};

}



