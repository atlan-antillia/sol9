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
 *  NetFwProducts.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwProduct.h>


namespace SOL {

class NetFwProducts: public ComIDispatch {
    
public:
  NetFwProducts()
    :ComIDispatch()
  {
    createInstance();
  }

public:
  HRESULT createInstance()
  {
    INetFwProducts* pProducts = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(::NetFwProducts),
          NULL,
          CLSCTX_INPROC_SERVER,
          __uuidof(INetFwProducts),
          (void**)&pProducts);
    if (SUCCEEDED(hr)) {
      set(pProducts);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwProducts* getProducts()
  {
    return (INetFwProducts*) getIDispatch();
  }

public:
  HRESULT getCount( 
            /* [retval][out] */ long *count)
  {
    HRESULT hr = getProducts() -> get_Count( 
        count);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  long getCount()
  {
    long count = 0;
    HRESULT hr = getProducts() -> get_Count( 
        &count);
    if (FAILED(hr)) {
      throw hr;
    }
    return count;
  }

public:
  HRESULT regist( 
            /* [in] */ INetFwProduct *product,
            /* [retval][out] */ IUnknown **registration)
  {
    HRESULT hr = getProducts() -> Register( 
        product,
        registration);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IUnknown* regist( 
            /* [in] */ INetFwProduct *product)
  {
    IUnknown* pRegistration = NULL;

    HRESULT hr = getProducts() -> Register( 
        product,
        &pRegistration);
    if (FAILED(hr)) {
      throw hr;
    }
    return pRegistration;
  }

public:
  HRESULT item( 
            /* [in] */ long index,
            /* [retval][out] */ INetFwProduct **product)
  {
    HRESULT hr = getProducts() -> Item( 
        index,
        product);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  INetFwProduct* item( 
            /* [in] */ long index)
  {
    INetFwProduct* pProduct = NULL;

    HRESULT hr = getProducts() -> Item( 
        index,
        &pProduct);
    if (FAILED(hr)) {
      throw hr;
    }
    return pProduct;
  }

public:
  HRESULT getNewEnum( 
            /* [retval][out] */ IUnknown **newEnum)
  {
    HRESULT hr = getProducts() -> get__NewEnum( 
        newEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        
    
public:
  IUnknown* getNewEnum()
  {
    IUnknown* pNewEnum = NULL;
    HRESULT hr = getProducts() -> get__NewEnum( 
        &pNewEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return pNewEnum;
  }        

public:
  virtual void display(HWND hwnd=NULL)
  {
    long count = getCount();

    _tprintf(_T("<Products count='%d'>\n"), count);
    for (long i = 0; i<count; i++) {
      try {
        NetFwProduct product = item(i);
        product.display(hwnd);
      } catch (...) {
        break;
      }
    }
    _tprintf(_T("</Products>\n"));

  }
};

}

