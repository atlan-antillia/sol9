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
 *  NetFwAuthorizedApplications.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <sol/com/EnumVariant.h>
#include <netfw.h>
#include <sol/netfw/NetFwAuthorizedApplication.h>
#include <sol/Writer.h>

/*
NetFwMgr mgr;
NetFwPolicy  policy = mgr.getLocalPolicy();
NetFwProfile profile = policy.getCurrentProfile();
NetFwAuthorizedApplications apps = profile.getAuthorizedApplications();
*/

namespace SOL {

class NetFwAuthorizedApplications: public ComIDispatch {
    

public:
  NetFwAuthorizedApplications(INetFwAuthorizedApplications* pApps)
    :ComIDispatch(pApps)
  {
  }

private:
  INetFwAuthorizedApplications* getApps()
  {
    return (INetFwAuthorizedApplications*) getIDispatch();
  }


public:
  HRESULT getCount( 
            /* [retval][out] */ long *count)
  {
    HRESULT hr = getApps() -> get_Count( 
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
    HRESULT hr = getApps() -> get_Count( 
        &count);
    if (FAILED(hr)) {
      throw hr;
    }
    return count;
  }

public:        
  HRESULT add( 
            /* [in] */ INetFwAuthorizedApplication *app)
  {
    HRESULT hr = getApps() -> Add( 
        app);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT remove( 
            /* [in] */ BSTR imageFileName)
  {
    HRESULT hr = getApps() -> Remove( 
        imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT item( 
            /* [in] */ BSTR imageFileName,
            /* [retval][out] */ INetFwAuthorizedApplication **app)
  {
    HRESULT hr = getApps() -> Item( 
        imageFileName,
        app);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwAuthorizedApplication* item( 
            /* [in] */ BSTR imageFileName)
  {
    INetFwAuthorizedApplication* pApp = NULL;
    HRESULT hr = getApps() -> Item( 
        imageFileName,
        &pApp);
    if (FAILED(hr)) {
      throw hr;
    }
    return pApp;
  }

public:
  HRESULT getNewEnum( 
            /* [retval][out] */ IUnknown **newEnum)
  {
    HRESULT hr = getApps() -> get__NewEnum( 
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
    HRESULT hr = getApps() -> get__NewEnum( 
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
    _tprintf(_T("<AuthorizedApplications count='%d'>\n"), getCount() );

    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwAuthorizedApplication));
        NetFwAuthorizedApplication authorizedApplication((INetFwAuthorizedApplication*)pDisp);
        authorizedApplication.display();
      } catch (...) {
        break;
      }
    }
    _tprintf(_T("</AuthorizedApplications>\n"));

  }

public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<AuthorizedApplications count='%d'>\n", getCount() );

    EnumVariant enumVariant = getEnumVariant();
    bool looping = true;
    while (looping) {
      try {
        ComIDispatch dispatch = enumVariant.next();
        IDispatch* pDisp = dispatch.queryInterface(__uuidof(INetFwAuthorizedApplication));
        NetFwAuthorizedApplication authorizedApplication((INetFwAuthorizedApplication*)pDisp);
        authorizedApplication.write(writer);
      } catch (...) {
        break;
      }
    }
    writer.write(L"</AuthorizedApplications>\n");

  }

};

}
