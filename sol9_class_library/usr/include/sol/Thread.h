/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Thread.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.24 Modified to use _beginthreadex and _endthreadex insteade
// of CreateThread and ExitThread.
// SOL9 
// 2008/09/05

#pragma once

#include <sol\Object.h>
#include <process.h>
#include <sol\stdio.h>
#include <sol\InvalidHandleException.h>

namespace SOL {

typedef unsigned (__stdcall *LPTHREAD_PROC)(void*);

class Thread :public Object {
public:
  static const UINT WM_SOL_THREAD_CANCEL = (WM_USER+2009);


private:

  void*  param;
  DWORD  threadId;
  HANDLE  handle;
  //2017/09/10 Updated argument to take void* instead of DWORD.
  static  DWORD WINAPI procedure(void* ptr) 

  {
    Thread* thread = (Thread*)ptr;
    if(thread) {
      // SOL++2000
      thread -> run();
    }
    return True;
  }

protected:
  void setHandle(HANDLE handle1) 
  {
    handle = handle1;
  }
  
  void setThreadId(int tid) 
  {
    threadId = tid;
  }

public:

  Thread(DWORD stack = 0, void* param = NULL)
  {
    this -> param = param;
    // Create a suspended thread.
    DWORD flags = CREATE_SUSPENDED;

    handle = (HANDLE)_beginthreadex((void*)NULL, (unsigned)stack, 
        (LPTHREAD_PROC)Thread::procedure,
        (void*)this, flags, (unsigned*)&threadId);
    if(handle == NULL || handle == INVALID_HANDLE_VALUE) {
      handle = NULL;
      throw InvalidHandleException("Failed to create a thread",
        GetLastError());
    }
  }

  ~Thread() 
  {
    kill();
  }
  
  void*  getParam() 
  {
    return param;
  }
  
  DWORD  getThreadId() 
  {
    return threadId;
  }

  HANDLE  getHandle() {
    return handle;
  }

  void  exit(DWORD exitCode) 
  {
    //::ExitThread(exitCode);
    _endthreadex(exitCode);
  }

  // Thread main loop.
  // Please define your own run method in the subclass derived from this class.
  virtual void run() 
  {
    // Do something
  }

  // SOL++ 3.0
  virtual DWORD start() 
  {
    return resume();
  }
  
  void  sleep(DWORD time) 
  {
    ::Sleep(time);
  }

  DWORD  resume() 
  {
    return ::ResumeThread(handle);
  }

  void  setPriority(int priority) 
  {
    ::SetThreadPriority(handle, priority);
  }

  DWORD  suspend() 
  {
    //Please be carefull to use this method,
    //because this may cause a something deadlock. 
    return ::SuspendThread(handle);
  }

  BOOL  close() 
  {
    if(handle) {
      HANDLE h = handle;
      handle = NULL;
      return ::CloseHandle(h);
    }
    return FALSE;
  }
  
  BOOL  post(UINT message, WPARAM wParam, LPARAM lParam) 
  {
    if(handle) {
      return ::PostThreadMessage(threadId, message, wParam, lParam);
    }
    else {
      return FALSE;
    }
  }

  BOOL   getExitCode(DWORD* id) 
  {
    return ::GetExitCodeThread(handle, id);
  }

   void    kill() 
  {
    if(handle) {
      close();
      DWORD id;
      while(getExitCode(&id)) {
        if(id == STILL_ACTIVE) {
          dispatchMessage();
          continue;
        }
        else {
          break;
        }
      }
    }
    handle = NULL;
   }

  BOOL  terminate(int exitCode) 
  {
    BOOL rc = FALSE;
    if (handle) {
      rc = TerminateThread(handle, exitCode);
    }
    return rc;
  }

  int  wait(int interval=INFINITE) 
  {
    int rc = 0;
    if (handle) {
      rc = ::WaitForSingleObject(handle, interval);
    }
    return rc;
  }

public:
  //2009/11/16
  void  msgWait()
  {
    bool loop = true;
    while (loop)   
      if (MsgWaitForMultipleObjects(1, &handle, FALSE,   
        INFINITE, QS_ALLINPUT|QS_ALLEVENTS) == WAIT_OBJECT_0+1 ) {
      dispatchMessage(); 
    }else {
      break;   
    }
  }


//2009/11/16
private:
  void dispatchMessage()
  {
    MSG msg;    
    while(PeekMessage (&msg,NULL,0,0,PM_REMOVE)) {
      SleepEx(10, TRUE);

      if (msg.message == WM_SOL_THREAD_CANCEL) {
        terminate(0);
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

public:
  virtual void stop() 
  {
    post(WM_SOL_THREAD_CANCEL, 0, 0);
  }

public:
  UINT getCancelMessage() 
  {
    return WM_SOL_THREAD_CANCEL;
  }
};

}


