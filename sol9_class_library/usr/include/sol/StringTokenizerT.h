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
 *  StringTokenizerT.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol\Analyzer.h>
#include <sol\StringT.h>
#include <sol\StringBufferT.h>

namespace SOL {


template <class T> class StringTokenizerT :public Analyzer {
  const T*  string;
  int    num;
  T   separator[5];

private:
  void defaultSeparator()
  {
    this->num = 0;
    this->separator[num++] = (T)' ';
    this->separator[num++] = (T)'\t';
    this->separator[num++] = (T)',';
  }

public:

  StringTokenizerT()
    :num(0), string(NULL)
  {
    defaultSeparator();
  }


public:
  StringTokenizerT(const T* str)
    :num(0), string(str)
  {
    defaultSeparator();
  }
/*
public:
  StringTokenizer(const String& str) 
    :num(0), string((const TCHAR*)str)
  {
    defaultSeparator();
  }

public:
  StringTokenizer(const StringBuffer& buffer) 
    :num(0), string((const TCHAR*)buffer)
  {
    defaultSeparator();
  }
*/
public:
  bool addSeparator(T s)
  {
    bool rc = false;
    if(num < CountOf(separator)) {
      separator[num++] = s;
      rc = true;
    }
    return rc;
  }

public:
  bool hasMoreToken()
  {
    bool rc = false;
  // 1999.09.23 Added *string != ZERO
    if (string != NULL && *string != (T)0) {
      rc = true;
    }
    return rc;
  }

public:
  void clearSeparator()
  {
    num = 0;
  }

public:
  bool isSeparator(T s)
  {
    bool rc = false;
    for(int i = 0; i< num; i++) {
      if(separator[i] == s) {
        rc = true;
        break;
      }
    }
    return rc;
  }

public:
  const T* getToken(StringT<T>& token)
  {
    if (string != NULL) {
      StringBufferT<T> buffer;
      string = getToken(buffer);
      token = buffer.getBuffer();
    }
    return string;
  }

public:
  const T* getToken(StringBufferT<T>& buffer)
  {
    int quotation = 0;
    const T* p = this->string;
  
    if(p == NULL || *p == (T)0) {
      return NULL;
    }

    while(*p !=(T)0 && isSeparator(*p) == true) {    
      p++;
    }

    while(*p != (T)0) {
      if(*p == (T)'"' && *(p+1) == (T)'"') {
        p += 2;
        break;
      }

      if(*p == (T)'"') {
        p++;  
        quotation++;
      }
    
      if(isSeparator(*p) == true && quotation == 2) {
        break;
      }
    
      if(isSeparator(*p) == true && quotation == 0) {
        break;
      }
      buffer.append(*p++);
    }
    return p;
  }

public:
  const T* getToken(T* token, int size)
  {
    if (this->string != NULL) {
      if (token !=NULL && size>0) {
        this->string = getToken(this->string, token, size);
      }
    }
    return string;
  }

public:
  const T* getToken(const T* p, T* first, int size)
  {
    //2009/10/10
    if (p == NULL || first == NULL || size<1) {
      return NULL;
    }

    if(*p == ZERO) {
      return NULL;
    }

    while(*p !=ZERO && isSeparator(*p) == true) {    
      p++;
    }

    int len = 1;

    int quotation = 0;

    while(*p != (T)ZERO) {
      if(*p == (T)'"' && *(p+1) == (T)'"') {
        p += 2;
        break;
      }
      if(*p == (T)'"') {
        p++;  
        quotation++;
      }
    
      if(isSeparator(*p) == true && quotation == 2) {
        break;
      }
      if(isSeparator(*p) == true && quotation == 0) {
        break;
      }
  
      if(len < size) {
        *first++ = *p++;
        len++;
      }
      else {
        break;
      }
    }
    *first = ZERO;
    return p;
  }
/*
public:
  const T* getInteger(const T* line, int* value)
  {
    T word[10];

    const T* ptr = getToken(line, word, CountOf(word));
    *value = atoi(word);
    return ptr; 
  }

public:
  int hexStringToInt(const TCHAR* str)
  {
      int n =0;

    if(*str++ =='0') {
      if (*str == (TCHAR)'x') {
        _stscanf(++str, _T("%x"), &n);
      }
      else if (*str == (TCHAR)'X') {        
        _stscanf(++str, _T("%X"), &n);
      }
    }
    return n;
  }
*/
};

}



