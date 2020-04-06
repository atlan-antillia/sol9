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
 *  DirectX3D12MainView.h
 *
 *****************************************************************************/

// 2016/11/12 Updated to register an eventHandler for WM_INITIALIZE_DIRECTX3D12_MAINVIEW message.
// 2016/11/14 Modified to use Direct3D12Device(DXGIFactory4*) to create a Direct3D12Device object.

#pragma once

#include <sol/ApplicationView.h>
#include <sol/String.h>
#include <sol/StringT.h>
#include <sol/PaintDC.h>
#include <sol/Stdio.h>
#include <sol/dxgi/DirectXGIFactory4.h>

#include <sol/dxgi/DirectXGIAdapter.h>
#include <sol/dxgi/DirectXGISwapChain3.h>
#include <sol/direct3d12/Direct3D12Device.h>
#include <sol/dxgi/DirectXGIFactory3.h>

namespace SOL {

#define WM_INITIALIZE_DIRECTX3D12_MAINVIEW (WM_USER+2030)

class DirectX3D12MainView :public ApplicationView {
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

  DirectXGIFactory4*  dxgiFactory4;

  DirectXGIAdapter*   adapter;

  Direct3D12Device*   d3d12Device;
    
public:
  long eraseBackground(Event& event)
  {
    WPARAM wParam = event.getWParam();
    RECT rc;
    HWND hwnd = getWindow();
    GetClientRect(hwnd, &rc);
    FillRect((HDC)wParam, &rc, (HBRUSH)GetClassLongPtr(hwnd, GCLP_HBRBACKGROUND));

    return 1L;
  }
  
private:
  long init(Event& event)
  {
    initialize();
    return 1L;
  }
  
  virtual void initialize()
  {
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
  
  virtual void display()
  {
  }
  
  long size(Event& event)
  {
    int width = 0;
    int height = 0;
    event.getSize(width, height);
    //Call a virtual resize method.
    if (width > 0 && height > 0) {
      resize(width, height);
    }
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

  DirectXGIFactory4* getDXGIFactory4()
  {
    return  dxgiFactory4;
  }

  Direct3D12Device* getD3D12Device()
  {
    return d3d12Device;
  }
  
  const TCHAR* getAppName()
  {
    return (const TCHAR*)appName;
  }
  
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
  
  virtual long getMinMaxInfo(Event& event)
  {
    MINMAXINFO* info = (MINMAXINFO*)event.getLParam();
    static const int MIN_WIDTH  = 200;
    static const int MIN_HEIGHT = 200;
    
    info -> ptMinTrackSize.x = MIN_WIDTH;
    info -> ptMinTrackSize.y = MIN_HEIGHT;

    return 0;
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
  
public:
  //Constructor
  DirectX3D12MainView(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
  adapterIndex(0),   //Default adapter index is 0
  dxgiFactory4(NULL),
  adapter(NULL),
  d3d12Device(NULL)
  {
    appName = applet.getName();
    if (args.has(XmNadapterIndex)) {
      adapterIndex = (UINT)args.get(XmNadapterIndex);
    }
    try {
      dxgiFactory4 = new DirectXGIFactory4();
      //2016/11/14
      d3d12Device  = new Direct3D12Device(*dxgiFactory4);
      // d3d12Device  = new Direct3D12Device();
      
      adapter      = new DirectXGIAdapter(*dxgiFactory4);

      D3D12_FEATURE_DATA_D3D12_OPTIONS options;
      d3d12Device->checkFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, (void*)&options, sizeof(options));

    } catch (Exception& ex) {
      ex.display();
      ::exit(0);
    }
        
    //Default File menu calllbacks for IDM_EXIT and IDM_VERSION
    addCallback(XmNmenuCallback, IDM_NEW, this,
      (Callback)&DirectX3D12MainView::clear, NULL);
    addCallback(XmNmenuCallback, IDM_OPEN, this,
      (Callback)&DirectX3D12MainView::open, NULL);
    addCallback(XmNmenuCallback, IDM_SAVE, this,
      (Callback)&DirectX3D12MainView::save, NULL);
    addCallback(XmNmenuCallback, IDM_SAVEAS, this,
      (Callback)&DirectX3D12MainView::saveAs, NULL);
    addCallback(XmNmenuCallback, IDM_EXIT, this,
      (Callback)&DirectX3D12MainView::exit, NULL);

    addCallback(XmNmenuCallback, IDM_HELP, this,
      (Callback)&DirectX3D12MainView::help, NULL);

    addCallback(XmNmenuCallback, IDM_VERSION, this,
      (Callback)&DirectX3D12MainView::version, NULL);

    addEventHandler(WM_INITIALIZE_DIRECTX3D12_MAINVIEW, this,
                    (Handler)&DirectX3D12MainView::init, NULL);

    addEventHandler(WM_ERASEBKGND, this,
                    (Handler)&DirectX3D12MainView::eraseBackground, NULL);
     //2016/11/11
    addEventHandler(WM_PAINT, this,
                    (Handler)&DirectX3D12MainView::paint, NULL);
 
    addEventHandler(WM_GETMINMAXINFO, this,
                    (Handler)&DirectX3D12MainView::getMinMaxInfo, NULL);
    addEventHandler(WM_SIZE, this,
                    (Handler)&DirectX3D12MainView::size, NULL);

    addEventHandler(WM_RBUTTONDOWN, this,
                    (Handler)&DirectX3D12MainView::rButtonDown, NULL);
    
    addEventHandler(WM_RBUTTONUP, this,
                    (Handler)&DirectX3D12MainView::rButtonUp, NULL);

    addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectX3D12MainView::lButtonDown, NULL);
    
    addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectX3D12MainView::lButtonUp, NULL);
    
    addEventHandler(WM_MOUSEMOVE, this,
                    (Handler)&DirectX3D12MainView::mMouseMove, NULL);
    
    addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectX3D12MainView::kDown, NULL);
    post(WM_INITIALIZE_DIRECTX3D12_MAINVIEW);
  }

  ~DirectX3D12MainView()
  {
 
    delete d3d12Device;
    delete adapter;
    delete dxgiFactory4;

  }
};

}


