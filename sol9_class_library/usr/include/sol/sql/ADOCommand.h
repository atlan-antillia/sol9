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
 *  ADOCommand.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/11
// 2009/05/15
// 2009/05/22 Added a helpler method appendToParameters to create an ADOParameter object
//    and append it to ADOParameters of ADOCommand object.
// 2009/05/22 Added a method enablePrepared(bool)

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADORecordset.h>
#include <sol/sql/ADOParameter.h>
#include <sol/sql/ADOParameters.h>


namespace SOL {

class ADOCommand :public ADOObject {

public:
  /**
   * Constructor
   */
  ADOCommand()
  {
  }

public:
  ~ADOCommand()
  {
  }
  
public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Command));
  }

public:
  void set(ADODB::_CommandPtr pC) 
  {
    setObject((IDispatchPtr)pC);
  }

public:
  ADODB::_CommandPtr getCommandPtr() 
  {
    return (ADODB::_CommandPtr)getObject();
  }

public:
  ADODB::_ConnectionPtr getActiveConnection()
  {
    return getCommandPtr()->GetActiveConnection();
  }

public:
  void putRefActiveConnection(__in ADODB::_Connection* ppvObject)
  {
    getCommandPtr()->PutRefActiveConnection(ppvObject);
  }


public:

  void putActiveConnection(__in const _variant_t& ppvObject)
  {
    getCommandPtr()->PutActiveConnection(ppvObject);
  }

public:

  void putActiveConnection(__in ADODB::_ConnectionPtr activeConnection)
  {
    _variant_t varConnection((IDispatch*)activeConnection);
    getCommandPtr()->PutActiveConnection(varConnection);
  }

public:

  _bstr_t getCommandText()
  {
    return getCommandPtr()->GetCommandText();
  }

public:

  void putCommandText(__in _bstr_t pbstr)
  {
    getCommandPtr()->PutCommandText(pbstr);
  }

public:

  long getCommandTimeout()
  {
    return getCommandPtr()->GetCommandTimeout();
  }

public:
  void putCommandTimeout(__in long pl)
  {
    getCommandPtr()->PutCommandTimeout(pl);
  }

public:

  VARIANT_BOOL getPrepared()
  {
    return getCommandPtr()->GetPrepared();
  }

public:
  //2008/05/23
  bool enablePrepared()
  {
    bool rc = false;
    VARIANT_BOOL prepared = getCommandPtr()->GetPrepared();
    if (prepared == VARIANT_TRUE) {
      rc = true;
    }
    return rc;
  }

public:
  //2009/05/22
  void enablePrepared(__in bool flag)
  {
    VARIANT_BOOL prepared = VARIANT_FALSE;
    if (flag) {
      prepared = VARIANT_TRUE;
    }
    getCommandPtr()->PutPrepared(prepared);
  }

public:

  void putPrepared(__in VARIANT_BOOL pfPrepared)
  {
    getCommandPtr()->PutPrepared(pfPrepared);
  }

