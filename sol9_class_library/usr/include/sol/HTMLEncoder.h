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
 *  HTMLEncoder.h
 *
 *****************************************************************************/

// SOL9
// 2012/03/10 Updated.

#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol\WString.h>

#include <sol/StringT.h>
#include <sol/StringConverter.h>
#include <sol/SmartPtrs.h>

namespace SOL {


/**
 * HTMLEncoder class 
 */
class HTMLEncoder :public Object {

public:
  /**
   *
   */
  HTMLEncoder() {

  }

public:
  /**
   * Convert the characters '&', '<', '>', ''' and '"' in html string to the strings 
   * "&amp;", "&lt;", "&gt;", "&#039;" and "&quot;" 
   *
   * @param  string  html string to be encoded.
   * @param  encoded  encoded string.  
   * @return  bool    
   */
  bool encode(const char* string, String& encoded) {
    bool rc = false;
    if (string) {
      char* enc = encode(string);
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  bool encode(const char* string, __out StringT<char>& encoded) {
    bool rc = false;
    if (string) {
      char* enc = encode(string);
      encoded.shallowCopy(enc);

      rc = true;
    }
    return rc;
  }

public:
  //2012/03/10
  bool encode(const wchar_t* string, StringT<wchar_t>& encoded) {
    bool rc = false;
    if (string) {
      wchar_t* enc = encode(string);
      encoded.shallowCopy(enc);
      rc = true;
    }
    return rc;
  }

public:
  //2009/12/22
  bool encode(const char* string, __out StringT<wchar_t>& encoded) {
    bool rc = false;
    if (string) {
      char* enc = encode(string);
      StringConverter converter;
      wchar_t* wenc = converter.toWideChar(enc);
      delete [] enc;
      encoded.shallowCopy(wenc);

      rc = true;
    }
    return rc;
  }

public:
  bool encode(const wchar_t* string, String& encoded) {
    bool rc = false;
    if (string) {
      wchar_t* enc = encode(string);
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  //2011/12/23
  bool encode(__in const char* string, __out _bstr_t& encoded) {
    bool rc = false;
    if (string) {
      char* enc = encode((const char*)string);
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  //2012/01/12
  bool encode(__in const _bstr_t bstring, __out _bstr_t& encoded) {
    bool rc = false;
    const char* string = (const char*)bstring;
    if (string) {
      char* enc = encode((const char*)string);
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  //2011/12/23
  bool encode(__in const wchar_t* string, __out _bstr_t& encoded) {
    bool rc = false;
    if (string) {
      wchar_t* enc = encode(string);
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }


public:
  //2012/03/10
  String encode(__in const String bstring) {
    const TCHAR* enc = NULL;
    const TCHAR* string = (const TCHAR*)bstring;
    if (string) {
      enc = encode(string);
    }
    return String(enc, false);
  }

public:
  //2012/03/10
  WString encode(__in const WString bstring) {
    const wchar_t* enc = NULL;
    const wchar_t* string = (const wchar_t*)bstring;
    if (string) {
      enc = encode(string);
    }
    return WString(enc, false);
  }


public:
  /**
   * Convert the characters '&', '<', '>', ''' and '"' in html string to the strings 
   * "&amp;", "&lt;", "&gt;", "&#039;" and "&quot;" 
   *
   * @param  string  html string to be encoded.
   * @return  char*  encoded string.  
   */
   char*  encode(const char* string) {

     static const char  specials[] = {'&',     '<',    '>',    '\'',     '"',    };//' '};
     static const char* entities[] = {"&amp;", "&lt;", "&gt;", "&#039;", "&quot;"};// "&nbsp;"};

    if (string == NULL) { 
      return NULL;
    }

    size_t slen = strlen(string)*6 + 1;

    char* encoded = new char[slen];

    memset(encoded, 0, slen);

    size_t len    = strlen(string);
    size_t splen = sizeof(specials)/sizeof(specials[0]);
  
    int n = 0;
    for (size_t i = 0; i<len; i++) {
      char c = string[i];  
      const char* entity = NULL;
      
      for (size_t j = 0; j<splen; j++) {
        if (c == specials[j]) {
          entity = entities[j];
          break;
        }
      }
      if (entity != NULL) {
        for(size_t s = 0; s<strlen(entity); s++) {
          encoded[n++] = entity[s];
        }
      } else {
        encoded[n++] = c;
      }
    }

    encoded[n] = '\0';

    return encoded;
  }

public:
  //2012/03/10 See sol/include/Wchardef.h
  wchar_t*  encode(const wchar_t* string) {

     static const wchar_t  specials[] = {'&',     '<',    '>',    '\'',     '"',    };//' '};
     static const wchar_t* entities[] = {L"&amp;", L"&lt;", L"&gt;", L"&#039;", L"&quot;"};// "&nbsp;"};

    if (string == NULL) { 
      return NULL;
    }

    size_t slen = strlen(string)*6 + 1;

    wchar_t* encoded = new wchar_t[slen];

    memset(encoded, (wchar_t)0, slen);

    size_t len    = strlen(string);
    size_t splen = sizeof(specials)/sizeof(specials[0]);
  
    int n = 0;
    for (size_t i = 0; i<len; i++) {
      wchar_t c = string[i];  
      const wchar_t* entity = NULL;
      
      for (size_t j = 0; j<splen; j++) {
        if (c == specials[j]) {
          entity = entities[j];
          break;
        }
      }
      if (entity != NULL) {
        for(size_t s = 0; s<strlen(entity); s++) {
          encoded[n++] = entity[s];
        }
      } else {
        encoded[n++] = c;
      }
    }

    encoded[n] = '\0';

    return encoded;
  }
};

}

