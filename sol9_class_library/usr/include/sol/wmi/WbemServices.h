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
 *  WbemServices.h
 *
 *****************************************************************************/

// 2010/03/14
// 2010/05/10 Modified the default value of the second paramete for execQuery( 
//   to be           ,
//            __in long lFlags=WBEM_FLAG_FORWARD_ONLY,  
//      
// 2012/03/08 Updated.

#pragma once

#include <sol/com/ComIUnknown.h>
#include <objbase.h>

#include <sol/COMTypeConverter.h>
#include <sol/Writer.h>
#include <sol/FileWriter.h>
#include <sol/ConsoleWriter.h>

#include <sol/LocalDateTime.h>
#include <sol/HTMLEncoder.h>

#include <wbemidl.h>
#include <wbemdisp.h>

#pragma comment(lib, "wbemuuid.lib")

#pragma comment(lib, "oleaut32.lib")


namespace SOL {

class WbemServices : public ComIUnknown {
private:
  // const BSTR strQueryLanguage;
  BSTR strQueryLanguage;
  
public:
  WbemServices(IWbemServices* services)
  :ComIUnknown(services),
  strQueryLanguage(L"WQL")
  {

  }      
  
public:
  ~WbemServices()
  {
  }
  

public:
  operator IWbemServices*()
  {
    return getServices();
  }

public:
  IWbemServices* getServices()
  {
    return (IWbemServices*)getIUnknown();
  }

public:
  HRESULT openNamespace( 
            __in const BSTR strNamespace,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __out IWbemServices **ppWorkingNamespace,
            __out IWbemCallResult **ppResult)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> OpenNamespace( 
        strNamespace,
        lFlags,
        pCtx,
        ppWorkingNamespace,
        ppResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  HRESULT cancelAsyncCall( 
            __in IWbemObjectSink *pSink)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> CancelAsyncCall( 
        pSink)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemObjectSink* queryObjectSink( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IWbemObjectSink *pResponseHandler = NULL;
    if (FAILED(hr = services -> QueryObjectSink( 
        lFlags,
        &pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pResponseHandler;
    }
  }

public:
  HRESULT getObject( 
            __in const BSTR strObjectPath,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __out IWbemClassObject **ppObject,
            __out IWbemCallResult **ppCallResult)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> GetObject( 
        strObjectPath,
        lFlags,
        pCtx,
        ppObject,
        ppCallResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }

  }

public:
  HRESULT getObjectAsync( 
            __in const BSTR strObjectPath,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> GetObjectAsync( 
        strObjectPath,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemCallResult* putClass( 
            __in IWbemClassObject *pObject,
            __in long lFlags,
            __in IWbemContext *pCtx)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IWbemCallResult *pCallResult = NULL;
    if (FAILED(hr = services -> PutClass( 
        pObject,
        lFlags,
        pCtx,
        &pCallResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pCallResult;
    }
  }


public:
  HRESULT putClassAsync( 
            __in IWbemClassObject *pObject,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> PutClassAsync( 
        pObject,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemCallResult* deleteClass( 
            __in const BSTR strClass,
            __in long lFlags,
            __in IWbemContext *pCtx)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IWbemCallResult *pCallResult = NULL;
    if (FAILED(hr = services -> DeleteClass( 
        strClass,
        lFlags,
        pCtx,
        &pCallResult)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pCallResult;
    }
  }

public:
  HRESULT deleteClassAsync( 
            __in const BSTR strClass,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> DeleteClassAsync( 
        strClass,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IEnumWbemClassObject* createClassEnum( 
            __in const BSTR strSuperclass,
            __in long lFlags,
            __in IWbemContext *pCtx
            )
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IEnumWbemClassObject *pEnum = NULL;
    if (FAILED(hr = services -> CreateClassEnum( 
        strSuperclass,
        lFlags,
        pCtx,
        &pEnum)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pEnum;
    }
  }

public:
  HRESULT createClassEnumAsync( 
            __in const BSTR strSuperclass,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> CreateClassEnumAsync( 
        strSuperclass,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemCallResult* putInstance( 
            __in IWbemClassObject *pInst,
            __in long lFlags,
            __in IWbemContext *pCtx)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IWbemCallResult *pCallResult = NULL;
    if (FAILED(hr = services -> PutInstance( 
        pInst,
        lFlags,
        pCtx,
        &pCallResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pCallResult;
    }
  }


public:
  HRESULT putInstanceAsync( 
            __in IWbemClassObject *pInst,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> PutInstanceAsync( 
        pInst,
        lFlags,
        pCtx,
        pResponseHandler)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemCallResult* deleteInstance( 
            __in const BSTR strObjectPath,
            __in long lFlags,
            __in IWbemContext *pCtx
            )
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IWbemCallResult *pCallResult = NULL;
    if (FAILED(hr = services -> DeleteInstance( 
        strObjectPath,
        lFlags,
        pCtx,
        &pCallResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pCallResult;
    }
  }

public:
  HRESULT deleteInstanceAsync( 
            __in const BSTR strObjectPath,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> DeleteInstanceAsync( 
        strObjectPath,
        lFlags,
        pCtx,
        pResponseHandler)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IEnumWbemClassObject* createInstanceEnum( 
            __in const BSTR strFilter,
            __in long lFlags,
            __in IWbemContext *pCtx
            )
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    IEnumWbemClassObject *pEnum = NULL;
    if (FAILED(hr = services -> CreateInstanceEnum( 
        strFilter,
        lFlags,
        pCtx,
        &pEnum)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pEnum;
    }
  }

public:
  HRESULT createInstanceEnumAsync( 
            __in const BSTR strFilter,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> CreateInstanceEnumAsync( 
        strFilter,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
public:
  IEnumWbemClassObject* execQuery( 
            __in const BSTR strQuery,
            __in long lFlags=WBEM_FLAG_FORWARD_ONLY,  //2010/05/10 |WBEM_FLAG_RETURN_IMMEDIATELY,
            __in IWbemContext *pCtx=NULL)
       
  {
    HRESULT hr = S_OK;
    IEnumWbemClassObject *pEnum = NULL;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecQuery( 
        this->strQueryLanguage,
        strQuery,
        lFlags,
        pCtx,
        &pEnum)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pEnum;
    }
  }


public:
  HRESULT execQueryAsync( 
            __in const BSTR strQuery,
      __in IWbemObjectSink *pResponseHandler,
      __in long lFlags = WBEM_FLAG_BIDIRECTIONAL,
            __in IWbemContext *pCtx =NULL)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecQueryAsync( 
        this->strQueryLanguage,
        strQuery,
        lFlags,
        pCtx,
        pResponseHandler)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  //wbemFlagForwardOnly|wbemFlagReturnImmediately,
  IEnumWbemClassObject* execNotificationQuery( 
            __in const BSTR strQuery,
            __in long lFlags=WBEM_FLAG_FORWARD_ONLY|WBEM_FLAG_RETURN_IMMEDIATELY,
            __in IWbemContext *pCtx = NULL)
  {
    HRESULT hr = S_OK;
    IEnumWbemClassObject *pEnum = NULL;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecNotificationQuery( 
        this->strQueryLanguage,
        strQuery,
        lFlags,
        pCtx,
        &pEnum)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pEnum;
    }
  }


public:
  HRESULT execNotificationQueryAsync( 
            __in const BSTR strQuery,
            __in IWbemObjectSink *pResponseHandler,
      __in long lFlags = WBEM_FLAG_SEND_STATUS,
            __in IWbemContext *pCtx = NULL)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecNotificationQueryAsync( 
        this->strQueryLanguage,
        strQuery,
        lFlags,
        pCtx,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  HRESULT execMethod( 
            __in const BSTR strObjectPath,
            __in const BSTR strMethodName,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemClassObject *pInParams,
            __out IWbemClassObject **ppOutParams,
            __out IWbemCallResult **ppCallResult)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecMethod( 
        strObjectPath,
        strMethodName,
        lFlags,
        pCtx,
        pInParams,
        ppOutParams,
        ppCallResult)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  HRESULT execMethodAsync( 
            __in const BSTR strObjectPath,
            __in const BSTR strMethodName,
            __in long lFlags,
            __in IWbemContext *pCtx,
            __in IWbemClassObject *pInParams,
            __in IWbemObjectSink *pResponseHandler)
  {
    HRESULT hr = S_OK;
    IWbemServices* services = getServices();
    if (FAILED(hr = services -> ExecMethodAsync( 
        strObjectPath,
        strMethodName,
        lFlags,
        pCtx,
        pInParams,
        pResponseHandler)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

};
    
}
