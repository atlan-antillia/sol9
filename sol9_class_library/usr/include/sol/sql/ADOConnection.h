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
 *  ADOConnection.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/11
/*
// 2009/05/17 Added the following execute method.
  bool execute (
    __in _bstr_t commandText,
    __out long& recordsAffected,  //Pass a ref to long not _variant_t
    __out ADORecordset& recordset,
    __in_opt long options = ADODB::adOptionUnspecified)
*/

#pragma once

#include <sol/sql/ADOObject.h>
#include <sol/sql/ADORecordset.h>

#include <sol/sql/ADOErrors.h>
#include <sol/sql/ADOConnectionProperties.h>


namespace SOL {

class ADOConnection: public ADOObject {

public:
  /**
   * Constructor
   */
  ADOConnection() 
  {
  }

public:
  /**
   * Destructor
   */
  ~ADOConnection() 
  {
    close();
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Connection));
  }

public:
  ADODB::_ConnectionPtr getConnectionPtr() 
  {
    return (ADODB::_ConnectionPtr)getObject();
  }

public:
  _bstr_t getConnectionString()
  {
    return getConnectionPtr()->GetConnectionString();
  }

public:
  void putConnectionString(_bstr_t pbstr)
  {
    getConnectionPtr()->PutConnectionString(pbstr);
  }

