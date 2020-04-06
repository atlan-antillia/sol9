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
 *  ADOXColumn.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADOXProperties.h>

namespace SOL {

class ADOXColumn :public ADOObject {

public:
  ADOXColumn()
  {
  }

public:
  ~ADOXColumn()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Column));
  }

public:
  void set(__in ADOX::_ColumnPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }

public:
  ADOX::_ColumnPtr getColumnPtr()
  {
    return(ADOX::_ColumnPtr)getObject();
  }

public:
  _bstr_t getName()
  {
    return getColumnPtr()->GetName();
  }

public:
  void putName(
    __in _bstr_t pVal)
  {
    getColumnPtr()->PutName(pVal);
  }

public:
  // Get printable attributes of the format like;
  // (adFldUnspecified, adFldUnknownUpdatable, adFldIsNullable, adFldMayBeNull)

  long getAttributes(__out _bstr_t& attributes)
  {
    static const ArgT<char> names[]=
    {
      {"adColFixed", ADOX::adColFixed},
      {"adColNullable", ADOX::adColNullable}

    };

    attributes = _bstr_t("(");

    long value = getAttributes();
    bool rc = false;
    for (int i = 0; i<XtNumber(names); i++) {
      //Check value bits

      if (value & names[i].value) {
        if (rc) {
          attributes += _bstr_t(", ");
        }
        attributes += _bstr_t(names[i].name);
        rc = true;
      }
    }
    attributes += _bstr_t(")");

    return value;
  }

public:
  ADOX::ColumnAttributesEnum getAttributes()
  {
    return getColumnPtr()->GetAttributes();
  }

public:
  void putAttributes(
    __in ADOX::ColumnAttributesEnum pVal)
  {
    getColumnPtr()->PutAttributes(pVal);
  }

public:
  long getDefinedSize()
  {
    return getColumnPtr()->GetDefinedSize();
  }

public:
  void putDefinedSize(
    __in long pVal)
  {
    getColumnPtr()->PutDefinedSize(pVal);
  }

public:
  unsigned char getNumericScale()
  {
    return getColumnPtr()->GetNumericScale();
  }

public:
  void putNumericScale(
    __in unsigned char pVal)
  {
    getColumnPtr()->PutNumericScale(pVal);
  }

public:
  long getPrecision()
  {
    return getColumnPtr()->GetPrecision();
  }

public:
  void putPrecision(
    __in long pVal)
  {
    getColumnPtr()->PutPrecision(pVal);
  }

public:
  _bstr_t getRelatedColumn()
  {
    return getColumnPtr()->GetRelatedColumn();
  }

public:
  void putRelatedColumn(__in _bstr_t pVal)
  {
    getColumnPtr()->PutRelatedColumn(
      pVal);
  }

public:
  ADOX::SortOrderEnum getSortOrder()
  {
    return getColumnPtr()->GetSortOrder();
  }

public:    
  void putSortOrder(__in ADOX::SortOrderEnum pVal)
  {
    getColumnPtr()->PutSortOrder(pVal);
  }

public:
  ADOX::DataTypeEnum getType()
  {
    return getColumnPtr()->GetType();
  }

public:
  void putType(__in ADOX::DataTypeEnum pVal)
  {
    getColumnPtr()-> PutType(pVal);
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
    return getColumnPtr()->GetProperties();
  }

public:
  ADOX::_CatalogPtr getParentCatalog()
    {
    return getColumnPtr()->GetParentCatalog();
  }
public:
  void putParentCatalog(
    __in ADOX::_Catalog * ppvObject)
  {
    getColumnPtr()->PutParentCatalog(ppvObject);
  }

public:
  void putRefParentCatalog(
    __in ADOX::_Catalog * ppvObject)
  {
    getColumnPtr()->PutRefParentCatalog(ppvObject);
  }

public:
  void dump()
  {
    _bstr_t name = getName();

    ADOXEnumNames names;
    const char* type = names.getName(getType());
    _bstr_t attrs = "";
    getAttributes(attrs);

    long definedSize = getDefinedSize(); 
    long prec = getPrecision();
  
    printf("<Column  Name=\"%s\" Type=\"%s\" Attributes=\"%s\" DefinedSize=\"%ld\" Precision=\"%ld\" />\n", 
      (const char*)name, 
      type,
      (const char*)attrs,
      definedSize,
      prec);

    //Dump properties of thie column 
    ADOXProperties properties;
    getProperties(properties);
    properties.dump();
  }
};

}
