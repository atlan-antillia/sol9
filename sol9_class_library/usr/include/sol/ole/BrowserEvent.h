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
 *  BrowserEvent.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed a IE browser control 
(an OLE object) into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/

// SOL9
#pragma once

#include <sol\Object.h>

#include <exdisp.h>
#include <exdispid.h> 
#include <sol/Stdio.h>

namespace SOL {

#define WM_BROWSER_DOCUMENTCOMPLETE  (WM_USER+2010)

class BrowserEvent :public IDispatch
{

private:
  IWebBrowser2* webBrowser;

private:
  DWORD dwCookie;

private:
  LPDISPATCH pDisp;

private:
  HWND  hParent;

public:
  /**
   * Constructor
   */
  BrowserEvent()
    :dwCookie(0),
    webBrowser(NULL),
    pDisp(NULL),
    hParent(NULL)
  {
  }

public:
  virtual ~BrowserEvent()
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
      *ppv = (IUnknown*)this;
    } else if(riid == IID_IDispatch) {
      *ppv = (IDispatch*)this;
    } else {
      *ppv = NULL;
      return E_NOINTERFACE;
    }
    return S_OK;
  }

public:
  STDMETHODIMP GetTypeInfoCount(UINT* pCountTypeInfo)
  {
    return S_OK;
  }

public:
  STDMETHODIMP GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
  {
    return S_OK;
  }

public:
  STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,   
    UINT cNames, LCID lcid, DISPID* rgDispId)
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
      hr = pCPC->FindConnectionPoint(iid, &pCP);
      if (SUCCEEDED(hr)) {
        hr = pCP->Advise(this, &dwCookie);
        pCP->Release();
      }
      pCPC->Release();  
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
      }
      pCPC->Release();
    }
    return hr;
  }


public:
  /**
   * Register DWebBrowserEvents2 to IWebBrowser2.
   */
  STDMETHODIMP Advise(HWND hwnd, IWebBrowser2* pIE)
  {
    this->hParent = hwnd;
    HRESULT hr = Advise(pIE, __uuidof(DWebBrowserEvents2));
    this->webBrowser = pIE;
    this->webBrowser->AddRef();

    return hr;
  }

public:
  /*
   * Unregister DWebBrowserEvents2 to IWebBrowser2.
   */
  STDMETHODIMP Unadvise()
  {
    HRESULT hr = Unadvise(this->webBrowser, __uuidof(DWebBrowserEvents2));
    this->webBrowser->Release();
    this->webBrowser = NULL;

    return hr;
  }


public:
  STDMETHODIMP Invoke(DISPID dispidMember,
      REFIID riid, LCID lcid, 
      WORD wFlags,
      DISPPARAMS* dispParams,
      VARIANT* pvarResult,
      EXCEPINFO* pExcepInfo,
      UINT* puArgErr)
  {
    if (pvarResult) {
      V_I4(pvarResult) = 0;//VARIANT_TRUE;
    }

    if (!dispParams) {
      return E_INVALIDARG;
    }

    switch (dispidMember) {

    case DISPID_BEFORENAVIGATE2:
      {
        //BSTR burl = dispParams->rgvarg[5].pvarVal->bstrVal;
      }
      break;

    case DISPID_ERROREVENT:
      {
      }
      break;

    case DISPID_NAVIGATECOMPLETE2:
      {
      //BSTR burl = dispParams->rgvarg[0].pvarVal->bstrVal;
      //Store dispID to this memeber varialbe this->pDisp;
      this->pDisp = dispParams->rgvarg[1].pdispVal;
      }
      break;

    case DISPID_DOCUMENTCOMPLETE:
      {
      //BSTR burl = dispParams->rgvarg[0].pvarVal->bstrVal;
      LPDISPATCH pDisp2 = dispParams->rgvarg[1].pdispVal;

        if (this->pDisp && this->pDisp == pDisp2) {
          PostMessage(hParent, WM_BROWSER_DOCUMENTCOMPLETE, 0, 0);
        }
      }
      break;

    case DISPID_ONQUIT:
            //AtlUnadvise(pBrowser, DIID_DWebBrowserEvents2, cookie);
      
      Unadvise();
      break;

    default: 
      break;
    }
    return S_OK;
  }

/*
#define DISPID_BEFORENAVIGATE2              250           // hyperlink clicked on
#define DISPID_NEWWINDOW2                   251
#define DISPID_NAVIGATECOMPLETE2            252           // UIActivate new document
#define DISPID_ONQUIT                       253
#define DISPID_ONVISIBLE                    254           // sent when the window goes visible/hidden
#define DISPID_ONTOOLBAR                    255           // sent when the toolbar should be shown/hidden
#define DISPID_ONMENUBAR                    256           // sent when the menubar should be shown/hidden
#define DISPID_ONSTATUSBAR                  257           // sent when the statusbar should be shown/hidden
#define DISPID_ONFULLSCREEN                 258           // sent when kiosk mode should be on/off
#define DISPID_DOCUMENTCOMPLETE             259           // new document goes ReadyState_Complete
#define DISPID_ONTHEATERMODE                260           // sent when theater mode should be on/off
#define DISPID_ONADDRESSBAR                 261           // sent when the address bar should be shown/hidden
#define DISPID_WINDOWSETRESIZABLE           262           // sent to set the style of the host window frame
#define DISPID_WINDOWCLOSING                263           // sent before script window.close closes the window 
#define DISPID_WINDOWSETLEFT                264           // sent when the put_left method is called on the WebOC
#define DISPID_WINDOWSETTOP                 265           // sent when the put_top method is called on the WebOC
#define DISPID_WINDOWSETWIDTH               266           // sent when the put_width method is called on the WebOC
#define DISPID_WINDOWSETHEIGHT              267           // sent when the put_height method is called on the WebOC 
#define DISPID_CLIENTTOHOSTWINDOW           268           // sent during window.open to request conversion of dimensions
#define DISPID_SETSECURELOCKICON            269           // sent to suggest the appropriate security icon to show
#define DISPID_FILEDOWNLOAD                 270           // Fired to indicate the File Download dialog is opening
#define DISPID_NAVIGATEERROR                271           // Fired to indicate the a binding error has occured
#define DISPID_PRIVACYIMPACTEDSTATECHANGE   272           // Fired when the user's browsing experience is impacted
#define DISPID_NEWWINDOW3                   273
#define DISPID_VIEWUPDATE                   281           // Fired when the contents of a shell browser window change
#define DISPID_SETPHISHINGFILTERSTATUS      282           // Fired by the Phishing Filter API to signal what state the analysis is in
#define DISPID_WINDOWSTATECHANGED           283           // Fired to indicate that the browser window's visibility or enabled state has changed

*/
};


}
