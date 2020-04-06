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
 *  SWbemEventSource.h
 *
 *****************************************************************************/

//\ 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>

namespace SOL {

class SWbemEventSource :public SWbemBaseObject {

public:
  SWbemEventSource(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemEventSource* get()
  {
    return (ISWbemEventSource*)getIDispatch();
  }

public:
  SWbemEventSource& operator=(ISWbemEventSource* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  ISWbemObject * nextEvent( 
           __in long iTimeoutMs)
  {
    HRESULT hr = E_FAIL;
    ISWbemEventSource* source = get();
    ISWbemObject *objWbemObject = NULL;
    hr = source -> NextEvent( 
      iTimeoutMs,
      &objWbemObject);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemObject;
  }

                

public:
  ISWbemSecurity* getSecurity_()
  {
    ISWbemSecurity* pObjWbemSecurity = NULL;
    HRESULT hr = E_FAIL;
    ISWbemEventSource* source = get();
  
    hr = source ->get_Security_( 
        &pObjWbemSecurity);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemSecurity;
  }
};


}

