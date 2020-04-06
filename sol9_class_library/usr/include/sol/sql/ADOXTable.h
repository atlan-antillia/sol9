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
 *  ADOXTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02
// 2009/06/07 Added a appendColumn() method to append a new column to ADOXColumns of an ADOXTabl object
/*
  ADOXTable table;
  table.createInstance();

  table.appendColumn("ID", ADOX::adInteger, 0);
  table.appendColumn("Name", ADOX::adVarChar, 255);
  ...
*/
#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADOXColumns.h>
#include <sol/sql/ADOXKeys.h>
#include <sol/sql/ADOXIndexes.h>
#include <sol/sql/ADOXProperties.h>


class ADOXTable :public ADOObject {

public:
  ADOXTable()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Table));
  }

public:
  void set(__in ADOX::_TablePtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }

public:
  ADOX::_TablePtr getTablePtr() 
  {
    return (ADOX::_TablePtr)getObject();  
  }

public:
  //1 Get an object of ADOXColumns from this table
  //2 Append a set of column data passed by arguments to the object as a new column 

  bool appendColumn(
    __in const _variant_t& item,
    __in ADOX::DataTypeEnum type,
     __in long definedSize)
  {
    bool rc = false;

    ADOXColumns columns;
    if (getColumns(columns)) {

      HRESULT hr = columns.append(
        item,
        type,
         definedSize);
      if (SUCCEEDED(hr)) {
        rc = true;
      } else {
        throw Exception(hr, "%s", __FUNCTION__);
      }
    }
    return rc;
  } 

public:
  bool getColumns(
       __out ADOXColumns& columns)
  {
    bool rc = false;
    ADOX::ColumnsPtr ptr = getColumns();

    if (ptr) {
      columns.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }


public:
  ADOX::ColumnsPtr getColumns()
  {
    return getTablePtr()->GetColumns();
  }

public:
  _bstr_t getName()
  {
     return getTablePtr()->GetName();
  }

public:
  void putName(__in _bstr_t pVal)
  {
    getTablePtr()->PutName(pVal);
  }

public:
  _bstr_t getType()
  {
    return getTablePtr()->GetType();
  }

public:
  bool getIndexes(
       __out ADOXIndexes& indexes)
  {
    bool rc = false;

    ADOX::IndexesPtr ptr = getIndexes();

    if (ptr) {
      indexes.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::IndexesPtr getIndexes()
  {
    return getTablePtr()->GetIndexes();
  }

public:
  bool getKeys(
       __out ADOXKeys& keys)
  {
    bool rc = false;
    ADOX::KeysPtr ptr = getKeys();

    if (ptr) {
      keys.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::KeysPtr getKeys()
  {
    return getTablePtr()->GetKeys();
  }

public:
  bool getProperties(
       __out ADOXProperties& properties)
  {
    bool rc = false;
    ADOX::PropertiesPtr ptr = getProperties();

    if (ptr) {
      properties.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::PropertiesPtr getProperties()
  {
    return getTablePtr()->GetProperties();
  }

public:
  _variant_t getDateCreated()
  {
    return getTablePtr()->GetDateCreated();
  }

public:
  _variant_t getDateModified()
  {
    return getTablePtr()->GetDateModified();
  }

public:
  ADOX::_CatalogPtr getParentCatalog()
  {
    return getTablePtr()->GetParentCatalog();
  }

public:
  void putParentCatalog (
    __in ADOX::_Catalog * ppvObject)
  {
    getTablePtr()->PutParentCatalog(
            ppvObject);
  }


public:
  void putRefParentCatalog(
         __in ADOX::_Catalog * ppvObject)
  {
    getTablePtr()->PutRefParentCatalog(ppvObject);
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    _bstr_t type = getType();

    COMTypeConverter converter;
    _variant_t val = getDateCreated();
    _bstr_t created="";
    converter.toString(val, created);

    printf("<Table Name=\"%s\" Type=\"%s\" Created=\"%s\">\n",
      (const char*)name,
      (const char*)type,
      (const char*)created
      );

    /*
    */
    ADOXColumns columns;
    getColumns(columns);
    columns.dump();

    ADOXKeys keys;
    getKeys(keys);
    keys.dump();

    ADOXIndexes indexes;
    getIndexes(indexes);
    indexes.dump();

    ADOXProperties properties;
    getProperties(properties);
    properties.dump();

    printf("</Table>\n");
  }
};

