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
 *  OpenCVImageView.h
 *
 *****************************************************************************/

// 2017/04/10
// 2017/04/25 Update to support mouse callback and label.

// This is a simple elementary container window for OpenCVNamedWindow 
// which has a resizable normal window style.

#pragma once

#include <sol/Static.h>
#include <sol/ClientDC.h>
#include <sol/PaintDC.h>
#include <sol/StringT.h>
#include <sol/Stdio.h>
#include <sol/ApplicationView.h>

#include <sol/opencv/OpenCVNamedWindow.h>
#include <sol/opencv/OpenCVMouseCallback.h>

namespace SOL {
  
  
class OpenCVImageView :public Composite {
private:
  SmartPtr<Static>            label;  //2017/04/25
  SmartPtr<OpenCVNamedWindow> namedWindow;
  StringT<char>               imageFileName;
  int                         imageLoadingFlag;
  OpenCVMouseCallback         mouseCallback;
  
public:
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
      //nameWindow->show(image);
      display();
    }
    event.handled();
    return 1L;
  }
  
  void resizeNamedWindow(int w, int h)
  {
    namedWindow -> reshape(0, 0, w, h);
  }
  
  void moveNamedWindow(int x, int y)
  {
    int w, h;
    namedWindow->getWindowSize(w, h);
    
    namedWindow -> move(x, y, w, h);
  }
  
  void resizeNamedWindow(int x, int y, double winw, double winh, double imw, double imh)
  {
    //Adjust the size of nameWindw to the size of cv::Mat.
    
    //Image size;
    double rw  = winw / imw;
    double rh  = winh / imh;
    //We change the size of namedWindow to fit imageSize keeping the aspecto ratio of mat image size.
    if (imw <= winw && imh <= winh) {
      if (rw >= rh) {
        namedWindow -> reshape(x, y, int(imw * rh), int(imh * rh));
      } else {
        namedWindow -> reshape(x, y, int(imw * rw), int(imh * rw));
      }
    } else if (imw > winw && imh <= winh) {
      if ( rw >= rh) {
        namedWindow->reshape(x, y, int(imw * rh), int(imh* rh) );
      } else  {
        namedWindow->reshape(x, y, int(imw * rw), int(imh* rw) );
      } 
    } else if (imw <= winw && imh > winh) {
      if ( rw <= rh) {
        namedWindow->reshape(x, y, int(imw * rw), int(imh* rw) );
      } else  {
        namedWindow->reshape(x, y, int(imw * rw), int(imh* rw) );
      } 
    } else if (imw >= winw && imh >= winh) {
      if ( rw >= rh) {
        namedWindow->reshape(x, y, int(imw * rh), int(imh* rh) );
      } else  {
        namedWindow->reshape(x, y, int(imw * rw), int(imh* rw) );
      } 
    }
  }

  void show(cv::Mat& mat)
  {
    if (namedWindow) {
     namedWindow -> show(mat); 
    }
  }
  
  //Pure virtual 
  virtual cv::Mat& getMat() = 0;

  //2017/07/25 Define your own setImage method in a subclass derived from this class. 
  virtual void setImage(cv::Mat& mat)
  {
  }
  
  virtual long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);
    ClientDC cdc(this);
    SIZE size;
    cdc.getTextExtent(_T("A"), 1, &size);
    int h1 = size.cy;
    int x = 0;
    int y = 0; 

    if (label) {
      label-> reshape(0, 2, w, h1);
      //view    -> reshape(0, 3+h1, w, h-3-h1);
      y = h1 + 3;
      h = h - h1 -3;
    }
    if (namedWindow) {
      cv::Mat& mat = getMat();
      
      if (!mat.empty()) {
        double imw = (double)mat.cols; 
        double imh = (double)mat.rows;
        if (imw > 0.0 && imh > 0.0) {
          resizeNamedWindow(x, y, (double)w, (double)h, imw, imh);
        }
      }
    }
    event.handled();
    return 1;
  }
  
  void reshape(int x, int y, int w, int h)
  {
//    postResizeRequest(w, h);

    View::reshape(x, y, w, h);
    postResizeRequest(w, h);
  }
  
  cv::Mat readImage(const char* filename, int flag=CV_LOAD_IMAGE_COLOR)
  {
    imageFileName    = filename;
    imageLoadingFlag = flag;
    
    cv::Mat mat = cv::imread(filename, flag);
    if (mat.empty()) {
      throw IException("Failed to imread: %s  %d", filename, flag);
    }
    
    View::activate();
    setFocus();
    
    return mat;
  }

  cv::Mat reload()
  {
    return readImage((const char*)imageFileName, imageLoadingFlag);
  }
  

  void writeImage(const char* filename)
  {
    cv::Mat& mat = getMat();
    if (! cv::imwrite(filename, mat)) {
      throw IException("Failed to imwrite: %s", filename);
    }
  }
  
public:
  //Constructor
  OpenCVImageView(View* parent, const char* name, Args& args)
  :Composite(parent, name, 
            args.set(XmNclassName, "_OpenCVImageView_")
                .set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
                .set(XmNexStyle,    (LONG_PTR)WS_EX_CONTROLPARENT)
                .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW) //|CS_DBLCLICK)
                .set(XmNstyle,      (LONG_PTR)WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS)
                                    )
  { 
    char winname[128];
    ULONG id = HandleToUlong(getWindow());
    sprintf_s(winname, CountOf(winname), "cvname_%ul", id);
    
    if (args.has(XmNlabelString)) {
      const char* string = (const char*)args.get(XmNlabelString);
      Args ar;
      label = new Static(this, string, ar);
    }
    
    Args ar;
    namedWindow = new OpenCVNamedWindow(this, winname, ar);
    
    addEventHandler(WM_PAINT, this,
          (Handler)&OpenCVImageView::paint, NULL);
    addEventHandler(WM_SIZE, this,
          (Handler)&OpenCVImageView::size, NULL);
    addEventHandler(WM_DROPFILES, this, 
        (Handler)&OpenCVImageView::dropFiles, this);
  }

  ~OpenCVImageView()
  {
  }
  
  void refresh()
  {
    postResizeRequest();
    View::refresh();
  }
  
  OpenCVNamedWindow* getNamedWindow()
  {
    return namedWindow;
  }
  
  void addCallback(const char* name, Object* object, Callback callback, void* data)
  {
    if (name == XmNdropCallback) {
      //1 Let this view accept WM_DROPFILES message.
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
      const char* winname = (const char*)namedWindow->getWinName();
      mouseCallback.object   = object;
      mouseCallback.callback = callback;
      mouseCallback.data     = data;
    
      cvSetMouseCallback(winname, commonMouseCallback, this); 
    }
  }
 
private:
  // void (*CvMouseCallback )(int event, int x, int y, int flags, void* data);
  static void commonMouseCallback(int event, int x, int y, int flags, void* param)
  {
    OpenCVImageView* view = (OpenCVImageView*)param;
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


