/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WbemClassObjectEnumerator.h
 *
 *****************************************************************************/

// 2010/02/14
//
// 2010/05/10 Modified getEnumerator() method.
// 2012/10/14 Added next() method.

#pragma once

#include <sol/com/ComIUnknown.h>
#include <objbase.h>

#include <sol/COMTypeConverter.h>

#include <sol/Writer.h>
#include <sol/FileWriter.h>
#include <sol/ConsoleWriter.h>

#include <sol/LocalDateTime.h>
#include <sol/HTMLEncoder.h>

#pragma comment(lib, "oleaut32.lib")


namespace SOL {

class WbemClassObjectEnumerator :public ComIUnknown {

public:
  WbemClassObjectEnumerator(IUnknown* enumerator=NULL)
  :ComIUnknown(enumerator)
  {

  }

public:
  ~WbemClassObjectEnumerator () 
  {
  }

public:
  IEnumWbemClassObject* getEnumerator()
  {
    //2010/05/10
    return (IEnumWbemClassObject*)getIUnknown();
  }

public:
  HRESULT reset()
  {
    HRESULT hr = S_OK;

    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator -> Reset() )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemClassObject* next( 
              __in long lTimeout,
              __in ULONG uCount,
              __out ULONG *puReturned)
  {
    HRESULT hr = S_OK;
    IWbemClassObject *apObjects = NULL;
    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator -> Next( 
                lTimeout,
                uCount,
                &apObjects,
                puReturned) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return apObjects;
    }
  }

public:
  // 2012/10/13
  IWbemClassObject* next()
  {
    long lTimeout = WBEM_INFINITE;
    ULONG uCount = 1;
    ULONG returned = 0;
    HRESULT hr = S_OK;
    IWbemClassObject *apObjects = NULL;
    IEnumWbemClassObject* enumerator = getEnumerator();
    hr = enumerator -> Next( 
                lTimeout,
                uCount,
                &apObjects,
                &returned);
    if (FAILED(hr) || returned == 0) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return apObjects;
    }
  }

public:
  HRESULT next( 
              __in long lTimeout,
              __in ULONG uCount,
              __out IWbemClassObject **apObjects,
              __out ULONG *puReturned)
  {
    HRESULT hr = S_OK;
    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator -> Next( 
                lTimeout,
                uCount,
                apObjects,
                puReturned) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:        
  HRESULT nextAsync( 
              __in ULONG uCount,
             __in IWbemObjectSink *pSink)
  {    
    HRESULT hr = S_OK;

    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator -> NextAsync( 
      uCount,
      pSink) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IEnumWbemClassObject* clone() 
  {
    HRESULT hr = S_OK;

    IEnumWbemClassObject *pEnum = NULL;
    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator -> Clone( 
      &pEnum) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pEnum;
    }
  }        

public:
  HRESULT skip( 
            __in long lTimeout,
            __in ULONG nCount)
  {
    HRESULT hr = S_OK;

    IEnumWbemClassObject* enumerator = getEnumerator();
    if (FAILED(hr = enumerator ->Skip( 
      lTimeout,
      nCount)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }        
    
public:
  virtual void display()
  {
  }
};


}
