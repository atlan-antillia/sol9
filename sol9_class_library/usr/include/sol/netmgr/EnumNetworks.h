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
 *  EnumNetworks.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once
#include <sol\com\ComIDispatch.h>
#include <netlistmgr.h>

namespace SOL {

class EnumNetworks: public ComIDispatch {

public:
  EnumNetworks(IEnumNetworks* pNetworks)
    :ComIDispatch(pNetworks)
  {
  }

private:
  IEnumNetworks* getNetworks()
  {
    return (IEnumNetworks*) getIDispatch();
  }

public:

  HRESULT getNewEnum( 
            /* [retval][out] */ IEnumVARIANT **ppEnumVar)
  {
    HRESULT hr = getNetworks() -> get__NewEnum( 
      ppEnumVar);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  IEnumVARIANT* getNewEnum()
  {
    IEnumVARIANT* pEnum = NULL;
    HRESULT hr = getNetworks() -> get__NewEnum( 
      &pEnum);

    if (FAILED(hr)) {
      throw hr;
    }
    return pEnum;
  }

  HRESULT next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ INetwork **rgelt,
            /* [full][out][in] */ ULONG *pceltFetched)
  {
    HRESULT hr = getNetworks() -> Next( 
        celt,
        rgelt,
        pceltFetched);
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        
  INetwork* next()
  {
    ULONG celt = 1;
    INetwork* pNetwork = NULL;
    ULONG celtFetched = 0;

    HRESULT hr = getNetworks() -> Next( 
        celt,
        &pNetwork,
        &celtFetched);
    if (hr != S_OK) {
      throw hr;
    }
    return pNetwork;
  }

  HRESULT skip( 
            /* [in] */ ULONG celt)
  {
    HRESULT hr = getNetworks() -> Skip( 
            celt);
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT reset()
  {
    HRESULT hr = getNetworks() -> Reset();
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT clone( 
            /* [retval][out] */ IEnumNetworks **ppEnumNetwork)
  {
    HRESULT hr = getNetworks() -> Clone( 
      ppEnumNetwork);

    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        
  IEnumNetworks* clone()
  {
    IEnumNetworks* pEnumNetwork = NULL;
    HRESULT hr = getNetworks() -> Clone( 
      &pEnumNetwork);

    if (hr != S_OK) {
      throw hr;
    }
    return pEnumNetwork;
  }
    
};
    
}
