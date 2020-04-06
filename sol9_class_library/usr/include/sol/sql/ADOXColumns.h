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
 *  ADOXColumns.h
 *
 *****************************************************************************/

// SOL9
///////////////////////////////
#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXColumn.h>

namespace SOL {

class ADOXColumns :public ADOCollection {


public:
  ADOXColumns()
  {
  }

public:
  ~ADOXColumns()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Columns));
  }

public:
  void set(__in ADOX::ColumnsPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }

public:
  ADOX::ColumnsPtr getColumnsPtr()
  {
    return (ADOX::ColumnsPtr)getObject();
  }

public:
   bool getItem(
    __in const _variant_t& item,
    __out ADOXColumn& column)
  {
    bool rc = false;
    ADOX::_ColumnPtr ptr = getItem(item);
    if (ptr) {
      column.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::_ColumnPtr getItem(
    __in const _variant_t& item)
  {
    return getColumnsPtr()->GetItem(item);
  }

public:
  HRESULT append(
    __in const _variant_t& item,
    __in ADOX::DataTypeEnum type,
     __in long definedSize)
  {
    return getColumnsPtr()->Append (
      item,
      type,
       definedSize);
  }

public:

  HRESULT remove(
    __in const _variant_t& item)
  {
    return getColumnsPtr()->Delete(item);
  }

public:
  long getCount()
  {
    return getColumnsPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getColumnsPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getColumnsPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Columns>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXColumn column;
      getItem(_variant_t(i), column);
      column.dump();
    }
    printf("</Columns>\n");
  }
};

}
