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
 *  EnumVariant.h
 *
 *****************************************************************************/

// 2009/12/04
// 2012/09/03 Updated. Modified not to use 'FAILED' macro.
// 2012/09/15 Modified to call VariantClear in 'next' methods.

#pragma once

#include <sol/Object.h>
#include <objbase.h>
#include <sol/com/ComIUnknown.h>

#pragma comment(lib, "oleaut32.lib")


namespace SOL {

class EnumVariant :public ComIUnknown {

public:
  EnumVariant(IUnknown* pUnk=NULL)
  :ComIUnknown(pUnk)
  {
  }

public:
  ~EnumVariant() 
  {
  }

public:
  IEnumVARIANT* get()
  {
    return (IEnumVARIANT*)getIUnknown();
  }

public:
  EnumVariant& operator=(IEnumVARIANT* pEnum)
  { 
    set(pEnum);
    return *this;
  }

public:
  ULONG next( 
             __in  ULONG celt,
             __out VARIANT *rgVar)
  {
    IEnumVARIANT* pEnum = get();      
    ULONG celtFetched = 0;

    HRESULT  hr = pEnum -> Next( 
        celt,
        rgVar,
        &celtFetched);
    
    if (hr != S_OK) {
      throw Exception(hr, "%s: %s", "Error",__FUNCTION__);
    }
    return celtFetched;
  }

public:
  IDispatch* next() 
   {
    IDispatch *pDisp = NULL;
    IEnumVARIANT* pEnum = get();

    VARIANT var;
    VariantInit(&var);
    ULONG celt = 1;
    ULONG celtFetched = 0;

    HRESULT  hr = pEnum -> Next( 
        celt,
        &var,
        &celtFetched);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    //Check Variant type
    if (var.vt==VT_DISPATCH && celtFetched == 1) {
      //If vt were VT DISPATCH
      pDisp = V_DISPATCH(&var);
      pDisp->AddRef();
    } else {
      VariantClear(&var);
      throw E_POINTER;
    }
    VariantClear(&var);
    return pDisp;
  }

public:
  ULONG next(
             __in  ULONG celt,
             __out IDispatch **ppDisp)
  {
    IEnumVARIANT* pEnum = get();
    VARIANT var;
    VariantInit(&var);
    ULONG celtFetched = 0;
    HRESULT hr = pEnum-> Next( 
        celt,
        &var,
        &celtFetched);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }

    //Check Variant type
    if (var.vt == VT_DISPATCH && celtFetched > 0) {
      //If vt were VT DISPATCH
      *ppDisp = V_DISPATCH(&var);
      (*ppDisp) -> AddRef();
    } else {
      VariantClear(&var);
      throw Exception(0, "Not IDispatch: %s", __FUNCTION__);
    }
    VariantClear(&var);

    return celtFetched;
  }

public:
  HRESULT next( 
             __in  ULONG celt,
             __out VARIANT *rgVar,
            __out ULONG *pCeltFetched)
  {
    IEnumVARIANT* pEnum = get();

    HRESULT hr = pEnum -> Next( 
        celt,
        rgVar,
        pCeltFetched);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    return hr;
  }

public:
  //2012/09/03
  ULONG next( 
             __out IUnknown **ppIUnk)
  {
    VARIANT var;
    VariantInit(&var);
    ULONG celtFetched = 0;
    ULONG celt = 1;

    IEnumVARIANT* pEnum = get();
    HRESULT hr = pEnum -> Next( 
        celt,
        &var,
        &celtFetched);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }

    if (V_VT(&var) == VT_UNKNOWN) {
      *ppIUnk =V_UNKNOWN(&var);
    } else {
      throw Exception(0, "Not IUnknown: %s", __FUNCTION__);
    }

    return celtFetched;
  }

public:
  //2012/09/03
  IUnknown* nextIUnknown()
  {
    IUnknown *pIUnk = NULL;

    VARIANT var;
    VariantInit(&var);
    ULONG celt = 1;
    ULONG celtFetched = 0;

    IEnumVARIANT* pEnum = get();
    HRESULT hr = pEnum -> Next( 
        celt,
        &var,
        &celtFetched);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }

    if (V_VT(&var) == VT_UNKNOWN) {
      pIUnk =V_UNKNOWN(&var);
    } else {
      throw Exception(0, "Not IUnknown: %s", __FUNCTION__);
    }

    return pIUnk;
  }

public:
  HRESULT skip( 
             __in ULONG celt)
  {
    IEnumVARIANT* pEnum = get();
    HRESULT hr = pEnum-> Skip(celt);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    return hr;
  }
        

public:
  HRESULT reset()
  {
    IEnumVARIANT* pEnum = get();
    HRESULT hr = pEnum->Reset();
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    return hr;
  }
        

public:
  HRESULT clone( 
            __out IEnumVARIANT **ppEnum)        
  {
    IEnumVARIANT* pEnum = get();
    HRESULT hr = pEnum -> Clone(ppEnum);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    return hr;
  }

public:
  //2012/09/02
  IEnumVARIANT* clone()        
  {
    IEnumVARIANT* pEnum = get();
    IEnumVARIANT* pCloned = NULL;
  
    HRESULT hr = pEnum -> Clone(&pCloned);
    if (hr != S_OK) {
      throw Exception(hr, "Error: %s", __FUNCTION__);
    }
    return pCloned;
  }
};

}
