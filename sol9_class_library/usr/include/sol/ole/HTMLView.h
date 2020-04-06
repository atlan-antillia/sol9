/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  HTMLView.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed an IE browser control 
(an OLE object) into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/

// SOL9
// 2008/08/11: to-arai Added zoom, execWB methods
// 2011/02/23: Added translateAccelarator method.
// 2012/02/03: Modified create method,
// 2012/02/08: Added a member variable IWebBrowser2* webBrowser.
// 2012/02/09: Added a lot of methods for IWebBrowser, IWebBrowserApp and IWebBrowser2 interfaces.
// 2012/02/10: Added loadString and loadStream methods.

#pragma once

#include <sol\Object.h>

#include <exdisp.h>

#include <sol\StringConverter.h>
#include <sol\String.h>
#include <sol\ole\OleStorage.h>

#include <sol\ole\IHTMLView.h>
#include <sol\ole\OleSite.h>
#include <sol\ole\OleInPlaceFrame.h>

//2008/09/16 
#include <sol\ole\BrowserEvent.h>


namespace SOL {

/**
 * Implementation of IHTMLView
 */
class HTMLView : public IHTMLView {

public:
  COleSite    site;
  COleInPlaceFrame frame;
  COleStorage  storage;
  IOleObject* oleObject;

  //2008/09/16
  BrowserEvent browserEvent;

  //2012/02/08
  IWebBrowser2* webBrowser;

public:
  /**
   * Constructor
   */
  HTMLView()
    :oleObject(NULL),
    webBrowser(NULL)
  {
    site.host = this;
    frame.host = this;
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    //2012/02/03 Added WS_CLIPCHILDREN
    Boolean rc = Composite::create(parent, name, args.set(XmNstyle, WS_CLIPCHILDREN) );

    createWebControl();

    return rc;
  }

public:
  /**
   * Destructor
   */
  ~HTMLView()
  {
    destroyWebControl();
  }

