/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenCVNamedWindow.h
 *
 *****************************************************************************/

// 2017/03/30
// This is a simple elementary wrapper class for a window created by cvNamedWindow
// API of OpenCV HighGui.

#pragma once

#include <sol/ClientDC.h>
#include <sol/PaintDC.h>
#include <sol/StringT.h>
#include <sol/Stdio.h>
#include <sol/ApplicationView.h>

#include <sol/opencv/OpenCVApplication.h>
#include <sol/opencv/OpenCVMouseCallback.h>

namespace SOL {

class OpenCVNamedWindow :public Composite {
private:
  WNDPROC              originalWndProc;
  
  HWND                 hInnerView;
  
  StringT<char>        winname;
 
  OpenCVMouseCallback  mouseCallback;

public:
  long eraseBackground(Event& event)
  {
    WPARAM wParam = event.getWParam();
    
    HWND hwnd = getWindow();
    RECT rc;
    GetClientRect(hwnd, &rc); 

    FillRect((HDC)wParam, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH)); 
    event.handled();
    return 1L;
  }
  
  
  //WM_DROPFILES event handler.
  long dropFiles(Event& event)
  {
    HWND hwnd = getWindow();
    callCallback(XmNdropCallback, (Key)hwnd, NULL, event);
    event.handled();
    return 1;
  }

  long paint(Event& event)
  {
    PaintDC dc(this);
    {
    //Call a virtual display method.
      display();
    }
    event.handled();
    return 1L;
  }

  //Please define your own display method in your subclass derived from this class.
  virtual void display()
  {
  }
   
public:
  const char* getViewName()
  {
    return (const char*)winname;
  }
  
  WNDPROC getOriginalWndProc()
  {
    return originalWndProc;
  }
  
  HWND getInnerWindow()
  {
    return hInnerView;
  }
  
  void show(cv::Mat& mat)
  {
    const char* name = getViewName();
    if (!mat.empty()) {
      imshow(name, mat);
    }
  }
 
  cv::Mat readImage(const char* filename, int flag=CV_LOAD_IMAGE_COLOR)
  {
    cv::Mat mat =imread(filename, flag);
    if (mat.empty()) {
      throw IException("Failed to imread: %s  %d", filename, flag);
    }
    return mat;
  }
  
  
  void writeImage(const char* filename, cv::Mat& mat)
  {
    if (! cv::imwrite(filename, mat)) {
      throw IException("Failed to imwrite: %s", filename);
    }
  }
  
public:
  //Constructor
  OpenCVNamedWindow(View* parent, const char* name, Args& args)
  :Composite(),
  originalWndProc(nullptr),
  hInnerView(nullptr),
  winname(name)
  {    
    if (name == nullptr || strlen(name) == 0) {
      throw IException("Invalid name parameter.");
    }
    
    int style = CV_GUI_NORMAL;
 
    //1 Create a hidden frame window and an inner view by HighGui API of OpenCV.
    //namedWindow(name, style);
    
    if ( !::cvNamedWindow(name, style) ) {
      throw IException("Failed to create a named window.");
    }
   
    
    //2 Get a window handle of the innerView
    hInnerView= (HWND)::cvGetWindowHandle(name);

    //3 Get a window handle of the frame window of the inner view. 
    HWND hFrame = GetParent(hInnerView);  //MainWindow

    //4 Change the windows style of the hFram.
    LONG ws = (LONG)GetWindowLong(hFrame, GWL_STYLE);
    //Remove  WS_OVERLAPPEDWINDOW style from the hFrame.
    ws ^= WS_OVERLAPPEDWINDOW;
    ws |= (WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
    if (args.has(XmNstyle)) {
      ws |= (int)args.get(XmNstyle);
    }
    SetWindowLong(hFrame, GWL_STYLE, ws) ;
  
    //5 Change the parent of hFrame of OpenCV to be the parent view hParent.
    HWND hParent = parent->getWindow();
    SetParent(hFrame, hParent);
    setWindow(hFrame);
  
    //6 Register a pair of hFrame of OpenCV and this to a hash talbe in Application class. 
    Application::add(hFrame, this);

    //7 Suclassing, in the sense of Windows, OpenCV MainFrame window,
    // by replacing an orignal window procedure of hFrane of OpenCV  with the OpenCVNamedWindow::mainWindowProc.
    originalWndProc = (WNDPROC)SetWindowLongPtr(hFrame, GWLP_WNDPROC, (LONG_PTR)mainWndProc);
    
    addEventHandler(WM_PAINT, this,
          (Handler)&OpenCVNamedWindow::paint, NULL);

    addEventHandler(WM_DROPFILES, this, 
          (Handler)&OpenCVNamedWindow::dropFiles, this);

  }

  ~OpenCVNamedWindow()
  {
  }
  
 
  const char* getWinName()
  {
    return (const char*)winname;
  }

  void addCallback(const char* name, Object* object, Callback callback, void* data)
  {
    if (name == XmNdropCallback) {
      // Let this view accept WM_DROPFILES message.
      dragAcceptFiles(TRUE);
      View::addCallback(name, (const Key)getWindow(), object, callback, data);
      
    } else {
      View::addCallback(name, object, callback, data);
    }
  }  

  //This will simply overwrite an existing mouseCallback entry if already registered, 
  //instead of adding a new entry.
  void addCallback(const char* name, Object* object, MouseCallback callback, void* data)
  {
    if (name == XmNmouseCallback) {
      mouseCallback.object   = object;
      mouseCallback.callback = callback;
      mouseCallback.data     = data;
    
      cv::setMouseCallback((const char*)winname, commonMouseCallback, this); 
    }
  }

private:
  static 
  LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    LRESULT result = 0;
    
    OpenCVNamedWindow* view = (OpenCVNamedWindow*)Application::lookup(hWnd);
    
    bool handled = false;
    
    if (view) {
      WNDPROC originalWndProc = view->getOriginalWndProc();
      
      //Call a virtual dispatch method of View.
      Event event(uMsg, wParam, lParam);
      result = view -> dispatch(event); //uMsg, wParam, lParam, handled);
      
      if (event.isHandled() == false) {
        if (originalWndProc) {
          return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
        } else {
          return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
      } else {
        return result;
      }
    } else {
      //Not found a view instance in Application lookup hashtable.
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
  }  
  
 
private:
  // void (*CvMouseCallback )(int event, int x, int y, int flags, void* data);
  static void commonMouseCallback(int event, int x, int y, int flags, void* param)
  {
    OpenCVNamedWindow* view = (OpenCVNamedWindow*)param;
    if (view) {
      MouseCallback callback   = view->mouseCallback.callback;
      Object*         object   = view->mouseCallback.object;
      void*           data     = view->mouseCallback.data;
      //Call instant method callback of callee object.
      (object->*callback)(event, x, y, flags, data);
    }
  }
  
};

}

