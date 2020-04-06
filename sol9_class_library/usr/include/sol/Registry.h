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
 *  Registry.h
 *
 *****************************************************************************/

// 2009/10/18 Modified to use StringT class.

#pragma once

#include <sol\Object.h>

#include <sol\String.h>
#include <sol\StringT.h>
#include <sol\StringConverter.h>

#include <sol\stdio.h>

namespace SOL {

class Registry :public Object {
private:
  HKEY baseKey;

private:
  /**
   * Constructor
   */
  Registry()
    :baseKey(NULL) 
  {
  }

public:
  /**
   * Constructor
   */
  Registry(HKEY base)
    :baseKey(base) 
  {
  }

public:
  /**
   */
  bool createKey(const TCHAR* regKey)
  {
    bool rc = false;
    if (regKey == NULL) {
      return rc;
    }

    HKEY hkReg = NULL; 
    if (RegOpenKeyEx(baseKey, _T(""), 0, KEY_READ, &hkReg) == ERROR_SUCCESS) {
  
      HKEY hSubKey = NULL;
      if (RegOpenKeyEx(hkReg, regKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {

        RegCloseKey(hSubKey);

        rc = true;
      } else {
        HKEY hKeyResult = NULL;
        if (RegCreateKey(hkReg, regKey, &hKeyResult) == ERROR_SUCCESS){
          rc = true;
        }
      }    
      RegCloseKey(hkReg);
    } 
    return rc;
  }

public:
  /**
   * @param regKey  [in]
   * @param regSubkey    [in]
   * @param text    [in,out] Buffer allocated by caller side. 
   * @param len    [in]     NumberOfElements of TCHAR array (TCHAR* text string)
   *              This is NOT bytesLength of TCHAR text
   */
  bool getText(__in const TCHAR* regKey, 
        __in const TCHAR* regSubkey, 
        __out TCHAR* text, 
        __in size_t len) 
  {
    bool rc = false;

    if (regKey == NULL || regSubkey == NULL || text ==NULL ||
      len <1) {
      return rc;
    }

    HKEY hkReg = NULL; 
    if (RegOpenKeyEx(baseKey, regKey, 0, KEY_READ, &hkReg) == ERROR_SUCCESS) {
      DWORD nType = REG_SZ; 

      DWORD cbData = 0;
      // 1 Get bytesSize(cbData) for this registry entry
      RegQueryValueEx(hkReg, regSubkey, NULL, &nType, NULL, &cbData);  

      // 2 BytesSize of parameter text TCHAR string.
      size_t textBytesSize = len*sizeof(TCHAR);

      if (textBytesSize<=cbData) {
        //3 Error;Buffer size for text is small.
        TCHAR error[1024];
        _stprintf_s(error, CountOf(error), 
          _T("Registry#getText() Error: buffer size(%d) is too small. It should be greater than %d.\r\nKey=%s rebsubKey=%s"),
          len, 
          cbData/sizeof(TCHAR)+1, 
          regKey, 
          regSubkey);

        MessageBox(NULL, error, _T("SOL9"), MB_OK);
        return rc;    
      }

      if (cbData>0) {
        TCHAR* data = (TCHAR*)new char[cbData];

        if (RegQueryValueEx(hkReg, regSubkey, NULL, 
          &nType, (LPBYTE)data, &cbData) == ERROR_SUCCESS){
          strcpy_s(text, len, data);
          rc = true;
        }
      
        delete [] data;
      }

      RegCloseKey(hkReg);
    }
    return rc;
  }



public:
  /** 
   * @param regKey    [in] 
   * @param regSubkey    [in]
   * @param text      [out]
   */
  // The type of regSubkey must be REG_SZ.
  bool getText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __out String& text) 
  {
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL) {
      return rc;
    }

    HKEY hkReg = NULL; 

    if (RegOpenKeyEx(baseKey, regKey, 0, KEY_READ, &hkReg) == ERROR_SUCCESS) {
      DWORD nType = REG_SZ; 

      DWORD cbData = 0;
      //Get the bytessize to return a value for a entry of regKey and regSubkey ;
      
      RegQueryValueEx(hkReg, regSubkey, NULL, 
        &nType, NULL, &cbData);  
      if (cbData >0) {
        TCHAR* data = (TCHAR*)new char[cbData];

        if (RegQueryValueEx(hkReg, regSubkey, NULL, 
          &nType, (LPBYTE)data, &cbData) == ERROR_SUCCESS){
          text.shallowCopy(data);
      
          rc = true;
        }
      }
      RegCloseKey(hkReg);
    }
    return rc;
  }

public:
  bool getText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __out StringT<char>& text) 
  {
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL) {
      return rc;
    }

