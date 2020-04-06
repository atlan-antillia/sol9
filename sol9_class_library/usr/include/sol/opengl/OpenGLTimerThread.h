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
 *  DirectX3D11TimerThread.h
 *
 *****************************************************************************/


// 2016/02/22 

#include <sol/Thread.h>
#include <sol/Mutex.h>
#include <sol/CriticalSection.h>
#include <sol/opengl/OpenGLView.h>

namespace SOL {
  
class OpenGLTimerThread : public Thread {
private:
  OpenGLView*       openglView;
  int               renderingInterval;
  bool              looping;
  
public:
  OpenGLTimerThread(__in OpenGLView* view, int interval)
  :openglView(view),
  renderingInterval(interval),
  looping(true)
  {
    if (view == NULL) {
      throw IException("Invalid view parameter.");
    } else {
      openglView = view;
    }
  }
    
public:
  ~OpenGLTimerThread()
  {
    looping = false;
    Sleep(renderingInterval+1);
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
      Sleep(renderingInterval);
      openglView ->postRenderRequest();
     // openglView ->postResizeRequest();
    }
  }
};
  
}
  