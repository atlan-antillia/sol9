/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  StringStreamT.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Analyzer.h>
#include <sol\StringT.h>
#include <sol\StringBufferT.h>

namespace SOL {

template<class T> StringStreamT :public Object {

private:
  int  length;
  StringT<T>*   string;
  
  StrngT<T>*    newLine;
    
private:
  void defaultSeparator()
  {
    this->num = 0;
    this->separator[num++] = (TCHAR)' ';
    this->separator[num++] = (TCHAR)'\t';
    this->separator[num++] = (TCHAR)',';
  }

public:

  StringStreamT(const StringT<T>* text, const T* nl)
  :length(0),
  string(NULL),
  newLine(NULL)
  {
    if (string && nl) {
      string = new StringT<T>(text);
      newLine = new StringT<T>(nl);
    } else {
      throw IException("Invalid argument");
    }
  }


public:
  ~StringStreamT()
  {
    delete text;
    delete newLine;
  }


public:
  bool hasMoreLine()
  {
    bool rc = false;
  // 1999.09.23 Added *string != ZERO
    if (string != NULL && *string != (T)0) {
      rc = true;
    }
    return rc;
  }


public:
  const T* getLine(__out StringT<T>& line)
  {
    if (string != NULL) {
      StringBufferT<T> buffer;
      string = getLine(buffer);
      line = buffer.getBuffer();
    }
    return string;
  }

public:
  const T* getLine(StringBufferT<T>& buffer)
  {
    int quotation = 0;
    const T* p = this->string;
  
    if(p == NULL || *p == (T)ZERO) {
      return NULL;
    }
    T* nl = strstr(p, newLine);
    while( (p != nl) || *p != NULL) {
        buffer.append(*p++);
    }
    buffer.append((T)ZERO);
    return p;
  }


};

}



