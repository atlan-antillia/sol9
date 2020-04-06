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
 *  HTMLParser.h
 *
 *****************************************************************************/

//2008/09/30 Simple HTMLParser based on IHTMLDocument2 interface.
//2012/02/16 Updated loadString method.
//2012/02/17 Modified to include <sol/Object.h> and not to import <mshtml.tlb>

// See the the following code.
// http://209.85.175.104/search?
// q=cache:zDWb5JtAMfIJ:www.ddj.com/architect/184411019+HTMLParser+IOleClientSite&hl=ja&ct=clnk&cd=3&gl=jp

//See also the following url.
//1: http://www.codeproject.com/KB/IP/parse_html.aspx?
//fid=3219&df=90&mpp=25&noise=3&sort=Position&view=Quick&fr=76&select=249106


#pragma once
#include <sol/Object.h>
#include <sol/Exception.h> //2015/07/15

#include <mshtmdid.h>
#include <docobj.h> 

#include <sol/Wchardef.h>

//namespace = MSHTML
//2012/02/17 #import "mshtml.tlb"  named_guids

#define WM_HTML_COMPLETE   WM_USER+2009

//
namespace SOL
{

/**
 * class HTMLParser without GUI of IE.
 */
class HTMLParser: public IPropertyNotifySink, 
        IOleClientSite, IDispatch {

private:
  // Member variables
  DWORD   dwRef;
  DWORD    dwCookie;
  IHTMLDocument2* pHTMLDocument;
  IConnectionPoint* pCP;

public:
  /**
   * Construtor
   */
  HTMLParser()
    :dwRef(1), 
      dwCookie(0),
      pHTMLDocument(NULL),
      pCP(NULL)
  {
    HRESULT hr = S_OK;
   
    try {
      //Create an instance of IHTMLDocument2, because we don't need IE UI.
      if (FAILED(hr = CoCreateInstance( CLSID_HTMLDocument, NULL, 
          CLSCTX_INPROC_SERVER, IID_IHTMLDocument2, (LPVOID*)&pHTMLDocument ))) {

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);//Failed to create MSHTMLDocument;    
      }

      LPOLEOBJECT pOleObject = NULL;

      if (FAILED(hr = pHTMLDocument->QueryInterface(IID_IOleObject, 
                                                   (LPVOID*)&pOleObject))) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);//Failed to query OleObject;    
      }
  
      hr = pOleObject->SetClientSite((IOleClientSite*)this);
      pOleObject->Release();

      //OleControl
      LPOLECONTROL pOleControl = NULL;

      if (FAILED(hr = pHTMLDocument->QueryInterface(IID_IOleControl, 
                                                   (LPVOID*)&pOleControl))) {

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);//Failed to query ConnectionPoint;    
      }
  
      hr = pOleControl->OnAmbientPropertyChange(DISPID_AMBIENT_DLCONTROL);
      pOleControl->Release();
    
      IConnectionPointContainer* tmppCPC = NULL;

      if (FAILED(hr = pHTMLDocument->QueryInterface(IID_IConnectionPointContainer,
        (LPVOID*)&tmppCPC))) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);//Failed to query ConnectionPoint;    
      }

      if (FAILED(hr = tmppCPC->FindConnectionPoint(IID_IPropertyNotifySink, 
                        &pCP))){
        tmppCPC->Release();
        throw hr  ;//Failed to find ConnectionPoint;    
      }
      tmppCPC->Release();

      if (FAILED(hr = pCP->Advise((LPUNKNOWN)(IPropertyNotifySink*)this, 
          &dwCookie))) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);  //Failed to Advice;    
      }
    } catch (HRESULT hr) {
      clear();
      throw Exception(E_FAIL, "%s: %s HRESULT(%ld)", "E_FAIL",__FUNCTION__, hr);
    }
  }

public:
  /**
   * Destructor
   */
  ~HTMLParser() 
  {
    clear();
  }

private:
  void clear() 
  {
    if (pCP) {
      pCP->Unadvise(dwCookie);
      pCP->Release();
    }
    if (pHTMLDocument) {
      pHTMLDocument->Release();
    }

    pCP = NULL;
    pHTMLDocument = NULL;
  }

