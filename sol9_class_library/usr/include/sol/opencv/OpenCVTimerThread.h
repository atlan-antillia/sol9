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
 *  OpenCVTimerThread.h
 *
 *****************************************************************************/


// 2016/02/22 

#include <sol/Thread.h>
#include <sol/Mutex.h>
#include <sol/CriticalSection.h>

#include <sol/opencv/OpenCVVideoCaptureView.h>

namespace SOL {
  
class OpenCVTimerThread : public Thread {
private:
  OpenCVVideoCaptureView*  videoCaptureView;
  int                captureInterval;   //milliseconds
  bool               looping;
  
public:
  OpenCVTimerThread(__in OpenCVVideoCaptureView* view, int interval)
  :videoCaptureView(view),
  captureInterval(interval),
  looping(true)
  {
    if (captureInterval < 10 || captureInterval >500) {
      captureInterval = 30;
    }
    if (view == NULL) {
      throw IException("Invalid view parameter.");
    } else {
      videoCaptureView = view;
    }
  }
    
public:
  ~OpenCVTimerThread()
  {
    looping = false;
    Sleep(captureInterval+1);
  }

public:
  void terminate()
  {
    looping = false;
  }
  
public:
  //Thread main procedure which will be started  by Thread::start() method.
  virtual void run()
  {
    looping = true;
    while (looping) {
      Sleep(captureInterval);
      //Post a capture Windows message to a queue.
      //videoCaptureView->postCaptureRequest();
      //You may call a capture method of
      if (videoCaptureView) {
        videoCaptureView->capture();
      }
    }
  }
};
  
}
  