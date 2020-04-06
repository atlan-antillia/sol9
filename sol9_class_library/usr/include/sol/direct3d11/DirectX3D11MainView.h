/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectX3D11MainView.h
 *
 *****************************************************************************/

// 2016/01/04

#pragma once

#include <sol/ApplicationView.h>
#include <sol/String.h>
#include <sol/StringT.h>
#include <sol/PaintDC.h>
#include <sol/Stdio.h>
#include <sol/dxgi/DirectXGIFactory.h>
#include <sol/dxgi/DirectXGIAdapter.h>
#include <sol/dxgi/DirectXGISwapChain.h>
#include <sol/direct3d11/Direct3D11Device.h>
#include <sol/direct3d11/Direct3D11ImmediateContext.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D10_MAINVIEW (WM_USER+2020)

class DirectX3D11MainView :public ApplicationView {
  //Default MENU_IDs
public:
  typedef enum {
    IDM_NEW  =100,
    IDM_OPEN,     //101
    IDM_SAVE,     //102
    IDM_SAVEAS,   //103
  } FILE_MENU;
  
  typedef enum {
  IDM_HELP = 200  
  } HELP_MENU;
  
  //
  static const int IDM_EXIT    = 2015;
  static const int IDM_VERSION = 2016;
  
public:
  StringT<TCHAR> appName;

  UINT                adapterIndex;
  DirectXGIFactory*   dxgiFactory;
  DirectXGIAdapter*   adapter;

  Direct3D11Device*   d3d11Device;
  Direct3D11ImmediateContext*   d3d11ImmediateContext;
  
public:
  long eraseBackground(Event& event)
  {
    return 1L;
  }
  
  long size(Event& event)
  {
    int width  = 0;
    int height = 0;
    event.getSize(width, height);
    //Call a virtual resize method.
    resize(width, height);
    return 1L;
  }

   //Please define your own resize method in subclass derived form this class.
  virtual void resize(int w, int h)
  {
  }

  long lButtonDown(Event& event)
  {
    leftButtonDown(event);
    return 0;
  }
  
  long lButtonUp(Event& event)
  {
    leftButtonUp(event);
    return 0;
  }
  
  long rButtonDown(Event& event)
  {
    rightButtonDown(event);
    return 0;
  }
  
  long rButtonUp(Event& event)
  {
    rightButtonUp(event);
    return 0;
  }

  long mMouseMove(Event& event)
  {
    mouseMove(event);
    return 0;
  }

  long kDown(Event& event)
  {
    keyDown(event);
    return 0;
  }

  //Please define your own leftButton method in subclass derived form this class.
  virtual void leftButtonDown(Event& event)
  {
  }

  //Please define your own leftButtonUp method in subclass derived form this class.
  virtual void leftButtonUp(Event& event)
  {
  }
 
  //Please define your own rigthButtonUp method in subclass derived form this class.
  virtual void rightButtonDown(Event& event)
  {
  }
  
  //Please define your own rigthButtonUp method in subclass derived form this class.
  virtual void rightButtonUp(Event& event)
  {
  }
  
  //Please define your own rigthButtonDown method in subclass derived form this class.
  virtual void mouseMove(Event& event)
  {
  }
  //Please define your own keyDown method in subclass derived form this class.
  virtual void keyDown(Event& event)
  {
  }

  //Default menuCallback for IDM_VERSION
  //Define your own method in a subclass derived from this class.
  virtual void version(Action& action)
  {
    TCHAR message[256];
    _stprintf_s(message, CountOf(message), _T("%s \r\n Copyright(c) 2016 Antillia.com"), (const TCHAR*)appName);
 
    showMessageDialog(_T("Version"), message, MB_ICONINFORMATION|MB_OK);
  }

public:
  //Default virtual menu callbacks.
  //Please define your own callbacks in your subclass derived from this class.
  virtual void clear(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: New", MB_ICONINFORMATION|MB_OK);
  }
  
  virtual void open(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Open", MB_ICONINFORMATION|MB_OK);
  }

