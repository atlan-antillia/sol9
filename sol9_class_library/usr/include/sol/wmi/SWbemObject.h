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
 *  SWbemObject.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.


#pragma once

#include <sol/wmi/SWbemBaseObject.h>
#include <sol/wmi/SWbemPropertySet.h>
#include <sol/wmi/SWbemObjectPath.h>
#include <sol/wmi/SWbemSecurity.h>

namespace SOL {

class SWbemObject :public SWbemBaseObject {

public:
  SWbemObject(IDispatch* pDisp=NULL)
    :SWbemBaseObject(pDisp)
  {
  }

public:
  ISWbemObject* get()
  {
    return (ISWbemObject*)getIDispatch();
  }

public:
  SWbemObject& operator=(ISWbemObject* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  ISWbemObjectPath* put( 
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemObjectPath* pObjWbemObjectPath = NULL;
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();
    if (FAILED(hr = object->Put_( 
        iFlags,
        objWbemNamedValueSet,
        &pObjWbemObjectPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectPath;
  }

        
        
public: 
  HRESULT putAsync( 
            __in IDispatch *objWbemSink,
           __in long iFlags = wbemChangeFlagCreateOrUpdate,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();
    if (FAILED(hr = object->PutAsync_( 
        objWbemSink,
        iFlags,
        objWbemNamedValueSet,
        objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public: 
  HRESULT remove( 
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();

    if (FAILED(hr = object ->Delete_( 
        iFlags,
        objWbemNamedValueSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

        
        
public: 
  HRESULT deleteAsync( 
            __in IDispatch *objWbemSink,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();

    if (FAILED(hr = object->DeleteAsync_( 
            objWbemSink,
            iFlags,
            objWbemNamedValueSet,
      objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public:
  ISWbemObjectSet* instances( 
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();
    ISWbemObjectSet *objWbemObjectSet = NULL;

    if (FAILED(hr = object-> Instances_( 
            iFlags,
            objWbemNamedValueSet,
      &objWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectSet;
  }

        
public: 
  HRESULT instancesAsync( 
            __in IDispatch *objWbemSink,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemObject* object = get();

    if (FAILED(hr = object->InstancesAsync_( 
        objWbemSink,
        iFlags,
        objWbemNamedValueSet,
        objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;

  }

public: 
  ISWbemObjectSet* subclasses( 
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemObjectSet* pObjWbemObjectSet = NULL;
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->Subclasses_( 
            iFlags,
            objWbemNamedValueSet,
      &pObjWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectSet;
  }

public: 
  HRESULT subclassesAsync( 
            __in IDispatch *objWbemSink,
           __in long iFlags = wbemQueryFlagDeep,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->SubclassesAsync_( 
            objWbemSink,
            iFlags,
            objWbemNamedValueSet,
      objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
        
public: 
  ISWbemObjectSet* associators( 
           __in BSTR strAssocClass,
           __in BSTR strResultClass,
           __in BSTR strResultRole,
           __in BSTR strRole,
           __in VARIANT_BOOL bClassesOnly,
           __in VARIANT_BOOL bSchemaOnly,
           __in BSTR strRequiredAssocQualifier,
           __in BSTR strRequiredQualifier,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet) 
  {
    ISWbemObjectSet* pObjWbemObjectSet = NULL;
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object-> Associators_( 
          strAssocClass,
          strResultClass,
          strResultRole,
          strRole,
          bClassesOnly,
          bSchemaOnly,
          strRequiredAssocQualifier,
          strRequiredQualifier,
          iFlags,
          objWbemNamedValueSet,
          &pObjWbemObjectSet))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectSet;
  }
        
        
public: 
  HRESULT associatorsAsync( 
            __in IDispatch *objWbemSink,
           __in BSTR strAssocClass = L"",
           __in BSTR strResultClass = L"",
           __in BSTR strResultRole = L"",
           __in BSTR strRole = L"",
           __in VARIANT_BOOL bClassesOnly = FALSE,
           __in VARIANT_BOOL bSchemaOnly = FALSE,
           __in BSTR strRequiredAssocQualifier = L"",
           __in BSTR strRequiredQualifier = L"",
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL) 
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object-> AssociatorsAsync_( 
          objWbemSink,
          strAssocClass,
          strResultClass,
          strResultRole,
          strRole,
          bClassesOnly,
          bSchemaOnly,
          strRequiredAssocQualifier,
          strRequiredQualifier,
          iFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
        
public: 
  ISWbemObjectSet* references( 
           __in BSTR strResultClass,
           __in BSTR strRole,
           __in VARIANT_BOOL bClassesOnly,
           __in VARIANT_BOOL bSchemaOnly,
           __in BSTR strRequiredQualifier,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemObjectSet* pObjWbemObjectSet = NULL;
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->References_( 
          strResultClass,
          strRole,
          bClassesOnly,
          bSchemaOnly,
          strRequiredQualifier,
          iFlags,
          objWbemNamedValueSet,
          &pObjWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectSet;
  }
        
        
public: 
  HRESULT feferencesAsync( 
            __in IDispatch *objWbemSink,
           __in BSTR strResultClass = L"",
           __in BSTR strRole = L"",
           __in VARIANT_BOOL bClassesOnly = FALSE,
           __in VARIANT_BOOL bSchemaOnly = FALSE,
           __in BSTR strRequiredQualifier = L"",
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
        
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->ReferencesAsync_( 
          objWbemSink,
          strResultClass,
          strRole,
          bClassesOnly,
          bSchemaOnly,
          strRequiredQualifier,
          iFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        
public: 
  ISWbemObject* execMethod( 
            __in BSTR strMethodName,
           __in IDispatch *objWbemInParameters,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemObject* pObjWbemOutParameters = NULL;
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->ExecMethod_( 
        strMethodName,
        objWbemInParameters,
        iFlags,
        objWbemNamedValueSet,
        &pObjWbemOutParameters))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemOutParameters;
  }
        
public: 
  HRESULT execMethodAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strMethodName,
           __in IDispatch *objWbemInParameters = NULL,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
        
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->ExecMethodAsync_( 
        objWbemSink,
        strMethodName,
        objWbemInParameters,
        iFlags,
        objWbemNamedValueSet,    
        objWbemAsyncContext))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
        

public: 
  ISWbemObject* clone()
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemObject *objWbemObject = NULL;

    if (FAILED(hr = object->Clone_( 
        &objWbemObject))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObject;
  }
        
public: 
  _bstr_t getObjectText( 
           __in long iFlags)
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    BSTR strObjectText=NULL;

    if (FAILED(hr = object->GetObjectText_( 
            iFlags,
      &strObjectText))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strObjectText, false);
  }
        
        
public: 
  ISWbemObject* spawnDerivedClass( 
           __in long iFlags)
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemObject *objWbemObject = NULL;
    if (FAILED(hr = object->SpawnDerivedClass_( 
        iFlags,
        &objWbemObject))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObject;
  }
        

public: 
  ISWbemObject* spawnInstance( 
           __in long iFlags)
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemObject *objWbemObject = NULL;

    if (FAILED(hr = object->SpawnInstance_( 
        iFlags,
        &objWbemObject))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObject;
  }

        
public: 
  bool compareTo( 
            __in IDispatch *objWbemObject,
           __in long iFlags)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object->CompareTo_( 
        objWbemObject,
        iFlags,
        &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }
        
public:
  ISWbemQualifierSet* getQualifiers()
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemQualifierSet *objWbemQualifierSet = NULL;

    if (FAILED(hr = object->get_Qualifiers_( 
      &objWbemQualifierSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemQualifierSet;
  }
        
public:
  ISWbemPropertySet* getProperties()
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemPropertySet *objWbemPropertySet = NULL;

    if (FAILED(hr = object-> get_Properties_( 
      &objWbemPropertySet))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemPropertySet;
  }

        
public:
  ISWbemMethodSet* getMethods()
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemMethodSet *objWbemMethodSet = NULL;

    if (FAILED(hr = object->get_Methods_( 
      &objWbemMethodSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemMethodSet;
  }
        
public:
  _variant_t getDerivation()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();

    if (FAILED(hr = object-> get_Derivation_( 
      &var))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _variant_t(var, false);
  }

public:
   ISWbemObjectPath* getPath() 
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemObjectPath *objWbemObjectPath = NULL;

    if (FAILED(hr = object->get_Path_( 
      &objWbemObjectPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectPath;
  }


public:
  //2009/12/22
  ISWbemSecurity* getSecurity( 
            )
  {
    HRESULT hr = E_FAIL;

    ISWbemObject* object = get();
    ISWbemSecurity *objWbemSecurity = NULL;

    if (FAILED(hr = object->get_Security_( 
      &objWbemSecurity))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemSecurity;
  }


/*
public:
  void display()
  {
    ReportWriter writer;
    report(writer);
  }
*/
public:
  void write(Writer& writer)
  {
    writer.writeln(L"<Object>");
    HTMLEncoder encoder;
    try {
      _bstr_t text = getObjectText(0);
      StringT<wchar_t> wtext;
      encoder.encode((const wchar_t*)text, wtext);
      writer.writeln(L"<ObjectText>%s</ObjectText>", (const wchar_t*)wtext);
      SWbemPropertySet propSet = getProperties();
      propSet.write(writer);
      SWbemObjectPath path = getPath();
      path.write(writer);
      SWbemSecurity security = getSecurity();
      security.write(writer);
    } catch (...) {

    }
    writer.writeln(L"</Object>");

  }

};


}
