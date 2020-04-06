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
 *  WideCharString.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\WideCharArray.h>

namespace SOL {

class WideCharString :public WideCharArray {

private:
  UINT getLength(const wchar_t* string) {
    UINT len = 0;
    if(string) {
      len = wcslen(string);
    } 
    return len;
  }

public:
  WideCharString(const wchar_t* string) 
    :WideCharArray(getLength(string)) 
  {
    copy(0, string, getSize());
  }


public:
  WideCharString(const char* mbstring) 
    :WideCharArray(0) 
  {
    const wchar_t* wcstring = toWideChar(mbstring);
    if (wcstring) {
      //NULL terminate string.
      shallowCopy(wcstring, wcslen(wcstring));
    }
    //copy(0, string, getSize());
  }


public:
  void append(const wchar_t* string) 
  {
    if (string) {
      int size = getSize();
      int len  = getLength(string);
      expand(len);
      copy(size, string, len);
    }
  }

public:
  operator wchar_t*()
  {
    return  WideCharArray::getContents();  
  }

public:
  operator const wchar_t*()
  {
    return  WideCharArray::getContents();  
  }


public:
  /**
   * Return a new wchar_t's copy string. Need to delete [] it after use.
   */
  wchar_t*  getString() 
  {
    UINT size = getSize();
    wchar_t* temp = new wchar_t[size+1];
    if(temp) {
      const wchar_t* ptr = getContents();
      for(UINT i = 0; i<size; i++) {
             *(temp+i) = *(ptr+i);
      }
      *(temp+size) = NULL;
    }
    return temp;
  }

private:
  wchar_t* toWideChar(const char* mbstring) {
    wchar_t* wcstring = NULL;

    if (mbstring == NULL) {
      return wcstring;
    }
    
    int cb = MultiByteToWideChar(CP_ACP, 0, mbstring, -1, NULL, 0); 
    if (cb >0) {
      wcstring = new wchar_t[cb];
      wcstring[0] = ZERO;
      MultiByteToWideChar(CP_ACP, 0, mbstring, -1, wcstring, cb); 
    }
    return wcstring;
  }

};

}


