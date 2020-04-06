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
 *  StringBufferT.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/11

#pragma once

#include <sol\Object.h>
#include <sol\StringT.h>
#include <sol\InvalidArgumentException.h>

namespace SOL {

template <class T> class StringBufferT :public Object{

private:
  T*  buffer;
  int    size;
  int    increment;
  int    position;

  //2008/07/06
public:

  StringBufferT(int s =SIZE_1KB, int inc = SIZE_128B)
    :size(s), increment(inc), buffer(NULL),
    position(0)
  { 
    if (size<=0 || increment<=0) {
      throw InvalidArgumentException("StringBuffer::StringBuffer,1,InvalidArgument");  
    }

    this->buffer = new T[size+1];
    memset(this->buffer, (T)0, size+1);
  }

public:
  ~StringBufferT()
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
      memset(this->buffer, (T)0, size+1);
    }
  }

public:
  bool append(T ch)
  {  
    if (position >=size) {
      size += increment;
      T* temp = new T[size+1];
      if (temp == NULL) {
        return false;
      }
      memset(temp, (T)0, size+1);
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
  bool append(const T* string)
  {
    bool rc = true;
    if (string) {
      size_t len = strlen(string);
     
      for (size_t i = 0; i<len; i++) {
        T c = (T)*string;
        string++;
        rc = append(c);
      }
    }
    return rc;
  }

private:

  bool appendFormat(T* format,...)
  {
    static const int BSIZE = 128;
    T buffer[BSIZE];
    memset(buffer, (T)0, BSIZE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(buffer, BSIZE, _TRUNCATE, format, pos);
    va_end(pos);
    return append(buffer);
  }

public:
  bool append(int num)
  {
    T format[8] ={(T)'%',(T)'d', (T)0};  
    return appendFormat(format, num);
  }


public:
  bool append(float num)
  {
    T format[8] ={(T)'%',(T)'f', (T)0};  
    return appendFormat(format, num);

  }

public:
  bool append(double num)
  {
    T format[8] ={(T)'%',(T)'f', (T)0};  
    return appendFormat(format, num);
  }


public:
  bool append(StringT<T>& string)
  {
    return append((const T*)string);
  }

public:
  StringT<T>* newString() 
  {
    //buffer should be NULL terminated
    return new StringT<T>(this->buffer);  
  }

public:
  bool getString(__out StringT<T>& string)
  {
    T empty[1] = {(T)0};
    string = empty;

    bool rc = false;
    if (buffer) {
      string = this->buffer;
      rc = true;
    }
    return rc;
  }

public:
  const T* find(const T* string)
  {
    const T* ptr = NULL;
    if (buffer && string) {
      ptr = strstr(buffer, string);
    }
    return ptr;//string;
  }

public:
  const T* getBuffer() const { 
    return this->buffer; 
  }

public:
  operator const T*() const{
    return this->buffer;
  }
/*
public:
  String*    getString() const { 
    return new String(this->buffer); 
  }
*/
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


