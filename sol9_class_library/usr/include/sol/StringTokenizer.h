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
 *  StringTokenizer.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Analyzer.h>
#include <sol\String.h>
#include <sol\StringBuffer.h>

namespace SOL {

class StringTokenizer :public Analyzer {
  const TCHAR*  string;
  int    num;
  TCHAR   separator[5];

private:
  void defaultSeparator()
  {
    this->num = 0;
    this->separator[num++] = (TCHAR)' ';
    this->separator[num++] = (TCHAR)'\t';
    this->separator[num++] = (TCHAR)',';
  }

public:

  StringTokenizer()
    :num(0), string(NULL)
  {
    defaultSeparator();
  }


public:
  StringTokenizer(const TCHAR* str)
    :num(0), string(str)
  {
    defaultSeparator();
  }

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

public:
  bool addSeparator(TCHAR s)
  {
    bool rc = false;
    if(num < CountOf(separator)) { //2012/06/25
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
    if (string != NULL && *string != (TCHAR)0) {
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
  bool isSeparator(TCHAR s)
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
  const TCHAR* getToken(__out String& token)
  {
    if (string != NULL) {
      StringBuffer buffer;
      string = getToken(buffer);
      token = buffer.getBuffer();
    }
    return string;
  }

public:
  const TCHAR* getToken(StringBuffer& buffer)
  {
    int quotation = 0;
    const TCHAR* p = this->string;
  
    if(p == NULL || *p == (TCHAR)ZERO) {
      return NULL;
    }

    while(*p !=ZERO && isSeparator(*p) == true) {    
      p++;
    }

    while(*p != ZERO) {
      if(*p == (TCHAR)'"' && *(p+1) == (TCHAR)'"') {
        p += 2;
        break;
      }

      if(*p == (TCHAR)'"') {
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
  const TCHAR* getToken(TCHAR* token, int size)
  {
    if (this->string != NULL) {
      this->string = getToken(this->string, token, size);
    }
    return string;
  }

public:
  const TCHAR* getToken(const TCHAR* p, TCHAR* first, int size)
  {

    if(*p == ZERO) {
      return NULL;
    }

    while(*p !=ZERO && isSeparator(*p) == true) {    
      p++;
    }

    int len = 1;

    int quotation = 0;

    while(*p != (TCHAR)ZERO) {
      if(*p == '"' && *(p+1) == '"') {
        p += 2;
        break;
      }
      if(*p == (TCHAR)'"') {
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

public:
  const TCHAR* getInteger(const TCHAR* line, int* value)
  {
    TCHAR word[10];

    const TCHAR* ptr = getToken(line, word, CountOf(word)); //2012/06/21
    *value = atoi(word);
    return ptr; 
  }

public:
  int hexStringToInt(const TCHAR* str)
  {
      int n =0;

    if(*str++ =='0') {
      if (*str == (TCHAR)'x') {
        _stscanf_s(++str, _T("%x"), &n);
      }
      else if (*str == (TCHAR)'X') {        
        _stscanf_s(++str, _T("%X"), &n);
      }
    }
    return n;
  }

};

}



