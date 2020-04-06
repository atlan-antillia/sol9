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
 *  ADOXIndexes.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXIndex.h>

namespace SOL {

class ADOXIndexes :public ADOCollection {

public:
  ADOXIndexes()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Indexes));
  }

public:
  void set(__in ADOX::IndexesPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::IndexesPtr getIndexesPtr() 
  {
    return (ADOX::IndexesPtr)getObject();  
  }


public:
   bool getItem (
    __in const _variant_t & item,
    __out ADOXIndex& index)
  {
    bool rc = false;
    ADOX::_IndexPtr ptr = getItem(item);
    if (ptr) {
      index.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::_IndexPtr getItem (
    __in const _variant_t& item)
  {
    return getIndexesPtr()->GetItem(
      item);
  }

public:
  HRESULT append (
    __in const _variant_t& item,
    __in_opt const _variant_t& columns = vtMissing)
  {
    return getIndexesPtr()->Append(
      item,
      columns);

  }

public:
  HRESULT remove(
    __in const _variant_t& item)
  {
    return getIndexesPtr()->Delete(
        item);
  }

public:
  long getCount()
  {
    return getIndexesPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getIndexesPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getIndexesPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Indexes>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXIndex index;
      getItem(_variant_t(i), index);
      index.dump();
    }
    printf("</Indexes>\n");

  }
};

}
