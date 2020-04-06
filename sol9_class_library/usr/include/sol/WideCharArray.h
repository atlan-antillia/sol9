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
 *  WideCharArray.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Array.h>
#include <sol\InvalidArgumentException.h>
#include <sol\OutOfMemoryException.h>

#include <sol\OutOfRangeException.h>

namespace SOL {

class WideCharArray :public Array {
private:
  wchar_t*   warray;
  
public:
  WideCharArray(UINT size=0)
    :Array(size), warray(NULL) 
  {
    if (size >0) {
      warray = new wchar_t[size];
      if(warray == NULL) {
        throw OutOfMemoryException("Failed to create a wideCharArray");
      }
    }
    /*else {
      throw InvalidArgumentException("WideCharArray::WideCharArray,1,InvalidArgument");
    }*/
  }

public:
  ~WideCharArray() 
  {
    clear();
  }

public:
  void clear() 
  {
    if(warray) {
      delete [] warray;
    }
    setSize(0);
    warray = NULL;
  }

public:
  // Simply set a Null pointer to the warray member not to delete the warray memory area. 
  void nullify()
  {
    warray = NULL;
    setSize(0);
  }

public:
  void copy(UINT pos, const wchar_t* string, UINT len) 
  {
    if ((pos + len) <= getSize()) {
      wchar_t* ptr = (warray + pos);
      for(UINT i = 0; i<len; i++) {
        *ptr++ = *string++;
      }
    }
  }


public:
  void shallowCopy(wchar_t* data, uint len) 
  {
    if (data && len>0) {
      if (data != warray) {
        clear();
      }
      warray = data;
      setSize(len);
    }
  }

public:
  BOOL expand(UINT len) 
  {
    UINT size = getSize();
    BOOL rc  = FALSE;
    wchar_t* temp = new wchar_t[size+len];
    if(temp) {
      for(UINT i = 0; i<size; i++) {
        *(temp + i) = *(warray + i);
      }
      size += len;
      setSize(size);
      delete [] warray;
      warray = temp;
      rc = TRUE;
    }
    return rc;
  }

public:
  wchar_t  getNth(UINT pos)
  {
    wchar_t wc = NULL;
    if(pos>=0 && pos < getSize()) {
      wc = warray[pos];
    }
    else {
      throw OutOfRangeException("WideCharArray::getNth,Index is out of range");
    }
    return wc;
  }

public:
  const wchar_t* getContents() { 
    return warray;
  }

public:
  void  setNth(UINT pos, wchar_t wc) {
    if(pos>=0 && pos < getSize()) {
      warray[pos] = wc;
    } else {
      throw OutOfRangeException("WideCharArray::setNth,Index is out of range");

    }
  }

public:
  bool isString()
  {
    bool rc = false;

    UINT size = getSize();
    if (size>0 && warray[size-1] == '\0') {
      rc = true;
      for(UINT i = 0; i<size-1; i++) {
        if (warray[i] == '\0') {
          rc = false;
          break;
        }
      }
    }
    return rc;
  }

};

}
