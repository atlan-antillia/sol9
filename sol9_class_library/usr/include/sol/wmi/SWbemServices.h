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
 *  SWbemServices.h
 *
 *****************************************************************************/

#pragma once

#include <sol\Object.h>
#include <sol/wmi/SWbemBaseObject.h>
#include <sol/wmi/SWbemObjectSet.h>

namespace SOL {

class SWbemServices :public SWbemBaseObject {

public:
  /**
   * Constructor
   * @param nameSpace  WMI namespace
   *  ExampleF_bstr_t(L"ROOT\\CIMV2")
   */
  
  SWbemServices(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {
  }
  
public:
  ISWbemServices* get()
  {
    return (ISWbemServices*)getIDispatch();
  }

public:
  SWbemServices& operator=(ISWbemServices* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  /**
   * Destructor
   */
  ~SWbemServices()
  {
  }


private:
  HRESULT clear() {
    HRESULT hr = S_OK;
    return hr;
  }


public:
   ISWbemObject* get( 
            __in BSTR strObjectPath,
            __in long iFlags,
            __in IDispatch *objWbemNamedValueSet) 
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemObject *objWbemObject = NULL;
  
    if (FAILED(hr = services->Get( 
        strObjectPath,
        iFlags,
        objWbemNamedValueSet,
        &objWbemObject))) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObject;
  }

public:
  HRESULT getAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strObjectPath = L"",
            __in long iFlags = 0,
            __in IDispatch *objWbemNamedValueSet = NULL,
            __in IDispatch *objWbemAsyncContext = NULL)    
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services ->GetAsync( 
          objWbemSink,
          strObjectPath,
          iFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }
 
public:
  HRESULT remove( 
            __in BSTR strObjectPath,
            __in long iFlags = 0,
            __in IDispatch *objWbemNamedValueSet = NULL)  
  {
    HRESULT hr = E_FAIL;
      
    ISWbemServices* services = get();
  
    if (FAILED(hr = services->Delete( 
          strObjectPath,
          iFlags,
          objWbemNamedValueSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return hr;
  }
    
public:
  HRESULT deleteAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strObjectPath,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->DeleteAsync( 
          objWbemSink,
          strObjectPath,
          iFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public:
  ISWbemObjectSet* instancesOf( 
            __in BSTR strClass,
            __in long iFlags,
            __in IDispatch *objWbemNamedValueSet)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemObjectSet *objWbemObjectSet = NULL;

    if (FAILED(hr = services->InstancesOf( 
          strClass,
          iFlags,
          objWbemNamedValueSet,
          &objWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectSet;
  }

public:
  HRESULT instancesOfAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strClass,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services ->InstancesOfAsync( 
        objWbemSink,
        strClass,
        iFlags = 0,
        objWbemNamedValueSet,
        objWbemAsyncContext))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }


public:
  ISWbemObjectSet * subclassesOf( 
           __in BSTR strSuperclass=NULL,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet=NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
      
    ISWbemObjectSet *objWbemObjectSet = NULL;

    if (FAILED(hr = services->SubclassesOf( 
        strSuperclass,
        iFlags,
        objWbemNamedValueSet,
        &objWbemObjectSet))) {
  
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectSet;
  }

public:
  HRESULT subclassesOfAsync( 
            __in IDispatch *objWbemSink,
           __in BSTR strSuperclass = L"",
           __in long iFlags = wbemQueryFlagDeep,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)  
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->SubclassesOfAsync( 
        objWbemSink,
        strSuperclass,
        iFlags,
        objWbemNamedValueSet,
        objWbemAsyncContext))) {      
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }


public:
  // Usage Example:
  // SWbemObjectSet objectSet = services.execQuery(L"Select * where Win32_Process");
  //
  ISWbemObjectSet* execQuery(
            __in BSTR strQuery,
           __in BSTR strQueryLanguage=L"WQL",
           __in long iFlags=wbemFlagReturnImmediately,
           __in IDispatch *objWbemNamedValueSet=NULL)  
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemObjectSet *objectSet = NULL;
    if (FAILED(hr = services->ExecQuery( 
          strQuery,
          strQueryLanguage,
          iFlags,    //0x10
          objWbemNamedValueSet,
          &objectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objectSet;
  }


public:
  HRESULT execQueryAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strQuery,
           __in BSTR strQueryLanguage = L"WQL",
           __in long lFlags = 0,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->ExecQueryAsync( 
          objWbemSink,
          strQuery,
          strQueryLanguage,
          lFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public:
  ISWbemObjectSet* associatorsOf( 
            __in BSTR strObjectPath,
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
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemObjectSet *objWbemObjectSet = NULL;

    if (FAILED(hr = services->AssociatorsOf( 
          strObjectPath,
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
          &objWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectSet;
  }

public:
  HRESULT associatorsOfAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strObjectPath,
           __in BSTR strAssocClass = L"",
           __in BSTR strResultClass = L"",
           __in BSTR strResultRole = L"",
           __in BSTR strRole = L"",
           __in VARIANT_BOOL bClassesOnly = FALSE,
           __in VARIANT_BOOL bSchemaOnly = FALSE,
           __in BSTR strRequiredAssocQualifier = L"",
           __in BSTR strRequiredQualifier = L"",
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = 0,
           __in IDispatch *objWbemAsyncContext = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->AssociatorsOfAsync( 
          objWbemSink,
          strObjectPath,
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
  ISWbemObjectSet* referencesTo( 
            __in BSTR strObjectPath,
           __in BSTR strResultClass,
           __in BSTR strRole,
           __in VARIANT_BOOL bClassesOnly,
           __in VARIANT_BOOL bSchemaOnly,
           __in BSTR strRequiredQualifier,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
      
    ISWbemObjectSet *objWbemObjectSet = NULL;

    if (FAILED(hr = services->ReferencesTo( 
          strObjectPath,
          strResultClass,
          strRole,
          bClassesOnly,
          bSchemaOnly,
          strRequiredQualifier,
          iFlags,
          objWbemNamedValueSet,
          &objWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObjectSet;
  }

public:
  HRESULT referencesToAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strObjectPath,
           __in BSTR strResultClass = L"",
           __in BSTR strRole = L"",
           __in VARIANT_BOOL bClassesOnly = FALSE,
           __in VARIANT_BOOL bSchemaOnly = FALSE,
           __in BSTR strRequiredQualifier = L"",
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = 0,
           __in IDispatch *objWbemAsyncContext = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->ReferencesToAsync( 
          objWbemSink,
          strObjectPath,
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
  // Usage Example:
  // SWbemEventSource eventSource = services.execNotifiationQuery(L"Select * from Win32_Service");
  //
  ISWbemEventSource* execNotificationQuery( 
            __in BSTR strQuery,
           __in BSTR strQueryLanguage=L"WQL",
           __in long iFlags= wbemFlagForwardOnly|wbemFlagReturnImmediately,
           //__in long iFlags= wbemFlagReturnImmediately,

       __in IDispatch *objWbemNamedValueSet=NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
  
    ISWbemEventSource *objWbemEventSource =NULL;

    if (FAILED(hr = services->ExecNotificationQuery(
          strQuery,
          strQueryLanguage,
          iFlags,
          objWbemNamedValueSet,
          &objWbemEventSource))) {
      //2009/12/21 Modified not to throw;
      printf("Failed to execNotificationQuery\n");
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemEventSource;
  }


public:
  HRESULT execNotificationQueryAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strQuery,
           __in BSTR strQueryLanguage = L"WQL",
           __in long iFlags = wbemFlagSendStatus,
       //wbemFlagDontSendStatus,
       //wbemFlagReturnImmediately,
      // wbemFlagForwardOnly,//|wbemFlagReturnImmediately,
           __in IDispatch *objWbemNamedValueSet = NULL,
           __in IDispatch *objWbemAsyncContext = NULL)  
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->ExecNotificationQueryAsync( 
          objWbemSink,
          strQuery,
          strQueryLanguage,
          iFlags,
          objWbemNamedValueSet,
          objWbemAsyncContext))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }


public:  
  ISWbemObject* execMethod( 
            __in BSTR strObjectPath,
            __in BSTR strMethodName,
           __in IDispatch *objWbemInParameters,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemObject *objWbemOutParameters = NULL;

    if (FAILED(hr = services->ExecMethod( 
          strObjectPath,
          strMethodName,
          objWbemInParameters,
          iFlags,
          objWbemNamedValueSet,
          &objWbemOutParameters))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemOutParameters;
  }

public:
  HRESULT execMethodAsync( 
            __in IDispatch *objWbemSink,
            __in BSTR strObjectPath,
            __in BSTR strMethodName,
           __in IDispatch *objWbemInParameters = 0,
           __in long iFlags = 0,
           __in IDispatch *objWbemNamedValueSet = 0,
           __in IDispatch *objWbemAsyncContext = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();

    if (FAILED(hr = services->ExecMethodAsync( 
          objWbemSink,
          strObjectPath,
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
  // Usage Example:
  // SWbemSecurity security = services.getSecurity();
  ISWbemSecurity* getSecurity()
  {
    HRESULT hr = E_FAIL;
    ISWbemServices* services = get();
    ISWbemSecurity *objWbemSecurity = NULL;

    if (FAILED(hr = services->get_Security_( 
            &objWbemSecurity))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemSecurity;
  }

};
  
}


/*
lFlags:

wbemFlagForwardOnly
  Causes a forward-only enumerator to be returned. Forward-only enumerators are generally much faster 
  and use less memory than conventional enumerators, but they do not allow calls to SWbemObject.Clone_.
 
wbemFlagBidirectional
  Causes WMI to retain pointers to objects of the enumeration until the client releases the enumerator.
 
wbemFlagReturnImmediately
  Causes the call to return immediately.
 
wbemFlagReturnWhenComplete
  Causes this call to block until the query is complete. This flag calls the method in the synchronous mode.
 
wbemQueryFlagPrototype
  Used for prototyping. It stops the query from happening and returns an object that looks like a typical 
  result object.
 
wbemFlagUseAmendedQualifiers
  Causes WMI to return class amendment data with the base class definition. For more information, see 
  Localizing WMI Class Information.
 
*/
 


