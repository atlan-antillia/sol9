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
 *  Profile.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/01 Modified to inherit class CurrentUserRegistry.
// The following registry is used.
//  "HKEY_CURRENT_USER\\Software\\Antillia\\Application\\[ModuleName]"
// Log output level for a SOL::LogWriter object gotten from the LogWriter::getInstance method
//  is defined in the following key on "Level"
//
//  "HKEY_CURRENT_USER\\Software\\Antillia\\Application\\[ModuleName]\\Log"
//
// 2008/09/13 Added two methods: setFileFolder/getFileFolder.
//
// 2009/06/20 Added two methods for wchar_t* string:
//  bool set(const char* section, char* entry, const wchar_t* wstring, size_t wlen)
//  bool get(const char* section, char* entry, wchar_t* wstring, size_t wlen)

#pragma once

#include <sol\Object.h>
#include <sol\CurrentUserRegistry.h>
#include <sol\Folder.h>

#include <mbstring.h>

#include <sol/StringT.h>
#include <sol/StringConverter.h>

namespace SOL {

class Profile :public CurrentUserRegistry {
private:
  TCHAR  key[SIZE_1KB];
 
public:
  /**
   * Constructor.
   * 
   * Note that the following registry is used to store your profile on
   *this constructor without argument.
   *
   * HKEY_CURRENT_USER\\Software\\Antillia\\Application\\[ModuleName]"
   */
  Profile(const TCHAR* name=NULL)
    :CurrentUserRegistry()
  {
    memset(key, (TCHAR)0, CountOf(key));

    wchar_t fileName[_MAX_PATH];
    wchar_t* wname = NULL;
    StringT<TCHAR> tname=_T("");

    //String moduleName = _T("");
    if(name) {
      tname = name;
    }

    else {
      //Get the module name from the current executable program.
      ::GetModuleFileNameW(NULL, fileName, _MAX_PATH);
      wname = ::wcsrchr(fileName, (wchar_t)'\\');
      if (wname) {
        wname++;      
      }
      wchar_t* dot = (wchar_t*)strrchr(wname, '.');
      if (dot) {
        *dot = (TCHAR)0;
      }
      StringConverter converter;
      converter.convert(wname, tname);
    }

    _stprintf_s(key, CountOf(key), _T("Software\\Antillia\\Application\\%s"), 
      (const TCHAR*)tname);

    //MessageBox(NULL, key, "Profile", MB_OK);
    createKey(key);
  }

public:
  ~Profile()
  {
  }

public:
  int get(const TCHAR* section, const TCHAR* entry, int defvalue)
  {
    int rc = defvalue;
    int value =0;
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    if (getInteger(regKey, entry, value)) {
      rc = value;  
    }
    return rc;
  }

public:
  bool get(__in const TCHAR* section, __in const TCHAR* entry, 
    __out String& value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);
    return getText(regKey, entry, value);
  }

public:
  bool get(__in const TCHAR* section, __in const TCHAR* entry, 
    __out StringT<char>& value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);
    return getText(regKey, entry, value);
  }

public:
  bool get(__in const TCHAR* section, __in const TCHAR* entry, 
    __out StringT<wchar_t>& value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);
    return getText(regKey, entry, value);
  }

public:
  bool get(const TCHAR* section, const TCHAR* entry,
    TCHAR* buff, UINT bufflen)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);
    return getText(regKey, entry, buff, bufflen);
  }

public:
  bool get(const TCHAR* section, const TCHAR* entry, TCHAR* defvalue, 
    TCHAR* buff, UINT bufflen)
  {
    bool rc = false;
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    if (getText(regKey, entry, buff, bufflen)) {
      rc = true;
    } else {
      strcpy_s(buff, bufflen, defvalue);
    }
    return rc;
  }

public:
  bool getLogLevel(int& level)
  {
    bool rc = false;
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, _T("Log"));
    if (getInteger(regKey, _T("Level"), level)) {
      rc = true;
    }
    return rc;
  }