public:

  STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv) 
  {
    *ppv = NULL;

    if (IID_IUnknown == riid || IID_IPropertyNotifySink == riid) {
      *ppv = (LPUNKNOWN)(IPropertyNotifySink*)this;
      AddRef();
      return NOERROR;
    } else if (IID_IOleClientSite == riid) {
      *ppv = (IOleClientSite*)this;
      AddRef();
      return NOERROR;
    } else if (IID_IDispatch == riid) {
      *ppv = (IDispatch*)this;
      AddRef();
      return NOERROR;
    } else {
      return E_NOTIMPL;
    }
  }


public:
  STDMETHOD_(ULONG, AddRef)() 
  {
    return ++dwRef;
  }

public:
  STDMETHOD_(ULONG, Release)() 
  {
    if (--dwRef == 0) { 
      delete this; 
      return 0; 
    }
    return dwRef;
  }

public:
  STDMETHODIMP OnChanged(DISPID dispID) 
  {
    HRESULT hr;
  
    if (DISPID_READYSTATE == dispID){
      VARIANT vResult = {0};
      EXCEPINFO excepInfo;
      UINT uArgErr;
      long lReadyState;
      DISPPARAMS dp = {NULL, NULL, 0, 0};
      
      if (SUCCEEDED(hr = pHTMLDocument->Invoke(DISPID_READYSTATE, IID_NULL, 
                          LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, 
                          &dp, &vResult, &excepInfo, &uArgErr))) {
        lReadyState = (READYSTATE)V_I4(&vResult);

        switch (lReadyState) {   
        case READYSTATE_UNINITIALIZED:
        case READYSTATE_LOADING: 
        case READYSTATE_LOADED: 
        case READYSTATE_INTERACTIVE:
          break;
        case READYSTATE_COMPLETE: 
          printf("ReadState_Complete\n");
          // IE has just finished parsing the HTML file(READYSTATE_COMPLETE).
          // Post a WM_HTML_COMPLETE message to this current thread.
          
          PostThreadMessage(GetCurrentThreadId(),
                                WM_HTML_COMPLETE, (WPARAM)0, (LPARAM)0);
          break;
        }
        VariantClear(&vResult);
      }
    }
    return NOERROR;
  }


public:
  /** 
   * If DISPID== DISPID_AMBIENT_DLCONTROL, set the following flags to return value, 
   * because this is a UI-less HTML Parser.
   *
   *  DLCTL_DOWNLOADONLY | 
   *  DLCTL_NO_SCRIPTS |    
   *  DLCTL_NO_JAVA |      
   *  DLCTL_NO_DLACTIVEXCTLS |  
   *  DLCTL_NO_RUNACTIVEXCTLS;
   */
  STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
            WORD wFlags, DISPPARAMS __RPC_FAR *pDispParams,
            VARIANT __RPC_FAR *pVarResult, EXCEPINFO __RPC_FAR *pExcepInfo,
            UINT __RPC_FAR *puArgErr) 
  {
    if (!pVarResult){
      return E_POINTER;
    }
    
    switch(dispIdMember) {

    case DISPID_AMBIENT_DLCONTROL:
      printf("HTMLParser::Invoke,DISPID_AMBIENT_DLCONTROL\n");
      V_VT(pVarResult) = VT_I4;
      
      V_I4(pVarResult) =  DLCTL_DOWNLOADONLY | 
                            DLCTL_NO_SCRIPTS | 
                            DLCTL_NO_JAVA |
                            DLCTL_NO_DLACTIVEXCTLS |
                            DLCTL_NO_RUNACTIVEXCTLS;            
      break;

    default:
      return DISP_E_MEMBERNOTFOUND;
    }
    return NOERROR;
  }


