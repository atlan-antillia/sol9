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
 *  ShellItemArray.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class ShellItemArray: public ComIUnknown {

public:
  ShellItemArray(IShellItemArray* pArray)
  :ComIUnknown(pArray)
  {
  }

public:
  IShellItemArray* getArray()
  {
    return (IShellItemArray*)getIUnknown();
  }

public:
  HRESULT bindToHandler( 
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID bhid,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppvOut)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> BindToHandler( 
            pbc,
            bhid,
            riid,
          ppvOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getPropertyStore( 
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetPropertyStore( 
            flags,
            riid,
            ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getPropertyDescriptionList( 
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetPropertyDescriptionList( 
            keyType,
            riid,
            ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT getAttributes( 
            /* [in] */ SIATTRIBFLAGS attribFlags,
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetAttributes( 
            attribFlags,
            sfgaoMask,
            psfgaoAttribs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  SFGAOF getAttributes( 
            /* [in] */ SIATTRIBFLAGS attribFlags,
            /* [in] */ SFGAOF sfgaoMask)
  {
    SFGAOF sfgaoAttribs;
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetAttributes( 
            attribFlags,
            sfgaoMask,
            &sfgaoAttribs);
    if (FAILED(hr)) {
      throw hr;
    }
    return sfgaoAttribs;
  }
        

public:
  HRESULT  getCount( 
            /* [out] */ DWORD *pdwNumItems)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray ->  GetCount( 
            pdwNumItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  DWORD  getCount()
  {
    DWORD dwNumItems;
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray ->  GetCount( 
            &dwNumItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return dwNumItems;
  }
        

public:
  HRESULT getItemAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IShellItem **ppsi)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetItemAt( 
            dwIndex,
            ppsi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  IShellItem* getItemAt( 
            /* [in] */ DWORD dwIndex)
  {
    IShellItem *psi = NULL;
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> GetItemAt( 
            dwIndex,
            &psi);
    if (FAILED(hr)) {
      throw hr;
    }
    return psi;
  }
        

public:
  HRESULT enumItems( 
            /* [out] */ IEnumShellItems **ppenumShellItems)
  {
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> EnumItems( 
        ppenumShellItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  IEnumShellItems* enumItems()
  {
    IEnumShellItems *penumShellItems = NULL;
    IShellItemArray* pArray = getArray();
    HRESULT hr = pArray -> EnumItems( 
        &penumShellItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return penumShellItems;
  }
    
};

}
