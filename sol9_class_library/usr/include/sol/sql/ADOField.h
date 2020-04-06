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
 *  ADOField.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/05/15
// 2009/05/26 Added dump() method
// 2009/05/28 Added long getAttributes(__out _bstr_t& attributes) method

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/ArgT.h>


namespace SOL {

class ADOField :public ADOObject {

public:
  /**
   * Constructor
   */
  ADOField()
  {
  }

public:
  /**
   * Destructor
   */
  ~ADOField()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Field));
  }

public:
  void set(__in ADODB::FieldPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }


public:
  ADODB::FieldPtr getFieldPtr()
  {
    return (ADODB::FieldPtr)getObject();
  }


public:
  ADODB::ADO_LONGPTR getActualSize() 
  {
    return getFieldPtr()->GetActualSize();
  }

public:
  // Return a or some combinations of (LONG_PTR)ADODB::FieldAttributeEnum type
  long getAttributes() 
  {
    return getFieldPtr()->GetAttributes();
  }

public:
  // Get printable attributes of the format like and it to the parameter attribute.
  // (adFldUnspecified, adFldUnknownUpdatable, adFldIsNullable, adFldMayBeNull)
  // 2009/05/28

  long getAttributes(__out _bstr_t& attributes)
  {
    static const ArgT<char> names[]=
    {
      {"adFldUnspecified", (LONG_PTR)ADODB::adFldUnspecified},
      {"adFldMayDefer", (LONG_PTR)ADODB::adFldMayDefer},
      {"adFldUpdatable", (LONG_PTR)ADODB::adFldUpdatable},
      {"adFldUnknownUpdatable", (LONG_PTR)ADODB::adFldUnknownUpdatable},
      {"adFldFixed", (LONG_PTR)ADODB::adFldFixed},
      {"adFldIsNullable", (LONG_PTR)ADODB::adFldIsNullable},
      {"adFldMayBeNull", (LONG_PTR)ADODB::adFldMayBeNull},
      {"adFldLong", (LONG_PTR)ADODB::adFldLong},
      {"adFldRowID", (LONG_PTR)ADODB::adFldRowID},
      {"adFldRowVersion", (LONG_PTR)ADODB::adFldRowVersion},
      {"adFldCacheDeferred", (LONG_PTR)ADODB::adFldCacheDeferred},
      {"adFldIsChapter", (LONG_PTR)ADODB::adFldIsChapter},
      {"adFldNegativeScale", (LONG_PTR)ADODB::adFldNegativeScale},
      {"adFldKeyColumn", (LONG_PTR)ADODB::adFldKeyColumn},
      {"adFldIsRowURL", (LONG_PTR)ADODB::adFldIsRowURL},
      {"adFldIsDefaultStream", (LONG_PTR)ADODB::adFldIsDefaultStream},
      {"adFldIsCollection", (LONG_PTR)ADODB::adFldIsCollection}
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
  ADODB::ADO_LONGPTR getDefinedSize()
  {
    return getFieldPtr()->GetDefinedSize();
  }

public:
  _bstr_t getName() 
  {
    return getFieldPtr()->GetName();
  }

public:
  /**
  This getType() method returns the following enum.

  DataTypeEnum
  {
    adEmpty = 0,
    adTinyInt = 16,
    adSmallInt = 2,
    adInteger = 3,
    adBigInt = 20,
    adUnsignedTinyInt = 17,
    adUnsignedSmallInt = 18,
    adUnsignedInt = 19,
    adUnsignedBigInt = 21,
    adSingle = 4,
    adDouble = 5,
    adCurrency = 6,
    adDecimal = 14,
    adNumeric = 131,
    adBoolean = 11,
    adError = 10,
    adUserDefined = 132,
    adVariant = 12,
    adIDispatch = 9,
    adIUnknown = 13,
    adGUID = 72,
    adDate = 7,
    adDBDate = 133,
    adDBTime = 134,
    adDBTimeStamp = 135,
    adBSTR = 8,
    adChar = 129,
    adVarChar = 200,
    adLongVarChar = 201,
    adWChar = 130,
    adVarWChar = 202,
    adLongVarWChar = 203,
    adBinary = 128,
    adVarBinary = 204,
    adLongVarBinary = 205,
    adChapter = 136,
    adFileTime = 64,
    adPropVariant = 138,
    adVarNumeric = 139,
    adArray = 8192
  };
   */
  ADODB::DataTypeEnum getType()
  {
    return getFieldPtr()->GetType();
  }



public:
  _variant_t getValue() 
  {
    return getFieldPtr()->GetValue();
  }

public:
  void putValue(__in const _variant_t & pvar)
  {
    getFieldPtr()->PutValue(pvar);
  }

public:
  unsigned char getPrecision()
  {
    return getFieldPtr()->GetPrecision();
  }

public:
  unsigned char getNumericScale()
  {
    return getFieldPtr()->GetNumericScale();
  }


public:
  HRESULT appendChunk(__in const _variant_t & data)
  {
    HRESULT hr = getFieldPtr()->AppendChunk(data);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  _variant_t getChunk(long length)
  {
    return getFieldPtr()->GetChunk(length);
  }

public:
  _variant_t getOriginalValue()
  {
    return getFieldPtr()->GetOriginalValue();
  }

public:
  _variant_t getUnderlyingValue()
  {
    return getFieldPtr()->GetUnderlyingValue();
  }

public:
  IUnknownPtr getDataFormat()
  {
    return getFieldPtr()->GetDataFormat();

  }

public:
  void putRefDataFormat(IUnknown * ppiDF)
  {
    getFieldPtr()->PutRefDataFormat(ppiDF);
  }

public:
  void putPrecision (unsigned char pbPrecision)
  {
    getFieldPtr()->PutPrecision (pbPrecision );
  }

public:
  void putNumericScale (unsigned char pbNumericScale)
  {
    getFieldPtr()->PutNumericScale(pbNumericScale);
  }

public:
  void putType(ADODB::DataTypeEnum pDataType)
  {
    getFieldPtr()->PutType (pDataType);
  }

public:
  void putDefinedSize(ADODB::ADO_LONGPTR pl)
  {

    getFieldPtr()->PutDefinedSize((long)pl);
  }

public:
  void putAttributes(long pl)
  {
    getFieldPtr()->PutAttributes(pl);
  }

public:
   
  long getStatus() 
  {
    return getFieldPtr()->GetStatus();
  }

public:
  // 2009/05/26
  void dump()
  {
    _bstr_t name = getName();
    ADOEnumNames names;
    const char* type = names.getName(getType());
    
    printf("Field:Name=%S, Type=%s\n",
      (const wchar_t*)name, type);

  }
};

}
