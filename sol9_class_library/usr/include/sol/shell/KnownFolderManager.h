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
 *  KnownFolderManager.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class KnownFolderManager: public ComIUnknown {

public:
  KnownFolderManager()
  {
    IKnownFolderManager *pkfm = NULL;
    HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager, 
                      NULL, 
                      CLSCTX_INPROC_SERVER, 
                      IID_PPV_ARGS(&pkfm));
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pkfm);
    }
  }

public:
  IKnownFolderManager* getManager()
  {
    return (IKnownFolderManager*)getIUnknown();
  }
 
public:
  HRESULT folderIdFromCsidl( 
            /* [in] */ int nCsidl,
            /* [out] */ KNOWNFOLDERID *pfid)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FolderIdFromCsidl( 
        nCsidl,
        pfid);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  KNOWNFOLDERID folderIdFromCsidl( 
            /* [in] */ int nCsidl)
  {
    KNOWNFOLDERID fid;

    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FolderIdFromCsidl( 
        nCsidl,
        &fid);

    if (FAILED(hr)) {
      throw hr;
    }
    return fid;
  }


public:
  HRESULT folderIdToCsidl( 
            /* [in] */ REFKNOWNFOLDERID rfid,
            /* [out] */ int *pnCsidl)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FolderIdToCsidl( 
        rfid,
        pnCsidl);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int folderIdToCsidl( 
            /* [in] */ REFKNOWNFOLDERID rfid)
  {
    int nCsidl;
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FolderIdToCsidl( 
        rfid,
        &nCsidl);

    if (FAILED(hr)) {
      throw hr;
    }
    return nCsidl;
  }
        

public:
  HRESULT getFolderIds( 
            /* [out] */ KNOWNFOLDERID **ppKFId,
            /* [out] */ UINT *pCount)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> GetFolderIds( 
        ppKFId,
        pCount);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT getFolder( 
            /* [in] */ REFKNOWNFOLDERID rfid,
            /* [out] */ IKnownFolder **ppkf)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> GetFolder( 
        rfid,
        ppkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IKnownFolder* getFolder( 
            /* [in] */ REFKNOWNFOLDERID rfid)
  {
    IKnownFolder* pkf = NULL;

    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> GetFolder( 
        rfid,
        &pkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return pkf;
  }


public:
  HRESULT getFolderByName( 
            /* [in] */ const wchar_t* pszCanonicalName,
            /* [out] */ IKnownFolder **ppkf)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> GetFolderByName( 
        pszCanonicalName,
        ppkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IKnownFolder* getFolderByName( 
            /* [in] */ const wchar_t* pszCanonicalName)
  {
    IKnownFolder *pkf = NULL;

    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> GetFolderByName( 
        pszCanonicalName,
        &pkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return pkf;
  }


public:
  HRESULT registerFolder( 
            /* [in] */ REFKNOWNFOLDERID rfid,
            /* [in] */ const KNOWNFOLDER_DEFINITION *pKFD)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> RegisterFolder( 
        rfid,
        pKFD);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT unregisterFolder( 
            /* [in] */ REFKNOWNFOLDERID rfid)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> UnregisterFolder( 
        rfid);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT findFolderFromPath( 
            /* [in] */ const wchar_t* pszPath,
            /* [in] */ FFFP_MODE mode,
            /* [out] */ IKnownFolder **ppkf)
  {
    IKnownFolderManager* pManager = getManager();

    HRESULT hr = pManager -> FindFolderFromPath( 
        pszPath,
        mode,
        ppkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IKnownFolder* findFolderFromPath( 
            /* [in] */ const wchar_t* pszPath,
            /* [in] */ FFFP_MODE mode=FFFP_EXACTMATCH)
  {
    IKnownFolder *pkf = NULL;

    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FindFolderFromPath( 
        pszPath,
        mode,
        &pkf);

    if (FAILED(hr)) {
      throw hr;
    }
    return pkf;
  }
        
public:
  HRESULT  findFolderFromIDList( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl,
            /* [out] */ IKnownFolder **ppkf)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FindFolderFromIDList( 
        pidl,
        ppkf);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IKnownFolder* findFolderFromIDList( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl)
  {
    IKnownFolder* pkf = NULL;

    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> FindFolderFromIDList( 
        pidl,
        &pkf);
    if (FAILED(hr)) {
      throw hr;
    }
    return pkf;
  }

        
public:
  HRESULT redirect( 
            /* [in] */ REFKNOWNFOLDERID rfid,
            /* [in] */ HWND hwnd,
            /* [in] */ KF_REDIRECT_FLAGS flags,
            /* [in] */ LPCWSTR pszTargetPath,
            /* [in] */ UINT cFolders,
            /* [in] */ const KNOWNFOLDERID *pExclusion,
            /* [out] */ LPWSTR *ppszError)
  {
    IKnownFolderManager* pManager = getManager();
    HRESULT hr = pManager -> Redirect( 
        rfid,
        hwnd,
        flags,
        pszTargetPath,
        cFolders,
        pExclusion,
        ppszError);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
};

}
