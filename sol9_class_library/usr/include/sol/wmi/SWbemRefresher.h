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
 *  SWbemRefresher.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>

namespace SOL {


class SWbemRefresher :public SWbemBaseObject {
   
public:
  SWbemRefresher(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemRefresher* get()
  {
    return (ISWbemRefresher*)getIDispatch();
  }

public:
  SWbemRefresher& operator=(ISWbemRefresher* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  HRESULT get__NewEnum( 
            __out IUnknown **pUnk)
  {
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> get__NewEnum( 
        pUnk))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  ISWbemRefreshableItem* item( 
            __in long iIndex)
  {
    ISWbemRefreshableItem* pObjWbemRefreshableItem = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> Item( 
        iIndex,
        &pObjWbemRefreshableItem))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemRefreshableItem;
  }        
        

public:
  long getCount()
  {
    long count = 0;
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> get_Count( 
          &count))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return count;
  }        
        

public:
  ISWbemRefreshableItem* add( 
            __in ISWbemServicesEx *objWbemServices,
            __in BSTR bsInstancePath,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemRefreshableItem* pObjWbemRefreshableItem = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> Add( 
        objWbemServices,
        bsInstancePath,
        iFlags,
        objWbemNamedValueSet,
        &pObjWbemRefreshableItem))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemRefreshableItem;
  }        
        

public:
  ISWbemRefreshableItem* addEnum( 
            __in ISWbemServicesEx *objWbemServices,
            __in BSTR bsClassName,
           __in long iFlags,
           __in IDispatch *objWbemNamedValueSet)
  {
    ISWbemRefreshableItem *pOobjWbemRefreshableItem = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> AddEnum( 
         objWbemServices,
         bsClassName,
        iFlags,
        objWbemNamedValueSet,
        &pObjWbemRefreshableItem))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pOobjWbemRefreshableItem;
  }        
        

public:
  HRESULT remove( 
            __in long iIndex,
           __in long iFlags = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> Remove( 
        iIndex,
        iFlags))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  HRESULT refresh( 
           __in long iFlags = 0)
  {
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> Refresh( 
          iFlags))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  bool getAutoReconnect()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> get_AutoReconnect( 
        &vbool))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }        
        

public:
  HRESULT putAutoReconnect( 
            __in bool bCount)
  {
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> put_AutoReconnect( 
        toVariantBool(bCount) ))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  HRESULT deleteAll()         
  {
    HRESULT hr = E_FAIL;
    ISWbemRefresher* refresher = get();

    if (FAILED(hr = refresher -> DeleteAll))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


};

}

