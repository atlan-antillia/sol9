/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WbemLocator.h
 *
 *****************************************************************************/

// 2010/03/14
// 2012/03/08 Updated
// 2012/10/12 Updated
#pragma once

#include <sol/com/ComIUnknown.h>
#include <objbase.h>

#include <sol/COMTypeConverter.h>
#include <sol/Writer.h>
#include <sol/FileWriter.h>
#include <sol/ConsoleWriter.h>

#include <sol/LocalDateTime.h>
#include <sol/HTMLEncoder.h>

#pragma comment(lib, "oleaut32.lib")

#include <sol/wmi/WbemServices.h>

namespace SOL {

class WbemLocator : public ComIUnknown {

public:
  WbemLocator()
  :ComIUnknown()
  {
    HRESULT hr = S_OK;
    IDispatch* pDisp = NULL;
    // Create an initial locator to WbemLocator 
    if (FAILED(hr = CoCreateInstance(
        CLSID_WbemLocator,             
        0, 
        CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator, (void**) &pDisp)) ) {

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    } else {
      set(pDisp);    
    }
  }

public:
  ~WbemLocator () 
  {
  }

public:
  IWbemLocator* getLocator()
  {
    IWbemLocator* pLocator = (IWbemLocator*)getIUnknown();
    if (pLocator == NULL) {
      throw Exception(0, "Exception: WbemLocator::getLocator");
    } else {
      return (IWbemLocator*)getIUnknown();
    }
  }

public:
  IWbemServices*  connectServer( 
    __in const BSTR strNetworkResource,
    __in const BSTR strUser=NULL,
            __in const BSTR strPassword=NULL,
            __in const BSTR strLocale=NULL,
            __in long lSecurityFlags=NULL,
            __in const BSTR strAuthority=NULL,
            __in IWbemContext *pCtx=NULL)
  {
    HRESULT hr = S_OK;
    IWbemServices *pServices =NULL;
    IWbemLocator* locator = getLocator();
  
    if (FAILED(hr = locator -> ConnectServer( 
      strNetworkResource,
      strUser,
      strPassword,
      strLocale,
      lSecurityFlags,
      strAuthority,
      pCtx,
      &pServices) )) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    //2012/10/12 Updated
    if (FAILED(hr = CoSetProxyBlanket(
        pServices,                   
        RPC_C_AUTHN_WINNT,           
        RPC_C_AUTHZ_NONE,            
        NULL,                         
        RPC_C_AUTHN_LEVEL_CALL,       
        RPC_C_IMP_LEVEL_IMPERSONATE, 
        NULL,                        
        EOAC_NONE                     
        )) ){

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return pServices;    
  }    


};

}
