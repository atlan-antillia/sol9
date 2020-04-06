/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  MediaEvents.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2011/02/21

// MediaEvents Listener class to implement IWMPEvents interface.
// Please derived your own listener class from this class.

#pragma once

#include <sol\Object.h>

#include <exdisp.h>
#include <exdispid.h> 

namespace SOL {

class MediaEvents :public IWMPEvents {

private:
  DWORD dwCookie;

public:
  /**
   * Constructor
   */
  MediaEvents()
    :dwCookie(0)
  {
  }

public:
  virtual ~MediaEvents()
  {
  }

public:
  STDMETHODIMP_(ULONG) AddRef()
  {
    return 1;
  }

public:
  STDMETHODIMP_(ULONG) Release()
  {
    return 1;
  }

public:
  STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
  {
    if(riid == IID_IUnknown) {
      //printf("IUnknown\n");
      *ppv = (IUnknown*)this;
    } else if(riid == IID_IDispatch) {
      //printf("IDispatch\n");
      *ppv = (IDispatch*)this;
    } else if(riid == __uuidof(IWMPEvents)) {;// IOleWindow)) {//IOleClientSite)) {
      //printf("IWMPEvents\n");
      *ppv = (IDispatch*)this;
    } else if(riid == __uuidof(IOleInPlaceSite)) {
      //printf("IOlceInPlaceSite\n");
      *ppv = (IDispatch*)this;
    } else {
      //printf("Other\n");
      *ppv = this;
      return S_OK;
    }  
    return S_OK;
  }

public:
  STDMETHODIMP GetTypeInfoCount(UINT* /*pCountTypeInfo*/)
  {
    return S_OK;
  }

public:
  STDMETHODIMP GetTypeInfo(UINT /* iTypeInfo */, LCID /* lcid */ , ITypeInfo** /* ppITypeInfo */)
  {
    return S_OK;
  }

public:
  STDMETHODIMP GetIDsOfNames(
    REFIID          /* riid */, 
    LPOLESTR*       /* rgszNames */ ,   
    UINT            /* cNames */, 
    LCID            /* lcid */, 
    DISPID*         /* rgDispId*/ )
  {
    return S_OK;
  }

public:
  STDMETHODIMP Advise(IUnknown* pUnkCP, const IID& iid)
  {
    if(pUnkCP == NULL) {
      return E_INVALIDARG;
    }

    IConnectionPointContainer* pCPC =NULL;
    HRESULT hr = pUnkCP->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<void**>(&pCPC));
    if (SUCCEEDED(hr)) {

      IConnectionPoint* pCP = NULL;
      hr = pCPC->FindConnectionPoint(iid, 
        &pCP);
      if (SUCCEEDED(hr)) {
        hr = pCP->Advise((IDispatch*)this, &dwCookie);
        pCP->Release();
      } else {
        //MessageBox(NULL, _T("Failed in connectionPointerContainer"), _T(""), MB_OK);
      }
      pCPC->Release();  
    } else {
      //MessageBox(NULL, _T("Failed in connectionPointerContainer2"), _T(""), MB_OK);
    }
    return hr;
  }


public:
  STDMETHODIMP Unadvise(IUnknown* pUnkCP, const IID& iid)
  {
    if(pUnkCP == NULL) {
      return E_INVALIDARG;
    }

    IConnectionPointContainer* pCPC =NULL;
    HRESULT hr = pUnkCP->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<void**>(&pCPC));
    if (SUCCEEDED(hr)) {
      IConnectionPoint* pCP = NULL;
      hr = pCPC->FindConnectionPoint(iid, &pCP);
      
      if (SUCCEEDED(hr)) {
        hr = pCP->Unadvise(dwCookie);
        pCP->Release();
      } else {
        //MessageBox(NULL, _T("Failed in connectionPointerContainer"), _T(""), MB_OK);
      }
      pCPC->Release();
    } else {
      //MessageBox(NULL, _T("Failed in connectionPointerContainer2"), _T(""), MB_OK);
    }
    return hr;
  }

