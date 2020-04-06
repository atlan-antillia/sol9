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
 *  ADORecordset.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/05/15

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADOFields.h>

namespace SOL {

class ADORecordset: public ADOObject {

public:
  /**
   *
   */
  ADORecordset()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Recordset));
  }

public:
  ~ADORecordset() 
  {
    close();
  }


public:
  /**
   *
   */
  void set(__in ADODB::_RecordsetPtr pRec)
  {
    close();
    setObject((IDispatchPtr)pRec);
  }

public:
  ADODB::_RecordsetPtr getRecordsetPtr()
  {
    return (ADODB::_RecordsetPtr)getObject();
  }

public:
  void close() 
  {
    try {
      getRecordsetPtr()->Close();
    } catch (...) {
    
    }
    clear();
  }


public: 
  /**
   This returns the following enum.

  PositionEnum
  {
    adPosUnknown = -1,
    adPosBOF = -2,
    adPosEOF = -3
  };
   */
  ADODB::PositionEnum_Param getAbsolutePosition()
  {
    return getRecordsetPtr()->GetAbsolutePosition();
  }

public:
  //2011/09/08 Changed PositionEnum_Param to PositionEnum 
  void putAbsolutePosition(__in ADODB::PositionEnum pl)
  {
    getRecordsetPtr()->PutAbsolutePosition(pl);
  }

public:
  void putRefActiveConnection(IDispatch * pvar)
  {
    getRecordsetPtr()->PutRefActiveConnection(pvar);
  }

public:
  void putActiveConnection(__in const _variant_t& pvar)
  {
    getRecordsetPtr()->PutActiveConnection(pvar);
  }

public:
  _variant_t getActiveConnection()
  {
    return getRecordsetPtr()->GetActiveConnection();
  }

public:
  VARIANT_BOOL getBOF()
  {
    return getRecordsetPtr()->GetBOF();
  }

public:
  _variant_t getBookmark()
  {
    return getRecordsetPtr()->GetBookmark();
  }

public:
  void putBookmark(__in const _variant_t & pvBookmark)
  {
    getRecordsetPtr()->PutBookmark(pvBookmark);
  }

public:
  long getCacheSize()
  {
    return getRecordsetPtr()->GetCacheSize();
  }

public:
  void putCacheSize(__in long pl)
  {
    getRecordsetPtr()->PutCacheSize( pl);
  }

public:
  /**
  This returns the following enum.

  CursorTypeEnum
  {
    adOpenUnspecified = -1,
    adOpenForwardOnly = 0,
    adOpenKeyset = 1,
    adOpenDynamic = 2,
    adOpenStatic = 3
  };
   */
  ADODB::CursorTypeEnum getCursorType()
  {
    return getRecordsetPtr()->GetCursorType();
  }

public:
  void putCursorType(__in ADODB::CursorTypeEnum plCursorType)
  {
    getRecordsetPtr()->PutCursorType(plCursorType);
  }

public:
  VARIANT_BOOL getadoEOF()
  {
    return getRecordsetPtr()->GetadoEOF();
  }

