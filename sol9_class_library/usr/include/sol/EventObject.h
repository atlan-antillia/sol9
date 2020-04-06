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
 *  EventObject.h
 *
 *****************************************************************************/

// SOL++2000
//2009/11/17 Modified

#pragma once

#include <sol\Object.h>    //2009/11/17


namespace SOL {

class EventObject :public Object {
private:
  HANDLE handle;

public:
  EventObject()
    :handle(NULL)
  {
  }

public:
  EventObject(LPSECURITY_ATTRIBUTES lpsa, BOOL manualReset, 
        BOOL initialState, LPCTSTR eventName)
    :handle(NULL)
  {
    handle = ::CreateEvent(lpsa, manualReset, initialState, eventName);
  }


public:
  HANDLE create(LPSECURITY_ATTRIBUTES lpsa, BOOL manualReset, 
        BOOL initialState, LPCTSTR eventName) 
  {
    close();
    handle = ::CreateEvent(lpsa, manualReset, initialState, eventName);
    return handle;
  }

public:
  ~EventObject() {
    close();
  }


  BOOL   set() {
      return ::SetEvent(handle);
  }

  BOOL   reset() {
      return ::ResetEvent(handle);
  }
  BOOL   pulse() {
      return ::PulseEvent(handle);
  }

  BOOL   close() {
    BOOL rc = FALSE;
    if (handle) {
      rc = ::CloseHandle(handle);
      handle = NULL;
    }
    return rc;
  }

  HANDLE  getHandle() {
      return handle;
  }
};

}