  long size(Event& event) 
  {
    int w, h;
    event.getSize(w, h);
    int x, y;
    getLocation(x, y);

    layout(x, y, w, h);
    
    if (webBrowser) {
      webBrowser->put_Left(0);
      webBrowser->put_Top(0);
      webBrowser->put_Width(w);
      webBrowser->put_Height(h);
      return TRUE;
    }
    return 0L;
  }

public:
  //2012/02/09
  HRESULT loadString(const TCHAR* html, bool insertBOM=true)
  {
    HRESULT hr = E_FAIL;

    if (html) {
      size_t length = strlen(html) + 1; //The number of characters of html including a NULL-mark.
      size_t nBytes = length * sizeof(TCHAR);  
      size_t bomBytes = 2;

      HGLOBAL hHTML = GlobalAlloc(GMEM_MOVEABLE, nBytes + bomBytes);
      unsigned char* buffer = (unsigned char*)GlobalLock(hHTML);
      memset(buffer, 0, nBytes + bomBytes);

      if (insertBOM) {
        //&& !(*btext==0xff && *(btext+1)== 0xfe) ) {
        *buffer++ = 0xff;
        *buffer++ = 0xfe;
      }

      memcpy(buffer, html, nBytes);

      GlobalUnlock(hHTML);

      if (hHTML) {
        IStream* pStream = NULL;
        if (SUCCEEDED(hr  = CreateStreamOnHGlobal(hHTML, FALSE, &pStream)) ) {
          hr = loadStream(pStream);
          pStream->Release();
        }
        GlobalFree(hHTML);
      }
    }
    return hr;
  }

public:
  //2012/02/09
  HRESULT loadStream(IStream* pStream)
  {    
    HRESULT hr = E_FAIL;
    if (pStream) {
      IDispatch* pDocument = NULL;
      //IHTMLDocument3* pDocument = NULL;
      if ( SUCCEEDED(hr = webBrowser->get_Document((IDispatch**)&pDocument)) ) {
        IPersistStreamInit* pStreamInit = NULL;

        if ( SUCCEEDED(hr = pDocument->QueryInterface(IID_IPersistStreamInit,
                (void**)&pStreamInit)) ) {
          if ( SUCCEEDED(hr = pStreamInit->InitNew()) ) {
            hr = pStreamInit->Load(pStream);
          }
          pStreamInit->Release();
        }
        pDocument->Release();
      }
    }
    return hr;
  }


public:
  /**
   * level should be 0,1,2,3,4
   */
  void zoom(int level) {
    if (level >= 0 && level <= 4) {
      VARIANT size;
      VariantClear(&size);
      size.vt = VT_I4;  //long
      size.lVal = level;  //0.1.2.3.4
      execWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER, &size, NULL);
    } else {
      ;//Ignore
    }
  }

public:
  //
  HRESULT execWB(OLECMDID cmdID, OLECMDEXECOPT option, VARIANT* pvaIn, VARIANT* pvalOut) 
  {
    HRESULT hr = S_OK;
    if (oleObject ==NULL) {
      //Not ready(oleObject is not created, but return S_OK
      return hr;
    }

    if (webBrowser) {
      webBrowser->ExecWB(cmdID, option, pvaIn, pvalOut);
      webBrowser->Refresh();
    }
    return hr;
  }

public:
  //
  HRESULT getLocationURL(String& url) 
  { 
    HRESULT hr = S_OK;
    if (oleObject ==NULL) {
      return hr;
    }

    BSTR location = NULL;
    hr = webBrowser->get_LocationURL(&location);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    StringConverter converter;
    url = converter.toMultiByte(location);

    SysFreeString(location);
  
    return hr;
  }

private:
  void createWebControl(void)
  {
    HRESULT hr = OleCreate(CLSID_WebBrowser,
      IID_IOleObject,
      OLERENDER_DRAW, 0, &site, &storage, 
      (void**)&oleObject);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    
    HWND hwnd = getWindow();

    oleObject->SetHostNames(L"Web Host", L"Web View");

    OleSetContainedObject(oleObject,TRUE);

    RECT rect;
    GetClientRect(hwnd, &rect);

     hr = oleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, &site, -1, 
          hwnd, //::GetParent(hwnd),  //hwnd
          &rect);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    //2008/09/16
    HWND hParent = ::GetParent(hwnd);
    
    //2012/02/08
    webBrowser = NULL;
    hr = oleObject->QueryInterface(IID_IWebBrowser2, (void**)&webBrowser);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    //2012/02/10
    if (webBrowser == NULL) {
      //2015/07/15
      throw Exception(-1, "Failed to get IWebBrowser2 interface");
    }

    hr = browserEvent.Advise(hParent, webBrowser);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    navigate(_T("about:blank"));
  }

public:
  //2011/02/23
  HRESULT translateAccelator(MSG* msg) 
  {
    IOleInPlaceActiveObject* activeObject = NULL;
    HRESULT hr = oleObject -> QueryInterface(IID_IOleInPlaceActiveObject, (void**)&activeObject);
    if (SUCCEEDED(hr)) {
      hr = activeObject->TranslateAccelerator(msg);
    }
    return hr;
  }

