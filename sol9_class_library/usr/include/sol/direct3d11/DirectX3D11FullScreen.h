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
 *  DirectX3D11FullScreen.h
 *
 *****************************************************************************/

// 2016/01/10

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
#include <sol/dxgi/DXGISwapChainDesc.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D11_MAINVIEW (WM_USER+2026)

class DirectX3D11FullScreen :public ApplicationView {
  
public:
  StringT<TCHAR> appName;

  UINT                adapterIndex;
  DirectXGIFactory*   dxgiFactory;
  DirectXGIAdapter*   adapter;

  Direct3D11Device*   d3d11Device;
  Direct3D11ImmediateContext* d3d11ImmediateContext;

  DirectXGISwapChain* swapChain; 

public:
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

public:
  void validateClientSize(int& width, int& height)
  {
    static const int MIN_WIDTH = 8;
    getClientSize(width, height);
    if (width < MIN_WIDTH ) {
      width = MIN_WIDTH;
    }
    if ( height < MIN_WIDTH) {
      height = MIN_WIDTH;
    }
  }
  
  //Event handler for WM_SIZE
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

  // Event handler for WM_PAINT
  long paint(Event& event)
  {
    PaintDC(this);
    {
      // Call a vitual display method/
      display();
    }

    return 0;
  }

  // Please define you own display method in the subclass derived from this class.
  virtual void display()
  {
  }

  // Event handler for WM_PAINT
  long init(Event& event)
  {
    int  width = 0;
    int  height = 0;   
    getClientSize(width, height);
    
    try {
      dxgiFactory = new DirectXGIFactory();
      adapter     = new DirectXGIAdapter(*dxgiFactory, adapterIndex); // 
      
      d3d11Device  = new Direct3D11Device(*adapter);
      d3d11ImmediateContext = new Direct3D11ImmediateContext(*d3d11Device);
      
      Args ar;
      ar.set(XmNbufferCount, 1);
      ar.set(XmNwidth,   width);
      ar.set(XmNheight,  height);
      ar.set(XmNformat, DXGI_FORMAT_R8G8B8A8_UNORM);
      ar.set(XmNrefreshRateNumerator, 60);
      ar.set(XmNrefreshRateDenominator, 1);
      ar.set(XmNsampleDescCount, 1);
      ar.set(XmNsampleDescQuality, 0);
      ar.set(XmNwindowed, TRUE);
      DXGISwapChainDesc swapChainDesc(getWindow(), ar);

      swapChain    = new DirectXGISwapChain(*dxgiFactory, *d3d11Device, swapChainDesc);

      swapChain ->setFullscreenState(TRUE, NULL);
      
    } catch (Exception& ex) {
      ex.display();
    }

    //Call a virtual initialize method.
    initialize();

    return 0;
  }
  
  // Please define you own initialize method in the subclass derived from this class.
  virtual void initialize()
  {
  }
  
  //Please define your own setViewPort method in subclass derived form this class, if needed.
  virtual void setViewPort(int width, int height)
  {
    if (d3d11ImmediateContext) {
      D3D11_VIEWPORT vport;
      memset(&vport, 0, sizeof(vport));
      vport.Width            = (float)width;
      vport.Height           = (float)height;
      vport.MaxDepth         = 1.0f;

      d3d11ImmediateContext ->setRSViewports(1, &vport);
    }
  }

  virtual long getMinMaxInfo(Event& event)
  {
    MINMAXINFO* info = (MINMAXINFO*)event.getLParam();
    static const int MIN_WIDTH  = 400;
    static const int MIN_HEIGHT = 400;
    
    info -> ptMinTrackSize.x = MIN_WIDTH;
    info -> ptMinTrackSize.y = MIN_HEIGHT;

    return 0;
  }
  
public:
  //Constructor
  DirectX3D11FullScreen(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
  adapterIndex(0),   //Default adapter index is 0
  dxgiFactory(NULL),
  adapter(NULL),
  d3d11Device(NULL),
  d3d11ImmediateContext(NULL),
  swapChain(NULL)
  {
    appName = applet.getName();
    if (args.has(XmNadapterIndex)) {
      adapterIndex = (UINT)args.get(XmNadapterIndex);
    }
  
    addEventHandler(WM_INITIALIZE_DIRECTX3D11_MAINVIEW, this,
                    (Handler)&DirectX3D11FullScreen::init, NULL);

    addEventHandler(WM_PAINT, this,
                    (Handler)&DirectX3D11FullScreen::paint, NULL);
    addEventHandler(WM_GETMINMAXINFO, this,
                    (Handler)&DirectX3D11FullScreen::getMinMaxInfo, NULL);
    
    addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D11FullScreen::size, NULL);

    addEventHandler(WM_RBUTTONDOWN, this,
                    (Handler)&DirectX3D11FullScreen::rButtonDown, NULL);
    
    addEventHandler(WM_RBUTTONUP, this,
                    (Handler)&DirectX3D11FullScreen::rButtonUp, NULL);

    addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D11FullScreen::lButtonDown, NULL);
    
    addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D11FullScreen::lButtonUp, NULL);
    
    addEventHandler(WM_MOUSEMOVE, this,
                    (Handler)&DirectX3D11FullScreen::mMouseMove, NULL);
    
    addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D11FullScreen::kDown, NULL);
    
    post(WM_INITIALIZE_DIRECTX3D11_MAINVIEW);

  }

  ~DirectX3D11FullScreen()
  {
    delete swapChain;
    delete d3d11ImmediateContext;

    delete d3d11Device;
    delete adapter;
    delete dxgiFactory;
    
  }
};

}


