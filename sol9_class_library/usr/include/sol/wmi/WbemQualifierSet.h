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
 *  WbemQualifierSet.h
 *
 *****************************************************************************/

// 2012/10/13

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

class WbemQualifierSet: public ComIUnknown {

public:
  WbemQualifierSet(IUnknown* classObject=NULL)
  :ComIUnknown(classObject)
  {

  }      

public:
  ~WbemQualifierSet()
  {
  }

public:
  IWbemQualifierSet* getQualifierSet()
  {
    return (IWbemQualifierSet*)getIUnknown();
  }

public:
  HRESULT get( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __out VARIANT *pVal,
            __out long *plFlavor)
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> Get( 
                wszName,
                lFlags,
                   pVal,
                plFlavor)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  HRESULT put( 
            __in LPCWSTR wszName,
            __in VARIANT *pVal,
            __in long lFlavor)
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> Put( 
          wszName,
          pVal,
          lFlavor
          ) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }       
  }

public:
  HRESULT remove( 
            __in LPCWSTR wszName)
  {  
    HRESULT hr = S_OK;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> Delete( 
                wszName)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  SAFEARRAY* getNames( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    SAFEARRAY *pNames = NULL;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> GetNames( 
      lFlags,
      &pNames) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNames;
    }
  }


public:
  HRESULT beginEnumeration( 
            __in long lEnumFlags)
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> BeginEnumeration( 
                lEnumFlags) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT next( 
            __in long lFlags,
          __out BSTR *strName,
          __out VARIANT *pVal,
          __out long *plFlavor)
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> Next( 
                lFlags,
                strName,
                pVal,
                plFlavor) )) {
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
    IWbemQualifierSet* set = getQualifierSet();
    if (FAILED(hr = set -> EndEnumeration() )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }


};

}