    String string;
    rc = getText(regKey, regSubkey, string);
    if (rc) {
      StringConverter converter;
      converter.convert((const TCHAR*)string, text);
    }
    return rc;
  }

public:
  bool getText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __out StringT<wchar_t>& text) 
  {
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL) {
      return rc;
    }

    String string;
    rc = getText(regKey, regSubkey, string);
    if (rc) {
      StringConverter converter;
      converter.convert((const TCHAR*)string, text);
    }
    return rc;
  }


public:
  /**
   * @param regKey  [in]
   * @param regSubkey  [in]
   * @param  text  [in] NULL terminated TCHAR string.
   *
   */
  // The type of regSubkey must be REG_SZ.

  bool setText(__in const TCHAR* regKey, 
        __in const TCHAR* regSubkey, 
        __in const TCHAR* text) 
  {   
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || text ==NULL) {
      return rc;
    }

    HKEY hkReg = NULL; 
    DWORD dpos = 0;
    //We need bytes size for the TCHAR string of text
    // 
    size_t bytesLen = (strlen(text)+1) * sizeof(TCHAR);

    if (RegCreateKeyEx(baseKey, regKey, 0, NULL, 0,
      KEY_WRITE, NULL, &hkReg, &dpos) == ERROR_SUCCESS) {
      if (RegSetValueEx(hkReg, regSubkey, 0, REG_SZ, 
        (LPBYTE)text, (DWORD)bytesLen) == ERROR_SUCCESS){  
        rc = true;
      }
      RegCloseKey(hkReg);
    }
    return rc;
  }

public:
  bool setText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __in String& text) 
  { 
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || text ==NULL) {
      return rc;
    }
    String tstring(text);
    return setText(regKey, regSubkey, (const TCHAR*)tstring);
  }

public:
  bool setText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __in StringT<char>& text) 
  {   
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || text ==NULL) {
      return rc;
    }
    String tstring(text);
    return setText(regKey, regSubkey, tstring);
  }

public:
  bool setText(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __in StringT<wchar_t>& text) 
  {   
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || text ==NULL) {
      return rc;
    }
    String tstring(text);
    return setText(regKey, regSubkey, tstring);
  }

public:
  /**
   * @param regKey  [in]
   * @param regSubkey  [in]
   * @param value    [out]

   */
  // The type of regSubkey must be REG_DWORD.

  bool getInteger(__in const TCHAR* regKey, 
          __in const TCHAR* regSubkey, 
          __out int& value) 
  {   
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL) {
      return rc;
    }

    HKEY hkReg = NULL; 

    if (RegOpenKeyEx(baseKey, regKey, 0, 
        KEY_READ, &hkReg) == ERROR_SUCCESS) {

      DWORD nType = REG_DWORD; 
      DWORD cbData = sizeof(value);
      if (RegQueryValueEx(hkReg, regSubkey, NULL, 
        &nType, (LPBYTE)&value, &cbData) == ERROR_SUCCESS){  
        rc = true;
      } 
      RegCloseKey(hkReg);
    }
    return rc;
  }

public:
  /**
   * @param regKey  [in]
   * @param regSubkey  [in]
   * @param value    [in]
   */
  // The type of regSubkey must be REG_DWORD.

  bool setInteger(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __in int  value) 
  { 
    
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL) {
      return rc;
    }

    HKEY hkReg = NULL; 
    DWORD dpos = 0;

    if (RegCreateKeyEx(baseKey, regKey, 0, NULL, 0, 
        KEY_WRITE, NULL, &hkReg, &dpos) == ERROR_SUCCESS) {

      if (RegSetValueEx(hkReg, regSubkey, 0, REG_DWORD, 
          (CONST BYTE*)&value, sizeof(value)) == ERROR_SUCCESS){  
        rc = true;
      }
      RegCloseKey(hkReg);
    }
    return rc;
  }

