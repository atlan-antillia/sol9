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
 *  ComPtr.h
 *
 *****************************************************************************/

// 2016/11/15  

#pragma once

#include <sol\Object.h>
#include <sol/Exception.h>

namespace SOL {


template <class T> class ComPtr {

private:
  T* ptr;

public:
  /**
   * Constructor
   */
  ComPtr()
  :ptr(NULL)  {  

  }

  /**
   * Constructor
   */
  ComPtr(T* t)
  :ptr(t) {

  }

  /**
   * Destructor
   */
  ~ComPtr()  {
    if (ptr) {
      ptr -> Release();
      ptr = NULL;
    }
  }
  
  operator T*() { 
    return ptr;
  }

  void addRef()
  {
    if (ptr) {
      ptr -> AddRef();
    }
  }
  
  void release()
  {
    if (ptr) {
      ptr -> Release();
    }
  }

  
  T&  operator*()  { 
    return *ptr;
  }

  T**  operator&() {
    return &ptr;
  }

  T*  operator->() {
    return ptr;
  }

  T* operator=(T* t) {
    if (ptr != t) {      
      delete ptr;
      ptr = t;
    }
    return ptr;
  }
};
}

