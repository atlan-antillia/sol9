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
 *  StringBuffer.h
 *
 *****************************************************************************/

// SOL++2000
// 2000/11/11
#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol\InvalidArgumentException.h>

namespace SOL {

class StringBuffer :public Object{
private:
  TCHAR*  buffer;
  int    size;
  int    increment;
  int    position;

  //2008/07/06
public:

  StringBuffer(int s =SIZE_1KB, int inc = SIZE_128B)
    :size(s), increment(inc), buffer(NULL),
    position(0)
  { 
    if (size<=0 || increment<=0) {
      throw InvalidArgumentException("StringBuffer::StringBuffer,1,InvalidArgument");  
    }

    this->buffer = new TCHAR[size+1];
    memset(this->buffer, (TCHAR)0, size+1);
  }

public:
  ~StringBuffer()
  {
    if (this->buffer) {
      delete [] this->buffer;
      this->buffer = NULL;
    }
  }

public:
  void clear()
  {
    this->position = 0;
    if (this->buffer) {
      //delete [] this->buffer;
    
      //this->size = SIZE_1KB; // 2008/07/05
      //this->buffer = new TCHAR[size+1];
      memset(this->buffer, (TCHAR)0, size+1);
    }
  }

public:
  bool append(TCHAR ch)
  {  
    if (position >=size) {
      size += increment;
      TCHAR* temp = new TCHAR[size+1];
      if (temp == NULL) {
        return false;
      }
      memset(temp, (TCHAR)0, size+1);
      memcpy(temp, buffer, position);
      delete [] buffer;
      buffer = temp;
    }

    *(buffer+position) = ch;
    position++;
    *(buffer+position) = ZERO;

    return true;
  }

public:
  bool append(const TCHAR* string)
  {
    bool rc = true;
    if (string) {
      size_t len = strlen(string);
      for (size_t i = 0; i<len; i++) {
        rc = append(*string++);
      }
    }
    return rc;
  }


//<added date="2000/11/10">
public:
  bool append(int num)
  {
    TCHAR integer[80];
    _stprintf_s(integer, CountOf(integer), _T("%d"), num);
    return append(integer);
  }

public:
  bool append(float num)
  {
    TCHAR integer[80];
    _stprintf_s(integer, CountOf(integer), _T("%f"), num);
    return append(integer);
  }

public:
  bool append(String& string)
  {
    return append((const TCHAR*)string);
  }

public:
  String* newString() 
  {
    //buffer is NULL terminated
    return new String(this->buffer);  
  }
//<added>

public:
  const TCHAR* find(const TCHAR* string)
  {
    const TCHAR* ptr = NULL;
    if (buffer && string) {
      ptr = strstr(buffer, string);
    }
    return string;
  }

public:
  const TCHAR* getBuffer() const { 
    return this->buffer; 
  }

public:
  operator const TCHAR*() const{
    return this->buffer;
  }

public:
  String*    getString() const { 
    return new String(this->buffer); 
  }

public:
  int      getSize() const  { 
    return this->size; 
  }

public:
  int      getContentSize() const { 
    return this->position; 
  }

};

}


