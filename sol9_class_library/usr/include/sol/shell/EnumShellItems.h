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
 *  EnumShellItems.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class EnumShellItems: public ComIUnknown {

public:
  EnumShellItems(IEnumShellItems* pItems)
    :ComIUnknown(pItems)
  {
  }

public:
  IEnumShellItems* getItems()
  {
    return (IEnumShellItems*)getIUnknown();
  }


public:
  HRESULT next( 
            /* [in] */ ULONG celt,
            /* [out] */ IShellItem **rgelt,
            /* [out] */ ULONG *pceltFetched)
  {
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Next(celt,
          rgelt,
          pceltFetched);

    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItem * next()
  {
    ULONG celt = 1;
    IShellItem * pItem = NULL;
    ULONG celtFetched = 0;
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Next(celt,
          &pItemt,
          &celtFetched);

    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT skip( 
            /* [in] */ ULONG celt)
  {
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Skip(celt);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT reset()
  {
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Reset();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
    
        
public:
  HRESULT Clone( 
            /* [out] */ IEnumShellItems **ppenum) 
  {
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Clone( 
        ppenum) ;

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IEnumShellItems* clone() 
  {
    IEnumShellItems* penum = NULL;
    IEnumShellItems* pItems = getItems();
    HRESULT hr = pItems -> Clone( 
        &penum) ;

    if (FAILED(hr)) {
      throw hr;
    }
    return penum;
  }
        
    
};

}

