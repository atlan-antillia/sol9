/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  XMLObject.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/23 Base class for XMLSomthing classes

#pragma once
#include <sol/com/ComObject.h>
#include <sol/com/ComError.h>
#include <sol/Exception.h>

//2015/07/15
//#import <msxml3.dll> 
#ifdef XML4
#import <msxml4.dll> 
#endif
//2015/12/19
#ifdef XML6
#import <msxml6.dll> 
#endif

using namespace MSXML2;

namespace SOL {

class XMLObject :public Object {

public:
  /**
   * Constructor
   */
  XMLObject()
  {
  }

public:
  /**
   * Destructor
   */
  ~XMLObject()
  {
  }

public:
  virtual void dump()
  {
  }

public:
  unsigned short* toShort(const _bstr_t string)
  {
    return (unsigned short*)(void*)((const wchar_t*)string);
  }

public:
  unsigned short* toShort(const wchar_t* pwchName)
  {
    return (unsigned short*)(void*)pwchName;
  }

public:
  wchar_t* toWchar(const unsigned short* pwchName)
  {
    return (wchar_t*)(void*)pwchName;
  }
};

}
