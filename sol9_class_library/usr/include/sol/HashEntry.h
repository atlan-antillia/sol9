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
 *  HashEntry.h
 *
 *****************************************************************************/

// 2012/04/22 Updated.
// 2015/12/02 Updated.

#pragma once

#include <sol\Entry.h>


namespace SOL {

class HashEntry  :public Entry {
private:
  Key         intKey; //2017/03/15 Key is LONG_PTR
  char*       charKey;
  wchar_t*    wcharKey;
  HashEntry*  next;

public:
  HashEntry(Key key, Object* object)
    :Entry(object, NULL),
    intKey (key),
    charKey(NULL),
    wcharKey(NULL),
    next   (NULL)
  {
  }

public:
  HashEntry(const char* key, Object* object)
    :Entry(object, NULL),
    intKey(0),
    charKey(NULL),
    wcharKey(NULL),
    next(NULL)
  {
    const char* text = key;
    if(text == NULL) {
      text = "";
    }
    size_t slen = strlen(text) + 1;
    charKey = new char[slen];
    strcpy_s(charKey, slen, text);
  }

public:
  HashEntry(const wchar_t* key, Object* object)
    :Entry(object, NULL),
    intKey(0),
    charKey(NULL),
    wcharKey(NULL),
    next(NULL)
  {
    const wchar_t* text = key;
    if(text == NULL) {
      text = L"";
    }
    size_t slen = wcslen(text) + 1;
    wcharKey = new wchar_t[slen];
    wcscpy_s(wcharKey, slen, text);
  }

public:
  ~HashEntry()
  {
    if(charKey) { 
      delete [] charKey;
      delete [] wcharKey;
    }
  }

  void  add(HashEntry* entry) { 
    next = entry; 
  }

  const char*  getCharKey(){ 
    return (const char*)charKey; 
  }

  const wchar_t*  getWcharKey(){ 
    return (const wchar_t*)wcharKey; 
  }

  const Key getIntKey() { 
    return intKey;  
  }

  HashEntry* getNext()  { 
    return next;    
  }
};

}


