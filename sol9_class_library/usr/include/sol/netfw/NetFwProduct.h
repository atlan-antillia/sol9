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
 *  NetFwProduct.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>

namespace SOL {

class NetFwProduct: public ComIDispatch {
    
public:
  NetFwProduct(INetFwProduct* pProduct=NULL)
    :ComIDispatch(pProduct)
  {
    if (pProduct==NULL) {
      createInstance();
    }
  }

public:
  HRESULT createInstance()
  {
    INetFwProduct* pProduct = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(::NetFwProduct),
          NULL,
          CLSCTX_INPROC_SERVER,
          __uuidof(INetFwProduct),
          (void**)&pProduct);
    if (SUCCEEDED(hr)) {
      set(pProduct);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwProduct* getProduct()
  {
    return (INetFwProduct*) getIDispatch();
  }

public:
  operator INetFwProduct*()
  {
    return (INetFwProduct*) getIDispatch();
  }

public:
  HRESULT getRuleCategories( 
            /* [retval][out] */ VARIANT *ruleCategories)
  {
    HRESULT hr = getProduct() -> get_RuleCategories( 
        ruleCategories);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _variant_t getRuleCategories()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getProduct() -> get_RuleCategories( 
        &var);
    if (FAILED(hr)) {
      throw hr;
    }
    return _variant_t(var, false);
  }

public:
  HRESULT putRuleCategories( 
            /* [in] */ VARIANT ruleCategories)
  {
    HRESULT hr = getProduct() -> put_RuleCategories( 
        ruleCategories);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getDisplayName( 
            /* [retval][out] */ BSTR *displayName)
  {
    HRESULT hr = getProduct() -> get_DisplayName( 
        displayName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getDisplayName()
  {
    BSTR name = NULL;
    HRESULT hr = getProduct() -> get_DisplayName( 
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }


public:
  HRESULT putDisplayName( 
            /* [in] */ BSTR displayName)
  {
    HRESULT hr = getProduct() -> put_DisplayName( 
        displayName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getPathToSignedProductExe( 
            /* [retval][out] */ BSTR *path)
  {
    HRESULT hr = getProduct() -> get_PathToSignedProductExe( 
        path);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getPathToSignedProductExe()
  {
    BSTR path = NULL;
    HRESULT hr = getProduct() -> get_PathToSignedProductExe( 
        &path);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(path, false);
  }    

public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("<Product>\n_"));

    _variant_t cat = getRuleCategories();
    _tprintf(_T("<DisplayName>%s</DisplayName>\n"), (const TCHAR*)getDisplayName() );
    _tprintf(_T("<PathToSignedProductExe>%s</PathToSignedProductExe>\n"), (const TCHAR*)getPathToSignedProductExe() );
    _tprintf(_T("</Product>\n_"));

  }

};

}
