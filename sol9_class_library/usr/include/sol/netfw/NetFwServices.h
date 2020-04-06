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
 *  NetFwServices.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <sol/com/EnumVariant.h>
#include <netfw.h>
#include <sol/netfw/NetFwService.h>
#include <sol/Writer.h>

/*
NetFwMgr mgr;
NetFwPolicy  policy = mgr.getLocalPolicy();
NetFwProfile profile = policy.getCurrentProfile();
NetFwServices services = profile.getServices();
*/

namespace SOL {

class NetFwServices: public ComIDispatch {
    
public:
  NetFwServices(INetFwServices* pServices)
    :ComIDispatch(pServices)
  {
  }

private:
  INetFwServices* getServices()
  {
    return (INetFwServices*) getIDispatch();
  }

public:
  HRESULT getCount( 
            /* [retval][out] */ long *count)
  {
    HRESULT hr = getServices() -> get_Count( 
          count);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  long getCount()
  {
    long count = 0;
    HRESULT hr = getServices() -> get_Count( 
          &count);
    if (FAILED(hr)) {
      throw hr;
    }
    return count;
  }

public:
  HRESULT item( 
            /* [in] */ NET_FW_SERVICE_TYPE svcType,
            /* [retval][out] */ INetFwService **service)
  {
    HRESULT hr = getServices() -> Item( 
          svcType,
          service);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

/*
typedef enum NET_FW_SERVICE_TYPE_ { 
  NET_FW_SERVICE_FILE_AND_PRINT,
  NET_FW_SERVICE_UPNP,
  NET_FW_SERVICE_REMOTE_DESKTOP,
  NET_FW_SERVICE_NONE,
  NET_FW_SERVICE_TYPE_MAX 
} NET_FW_SERVICE_TYPE;
*/

public:
  INetFwService* item( 
            /* [in] */ NET_FW_SERVICE_TYPE svcType)
  {
    INetFwService* pService = NULL;
    HRESULT hr = getServices() -> Item( 
          svcType,
          &pService);
    if (FAILED(hr)) {
      throw hr;
    }
    return pService;
  }

public:
  HRESULT getNewEnum( 
            /* [retval][out] */ IUnknown **newEnum)
  {
    HRESULT hr = getServices() -> get__NewEnum( 
          newEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  IUnknown* getNewEnum()
  {
    IUnknown* pEnum = NULL;
    HRESULT hr = getServices() -> get__NewEnum( 
          &pEnum);
    if (FAILED(hr)) {
      throw hr;
    }
    return pEnum;
  }

public:
  IEnumVARIANT* getEnumVariant()
  {
    ComIUnknown unknown = getNewEnum();
    return unknown.getEnumVariant();
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("<Services count='%d'>\n"), getCount() );

    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwService));
        NetFwService service((INetFwService*)pDisp);
        service.display();
      } catch (...) {
        break;
      }
    }
    _tprintf(_T("</Services>\n"));

  }

public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<Services count='%d'>\n", getCount() );

    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwService));
        NetFwService service((INetFwService*)pDisp);
        service.write(writer);
      } catch (...) {
        break;
      }
    }
    writer.write(L"</Services>\n");
  }

};

}

