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
 *  ShellWindows.h
 *
 *****************************************************************************/


// SOL9 2012/11/09

#pragma once

#include <sol\Object.h>
#include <exdisp.h>
#include <exdispid.h> 

// IShellWindows interface is defined in ExpDisp.h
//

#include <sol/com/ComIDispatch.h>

namespace SOL {

class ShellWindows: public ComIDispatch {

public:
  ShellWindows()
  :ComIDispatch()
  {
    IShellWindows* pWindows = NULL;
    HRESULT hr = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_ALL, 
        IID_IShellWindows, (void**)&pWindows);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pWindows);
    }

  }

public:
  IShellWindows* getWindows()
  {
    return (IShellWindows*)getIDispatch();
  }

public:
  HRESULT getCount( 
            /* [retval][out] */ long *count)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> get_Count(count);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

/*
If the type of VARI\ANT index of item method is VT_UI4, 
the value of index is interpreted as a member of 
ShellWindowTypeConstants; 
 typedef enum  { 
  SWC_EXPLORER  = 0x0,
  SWC_BROWSER   = 0x00000001,
  SWC_3RDPARTY  = 0x00000002,
  SWC_CALLBACK  = 0x00000004,
  SWC_DESKTOP   = 0x00000008
} ShellWindowTypeConstants;
*/
public:
  HRESULT item( 
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ IDispatch **folder)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> Item(index, folder);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IDispatch* item( 
            /* [optional][in] */ VARIANT index)
  {
    IDispatch* folder = NULL;

    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> Item(index, &folder);
    if (FAILED(hr)) {
      throw hr;
    }
    return folder;
  }
        
public:
  HRESULT newEnum( 
            /* [retval][out] */ IUnknown **ppunk)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> _NewEnum(ppunk);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IUnknown* newEnum()
  {
    IUnknown* punk = NULL;

    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> _NewEnum(&punk);
    if (FAILED(hr)) {
      throw hr;
    }
    return punk;
  }

        
public:
  HRESULT _register( 
            /* [in] */ IDispatch *pid,
            /* [in] */ long hwnd,
            /* [in] */ int swClass,
            /* [out] */long *plCookie) 
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> Register(pid,
        hwnd,
        swClass,
        plCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  long _register( 
            /* [in] */ IDispatch *pid,
            /* [in] */ long hwnd,
            /* [in] */ int swClass) 
  {
    long lCookie = 0;
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> Register(pid,
        hwnd,
        swClass,
        &lCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return lCookie;
  }

public:
  HRESULT registerPending( 
            /* [in] */ long lThreadId,
            /* [in] */ VARIANT *pvarloc,
            /* [in] */ VARIANT *pvarlocRoot,
            /* [in] */ int swClass,
            /* [out] */ long *plCookie)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> RegisterPending( 
      lThreadId,
      pvarloc,
      pvarlocRoot,
      swClass,
      plCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  long registerPending( 
            /* [in] */ long lThreadId,
            /* [in] */ VARIANT *pvarloc,
            /* [in] */ VARIANT *pvarlocRoot,
            /* [in] */ int swClass)
  {
    long lCookie = 0;
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> RegisterPending( 
      lThreadId,
      pvarloc,
      pvarlocRoot,
      swClass,
      &lCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return lCookie;
  }

        
public:
  HRESULT revoke( 
            /* [in] */ long lCookie) 
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> Revoke( 
      lCookie) ;
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT onNavigate( 
            /* [in] */ long lCookie,
            /* [in] */ VARIANT *pvarLoc)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> OnNavigate( 
      lCookie,
      pvarLoc);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT onActivated( 
            /* [in] */ long lCookie,
            /* [in] */ VARIANT_BOOL fActive)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> OnActivated(
      lCookie,
      fActive);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT findWindowSW( 
            /* [in] */ VARIANT *pvarLoc,
            /* [in] */ VARIANT *pvarLocRoot,
            /* [in] */ int swClass,
            /* [out] */ long *phwnd,
            /* [in] */ int swfwOptions,
            /* [retval][out] */ IDispatch **ppdispOut)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> FindWindowSW( 
      pvarLoc,
      pvarLocRoot,
      swClass,
      phwnd,
      swfwOptions,
      ppdispOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IDispatch* findWindowSW( 
            /* [in] */ VARIANT *pvarLoc,
            /* [in] */ VARIANT *pvarLocRoot,
            /* [in] */ int swClass,
            /* [out] */ long *phwnd,
            /* [in] */ int swfwOptions)
  {
    IDispatch* pdispOut = NULL;

    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> FindWindowSW( 
      pvarLoc,
      pvarLocRoot,
      swClass,
      phwnd,
      swfwOptions,
      &pdispOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return pdispOut;
  }

        
public:
  HRESULT onCreated( 
            /* [in] */ long lCookie,
            /* [in] */ IUnknown *punk)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> OnCreated( 
      lCookie,
      punk);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT processAttachDetach( 
            /* [in] */ VARIANT_BOOL fAttach)
  {
    IShellWindows* pWindows = getWindows();
    HRESULT hr = pWindows -> ProcessAttachDetach( 
       fAttach);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
};

}
