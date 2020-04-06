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
 *  OpenCVVideoCaptureThread.h
 *
 *****************************************************************************/

// 2017/07/20
// On cv::VideoCapture
// See: http://docs.opencv.org/3.1.0/d8/dfe/classcv_1_1VideoCapture.html

#pragma once

#include <sol/StringT.h>
#include <sol/Thread.h>
#include <sol/opencv/OpenCVApplication.h>
#include <sol/opencv/OpenCVVideoCapture.h>
#include <sol/opencv/OpenCVApplicationView.h>
#include <sol/opencv/OpenCVScrolledImageView.h>

namespace SOL {
  
class OpenCVVideoCaptureThread :public Thread {
private:
  static const int  INVALID_DEVICE_INDEX  = -1;
  static const int  DEFAULT_INTERVAL_MSEC = 30;
  
  OpenCVScrolledImageView*   view;  //Shallow copy
  int               deviceIndex;
  StringT<char>     videoFileName;
  
  cv::VideoCapture  videoCapture;
  int               capturingInterval; //millsecond
  
  bool              looping;
  
public:
  //Constructor which creates a suspenced thread.
  OpenCVVideoCaptureThread(OpenCVScrolledImageView* renderv, int deviceId, int interval = DEFAULT_INTERVAL_MSEC)
  :Thread(),
  view(renderv),
  deviceIndex(deviceId),
  videoFileName(""),
  capturingInterval(interval),
  looping(true)
  {    
    if (interval <5 || interval > 1000) {
      interval = DEFAULT_INTERVAL_MSEC;
    }
  }
  
public:
  //Constructor which creates a suspenced thread.
  OpenCVVideoCaptureThread(OpenCVScrolledImageView* renderv, const char* filename, int millisec = 40)
  :Thread(),
  view(renderv),
  deviceIndex(INVALID_DEVICE_INDEX),
  videoFileName(filename),
  capturingInterval(millisec),
  looping(true)
  {    
  }

  ~OpenCVVideoCaptureThread()
  {
    close();
  }
  

  //Thread main procedure which can be started by Thread::start method.
  virtual void run()
  {
    if (deviceIndex != INVALID_DEVICE_INDEX) {
      open(deviceIndex);
    }
    
    if (!videoFileName.isEmpty()) {
      open(videoFileName);
    }
    
    MSG msg = {0};
    while( looping ) {
      if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )  {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      } else {
        if (view) {
          cv::Mat frame;
          //Read a video frame from a videoCapture object, 
          if (read(frame)) {
            //and set the frame to the view, and call display method of the view.
            view->setImage(frame);
            //view->display();
          }
        }
        Sleep(capturingInterval);
      }
    }
  }

  void open(int deviceIndex)
  {
    close();
    
    if (videoCapture.open(deviceIndex)) {
      if (!videoCapture.isOpened()) {
        throw IException("Failed to open deviceIndex=%d", deviceIndex);
      }
    }
  }

  bool isOpened()
  {
    return videoCapture.isOpened();
  }

  void open(const char* filename)
  {
    close();
    
    if (videoCapture.open(filename)) {
      if (!videoCapture.isOpened()) {
        throw IException("Failed to open a filename=%s", filename);
      }
    }
  }

  void close()
  {
    if (videoCapture.isOpened()) {
      videoCapture.release();
    }
  }

  
  bool read(cv::Mat& frame)
  {
    bool rc = false;
    if (videoCapture.isOpened() ) {
      if (!videoCapture.read(frame)) {
        rc = false;
      } else {
        rc = true;
      }
    }
    return rc;
  }

  cv::VideoCapture& getVideoCapture()
  {
    return videoCapture;
  }
  
  bool getVideoFrameSize(int& w, int& h)
  {
    bool rc = false;
    w = 640;
    h = 480;
    if (videoCapture.isOpened()) {
      w = (int)videoCapture.get(CAP_PROP_FRAME_WIDTH); 
      h = (int)videoCapture.get(CAP_PROP_FRAME_HEIGHT);
      rc = false;
    }
    return rc;
  }
};

}


