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
 *  SWbemRefreshableItem.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.


#pragma once

#include <sol/wmi/SWbemBaseObject.h>


namespace SOL {

class SWbemRefreshableItem : public SWbemBaseObject {

public:
  SWbemRefreshableItem(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemRefreshableItem* get()
  {
    return (ISWbemRefreshableItem*)getIDispatch();
  }

public:
  SWbemRefreshableItem& operator=(ISWbemRefreshableItem* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  long getIndex()
  {
    long index = 0;
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> get_Index( 
        &index))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return index;
  }        
        

public:
  ISWbemRefresher* getRefresher()
  {
    ISWbemRefresher* pObjWbemRefresher = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> get_Refresher( 
        &pObjWbemRefresher))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemRefresher;
  }        
        

public:
  bool getIsSet()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> get_IsSet( 
        &vbool))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }        
        

public:
  ISWbemObjectEx* getObject()
  {
    ISWbemObjectEx* pObjWbemObject = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> get_Object( 
          &pObjWbemObject))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObject;
  }        
        

public:
  ISWbemObjectSet* getObjectSet()
  {
    ISWbemObjectSet* pObjWbemObjectSet = NULL;
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> get_ObjectSet( 
        &pObjWbemObjectSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObjectSet;
  }        
        

public:
  HRESULT remove( 
           __in long iFlags = 0)
        
  {
    HRESULT hr = E_FAIL;
    ISWbemRefreshableItem* refreshable = get();

    if (FAILED(hr = refreshable -> Remove( 
        iFlags ))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

};

}
