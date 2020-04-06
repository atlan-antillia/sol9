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
 *  WbemCallResult.h
 *
 *****************************************************************************/

// 2010/02/14

#pragma once

#include <sol/com/ComIUnknown.h>
#include <objbase.h>

#include <sol/COMTypeConverter.h>
#include <sol/Writer.h>
#include <sol/FileWriter.h>
#include <sol/ConsoleWriter.h>

#include <sol/LocalDateTime.h>
#include <sol/HTMLEncoder.h>

//2010/05/09
#include <wbemidl.h>
#include <wbemdisp.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "oleaut32.lib")


namespace SOL {

class WbemCallResult :public ComIUnknown {

public:
  WbemCallResult(IUnknown* callResult=NULL)
  :ComIUnknown(callResult)
  {

  }      

public:
  ~WbemCallResult()
  {
  }

public:
  IWbemCallResult* getCallResult()
  {
    return (IWbemCallResult*)getCallResult();
  }

public:
  IWbemClassObject* getResultObject( 
            __in long lTimeout)
  {
    HRESULT hr = S_OK;
    IWbemCallResult* callResult = getCallResult();
    IWbemClassObject *pResultObject =NULL;
    if (FAILED(hr = callResult -> GetResultObject( 
        lTimeout,
        &pResultObject)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pResultObject;
    }
  }


public:
  _bstr_t getResultString( 
            __in long lTimeout)
  {
    HRESULT hr = S_OK;
    IWbemCallResult* callResult = getCallResult();
    BSTR strResultString = NULL;
    if (FAILED(hr = callResult -> GetResultString( 
        lTimeout,
        &strResultString)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return _bstr_t(strResultString, false);
    }
  }


public:
  IWbemServices* getResultServices( 
            __in long lTimeout)
  {
    HRESULT hr = S_OK;
    IWbemCallResult* callResult = getCallResult();
    IWbemServices *pServices = NULL;
    if (FAILED(hr = callResult -> GetResultServices( 
        lTimeout,
        &pServices)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pServices;
    }
  }


public:
  long getCallStatus( 
            __in long lTimeout)  
  {
    HRESULT hr = S_OK;
    IWbemCallResult* callResult = getCallResult();
    long lStatus = 0;
    if (FAILED(hr = callResult -> GetCallStatus( 
        lTimeout,
        &lStatus)     )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return lStatus;
    }
  }

};

}
