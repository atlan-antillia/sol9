/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  HTMLDecoder.h
 *
 *****************************************************************************/

// SOL9
// 2012/03/10 Updated.

#pragma once


#include <sol\Object.h>
#include <sol\String.h>
#include <sol\WString.h>

#include <sol\StringT.h>

namespace SOL {

/**
 *
 */
class HTMLDecoder :public Object {

public:
  /**
   */
  HTMLDecoder() {

  }

public:
  /**
   *
   */
  bool decode(const char* string, __out String& decoded) {
    bool rc = false;
    if (string) {
      char* dec = decode(string);
      decoded = dec;
      delete [] dec;
      rc = true;
    }
    return rc;
  }

public:
  /**
   *
   */
  bool decode(const char* string, __out StringT<char>& decoded) {
    bool rc = false;
    if (string) {
      char* dec = decode(string);
      decoded.shallowCopy(dec);
      rc = true;
    }
    return rc;
  }

public:
  //2012/03/10
  bool decode(const wchar_t* string, StringT<wchar_t>& decoded) {
    bool rc = false;
    if (string) {
      wchar_t* enc = decode(string);
      decoded.shallowCopy(enc);
      rc = true;
    }
    return rc;
  }

public:
  // 2012/03/10
  String decode(const String bstring) {
    const TCHAR* dec = NULL;
    const TCHAR* string = (const TCHAR*)bstring;
    if (string) {
      dec = decode(string);
    }
    return String(dec, false);
  }

public:
  // 2012/03/10
  WString decode(const WString bstring) {
    const wchar_t* dec = NULL;
    const wchar_t* string = (const wchar_t*)bstring;
    if (string) {
      dec = decode(string);
    }
    return WString(dec, false);
  }

public:
  /**
   *
   */
  char* decode(const char* string) {

    static char*  entities[] = {"&amp;", "&lt;", "&gt;", "&#039;", "&quot;",};// "&nbsp;"};
    static char   specials[] = {'&',     '<',    '>',    '\'',     '"',     };//' '};

    if (string == NULL) {
      return NULL;
    }

    char* decoded = new char[strlen(string)+1];
    const char* src = string;

    char* dst = decoded;
    int entlen = sizeof(entities)/sizeof(entities[0]);
    
    while (*src) {
      if (*src == '&') {
        for (int i= 0; i<entlen; i++) {
          char* entity = entities[i];
          if (memcmp(src, entity, strlen(entity)) ==0) {
            char s = specials[i];
            *dst++ = s;
            src = src + strlen(entity);
            break;                
          }
        }
      } else {
        *dst++ = *src++;
      }
    }  
    *dst = '\0';
    
    return decoded;
  }

public:
  //2012/03/10 See sol/include/Wchardef.h
  wchar_t* decode(const wchar_t* string) {

    static wchar_t*  entities[] = {L"&amp;", L"&lt;", L"&gt;", L"&#039;", L"&quot;",};// "&nbsp;"};
    static wchar_t   specials[] = {'&',     '<',    '>',    '\'',     '"',     };//' '};

    if (string == NULL) {
      return NULL;
    }

    wchar_t* decoded = new wchar_t[strlen(string)+1];
    const wchar_t* src = string;

    wchar_t* dst = decoded;
    int entlen = sizeof(entities)/sizeof(entities[0]);
    
    while (*src) {
      if (*src == '&') {
        for (int i= 0; i<entlen; i++) {
          wchar_t* entity = entities[i];
          if (memcmp(src, entity, strlen(entity)) ==0) {
            wchar_t s = specials[i];
            *dst++ = s;
            src = src + strlen(entity);
            break;                
          }
        }
      } else {
        *dst++ = *src++;
      }
    }  
    *dst = '\0';
    
    return decoded;
  }

};


}