public:
  //Please redfine the following methods in your own listener class derived from this class.
  virtual HRESULT Invoke(  
    DISPID             /* dispIdMember */ ,
    REFIID             /* riid */ ,
    LCID               /* lcid */ ,
    WORD               /* wFlags */ ,
    DISPPARAMS FAR*    /* pDispParams */ ,
    VARIANT FAR*       /* pVarResult */ ,
    EXCEPINFO FAR*     /* pExcepInfo */ ,
    unsigned int FAR*  /* puArgErr */)
  {
    HRESULT hr = S_OK;
    return hr;
  }

  virtual void __stdcall OpenStateChange(
    __in long /* NewState */) 
  {
  }

  virtual void __stdcall PlayStateChange(
    __in long /* NewState */)
  {
    /*
    if(NewState == 1) {
      printf("Play finished\n");  
    }
    if(NewState == 3) {
      printf("Play started\n");  
    }
    */
  }

  virtual void __stdcall AudioLanguageChange(
    __in long /* LangID */) 
  {
  }

  virtual void __stdcall StatusChange() 
  {
  }

  virtual void __stdcall ScriptCommand(
    __in BSTR /* scType */,
    __in BSTR /* Param  */)
  {
  }

  virtual void __stdcall NewStream()
  {
  }

  virtual void __stdcall Disconnect(
    __in long Result) 
  {
  }

  virtual void __stdcall Buffering(
    __in VARIANT_BOOL /* Start */) 
  {
  }

  virtual void __stdcall Error()
  {
  }

  virtual void __stdcall Warning(
    __in long /* WarningType */,
    __in long /* Param */ ,
    __in BSTR /* Description */)
  {
  }

  virtual void __stdcall EndOfStream(
    __in long /* Result */) 
  {
  }

  virtual void __stdcall PositionChange(
    __in double /* oldPosition */,
    __in double /* newPosition */) 
  {
  }

  virtual void __stdcall MarkerHit(
    __in long /* MarkerNum */) 
  {
  }

  virtual void __stdcall DurationUnitChange(
    __in long /* NewDurationUnit */)
  {
  }

  virtual void __stdcall CdromMediaChange(
    __in long /* CdromNum */) 
  {
  }

  virtual void __stdcall PlaylistChange(
    __in IDispatch * Playlist,
    __in enum WMPPlaylistChangeEventType /* change */)
  {
  }

  virtual void __stdcall CurrentPlaylistChange(
    __in enum WMPPlaylistChangeEventType /* change */) 
  {
  }

  virtual void __stdcall CurrentPlaylistItemAvailable(
    __in BSTR bstrItemName) 
  {
  }

  virtual void __stdcall MediaChange(
    __in IDispatch* /*Item*/ ) 
  {
  }

  virtual void __stdcall CurrentMediaItemAvailable(
    __in BSTR /* bstrItemName */) 
  {
  }

  virtual void __stdcall CurrentItemChange(
    __in IDispatch * /* pdispMedia */) 
  {
  }

  virtual void __stdcall MediaCollectionChange() 
  {
  }

  virtual void __stdcall MediaCollectionAttributeStringAdded(
    __in BSTR /* bstrAttribName */,
    __in BSTR /* bstrAttribVal  */) 
  {
  }

  virtual void __stdcall MediaCollectionAttributeStringRemoved(
    __in BSTR /* bstrAttribName */,
    __in BSTR /* bstrAttribVal */) 
  {
  }

  virtual void __stdcall MediaCollectionAttributeStringChanged(
    __in BSTR /* bstrAttribName */ ,
    __in BSTR /* bstrOldAttribVal */ ,
    __in BSTR /* bstrNewAttribVal */) 
  {
  }

  virtual void __stdcall PlaylistCollectionChange() 
  {
  }

  virtual void __stdcall PlaylistCollectionPlaylistAdded(
    __in BSTR /* bstrPlaylistName*/ ) 
  {
  }

  virtual void __stdcall PlaylistCollectionPlaylistRemoved(
    __in BSTR /* bstrPlaylistName */) 
  {
  }

  virtual void __stdcall PlaylistCollectionPlaylistSetAsDeleted(
    __in BSTR         /* bstrPlaylistName */ ,
    __in VARIANT_BOOL /* varfIsDeleted */)
  {
  }

  virtual void __stdcall ModeChange(
    __in BSTR ModeName,
    __in VARIANT_BOOL /* NewValue */ ) 
  {
  }

  virtual void __stdcall MediaError(
    __in IDispatch* /* pMediaObject */ ) 
  {
  }

  virtual void __stdcall OpenPlaylistSwitch(
    __in IDispatch* /* pItem */)
  {
  }

  virtual void __stdcall DomainChange(
    __in BSTR /* strDomain */) 
  {
  }

  virtual void __stdcall SwitchedToPlayerApplication()
  {
  }

  virtual void __stdcall SwitchedToControl() 
  {
  }

  virtual void __stdcall PlayerDockedStateChange() 
  {
  }

  virtual void __stdcall PlayerReconnect() 
  {
  }

  virtual void __stdcall Click(
    __in short /* nButton */ ,
    __in short /* nShiftState */ ,
    __in long  /* fX */ ,
    __in long  /* fY */) 
  { 
  }

  virtual void __stdcall DoubleClick(
    __in short /* nButton */ ,
    __in short /* nShiftState */ ,
    __in long  /* fX */ ,
    __in long  /* fY */) 
  { 
  }

  virtual void __stdcall KeyDown(
    __in short /* nKeyCode */ ,
    __in short /* nShiftState */ ) 
  { 
  }

  virtual void __stdcall KeyPress(
    __in short /* nKeyAscii */ ) 
  { 
  }

  virtual void __stdcall KeyUp(
    __in short /* nKeyCode */ ,
    __in short /* nShiftState */) 
  { 
  }

  virtual void __stdcall MouseDown(
    __in short /* nButton */ ,
    __in short /* nShiftState */ ,
    __in long  /* fX */,
    __in long  /* fY */) 
  { 
  }

  virtual void __stdcall MouseMove(
    __in short /* nButton */ ,
    __in short /* nShiftState */,
    __in long  /* fX */,
    __in long  /* fY */) 
  { 
  }

  virtual void __stdcall MouseUp(
    __in short /* nButton */ ,
    __in short /* nShiftState */ ,
    __in long  /* fX */ ,
    __in long  /* fY */) 
  { 
  }

};


}
