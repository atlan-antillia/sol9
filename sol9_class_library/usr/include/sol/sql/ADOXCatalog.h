/******************************************************************************
 *
 * Copyright(c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  ADOXCatalog.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02
// 2009/06/06 Added appendTable() method.

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADOXTables.h>
#include <sol/sql/ADOXProperties.h>
#include <sol/sql/ADOXProcedures.h>
#include <sol/sql/ADOXViews.h>
#include <sol/sql/ADOXGroups.h>
#include <sol/sql/ADOXUsers.h>


namespace SOL {

class ADOXCatalog :public ADOObject {

public:
  ADOXCatalog()
  {
  }

public:
  ~ADOXCatalog()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Catalog));
  }

public:
  void set(__in ADOX::_CatalogPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }
public:
  void close()
  {
    clear();
  }

public:
  ADOX::_CatalogPtr getCatalogPtr()
  {
    return(ADOX::_CatalogPtr)getObject();
  }

public:
  /**If a initial catalog in connectionString already exists,
   1 Try to call putActiveConnection().
   2 If already exists, then the call throws IException.
   3 Catch the IException, try to create.
   4 If faield to create, the call throws IException.
   */
  HRESULT open(_bstr_t connectionString)
  {
    HRESULT hr = E_FAIL;
    try {
      //printf("Try to connect to an existing catalog\n");
      
      putActiveConnection(connectionString);
      //printf("OK, connected to an existing catalog\n");

      hr = S_OK;
    } catch (_com_error& ex) {
      COMError error(ex);
      error.dump();
      //printf("Try to catalog.create\n");

      create(connectionString);
      //printf("OK, created a new catalog\n");
      hr = S_OK;
    }
    return hr;
  }

public:
  //
  bool getTables(__out ADOXTables& tables)
  {
    bool rc = false;
    ADOX::TablesPtr ptr = getTables();
    if (ptr) {
      tables.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }    
    return rc;
  }

public:
  ADOX::TablesPtr getTables()
  {
    return getCatalogPtr()->GetTables();
  }

public:
  //2009/06/06
  bool appendTable(__in ADOXTable& table)
  {
    bool rc = false;
    // 1 Get ADOXTables object from this catalog
    ADOXTables tables;
    if (getTables(tables)) {
      //2 Try to append ADOXTable object to the ADOXTables object.
      HRESULT hr = tables.append(table);
      if (SUCCEEDED(hr)) {
        rc = true;
      }
    }
    return rc;
  }

public:
  _variant_t getActiveConnection()
  {
    return getCatalogPtr()->GetActiveConnection();
  }

public:
  void putActiveConnection(__in const _variant_t & pVal)
  {
    getCatalogPtr()->PutActiveConnection(pVal);
  }

public:
  void putActiveConnection(__in const _bstr_t & pVal)
  {
    _variant_t varConnection(pVal);
    getCatalogPtr()->PutActiveConnection(varConnection);
  }

public:
  //2009/06/03
  void putActiveConnection(__in ADODB::_ConnectionPtr activeConnection)
  {
    _variant_t varConnection((IDispatch*)activeConnection);
    getCatalogPtr()->PutActiveConnection(varConnection);
  }

public:
  void putRefActiveConnection(__in IDispatch * pVal)
  {
    getCatalogPtr()->PutRefActiveConnection(pVal);
  }

public:
  //
  bool getProcedures(__out ADOXProcedures& procedures)
  {
    bool rc = false;
    ADOX::ProceduresPtr ptr = getProcedures();
    if (ptr) {
      procedures.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::ProceduresPtr getProcedures()
  {
    return getCatalogPtr()->GetProcedures();
  }

public:
  //
  bool getViews(__out ADOXViews& views)
  {
    bool rc = false;
    ADOX::ViewsPtr ptr = getViews();
    if (ptr) {
      views.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }  
    return rc;
  }

public:
  ADOX::ViewsPtr getViews()
  {
    return getCatalogPtr()->GetViews();
  }

public:
  //
  bool getGroups(__out ADOXGroups& groups)
  {
    bool rc = false;
    ADOX::GroupsPtr ptr = getGroups();

    if (ptr) {
      groups.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }    
    return rc;
  }


public:
  ADOX::GroupsPtr getGroups()
  {
    return getCatalogPtr()->GetGroups();
  }

public:
  //
  bool getUsers(__out ADOXUsers& users)
  {
    bool rc = false;
    ADOX::UsersPtr ptr = getUsers();

    if (ptr) {
      users.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }    
    return rc;
  }

public:
  ADOX::UsersPtr getUsers()
  {
    return getCatalogPtr()->GetUsers();
  }

public:
  _variant_t create(
    __in _bstr_t connectString)
  {
    return getCatalogPtr()->Create(connectString);
  }

public:
  _bstr_t getObjectOwner(
    __in _bstr_t objectName,
    __in ADOX::ObjectTypeEnum objectType,
    __in_opt const _variant_t& objectTypeId = vtMissing)
  {
    return getCatalogPtr()->GetObjectOwner(
      objectName,
      objectType,
      objectTypeId);
  }

public:
  HRESULT setObjectOwner(
    __in _bstr_t objectName,
    __in ADOX::ObjectTypeEnum objectType,
    __in _bstr_t userName,
    __in_opt const _variant_t& objectTypeId = vtMissing)
  {
    return getCatalogPtr()->SetObjectOwner(
      objectName,
      objectType,
      userName,
      objectTypeId);
  }

};

}
