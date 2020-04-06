/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FolderViewHost.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class FolderViewHost: public ComIUnknown {

public:
  FolderViewHost()
  {
    IFolderViewHost* pHost = NULL;
    HRESULT hr = CoCreateInstance(CLSID_FolderViewHost, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pHost));
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pHost);
    }
  }


public:
  IFolderViewHost* getHost()
  {
    return (IFolderViewHost*)getIUnknown();
  }

public:
  HRESULT initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ IDataObject *pdo,
            /* [in] */ RECT& rec)
  {
    IFolderViewHost* pHost = getHost();
    HRESULT hr = pHost -> Initialize(
        hwndParent,
        pdo,
        &rec);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

    
public:
  HRESULT initialize(HWND hwndParent, PIDLIST_ABSOLUTE pidl)
  {
    IDataObject* pDataObject = NULL;

    HRESULT hr = SHCreateDataObject(pidl, 0, 0, NULL, IID_IDataObject, (void**)&pDataObject);
    if (FAILED(hr)) {
      throw hr;
    } 

    IFolderViewHost* pHost = getHost();
    RECT rec = {0, 0, 0, 0};
    hr = pHost->Initialize(hwndParent, pDataObject, &rec);
    pDataObject->Release();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
    IShellBrowser* getShellBrowser()
  {
    IShellBrowser* pBrowser = NULL;
    IFolderViewHost* pHost = getHost();

    HRESULT hr = pHost ->QueryInterface(IID_PPV_ARGS(&pBrowser));
    if (FAILED(hr)) {
      throw hr;
    }
    return pBrowser;
  }

public:
  IShellView* queryActiveView()
  {
    IShellView* pView = NULL;
    IShellBrowser* pBrowser = getShellBrowser();
    HRESULT hr = pBrowser->QueryActiveShellView(&pView);
    if (FAILED(hr)) {
      throw hr;
    }
    return pView;
  }

};

}
