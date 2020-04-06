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
 *  WbemContext.h
 *
 *****************************************************************************/

// 2010/02/14
// 2012/03/08 Updated

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

class WbemContext : public ComIUnknown {

public:
  WbemContext(IUnknown* context=NULL)
  :ComIUnknown(context)
  {

  }

public:
  ~WbemContext () 
  {
  }

public:
  IWbemContext* getContext()
  {
    return (IWbemContext*)getContext();
  }

public:
  IWbemContext* clone()
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    IWbemContext *pNewCopy = NULL;
    if (FAILED(hr = context ->  Clone( 
      &pNewCopy)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNewCopy;
    }       
  }        
/*
public:    
  HRESULT clone( 
            __out IWbemContext **ppNewCopy)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context ->  Clone( 
      ppNewCopy)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
*/

public:
  SAFEARRAY* getNames( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    SAFEARRAY *pNames = NULL;
    if (FAILED(hr = context -> GetNames( 
      lFlags,
      &pNames)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNames;
    }       
  }
/*
public:
  HRESULT getNames( 
            __in long lFlags,
            __out SAFEARRAY **pNames)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> GetNames( 
      lFlags,
      pNames)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
*/        
        
public:
  HRESULT beginEnumeration( 
            __in long lFlags) 
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> BeginEnumeration( 
      lFlags)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
        
        
public:
  HRESULT next( 
            __in long lFlags,
            __out BSTR *pstrName,
            __out VARIANT *pValue)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> Next( 
      lFlags,
      pstrName,
      pValue)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
        
public:
  HRESULT endEnumeration()
   {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> EndEnumeration()   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
       
        
public:
  HRESULT setValue( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __in VARIANT *pValue)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> SetValue( 
      wszName,
      lFlags,
      pValue)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
        
        
public:
  HRESULT getValue( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __out VARIANT *pValue)
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> GetValue( 
      wszName,
      lFlags,
      pValue)    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
        
public:
  HRESULT deleteValue( 
            __in LPCWSTR wszName,
            __in long lFlags) 
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> DeleteValue( 
                wszName,
      lFlags)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }
        
        
public:
  HRESULT deleteAll() 
  {
    HRESULT hr = S_OK;
    IWbemContext* context = getContext();
    if (FAILED(hr = context -> DeleteAll()    )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }        
  }
    
};

}
