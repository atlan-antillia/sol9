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
 *  DirectX3D12TimerThread.h
 *
 *****************************************************************************/

// 2016/02/22 
// 2016/11/12 Replaced a rendering target view from class DirectX3D12View from class View.
// 2016/12/04 Updated to use messageQueuing member variable.
 
#include <sol/Thread.h>
#include <sol/Mutex.h>
#include <sol/CriticalSection.h>
#include <sol/View.h>
#include <sol/direct3d12/DirectX3D12View.h>

namespace SOL {
  
class DirectX3D12TimerThread : public Thread {
private:
  View*             view;   //2016/11/12 Modifed 
  int               renderingInterval;
  bool              looping;
  bool              messageQueuing;
  
public:
  DirectX3D12TimerThread(__in View* target, int interval, bool queuing=true)
  :view(target),
  renderingInterval(interval),
  looping(true),
  messageQueuing(queuing)
  {
    if (interval <10) { //10ms
      throw IException("Rendering Interval is too small. Interva(%d).", interval);
    }
    if (view == NULL) {
      throw IException("Invalid view parameter.");
    } else {
      view = target;
    }
  }
    
public:
  ~DirectX3D12TimerThread()
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
      //2016/12/04
      if (messageQueuing) {
        view ->postRenderRequest();
      } else {
        //Direct display method call
        view -> display();
      }
      //2016/11/10 direct3d12View ->postResizeRequest();
    }
  }
};
  
}
  