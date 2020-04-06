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
 *  ADORecord.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/05/15

#pragma once

#include <sol/sql/ADOObject.h>


namespace SOL {

class ADORecord :public ADOObject {

public:
  ADORecord()
  {
  }

public:
  ~ADORecord()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Record));
  }

public:
  void set(__in ADODB::_RecordPtr pRec)
  {
    setObject((IDispatchPtr)pRec);
  }

public:
  ADODB::_RecordPtr getRecordPtr()
  {
    return (ADODB::_RecordPtr)getObject();
  }

public: 
  _variant_t getActiveConnection ()
  {
    return getRecordPtr()->GetActiveConnection();
  }

public:
  void putActiveConnection(__in _bstr_t pvar) 
  {
    getRecordPtr()->PutActiveConnection (pvar);
  }

public:
  void putRefActiveConnection(__in ADODB::_Connection* pvar)
  {
    getRecordPtr()->PutRefActiveConnection (pvar);
  }

public:
  ADODB::ObjectStateEnum getState()
  {
    return getRecordPtr()->GetState();
  }

public:
  _variant_t getSource() {
    return getRecordPtr()->GetSource();
  }

public:
  void putSource (__in _bstr_t pvar)
  {
    getRecordPtr()->PutSource(pvar);
  }

public:
  void putRefSource(__in IDispatch * pvar)
  {    
    getRecordPtr()->PutRefSource(pvar);
  }

public:
  ADODB::ConnectModeEnum getMode() 
  {
    return getRecordPtr()->GetMode();
  }
public:
  void putMode(__in ADODB::ConnectModeEnum pMode)
  {
       getRecordPtr()->PutMode(pMode);
  }

public:
  _bstr_t getParentURL() 
  {
    return getRecordPtr()->GetParentURL();
  }

public:
    _bstr_t moveRecord(
    _bstr_t source,
    _bstr_t destination,
    _bstr_t userName,
    _bstr_t password,
    ADODB::MoveRecordOptionsEnum options,
    VARIANT_BOOL async )
  {
    return getRecordPtr()->MoveRecord (
      source,
      destination,
      userName,
      password,
      options,
             async );
  }

public:
  _bstr_t copyRecord(
    _bstr_t source,
    _bstr_t destination,
    _bstr_t userName,
    _bstr_t password,
    ADODB::CopyRecordOptionsEnum options,
    VARIANT_BOOL async)
  {

    return getRecordPtr()->CopyRecord(
      source,
      destination,
      userName,
            password,
            options,
            async);
  }

public:
  
  HRESULT deleteRecord(
          _bstr_t source,  
          VARIANT_BOOL async)
  {
    HRESULT hr = getRecordPtr()-> DeleteRecord (
        source,
        async);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }


public:
  HRESULT open(
    const _variant_t& source,
    const _variant_t& activeConnection,
    ADODB::ConnectModeEnum mode,
    ADODB::RecordCreateOptionsEnum createOptions,
    ADODB::RecordOpenOptionsEnum options,
    _bstr_t userName,
    _bstr_t password )
  {
    HRESULT hr = getRecordPtr()->Open(
            source,
            activeConnection,
            mode,
             createOptions,
            options,
            userName,
            password);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  void close() 
  {
    try {
      getRecordPtr()->Close();
    } catch (...) {

    }
    clear();
  }

public:
  ADODB::FieldsPtr getFields() 
  {
    return getRecordPtr()->GetFields();
  }

public:
  ADODB::RecordTypeEnum getRecordType()
  {
    return getRecordPtr()->GetRecordType();
  }

public:
  ADODB::_RecordsetPtr getChildren() 
  {
    return getRecordPtr()->GetChildren();
  }

public:

  HRESULT cancel() 
  {
    HRESULT hr = getRecordPtr()->Cancel();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

};

}
