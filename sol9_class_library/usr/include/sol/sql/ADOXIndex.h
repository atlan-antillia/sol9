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
 *  ADOXIndex.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {

class ADOXIndex : public ADOObject {

public:
  ADOXIndex()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Index));
  }

public:
  void set(__in ADOX::_IndexPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }

public:
  ADOX::_IndexPtr getIndexPtr() 
  {
    return(ADOX::_IndexPtr)getObject();  
  }


public:
  _bstr_t getName()
  {
    return getIndexPtr()->GetName();
  }

public:
  void putName(__in _bstr_t pVal)
  {
    getIndexPtr()->PutName(pVal);
  }

public:

  VARIANT_BOOL getClustered()
  {
    return getIndexPtr()->GetClustered();
  }

public:
  void putClustered(
    __in VARIANT_BOOL pVal)
  {
    getIndexPtr()->PutClustered(pVal);
  }

public:

  ADOX::AllowNullsEnum getIndexNulls()
  {
    return getIndexPtr()->GetIndexNulls();
  }

public:
    
  void putIndexNulls(
    __in ADOX::AllowNullsEnum pVal)
  {
    getIndexPtr()->PutIndexNulls(pVal);
  }

public:

  VARIANT_BOOL getPrimaryKey()
  {
    return getIndexPtr()->GetPrimaryKey();
  }

public:
  
  void putPrimaryKey(
    __in VARIANT_BOOL pVal)
  {
    getIndexPtr()->PutPrimaryKey(pVal);
  }

public:

  VARIANT_BOOL getUnique()
  {
    return getIndexPtr()->GetUnique();
  }

public:
    
  void putUnique(
    __in VARIANT_BOOL pVal)
  {
    getIndexPtr()->PutUnique(pVal);
  }

public:

  ADOX::ColumnsPtr getColumns()
  {
    return getIndexPtr()->GetColumns();
  }

public:    
  ADOX::PropertiesPtr getProperties()
  {
    return getIndexPtr()->GetProperties();
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    ADOXEnumNames names;

    const char* indexNulls = names.getName(getIndexNulls());
    VARIANT_BOOL primaryKey = getPrimaryKey();
    printf("<Index Name=\"%s\" IndexNull=\"%s\" PrimanryKey=\"%d\" />\n", 
      (const char*)name,
      indexNulls,
      primaryKey
      );
  }
};

}
