/******************************************************************************
 *
 * Copyright (c) 2008-2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OleSite.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed an IE browser control 
(an OLE object) or something like that into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/

// SOL9
// 2008/08/10
// 2011/02/21 Updated

#pragma once

#include <sol\Object.h>

#include <exdisp.h>
#include <sol\ole\IHTMLView.h>
#include <oleidl.h>
#include <sol/Stdio.h>

namespace SOL {

/**
 * Implementation of IOleClientSite and IOleInPlaceSite interfaces.
 */
class COleSite: public IOleClientSite, public IOleInPlaceSite {
  
public:
  Composite* host;  //2011/02/21 Modified 

public:
  COleSite()
    :host(NULL)
  {
  }

public:
  //
  // IOleSite
  //
  STDMETHODIMP QueryInterface(REFIID riid, void ** ppvObject)
  {
    if(riid == IID_IDispatch) {
      *ppvObject = (IDispatch*)this;
    }
    if(riid == IID_IUnknown || riid == IID_IOleClientSite) {
      *ppvObject = (IOleClientSite*)this;
    }
    else if(riid == IID_IOleInPlaceSite ) {
      *ppvObject = (IOleInPlaceSite*)this;
    } else if (riid == IID_IOleInPlaceActiveObject ) { //2011/02/23
      *ppvObject = (IOleInPlaceActiveObject*)this;

    } else{
      *ppvObject = NULL;
      return E_NOINTERFACE;
    }
    return S_OK;
  }

  STDMETHODIMP_(ULONG) AddRef(void){
    return 1;
  }


  STDMETHODIMP_(ULONG) Release(void){
    return 1;
  }


// IOleClientSite

  STDMETHODIMP SaveObject(){  
    return E_NOTIMPL;
  }

  STDMETHODIMP GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker ** ppmk) {
    return E_NOTIMPL;
  }


  STDMETHODIMP GetContainer(LPOLECONTAINER FAR* ppContainer){
    // Don't support a container.
    *ppContainer = NULL;
    return E_NOTIMPL;
  }


  STDMETHODIMP ShowObject() {
    //  ;
    return NOERROR;
  }

  STDMETHODIMP OnShowWindow(BOOL fShow){
    return E_NOTIMPL;
  }


  STDMETHODIMP RequestNewObjectLayout(){
    return E_NOTIMPL;
  }

// IOleWindow

  STDMETHODIMP GetWindow(HWND FAR* lphwnd) {
    *lphwnd = NULL;
    if (host) {
      *lphwnd = host->getWindow();
    }
    return S_OK;
  }

  STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode){
    return E_NOTIMPL;
  }

// IOleInPlaceSite

  STDMETHODIMP CanInPlaceActivate() {
  // Yes we can
    return S_OK;
  }

  STDMETHODIMP OnInPlaceActivate() {
     return S_OK;
  }

  STDMETHODIMP OnUIActivate(){
    return S_OK;
  }

  STDMETHODIMP GetWindowContext(
    LPOLEINPLACEFRAME FAR* ppFrame,
    LPOLEINPLACEUIWINDOW FAR* ppDoc,
    LPRECT prcPosRect,
    LPRECT prcClipRect,
    LPOLEINPLACEFRAMEINFO lpFrameInfo)
  {
    HWND hwnd = NULL ;//host->getWindow();
    *ppFrame = NULL; //host->getInPlaceFrame();  
    if (host) {
      hwnd = host->getWindow();
      *ppFrame = host->getInPlaceFrame();  
    }

    *ppDoc = NULL;

    GetClientRect(hwnd, prcPosRect);
    GetClientRect(hwnd, prcClipRect);

    lpFrameInfo->fMDIApp = FALSE;

    lpFrameInfo->hwndFrame = hwnd;
    lpFrameInfo->haccel = NULL;
    lpFrameInfo->cAccelEntries = 0;
    return S_OK;
  }


  STDMETHODIMP Scroll(SIZE scrollExtent){
    return E_NOTIMPL;
  }

  STDMETHODIMP OnUIDeactivate(BOOL fUndoable){
    return S_OK;
  }

  STDMETHODIMP OnInPlaceDeactivate(){
    return S_OK;
  }

  STDMETHODIMP DiscardUndoState(){
    return E_NOTIMPL;
  }

  STDMETHODIMP DeactivateAndUndo(){
    return E_NOTIMPL;
  }

  STDMETHODIMP OnPosRectChange(LPCRECT lprcPosRect)
  {
    //2008/08/05: to-arai
    IOleInPlaceObject* inplace =NULL;
    HRESULT hr = E_FAIL;
    if (host) {
      IOleObject* oleObject = host->getOleObject();
      if (oleObject) {
        if (!oleObject->QueryInterface(IID_IOleInPlaceObject, (void**)&inplace)) {
          hr = inplace->SetObjectRects(lprcPosRect, lprcPosRect);
        }
      }
    }
    return hr;
  }


};

}
