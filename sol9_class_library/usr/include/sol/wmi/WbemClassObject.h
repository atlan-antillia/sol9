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
 *  WbemClassObject.h
 *
 *****************************************************************************/

// 2010/02/14
// 2012/03/08 Updated.
// 2012/10/22 Updated.

#pragma once

#include <sol/com/ComIUnknown.h>
#include <objbase.h>

#include <sol/COMTypeConverter.h>
#include <sol/Writer.h>
#include <sol/FileWriter.h>
#include <sol/ConsoleWriter.h>

#include <sol/LocalDateTime.h>
#include <sol/HTMLEncoder.h>

//2012/10/22
#include <sol/SafeArray.h>

//2010/05/09
#include <wbemidl.h>
#include <wbemdisp.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "oleaut32.lib")


namespace SOL {

class WbemClassObject : public ComIUnknown {

public:
  WbemClassObject(IUnknown* classObject=NULL)
  :ComIUnknown(classObject)
  {

  }      

public:
  ~WbemClassObject()
  {
  }

public:
  IWbemClassObject* getClassObject()
  {
    return (IWbemClassObject*)getIUnknown();
  }

public:    
  IWbemQualifierSet* getQualifierSet()
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet *pQualSet = NULL;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetQualifierSet( 
                &pQualSet)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pQualSet;
    }
  }
/*
public:
  HRESULT getQualifierSet( 
            __out IWbemQualifierSet **ppQualSet)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetQualifierSet( 
                ppQualSet)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
*/

public:
  HRESULT get( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __out VARIANT *pVal,
            __out CIMTYPE *pType,
            __out long *plFlavor)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Get( 
                wszName,
                lFlags,
                   pVal,
                pType,
                plFlavor)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  _variant_t get( 
            __in LPCWSTR wszName,
            __in long lFlags=0)
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Get( 
                wszName,
                lFlags,
                   &var,
          NULL,
                NULL)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return _variant_t(var, false);
    }
  }

public:

  HRESULT put( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __in VARIANT *pVal,
            __in CIMTYPE type) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Put( 
                wszName,
                lFlags,
                pVal,
                type)   )) {
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
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Delete( 
                wszName)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  SAFEARRAY* getNames( 
            __in LPCWSTR wszQualifierName,
            __in long lFlags,
            __in VARIANT *pQualifierVal)
  {
    HRESULT hr = S_OK;
    SAFEARRAY *pNames = NULL;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetNames( 
      wszQualifierName,
      lFlags,
      pQualifierVal,
      &pNames) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNames;
    }
  }

public:
  //2012/10/22
  SAFEARRAY* getNames( 
            __in long lFlags=WBEM_FLAG_ALWAYS|WBEM_MASK_CONDITION_ORIGIN)
  {
    HRESULT hr = S_OK;
    LPCWSTR wszQualifierName = NULL;
    VARIANT *pQualifierVal = NULL;

    SAFEARRAY *pNames = NULL;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetNames( 
      wszQualifierName,
      lFlags,
      pQualifierVal,
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
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> BeginEnumeration( 
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
          __out CIMTYPE *pType,
          __out long *plFlavor)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Next( 
                lFlags,
                strName,
                pVal,
                pType,
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
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> EndEnumeration() )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemQualifierSet* getPropertyQualifierSet( 
            __in LPCWSTR wszProperty)
  {
    HRESULT hr = S_OK;
    IWbemQualifierSet *pQualSet = NULL;

    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetPropertyQualifierSet( 
                wszProperty,
                &pQualSet)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pQualSet;
    }
  }


public:
  IWbemClassObject* clone()
  {
    HRESULT hr = S_OK;
    IWbemClassObject *pCopy = NULL;

    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> Clone( 
                &pCopy)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pCopy;
    }
  }        


public:
  /* 
  This returns a text expression of the object in Managed Object Format (MOF) syntax.
   */
  _bstr_t getObjectText( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    BSTR strObjectText = NULL;
    if (FAILED(hr = classObject -> GetObjectText( 
                lFlags,
                &strObjectText)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return _bstr_t(strObjectText, false);
    }
  }


public:
  IWbemClassObject* spawnDerivedClass( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemClassObject *pNewClass = NULL;

    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> SpawnDerivedClass( 
                lFlags,
                &pNewClass)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNewClass;
    }
  }

public:
  IWbemClassObject* spawnInstance( 
            __in long lFlags)
  {
    HRESULT hr = S_OK;
    IWbemClassObject *pNewInstance = NULL;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> SpawnInstance( 
                lFlags,
                &pNewInstance)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pNewInstance;
    }
  }

        
public:
  HRESULT compareTo( 
            __in long lFlags,
            __in IWbemClassObject *pCompareTo)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> CompareTo( 
                lFlags,
                pCompareTo)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  _bstr_t getPropertyOrigin( 
            __in LPCWSTR wszName) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    BSTR strClassName = NULL;
    if (FAILED(hr = classObject -> GetPropertyOrigin( 
                wszName,
                &strClassName)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return _bstr_t(strClassName, false);
    }
  }
        
public:
  HRESULT inheritsFrom( 
            __in LPCWSTR strAncestor)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> InheritsFrom( 
                strAncestor)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  HRESULT getMethod( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __out IWbemClassObject **ppInSignature,
            __out IWbemClassObject **ppOutSignature)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> GetMethod( 
                wszName,
                lFlags,
                ppInSignature,
                ppOutSignature) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT putMethod( 
            __in LPCWSTR wszName,
            __in long lFlags,
            __in IWbemClassObject *pInSignature,
            __in IWbemClassObject *pOutSignature) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> PutMethod( 
                wszName,
               lFlags,
                pInSignature,
                pOutSignature) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT deleteMethod( 
            __in LPCWSTR wszName) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> DeleteMethod( 
                wszName)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT beginMethodEnumeration( 
            __in long lEnumFlags) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> BeginMethodEnumeration( 
                lEnumFlags)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT nextMethod( 
            __in long lFlags,
            __out BSTR *pstrName,
            __out IWbemClassObject **ppInSignature,
            __out IWbemClassObject **ppOutSignature)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> NextMethod( 
                lFlags,
                pstrName,
                ppInSignature,
                ppOutSignature)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }
        
public:
  HRESULT endMethodEnumeration()
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    if (FAILED(hr = classObject -> EndMethodEnumeration()  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return hr;
    }
  }

public:
  IWbemQualifierSet* getMethodQualifierSet( 
            __in LPCWSTR wszMethod)
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    IWbemQualifierSet *pQualSet = NULL;
    if (FAILED(hr = classObject -> GetMethodQualifierSet( 
                wszMethod,
                &pQualSet)  )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return pQualSet;
    }
  }

public:
  _bstr_t getMethodOrigin( 
            __in LPCWSTR wszMethodName) 
  {
    HRESULT hr = S_OK;
    IWbemClassObject* classObject = getClassObject();
    BSTR strClassName = NULL;
    if (FAILED(hr = classObject -> GetMethodOrigin( 
      wszMethodName,
      &strClassName)   )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    else {
      return _bstr_t(strClassName, false);
    }
  }


public:
  void display()
  {
    _bstr_t text = getObjectText(0);
    Writer writer;
    writer.write((const wchar_t*)text);
  }
};

}
