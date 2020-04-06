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
 *  SWbemNamedValue.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>


namespace SOL {

class SWbemNamedValue : public SWbemBaseObject {

public:
  SWbemNamedValue(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }  

public:
  ISWbemNamedValue* get()
  {
    return (ISWbemNamedValue*)getIDispatch();
  }

public:
  SWbemNamedValue& operator=(ISWbemNamedValue* pDisp)
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
    ISWbemNamedValue* namedvalue = get();

    if (FAILED(hr = namedvalue->get_Value(&var))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _variant_t(var, false);
  }  

public:
  HRESULT putValue( 
            __in _variant_t varValue) 
  {
    VARIANT var = (VARIANT)varValue;
    HRESULT hr = E_FAIL;
    ISWbemNamedValue* namedvalue = get();

    if (FAILED(hr = namedvalue->put_Value(&var))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;

  }
public:
  _bstr_t getName() 
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValue* namedvalue = get();
    BSTR strName = NULL;
    if (FAILED(hr = namedvalue->get_Name(&strName))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strName. false);
  } 

public:
  void write(Writer& writer)
  {
    writer.writeln(L"<NamedValue>");
    try {
      _bstr_t name = getName();
      _variant_t variant = getValue();
    
      COMTypeConverter converter;
      _bstr_t string;
      converter.toString(variant, string, _bstr_t("(NULL)"));

      StringT<wchar_t> wname;
      encoder.encode((const wchar_t*)name, wname); 
      writer.writeln(L"<Name>%s</Name>",
        (const wchar_t*)wname);

      StringT<wchar_t> wstring;
      encoder.encode((const wchar_t*)string, wstring);
      writer.writeln(L"<Value>%s</Value>",    
        (const wchar_t*)wstring);
    } catch (...) {

    }
    writer.writeln(L"</NamedValue>");

  }

};

}