public:
  /**
   * Load connection string from a file of filePath, and put it this ADOConnection object.
   */
  //2009/05/14
  bool loadConnectionProperties(const TCHAR* filePath)
  {
    if (filePath == NULL) {
      throw Exception(E_POINTER, "%s: %s", "E_POINTER",__FUNCTION__);

    }
    //If filePath file does not exist, throw E_FAIL; 
    if (GetFileAttributes(filePath) == 0xffffffff) {
      throw Exception(E_INVALIDARG, "%s: %s", "File not found",__FUNCTION__);
    }

    bool rc = false;

    ADOConnectionProperties props;
    if (props.load(filePath)) {

      String constring;
      props.getString(constring);  
      _bstr_t string = (const TCHAR*)constring;

      //Put the string to this connection object.
      putConnectionString(string);

      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return rc;
  }

public:
  long getCommandTimeout()
  {
    return getConnectionPtr()->GetCommandTimeout();
  }

public:
  void putCommandTimeout(long plTimeout)
  {
    getConnectionPtr()->PutCommandTimeout(plTimeout);
  }

public:
  long getConnectionTimeout()
  {
    return getConnectionPtr()->GetConnectionTimeout();
  }

public:
  void putConnectionTimeout(long plTimeout)
  {
    getConnectionPtr()->PutConnectionTimeout(plTimeout);
  }

public:
  _bstr_t getVersion()
  {
    return getConnectionPtr()->GetVersion();
  }

public:
  void close()
  {
    try {
      getConnectionPtr()->Close();
    } catch (...) {
      //This IException will happen provided the connection was not opened,
    }
    clear();
  }

public:
  // 2009/05/17
  /**
   * 1 Execute the first parameter commandText
   * 2 Return an instance ADORecordset to a parameter recordset
   * 3 Return the number of records affected by this operation.
   *
   *
   */
  long execute (
    __in _bstr_t commandText,
    __out ADORecordset& recordset,
    __in_opt long options = ADODB::adOptionUnspecified)
  {
    long rc = -1L;
    _variant_t varAffected(0L);

    ADODB::_RecordsetPtr recset = execute (
        commandText,
        varAffected,
          options);
    if (recset) {
      recordset.set(recset);
      rc = (long)varAffected;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return rc;
  }

public:
  bool execute (
    __in _bstr_t commandText,
    __out _variant_t& recordsAffected,
    __out ADORecordset& recordset,
    __in_opt long options = ADODB::adOptionUnspecified)
  {
    bool rc = false;

    ADODB::_RecordsetPtr recset = execute (
        commandText,
        recordsAffected,
          options);
    if (recset) {
      recordset.set(recset);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    
    return rc;
  }

public:
  ADODB::_RecordsetPtr execute(
    __in _bstr_t commandText,
    __out _variant_t& recordsAffected,
      __in long options)
  {
    return getConnectionPtr()->Execute(
            commandText,
            &recordsAffected,
        options);
  }

public:
  long beginTrans()
  {
    return getConnectionPtr()->BeginTrans();
  }

public:

  HRESULT commitTrans()
  {
    HRESULT hr = getConnectionPtr()->CommitTrans();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  HRESULT rollbackTrans()
  {
    HRESULT hr = getConnectionPtr()->RollbackTrans();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;

  }

public:
  /**
   * Open a connection to a db specified by connectionString.
   * If not succeeded, throw HRESULT code.
   
   *
   */
    HRESULT open(
    __in_opt _bstr_t connectionString = "",
    __in_opt _bstr_t userID = "",
    __in_opt _bstr_t password = "" ,
    __in_opt long options=ADODB::adConnectUnspecified)
  {
    HRESULT hr = getConnectionPtr()->Open(
        connectionString,
             userID,
            password,
        options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }


public:
  bool getErrors(__out ADOErrors& errors)
  {
    bool rc = false;
    ADODB::ErrorsPtr pErrors= getConnectionPtr()->GetErrors();
    if (pErrors) {
      errors.set(pErrors);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADODB::ErrorsPtr getErrors()
  {
    return getConnectionPtr()->GetErrors();
  }

public:
  _bstr_t getDefaultDatabase()
  {
    return getConnectionPtr()->GetDefaultDatabase();
  }

public:
  void putDefaultDatabase(__in _bstr_t pbstr)
  {
    getConnectionPtr()->PutDefaultDatabase(pbstr);
  }

public:
  /**
  This returns the following enum.

  IsolationLevelEnum
  {
    adXactUnspecified = -1,
    adXactChaos = 16,
    adXactReadUncommitted = 256,
    adXactBrowse = 256,
    adXactCursorStability = 4096,
    adXactReadCommitted = 4096,
    adXactRepeatableRead = 65536,
    adXactSerializable = 1048576,
    adXactIsolated = 1048576
  };
  */
  ADODB::IsolationLevelEnum getIsolationLevel()
  {
    return getConnectionPtr()->GetIsolationLevel();
  }

public:
  void putIsolationLevel(__in ADODB::IsolationLevelEnum level)
  {
    getConnectionPtr()->PutIsolationLevel(level);
  }

public:

  long getAttributes()
  {
    return getConnectionPtr()->GetAttributes();
  }

public:
  void putAttributes(long plAttr)
  {
    getConnectionPtr()->PutAttributes(plAttr);
  }

public:
  /**
  This returns the following enum.

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
    return getConnectionPtr()->GetCursorLocation();
  }

public:
  void putCursorLocation(__in ADODB::CursorLocationEnum plCursorLoc)
  {
    getConnectionPtr()->PutCursorLocation(plCursorLoc);
  }

public:
  /**
  This returns the following enum.

  ConnectModeEnum
  {
    adModeUnknown = 0,
    adModeRead = 1,
    adModeWrite = 2,
    adModeReadWrite = 3,
    adModeShareDenyRead = 4,
    adModeShareDenyWrite = 8,
    adModeShareExclusive = 12,
    adModeShareDenyNone = 16,
    adModeRecursive = 4194304
  };
   */
  ADODB::ConnectModeEnum getMode()
  {
    return getConnectionPtr()->GetMode();
  }

public:
  void putMode(__in ADODB::ConnectModeEnum plMode)
  {
    getConnectionPtr()->PutMode(plMode);
  }

public:
  _bstr_t getProvider()
  {
    return getConnectionPtr()->GetProvider();
  }

public:

  void putProvider(__in _bstr_t pbstr)
  {
    getConnectionPtr()->PutProvider(pbstr);
  }

public:
  long getState()
  {
    return getConnectionPtr()->GetState();
  }


public:
  /**
   @param schema  This can take one of the following enum.
 
  SchemaEnum
  {
    adSchemaProviderSpecific = -1,
    adSchemaAsserts = 0,
    adSchemaCatalogs = 1,
    adSchemaCharacterSets = 2,
    adSchemaCollations = 3,
    adSchemaColumns = 4,
    adSchemaCheckConstraints = 5,
    adSchemaConstraintColumnUsage = 6,
    adSchemaConstraintTableUsage = 7,
    adSchemaKeyColumnUsage = 8,
    adSchemaReferentialContraints = 9,
    adSchemaReferentialConstraints = 9,
    adSchemaTableConstraints = 10,
    adSchemaColumnsDomainUsage = 11,
    adSchemaIndexes = 12,
    adSchemaColumnPrivileges = 13,
    adSchemaTablePrivileges = 14,
    adSchemaUsagePrivileges = 15,
    adSchemaProcedures = 16,
    adSchemaSchemata = 17,
    adSchemaSQLLanguages = 18,
    adSchemaStatistics = 19,
    adSchemaTables = 20,
    adSchemaTranslations = 21,
    adSchemaProviderTypes = 22,
    adSchemaViews = 23,
    adSchemaViewColumnUsage = 24,
    adSchemaViewTableUsage = 25,
    adSchemaProcedureParameters = 26,
    adSchemaForeignKeys = 27,
    adSchemaPrimaryKeys = 28,
    adSchemaProcedureColumns = 29,
    adSchemaDBInfoKeywords = 30,
    adSchemaDBInfoLiterals = 31,
    adSchemaCubes = 32,
    adSchemaDimensions = 33,
    adSchemaHierarchies = 34,
    adSchemaLevels = 35,
    adSchemaMeasures = 36,
    adSchemaProperties = 37,
    adSchemaMembers = 38,
    adSchemaTrustees = 39,
    adSchemaFunctions = 40,
    adSchemaActions = 41,
    adSchemaCommands = 42,
    adSchemaSets = 43
  };

   */
   bool openSchema (
    __in ADODB::SchemaEnum schema,
    __out ADORecordset& recordset,
    __in_opt const _variant_t& restrictions =vtMissing,
    __in_opt const _variant_t& schemaID =vtMissing
    )
  {
    bool rc = false;
    ADODB::_RecordsetPtr recset = openSchema(
      schema,
      restrictions,
      schemaID);
    if (recset) {
      recordset.set(recset);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADODB::_RecordsetPtr openSchema (
    __in ADODB::SchemaEnum schema,
    __in_opt const _variant_t& restrictions = vtMissing,
    __in_opt const _variant_t& schemaID = vtMissing)

  {
    return getConnectionPtr()->OpenSchema(
      schema,
      restrictions,
      schemaID);
  }

public:

  HRESULT cancel()
  {
    HRESULT hr= getConnectionPtr()->Cancel();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);      
    }
    return hr;
  }
};

}
