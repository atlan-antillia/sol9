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
 *  UnsecuredApartment.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#define _WIN32_DCOM

#include <sol\Object.h>
#include <wbemidl.h>

namespace SOL {

class UnsecuredApartment :public Object {

private:
  // Use an unsecured apartment for security
    IUnsecuredApartment* apartment;
private:
  IUnknown* stubUnknown;

public:
  /**
   * Constructor
   */
  UnsecuredApartment()
    :apartment(NULL),
    stubUnknown(NULL)
  {
    HRESULT hr;
    if (FAILED(hr = CoCreateInstance(CLSID_UnsecuredApartment, NULL, 
      CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, 
      (void**)&apartment))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    
  }

public:
  /**
   * Destructor
   */
  ~UnsecuredApartment()
  {
    if (apartment) {
      apartment->Release();
      apartment = NULL;
    }
    
    if (stubUnknown) {
      stubUnknown->Release();
      stubUnknown = NULL;
    }
  }

public:
  /**
   * Create an instance of stubObject of IWbemObjectSink.
   * Usage:
   *  WbemObjectSink* pSink = new WbemObjectSink;
   *  IWebObjectSink* pStubSink = NULL;  
   *  unsecApartment->createStubSink(pSink, &pStubSink);
   *  //Pass this a method of WebServices class.
   */
  HRESULT createStubSink(/*[in]*/IWbemObjectSink* pSink,
          /*[out]*/ IWbemObjectSink** ppStubSink)
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = apartment->CreateObjectStub(pSink, &stubUnknown))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    
    hr = stubUnknown->QueryInterface(IID_IWbemObjectSink,
      (void **)ppStubSink);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
};

}
