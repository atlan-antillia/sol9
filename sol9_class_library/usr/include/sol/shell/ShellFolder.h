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
 *  ShellFolder.h
 *
 *****************************************************************************/


// 2012/10/30
// 2012/11/30 Added new constructor, and getSystemImageListIndex method.
// 

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class ShellFolder: public ComIUnknown {

public:
  ShellFolder(IShellFolder* pFolder)
  :ComIUnknown(pFolder)
  {
  }

public:
  //2012/11/30
  ShellFolder(PIDLIST_ABSOLUTE pidl)
  :ComIUnknown()
  {  
    IShellFolder* pFolder = NULL;
    //Bind the pidl to its parent shellFolder
    HRESULT  hr = SHBindToParent(pidl, IID_IShellFolder, (void**)&pFolder, NULL);
    if (FAILED(hr)) { 
      throw hr;
    } else {
      set(pFolder);
    }
  }

public:
  ShellFolder(const wchar_t* path)
  :ComIUnknown()
  {
    PIDLIST_ABSOLUTE pidl = NULL;
    HRESULT hr = SHILCreateFromPath(path, &pidl, NULL);
     if (FAILED(hr)) {
      throw hr;
    } else {
      IShellFolder* pFolder = NULL;

      hr = SHBindToParent(pidl, IID_IShellFolder, (void**)&pFolder, NULL);
      ILFree(pidl);
      if (FAILED(hr)) { 
        throw hr;
      } else {
        set(pFolder);
      }
    }
  }

public:
  IShellFolder* getFolder()
  {
    return (IShellFolder*)getIUnknown();
  }

public:
  HRESULT parseDisplayName( 
            /* [in] */ HWND hwnd,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ LPWSTR pszDisplayName,
            /* [out][in] */ ULONG *pchEaten,
            /* [out] */ PIDLIST_RELATIVE *ppidl,
            /* [out][in] */ ULONG *pdwAttributes)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> ParseDisplayName( 
        hwnd,
        pbc,
        pszDisplayName,
        pchEaten,
        ppidl,
        pdwAttributes);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT enumObjects( 
            /* [in] */ HWND hwnd,
            /* [in] */ SHCONTF grfFlags,
            /* [out] */ IEnumIDList **ppenumIDList)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> EnumObjects( 
        hwnd,
        grfFlags,
        ppenumIDList);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IEnumIDList* enumObjects( 
            /* [in] */ HWND hwnd,
            /* [in] */ SHCONTF grfFlags)
  {
    IEnumIDList* penumIDList = NULL;
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> EnumObjects( 
        hwnd,
        grfFlags,
        &penumIDList);

    if (FAILED(hr)) {
      throw hr;
    }
    return penumIDList;
  }

        
public:
  HRESULT bindToObject( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> BindToObject( 
        pidl,
        pbc,
        riid,
        ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT bindToStorage( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> BindToStorage( 
        pidl,
        pbc,
        riid,
        ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT compareIDs( 
            /* [in] */ LPARAM lParam,
            /* [in] */ PCUIDLIST_RELATIVE pidl1,
            /* [in] */ PCUIDLIST_RELATIVE pidl2)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> CompareIDs( 
        lParam,
        pidl1,
        pidl2);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT createViewObject( 
            /* [in] */ HWND hwndOwner,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> CreateViewObject( 
        hwndOwner,
        riid,
        ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getAttributesOf( 
            /* [in] */ UINT cidl,
            /* [in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [out][in] */ SFGAOF *rgfInOut)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetAttributesOf( 
        cidl,
        apidl,
        rgfInOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;

  }
        

public:
  HRESULT getUIObjectOf( 
            /* [in] */ HWND hwndOwner,
            /* [in] */ UINT cidl,
            /* [in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ REFIID riid,
            /* [out][in] */ UINT *rgfReserved,
            /* [out] */ void **ppv)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetUIObjectOf( 
        hwndOwner,
        cidl,
        apidl,
        riid,
        rgfReserved,
        ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  void* getUIObjectOf( 
            /* [in] */ HWND hwndOwner,
            /* [in] */ UINT cidl,
            /* [in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ REFIID riid,
            /* [out][in] */ UINT *rgfReserved)
  {
    void* pv = NULL;
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetUIObjectOf( 
        hwndOwner,
        cidl,
        apidl,
        riid,
        rgfReserved,
        &pv);
    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }

public:
  HRESULT getDisplayNameOf( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ STRRET *pName)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetDisplayNameOf( 
        pidl,
        uFlags,
        pName);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }



public:
  HRESULT setNameOf( 
            /* [in] */ HWND hwnd,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ LPCWSTR pszName,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ PITEMID_CHILD *ppidlOut)
  {
    IShellFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> SetNameOf( 
        hwnd,
        pidl,
        pszName,
        uFlags,
        ppidlOut);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  //2012/11/30
  int getSystemImageListIndex(PITEMID_CHILD pidlChild, int& openIconIndex)  
  {
    IShellFolder* pFolder = getFolder();

    int normalIconIndex = SHMapPIDLToSystemImageListIndex(
      pFolder,
      pidlChild,
      &openIconIndex);
    return normalIconIndex;
  }    
};
    
}