public:
  bool getGeometry(int* x, int* y, int* w, int* h)
  {
    bool rc = false;

      *x = CW_USEDEFAULT;
    *y = CW_USEDEFAULT;
    *w = CW_USEDEFAULT;
    *h = CW_USEDEFAULT;

    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, _T("Windows"));

    TCHAR geo[128];

    if(getText(regKey, _T("Geometry"), geo, CountOf(geo) )) {
      _stscanf_s(geo, _T("%d %d %d %d"), x, y, w, h);
      if (*w <=0)  *w =400;
      if (*h <=0)  *h =300; 
      rc = true;
    }
    return rc;
  }

public:
  bool set(const TCHAR* section, const TCHAR* entry, int value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setInteger(regKey, entry, value);

  }

public:
  bool set(const TCHAR* section, const TCHAR* entry, TCHAR* value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);
    
    return setText(regKey, entry, value);

  }

public:
  bool set(const TCHAR* section, const TCHAR* entry, __in StringT<char>&  value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setText(regKey, entry, value);

  }
public:
  bool set(const TCHAR* section, const TCHAR* entry, __in StringT<wchar_t>& value)
  {
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setText(regKey, entry, value);

  }

public:
  //2008/09/14: Added
  // Used to store a selected folder in SOL::FileDialog to registry. 
  bool setFileFolder(const TCHAR* value=_T(".\\"))
  {
    const TCHAR* section = _T("FileFolder");
    const TCHAR* entry   = _T("directory");
    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setText(regKey, entry, value);

  }

public:
  //2008/09/14: Added
  // Used to restore a previously selected folder in SOL::FileDialog to registry. 
  bool getFileFolder(TCHAR* value, UINT len)
  {
    const TCHAR* section = _T("FileFolder");
    const TCHAR* entry   = _T("directory");
    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return getText(regKey, entry, value, len);
  }

public:
  //2017/03/28 Added
  // Used to store a selected folder in SOL::FolderBrowser to registry. 
  bool setFolderBrowserFolder(const TCHAR* value=_T(".\\"))
  {
    const TCHAR* section = _T("FolderBrowser");
    const TCHAR* entry   = _T("directory");
    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setText(regKey, entry, value);

  }

public:
  //2017/09/14: Added
  // Used to get a previously selected folder in SOL::FolderBrowser to registry. 
  bool getFolderBrowserFolder(TCHAR* value, UINT len)
  {
    const TCHAR* section = _T("FolderBrowser");
    const TCHAR* entry   = _T("directory");
    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return getText(regKey, entry, value, len);
  }

public:
  //2009/06/20
  bool set(const TCHAR* section, TCHAR* entry, const wchar_t* wstring, size_t wlen)
  {    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return setBinary(regKey, entry, (unsigned char*)wstring, (wlen+1)*2);
  }

public:
  //2009/06/20
  bool get(const TCHAR* section, TCHAR* entry, wchar_t* wstring, size_t wlen)
  {    
    TCHAR regKey[SIZE_1KB];
    _stprintf_s(regKey, CountOf(regKey), _T("%s\\%s"), this->key, section);

    return getBinary(regKey, entry, (unsigned char*)wstring, (wlen+1)*2);
  }

public:
  void setGeometry(int x, int y, int w, int h)
  {
    TCHAR geo[128];
    _stprintf_s(geo, CountOf(geo), 
        _T("%d %d %d %d"), x, y, w, h);
    set(_T("Windows"), _T("Geometry"), geo);
  }

public:
  void setGeometry(RECT* r)
  {
    TCHAR geo[128];
    _stprintf_s(geo, CountOf(geo),
      _T("%d %d %d %d"), r->left, r->top,
      r->right - r->left, r->bottom - r->top);
    set(_T("Windows"), _T("Geometry"), geo);
  }
};

}

