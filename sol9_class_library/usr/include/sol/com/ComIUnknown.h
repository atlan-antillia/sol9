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
 *  ComIUnknown.h
 *
 *****************************************************************************/

// 2009/12/04
// 2010/04/01

#pragma once

#include <sol/Object.h>
#include <objbase.h>
#include <sol/Exception.h>

#include <sol/COMTypeConverter.h>

//2010/04/01
#include <sol/BString.h>

#pragma comment(lib, "ole32.lib" )    //2012/09/12
#pragma comment(lib, "oleaut32.lib")

namespace SOL {

class ComIUnknown :public Object {

private:
  IUnknown* pUnknown;

public:
  ComIUnknown(IUnknown* pUnk=NULL)
  :pUnknown(pUnk)
  {

  }

public:
  ~ComIUnknown() 
  {
    clear();
  }


public:
  ULONG addRef()
  {
    ULONG ref = 0;
    if (pUnknown) {
      ref = pUnknown->AddRef();
    }
    return ref;
  }

public:
  ULONG release()
  {
    ULONG ref = 0;
    if (pUnknown) {
      ref =pUnknown->Release();
    }
    return ref;
  }

public:
  void clear()
  {
    if (pUnknown) {
      pUnknown->Release();
      pUnknown = NULL;
    }
  }

public:
  HRESULT queryInterface(REFIID riid, void **ppvObject)
  {
    //2012/09/15 return pUnk->QueryInterface(riid, ppvObject);
    HRESULT hr = getIUnknown() -> QueryInterface(riid, ppvObject);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IDispatch* queryInterface(REFIID riid)
  {
    IDispatch* pObject = NULL;
    HRESULT hr = queryInterface(riid, (void**)&pObject);
    if (FAILED(hr)) {
      throw hr;
    }
    return pObject;
  }

public:
  // 2012/09/15
  IEnumVARIANT* getEnumVariant()
  {
    IEnumVARIANT* pEnum = NULL;
    HRESULT hr = queryInterface(__uuidof(IEnumVARIANT),
                                       (void**)&pEnum);
    if (FAILED(hr)) {
      throw hr;
    }        
    return pEnum;
  }

public:
  virtual void display()
  {
    printf("ComIUnknown::display\n");
  }


public:
  void set(IUnknown* pUnk)
  {
    pUnknown = pUnk;
  }

public:
  IUnknown* getIUnknown()
  {
    if (pUnknown == NULL) {
      throw E_POINTER;
    //return NULL;
    } else {
      return pUnknown;
    }
  }

public:
  operator IUnknown*() {
    return getIUnknown();
  }

public:
  //2009/12/21
  bool toBool(VARIANT_BOOL varBool)
  {
    bool rc = false;
    if (varBool == VARIANT_TRUE) {
      rc = true;
    }
    return rc;
  }

public:
  //2009/12/21
  VARIANT_BOOL toVariantBool(bool bBool)
  {
    VARIANT_BOOL rc = VARIANT_FALSE;
    if (bBool == true) {
      rc = VARIANT_TRUE;
    }
    return rc;
  }

public:
  void writeln(_variant_t& var)
  {
    COMTypeConverter converter;
    _bstr_t string;
    if (converter.toString(var, string)) {
      _tprintf(_T("%s\n"), (const TCHAR*)string);
    }
  }

public:
  bool toString(_variant_t var, _bstr_t& string)
  {
    COMTypeConverter converter;
    return converter.toString(var, string);
  }

public:
  //2012/09/12
  _bstr_t toString(_variant_t var)
  {
    COMTypeConverter converter;
    return converter.toString(var);
  }

public:
  void release(IUnknown* unknown)
  {
    if (unknown) {
      unknown->Release();
    }
  }
};

}
