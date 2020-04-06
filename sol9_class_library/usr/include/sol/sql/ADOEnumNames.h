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
 *  ADOEnums.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/24

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>

namespace SOL {

class ADOEnumNames :public Object {

public:
  /**
   * Constructor
   */
  ADOEnumNames()
  {
  }

public:
  /**
   * Destructor
   */
  ~ADOEnumNames()
  {
  }


public:
  const char* getName(ADODB::LockTypeEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adLockUnspecified", (LONG_PTR)ADODB::adLockUnspecified},
      {"adLockReadOnly", (LONG_PTR)ADODB::adLockReadOnly},
      {"adLockPessimistic", (LONG_PTR)ADODB::adLockPessimistic},
      {"adLockOptimistic", (LONG_PTR)ADODB::adLockOptimistic},
      {"adLockBatchOptimistic", (LONG_PTR)ADODB::adLockBatchOptimistic}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::ExecuteOptionEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adOptionUnspecified", (LONG_PTR)ADODB::adOptionUnspecified},
      {"adAsyncExecute", (LONG_PTR)ADODB::adAsyncExecute},
      {"adAsyncFetch", (LONG_PTR)ADODB::adAsyncFetch},
      {"adAsyncFetchNonBlocking", (LONG_PTR)ADODB::adAsyncFetchNonBlocking},
      {"adExecuteNoRecords", (LONG_PTR)ADODB::adExecuteNoRecords},
      {"adExecuteStream", (LONG_PTR)ADODB::adExecuteStream},
      {"adExecuteRecord", (LONG_PTR)ADODB::adExecuteRecord}
    };

    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ConnectOptionEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adConnectUnspecified", (LONG_PTR)ADODB::adConnectUnspecified},
      {"adAsyncConnect", (LONG_PTR)ADODB::adAsyncConnect}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ObjectStateEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adStateClosed", (LONG_PTR)ADODB::adStateClosed},
      {"adStateOpen", (LONG_PTR)ADODB::adStateOpen},
      {"adStateConnecting", (LONG_PTR)ADODB::adStateConnecting},
      {"adStateExecuting", (LONG_PTR)ADODB::adStateExecuting},
      {"adStateFetching", (LONG_PTR)ADODB::adStateFetching}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::FieldAttributeEnum type)
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
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::EditModeEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adEditNone", (LONG_PTR)ADODB::adEditNone},
      {"adEditInProgress", (LONG_PTR)ADODB::adEditInProgress},
      {"adEditAdd", (LONG_PTR)ADODB::adEditAdd},
      {"adEditDelete", (LONG_PTR)ADODB::adEditDelete}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::RecordStatusEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adRecOK", (LONG_PTR)ADODB::adRecOK},
      {"adRecNew", (LONG_PTR)ADODB::adRecNew},
      {"adRecModified", (LONG_PTR)ADODB::adRecModified},
      {"adRecDeleted", (LONG_PTR)ADODB::adRecDeleted},
      {"adRecUnmodified", (LONG_PTR)ADODB::adRecUnmodified},
      {"adRecInvalid", (LONG_PTR)ADODB::adRecInvalid},
      {"adRecMultipleChanges", (LONG_PTR)ADODB::adRecMultipleChanges},
      {"adRecPendingChanges", (LONG_PTR)ADODB::adRecPendingChanges},
      {"adRecCanceled", (LONG_PTR)ADODB::adRecCanceled},
      {"adRecCantRelease", (LONG_PTR)ADODB::adRecCantRelease},
      {"adRecConcurrencyViolation", (LONG_PTR)ADODB::adRecConcurrencyViolation},
      {"adRecIntegrityViolation", (LONG_PTR)ADODB::adRecIntegrityViolation},
      {"adRecMaxChangesExceeded", (LONG_PTR)ADODB::adRecMaxChangesExceeded},
      {"adRecObjectOpen", (LONG_PTR)ADODB::adRecObjectOpen},
      {"adRecOutOfMemory", (LONG_PTR)ADODB::adRecOutOfMemory},
      {"adRecPermissionDenied", (LONG_PTR)ADODB::adRecPermissionDenied},
      {"adRecSchemaViolation", (LONG_PTR)ADODB::adRecSchemaViolation},
      {"adRecDBDeleted", (LONG_PTR)ADODB::adRecDBDeleted}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::GetRowsOptionEnum type)
  {
    static const ArgT<char> names[]=
    {
      {"adGetRowsRest", (LONG_PTR)ADODB::adGetRowsRest}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::PositionEnum type)
  {
    static const ArgT<char> names[]= 
    {
      {"adPosUnknown", (LONG_PTR)ADODB::adPosUnknown},
      {"adPosBOF", (LONG_PTR)ADODB::adPosBOF},
      {"adPosEOF", (LONG_PTR)ADODB::adPosEOF}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::BookmarkEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adBookmarkCurrent", (LONG_PTR)ADODB::adBookmarkCurrent},
      {"adBookmarkFirst", (LONG_PTR)ADODB::adBookmarkFirst},
      {"adBookmarkLast", (LONG_PTR)ADODB::adBookmarkLast}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::MarshalOptionsEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adMarshalAll", (LONG_PTR)ADODB::adMarshalAll},
      {"adMarshalModifiedOnly", (LONG_PTR)ADODB::adMarshalModifiedOnly}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::AffectEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adAffectCurrent", (LONG_PTR)ADODB::adAffectCurrent},
      {"adAffectGroup", (LONG_PTR)ADODB::adAffectGroup},
      {"adAffectAll", (LONG_PTR)ADODB::adAffectAll},
      {"adAffectAllChapters", (LONG_PTR)ADODB::adAffectAllChapters}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ResyncEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adResyncUnderlyingValues", (LONG_PTR)ADODB::adResyncUnderlyingValues},
      {"adResyncAllValues", (LONG_PTR)ADODB::adResyncAllValues}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::CompareEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adCompareLessThan", (LONG_PTR)ADODB::adCompareLessThan},
      {"adCompareEqual", (LONG_PTR)ADODB::adCompareEqual},
      {"adCompareGreaterThan", (LONG_PTR)ADODB::adCompareGreaterThan},
      {"adCompareNotEqual", (LONG_PTR)ADODB::adCompareNotEqual},
      {"adCompareNotComparable", (LONG_PTR)ADODB::adCompareNotComparable}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::FilterGroupEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adFilterNone", (LONG_PTR)ADODB::adFilterNone},
      {"adFilterPendingRecords", (LONG_PTR)ADODB::adFilterPendingRecords},
      {"adFilterAffectedRecords", (LONG_PTR)ADODB::adFilterAffectedRecords},
      {"adFilterFetchedRecords", (LONG_PTR)ADODB::adFilterFetchedRecords},
      {"adFilterPredicate", (LONG_PTR)ADODB::adFilterPredicate},
      {"adFilterConflictingRecords", (LONG_PTR)ADODB::adFilterConflictingRecords}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::SearchDirectionEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adSearchForward", (LONG_PTR)ADODB::adSearchForward},
      {"adSearchBackward", (LONG_PTR)ADODB::adSearchBackward}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::PersistFormatEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adPersistADTG", (LONG_PTR)ADODB::adPersistADTG},
      {"adPersistXML", (LONG_PTR)ADODB::adPersistXML}
    };
    return findName(names, XtNumber(names), type);
  }

public:
  const char* getName(ADODB::StringFormatEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adClipString", (LONG_PTR)ADODB::adClipString}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ConnectPromptEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adPromptAlways", (LONG_PTR)ADODB::adPromptAlways},
      {"adPromptComplete", (LONG_PTR)ADODB::adPromptComplete},
      {"adPromptCompleteRequired", (LONG_PTR)ADODB::adPromptCompleteRequired},
      {"adPromptNever", (LONG_PTR)ADODB::adPromptNever}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::PropertyAttributesEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adPropNotSupported", (LONG_PTR)ADODB::adPropNotSupported},
      {"adPropRequired", (LONG_PTR)ADODB::adPropRequired},
      {"adPropOptional", (LONG_PTR)ADODB::adPropOptional},
      {"adPropRead", (LONG_PTR)ADODB::adPropRead},
      {"adPropWrite", (LONG_PTR)ADODB::adPropWrite}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  
  const char* getName(ADODB::CommandTypeEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adCmdUnspecified", (LONG_PTR)ADODB::adCmdUnspecified}, 
      {"adCmdText",      (LONG_PTR)ADODB::adCmdText},
      {"adCmdTable",      (LONG_PTR)ADODB::adCmdTable},
      {"adCmdStoredProc",    (LONG_PTR)ADODB::adCmdStoredProc},

      {"adCmdUnknown",    (LONG_PTR)ADODB::adCmdUnknown},
      {"adCmdFile",      (LONG_PTR)ADODB::adCmdFile},
      {"adCmdTableDirect",  (LONG_PTR)ADODB::adCmdTableDirect},
    };

    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::ParameterDirectionEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adParamUnknown", (LONG_PTR)ADODB::adParamUnknown},
      {"adParamInput", (LONG_PTR)ADODB::adParamInput},
      {"adParamOutput", (LONG_PTR)ADODB::adParamOutput},
      {"adParamInputOutput", (LONG_PTR)ADODB::adParamInputOutput},
      {"adParamReturnValue", (LONG_PTR)ADODB::adParamReturnValue},
    };

    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::DataTypeEnum type)
  {
    //ADODB::DataTypeEnum type = getType();
    static const ArgT<char> names[] = {
      {"Empty",      (LONG_PTR)ADODB::adEmpty},
      {"TineyInt",    (LONG_PTR)ADODB::adTinyInt},
      {"SmallInt",    (LONG_PTR)ADODB::adSmallInt},
      {"Integer",      (LONG_PTR)ADODB::adInteger},
      {"BigInt",      (LONG_PTR)ADODB::adBigInt},
      {"UnsignedTinyInt", (LONG_PTR)ADODB::adUnsignedTinyInt},
      {"UnsignedSmallInt",ADODB::adUnsignedSmallInt},
      {"UnsignedIn",    (LONG_PTR)ADODB::adUnsignedInt},
      {"UnsignedBigInt",  (LONG_PTR)ADODB::adUnsignedBigInt},
      {"Single",      (LONG_PTR)ADODB::adSingle},
      {"Double",      (LONG_PTR)ADODB::adDouble},
      {"Currency",    (LONG_PTR)ADODB::adCurrency},
      {"Decimal",      (LONG_PTR)ADODB::adDecimal},
      {"Numeric",      (LONG_PTR)ADODB::adNumeric},
      {"Boolean",      (LONG_PTR)ADODB::adBoolean},
      {"Error",      (LONG_PTR)ADODB::adError},
      {"UserDefined",    (LONG_PTR)ADODB::adUserDefined},
      {"Variant",      (LONG_PTR)ADODB::adVariant},
      {"IDispatch",    (LONG_PTR)ADODB::adIDispatch},
      {"IUnknown",    (LONG_PTR)ADODB::adIUnknown},
      {"GUID",      (LONG_PTR)ADODB::adGUID},
      {"Date",      (LONG_PTR)ADODB::adDate},
      {"DBDate",      (LONG_PTR)ADODB::adDBDate},
      {"DBTime",      (LONG_PTR)ADODB::adDBTime},
      {"DBTimeStamp",    (LONG_PTR)ADODB::adDBTimeStamp},
      {"BSTR",      (LONG_PTR)ADODB::adBSTR},
      {"Char",      (LONG_PTR)ADODB::adChar},
      {"VarChar",      (LONG_PTR)ADODB::adVarChar},
      {"LongVarChar",    (LONG_PTR)ADODB::adLongVarChar},
      {"WChar",      (LONG_PTR)ADODB::adWChar},
      {"VarWChar",    (LONG_PTR)ADODB::adVarWChar},
      {"LongVarWChar",  (LONG_PTR)ADODB::adLongVarWChar},
      {"Binary",      (LONG_PTR)ADODB::adBinary},
      {"VarBinary",    (LONG_PTR)ADODB::adVarBinary},
      {"LongVarBinary",  (LONG_PTR)ADODB::adLongVarBinary},
      {"Chapter",      (LONG_PTR)ADODB::adChapter},
      {"FileTime",    (LONG_PTR)ADODB::adFileTime},
      {"PropVariant",    (LONG_PTR)ADODB::adPropVariant},
      {"VarNumeric",    (LONG_PTR)ADODB::adVarNumeric},
      {"Array",      (LONG_PTR)ADODB::adArray}
    };
    return findName(names, XtNumber(names), (int)type);
  }