public:
  /**
   1 Execute commandText property put by putCommandText method.
   2 Return an instance of ADORecordset to the first parameter recordset.
   3 Return the number of records affected by this operation.

  option takes one of the following enum.

  CommandTypeEnum
  {
  adCmdUnspecified 
  adCmdText
  adCmdTable
  adCmdStoredProc
  adCmdUnknown (default)
  adCmdFile
  adCmdTableDirect
  };
   */
  //2009/05/17 
  long execute(
    __out ADORecordset& recordset,
    __in_opt variant_t* parameters=NULL,
    __in_opt long options =ADODB::adCmdUnspecified)

  {
    long rc = -1L;
    _variant_t varAffected(0L);

    ADODB::_RecordsetPtr recset = execute(
      varAffected,
      parameters,
      options);
    if (recset) {
      recordset.set(recset);
      rc = (long)varAffected;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }


public:
  /**
  option takes one of the following enum.

  CommandTypeEnum
  {
  adCmdUnspecified 
  adCmdText
  adCmdTable
  adCmdStoredProc
  adCmdUnknown (default)
  adCmdFile
  adCmdTableDirect
  };
   */
  bool execute(
    __out _variant_t& recordsAffected,
    __out ADORecordset& recordset,
    __in_opt variant_t* parameters=NULL,
    __in_opt long options =ADODB::adCmdUnspecified)

  {
    bool rc = false;

    ADODB::_RecordsetPtr recset = execute(
      recordsAffected,
      parameters,
      options);
    if (recset) {
      recordset.set(recset);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }


public:
  ADODB::_RecordsetPtr execute(
    __out _variant_t& recordsAffected,
    __in variant_t* parameters =NULL,
    __in long options = ADODB::adCmdUnspecified)
  {
    return getCommandPtr()->Execute(
      &recordsAffected,
      (VARIANT*)parameters,
      options);
  }

public:
  /**
  type takes one of the following values.

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

  parameter takes one of the following values.

  ParameterDirectionEnum
  {
    adParamUnknown = 0,
    adParamInput = 1,
    adParamOutput = 2,
    adParamInputOutput = 3,
    adParamReturnValue = 4
  };
   */
  bool createParameter(
    __in _bstr_t name,
    __in ADODB::DataTypeEnum type,
    __in ADODB::ParameterDirectionEnum direction,
    __in long size, //ADODB::ADO_LONGPTR size,
    __in const _variant_t& value,//vtMissing,
    __out ADOParameter& parameter
    )
  {
    bool rc = false;
    ADODB::_ParameterPtr pParam = createParameter(
        name,
        type,
        direction,
        size,
        value);
    if (pParam) {
      parameter.set(pParam);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:

  ADODB::_ParameterPtr createParameter(
    __in _bstr_t name,
    __in ADODB::DataTypeEnum type,
    __in ADODB::ParameterDirectionEnum direction,
    __in long size, //ADODB::ADO_LONGPTR size,
    __in_opt const _variant_t& value = vtMissing)
  {
    return getCommandPtr()->CreateParameter(
        name,
        type,
        direction,
        size,
        value);
  }

public:
  /**
   * Create an ADOParameter Object from arguments of appendToParameters
   * and apppend it to ADOParameters of ADOCommand.
   */
  //2009/05/22
  //2009/05/27
  bool appendParameter(
    __in _bstr_t name,
    __in ADODB::DataTypeEnum type,
    __in ADODB::ParameterDirectionEnum direction,
    __in long size, //ADODB::ADO_LONGPTR size,
    __in const _variant_t& value
    //__out ADOParameter& parameter
    )
  {
    bool rc = false;
    ADODB::_ParameterPtr pParam = createParameter(
        name,
        type,
        direction,
        size,
        value);
    if (pParam) {
      //If succeeded to create a Parameter, 
      // then append it to an ADOParameters obect of this ADOCommand.
      ADOParameters parameters;
      if (getParameters(parameters)) {
        IDispatch* iobject = (IDispatch*)pParam;
        if (parameters.append(iobject)) {
          rc = true;
        }
      }
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  bool getParameters(__out ADOParameters& parameters)
  {
    bool rc = false;
    ADODB::ParametersPtr pParams = getParameters();
    if (pParams) {
      parameters.set(pParams);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;  
  }

public:
  // 2009/05/22
  bool appendParameter(ADOParameter& param)
  {
    bool rc = false;

    ADOParameters parameters;
    if (getParameters(parameters)) {
      IDispatch* iobject = (IDispatch*)param.getParameterPtr();
      if (parameters.append(iobject)) {
        rc = true;
      }
    }
    return rc;

  }

public:
  ADODB::ParametersPtr getParameters()
  {
    return getCommandPtr()->GetParameters();
  }

public:
  /**
  CommandTypeEnum
  {
    adCmdUnspecified = -1,
    adCmdUnknown = 8,
    adCmdText = 1,
    adCmdTable = 2,
    adCmdStoredProc = 4,
    adCmdFile = 256,
    adCmdTableDirect = 512
  };
  */
  void putCommandType(ADODB::CommandTypeEnum plCmdType)
  {
    getCommandPtr()->PutCommandType(plCmdType);
  }

public:

  ADODB::CommandTypeEnum getCommandType()
  {
    return getCommandPtr()->GetCommandType();
  }

public:

  _bstr_t getName()
  {
    return getCommandPtr()->GetName();
  }


public:
  void putName(_bstr_t pbstrName)
  {
    getCommandPtr()->PutName(pbstrName);
  }

public:
  long getState()
  {
    return getCommandPtr()->GetState();
  }

public:
  HRESULT cancel()
  {
    HRESULT hr = getCommandPtr()->Cancel();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  void putRefCommandStream(IUnknown* pvStream)
  {
    getCommandPtr()->PutRefCommandStream(pvStream);
  }

public:
  _variant_t getCommandStream()
  {
    return getCommandPtr()->GetCommandStream();
  }

public:
  void putDialect(_bstr_t pbstrDialect)
  {
    getCommandPtr()->PutDialect(pbstrDialect);
  }

public:
  _bstr_t getDialect()
  {
    return getCommandPtr()->GetDialect();
  }


public:
  void putNamedParameters(VARIANT_BOOL pfNamedParameters)
  {
    getCommandPtr()->PutNamedParameters(pfNamedParameters);
  }

public:
  VARIANT_BOOL getNamedParameters()
  {
    return getCommandPtr()->GetNamedParameters();
  }

public:
  //2009/05/15
  //Return all fields list for a table of tableName to fields. 
  bool getFields(
    __in _bstr_t tableName,
    __in ADODB::_ConnectionPtr activeConnection,
    __out ADOFields& fields)
  {
    bool rc = false;
    
    putActiveConnection(activeConnection);
    putCommandText(tableName);
    putCommandType(ADODB::adCmdTable);
    putCommandTimeout(20);

    _variant_t recordsAffected(0L);
    ADORecordset recordset;
    if (execute(recordsAffected, recordset, NULL, 
      //ADODB::adOpenKeyset)) {
      ADODB::adCmdTable)) {      
      //ADOFields fields;
      if (recordset.getFields(fields)) {
        //long count = fields.getCount();
        //printf("OK, fields.getCount(): %d\n", count);
        rc = true;
      }
    }
    return rc;
  }
};

}
