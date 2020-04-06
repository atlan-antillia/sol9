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
 *  ShellLink.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/11
// 2012/06/25

#pragma once


#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/String.h>

namespace SOL {

class ShellLink :public Object {

private:
  IShellLink*  pShellLink;

private:
  IPersistFile*  pPersistFile;
  

public:
  ShellLink()
  :pPersistFile(NULL),
  pShellLink(NULL)
  {
    bool rc = false;
    HRESULT hr = S_OK;
    if (FAILED(hr = CoCreateInstance( CLSID_ShellLink, NULL,
        CLSCTX_INPROC_SERVER, IID_IShellLink, 
        (LPVOID *)&pShellLink)) ) {

      throw Exception(hr, "%s", __FUNCTION__);;
    }

    if (FAILED (hr = pShellLink->QueryInterface( IID_IPersistFile, 
      (LPVOID *)&pPersistFile)) ) {

      throw Exception(hr, "%s", __FUNCTION__);  
    }
  }
  
public:
  ~ShellLink()
  {
    if (pPersistFile != NULL) {
      pPersistFile->Release();
    }

    if( pShellLink != NULL) {
      pShellLink->Release();
    }
  }

public:
  bool load(__in const wchar_t* wlinkFile)
  {

    HRESULT hr = S_OK;
    if (FAILED(hr = pPersistFile->Load(wlinkFile, STGM_READ)) ) {
      throw Exception(hr, "%s", __FUNCTION__);
    }

    if (FAILED(hr = pShellLink->Resolve(NULL, SLR_NO_UI)) ) {
      throw Exception(hr, "%s", __FUNCTION__);    
    }
    return true;
  }

public:
  bool load(__in const char* shortCut)
  {
    wchar_t  wlinkFile[MAX_PATH];

    MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, shortCut, -1,
      wlinkFile, MAX_PATH );

    HRESULT hr = S_OK;
    if (FAILED(hr = pPersistFile->Load(wlinkFile, STGM_READ)) ) {
      throw Exception(hr, "%s", __FUNCTION__);
    }

    if (FAILED(hr = pShellLink->Resolve(NULL, SLR_NO_UI)) ) {
      throw Exception(hr, "%s", __FUNCTION__);    
    }
    return true;
  }

public:
  bool getPath(__out String& path)
  {
    TCHAR buffer[MAX_PATH];
    bool rc = getPath(buffer, CountOf(buffer));
    if (rc) {
      path = buffer;
    }
    return rc;
  }

public:
  bool getPath(__out TCHAR* path, __in int size)
  {
    WIN32_FIND_DATA wfd;

    HRESULT hr = E_FAIL;
    if (FAILED(hr = pShellLink->GetPath(path, size, &wfd, SLGP_UNCPRIORITY))) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return true;
  }

public:
  bool getPath(__out TCHAR* path, 
      __in int size,
      __out WIN32_FIND_DATA& wfd)
  {
    HRESULT hr = E_FAIL;
    if (FAILED(hr = pShellLink->GetPath(path, size, &wfd, SLGP_UNCPRIORITY))) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return true;
  }

public:
  bool getIconLocation(__out TCHAR* path, 
      __in int size,
      __out int *piIcon)
  {
    HRESULT hr = E_FAIL;
    if (FAILED(hr = pShellLink->GetIconLocation(path, size, piIcon))) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return true;
  }

};

}

