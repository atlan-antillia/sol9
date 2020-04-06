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
 *  WbemObjectStubSink.h
 *
 *****************************************************************************/


#pragma once

#define _WIN32_DCOM

#include <sol\Object.h>
#include <wbemidl.h>

namespace SOL {
/**
 * Simple wrapper class to create a stubSink object of IWbemObjectSink
 * from a sink object of IWbemObjectSink, by using IUnsecuredApartment interface.
 */
class WbemObjectStubSink :public Object {

private:
  IWbemObjectSink* pSink;

private:
  // Use an unsecured apartment for security
    IUnsecuredApartment* apartment;
private:
  IUnknown* stubUnknown;

private:
  IWbemObjectSink* stubSink;

public:
  /**
   * Constructor
   */
  WbemObjectStubSink(IWbemObjectSink* pSink)
    :apartment(NULL),
    stubUnknown(NULL),
    stubSink(NULL)
  {
    HRESULT hr;
    if (FAILED(hr = CoCreateInstance(CLSID_UnsecuredApartment, NULL, 
      CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, 
      (void**)&apartment))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    if (FAILED(hr = apartment->CreateObjectStub(pSink, &stubUnknown))) {
      apartment->Release();
      apartment = NULL;
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    if (FAILED(hr = stubUnknown->QueryInterface(IID_IWbemObjectSink,
      (void **)&stubSink))) {
      apartment->Release();
      apartment = NULL;
      stubUnknown->Release();
      stubUnknown = NULL;

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
  }

public:
  /**
   * Destructor
   */
  ~WbemObjectStubSink()
  {
    if (apartment) {
      apartment->Release();
      apartment = NULL;
    }
    
    if (stubUnknown) {
      stubUnknown->Release();
      stubUnknown = NULL;
    }
    if (stubSink) {
      stubSink->Release();
      stubSink = NULL;
    }
  }

public:
  IWbemObjectSink* getStubSink() {
    return stubSink;
  }
};

}
