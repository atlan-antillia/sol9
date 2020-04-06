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
 *  URLEncoder.h
 *
 *****************************************************************************/

#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol/WString.h>

#include <sol/StringT.h>

/**
 */
namespace SOL {

class URLEncoder :public Object {

public:
  /**
   */
  URLEncoder() {
  }

  /**
   */
  ~URLEncoder() {
  }

public:
  /**
   * @param data    [IN]  Null-terminated string to encode.
   * @param encoded  [OUT]  URL-encoded string.
   */
  bool encode(__in const _bstr_t data, __out _bstr_t& encoded) {
    bool rc = false;

    char* enc = encode((const char*)data);
    if (enc) {
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  /**
   * @param data    [IN]  Null-terminated string to encode.
   * @param encoded  [OUT]  URL-encoded string.
   */
  bool encode(const char* data, String& encoded) {
    bool rc = false;
    char* enc = encode(data);
    if (enc) {
      encoded = enc;
      delete [] enc;
      rc = true;
    }
    return rc;
  }

public:
  //2009/11/28
  /**
   * @param data    [IN]  Null-terminated string to encode.
   * @param encoded  [OUT]  URL-encoded string.
   */
  bool encode(const char* data, StringT<char>& encoded) {
    bool rc = false;
    char* enc = encode(data);
    if (enc) {
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
   * @param data  [IN] Null-terminated string to encode.
   * @return char*  URL-encoded string.
   */
  char* encode(const char* data) {

    if (data == NULL) {
      return NULL;
    }
    static const char table[] = "0123456789ABCDEF";

    int len = strlen(data);

    int slen = len*3 + 1;
    char* buffer = new char[slen];
    memset(buffer, 0, slen);
  
    int n = 0;
    for (int i = 0; i < len; i++) {
      //Important
      unsigned char c = (unsigned char)data[i] & 0xff;
      if (isalnum(c)) {
        buffer[n++] = c;
      }
      else if ( c == '-' || c == '_' || c== '.' || c== '*') {
        buffer[n++] = c;  
        //Refer Java URLEncoder class.
      }
      else if (c == ' '){
        buffer[n++] = '+';
      } else {
        buffer[n++] = '%';
        buffer[n++] = table[c/16]; 
        buffer[n++] = table[c%16];
      }
      }
  
    buffer[n] = ZERO;  
    return buffer;
  }

public:
  wchar_t* encode(const wchar_t* data) {

    if (data == NULL) {
      return NULL;
    }
    static const wchar_t table[] = L"0123456789ABCDEF";

    int len = wcslen(data);

    int slen = len*3 + 1;
    wchar_t* buffer = new wchar_t[slen];
    memset(buffer, (wchar_t)0, slen);
  
    int n = 0;
    for (int i = 0; i < len; i++) {
  
      wchar_t c = (wchar_t)data[i] & 0xffff; //0xff;
      if (iswalnum(c)) {
        buffer[n++] = c;
      }
      else if ( c == '-' || c == '_' || c== '.' || c== '*') {
        buffer[n++] = c;  
        //Refer Java URLEncoder class.
      }
      else if (c == ' '){
        buffer[n++] = '+';
      } else {
        buffer[n++] = '%';
        buffer[n++] = table[c/16]; 
        buffer[n++] = table[c%16];
      }
      }
  
    buffer[n] = ZERO;  
    return buffer;
  }
};

}



