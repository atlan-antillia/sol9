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
 *  OpenCVVideoCaptureView.h
 *
 *****************************************************************************/

// 2017/07/20
// On cv::VideoCapture
// See: http://docs.opencv.org/3.1.0/d8/dfe/classcv_1_1VideoCapture.html

#pragma once

#include <sol/StringT.h>
#include <sol/File.h>

#include <sol/opencv/OpenCVApplication.h>

#include <sol/opencv/OpenCVVideoCapture.h>
#include <sol/opencv/OpenCVImageView.h>

#include <sol/opencv/OpenCVApplicationView.h>

namespace SOL {
  
class OpenCVVideoCaptureView :public OpenCVApplicationView {
private:
  static const int INVALID_DEVICE_INDEX= -1;

  StringT<char>       videoFileName;    
  int                 deviceIndex;
  
  OpenCVVideoCapture  videoCapture;
  
  //Define your own render method in a subclass derived from this class.
  virtual void render()
  {
    //1 cv::Mat frame;
    // OpenCVVideoImageView::readVideoFrame(frame);
    //2 For example, you may call imshow to display the frame on a cvNamedWindow of
    // windowName.
    // OpenCVNamedWindow* window;
    // window->show(frame);
    // or
    // OpenCVImageView* view;
    // view->display();
  }

public:
  //Constructor
  OpenCVVideoCaptureView(OpenCVApplication& applet, const TCHAR* caption, Args& args)
  :OpenCVApplicationView(applet, caption, 
          args.set(XmNclassName, _T("_OpenCVVideoCaptureView_")) 
          .set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
          .set(XmNexStyle, (LONG_PTR)WS_EX_CONTROLPARENT)
          .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW)
          .set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN) )
  ,deviceIndex(INVALID_DEVICE_INDEX)
  {    
    bool autoStart = (bool)args.get(XmNcaptureAutoStart);
  
   if (args.has(XmNvideoDeviceIndex)) {
      deviceIndex    = (int)args.get(XmNvideoDeviceIndex);
      if (autoStart) {
        openDevice(deviceIndex);
      }
    } else if (args.has(XmNvideoFileName)) {

      const char* filename = (const char*)args.get(XmNvideoFileName);
      if (autoStart) {
         openDevice(filename);
      }
    }    
  }

  ~OpenCVVideoCaptureView()
  {
  }

  void closeDevice()
  {
    videoCapture.close();
    const char* appName = getAppName();
    
    setText(appName);   
  }
  
  void openDevice(int device)
  {
    try {
      videoCapture.open(device);
    
      const char* appName = getAppName();
    
      char title[MAX_PATH];
      sprintf(title, "Capturing deviceIndex=%d  - %s", deviceIndex, appName);
      setText(title);
    } catch (SOL::Exception& ex) {
      caught(ex);
    }
  }
  
  void openDevice(const char* filename)
  {
    File file;
    if (!file.isExistent(filename) ) {
      throw IException("Invalid video filename=%s", filename);
    }

    videoFileName = filename;

    try {
      videoCapture.open(filename);
    
      const char* appName = getAppName();
    
      char title[MAX_PATH];
      sprintf(title, "Capturing filename=%s - %s", filename, appName);
      setText(title);
    } catch (SOL::Exception& ex) {
      caught(ex);
    }
  }

  //Please define your own callbacks in your subclass derived from this class.
  virtual void stopCapture(Action& action)
  {
    videoCapture.close();
    setText(getAppName() );
  }
  
  void startCapture(Action& action)
  {
    openDevice(deviceIndex);
  }
  
  bool readVideoFrame(cv::Mat& frame)
  {
    if (videoCapture.isOpened()) {
      return videoCapture.read(frame);
    } else {
      return false;
    }
  }

  cv::VideoCapture& getVideoCapture()
  {
    return videoCapture.getVideoCapture();
  }
  
  void setImageViewSize(OpenCVImageView* view)
  {
    cv::Mat frame;
    if (readVideoFrame(frame)) {
      if (!frame.empty() && view) {
        view -> setImage(frame);
        view -> postResizeRequest();
      }
    }
  }
};

}


