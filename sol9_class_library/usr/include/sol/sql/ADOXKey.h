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
 *  ADOXKey.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/12

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {

class ADOXKey :public ADOObject {

public:
  ADOXKey()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Key));
  }

public:
  void set(__in ADOX::_KeyPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::_KeyPtr getKeyPtr() 
  {
    return (ADOX::_KeyPtr)getObject();  
  }

public:
  _bstr_t getName()
  {
    return getKeyPtr()->GetName();
  }

public:
  void putName(__in _bstr_t pVal)
  {
    getKeyPtr()->PutName(pVal);
  }

public:
  ADOX::RuleEnum getDeleteRule()
  {
    return getKeyPtr()->GetDeleteRule();
  }

public:
  void putDeleteRule (
    __in ADOX::RuleEnum pVal)
  {
    getKeyPtr()->PutDeleteRule (
      pVal);
  }
public:
  ADOX::KeyTypeEnum getType()
  {
    return getKeyPtr()->GetType( );
  }

public:
  void putType(
    __in ADOX::KeyTypeEnum pVal)
  {
    getKeyPtr()->PutType (
      pVal);
  }

public:
  _bstr_t getRelatedTable()
  {
    return getKeyPtr()-> GetRelatedTable();
  }


public:
  void putRelatedTable(
    __in _bstr_t pVal)
  {
    getKeyPtr()->PutRelatedTable (
      pVal);
  }
public:
  ADOX::RuleEnum getUpdateRule()
  {
    return getKeyPtr()->GetUpdateRule();
    }

public:
  void putUpdateRule (
     __in ADOX::RuleEnum pVal)
  {
    getKeyPtr()->PutUpdateRule (
         pVal);
      }
public:
  ADOX::ColumnsPtr getColumns()
  {
    return getKeyPtr()->GetColumns();
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    ADOXEnumNames names;

    const char* type = names.getName(getType());
    _bstr_t reltable = getRelatedTable();
    printf("<Key Name=\"%s\" Type=\"%s\" RelatedTable=\"%s\" />\n", 
      (const char*)name, 
      type,
      (const char*)reltable);
  }

};

}
