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
 *  SWbemNamedValueSet.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObjectSet.h>
namespace SOL {

class SWbemNamedValueSet : public SWbemBaseObjectSet {


public:
  SWbemNamedValueSet(IDispatch* pDisp=NULL)
  :SWbemBaseObjectSet(pDisp)
  {

  }

public:
  ISWbemNamedValueSet* get()
  {
    return (ISWbemNamedValueSet*)getIDispatch();
  }
    
public:
  SWbemNamedValueSet& operator=(ISWbemNamedValueSet* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  IUnknown* get__NewEnum()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();

    if (FAILED(hr = set->get__NewEnum(&pUnk))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pUnk;
  }
        
public:
  ISWbemNamedValue *item( 
            __in _bstr_t strName,
           __in long iFlags)
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();
    ISWbemNamedValue *objWbemNamedValue = NULL;

    if (FAILED(hr = set->Item( 
      (BSTR)strName,
      iFlags,
      &objWbemNamedValue))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemNamedValue;
  }


public:
  lonf getCount()
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();
    long iCount = 0;

    if (FAILED(hr = set->get_Count(&iCount))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iCount;
  }
        
public:
  ISWbemNamedValue *  add( 
            __in _bstr_t strName,
            __in VARIANT *varValue,
           __in long iFlags)
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();
    ISWbemNamedValue *objWbemNamedValue =NULL;

    if (FAILED(hr = set->Add( 
      (BSTR)strName,
      varValue,
      iFlags,
      &objWbemNamedValue))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemNamedValue;
  }
                

public:
  HRESULT remove( 
            __in _bstr_t strName,
           __in long iFlags = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();

    if (FAILED(hr = set->Remove( 
      (BSTR)strName,
      iFlags))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        

public:
  ISWbemNamedValueSet* clone()
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();
    ISWbemNamedValueSet *objWbemNamedValueSet=NULL;

    if (FAILED(hr = set->Clone( 
      &objWbemNamedValueSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemNamedValueSet;
  }

public:
  HRESULT deleteAll()
  {
    HRESULT hr = E_FAIL;
    ISWbemNamedValueSet* set = get();

    if (FAILED(hr = set->DeleteAll())) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
   
public:
  void write(Writer& writer)
  {
    long c = getCount();

    writer.writeln(L"<NamedValueSet>");
    
    try {
      EnumVariant enumVar = ComObjectSet::getNewEnum();
      IDispatch* pDisp = NULL;
      while (enumVar.next(1, &pDisp) == 1) {
    
        try {
          SWbemNamedValue namedValue = pDisp;
          namedValue.write(Writer);
        } catch (...) {
          break;
        }
      }

    } catch (...) {
      
    }
    reportWriter.writeln(L"</NameValueSet>");

  }
};

}
 
