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
 *  ADOXProcedures.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXProcedure.h>


namespace SOL {

class ADOXProcedures :public ADOCollection {

public:
  ADOXProcedures()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Procedures));
  }

public:
  void set(__in ADOX::ProceduresPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }

public:
  ADOX::ProceduresPtr getProceduresPtr() 
  {
    return (ADOX::ProceduresPtr)getObject();  
  }


public:

  bool getItem(
          __in const _variant_t& index, 
      __out ADOXProcedure& procedure)
  {
    bool rc = false;
    ADOX::ProcedurePtr ptr = getItem(index);
    if (ptr) {
      procedure.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);

    }
    return rc;
  }

public:
  ADOX::ProcedurePtr getItem (
    __in const _variant_t& item)
  {
    return getProceduresPtr()->GetItem(item);
  }

public:
  HRESULT append(
    __in _bstr_t name,
    __in IDispatch* command)
  {
    return getProceduresPtr()->Append(
      name,
      command);
  }

public:
  HRESULT remove(
    __in const _variant_t& item)
  {
    return getProceduresPtr()->Delete(item); 
  }

public:
  long getCount()
  {
    return getProceduresPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getProceduresPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getProceduresPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Procedues>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXProcedure procedure;
      getItem(_variant_t(i), procedure);
      procedure.dump();
    }
    printf("</Procedues>\n");

  }
};


}
