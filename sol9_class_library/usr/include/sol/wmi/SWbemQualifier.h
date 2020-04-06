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
 *  SWbemQualifier.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>

namespace SOL {

class SWbemQualifier : public SWbemBaseObject {
    
public:
  SWbemQualifier(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemQualifier* get()
  {
    return (ISWbemQualifier*)getIDispatch();    
  }

public:
  SWbemQualifier& operator=(ISWbemQualifier* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  _variant_t getValue()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_Value( 
      &var))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _variant_t(var, false);
  }
        

public:
  HRESULT putValue( 
            __in _variant_t varValue)
  {
    VARIANT var =(VARIANT)varValue;
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->put_Value( 
      &var))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        

public:
  _bstr_t getName()
  {
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    BSTR strName = NULL;
    if (FAILED(hr = qualifier->get_Name( 
      &strName))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strName, false);
  }
                
         
public:
  bool getIsLocal()
  {
    VARIANT_BOOL vbool;

    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_IsLocal( 
      &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }
        
         
public:
  bool getPropagatesToSubclass()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_PropagatesToSubclass( 
      &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }
        
        
public:
  HRESULT putPropagatesToSubclass( 
            __in bool bPropagatesToSubclass)
  {
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->put_PropagatesToSubclass( 
      toVariantBool(bPropagatesToSubclass) ))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
         
public:
  bool getPropagatesToInstance()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_PropagatesToInstance( 
      &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }

public:
  HRESULT putPropagatesToInstance( 
            __in bool bPropagatesToInstance)
  {
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->put_PropagatesToInstance( 
      toVariantBool(bPropagatesToInstance) ))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
         
public:
  bool getIsOverridable()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_IsOverridable( 
      &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }

public:
  HRESULT putIsOverridable( 
            __in bool bIsOverridable)
  {
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->put_IsOverridable( 
      toVariantBool(bIsOverridable) ))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
         
public:
  bool getIsAmended()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemQualifier* qualifier = get();
    if (FAILED(hr = qualifier->get_IsAmended( 
      &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }

public:
  void write(Writer& writer)
  {
    writer.writeln(L"<Qualifier>");
    HTMLEncoder encoder;
    try {
      _bstr_t name = getName();
    
      _variant_t variant = getValue();

      COMTypeConverter converter;
      _bstr_t string;

      converter.toString(variant, string);

      StringT<wchar_t> wname;
      encoder.encode((const wchar_t*)name, wname); 
      writer.writeln(L"<Name>%s</Name>", (const wchar_t*)wname);

      StringT<wchar_t> wstring;
      encoder.encode((const wchar_t*)string, wstring);
      writer.writeln(L"<Value>%s</Value>", (const wchar_t*)wstring);

    } catch (...) {

    }
    writer.writeln(L"</Qualifier>");

  }

};

}
