/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Guid.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2010/12/16 Added a static 'toString' method
// 2012/08/30 Updated

/*
  typedef struct _GUID {
    DWORD  Data1;      // 4
    WORD   Data2;      // 2
    WORD   Data3;      // 2
    BYTE   Data4[8];   // 1Å~8
  } GUID, UUID;
*/


#pragma once

#include <sol\Object.h>
#include <sol\StringT.h>
#include <sol\Bytes.h>
#include <sol\StringConverter.h>
#include <sol\Exception.h>

#pragma comment(lib, "ole32.lib")

/**
 * Guid class
 */

namespace SOL {

class Guid :public Object {

public:
  /**
   */
  Guid() {
  }

public:
  /**
   * Create a new GUID of bytes of the form:
   *  43 09 61 9F 19 58 B1 40 95 F6 91 A2 13 79 D7 F0,
   * and return a string like: "{9F610943-5819-40B1-95F6-91A21379D7F0}"
   *
   * @param id  Reference to String. GUID of string format something like:
   *        "{9F610943-5819-40B1-95F6-91A21379D7F0}"
   */
  bool create(__out StringT<TCHAR>& id) { 
    bool rc = false;
    GUID guid;
    if (SUCCEEDED(CoCreateGuid(&guid))) {
      /*
      int len = sizeof(guid);
      unsigned char* data = new unsigned char[len];
      memcpy(data, &guid, len);
      ByteArray ba;
      ba.shallowCopy(data, len);
      ba.dump();
      */
      wchar_t buff[128];
      if(StringFromGUID2(guid, buff, CountOf(buff))) {
    
        StringConverter converter;
        converter.convert(buff,id);
        //char* tmp = converter.toMultiByte(buff);
        //id.shallowCopy(tmp);

        rc = true;
      }
    }
    return rc;
  }

public:
  /**
   * Create a new GUID of bytes of the form:
   *  43 09 61 9F 19 58 B1 40 95 F6 91 A2 13 79 D7 F0,
   * and return it
   *
   * @param ba  Reference to ByteArray. GUID of byte format something like:
   *        43 09 61 9F 19 58 B1 40 95 F6 91 A2 13 79 D7 F0
   */
  bool create(Bytes& ba) { 
    bool rc = false;
    GUID guid;
    if (SUCCEEDED(CoCreateGuid(&guid))) {
      int len = sizeof(guid);
      unsigned char* data = new unsigned char[len];
      memcpy(data, &guid, len);
      ba.shallowCopy(data, len);
      rc = true;
    }
    return rc;
  }

public:
  /**
   * @param guid  GUID
   * @param id  Reference to String. GUID of string format something like:
   *        "{9F610943-5819-40B1-95F6-91A21379D7F0}"
   */
  //2010/12/16
  static const TCHAR* toString(__in GUID guid, __out StringT<TCHAR>& id) { 
    id = _T("");

    wchar_t buff[128];
    if(StringFromGUID2(guid, buff, CountOf(buff))) {
    
      StringConverter converter;
      converter.convert(buff,id);
    }
    return (const TCHAR*)id;
  }

  //2012/08/30
  static _bstr_t toString(__in GUID guid) 
  { 
    wchar_t buff[128];
    if(StringFromGUID2(guid, buff, CountOf(buff))) {
      return _bstr_t(buff);
    } else {
      throw Exception(0, "Failed to convert guid to string");
    }
  }
};

}

