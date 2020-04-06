/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OleInPlaceFrame.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed a IE browser control 
(an OLE object) into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/

// SOL9
// 2008/08/10

#pragma once

#include <sol\Object.h>


#include <exdisp.h>


#include <sol\ole\IHTMLView.h>
#include <sol\ole\OleSite.h>
#include <sol/Stdio.h>

namespace SOL {

/**
 * Implementation ofIOleInPlaceFrame interface.
 */
class COleInPlaceFrame :public IOleInPlaceFrame
{
public:
  //IHTMLView* host;
  Composite* host;

public:
  COleInPlaceFrame()
    :host(NULL)
  {
  }

  //
  // COleInPlaceFrame
  //
public:
  // IUnknown
  STDMETHODIMP QueryInterface(REFIID riid, void ** ppvObject){
    return E_NOTIMPL;
  }

  STDMETHODIMP_(ULONG) AddRef(void){
    return 1;
  }

  STDMETHODIMP_(ULONG) Release(void){
    return 1;
  }

  // IOleWindow
  STDMETHODIMP GetWindow(HWND FAR* lphwnd) {
  //depends on host->getWindow();
    *lphwnd = NULL;
    if (host) {
      *lphwnd = host->getWindow();
    }
    return S_OK;
  }

  STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode){
    return E_NOTIMPL;
  }

  // IOleInPlaceUIWindow
  STDMETHODIMP GetBorder(LPRECT lprectBorder){
    return E_NOTIMPL;
  }

  STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS pborderwidths){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS pborderwidths){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName){
    return S_OK;
  }

  // IOleInPlaceFrame
  STDMETHODIMP InsertMenus(HMENU hmenuShared,LPOLEMENUGROUPWIDTHS lpMenuWidths){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject){
    return S_OK;
  }

  STDMETHODIMP RemoveMenus(HMENU hmenuShared){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetStatusText(LPCOLESTR pszStatusText){
    return S_OK;
  }

  STDMETHODIMP EnableModeless(BOOL fEnable){
    return S_OK;
  }

  STDMETHODIMP TranslateAccelerator(LPMSG lpmsg, WORD wID){
    return E_NOTIMPL;
  }
};

}
