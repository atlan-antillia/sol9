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
 *  Mutex.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>
#include <sol\InvalidHandleException.h>
#include <sol\String.h>


namespace SOL {

class Mutex :public Object {
private:
  HANDLE hMutex;
  String name;

public:
  /**
   */
  Mutex(const TCHAR* id=_T("SolMutex"))
    :hMutex(NULL),
    name(_T(""))
  {
    if (id) {
      this->name = id;
      this->name.replace('\\', '/');
    }
  }


public:
  /**
   */
  Mutex(LPSECURITY_ATTRIBUTES security, BOOL owner, const TCHAR* id)
    :hMutex(NULL),name(_T(""))
  {
    if (id) {
      this->name = id;
      this->name.replace('\\', '/');
    }
    
    this->hMutex = ::CreateMutex(security, owner, (const TCHAR*)this->name);
    if(hMutex == NULL) {
      throw InvalidHandleException("Failed to create a mutex",
        ::GetLastError());
    }
  }
  

public:
  /**
   */
  ~Mutex() {
    close();
  }

public:
  /**
   */
  //Apply for mutex created Mutex(id)
  DWORD  lock() {
    DWORD rc = 0;
    if (this->hMutex) {
      close();
    }

    this->hMutex = CreateMutex(NULL, FALSE, (const TCHAR*)name);
    
    if (this->hMutex) {
      // Enter an infinite loop, should be modified to handle 
      //Windows message;
      rc = WaitForSingleObject(this->hMutex, INFINITE);
    }
    
    return rc;  
  }

public:
  /**
   */
  void  unlock() {
    close();
  }



public:
  void close() {
    if(this->hMutex) {
      ::ReleaseMutex(this->hMutex);
      ::CloseHandle(this->hMutex);
      this->hMutex = NULL;
    }
  }

  DWORD  wait(DWORD millisec = INFINITE) {
      return ::WaitForSingleObject(hMutex, millisec);
  }

  BOOL  release() {
      return ::ReleaseMutex(hMutex);
  }
};

}

