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
 *  ADOXKeys.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXKey.h>

namespace SOL {

class ADOXKeys :public ADOCollection {

public:
  ADOXKeys()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Keys));
  }

public:
  void set(__in ADOX::KeysPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::KeysPtr getKeysPtr() 
  {
    return (ADOX::KeysPtr)getObject();  
  }

public:
   bool getItem (
    __in const _variant_t& item,
    __out ADOXKey& key)
  {
    bool rc = false;
    ADOX::_KeyPtr ptr = getItem(item);
    if (ptr) {
      key.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::_KeyPtr getItem (
          __in const _variant_t& item)
  {
    return getKeysPtr()->GetItem(item);
  }

public:
  HRESULT append(
    __in const _variant_t& item,
    __in ADOX::KeyTypeEnum type,
    __in const _variant_t& column,
    __in _bstr_t relatedTable,
    __in bstr_t relatedColumn)
  {
    return getKeysPtr()->Append(
      item,
      type,
      column,
      relatedTable,
      relatedColumn);
  }    

public:
  HRESULT remove(
    __in const _variant_t& item)
  {
    return getKeysPtr()->Delete(item);
  }

public:
  long getCount()
  {
    return getKeysPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getKeysPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getKeysPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Keys>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXKey key;
      getItem(_variant_t(i), key);
      key.dump();
    }
    printf("</Keys>\n");

  }
};

}