public:
  const char* getName(ADODB::CursorLocationEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adUseNone", (LONG_PTR)ADODB::adUseNone},
      {"adUseServer", (LONG_PTR)ADODB::adUseServer},
      {"adUseClient", (LONG_PTR)ADODB::adUseClient},
      {"adUseClientBatch", (LONG_PTR)ADODB::adUseClientBatch},
    };

    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ConnectModeEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adModeUnknown", (LONG_PTR)ADODB::adModeUnknown},
      {"adModeRead", (LONG_PTR)ADODB::adModeRead},
      {"adModeWrite", (LONG_PTR)ADODB::adModeWrite},
      {"adModeReadWrite", (LONG_PTR)ADODB::adModeReadWrite},
      {"adModeShareDenyRead", (LONG_PTR)ADODB::adModeShareDenyRead},
      {"adModeShareDenyWrite", (LONG_PTR)ADODB::adModeShareDenyWrite}, 
      {"adModeShareExclusive", (LONG_PTR)ADODB::adModeShareExclusive},
      {"adModeShareDenyNone", (LONG_PTR)ADODB::adModeShareDenyNone},
      {"adModeRecursive", (LONG_PTR)ADODB::adModeRecursive},
    };
    return findName(names, XtNumber(names), (int)type);
  }
public:
  
  const char* getName(ADODB::SchemaEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adSchemaProviderSpecific", (LONG_PTR)ADODB::adSchemaProviderSpecific},
      {"adSchemaAsserts",  (LONG_PTR)ADODB::adSchemaAsserts},
      {"adSchemaCatalogs",  (LONG_PTR)ADODB::adSchemaCatalogs},
      {"adSchemaCharacterSets", (LONG_PTR)ADODB::adSchemaCharacterSets},
      {"adSchemaCollations", (LONG_PTR)ADODB::adSchemaCollations},
      {"adSchemaColumns", (LONG_PTR)ADODB::adSchemaColumns},
      {"adSchemaCheckConstraints", (LONG_PTR)ADODB::adSchemaCheckConstraints},
      {"adSchemaConstraintColumnUsage", (LONG_PTR)ADODB::adSchemaConstraintColumnUsage},
      {"adSchemaConstraintTableUsage", (LONG_PTR)ADODB::adSchemaConstraintTableUsage},
      {"adSchemaKeyColumnUsage", (LONG_PTR)ADODB::adSchemaKeyColumnUsage},
      {"adSchemaReferentialContraints", (LONG_PTR)ADODB::adSchemaReferentialContraints},
      {"adSchemaReferentialConstraints", (LONG_PTR)ADODB::adSchemaReferentialConstraints},
      {"adSchemaTableConstraints", (LONG_PTR)ADODB::adSchemaTableConstraints},
      {"adSchemaColumnsDomainUsage", (LONG_PTR)ADODB::adSchemaColumnsDomainUsage},
      {"adSchemaIndexes", (LONG_PTR)ADODB::adSchemaIndexes},
      {"adSchemaColumnPrivileges", (LONG_PTR)ADODB::adSchemaColumnPrivileges},
      {"adSchemaTablePrivileges", (LONG_PTR)ADODB::adSchemaTablePrivileges},
      {"adSchemaUsagePrivileges", (LONG_PTR)ADODB::adSchemaUsagePrivileges},
      {"adSchemaProcedures", (LONG_PTR)ADODB::adSchemaProcedures},
      {"adSchemaSchemata", (LONG_PTR)ADODB::adSchemaSchemata},
      {"adSchemaSQLLanguages", (LONG_PTR)ADODB::adSchemaSQLLanguages},
      {"adSchemaStatistics", (LONG_PTR)ADODB::adSchemaStatistics},
      {"adSchemaTables", (LONG_PTR)ADODB::adSchemaTables},
      {"adSchemaTranslations", (LONG_PTR)ADODB::adSchemaTranslations},
      {"adSchemaProviderTypes", (LONG_PTR)ADODB::adSchemaProviderTypes},
      {"adSchemaViews", (LONG_PTR)ADODB::adSchemaViews},
      {"adSchemaViewColumnUsage", (LONG_PTR)ADODB::adSchemaViewColumnUsage},
      {"adSchemaViewTableUsage", (LONG_PTR)ADODB::adSchemaViewTableUsage},
      {"adSchemaProcedureParameters", (LONG_PTR)ADODB::adSchemaProcedureParameters},
      {"adSchemaForeignKeys", (LONG_PTR)ADODB::adSchemaForeignKeys},
      {"adSchemaPrimaryKeys", (LONG_PTR)ADODB::adSchemaPrimaryKeys},
      {"adSchemaProcedureColumns", (LONG_PTR)ADODB::adSchemaProcedureColumns},
      {"adSchemaDBInfoKeywords", (LONG_PTR)ADODB::adSchemaDBInfoKeywords},
      {"adSchemaDBInfoLiterals", (LONG_PTR)ADODB::adSchemaDBInfoLiterals},
      {"adSchemaCubes", (LONG_PTR)ADODB::adSchemaCubes},
      {"adSchemaDimensions", (LONG_PTR)ADODB::adSchemaDimensions},
      {"adSchemaHierarchies", (LONG_PTR)ADODB::adSchemaHierarchies},
      {"adSchemaLevels", (LONG_PTR)ADODB::adSchemaLevels},
      {"adSchemaMeasures", (LONG_PTR)ADODB::adSchemaMeasures},
      {"adSchemaProperties", (LONG_PTR)ADODB::adSchemaProperties},
      {"adSchemaMembers", (LONG_PTR)ADODB::adSchemaMembers},
      {"adSchemaTrustees", (LONG_PTR)ADODB::adSchemaTrustees},
      {"adSchemaFunctions", (LONG_PTR)ADODB::adSchemaFunctions},
      {"adSchemaActions", (LONG_PTR)ADODB::adSchemaActions},
      {"adSchemaCommands", (LONG_PTR)ADODB::adSchemaCommands},
      {"adSchemaSets", (LONG_PTR)ADODB::adSchemaSets},
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::ErrorValueEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adErrProviderFailed", (LONG_PTR)ADODB::adErrProviderFailed},
      {"adErrInvalidArgument", (LONG_PTR)ADODB::adErrInvalidArgument},
      {"adErrOpeningFile", (LONG_PTR)ADODB::adErrOpeningFile},
      {"adErrReadFile", (LONG_PTR)ADODB::adErrReadFile},
      {"adErrWriteFile", (LONG_PTR)ADODB::adErrWriteFile},
      {"adErrNoCurrentRecord", (LONG_PTR)ADODB::adErrNoCurrentRecord},
      {"adErrIllegalOperation", (LONG_PTR)ADODB::adErrIllegalOperation},
      {"adErrCantChangeProvider", (LONG_PTR)ADODB::adErrCantChangeProvider},
      {"adErrInTransaction", (LONG_PTR)ADODB::adErrInTransaction},
      {"adErrFeatureNotAvailable", (LONG_PTR)ADODB::adErrFeatureNotAvailable},
      {"adErrItemNotFound", (LONG_PTR)ADODB::adErrItemNotFound},
      {"adErrObjectInCollection", (LONG_PTR)ADODB::adErrObjectInCollection},
      {"adErrObjectNotSet", (LONG_PTR)ADODB::adErrObjectNotSet},
      {"adErrDataConversion", (LONG_PTR)ADODB::adErrDataConversion},
      {"adErrObjectClosed", (LONG_PTR)ADODB::adErrObjectClosed},
      {"adErrObjectOpen", (LONG_PTR)ADODB::adErrObjectOpen},
      {"adErrProviderNotFound", (LONG_PTR)ADODB::adErrProviderNotFound},
      {"adErrBoundToCommand", (LONG_PTR)ADODB::adErrBoundToCommand},
      {"adErrInvalidParamInfo", (LONG_PTR)ADODB::adErrInvalidParamInfo},
      {"adErrInvalidConnection", (LONG_PTR)ADODB::adErrInvalidConnection},
      {"adErrNotReentrant", (LONG_PTR)ADODB::adErrNotReentrant},
      {"adErrStillExecuting", (LONG_PTR)ADODB::adErrStillExecuting},
      {"adErrOperationCancelled", (LONG_PTR)ADODB::adErrOperationCancelled},
      {"adErrStillConnecting", (LONG_PTR)ADODB::adErrStillConnecting},
      {"adErrInvalidTransaction", (LONG_PTR)ADODB::adErrInvalidTransaction},
      {"adErrNotExecuting", (LONG_PTR)ADODB::adErrNotExecuting},
      {"adErrUnsafeOperation", (LONG_PTR)ADODB::adErrUnsafeOperation},
      {"adwrnSecurityDialog", (LONG_PTR)ADODB::adwrnSecurityDialog},
      {"adwrnSecurityDialogHeader", (LONG_PTR)ADODB::adwrnSecurityDialogHeader},
      {"adErrIntegrityViolation", (LONG_PTR)ADODB::adErrIntegrityViolation},
      {"adErrPermissionDenied", (LONG_PTR)ADODB::adErrPermissionDenied},
      {"adErrDataOverflow", (LONG_PTR)ADODB::adErrDataOverflow},
      {"adErrSchemaViolation", (LONG_PTR)ADODB::adErrSchemaViolation},
      {"adErrSignMismatch", (LONG_PTR)ADODB::adErrSignMismatch},
      {"adErrCantConvertvalue", (LONG_PTR)ADODB::adErrCantConvertvalue},
      {"adErrCantCreate", (LONG_PTR)ADODB::adErrCantCreate},
      {"adErrColumnNotOnThisRow", (LONG_PTR)ADODB::adErrColumnNotOnThisRow},
      {"adErrURLDoesNotExist", (LONG_PTR)ADODB::adErrURLDoesNotExist},
      {"adErrTreePermissionDenied", (LONG_PTR)ADODB::adErrTreePermissionDenied},
      {"adErrInvalidURL", (LONG_PTR)ADODB::adErrInvalidURL},
      {"adErrResourceLocked", (LONG_PTR)ADODB::adErrResourceLocked},
      {"adErrResourceExists", (LONG_PTR)ADODB::adErrResourceExists},
      {"adErrCannotComplete", (LONG_PTR)ADODB::adErrCannotComplete},
      {"adErrVolumeNotFound", (LONG_PTR)ADODB::adErrVolumeNotFound},
      {"adErrOutOfSpace", (LONG_PTR)ADODB::adErrOutOfSpace},
      {"adErrResourceOutOfScope", (LONG_PTR)ADODB::adErrResourceOutOfScope},
      {"adErrUnavailable", (LONG_PTR)ADODB::adErrUnavailable},
      {"adErrURLNamedRowDoesNotExist", (LONG_PTR)ADODB::adErrURLNamedRowDoesNotExist},
      {"adErrDelResOutOfScope", (LONG_PTR)ADODB::adErrDelResOutOfScope},
      {"adErrPropInvalidColumn", (LONG_PTR)ADODB::adErrPropInvalidColumn},
      {"adErrPropInvalidOption", (LONG_PTR)ADODB::adErrPropInvalidOption},
      {"adErrPropInvalidValue", (LONG_PTR)ADODB::adErrPropInvalidValue},
      {"adErrPropConflicting", (LONG_PTR)ADODB::adErrPropConflicting},
      {"adErrPropNotAllSettable", (LONG_PTR)ADODB::adErrPropNotAllSettable},
      {"adErrPropNotSet", (LONG_PTR)ADODB::adErrPropNotSet},
      {"adErrPropNotSettable", (LONG_PTR)ADODB::adErrPropNotSettable},
      {"adErrPropNotSupported", (LONG_PTR)ADODB::adErrPropNotSupported},
      {"adErrCatalogNotSet", (LONG_PTR)ADODB::adErrCatalogNotSet},
      {"adErrCantChangeConnection", (LONG_PTR)ADODB::adErrCantChangeConnection},
      {"adErrFieldsUpdateFailed", (LONG_PTR)ADODB::adErrFieldsUpdateFailed},
      {"adErrDenyNotSupported", (LONG_PTR)ADODB::adErrDenyNotSupported},
      {"adErrDenyTypeNotSupported", (LONG_PTR)ADODB::adErrDenyTypeNotSupported},
      {"adErrProviderNotSpecified", (LONG_PTR)ADODB::adErrProviderNotSpecified},
      {"adErrConnectionStringTooLong", (LONG_PTR)ADODB::adErrConnectionStringTooLong}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::RecordCreateOptionsEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adCreateCollection", (LONG_PTR)ADODB::adCreateCollection},
      {"adCreateStructDoc", (LONG_PTR)ADODB::adCreateStructDoc},
      {"adCreateNonCollection", (LONG_PTR)ADODB::adCreateNonCollection},
      {"adOpenIfExists", (LONG_PTR)ADODB::adOpenIfExists},
      {"adCreateOverwrite", (LONG_PTR)ADODB::adCreateOverwrite},
      {"adFailIfNotExists", (LONG_PTR)ADODB::adFailIfNotExists}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::RecordOpenOptionsEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adOpenRecordUnspecified", (LONG_PTR)ADODB::adOpenRecordUnspecified},
      {"adOpenSource", (LONG_PTR)ADODB::adOpenSource},
      {"adOpenOutput", (LONG_PTR)ADODB::adOpenOutput},
      {"adOpenAsync", (LONG_PTR)ADODB::adOpenAsync},
      {"adDelayFetchStream", (LONG_PTR)ADODB::adDelayFetchStream},
      {"adDelayFetchFields", (LONG_PTR)ADODB::adDelayFetchFields},
      {"adOpenExecuteCommand", (LONG_PTR)ADODB::adOpenExecuteCommand}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADODB::IsolationLevelEnum type)
  {
    static const ArgT<char> names[] = 
    {
      {"adXactUnspecified", (LONG_PTR)ADODB::adXactUnspecified},
      {"adXactChaos", (LONG_PTR)ADODB::adXactChaos},
      {"adXactReadUncommitted", (LONG_PTR)ADODB::adXactReadUncommitted},
      {"adXactBrowse", (LONG_PTR)ADODB::adXactBrowse},
      {"adXactCursorStability", (LONG_PTR)ADODB::adXactCursorStability},
      {"adXactReadCommitted", (LONG_PTR)ADODB::adXactReadCommitted},
      {"adXactRepeatableRead", (LONG_PTR)ADODB::adXactRepeatableRead},
      {"adXactSerializable", (LONG_PTR)ADODB::adXactSerializable},
      {"adXactIsolated", (LONG_PTR)ADODB::adXactIsolated}
    };
    return findName(names, XtNumber(names), (int)type);
  }

private:
  const char* findName(const ArgT<char>* names, const int count, int type)
  {
    const char* name = "";
    for(int i = 0; i<count; i++) {
      if ((int)names[i].value == type) {
        name = names[i].name;
        break;
      }
    }
    return name;
  }

};

}
