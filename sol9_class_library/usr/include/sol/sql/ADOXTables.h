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
 *  ADOXTables.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/07 Added a new method append(__in ADOXTable& table), which is used
// to append an ADOXTable object to an ADOXTables object

// 2009/06/07 Added a new method find(__in _bstr_t name, __out ADOXTable& table), which is used
// to find an ADOXTable object matching to name from an ADOXTables object

// 2009/06/07 Added a new method remove(__in _bstr_t name), which is used
// to remove an ADOXTable object matching to name from an ADOXTables object

///////////////////////////////
#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXTable.h>

namespace SOL {

class ADOXTables :public ADOCollection {


public:
  ADOXTables()
  {
  }

public:
  ~ADOXTables()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Tables));
  }

public:
  void set(__in ADOX::TablesPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }

public:
  ADOX::TablesPtr getTablesPtr()
  {
    return (ADOX::TablesPtr)getObject();
  }

public:
   bool getItem (
    __in const _variant_t& item,
    __out ADOXTable& table)
  {
    bool rc = false;
    ADOX::_TablePtr ptr = getItem(item);
    if (ptr) {
      table.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::_TablePtr getItem(
          __in const _variant_t& item)
  {
    return getTablesPtr()->GetItem(item);
  }

public:
  //2009/06/07
  HRESULT append(
    __in ADOXTable& table)
  {
    HRESULT hr = E_FAIL;
    ADOX::_TablePtr ptr = table.getTablePtr();
    if (ptr) {
      _variant_t item((IDispatch *)ptr);
      hr = append(item);
      if (FAILED(hr)) {
        throw Exception(hr, "%s", __FUNCTION__);
      }
    }
    return hr;
  }

public:
  HRESULT append(
    __in const _variant_t& item)
  {
    return getTablesPtr()->Append(item);
  }

public:
  HRESULT remove(
    __in const _variant_t& item)
  {
    return getTablesPtr()->Delete(item);
  }

public:
  long getCount()
  {
    return getTablesPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getTablesPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getTablesPtr()->_NewEnum();
  }

public:
  //2009/06/07
  bool remove(__in _bstr_t tablename)
  {
    bool rc = false;
    long c = getCount();

    const char* ctablename =(const char*)tablename;
    ADOXTable table;
    for (long i = 0; i<c; i++) {
      _variant_t item(i);
      getItem(item, table);
      _bstr_t name = table.getName();
      const char* cname = (const char*)name;
      //compare two string(const char*) with case insentive
      if (_stricmp(ctablename, cname) ==0) {
        //rc = getTablesPtr()->Delete(item);
        HRESULT hr = getTablesPtr()->Delete(item);
        if (SUCCEEDED(hr)) {
          rc = true;
        }
        break;
      }
    }
    return rc;
  }

public:
  //2009/06/07
  bool find(__in _bstr_t tablename,
        __out ADOXTable& table)
  {
    bool rc = false;
    long c = getCount();

    const char* ctablename =(const char*)tablename;
    
    for (long i = 0; i<c; i++) {
      getItem(_variant_t(i), table);
      _bstr_t name = table.getName();
      const char* cname = (const char*)name;
      //compare two string(const char*) with case insentive
      if (_stricmp(ctablename, cname) ==0) {
        rc = true;
        break;
      }
    }
    return rc;
  }

public:
  void dump()
  {
    printf("<Tables>\n");
    long c = getCount();
    
    for (long i = 0; i<c; i++) {
      ADOXTable table;
      getItem(_variant_t(i), table);
      table.dump();
    }
    printf("</Tables>\n");

  }
};

}
