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
 *  SmartPtr.h
 *
 *****************************************************************************/

// 2019/05/05 Updated to use std::unique_ptr

#pragma once

#include <sol\Exception.h>

#include <iostream>
#include <memory>
#include <stdio.h>
#include <memory.h>

namespace SOL {

template <class T> class SmartPtr {

private:
   std::unique_ptr<T> ptr;

public:
  /**
   * Constructor
   */
  SmartPtr()
  :ptr(nullptr)
  { 
  
  }

  /**
   * Constructor
   */
  SmartPtr(T* t)
  :ptr(t) 
  {

  }

  /**
   * Destructor
   */
  ~SmartPtr()  
  {
  }

  operator T*() 
  { 
    return ptr.get();
  }

  
  T&  operator*()  
  { 
    T* p = ptr.get();
    return *p;
  }

  T**  operator&() 
  {
    T* p = ptr.get();
    return &p;
  }

  T*  operator->() 
  {
    T* p = ptr.get();
    if (p != nullptr) {
      return p;
    } else {
      throw IException("Invalid pointer.");
    }
  }

  T* operator=(T* t) 
  {
    T* p = ptr.get();
    if (p != t) {      
      ptr.reset(t);
    }
    p = ptr.get();
    return p;
  }

  bool operator!=(T* t) 
  {
    T* p = ptr.get();
    if (p != t) {      
      return true;
    } else {
      return false;
    }
  }

  bool operator==(T* t) 
  {
    T* p = ptr.get();
    if (p != t) {      
      return false;
    } else {
      return true;
    }
  }

  bool null()
  {
    bool rc = true;
    T* p = ptr.get();
    if (p != nullptr) {
      rc = false;
    }
    return rc;
  }

  bool isNull()
  {
  	return null();
  }

  bool notNull()
  {
    bool rc = false;
    T* p = ptr.get();
    if (p) {
      rc = true;
    }
    return rc;
  }

  bool isNotNull()
  {
  	return notNull();
  }
	
/*  void nullify() 
  {
    if (ptr) {      
      delete ptr;
      ptr = NULL;
    }
  }
 */
};
}

