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
 *  NetFwRules.h
 *
 *****************************************************************************/

//2012/09/14

#pragma once

#include <sol/com/ComIDispatch.h>
#include <sol/com/EnumVariant.h>
#include <netfw.h>
#include <sol/netfw/NetFwRule.h>
#include <sol/Writer.h>

/** Usage:
{
  NetFwPolicy2  policy2;
  NetFwRules rules = policy2.getRules();
  NetFwRule  rule;
  ...
  rules.add((INetFwRule*)rule);
}
*/

namespace SOL {

class NetFwRules: public ComIDispatch {
public:
  NetFwRules(INetFwRules* pRules=NULL)
    :ComIDispatch(pRules)
  {
  }

private:
  INetFwRules* getRules()
  {
    return (INetFwRules*) getIDispatch();
  }

public:
  HRESULT getCount( 
            /* [retval][out] */ long *count)
  {
    HRESULT hr = getRules() -> get_Count( 
        count);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  long getCount()
  {
    long count = 0;
    HRESULT hr = getRules() -> get_Count( 
        &count);
    if (FAILED(hr)) {
      throw hr;
    }
    return count;
  }

public:
  HRESULT add( 
            /* [in] */ INetFwRule *rule)
  {
    HRESULT hr = getRules() -> Add( 
        rule);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT remove( 
            /* [in] */ BSTR name)
  {
    HRESULT hr = getRules() -> Remove( 
        name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT item( 
            /* [in] */ BSTR name,
            /* [retval][out] */ INetFwRule **rule)
  {
    HRESULT hr = getRules() -> Item( 
        name,
        rule);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwRule* item( 
            /* [in] */ BSTR name)
  {
    INetFwRule* pRule = NULL;
    HRESULT hr = getRules() -> Item( 
        name,
        &pRule);
    if (FAILED(hr)) {
      throw hr;
    }
    return pRule;
  }

public:
  HRESULT getNewEnum( 
            /* [retval][out] */ IUnknown **newEnum)
  {
    HRESULT hr = getRules() -> get__NewEnum( 
        newEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  IUnknown* getNewEnum()
  {
    IUnknown* pEnum = NULL;
    HRESULT hr = getRules() -> get__NewEnum( 
        &pEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return pEnum;
  }
    
public:
  IEnumVARIANT* getEnumVariant()
  {
    ComIUnknown unknown = getNewEnum();
    return unknown.getEnumVariant();
  }

public:
  //2012/09/22
  INetFwRule* getItem(long index)
  {  
    INetFwRule* rule = NULL;
    EnumVariant enumVariant = getEnumVariant();
    int n = 0;
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        if (n == index) {
          rule = (INetFwRule*)dispatch.queryInterface(__uuidof(INetFwRule));
          break;
        }
        n++;
      } catch (...) {
        break;
      }
    }
    return rule;
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("<Rules count='%d'>\n"), getCount() );
    
    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwRule));
        NetFwRule rule((INetFwRule*)pDisp);
        rule.display(hwnd);
      } catch (...) {
        break;
      }
    }
    _tprintf(_T("</Rules>\n") );

  }

public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<Rules count='%d'>\n", getCount() );
    
    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwRule));
        NetFwRule rule((INetFwRule*)pDisp);
        rule.write(writer);
      } catch (...) {
        break;
      }
    }
    writer.write(L"</Rules>\n");

  }

};

}
