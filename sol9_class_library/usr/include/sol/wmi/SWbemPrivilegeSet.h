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
 *  SWbemPrivilegeSet.h
 *
 *****************************************************************************/

// 2009/12/22 Moddified base class to be SWbemBaseObjectSet not SWbemBaseObject
// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObjectSet.h>
#include <sol/wmi/SWbemPrivilege.h>

namespace SOL {

class SWbemPrivilegeSet : public SWbemBaseObjectSet {

public:
  SWbemPrivilegeSet(IDispatch* pDisp=NULL)
  :SWbemBaseObjectSet(pDisp)
  {

  }

public:
  ISWbemPrivilegeSet* get()
  {
    return (ISWbemPrivilegeSet*)getIDispatch();
  }

public:
  SWbemPrivilegeSet& operator=(ISWbemPrivilegeSet* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  IUnknown* get__NewEnum()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();

    if (FAILED(hr = set -> get__NewEnum(&pUnk))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pUnk;
  }        
        
public:
  ISWbemPrivilege* item( 
            __in WbemPrivilegeEnum iPrivilege)
  {
    ISWbemPrivilege* pObjWbemPrivilege = NULL;
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();

    if (FAILED(hr = set -> Item( 
                iPrivilege,
          &pObjWbemPrivilege))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemPrivilege;
  }        
        
public:
  long getCount()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();
    long iCount = 0;

    if (FAILED(hr = set -> get_Count( 
      &iCount))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iCount;
  }        
        

public:
  ISWbemPrivilege* add( 
            __in WbemPrivilegeEnum iPrivilege,
           __in bool bIsEnabled)
  {
    ISWbemPrivilege* pObjWbemPrivilege = NULL;
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();

    if (FAILED(hr = set -> Add( 
      iPrivilege,
      toVariantBool(bIsEnabled),
      &pObjWbemPrivilege))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemPrivilege;
  }        
        
public:
  HRESULT remove( 
            __in WbemPrivilegeEnum iPrivilege)
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();

    if (FAILED(hr = set -> Remove( 
      iPrivilege))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        
public:
  HRESULT deleteAll()
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();

    if (FAILED(hr = set -> DeleteAll())) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

  //2009/12/20
public:
   ISWbemPrivilege* addAsString( 
            __in _bstr_t strPrivilege,
           __in bool bIsEnabled)
  {
    HRESULT hr = E_FAIL;
    ISWbemPrivilegeSet* set = get();
    ISWbemPrivilege *objWbemPrivilege = NULL;

    if (FAILED(hr = set -> AddAsString( 
        (BSTR)strPrivilege,
        toVariantBool(bIsEnabled),
        &objWbemPrivilege))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemPrivilege;
  }        

public:
  void write(Writer& writer)
  {
    writer.writeln(L"<PrivilegeSet>");

    try {
      EnumVariant enumVar = ComObjectSet::getNewEnum();
      IDispatch* pDisp = NULL;
  
      while ((pDisp = enumVar.next()) !=NULL ) {
        try {
          SWbemPrivilege privilege = pDisp;
          privilege.write(writer);
        } catch (...) {

        }
      }
    } catch (...) {

    }
    writer.writeln(L"</PrivilegeSet>");

  }

};

}
