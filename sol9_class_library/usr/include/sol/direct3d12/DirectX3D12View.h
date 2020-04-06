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
 *  DirectX3D12View.h
 *
 *****************************************************************************/

//2016/10/04

#pragma once

#include <sol/ClientDC.h>
#include <sol/Mutex.h>

#include <sol/Primitive.h>
#include <sol/PaintDC.h>

#include <sol/dxgi/DXGISwapChainDesc.h>
#include <sol/dxgi/DirectXGIFactory4.h>
#include <sol/dxgi/DirectXGIDevice.h>
#include <sol/dxgi/DirectXGISwapChain1.h>
#include <sol/dxgi/DirectXGISwapChain3.h>

#include <sol/direct3d12/Direct3D12Device.h>
#include <sol/direct3d12/Direct3D12CommandQueue.h>


//2016/09/24
#include <sol/direct3dcommon/XMColor.h>


#include <sol/Stdio.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D12_VIEW (WM_USER+2021)

  
class DirectX3D12View :public Primitive {

private:
  static const UINT        FRAME_COUNT = 2;

  DirectXGIFactory4*       dxgiFactory4;  //Shallow copy from DirectX3DMainView

  Direct3D12Device*        d3d12Device;   //Shallow copy from DirectX3DMainView
  
  Direct3D12CommandQueue*  commandQueue; 
  DirectXGISwapChain3*     swapChain3;
  
private:
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
    //2016/10/25
    if (w > 0 && h >0) { 
      resize(w, h);
    }
    
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
  
  StringT<TCHAR> getShaderFilePath(const StringT<TCHAR>& directory, const TCHAR* filename)
  {
    TCHAR fullpath[MAX_PATH];
    //_stprintf_s(fullpath, CountOf(fullpath), 
    //      _T("%s\\..\\%s"), (const TCHAR*)directory, filename);
    _stprintf_s(fullpath, CountOf(fullpath), 
          _T("%s\\%s"), (const TCHAR*)directory, filename);
  	
    return StringT<TCHAR>(fullpath);
  }

  //Define a createSwapChain3 depending on your need.
  virtual void createSwapChain3()
  {
    try {
      HWND hwnd = getWindow();
      DXGI_SWAP_CHAIN_DESC swapChainDesc;
      ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
      swapChainDesc.BufferCount       = FRAME_COUNT;
      swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      swapChainDesc.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      swapChainDesc.OutputWindow      = hwnd;
      swapChainDesc.SampleDesc.Count  = 1;
      swapChainDesc.Windowed          = TRUE;
      swapChainDesc.SwapEffect        = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
      swapChainDesc.Flags             = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

     //3 Create a DirectXGISwapChain3.
      swapChain3 = new DirectXGISwapChain3(*dxgiFactory4, *commandQueue, &swapChainDesc);
      
      
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  //Define a createSwapChain3 depending on your need.
  virtual void createSwapChain3(UINT width, UINT height, UINT frameCount=2)
  {
    UINT MIN = 8;
    if (width < MIN) {
      width = MIN;
    }  
    if (height < MIN) {
      height= MIN;
    }  
    
    try {
      HWND hwnd = getWindow();
 
     // Create a DirectXGISwapChain3.
      swapChain3 = new DirectXGISwapChain3(*dxgiFactory4, 
                            *commandQueue, 
                            frameCount,
                            hwnd,
                            width,
                            height);
      
      
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  virtual long init(Event& event)
  {
    int width = 0;
    int height = 0;
    getClientSize(width, height);

    try {
      //1 Create a commandQueue
      commandQueue = new Direct3D12CommandQueue(*d3d12Device);

      
      //2016/11/10 
      //createSwapChain3();
      createSwapChain3(width, height);
      
     //3 Call a virtual initialize method, which may be redefined in your own subclass derived from this class.
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
  Direct3D12Device*  getD3D12Device()
  {
    return d3d12Device;
  }

  DirectXGISwapChain3* getSwapChain3()
  {
    return swapChain3;
  }

  Direct3D12CommandQueue* getCommandQueue()
  {
    return commandQueue;
  }

public:
  //Constructor
  DirectX3D12View()
  :Primitive(),
  dxgiFactory4(NULL),
  d3d12Device(NULL),
  commandQueue(NULL),
  swapChain3(NULL)
  { 
  }

public:
  //Constructor
  DirectX3D12View(DirectX3D12MainView* parent, const TCHAR* caption, Args& args)
  :Primitive(),
  dxgiFactory4(NULL),
  d3d12Device(NULL),
  commandQueue(NULL),
  swapChain3(NULL)
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(DirectX3D12MainView* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = False;
    try {
      //Shallow copies from the parent.
      d3d12Device    = parent -> getD3D12Device();
      dxgiFactory4   = parent -> getDXGIFactory4();

      rc = Primitive::create(parent, caption,  
                args.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE)
                    .set(XmNclassName, _T("DirectX3D12View")) );
                 // .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));

      addEventHandler(WM_INITIALIZE_DIRECTX3D12_VIEW, this,
                    (Handler)&DirectX3D12View::init, NULL);

      addEventHandler(WM_PAINT, this,
                    (Handler)&DirectX3D12View::paint, NULL);
    
      addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D12View::size, NULL);
    
      addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D12View::lButtonDown, NULL);
      addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D12View::lButtonUp, NULL);
      
      addEventHandler(WM_RBUTTONDOWN, this,
                    (Handler)&DirectX3D12View::rButtonDown, NULL);
      addEventHandler(WM_RBUTTONUP, this,
                    (Handler)&DirectX3D12View::rButtonUp, NULL);
      
      addEventHandler(WM_MOUSEMOVE, this,
                    (Handler)&DirectX3D12View::mMouseMove, NULL);
        
      addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D12View::kDown, NULL);
      addEventHandler(WM_KEYUP, this,
                    (Handler)&DirectX3D12View::kUp, NULL);
      
      post(WM_INITIALIZE_DIRECTX3D12_VIEW, 0, 0);

    } catch (Exception& ex) {
      ex.display();
    }  
    return rc;
  }

  ~DirectX3D12View()
  {
    delete commandQueue;
    delete swapChain3;
  }

  virtual void render()
  {
  }
};

}
