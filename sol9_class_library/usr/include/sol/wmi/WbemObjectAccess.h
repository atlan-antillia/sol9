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
 *  WbemObjectAccess.h
 *
 *****************************************************************************/

// 2010/02/14

#pragma once

#include <sol/wmi/WbemClassObject.h>

#pragma comment(lib, "oleaut32.lib")

namespace SOL {

class WbemObjectAccess : public WbemClassObject {
  
public:
  WbemObjectAccess(IWbemObjectAccess* objectAccess=NULL)
  :WbemClassObject(objectAccess)
  {

  }      

public:
  ~WbemObjectAccess()
  {
  }

public:
  IWbemObjectAccess* getObjectAccess()
  {
    return (IWbemObjectAccess*)getObjectAccess();
  }

public:
        
  HRESULT getPropertyHandle( 
            __in LPCWSTR wszPropertyName,
            __out CIMTYPE *pType,
            __out long *plHandle)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> GetPropertyHandle( 
        wszPropertyName,
        pType,
        plHandle)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        


public:        
        
  HRESULT writePropertyValue( 
            __in long lHandle,
            __in long lNumBytes,
            __in const byte *aData)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> WritePropertyValue( 
            lHandle,
            lNumBytes,
            aData)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        

public:        
  HRESULT readPropertyValue( 
            __in long lHandle,
            __in long lBufferSize,
            __out long *plNumBytes,
            __out byte *aData)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> ReadPropertyValue( 
        lHandle,
        lBufferSize,
        plNumBytes,
        aData)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
        
        
public:        
  HRESULT readDWORD( 
            __in long lHandle,
            __out DWORD *pdw)
   {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> ReadDWORD( 
        lHandle,
        pdw)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
       
        
public:        
  HRESULT writeDWORD( 
            __in long lHandle,
            __in DWORD dw) 
   {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> WriteDWORD( 
        lHandle,
        dw)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
        
public:        
  HRESULT readQWORD( 
            __in long lHandle,
            __out unsigned __int64 *pqw)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> ReadQWORD( 
        lHandle,
        pqw)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
        
public:        
        
  HRESULT writeQWORD( 
            __in long lHandle,
            __in unsigned __int64 pw)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> WriteQWORD( 
            lHandle,
            pw)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
        
        
public:        
  HRESULT getPropertyInfoByHandle( 
            __in long lHandle,
            __out BSTR *pstrName,
            __out CIMTYPE *pType)
   {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> GetPropertyInfoByHandle( 
        lHandle,
        pstrName,
        pType)      )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
       
public:        
  HRESULT lock( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> Lock( 
        lFlags)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:        
    //2012/03/08
  HRESULT unlock( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemObjectAccess* objectAccess = getObjectAccess();
    if (FAILED(hr = objectAccess -> Unlock( 
        lFlags)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
    
};

}
