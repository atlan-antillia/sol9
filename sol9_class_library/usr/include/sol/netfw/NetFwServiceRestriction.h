/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  NetFwServiceRestriction.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwRules.h>
#include <sol/Writer.h>

namespace SOL {

class NetFwServiceRestriction: public ComIDispatch {
public:
  NetFwServiceRestriction(INetFwServiceRestriction* pRestriction)
    :ComIDispatch(pRestriction)
  {
  }


private:
  INetFwServiceRestriction* getRestriction()
  {
    return (INetFwServiceRestriction*) getIDispatch();
  }

public:
  HRESULT restrictService( 
            /* [in] */ BSTR serviceName,
            /* [in] */ BSTR appName,
            /* [in] */ VARIANT_BOOL restrictService,
            /* [in] */ VARIANT_BOOL serviceSidRestricted)
  {
    HRESULT hr = getRestriction() -> RestrictService( 
            serviceName,
            appName,
            restrictService,
            serviceSidRestricted);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT restrictService( 
            /* [in] */ BSTR serviceName,
            /* [in] */ BSTR appName,
            /* [in] */ bool restrictService,
            /* [in] */ bool serviceSidRestricted)
  {
    HRESULT hr = getRestriction() -> RestrictService( 
            serviceName,
            appName,
            toVariantBool(restrictService),
            toVariantBool(serviceSidRestricted) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT serviceRestricted( 
            /* [in] */ BSTR serviceName,
            /* [in] */ BSTR appName,
            /* [retval][out] */ VARIANT_BOOL *serviceRestricted)
  {
    HRESULT hr = getRestriction() -> ServiceRestricted( 
          serviceName,
          appName,
          serviceRestricted);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool serviceRestricted( 
            /* [in] */ BSTR serviceName,
            /* [in] */ BSTR appName)
  {
    VARIANT_BOOL serviceRestricted;
    HRESULT hr = getRestriction() -> ServiceRestricted( 
          serviceName,
          appName,
          &serviceRestricted);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(serviceRestricted);
  }

public:
  HRESULT getRules( 
            /* [retval][out] */ INetFwRules **rules)
  {
    HRESULT hr = getRestriction() -> get_Rules( 
        rules);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwRules* getRules()
  {
    INetFwRules* pRules = NULL;
    HRESULT hr = getRestriction() -> get_Rules( 
        &pRules);
    if (FAILED(hr)) {
      throw hr;
    }
    return pRules;
  }
    
public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("<ServiceRestriction>\n"));

    NetFwRules rules = getRules();
    rules.display(hwnd);
    _tprintf(_T("</ServiceRestriction>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<ServiceRestriction>\n");

    NetFwRules rules = getRules();
    rules.write(writer);
    writer.write(L"</ServiceRestriction>\n");
  }
};
}

