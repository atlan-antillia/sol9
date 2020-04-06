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
 *  Semaphore.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>

#include <sol\InvalidHandleException.h>

namespace SOL {

class Semaphore :public Object {
private:
  HANDLE handle;

public:

  Semaphore(LPSECURITY_ATTRIBUTES sa, long initialCount, 
    long maxCount, const TCHAR* name)
    :handle(NULL)
  {
    handle = ::CreateSemaphore(sa, initialCount, maxCount, name);
    if(handle == NULL) {
      throw InvalidHandleException("Failed to create a semaphore",
      GetLastError());
    }
  }

public:
  ~Semaphore() 
  {
    close();
  }

public:
  BOOL close() 
  {
    BOOL rc = FALSE;
    if(handle) {
      rc = ::CloseHandle(handle);
    }
    handle = NULL;
    return rc;
  }

public:
  BOOL release(long releaseCount, long* prevCount) 
  {
    BOOL rc = FALSE;
    if(handle) {
      rc = ::ReleaseSemaphore(handle, releaseCount, prevCount);
    }
    return rc;
  }

public:
  DWORD wait(DWORD milliSecond) 
  {
    DWORD rc = 0;
    if (handle) {
      rc = ::WaitForSingleObject(handle, milliSecond);
    }
    return rc;
  }

};

}
