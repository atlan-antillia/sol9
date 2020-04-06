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
 *  DirectX3D11View.h
 *
 *****************************************************************************/

//2016/01/04

#pragma once

#include <sol/ClientDC.h>
#include <sol/Mutex.h>

#include <sol/Primitive.h>
#include <sol/PaintDC.h>

#include <sol/direct3d11/Direct3D11Device.h>
#include <sol/direct3d11/Direct3D11ImmediateContext.h>
#include <sol/direct3d11/Direct3D11DeferredContext.h>
#include <sol/direct3d11/XMMatrix.h>
#include <sol/direct3d11/XMVector.h>

#include <sol/dxgi/DXGISwapChainDesc.h>

#include <sol/dxgi/DirectXGIFactory.h>
#include <sol/dxgi/DirectXGIDevice.h>
#include <sol/dxgi/DirectXGISwapChain.h>
//2016/09/24
#include <sol/direct3dcommon/XMColor.h>


#include <sol/Stdio.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D11_VIEW (WM_USER+2021)

  
class DirectX3D11View :public Primitive {

private:
  //Shallow copy from the parent (DirectX3D11MainView)
  DirectXGIFactory*        dxgiFactory;

  //Shallow copy from the parent (DirectX3D11MainView)
  Direct3D11Device*        d3d11Device;
  
  //Shallow copy from the parent (DirectX3D11MainView)
  Direct3D11ImmediateContext* d3d11ImmediateContext;
  //
  DirectXGISwapChain*      swapChain;
 
private:
  
  long eraseBackground(Event& event)
  {
    return 1L;
  }

  long paint(Event& event)
  {
    PaintDC dc(this);
    {
    //Call a virtual display method.
      display();
    }
    return 1L;
  }

  long size(Event& event)
  {
    int w = 0;
    int h = 0;
    event.getSize(w, h);
  //Call a virtual resize method.
    resize(w, h);
    
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

  long rButtonDown(Event& event)
  {
    rightButtonDown(event);
    return 0L;
  }


  long rButtonUp(Event& event)
  {
    rightButtonUp(event);
    return 0L;
  }

  long mMouseMove(Event& event)
  {
    mouseMove(event);
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

public:

  //Please define your own display method in subclass derived form this class.
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
  virtual void rightButtonUp(Event& event)
  {
  }
  
  virtual void rightButtonDown(Event& event)
  {
  }

  virtual void mouseMove(Event& event)
  {
  }

  //Please define your own method in subclass derived form this class.
  virtual void keyDown(Event& event)
  {
  }
  
  virtual void keyUp(Event& event)
  {
  }

  //Please define your own setViewPort method in subclass derived form this class, if needed.
  virtual void setViewPort(int width, int height)
  {
    if (d3d11ImmediateContext) {
      D3D11_VIEWPORT vport;
      memset(&vport, 0, sizeof(vport));
      vport.Width            = (FLOAT)width;
      vport.Height           = (FLOAT)height;
      vport.MaxDepth         = 1.0f;

      d3d11ImmediateContext ->setRSViewports(1, &vport);
    }
  }

  virtual long init(Event& event)
  {
    int width = 0;
    int height = 0;
    getClientSize(width, height);
    try {
      Args ar;
      ar.set(XmNbufferCount, 1);
      ar.set(XmNwidth,   width);
      ar.set(XmNheight,  height);
      ar.set(XmNformat, DXGI_FORMAT_R8G8B8A8_UNORM);
      ar.set(XmNrefreshRateNumerator, 60);
      ar.set(XmNrefreshRateDenominator, 1);
      ar.set(XmNbufferUsage, DXGI_USAGE_RENDER_TARGET_OUTPUT);
      ar.set(XmNsampleDescCount, 1);
      ar.set(XmNsampleDescQuality, 0);
      ar.set(XmNwindowed, TRUE);
      HWND hwnd = getWindow();
      DXGISwapChainDesc swapChainDesc(hwnd, ar);
     
      swapChain    = new DirectXGISwapChain(*dxgiFactory, *d3d11Device, swapChainDesc);

    //Call a virtual initialize method,
     initialize();
    } catch (Exception& ex) {
       ex.display();
    }
     return 0;
  }
  
  //Please define your own initialize method in the subclass derived from this class.
  virtual void initialize()
  {
  }
  
public:
  Direct3D11Device*  getD3D11Device()
  {
    return d3d11Device;
  }

  Direct3D11ImmediateContext*  getD3D11ImmediateContext()
  {
    return d3d11ImmediateContext;
  }

  DirectXGISwapChain* getSwapChain()
  {
    return swapChain;
  }
  
public:
  //Constructor
  DirectX3D11View()
  :Primitive(),
  dxgiFactory(NULL),
  d3d11Device(NULL),
  d3d11ImmediateContext(NULL),
  swapChain(NULL)
  { 
  }

public:
  //Constructor
  DirectX3D11View(DirectX3D11MainView* parent, const TCHAR* caption, Args& args)
  :Primitive(),
  dxgiFactory(NULL),
  d3d11Device(NULL),
  d3d11ImmediateContext(NULL),
  swapChain(NULL)
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(DirectX3D11MainView* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = False;
    try {
      d3d11Device           = parent -> getD3D11Device();
      d3d11ImmediateContext = parent -> getD3D11ImmediateContext();
      dxgiFactory           = parent -> getDXGIFactory();

      rc = Primitive::create(parent, caption,  
                args.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE)
                    .set(XmNclassName, _T("DirectX3D11View")) 
                     .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));

      addEventHandler(WM_INITIALIZE_DIRECTX3D11_VIEW, this,
                    (Handler)&DirectX3D11View::init, NULL);

      addEventHandler(WM_PAINT, this,
                    (Handler)&DirectX3D11View::paint, NULL);
    
      addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D11View::size, NULL);
    
      addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D11View::lButtonDown, NULL);
      addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D11View::lButtonUp, NULL);
      
      addEventHandler(WM_RBUTTONDOWN, this,
                    (Handler)&DirectX3D11View::rButtonDown, NULL);
      addEventHandler(WM_RBUTTONUP, this,
                    (Handler)&DirectX3D11View::rButtonUp, NULL);
      
      addEventHandler(WM_MOUSEMOVE, this,
                    (Handler)&DirectX3D11View::mMouseMove, NULL);
        
      addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D11View::kDown, NULL);
      addEventHandler(WM_KEYUP, this,
                    (Handler)&DirectX3D11View::kUp, NULL);
      
      post(WM_INITIALIZE_DIRECTX3D11_VIEW, 0, 0);

    } catch (Exception& ex) {
      ex.display();
    }  
    return rc;
  }

  ~DirectX3D11View()
  {
    delete swapChain;
  }

  virtual void render()
  {
  }


};

}
