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
 *  SWbemServicesEx.h
 *
 *****************************************************************************/



#pragma once

#include <sol/wmi/SWbemServices.h>


namespace SOL {

class SWbemServicesEx :public SWbemServices
{

public:
  SWbemServicesEx(IDispatch* pDisp=NULL)
  :SWbemServices(pDisp)
  {

  }

public:
  ISWbemServicesEx* get()
  {
    return (ISWbemServicesEx*)getIDispatch();
  }

public:
  SWbemServicesEx& operator=(ISWbemServicesEx* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:

  ISWbemObjectPath* put( 
            /* [in] */ ISWbemObjectEx *objWbemObject,
            /* [defaultvalue][in] */ long iFlags,
            /* [defaultvalue][in] */ IDispatch *objWbemNamedValueSet)
  {
    ISWbemObjectPath* pObjWbemObjectPath = NULL;
    HRESULT hr = E_FAIL;
    ISWbemServicesEx* services = get();

    if (FAILED(hr = services -> Put( 
        objWbemObject,
        iFlags,
        objWbemNamedValueSet,
        &pObjWbemObjectPath))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectPath;
  }           
        
public:
  HRESULT putAsync( 
            /* [in] */ ISWbemSink *objWbemSink,
            /* [in] */ ISWbemObjectEx *objWbemObject,
            /* [defaultvalue][in] */ long iFlags = wbemChangeFlagCreateOrUpdate,
            /* [defaultvalue][in] */ IDispatch *objWbemNamedValueSet = 0,
            /* [defaultvalue][in] */ IDispatch *objWbemAsyncContext = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemServicesEx* services = get();

    if (FAILED(hr = services -> PutAsync( 
        objWbemSink,
        objWbemObject,
        iFlags,
        objWbemNamedValueSet,
        objWbemAsyncContext))) {

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }           

};

}
