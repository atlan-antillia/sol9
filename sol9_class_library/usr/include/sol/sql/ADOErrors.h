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
 *  ADOErrors.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/05/15

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOError.h>

namespace SOL {


class ADOErrors :public ADOCollection {


public:
  ADOErrors()
  {
  }

public:
  ~ADOErrors()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Errors));
  }


public:
  void set(__in ADODB::ErrorsPtr pEs)
  {
    setObject((IDispatchPtr)pEs);
  }

public:
  ADODB::ErrorsPtr getErrorsPtr()
  {
    return (ADODB::ErrorsPtr)getObject();
  }

public:
  bool getItem(const _variant_t& index,
      __out ADOError& error)
  {
    bool rc = false;
    ADODB::ErrorPtr pE = getErrorsPtr()->GetItem(index);
    if (pE) {
      error.set(pE);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADODB::ErrorPtr getItem(const _variant_t& index)
  {
    return getErrorsPtr()->GetItem(index);
  }


public:

  HRESULT clear()
  {
    HRESULT hr = getErrorsPtr()->Clear();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }


public:
  long getCount()
  {
    return getErrorsPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getErrorsPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getErrorsPtr()->_NewEnum();
  }

public:
  void dump()
  {
      long count = getCount();
      printf("ADOErrors:\n");
      for (long i=0; i<count; i++) {
        ADOError error;
        if (getItem(_variant_t(i), error)) {
          error.dump();
          printf("\n");  
        }
      }
  }
};

}

