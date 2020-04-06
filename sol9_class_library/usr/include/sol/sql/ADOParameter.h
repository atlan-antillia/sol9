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
 *  ADOParameter.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/08
// 2009/05/15
// 2009/05/22

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {

class ADOParameter :public ADOObject {

public:
  ADOParameter()
  {
  }


public:
  ~ADOParameter()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Parameter));
  }

public:
  void set(__in ADODB::_ParameterPtr pF) 
  {
    clear();
    setObject((IDispatchPtr)pF);
  }

public:
  ADODB::_ParameterPtr getParameterPtr() 
  {
    return (ADODB::_ParameterPtr)getObject();
  }

public:
    _bstr_t getName() 
  {
    return getParameterPtr()->GetName();
  }

public:
  void putName(__in _bstr_t pbstr)
  {
    getParameterPtr()->PutName(pbstr);
  }

public:
  _variant_t getValue()
  {
    return getParameterPtr()->GetValue();
  }

public:
  void putValue(__in const _variant_t & pvar)
  {

    getParameterPtr()->PutValue(pvar);
  }

public:
  ADODB::DataTypeEnum getType()
  {
    return getParameterPtr()->GetType();
  }

public:
  /**
   * psDataType takes one of the following enum values:
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
  void putType(__in ADODB::DataTypeEnum psDataType)
  {
    getParameterPtr()->PutType(psDataType);
  }
/*
public:
  const char* getTypeName()
  {
    ADODB::DataTypeEnum type = getType();
    static Arg types[] = {
      {"Empty",      ADODB::adEmpty},
      {"TineyInt",    ADODB::adTinyInt},
      {"SmallInt",    ADODB::adSmallInt},
      {"Integer",      ADODB::adInteger},
      {"BigInt",      ADODB::adBigInt},
      {"UnsignedTinyInt", ADODB::adUnsignedTinyInt},
      {"UnsignedSmallInt",ADODB::adUnsignedSmallInt},
      {"UnsignedIn",    ADODB::adUnsignedInt},
      {"UnsignedBigInt",  ADODB::adUnsignedBigInt},
      {"Single",      ADODB::adSingle},
      {"Double",      ADODB::adDouble},
      {"Currency",    ADODB::adCurrency},
      {"Decimal",      ADODB::adDecimal},
      {"Numeric",      ADODB::adNumeric},
      {"Boolean",      ADODB::adBoolean},
      {"Error",      ADODB::adError},
      {"UserDefined",    ADODB::adUserDefined},
      {"Variant",      ADODB::adVariant},
      {"IDispatch",    ADODB::adIDispatch},
      {"IUnknown",    ADODB::adIUnknown},
      {"GUID",      ADODB::adGUID},
      {"Date",      ADODB::adDate},
      {"DBDate",      ADODB::adDBDate},
      {"DBTime",      ADODB::adDBTime},
      {"DBTimeStamp",    ADODB::adDBTimeStamp},
      {"BSTR",      ADODB::adBSTR},
      {"Char",      ADODB::adChar},
      {"VarChar",      ADODB::adVarChar},
      {"LongVarChar",    ADODB::adLongVarChar},
      {"WChar",      ADODB::adWChar},
      {"VarWChar",    ADODB::adVarWChar},
      {"LongVarWChar",  ADODB::adLongVarWChar},
      {"Binary",      ADODB::adBinary},
      {"VarBinary",    ADODB::adVarBinary},
      {"LongVarBinary",  ADODB::adLongVarBinary},
      {"Chapter",      ADODB::adChapter},
      {"FileTime",    ADODB::adFileTime},
      {"PropVariant",    ADODB::adPropVariant},
      {"VarNumeric",    ADODB::adVarNumeric},
      {"Array",      ADODB::adArray}
    };
    int count = XtNumber(types);
    const char* name = "";
    for(int i = 0; i<count; i++) {
      if (types[i].value == type) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }
*/
public:
  /**
   plParamDirection takes one of the following enum values.
  ParameterDirectionEnum
  {
    adParamUnknown = 0,
    adParamInput = 1,
    adParamOutput = 2,
    adParamInputOutput = 3,
    adParamReturnValue = 4
  };
   */
  void putDirection(__in ADODB::ParameterDirectionEnum plParmDirection)
  {
    getParameterPtr()->PutDirection(plParmDirection);
  }

public:
  ADODB::ParameterDirectionEnum getDirection()
  {
    return getParameterPtr()->GetDirection();
  }

public:
    void putPrecision (__in unsigned char pbPrecision)
  {    
    getParameterPtr()->PutPrecision(pbPrecision);
  }

public:
    unsigned char getPrecision()
  {
    return getParameterPtr()->GetPrecision();
  }

public:
    void putNumericScale(__in unsigned char pbScale)
  {    
    getParameterPtr()->PutNumericScale(pbScale);
  }

public:
    unsigned char getNumericScale()
  {
    return getParameterPtr()->GetNumericScale();
  }

public:
    void putSize(__in long pl) //ADODB::ADO_LONGPTR pl)
  {
    getParameterPtr()->PutSize(pl);
  }

public:
  //ADODB::ADO_LONGPTR 
  long getSize()
  {
    return getParameterPtr()->GetSize();
  }

public:
   HRESULT appendChunk(__in const _variant_t& val)
  {
    HRESULT hr = getParameterPtr()->AppendChunk(val);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  long getAttributes() 
  {
    return getParameterPtr()->GetAttributes();
  }

public:

  void putAttributes(__in long plParmAttribs)
  {
    getParameterPtr()->PutAttributes(plParmAttribs);
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    _variant_t value = getValue();
    COMTypeConverter converter;
    _bstr_t string = "";
    converter.toString(value, string);
    long size = getSize();
    ADOEnumNames names;
    const char* type      = names.getName(getType());
    const char* direction = names.getName(getDirection());

    printf("Parameter: Name=%S, Value=%S, Size=%ld, Type=%s, Direction=%s\n",
      (const wchar_t*)name,
      (const wchar_t*)string,
      size,
      type,
      direction);
  }
};

}
