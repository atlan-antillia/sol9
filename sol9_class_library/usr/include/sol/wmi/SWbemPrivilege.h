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
 *  SWbemPrivilege.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>


namespace SOL {
   
class SWbemPrivilege : public SWbemBaseObject {
    
public:
  SWbemPrivilege(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemPrivilege* get()
  {
    return (ISWbemPrivilege*)getIDispatch();
  }

public:
  SWbemPrivilege& operator=(ISWbemPrivilege* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  bool getIsEnabled()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilege* privilege = get();
    VARIANT_BOOL bIsEnabled = VARIANT_FALSE;

    if (FAILED(hr = privilege -> get_IsEnabled( 
      &bIsEnabled))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
  
    return toBool(bIsEnabled);
  }        
                

public:
  HRESULT putIsEnabled( 
            __in bool bIsEnabled)
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilege* privilege = get();

    if (FAILED(hr = privilege -> put_IsEnabled( 
      toVariantBool(bIsEnabled) ))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  _bstr_t getName()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilege* privilege = get();
    BSTR strDisplayName = NULL;

    if (FAILED(hr = privilege -> get_Name( 
      &strDisplayName))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strDisplayName, false);
  }        

public:
  _bstr_t getDisplayName()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilege* privilege = get();
    BSTR strDisplayName = NULL;

    if (FAILED(hr = privilege -> get_DisplayName( 
      &strDisplayName))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strDisplayName, false);
  }        
        

public:
  WbemPrivilegeEnum getIdentifier()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilege* privilege = get();
    WbemPrivilegeEnum iPrivilege;

    if (FAILED(hr = privilege -> get_Identifier( 
      &iPrivilege))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iPrivilege;
  }            


public:
  void write(Writer& writer)
  {
    _bstr_t name        = getName();

    writer.writeln(L"<Privilege>");
    try {
      _bstr_t displayName = getDisplayName();
      bool isEnabled = getIsEnabled();
      WbemPrivilegeEnum id = getIdentifier();
      writer.writeln(L"<Name>%s</Name>", (const wchar_t*)name);
      
      //printf("Name=%S\n", (const wchar_t*)name);
      writer.writeln(L"<DisplayName>%s</DisplayName>", (const wchar_t*)displayName);
      writer.writeln(L"<Identifier>%d</Identifier>", id);
      writer.writeln(L"<IsEnabled>%d</IsEnabled>", isEnabled);
    } catch(...) {

    }
    writer.writeln(L"</Privilege>");

  }
};

}