public:
  // 2009/05/12
  bool getFields(__out ADOFields& fields)
  {
    bool rc = false;

    ADODB::FieldsPtr pFields = getFields();
    if (pFields) {
      fields.set(pFields);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADODB::FieldsPtr getFields()
  {
    return getRecordsetPtr()->GetFields();
  }

public:
  /**
  This returns the following enum.

  LockTypeEnum
  {
    adLockUnspecified = -1,
    adLockReadOnly = 1,
    adLockPessimistic = 2,
    adLockOptimistic = 3,
    adLockBatchOptimistic = 4
  };
   */
  ADODB::LockTypeEnum getLockType()
  {
    return getRecordsetPtr()->GetLockType();
  }

public:
  void putLockType(__in ADODB::LockTypeEnum plLockType)
  {
    getRecordsetPtr()->PutLockType(plLockType);
  }

public:
  //ADODB::ADO_LONGPTR 
  long getMaxRecords()
  {
    return getRecordsetPtr()->GetMaxRecords();
  }

public:
  void putMaxRecords(__in ADODB::ADO_LONGPTR plMaxRecords)
  {
    getRecordsetPtr()->PutMaxRecords((long) plMaxRecords);
  }

public:
  //ADODB::ADO_LONGPTR 
  long getRecordCount()
  {
    return getRecordsetPtr()->GetRecordCount();
  }

public:
  void putRefSource(__in IDispatch* pvSource)
  {
    getRecordsetPtr()->PutRefSource(pvSource);
  }

public:
  void putSource(__in _bstr_t pvSource)
  {
    getRecordsetPtr()->PutSource(pvSource);
  }

public:
  _variant_t getSource()
  {
    return getRecordsetPtr()->GetSource();
  }

public:
  HRESULT addNew(
          __in_opt const _variant_t& fieldList = vtMissing,
          __in_opt const _variant_t& values = vtMissing)
  {
    HRESULT hr  = getRecordsetPtr()->AddNew(
            fieldList,
            values);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT cancelUpdate()
  {
    HRESULT hr = getRecordsetPtr()->CancelUpdate();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  /**
  affectRecords takes one of the following enum values.
  AffectEnum
  {
    adAffectCurrent = 1,
    adAffectGroup = 2,
    adAffectAll = 3,
    adAffectAllChapters = 4
  };
   */
  HRESULT remove(__in ADODB::AffectEnum affectRecords)
  {
    HRESULT hr = getRecordsetPtr()->Delete(affectRecords);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  _variant_t getRows(
    __in long rows,
    __in_opt const _variant_t& start = vtMissing,
    __in_opt const _variant_t& fields = vtMissing)
  {
    return getRecordsetPtr()->GetRows(
      rows,
      start,
      fields);
  }

public:
  HRESULT move(
    __in long numRecords,//ADODB::ADO_LONGPTR numRecords,
    __in_opt const _variant_t& start = vtMissing)
  {
    HRESULT hr = getRecordsetPtr()->Move(
        numRecords,
        start);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT moveNext()
  {
    HRESULT hr = getRecordsetPtr()->MoveNext();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT movePrevious()
  {
    HRESULT hr = getRecordsetPtr()->MovePrevious();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT moveFirst()
  {
    HRESULT hr = getRecordsetPtr()->MoveFirst();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT moveLast()
  {
    HRESULT hr = getRecordsetPtr()->MoveLast();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  /**
   * Open a source on an activeConnection with specified parameters.
   *
   * @param cursorType This can take one of the following enum.

  CursorTypeEnum
  {
    adOpenUnspecified = -1,
    adOpenForwardOnly = 0,
    adOpenKeyset = 1,
    adOpenDynamic = 2,
    adOpenStatic = 3
  };

     @param lockType This can take one of the following enum.

  LockTypeEnum
  {
    adLockUnspecified = -1,
    adLockReadOnly = 1,
    adLockPessimistic = 2,
    adLockOptimistic = 3,
    adLockBatchOptimistic = 4
  };

   @param options This can take one of some combinations of the following enum.

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

  HRESULT open(
    __in const _variant_t& source,
    __in const _variant_t& activeConnection,
    __in_opt ADODB::CursorTypeEnum cursorType=ADODB::adOpenForwardOnly,
    __in_opt ADODB::LockTypeEnum lockType= ADODB::adLockReadOnly,
    __in_opt long options=ADODB::adCmdUnspecified )
  {
    HRESULT hr = getRecordsetPtr()->Open(
        source,
        activeConnection,
        cursorType,
        lockType,
        options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT open(
    __in const _variant_t& source,
    __in ADODB::_ConnectionPtr activeConnection,
    __in_opt  ADODB::CursorTypeEnum cursorType=ADODB::adOpenForwardOnly,
    __in_opt ADODB::LockTypeEnum lockType = ADODB::adLockReadOnly,
    __in_opt long options=ADODB::adCmdUnspecified)
  {
    _variant_t varConnection((IDispatch*)activeConnection);

    HRESULT hr = getRecordsetPtr()->Open(
        source,
        varConnection,
        cursorType,
        lockType,
        options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }


public:
  HRESULT requery(long options)
  {
    HRESULT hr = getRecordsetPtr()->Requery(options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT update(
    __in_opt const _variant_t& fields = vtMissing,
    __in_opt const _variant_t& values = vtMissing)
  {
    HRESULT hr = getRecordsetPtr()->Update(
      fields,
      values);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  ADODB::PositionEnum_Param getAbsolutePage()
  {
    return getRecordsetPtr()->GetAbsolutePage();
  }

public:
  //2011/09/08 Changed PositionEnum_Param to PositionEnum 
  void putAbsolutePage(__in ADODB::PositionEnum pl)
  {
    getRecordsetPtr()->PutAbsolutePage(pl);
  }

public:
  /**
  This returns the following enum.

  EditModeEnum
  {
    adEditNone = 0,
    adEditInProgress = 1,
    adEditAdd = 2,
    adEditDelete = 4
  };
   */
  ADODB::EditModeEnum getEditMode()
  {
    return getRecordsetPtr()->GetEditMode();
  }

public:
  _variant_t getFilter()
  {
    return getRecordsetPtr()->GetFilter();
  }

public:
  void putFilter(__in const _variant_t& criteria)
  {
    getRecordsetPtr()->PutFilter(criteria);
  }

public:
  ADODB::ADO_LONGPTR getPageCount()
  {
    return getRecordsetPtr()->GetPageCount();
  }

public:
  long getPageSize()
  {
    return getRecordsetPtr()->GetPageSize();
  }

public:
  void putPageSize(__in long pl)
  {
    getRecordsetPtr()->PutPageSize(pl);
  }

public:
  _bstr_t getSort()
  {
    return getRecordsetPtr()->GetSort();
  }

public:
  void putSort(_bstr_t criteria)
  {
    getRecordsetPtr()->PutSort(criteria);
  }

public:
  long getStatus()
  {
    return getRecordsetPtr()->GetStatus();
  }

public:
  long getState()
  {
    return getRecordsetPtr()->GetState();
  }

public:
  HRESULT updateBatch(__in ADODB::AffectEnum affectRecords)
  {
    HRESULT hr = getRecordsetPtr()->UpdateBatch(affectRecords);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT cancelBatch(__in ADODB::AffectEnum affectRecords)
  {
    HRESULT hr = getRecordsetPtr()->CancelBatch(affectRecords);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  /**
  This return the following enum.

  CursorLocationEnum
  {
  adUseNone = 1,
    adUseServer = 2,
    adUseClient = 3,
    adUseClientBatch = 3
  };
   */
  ADODB::CursorLocationEnum getCursorLocation()
  {
    return getRecordsetPtr()->GetCursorLocation();
  }

public:
  void putCursorLocation(__in ADODB::CursorLocationEnum plCursorLoc)
  {
    getRecordsetPtr()->PutCursorLocation(plCursorLoc);
  }

public:
  ADODB::_RecordsetPtr nextRecordset(__in VARIANT* recordsAffected)
  {
    return getRecordsetPtr()->NextRecordset(recordsAffected);
  }

public:
  VARIANT_BOOL supports(__in ADODB::CursorOptionEnum cursorOptions)
  {
    return getRecordsetPtr()->Supports(cursorOptions);
  }

public:
  _variant_t getCollect(__in const _variant_t& index)
  {
    return getRecordsetPtr()->GetCollect(index);
  }

public:
  void putCollect(
    const _variant_t& index,
    const _variant_t& pvar)
  {
    getRecordsetPtr()->PutCollect(
      index,
      pvar);
  }

public:
  /**
  MarshalOptionsEnum
  {
    adMarshalAll = 0,
    adMarshalModifiedOnly = 1
  };
   */
  ADODB::MarshalOptionsEnum getMarshalOptions()
  {
    return getRecordsetPtr()->GetMarshalOptions();
  }  

public:
  void putMarshalOptions(__in ADODB::MarshalOptionsEnum peMarshal)
  {
    getRecordsetPtr()->PutMarshalOptions(peMarshal);
  }

public:
  /**
  SearchDirectionEnum
  {
  adSearchForward = 1,
    adSearchBackward = -1
  };
   */
  HRESULT find(
    __in _bstr_t criteria,
    __in long skipRecords, //ADODB::ADO_LONGPTR skipRecords,
    __in ADODB::SearchDirectionEnum searchDirection,
    __in_opt const _variant_t& start = vtMissing)
  {
    HRESULT hr = getRecordsetPtr()->Find(
        criteria,
        skipRecords,
        searchDirection,
        start);

    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }


public:
  HRESULT cancel()
  {
    HRESULT hr = getRecordsetPtr()->Cancel();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  IUnknownPtr getDataSource()
  {
    return getRecordsetPtr()->GetDataSource();
  }

public:
  void putRefDataSource(__in IUnknown* ppunkDataSource)
  {
    getRecordsetPtr()->PutRefDataSource(ppunkDataSource);
  }

public:
  IDispatchPtr getActiveCommand()
  {
    return getRecordsetPtr()->GetActiveCommand();
  }

public:
  void putStayInSync(__in VARIANT_BOOL pbStayInSync)
  {
    getRecordsetPtr()->PutStayInSync(pbStayInSync);
  }

public:
  VARIANT_BOOL getStayInSync()
  {
    return getRecordsetPtr()->GetStayInSync();
  }

public:
  /**
   @ param stringFormat This can take one of following enum value
  StringFormatEnum
  {
    adClipString = 2
  };
  */
  _bstr_t getString(
    __in ADODB::StringFormatEnum stringFormat,
    __in long numRows,
    __in _bstr_t columnDelimeter,
    __in _bstr_t rowDelimeter,
    __in _bstr_t NULLExpr)
  {
    return getRecordsetPtr()->GetString(
        stringFormat,
        numRows,
        columnDelimeter,
        rowDelimeter,
        NULLExpr);
  }

public:
  /**
   * Simple getString method.
   * This returns _bstr_t string expression of all records of this recordset.
   *
   */
  _bstr_t getString()
  {
    long numRows = getRecordCount();  //All records
    _bstr_t columnDelimeter("\t");    //TAB
    _bstr_t rowDelimeter("\r\n");    //CRLF
    _bstr_t NULLExpr("");        //""

    return getRecordsetPtr()->GetString(
        ADODB::adClipString,
        numRows,
        columnDelimeter,
        rowDelimeter,
        NULLExpr);
  }

public:
  _bstr_t getDataMember()
  {
    return getRecordsetPtr()->GetDataMember();
  }

public:
  void putDataMember(__in _bstr_t pbstrDataMember)
  {
    getRecordsetPtr()->PutDataMember(pbstrDataMember);
  }

public:
  /**
  CompareEnum
  {
    adCompareLessThan = 0,
    adCompareEqual = 1,
    adCompareGreaterThan = 2,
    adCompareNotEqual = 3,
    adCompareNotComparable = 4
  };
   */
  ADODB::CompareEnum compareBookmarks(
    __in const _variant_t& bookmark1,
    __in const _variant_t& bookmark2)
  {
    return getRecordsetPtr()->CompareBookmarks(
      bookmark1,
      bookmark2);

  }

public:
  ADODB::_RecordsetPtr clone(__in ADODB::LockTypeEnum lockType)
  {
    return getRecordsetPtr()->Clone(
      lockType);

  }

public:
  /**

  AffectEnum
  {
    adAffectCurrent = 1,
    adAffectGroup = 2,
    adAffectAll = 3,
    adAffectAllChapters = 4
  };

  ResyncEnum
  {
    adResyncUnderlyingValues = 1,
    adResyncAllValues = 2
  };
   */
  HRESULT resync(
          __in ADODB::AffectEnum affectRecords,
      __in ADODB::ResyncEnum resyncValues)
  {
    HRESULT hr = getRecordsetPtr()->Resync(
              affectRecords,
          resyncValues);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  /**

  SeekEnum
  {
    adSeekFirstEQ = 1,
    adSeekLastEQ = 2,
    adSeekAfterEQ = 4,
    adSeekAfter = 8,
    adSeekBeforeEQ = 16,
    adSeekBefore = 32
  };
   */
  HRESULT seek(
    __in const _variant_t& keyValues,
    __in ADODB::SeekEnum seekOption)
  {
    HRESULT hr = getRecordsetPtr()->Seek (
      keyValues,
      seekOption );
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  void putIndex(__in _bstr_t pbstrIndex)
  {
    getRecordsetPtr()->PutIndex(pbstrIndex);
  }

public:
  _bstr_t getIndex()
  {
    return getRecordsetPtr()->GetIndex();
  }

public:
  /**
   persistFormat takes one of the following enum.

  PersistFormatEnum
  {
  adPersistADTG = 0,
  adPersistXML = 1
  };
   */
  HRESULT save(
    __in const _variant_t & destination,
    __in ADODB::PersistFormatEnum persistFormat)
  {
    HRESULT hr = getRecordsetPtr()->Save(
      destination,
      persistFormat);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  void dump()
  {
    printf("ADORecordset:\n");
  
    while(!getadoEOF()){
      //Gettting an object ofADOFields from the recordset object.
      ADOFields colFields;
      getFields(colFields);
      long count = colFields.getCount();

      printf("Record: \n");
      for (long i = 0L; i<count; i++) {
        //Get an each ADOField object from colFields.
        ADOField field;
        if (colFields.getItem(i, field)) {
          _bstr_t name = field.getName();
          ADOEnumNames names;

          const char* type = names.getName(field.getType());
          _variant_t variant = field.getValue();
          
          _bstr_t value = "";
          COMTypeConverter converter;
          converter.toString(variant, value, _bstr_t("(NULL)"));
          printf("Name=%S, Type=%s, Value=%S, DefinedSize=%lld, ActualSize=%lld\n",    //2017/01/15
              (const wchar_t*)name, 
              type,
              (const wchar_t*)value,
              field.getDefinedSize(),
              field.getActualSize());
      
        }
      }

      moveNext();
    }

  }
};

}
