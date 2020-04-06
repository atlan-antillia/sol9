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
 *  ExplorerBrowserEvents.h
 *
 *****************************************************************************/

// SOL9
// 2012/11/11

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class ExplorerBrowserEvents: public IExplorerBrowserEvents {

private:
  IShellView  *pShellView;

public:
  ExplorerBrowserEvents()
  :pShellView(NULL)
  {
  }  

public:
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
      /* [in */ REFIID riid, 
      /* [out */ void** ppv)
  {
    *ppv  = NULL;
    if (IsEqualIID(riid, IID_IUnknown) || 
      IsEqualIID(riid, IID_IExplorerBrowserEvents)) {
      *ppv = static_cast<IExplorerBrowserEvents *>(this);
    } else {
      return E_NOINTERFACE;
    }
  
    return S_OK;  
  }

  ULONG STDMETHODCALLTYPE AddRef()
  {
    return 1;
  }

  
  ULONG STDMETHODCALLTYPE Release()
  {
    return 1;
  }

  virtual HRESULT STDMETHODCALLTYPE OnNavigationPending(
    /* [in */ PCIDLIST_ABSOLUTE pidlFolder)
  {
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE OnViewCreated(
    /* [in */ IShellView *psv)
  {
    pShellView = psv;

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE OnNavigationComplete(
    /* [in */ PCIDLIST_ABSOLUTE pidlFolder)
  {
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE OnNavigationFailed(
    /* [in */ PCIDLIST_ABSOLUTE pidlFolder)
  {
    return S_OK;
  }

public:
  IShellView* getShellView()
  {
    return pShellView;
  }
};

}
