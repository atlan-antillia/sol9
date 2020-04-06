/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  CoSmartPtr.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/08/04  

#pragma once

#include <sol\Object.h>

namespace SOL {

/**
 *
 * SmatPtr<char> buff(new char[100]);
 * char* b = (char*)buff;
 * 
 */

template <class T> class CoSmartPtr {

private:
  T ptr;

public:
  /**
   * Constructor
   */
  CoSmartPtr()
  :ptr(NULL)  {  

  }

  /**
   * Constructor
   */
  CoSmartPtr(T t)
  :ptr(t) {

  }

  /**
   * Destructor
   */
  ~CoSmartPtr()  {
    if (ptr) {
      CoTaskMemFree(ptr);
      ptr = NULL;
    }
  }

  operator T() { 
    return ptr;
  }

  
  /*T&  operator*()  { 
    return *ptr;
  }
  */
  /*
  T**  operator&() {
    return &ptr;
  }

  T*  operator->() {
    return ptr;
  }
  */

  T operator=(T t) {
    if (ptr != t) {      
      CoTaskMemFree(ptr);
      ptr = t;
    }
    return ptr;
  }
};


}

