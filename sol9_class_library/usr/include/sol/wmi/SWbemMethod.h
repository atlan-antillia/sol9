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
 *  SWbemMethod.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>

namespace SOL {

class SWbemMethod :public SWbemBaseObject {
    
public:
  SWbemMethod(IDispatch* pDisp=NULL) 
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemMethod* get()
  {
    return (ISWbemMethod*)getIDispatch();
  }

public:
  SWbemMethod& operator=(ISWbemMethod* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  _bstr_t getName()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethod* method = get();
    BSTR strName = NULL;

    if (FAILED(hr = method->get_Name(&strName))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strName, false);
  }        

public:
  _bstr_t getOrigin()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethod* method = get();
    BSTR strOrigin = NULL;

    if (FAILED(hr = method->get_Origin(&strOrigin))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strOrigin, false);
  }    

public:
  ISWbemObject* getInParameters()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethod* method = get();
    ISWbemObject *objWbemInParameters = NULL;

    if (FAILED(hr = method->get_InParameters(
        &objWbemInParameters))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemInParameters;
  }    


public:
  ISWbemObject* getOutParameters()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethod* method = get();
    ISWbemObject *objWbemOutParameters = NULL;

    if (FAILED(hr = method->get_OutParameters( 
        &objWbemOutParameters))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemOutParameters;
  }    

        
public:
  ISWbemQualifierSet* getQualifiers()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethod* method = get();
    ISWbemQualifierSet *objWbemQualifierSet = NULL;

    if (FAILED(hr = method->get_Qualifiers_( 
        &objWbemQualifierSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemQualifierSet;
  }    


public:
  void write(Writer& writer)
  {
    _bstr_t name = getName();

    writer.writeln(L"<Method>");
    writer.writeln(L"<Name>%s</Name>", 
      (const wchar_t*)name);

    try {
      SWbemObject inParameters  = getInParameters();
      SWbemObject outParameters = getOutParameters();
      writer.writeln(L"<InParameters>");
      inParameters.write(writer);
      writer.writeln(L"</InParameters>");

      writer.writeln(L"<OutParameters>");
      outParameters.write(writer);
      writer.writeln(L"</OutParameters>");

    } catch (...) {

    }
    writer.writeln(L"</Method>");
  }

};

}

