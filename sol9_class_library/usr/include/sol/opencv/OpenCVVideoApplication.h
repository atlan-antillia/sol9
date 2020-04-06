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
 *  OpenCVVideoApplication.h
 *
 *****************************************************************************/

//2017/3/15

#pragma once

#include <sol/Application.h>
#include <sol/View.h>

#include <sol/opencv/OpenCVObject.h>
#include <sol/opencv/OpenCVApplication.h>

namespace SOL {
    
class OpenCVVideoApplication :public OpenCVApplication {
private:
  int  delaymsec;
  static const int DEFAULT_DELAY_MSEC = 30;
public:
  OpenCVVideoApplication(const char* name, int argc, TCHAR** argv, int delay=30)
  :OpenCVApplication(name, argc, argv),
  delaymsec(delay)
  {
    if (delaymsec <5 || delaymsec > 1000) {
      delaymsec = DEFAULT_DELAY_MSEC;
    }
  }
  
  ~OpenCVVideoApplication()
  {
    cvDestroyAllWindows();
  }
  
  WPARAM run()
  {
    return Application::run();
  }
  void run(Window& window)
  {
      // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ) {
      if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )  {
       if(dialogMessage(&msg)) {
         continue;
       }
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      } else {
        //Call a virtual render method of Window.
        window.render();
        Sleep(delaymsec);
      }
    }
  }
  
};

}

