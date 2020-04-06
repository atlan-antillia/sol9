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
 *  ServiceProvider.h
 *
 *****************************************************************************/

//2012/11/10

#pragma once

#include <sol/com/ComIUnknown.h>
#include <comutil.h>
#include <objbase.h>

namespace SOL {

class ServiceProvider :public ComIUnknown {

public:
  ServiceProvider(IServiceProvider* pProvider)
  :ComIUnknown(pProvider)
  {  
  }

public:
  IServiceProvider* getProvider()
  {
    return (IServiceProvider*)getIUnknown();
  }

public:
  HRESULT queryService(
      /* [in] */ REFGUID guidService,
      /* [in] */ REFIID riid,
      /* [out] */ void *ppvObject))
  {
    IServiceProvider* pProvider = getProvider();

        HRESULT hr = pProvider = QueryService(guidService, riid, 
        ppvObject);
    if (FAILED(hr)) {
      throw hr;
    }    
    return hr;
  }

public:
  void** queryService(
      /* [in] */ REFGUID guidService)
  {
    Guid riid = IID_IUnknown;
    void* pvObject = NULL;
    IServiceProivder* pProvider = getProvider();

        HRESULT hr = pProvider = QueryService(guidService, riid, 
        &pvObject);
    if (FAILED(hr)) {
      throw hr;
    }    
    return pvObject;
  }
};

}