public:
  /**
   * @param regKey    [in]
   * @param regSubkey    [in]
   * @param data      [in,out]
   * @param len      [in]
   */
  // The type of regSubkey must be REG_BINARY.

  bool getBinary(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __out unsigned char* data,
        __in size_t len) 
  { 
    
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || data ==NULL ||
      len <1) {
      return rc;
    }

    HKEY hkReg = NULL; 
    if (RegOpenKeyEx(baseKey, regKey, 0, KEY_READ, &hkReg) == ERROR_SUCCESS) {
    
      DWORD nType = REG_BINARY; 
      DWORD cbData = 0;

      RegQueryValueEx(hkReg, regSubkey, NULL, &nType, NULL, &cbData);
      if (cbData>len) {  
        TCHAR error[1024];
        _stprintf_s(error, CountOf(error), 
          _T("Registry#getBinary() Error: buffer size(%d) is too small. It should be greater than %d.\r\nKey=%s rebsubKey=%s"),
        len, 
        cbData, 
        regKey, 
        regSubkey);

        MessageBox(NULL, error, _T("SOL9"), MB_OK);
        return rc;
      }

      if (RegQueryValueEx(hkReg, regSubkey, NULL, &nType, (LPBYTE)data, &cbData) == ERROR_SUCCESS){
        rc = true;
      }
  
      RegCloseKey(hkReg);
    }
    return rc;
  }

public:
  /**
   * @param regKey    [in]
   * @param regSubkey    [in]
   * @param data      [in,out]
   * @param len      [in]
   */
  // The type of regSubkey must be REG_BINARY.
  //2009/06/18
  bool setBinary(__in const TCHAR* regKey, 
        __in const TCHAR*   regSubkey, 
        __in unsigned char* data,
        __in size_t len) 
  { 
    bool rc = false;
    if (regKey == NULL || regSubkey == NULL || data ==NULL ||
      len <1) {
      return rc;
    }

    HKEY hkReg = NULL; 
    DWORD dpos = 0;

    if (RegCreateKeyEx(baseKey, regKey, 0, NULL, 0, 
        KEY_WRITE, NULL, &hkReg, &dpos) == ERROR_SUCCESS) {

      if (RegSetValueEx(hkReg, regSubkey, 0, REG_BINARY, 
          (CONST BYTE*)data, (DWORD)len) == ERROR_SUCCESS){
        rc = true;
      }
      RegCloseKey(hkReg);
    }
    return rc;
  }


public:
  long enumKey(DWORD index, TCHAR* name, DWORD* cbName)
  {
    FILETIME lastWrite;
    return ::RegEnumKeyEx(this->baseKey, index, name, cbName, NULL,
        NULL, 0, &lastWrite);
  }

public:
  long enumKey(DWORD index, TCHAR* name, DWORD* cbName,
    TCHAR* cls, DWORD* cbCls, FILETIME* lastWrite)
  {
    return ::RegEnumKeyEx(this->baseKey, index, name, cbName, NULL,
        cls, cbCls, lastWrite);
  }

public:
  long enumValue(DWORD index, TCHAR* value, DWORD* cbValue,
    DWORD* type, BYTE* data, DWORD* cbData)
  {
    return ::RegEnumValue(this->baseKey, index, value, cbValue, NULL,
        type, data, cbData);
  }

public:
  int setValue(const TCHAR* subkey, DWORD type, const TCHAR* value, int cbsize)
  {
    return ::RegSetValueEx(this->baseKey, subkey, NULL, type, 
      (const byte*) value, cbsize);
  }
 

public:
  int getValue(const TCHAR* subkey, DWORD* type, TCHAR* value, DWORD* cbsize)
  {
    return ::RegQueryValueEx(this->baseKey, subkey, NULL, type, 
        (byte*)value, cbsize);
  }
  
};

}

