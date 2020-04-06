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
 *  SWbemObjectPath.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>


namespace SOL {

class SWbemObjectPath : public SWbemBaseObject {

public:
  SWbemObjectPath(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemObjectPath* get()
  {
    return (ISWbemObjectPath*)getIDispatch();
  }

public:
  SWbemObjectPath& operator=(ISWbemObjectPath* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
   _bstr_t getPath() 
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strPath =NULL;

    if (FAILED(hr = path -> get_Path(&strPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strPath, false);
  }
        

public:
  HRESULT putPath( 
            __in _bstr_t strPath)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Path( 
      (BSTR)strPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  _bstr_t getRelPath()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strRelPath = NULL;

    if (FAILED(hr = path -> get_RelPath( 
      &strRelPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strRelPath, false);
  }
        

public:
  HRESULT putRelPath( 
            __in _bstr_t strRelPath)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_RelPath( 
      (BSTR)strRelPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  _bstr_t getServer()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strServer = NULL;

    if (FAILED(hr = path -> get_Server( 
      &strServer))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strServer, false);
  }

public:
  HRESULT putServer( 
            __in _bstr_t strServer)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Server( 
      (BSTR)strServer))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  _bstr_t getNamespace()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strNamespace = NULL;

    if (FAILED(hr = path -> get_Namespace( 
      &strNamespace))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strNamespace, false);
  }
        

public:
  HRESULT putNamespace( 
            __in _bstr_t strNamespace)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Namespace( 
      (BSTR)strNamespace))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  _bstr_t getParentNamespace()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strParentNamespace = NULL;

    if (FAILED(hr = path -> get_ParentNamespace( 
      &strParentNamespace))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strParentNamespace, false);
  }

public:
  _bstr_t getDisplayName()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strDisplayName = NULL;

    if (FAILED(hr = path -> get_DisplayName( 
      &strDisplayName))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strDisplayName, false);
  }
        

public:
  HRESULT putDisplayName( 
            __in _bstr_t strDisplayName)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_DisplayName( 
      (BSTR)strDisplayName))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  _bstr_t getClass()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strClass = NULL;

    if (FAILED(hr = path -> get_Class( 
      &strClass))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strClass, false);
  }
        

public:
  HRESULT putClass( 
            __in _bstr_t strClass)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Class( 
      (BSTR)strClass))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public:
  bool isClass()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    VARIANT_BOOL bIsClass = VARIANT_FALSE;;

    if (FAILED(hr = path -> get_IsClass(&bIsClass))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return toBool(bIsClass);
  }

        
public:
  HRESULT setAsClass()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> SetAsClass())) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  bool isSingleton()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    VARIANT_BOOL bIsSingleton = VARIANT_FALSE;

    if (FAILED(hr = path -> get_IsSingleton(&bIsSingleton))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bIsSingleton);
  }

        
public:
  HRESULT setAsSingleton()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> SetAsSingleton())) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public:
  ISWbemNamedValueSet* getKeys()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    ISWbemNamedValueSet *objWbemNamedValueSet = NULL;

    if (FAILED(hr = path -> get_Keys( 
      &objWbemNamedValueSet))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemNamedValueSet;
  }


public:
  ISWbemSecurity* getSecurity()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    ISWbemSecurity *objWbemSecurity = NULL;

    if (FAILED(hr = path -> get_Security_( 
      &objWbemSecurity))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemSecurity;
  }

        
public:
  _bstr_t getLocale()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();
    BSTR strLocale = NULL;

    if (FAILED(hr = path -> get_Locale( 
      &strLocale))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strLocale, false);
  }

public:
  HRESULT putLocale( 
            __in _bstr_t strLocale)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Locale( 
      (BSTR)strLocale))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        

public:
  _bstr_t getAuthority()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    BSTR strAuthority = NULL;

    if (FAILED(hr = path -> get_Authority( 
      &strAuthority))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strAuthority, false);
  }

public:
  HRESULT putAuthority( 
            __in _bstr_t strAuthority)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectPath* path = get();

    if (FAILED(hr = path -> put_Authority( 
      (BSTR)strAuthority))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
/*
public:
  void display()
  {
    ReportWriter writer;
    report(writer);
  }
*/
public:
  void write(Writer& writer)
  {
    writer.writeln(L"<ObjectPath>");
    HTMLEncoder encoder;
    try {
      _bstr_t className = getClass();
      StringT<wchar_t> wclassName;
      encoder.encode((const wchar_t*)className, wclassName);
      writer.writeln(L"<ClassName>%s</ClassName>", (const wchar_t*)wclassName);

      _bstr_t displayName = getDisplayName();
      StringT<wchar_t> wname;
      encoder.encode((const wchar_t*)displayName, wname);
      writer.writeln(L"<DisplayName>%s</DisplayName>", (const wchar_t*)wname);

      _bstr_t authority = getAuthority();
      StringT<wchar_t> wauth;
      encoder.encode((const wchar_t*)authority, wauth);
      writer.writeln(L"<Authority>%s</Authority>", (const wchar_t*)wauth);
    } catch (...) {

    }
    writer.writeln(L"</ObjectPath>");

  }

};

}