protected:
  STDMETHODIMP OnRequestEdit(DISPID dispID) { 
    return NOERROR; 
  }
        
  // IOleClientSite methods
  STDMETHODIMP SaveObject(void) { 
    return E_NOTIMPL; 
  }

  STDMETHODIMP GetMoniker(DWORD dwAssign,
    DWORD dwWhichMoniker, IMoniker** ppmk){
    return E_NOTIMPL; 
  }

  STDMETHODIMP GetContainer(IOleContainer** ppContainer){
    return E_NOTIMPL; 
  }
        
  STDMETHODIMP ShowObject(void){ 
    return E_NOTIMPL; 
  }
     
  STDMETHODIMP OnShowWindow(BOOL fShow){ 
    return E_NOTIMPL; 
  }
    
    STDMETHODIMP RequestNewObjectLayout(void){ 
    return E_NOTIMPL; 
  }
  
  
  // IDispatch method
  STDMETHODIMP GetTypeInfoCount(UINT* pctinfo){ 
    return E_NOTIMPL; 
  }
     
  STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo){ 
    return E_NOTIMPL; 
  }
    
  STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
                                UINT cNames, LCID lcid, DISPID* rgDispId){ 
    return E_NOTIMPL; 
  }

public:
  /**
   * Load HTML from an interface of IStream.
   */
  HRESULT loadFromStream(IStream* pStream)
  {
    HRESULT hr = E_FAIL;
    IPersistStreamInit* pPersistStreamInit = NULL;

    if (pHTMLDocument != NULL) {

      if (SUCCEEDED(pHTMLDocument->QueryInterface(IID_IPersistStreamInit, 
        (void**)&pPersistStreamInit))) {
      
        if (SUCCEEDED(pPersistStreamInit->InitNew())) {
      
          if (SUCCEEDED(hr = pPersistStreamInit->Load(pStream))) {
            wait();
          }
        }
        pPersistStreamInit->Release();
      }
    }
    return hr;
  }

public:
  /**
   * LoadFrom a string.
   */
  HRESULT loadFromString(const TCHAR* html)
  {  
    HRESULT hr = E_FAIL;
    if (html == NULL) {
      return hr;
    }
    //<Modified at="2012/02/16">
    int cchLength = strlen(html)+1;
    int nBytes = cchLength* sizeof(TCHAR);

    HGLOBAL hHTML = GlobalAlloc(GPTR, nBytes);

    if (hHTML){
      void* buff = GlobalLock(hHTML);
      memcpy(buff, html, nBytes);

      GlobalUnlock(hHTML);

      IStream* pStream = NULL;
      if (SUCCEEDED(hr = CreateStreamOnHGlobal(hHTML, FALSE, &pStream))) {
        //</Modified>
        ULARGE_INTEGER size;
        size.QuadPart = nBytes;
        pStream->SetSize(size);
        hr = loadFromStream(pStream);
        pStream->Release();
      }
      GlobalFree(hHTML);
    }
    return hr;
  }

public:
  /**
   * Load an HTML file something like iC:\root\htmo\sample.htmlj
   * 
   */
  HRESULT loadFromFile(const TCHAR* filePath) 
  { 
    HRESULT  hr =E_FAIL;
    if (filePath == NULL) {
      return hr;
    }

    if (GetFileAttributes(filePath) == 0xffffffff ){
      printf("File is access error\n");
      return hr;
    }
    
    _bstr_t bstrFile(filePath);
    
    IPersistFile* pPF = NULL;
    //Get an interface for IID_IPersistFile.
    if (SUCCEEDED(hr = pHTMLDocument->QueryInterface(IID_IPersistFile, 
          (LPVOID*) &pPF))) {

      //Load the content by using a IPersitentFile interface.
      if (SUCCEEDED(hr = pPF->Load((LPCWSTR)bstrFile, STGM_READ | STGM_SHARE_DENY_NONE))) {
        wait();
      } 
      pPF->Release();
    }
    return hr;
  }

public:
  /**
   */
  void wait() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
      // Notification from OnChanged
      if (WM_HTML_COMPLETE == msg.message && NULL == msg.hwnd) {
        printf("HTMLParser#wait,1,OK,loading completed\n");
        break;
      } else {
        DispatchMessage(&msg);
      }
    }
  }



public:
  IHTMLDocument2* getHTMLDocument() 
  {
    if (pHTMLDocument) {
      pHTMLDocument->AddRef();
    }
    return this->pHTMLDocument;
  }

}; 

}