  virtual void save(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Save", MB_ICONINFORMATION|MB_OK);
  }

  virtual void saveAs(Action& action)
  {
    showMessageDialog("Menu", "Default enu callack: SaveAs", MB_ICONINFORMATION|MB_OK);
  }
    
  virtual void help(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Help", MB_ICONINFORMATION|MB_OK);
  }
  
public:
  DirectXGIFactory* getDXGIFactory()
  {
    return  dxgiFactory;
  }

  Direct3D11Device* getD3D11Device()
  {
    return d3d11Device;
  }

  Direct3D11ImmediateContext* getD3D11ImmediateContext()
  {
    return d3d11ImmediateContext;
  }

  
  const TCHAR* getAppName()
  {
    return (const TCHAR*)appName;
  }
  
  virtual long getMinMaxInfo(Event& event)
  {
    MINMAXINFO* info = (MINMAXINFO*)event.getLParam();
    static const int MIN_WIDTH  = 200;
    static const int MIN_HEIGHT = 200;
    
    info -> ptMinTrackSize.x = MIN_WIDTH;
    info -> ptMinTrackSize.y = MIN_HEIGHT;

    return 0;
  }
  
  
public:
  //Constructor
  DirectX3D11MainView(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
  adapterIndex(0),   //Default adapter index is 0
  dxgiFactory(NULL),
  adapter(NULL),
  d3d11Device(NULL)
  {
    appName = applet.getName();
    if (args.has(XmNadapterIndex)) {
      adapterIndex = (UINT)args.get(XmNadapterIndex);
    }
    try {
      dxgiFactory           = new DirectXGIFactory();
      adapter               = new DirectXGIAdapter(*dxgiFactory, adapterIndex); 
      d3d11Device           = new Direct3D11Device(*adapter);
      d3d11ImmediateContext = new Direct3D11ImmediateContext(*d3d11Device);
      
    } catch (Exception& ex) {
      ex.display();
      ::exit(0);
    }
  
    //Default File menu calllbacks for IDM_EXIT and IDM_VERSION
    addCallback(XmNmenuCallback, IDM_NEW, this,
      (Callback)&DirectX3D11MainView::clear, NULL);
    addCallback(XmNmenuCallback, IDM_OPEN, this,
      (Callback)&DirectX3D11MainView::open, NULL);
    addCallback(XmNmenuCallback, IDM_SAVE, this,
      (Callback)&DirectX3D11MainView::save, NULL);
    addCallback(XmNmenuCallback, IDM_SAVEAS, this,
      (Callback)&DirectX3D11MainView::saveAs, NULL);
    addCallback(XmNmenuCallback, IDM_EXIT, this,
      (Callback)&DirectX3D11MainView::exit, NULL);

    addCallback(XmNmenuCallback, IDM_HELP, this,
      (Callback)&DirectX3D11MainView::help, NULL);

    addCallback(XmNmenuCallback, IDM_VERSION, this,
      (Callback)&DirectX3D11MainView::version, NULL);

    addEventHandler(WM_ERASEBKGND, this,
                    (Handler)&DirectX3D11MainView::eraseBackground, NULL);

    addEventHandler(WM_GETMINMAXINFO, this,
                    (Handler)&DirectX3D11MainView::getMinMaxInfo, NULL);
    addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D11MainView::size, NULL);

    addEventHandler(WM_RBUTTONDOWN, this,
                    (Handler)&DirectX3D11MainView::rButtonDown, NULL);
    
    addEventHandler(WM_RBUTTONUP, this,
                    (Handler)&DirectX3D11MainView::rButtonUp, NULL);

    addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D11MainView::lButtonDown, NULL);
    
    addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D11MainView::lButtonUp, NULL);
    
    addEventHandler(WM_MOUSEMOVE, this,
                    (Handler)&DirectX3D11MainView::mMouseMove, NULL);
    
    addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D11MainView::kDown, NULL);
  }

  ~DirectX3D11MainView()
  {
    delete d3d11ImmediateContext;
    delete d3d11Device;
    delete adapter;
    delete dxgiFactory;    
  }
};

}