public:
  void navigate(const TCHAR* url) 
  {
    if (webBrowser ==NULL) {
      return;
    }

    StringConverter converter;

    VARIANT vURL;
    VariantInit(&vURL);
    vURL.vt = VT_BSTR;
    vURL.bstrVal = converter.toBSTR(url);

    VARIANT ve1, ve2, ve3, ve4;
    ve1.vt = VT_EMPTY;
    ve2.vt = VT_EMPTY;
    ve3.vt = VT_EMPTY;
    ve4.vt = VT_EMPTY;

    webBrowser->Stop();  //2008/08/11

    HRESULT hr = webBrowser->Navigate2(&vURL, &ve1, &ve2, &ve3, &ve4);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    while(true) {
      VARIANT_BOOL busy;
      webBrowser->get_Busy(&busy);
      if (busy == VARIANT_FALSE) {
        break;
      }

      MSG msg;
      if (PeekMessage(&msg,0,0,0, TRUE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      Sleep(100);
    }
    VariantClear(&vURL);
  }

private:
  void destroyWebControl(void)
  {
    if (webBrowser) {
      webBrowser->Quit();  
      webBrowser->Release();
      webBrowser = NULL;
    }

    if (oleObject) {
      oleObject->Close(OLECLOSE_NOSAVE);
      oleObject->Release();
      oleObject = NULL;
    }
  }

public:
  virtual IOleInPlaceFrame* getInPlaceFrame() 
  { 
    return &frame;
  }

public:
  virtual IOleObject* getOleObject() 
  { 
    return oleObject; 
  };


  //<IWebBrowserInterface>
public:
  HRESULT goBack()
  {
    HRESULT hr = webBrowser->GoBack();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT goForward()
  {
    HRESULT hr = webBrowser->GoForward();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT goHome()
  {
    HRESULT hr = webBrowser->GoHome();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
    HRESULT goSearch()
  {
    HRESULT hr = webBrowser->GoSearch();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT navigate( 
            /* [in] */ _bstr_t url,
            /* [unique][optional][in] */ _variant_t *flags,
            /* [unique][optional][in] */ _variant_t *targetFrameName,
            /* [unique][optional][in] */ _variant_t *postData,
            /* [unique][optional][in] */ _variant_t *headers)
        
  {

    HRESULT hr = webBrowser->Navigate( 
        (BSTR)url,
        (VARIANT*)flags,
        (VARIANT*)targetFrameName,
        (VARIANT*)postData,
        (VARIANT*)headers);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;   
  }

  HRESULT refresh()
  {
    HRESULT hr = webBrowser->Refresh();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT refresh2( 
            /* [unique][optional][in] */ _variant_t *level)
  {
    HRESULT hr = webBrowser->Refresh2( 
                (VARIANT*)level);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT stop()
  {
    HRESULT hr = webBrowser->Stop();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  IDispatch* getApplication()
  {
    IDispatch *pDisp;
    HRESULT hr = webBrowser->get_Application(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  IDispatch* getParent()
  {
    IDispatch *pDisp;
    HRESULT hr = webBrowser->get_Parent(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }

  IDispatch* getContainer()
  {
    IDispatch *pDisp;
    HRESULT hr = webBrowser->get_Container(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;  
  }
        
  IDispatch* getDocument()
  {
    IDispatch *pDisp = NULL;
    HRESULT hr = webBrowser->get_Document(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return pDisp;
  }
        
  bool getTopLevelContainer()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_TopLevelContainer(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(value);
  }
        
  _bstr_t getType()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_Type(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return _bstr_t(value, false);
  }

        
  long getLeft()
  {
    long l;
    HRESULT hr = webBrowser->get_Left(&l);
    return l;
  }

  HRESULT putLeft( 
            /* [in] */ long left)
  {
    HRESULT hr = webBrowser->put_Left(left);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  long getTop()
  {
    long l;
    HRESULT hr = webBrowser->get_Top(&l);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return l;
  }

  HRESULT putTop( 
            /* [in] */ long top)
  {
    HRESULT hr = webBrowser->put_Top(top);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
                
  long getWidth()
  {
    long l;
    HRESULT hr = webBrowser->get_Width(&l);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return l;
  }

  HRESULT putWidth( 
            /* [in] */ long width)
  {
    HRESULT hr = webBrowser->put_Width(width);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
                
  long getHeight()
  {
    long l;
    HRESULT hr = webBrowser->get_Height(&l);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return l;
  }

  HRESULT putHeight( 
            /* [in] */ long height)
  {
    HRESULT hr = webBrowser->put_Height(height);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
                
  _bstr_t getLocationName()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_LocationName(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(value, false);
  }
        
  _bstr_t getLocationURL()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_LocationURL(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return _bstr_t(value, false);
  }

  bool getBusy()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_Busy(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return toBool(value);
  }        
  //</IWebBrowserInterface>


  //<IWebBrowserAppInterface>
public:
  HRESULT quit()
  {
    HRESULT hr = webBrowser->Quit();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT clientToWindow( 
            /* [out][in] */ int *pcx,
            /* [out][in] */ int *pcy) 
  {
    HRESULT hr = webBrowser->ClientToWindow(pcx, pcy);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return hr;
  }

  HRESULT putProperty( 
            /* [in] */ _bstr_t property,
            /* [in] */ _variant_t vtValue)
  {
    HRESULT hr = webBrowser->PutProperty((BSTR)property, (VARIANT)vtValue);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return hr;
  }
        
  _variant_t getProperty( 
            /* [in] */ _bstr_t property)
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = webBrowser->GetProperty((BSTR)property, &var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return _variant_t(var, false);
  }
        
  _bstr_t getName()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_Name(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return _bstr_t(value, false);
  }
                
  SHANDLE_PTR getHWND()
  {
    SHANDLE_PTR hwnd = NULL;
    HRESULT hr = webBrowser->get_HWND(&hwnd);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hwnd;
  }
  //2012/02/20
  _bstr_t getFullName()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_FullName(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(value, false);
  }
        
  _bstr_t getPath()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_Path(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(value, false);
  }
            
  bool getVisible()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_Visible(&value);
    return toBool(value);
  }

  HRESULT putVisible( 
            /* [in] */ bool value)
  {
    HRESULT hr = webBrowser->put_Visible(toVariantBool(value));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  bool getStatusBar()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_StatusBar(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(value);
  }

  HRESULT putStatusBar( 
            /* [in] */ bool value)
  {
    HRESULT hr = webBrowser->put_StatusBar( toVariantBool(value) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
        
  _bstr_t getStatusText()
  {
    BSTR value = NULL;
    HRESULT hr = webBrowser->get_StatusText(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(value, false);

  }

  HRESULT putStatusText( 
            /* [in] */ _bstr_t statusText)
  {
    HRESULT hr = webBrowser->put_StatusText((BSTR)statusText);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  int getToolBar()
  {
    int value;
    HRESULT hr = webBrowser->get_ToolBar(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }

  HRESULT putToolBar( 
            /* [in] */ int value)
  {
    HRESULT hr = webBrowser->put_ToolBar(value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
              
  bool getMenuBar()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_MenuBar(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(value);
  }

  HRESULT putMenuBar( 
            /* [in] */ bool value)
  {
    HRESULT hr = webBrowser->put_MenuBar(toVariantBool(value) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
                
  bool getFullScreen()
  {
    VARIANT_BOOL bFullScreen;
    HRESULT hr = webBrowser->get_FullScreen(&bFullScreen);
    return toBool(bFullScreen);
  }

  HRESULT putFullScreen( 
            /* [in] */ bool bFullScreen)
  {
    HRESULT hr = webBrowser->put_FullScreen( toVariantBool(bFullScreen) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
  //</IWebBrowserAppInterface>


  //<IWebBrowser2>
public:
  HRESULT navigate2( 
            /* [in] */ _variant_t *url,
            /* [unique][optional][in] */ _variant_t *flags,
            /* [unique][optional][in] */ _variant_t *targetFrameName,
            /* [unique][optional][in] */ _variant_t *postData,
            /* [unique][optional][in] */ _variant_t *headers)
  {
    HRESULT hr = webBrowser->Navigate2( 
               (VARIANT*)url,
        (VARIANT*)flags,
        (VARIANT*)targetFrameName,
        (VARIANT*)postData,
        (VARIANT*)headers);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT queryStatusWB( 
            /* [in] */ OLECMDID cmdID,
            /* [retval][out] */ OLECMDF *pcmdf)
  {
    HRESULT hr = webBrowser->QueryStatusWB( 
      cmdID,
      pcmdf);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;

  }
/*        
  HRESULT execWB( 
            __in OLECMDID cmdID,
            __in OLECMDEXECOPT cmdexecopt,
            __in VARIANT *pvaIn,
            __in__out __RPC__inout_opt VARIANT *pvaOut)
  {
    HRESULT hr = webBrowser->ExecWB( 
      cmdID,
      cmdexecopt,
      pvaIn,
      pvaOut);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
 */       
  HRESULT showBrowserBar( 
            /* [in] */ _variant_t *pvaClsid,
            /* [unique][optional][in] */ _variant_t *pvarShow,
            /* [unique][optional][in] */ _variant_t *pvarSize)
  {
    HRESULT hr = webBrowser->ShowBrowserBar( 
              (VARIANT*)pvaClsid,
          (VARIANT*)pvarShow,
          (VARIANT*)pvarSize);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
                
  READYSTATE getReadyState()
  {
    READYSTATE readyState;
    HRESULT hr = webBrowser->get_ReadyState(&readyState);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return readyState;
  }

  bool getOffline()
  {
    VARIANT_BOOL bOffline;
    HRESULT hr = webBrowser->get_Offline(&bOffline);
    
    return toBool(bOffline);
  }

  HRESULT putOffline( 
            /* [in] */ bool bOffline)
  {
    HRESULT hr = webBrowser->put_Offline( toVariantBool(bOffline) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
                
  bool getSilent()
  {
    VARIANT_BOOL bSilent;
    HRESULT hr = webBrowser->get_Silent(&bSilent);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(bSilent);
  }

  HRESULT putSilent( 
            /* [in] */ bool bSilent)
  {
    HRESULT hr = webBrowser->put_Silent( toVariantBool(bSilent) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  bool getRegisterAsBrowser()
  {
    VARIANT_BOOL bRegister;
    HRESULT hr = webBrowser->get_RegisterAsBrowser(&bRegister);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(bRegister);
  }

  HRESULT putRegisterAsBrowser( 
            /* [in] */ bool bRegister)
  {
    HRESULT hr = webBrowser->put_RegisterAsBrowser(toVariantBool(bRegister) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }       

  bool getRegisterAsDropTarget()
  {
    VARIANT_BOOL bRegister;
    HRESULT hr = webBrowser->get_RegisterAsDropTarget(&bRegister);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(bRegister);
  }

  HRESULT putRegisterAsDropTarget( 
            /* [in] */ bool bRegister)
  {
    HRESULT hr = webBrowser->put_RegisterAsDropTarget(toVariantBool(bRegister) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    return hr;
  }
  
  bool getTheaterMode()
  {
    VARIANT_BOOL bRegister;
    HRESULT hr = webBrowser->get_TheaterMode(&bRegister);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(bRegister);
  }

  HRESULT putTheaterMode( 
            /* [in] */ bool bRegister)
  {
    HRESULT hr = webBrowser->put_TheaterMode(toVariantBool(bRegister) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
      
  bool getAddressBar()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_AddressBar(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(value);
  }

  HRESULT putAddressBar( 
            /* [in] */ bool value)
  {
    HRESULT hr = webBrowser->put_AddressBar(toVariantBool(value));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
     

  bool getResizable()
  {
    VARIANT_BOOL value;
    HRESULT hr = webBrowser->get_Resizable(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(value);
  }
        

  HRESULT putResizable( 
            /* [in] */ bool value)
  {
    HRESULT hr = webBrowser->put_Resizable(toVariantBool(value) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }

  //</IWebBrowser2>

public:
  bool toBool(VARIANT_BOOL value)
  {
    bool rc = false;
    if (value == VARIANT_TRUE) {
      rc = true;
    }
    return rc;
  }

public:
  VARIANT_BOOL toVariantBool(bool value)
  {
    VARIANT_BOOL rc = VARIANT_FALSE;
    if (value == true) {
      rc = VARIANT_TRUE;
    }
    return rc;
  }

};

}

