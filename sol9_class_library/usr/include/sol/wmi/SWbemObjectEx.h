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
 *  SWbemObjectEx.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemObject.h>


namespace SOL {

class SWbemObjectEx :public SWbemObject {
    
public:
  SWbemObjectEx(IDispatch* pDisp=NULL)
  :SWbemObject(pDisp)
  {

  }

public:
  ISWbemObjectEx* get()
  {
    return (ISWbemObjectEx*)getIDispatch();
  }
public:
  SWbemObjectEx& operator=(ISWbemObjectEx* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  HRESULT refresh( 
            __in long iFlags = 0,
            __in IDispatch *objWbemNamedValueSet = NULL)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectEx* object = get();

    if (FAILED(hr = object -> Refresh_( 
        iFlags,
        objWbemNamedValueSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  //2009/12/21
  ISWbemPropertySet* getSystemProperties()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectEx* object = get();
    ISWbemPropertySet *objWbemPropertySet = NULL;

    if (FAILED(hr = object -> get_SystemProperties_( 
      &objWbemPropertySet)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemPropertySet;
  }        

public:
  //2009/12/21
  _bstr_t getText( 
            __in WbemObjectTextFormatEnum iObjectTextFormat,
            __in long iFlags,
            __in IDispatch *objWbemNamedValueSet)
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectEx* object = get();
    BSTR bsText = NULL;

    if (FAILED(hr = object -> GetText_( 
        iObjectTextFormat,
        iFlags,
        objWbemNamedValueSet,
        &bsText))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(bsText, false);
  }        

        

public:
  HRESULT setFromText( 
            __in _bstr_t bsText,
            __in WbemObjectTextFormatEnum iObjectTextFormat,
            __in long iFlags = 0,
            __in IDispatch *objWbemNamedValueSet = NULL)
        
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectEx* object = get();

    if (FAILED(hr = object -> SetFromText_( 
        (BSTR)bsText,
        iObjectTextFormat,
        iFlags,
        objWbemNamedValueSet))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

};

}
