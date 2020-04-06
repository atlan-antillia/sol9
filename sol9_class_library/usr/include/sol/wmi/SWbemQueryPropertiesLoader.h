/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SWbemQueryPropertiesLoader.h
 *
 *****************************************************************************/

// SOL9
// 2015/12/15 Updated.

#pragma once

#include <sol/Exception.h>
#include <sol/wmi/SWbemQueryProperties.h>


namespace SOL {

class  SWbemQueryPropertiesLoader: public Object {

public:
  SWbemQueryPropertiesLoader()
  {

  }


public:

  bool load(__out SWbemQueryProperties& properties,
          __in_opt const TCHAR* propertiesFile=NULL)
  {
    bool rc = false;
    TCHAR filePath[_MAX_PATH];
    memset(filePath, (TCHAR)0, CountOf(filePath));

    const TCHAR* DEFAULT_PROPERTIES_FILE_NAME = _T("Query.properties"); 
    if (propertiesFile == NULL) {
      TCHAR module[_MAX_PATH];
      memset(module, (TCHAR)0, CountOf(module));
      GetModuleFileName(NULL, module, _MAX_PATH);
      TCHAR* dot = strrchr(module, '.');
      if (dot) {
        *dot = '\0';  //NULL terminated hered
      }
      _stprintf_s(filePath, CountOf(filePath), _T("%s.%s"), module, DEFAULT_PROPERTIES_FILE_NAME);
      
      if (GetFileAttributes(filePath) == 0xffffffff) {
        _bstr_t bstring = filePath;
        throw Exception(E_INVALIDARG, "File not found:\"%s\" %s",  (const char*)bstring, __FUNCTION__); 
      }
    } else {
      _stprintf_s(filePath, CountOf(filePath), _T("%s"), propertiesFile);
    }
    if (GetFileAttributes(filePath) == 0xffffffff) {
      _bstr_t bstring = filePath;

      throw Exception(E_INVALIDARG, "Filenot found:\"%s\" %s",  (const char*)bstring,  __FUNCTION__); 
    } else {
      rc = properties.load(filePath);
    }
    return rc;
  }

};

}
