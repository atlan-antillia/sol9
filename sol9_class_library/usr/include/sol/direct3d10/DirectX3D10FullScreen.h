/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectX3D10FullScreen.h
 *
 *****************************************************************************/

// 2015/10/01

#pragma once

#include <sol/ApplicationView.h>
#include <sol/String.h>
#include <sol/StringT.h>
#include <sol/PaintDC.h>
#include <sol/Stdio.h>
#include <sol/dxgi/DirectXGIFactory.h>
#include <sol/dxgi/DirectXGIAdapter.h>
#include <sol/dxgi/DirectXGISwapChain.h>
#include <sol/direct3d10/Direct3D10Device.h>
#include <sol/dxgi/DXGISwapChainDesc.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D10_MAINVIEW (WM_USER+2015)

class DirectX3D10FullScreen :public ApplicationView {
  
public:
  StringT<TCHAR> appName;

  UINT                adapterIndex;
  DirectXGIFactory*   dxgiFactory;
  DirectXGIAdapter*   adapter;

  Direct3D10Device*   d3d10Device;
  DirectXGISwapChain* swapChain; 
  
public:

  long init(Event& event)
  {
    int  width = 0;
    int  height = 0;   
    getClientSize(width, height);

    try {
      dxgiFactory = new DirectXGIFactory();
      adapter     = new DirectXGIAdapter(*dxgiFactory, adapterIndex); // 
      
      d3d10Device  = new Direct3D10Device(*adapter);
   
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

      swapChain    = new DirectXGISwapChain(*dxgiFactory, *d3d10Device, swapChainDesc);

      swapChain ->setFullscreenState(TRUE, NULL);
      
      //Call a virtual initialize method which should be redefined in a subclass derived from this class,
      initialize();

    } catch (Exception& ex) {
      ex.display();
    }

    return 1;
  }

  long paint(Event& event)
  {
    PaintDC dc(this);
    if (d3d10Device && swapChain) {
      //Call a virtual display method to render something d3d10 contents.
      display();
    }
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

  long lButtonDown(Event& event)
  {
    leftButtonDown(event);
    return 0L;
  }


  long lButtonUp(Event& event)
  {
    leftButtonUp(event);
    return 0L;
  }

  long kDown(Event& event)
  {
    keyDown(event);
    return 0L;
  }

  long kUp(Event& event)
  {
    keyUp(event);
    return 0L;
  }
  
  virtual void initialize()
  {
  }

  virtual void display()
  {
  }

   //Please define your own resize method in subclass derived form this class.
  virtual void resize(int w, int h)
  {
  }
  
  //Please define your own method in subclass derived form this class.
  virtual void leftButtonUp(Event& event)
  {
  }
  
  virtual void leftButtonDown(Event& event)
  {
  }

  //Please define your own method in subclass derived form this class.
  virtual void keyDown(Event& event)
  {
  }
  
  virtual void keyUp(Event& event)
  {
  }

  
public:
  DirectXGIFactory* getDXGIFactory()
  {
    return  dxgiFactory;
  }

  Direct3D10Device* getD3D10Device()
  {
    return d3d10Device;
  }
  
  DirectXGISwapChain* getSwapChain()
  {
    return swapChain;
  }
  
  const TCHAR* getAppName()
  {
    return (const TCHAR*)appName;
  }
  
  //Please define your own setViewPort method in subclass derived form this class, if needed.
  virtual void setViewPort(int width, int height)
  {
    if (d3d10Device) {
      D3D10_VIEWPORT vport;
      memset(&vport, 0, sizeof(vport));
      vport.Width            = width;
      vport.Height           = height;
      vport.MaxDepth         = 1.0f;

      d3d10Device ->setRSViewports(1, &vport);
    }
  }

public:
  //Constructor
  DirectX3D10FullScreen(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
  adapterIndex(0),   //Default adapter index is 0
  dxgiFactory(NULL),
  adapter(NULL),
  d3d10Device(NULL),
  swapChain(NULL)
  {
    appName = applet.getName();
    if (args.has(XmNadapterIndex)) {
      adapterIndex = (UINT)args.get(XmNadapterIndex);
    }

    //EventHanlders
    addEventHandler(WM_INITIALIZE_DIRECTX3D10_MAINVIEW, this,
                    (Handler)&DirectX3D10FullScreen::init, NULL);
       
    addEventHandler(WM_PAINT, this,
                    (Handler)&DirectX3D10FullScreen::paint, NULL);
    
    addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D10FullScreen::size, NULL);
    
    addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D10FullScreen::lButtonDown, NULL);
    addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D10FullScreen::lButtonUp, NULL);
    
    addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D10FullScreen::kDown, NULL);
    addEventHandler(WM_KEYUP, this,
                    (Handler)&DirectX3D10FullScreen::kUp, NULL);

    post(WM_INITIALIZE_DIRECTX3D10_MAINVIEW);
  }

  ~DirectX3D10FullScreen()
  {
    delete d3d10Device;
    delete swapChain;
    delete adapter;
    delete dxgiFactory;
    
  }
};

}


