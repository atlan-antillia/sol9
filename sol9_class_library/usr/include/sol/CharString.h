/******************************************************************************
 *
 * Copyright (c) 2014 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  CharString.h
 *
 *****************************************************************************/

#pragma once
#include <sol/Object.h>

#include <sol/Exception.h>
#include <string.h>
#include <sol/StringT.h>

namespace SOL {

class CharString :public StringT<char> {

public:
  /**
   */
  CharString()
  :StringT<char>()
  {
  }

public:
  CharString(const char* string, bool deepCopy=true)
  :StringT<char>(string, deepCopy)
  {   
  }

public:
  CharString(char* array, int len)
  :StringT<char>(array, len)
  {
  }

public:
  CharString(const CharString* string)
  :StringT<char>(string)
  {   
  }


public:
  CharString(const CharString& string)
  :StringT<char>(string)
  {
  }

 
  virtual const char* toString()
  {
    return (const char*)(*this);	
  }
public:
  int compare(Object* object)
  {
    int rc = 0;
    if (object==NULL) {
      return rc;
    }

    CharString* string = (CharString*)object;
    const char* p1 = toString();

    const char* p2 = string->toString();
    if (p1 == NULL && p2 == NULL) {
      rc = 0;
    }
    if (p1 == NULL && p2 != NULL) {
      rc = 0;
    }
    if (p1 != NULL && p2 == NULL) {
      rc = 1;
    }
    if (p1 != NULL && p2 != NULL) {
      //rc = __strcmp(p1, p2);
      rc = strcmp(p1, p2);
    }
    return rc;
  }
	
};


inline int __strlen(CharString* string)
{
  assert(string);
  return string->getLength();
}

}

