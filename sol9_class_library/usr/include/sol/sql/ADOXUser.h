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
 *  ADOXUser.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADOXGroups.h>

namespace SOL {

class ADOXUser: public ADOObject {

public:
  ADOXUser()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::User));
  }

public:
  void set(__in ADOX::_UserPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::_UserPtr getUserPtr()
  {
    return (ADOX::_UserPtr)getObject();
  }
public:
  _bstr_t getName() 
  {  
    return getUserPtr()->GetName();
  }

public:
  void putName(__in _bstr_t pVal)
  {
    getUserPtr()->PutName(pVal);
  }

public:
  ADOX::RightsEnum getPermissions(
    __in const _variant_t& name,
    __in ADOX::ObjectTypeEnum objectType,
    __in_opt const _variant_t& objectTypeId = vtMissing)
  {
    return  getUserPtr()->GetPermissions(
      name,
      objectType,
      objectTypeId);
  }

public:
    HRESULT setPermissions(
    __in const _variant_t& name,
    __in ADOX::ObjectTypeEnum objectType,
    __in ADOX::ActionEnum action,
    __in ADOX::RightsEnum rights,
    __in ADOX::InheritTypeEnum inherit,
    __in_opt const _variant_t& objectTypeId = vtMissing)
  {
    return getUserPtr()->SetPermissions(
      name,
      objectType,
      action,
      rights,
      inherit,
      objectTypeId);
  }

public:
    HRESULT changePassword(
    __in _bstr_t oldPassword,
    __in _bstr_t newPassword)
  {
    return getUserPtr()->ChangePassword(
      oldPassword,
      newPassword);
  }

public:
  bool getGroups(ADOXGroups& groups)
  {
    bool rc = false;
    ADOX::GroupsPtr ptr = getGroups();
    if (ptr) {
      groups.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::GroupsPtr getGroups()
  {
    return getUserPtr()->GetGroups();
  }

public:
  ADOX::PropertiesPtr getProperties()
  {
    return getUserPtr()->GetProperties();
  }

public:
  ADOX::_CatalogPtr getParentCatalog()
  {
    return getUserPtr()->GetParentCatalog();
  }


public:
  void putParentCatalog(
          __in ADOX::_Catalog * ppvObject)
  {
    getUserPtr()->PutParentCatalog(ppvObject);
  }

public:
  void putRefParentCatalog(
    __in ADOX::_Catalog * ppvObject)
  {
    getUserPtr()->PutRefParentCatalog(ppvObject);
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    printf("<User Name=\"%s\" />\n", (const char*)name);
  }
};

}
