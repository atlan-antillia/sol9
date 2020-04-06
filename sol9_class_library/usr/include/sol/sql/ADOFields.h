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
 *  ADOFields.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/12

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOField.h>


namespace SOL {

class ADOFields :public ADOCollection {

public:
  ADOFields()
  {
  }

public:
  ~ADOFields()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Fields));
  }

public:
  void set(ADODB::FieldsPtr pFs)
  {
    setObject((IDispatchPtr)pFs);
  }

public:
  ADODB::FieldsPtr getFieldsPtr()
  {
    return (ADODB::FieldsPtr)getObject();
  }

public:
  // 2009/05/12
  bool getItem(
          __in long index, 
      __out ADOField& field)
  {
    return getItem(_variant_t(index), field);
  }
  
public:
  // 2009/05/12
  bool getItem(
          __in const _variant_t& index, 
      __out ADOField& field)
  {
    bool rc = false;
    ADODB::FieldPtr pField = getItem(index);
    if (pField) {
      field.set(pField);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);

    }
    return rc;
  }
  
public:

  ADODB::FieldPtr getItem(
          __in const _variant_t& index)
  {
    return getFieldsPtr()->GetItem (index);
  }

public:
    HRESULT remove(
        __in const _variant_t & index)
  {
    HRESULT hr = getFieldsPtr()->Delete(index);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
    HRESULT append(
    __in _bstr_t name,
    __in ADODB::DataTypeEnum type,
    __in ADODB::ADO_LONGPTR definedSize,
    __in ADODB::FieldAttributeEnum attrib,
    __in_opt const _variant_t& fieldValue = vtMissing)
  {
    HRESULT hr = getFieldsPtr()->Append(
            name,
             type,
      (long)definedSize,
             attrib,
            fieldValue);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT update()
  {
    HRESULT hr = getFieldsPtr()->Update();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT resync(ADODB::ResyncEnum resyncValues)
  {
    HRESULT hr = getFieldsPtr()->Resync(resyncValues);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT cancelUpdate()
  {
    HRESULT hr = getFieldsPtr()->CancelUpdate();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  long getCount()
  {
    return getFieldsPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getFieldsPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getFieldsPtr()->_NewEnum();
  }

public:
  // 2009/05/26
  long getNameIndex(__in _bstr_t& name)
  {
    long index = -1L;  //Not found
    long count = getCount();
    const wchar_t* wname = (const wchar_t*)name;

    for (long i = 0L; i<count; i++) {
      ADOField field;
      getItem(_variant_t(i), field);
      _bstr_t n = field.getName();
      const wchar_t* wn = (const wchar_t*)n;
      if (wname && wn && _wcsicmp(wname, wn) == 0) {
        index = i;  
        break;
      }
    }
    if (index == -1L) {
      throw Exception(E_FAIL, "Not found index for fieldName=\"%S\": %s",
          (const wchar_t*)name, __FUNCTION__);
    }
    return index;  
  }

public:
  // 2009/05/23
  void dump()
  {
    long count = getCount();
    printf("Fields:\n");
    for (long i = 0L; i<count; i++) {
      ADOField field;
      getItem(_variant_t(i), field);
      field.dump();
    }
  }

};

}
