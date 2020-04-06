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
 *  StringConverter.h
 *
 *****************************************************************************/


#pragma once

#include <sol\Object.h>
#include <sol\StringT.h>

/**
 */
namespace SOL {

class StringConverter :public Object {

public:
  StringConverter() {
  }

public:
  // char -> char
  bool convert(const char* mbstring, __out StringT<char>& string)
  {
    bool rc = false;
    if (mbstring) {
      //return a copy of mbstring
      string = mbstring;
      rc = true;
    }
    return rc;
  }

public:
  // char -> wchar_t
  bool convert(const char* mbstring, __out StringT<wchar_t>& string)
  {
    return toWideChar(mbstring, string);
  }

public:
  // wchar_t -> char
  bool convert(const wchar_t* wcstring, __out StringT<char>& string)
  {
    return toMultiByte(wcstring, string);
  }

public:
  // wchar_t -> wchar_t
  bool convert(const wchar_t* wcstring, __out StringT<wchar_t>& string)
  {
    bool rc = false;
    if (wcstring) {
      //return a copy of mbstring
      string = wcstring;
      rc = true;
    }
    return rc;
  }


public:
  /**
   * MultiByteString -> WideCharString(Unicode)
   */
  wchar_t* toWideChar(const char* mbstring) {
    wchar_t* wcstring = NULL;

    if (mbstring == NULL) {
      return wcstring;
    }
    
    int cb = MultiByteToWideChar(CP_ACP, 0, mbstring, -1, NULL, 0); 
    if (cb >0) {
      wcstring = new wchar_t[cb];
      wcstring[0] = ZERO;
      MultiByteToWideChar(CP_ACP, 0, mbstring, -1, wcstring, cb); 
    }
    return wcstring;
  }

public:
  /**
   * WideCharString -> WideCharString(Unicode)
   */
  wchar_t* toWideChar(const wchar_t* wstring) {
    wchar_t* wcstring = NULL;

    if (wstring == NULL) {
      return wcstring;
    }

    //Simply return a duplicate wchar_t string.
    wcstring = _strdup(wstring);

    return wcstring;
  }

public:
  /**
   * MultiByteString -> WideCharString(Unicode)
   */
  //2009/10/10
  bool toWideChar(__in const char* mbstring, __out StringT<wchar_t>& stringw) {
    bool rc = false;

    if (mbstring == NULL) {
      return rc;
    }
    
    int cb = MultiByteToWideChar(CP_ACP, 0, mbstring, -1, NULL, 0); 
    if (cb >0) {
      wchar_t* wcstring = NULL;

      wcstring = new wchar_t[cb];
      wcstring[0] = ZERO;
      MultiByteToWideChar(CP_ACP, 0, mbstring, -1, wcstring, cb);
      stringw.shallowCopy(wcstring);
      rc = true;
    }
    return rc;
  }

public:
  /**
   * WideCharString(Unicode) -> MultiByteString 
   */
  char* toMultiByte(const wchar_t* wcstring) {

    char* mbstring = NULL;

    if (wcstring == NULL) {
      return mbstring;
    }
    
    int cb = WideCharToMultiByte(CP_ACP, 0, wcstring, -1, NULL, 0, NULL, NULL);
    
    if (cb > 0) {
      mbstring = new char[cb];
      mbstring[0] = ZERO;
      WideCharToMultiByte(CP_ACP, 0, wcstring, -1, mbstring, cb, NULL, NULL);
    }
    return mbstring;
  }

public:
  /**
   * MultiByteString(Unicode) -> MultiByteString 
   */
  char* toMultiByte(const char* cstring) {

    char* mbstring = NULL;

    if (cstring == NULL) {
      return mbstring;
    }

    //Simply return a duplicate char string.
    mbstring = _strdup(cstring);

    return mbstring;
  }



public:
  /**
   * WideCharString(Unicode) -> MultiByteString 
   */
  //2009/10/10
  bool toMultiByte(__in const wchar_t* wcstring, __out StringT<char>& stringt) {

    bool rc = false;

    if (wcstring == NULL) {
      return rc;
    }
    
    int cb = WideCharToMultiByte(CP_ACP, 0, wcstring, -1, NULL, 0, NULL, NULL);
    
    if (cb > 0) {
      char* mbstring = new char[cb];
      mbstring[0] = ZERO;
      WideCharToMultiByte(CP_ACP, 0, wcstring, -1, mbstring, cb, NULL, NULL);
      
      stringt.shallowCopy(mbstring);

      rc = true;
    }
    return rc;
  }


public:
  /**
   * MultiByteString -> BSTR
   */
  BSTR toBSTR(const char* mbstring) {
  
     BSTR bstring = NULL;
  
    if (mbstring == NULL) {
      return bstring;
    }

    int  cb = MultiByteToWideChar(CP_ACP, 0, mbstring, -1, NULL, NULL) -1;
     bstring = SysAllocStringLen(NULL, cb);
    if (bstring != NULL) {
      MultiByteToWideChar(CP_ACP, 0, mbstring, -1, bstring, cb);
    }
    return bstring;
  }

public:
  //2009/06/18
  BSTR toBSTR(const wchar_t* wcstring)
  {
    BSTR bstring = NULL;
    if (wcstring == NULL) {
      return bstring;
    }
  
    bstring = SysAllocStringLen(wcstring, (UINT)wcslen(wcstring));

    return bstring;
  }
};

}
