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
 *  ADOParameters.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/09
// 2009/05/14 Added getParameter(ADOParameter& ) method.
// 2009/05/15
// 2009/05/22 Added append and remove methods
#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOParameter.h>

namespace SOL {

class ADOParameters :public ADOCollection {

public:
  ADOParameters()
  {
  }

public:
  ~ADOParameters()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Parameters));
  }

public:
  void set(__in ADODB::ParametersPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }

public:
  ADODB::ParametersPtr getParametersPtr()
  {
    return (ADODB::ParametersPtr)getObject();
  }

public:
  //2009/05/14
  bool getItem(
      __in const _variant_t& index,
      __out ADOParameter& parameter)
  {
    bool rc = false;
    ADODB::_ParameterPtr pParam = getItem(index);
    if (pParam) {
      parameter.set(pParam);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:

  ADODB::_ParameterPtr getItem(
          __in const _variant_t& index)
  {
    return getParametersPtr()->GetItem(index);
  }
  

public:
  long getCount()
  {
    return getParametersPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getParametersPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getParametersPtr()->_NewEnum();
  }

public:
  //2009/05/22
    HRESULT append(ADOParameter& param)
  {
    IDispatch* iobject = (IDispatch*)param.getParameterPtr();
    HRESULT hr = getParametersPtr()->Append(iobject);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  //2009/05/22
    HRESULT append(IDispatch* iobject)
  {
    HRESULT hr = getParametersPtr()->Append(iobject);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  //2009/05/22
    HRESULT remove(const _variant_t& index)
  {
    HRESULT hr = getParametersPtr()->Delete(index);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  void dump()
  {
    long count = getCount();
    printf("Parameters: \n");
    for (long n = 0; n<count; n++) {
      ADOParameter param;
      if (getItem(_variant_t(n), param)) {
        param.dump();
      }
    }

  }

};

}
