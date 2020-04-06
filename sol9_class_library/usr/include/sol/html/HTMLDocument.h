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
 *  HTMLDocument.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/Object.h>

#include <sol/html/HTMLObject.h>
#include <urlmon.h>

#pragma comment (lib, "urlmon.lib")


namespace SOL {

class HTMLDocument : public HTMLObject {

private:
  IHTMLDocument*  pDocument;
  IHTMLDocument2* pDocument2;
  IHTMLDocument3* pDocument3;
  IHTMLDocument4* pDocument4;
  IHTMLDocument5* pDocument5;
  IHTMLDocument6* pDocument6;
    
public:
  HTMLDocument(IDispatch* pDisp=NULL)
  :HTMLObject(pDisp),
  pDocument (NULL), pDocument2(NULL), pDocument3(NULL),
  pDocument4(NULL), pDocument5(NULL), pDocument6(NULL)
  {
              
  }

public:
  HTMLDocument(__in REFIID riid)
  :HTMLObject(NULL),
  pDocument (NULL), pDocument2(NULL), pDocument3(NULL),
  pDocument4(NULL), pDocument5(NULL), pDocument6(NULL)
  {
    if (riid == IID_IHTMLDocument  || riid == IID_IHTMLDocument2 || riid == IID_IHTMLDocument3 ||
      riid == IID_IHTMLDocument4 || riid == IID_IHTMLDocument5 || riid == IID_IHTMLDocument6) {
        //
        createDocument(riid);
    } else {
      throw Exception("HTMLDocument::HTMLDocument invalid riid\n");
    }
  }

public:
  HRESULT createDocument(__in REFIID riid = IID_IHTMLDocument2)
  {
    return createInstance(CLSID_HTMLDocument, riid);
  }

public:
  HRESULT createDocument3()
  {
    return createInstance(CLSID_HTMLDocument, IID_IHTMLDocument3);
  }
 
public:
  HRESULT createDocument4()
  {
    HRESULT hr = createInstance(CLSID_HTMLDocument, IID_IHTMLDocument4);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

public:
  HRESULT createDocument5()
  {
    return createInstance(CLSID_HTMLDocument, IID_IHTMLDocument5);
  }

public:
  HRESULT createDocument6()
  {
    return createInstance(CLSID_HTMLDocument, IID_IHTMLDocument6);
  }

public:
  ~HTMLDocument()
  {
    if (pDocument) {
      pDocument -> Release();
      pDocument  = NULL;
    }

    if (pDocument2) {
      pDocument2 -> Release();
      pDocument2  = NULL;
    }
    if (pDocument3) {
      pDocument3 -> Release();
      pDocument3  = NULL;
    }
    if (pDocument4) {
      pDocument4 -> Release();
      pDocument4  = NULL;
    }
    if (pDocument5) {
      pDocument5 -> Release();
      pDocument5  = NULL;
    }
    if (pDocument6) {
      pDocument6 -> Release();
      pDocument6  = NULL;
    }              
  }


public:
  /**
   * Load an HTML file something like iC:\root\htmo\sample.htmlj
   * 
   */
  HRESULT loadFromFile(const TCHAR* filePath) {
   
    HRESULT  hr =E_FAIL;
    if (filePath == NULL) {
      return hr;
    }
    if (GetFileAttributes(filePath) == 0xffffffff ){
      throw Exception(0, _T("File not found: %s;\n"), filePath);
    }
    _bstr_t bstrFile(filePath);
    
    IPersistFile*  pPF=NULL;
    //Get an interface for IID_IPersistFile.
    if (SUCCEEDED(hr = getDocument2() ->QueryInterface(IID_IPersistFile, 
          (LPVOID*) &pPF))) {

      //Load the content by using a IPersitentFile interface.
      if (SUCCEEDED(hr = pPF->Load((LPCWSTR)bstrFile, STGM_READ | STGM_SHARE_DENY_NONE))) {
        //Wait to complete to load the file of bstrFile
        waitForComplete();
      } 
      pPF->Release();

      if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);  

    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return hr;
  }

public:
  void waitForComplete() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE) ) {

      _bstr_t state = getReadyState();
      //_tprintf(_T("%s\n"), (const TCHAR*)state);
      if (state == _bstr_t("complete")) {
        break;
      }
      DispatchMessage(&msg);
      Sleep(200);
    }
  }

private:
  IHTMLDocument* getDocument()
  {
    HRESULT hr = S_OK;
    if (pDocument == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument,
                (void**)&pDocument)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    return pDocument;
  }

public:
  IDispatch* getScript()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getDocument() -> get_Script(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }  
    

    
private:
  IHTMLDocument2* getDocument2()
  {
    HRESULT hr = S_OK;
    if (pDocument2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument2,
                (void**)&pDocument2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pDocument2 == NULL) {
      throw NullPointerException("IHTMLDocument2 is NULL");
    }
    return pDocument2;
  }

public:

  IHTMLElementCollection* getAll()
  {
    IHTMLElementCollection *pCollection = NULL;
    HRESULT hr = getDocument2() -> get_all(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }        

  IHTMLElement* getBody()
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getDocument2() -> get_body(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pElement;
  }
        
  IHTMLElement* getActiveElement()
  {
    IHTMLElement *pElement = NULL;
    HRESULT hr = getDocument2() -> get_activeElement(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pElement;
  }
        
  IHTMLElementCollection* getImages()
  {
    IHTMLElementCollection *pCollection = NULL;
    HRESULT hr = getDocument2() -> get_images(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }

  IHTMLElementCollection* getApplets()
  {
    IHTMLElementCollection *pCollection = NULL;
    HRESULT hr = getDocument2() -> get_applets(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  IHTMLElementCollection* getLinks()
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_links(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  IHTMLElementCollection* getForms()
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_forms(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  IHTMLElementCollection* getAnchors()
  {
    IHTMLElementCollection *pCollection = NULL;

    HRESULT hr = getDocument2() -> get_anchors(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  HRESULT putTitle( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_title((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getTitle()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_title(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  IHTMLElementCollection* getScripts()
  {
    IHTMLElementCollection* pCollection;
    HRESULT hr = getDocument2() -> get_scripts(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  HRESULT putDesignMode( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_designMode((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getDesignMode()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_designMode(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  IHTMLSelectionObject* getSelection()
  {
    IHTMLSelectionObject *pObject = NULL;
    HRESULT hr = getDocument2() -> get_selection(&pObject);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pObject;
  }
    

  /*
  The getReadyState returns one of the following strings.
  complete   : The object is completely loaded.  
  interactive: The object can be interacted with even though it is not fully loaded.  
  loading    : The object is currently being loaded.  
  unitialized: The object is not created. Usually when the object is being downloaded.  
   */
  _bstr_t getReadyState()        
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_readyState(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return _bstr_t(bstr, false);
  }

  IHTMLFramesCollection2* getFrames()
  {
    IHTMLFramesCollection2* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_frames(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  IHTMLElementCollection* getEmbeds()
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_embeds(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  IHTMLElementCollection* getPlugins()
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_plugins(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  HRESULT putAlinkColor( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_alinkColor(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getAlinkColor()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_alinkColor(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putBgColor( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_bgColor(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getBgColor()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_bgColor(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putFgColor( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_fgColor(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getFgColor()
  {
    VARIANT var;
    VariantInit(&var);
    
    HRESULT hr = getDocument2() -> get_fgColor(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);;
  }
        
  HRESULT putLinkColor( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_linkColor(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getLinkColor()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_linkColor(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putVlinkColor( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_vlinkColor(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getVlinkColor()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_vlinkColor(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  _bstr_t getReferrer()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_referrer(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  IHTMLLocation* getLocation()
  {
    IHTMLLocation* pLocation = NULL;
    HRESULT hr = getDocument2() -> get_location(&pLocation);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pLocation;
  }

        
  _bstr_t getLastModified()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_lastModified(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
  
    return _bstr_t(bstr, false);
  }
        
  HRESULT putURL( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_URL((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getURL()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_URL(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  HRESULT putDomain( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_domain((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getDomain()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_domain(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  HRESULT putCookie( 
            /* [out][retval] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_cookie((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

  _bstr_t getCookie()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_cookie(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }

  HRESULT putExpando( 
            /* [in] */ bool v)
  {
    HRESULT hr = getDocument2() -> put_expando(toVariantBool(v));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  bool getExpando()
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> get_expando(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  HRESULT putCharset( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_charset((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getCharset()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_charset(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putDefaultCharset( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument2() -> put_defaultCharset((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _bstr_t getDefaultCharset()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_defaultCharset(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getMimeType()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_mimeType(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }

  _bstr_t getFileSize()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_fileSize(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getFileCreatedDate()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_fileCreatedDate(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  _bstr_t getFileModifiedDate()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_fileModifiedDate(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getFileUpdatedDate()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_fileUpdatedDate(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getSecurity()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_security(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getProtocol()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_protocol(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _bstr_t getNameProp()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> get_nameProp(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  HRESULT write(_bstr_t html)
  {
    HRESULT hr = E_FAIL;
    // Creates a one-dimensional array
    SAFEARRAY *sarray = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    if (sarray ) {
      VARIANT *param = NULL;
      HRESULT hr = SafeArrayAccessData(sarray, (void**)&param);
      param->vt = VT_BSTR;
      param->bstrVal = (BSTR)html;

      hr = SafeArrayUnaccessData(sarray);
      try {
        hr = write(sarray);
      } catch (...) {
    
      }
      SafeArrayDestroy(sarray);
    }  
    return hr;
  }

  HRESULT write( 
            /* [in] */ SAFEARRAY * psarray)
  {
    HRESULT hr = getDocument2() -> write(psarray);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  HRESULT writeln( 
            /* [in] */ SAFEARRAY * psarray)
  {
    HRESULT hr = getDocument2() -> writeln(psarray);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  IDispatch* open( 
            /* [in][defaultvalue] */ _bstr_t url,
            /* [in][optional] */ _variant_t name,
            /* [in][optional] */ _variant_t features,
            /* [in][optional] */ _variant_t replace)
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getDocument2() -> open( 
        url,
        name,
        features,
        replace,
        &pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pDisp;
  }
        
  HRESULT close()
  {
    HRESULT hr = getDocument2() -> close();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  HRESULT clear()
  {
    HRESULT hr = getDocument2() -> clear();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  bool queryCommandSupported( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> queryCommandSupported( 
          cmdID,
          &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  bool queryCommandEnabled( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> queryCommandEnabled( 
        cmdID,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  bool queryCommandState( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> queryCommandState( 
        cmdID,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  bool queryCommandIndeterm( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> queryCommandIndeterm( 
        cmdID,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  _bstr_t queryCommandText( 
            /* [in] */ _bstr_t cmdID)
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> queryCommandText( 
        cmdID,
        &bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _bstr_t(bstr, false);
  }
        
  _variant_t queryCommandValue( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> queryCommandValue( 
        cmdID,
        &var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  bool execCommand( 
            /* [in] */ _bstr_t cmdID,
            /* [in][defaultvalue] */bool showUI,
            /* [in][optional] */ _variant_t value)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> execCommand( 
        (BSTR)cmdID,
        toVariantBool(showUI),
        (VARIANT)value,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  bool execCommandShowHelp( 
            /* [in] */ _bstr_t cmdID)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument2() -> execCommandShowHelp( 
        (BSTR)cmdID,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return toBool(vbool);
  }
        
  IHTMLElement* createElement( 
            /* [in] */ _bstr_t eTag)
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getDocument2() -> createElement( 
        (BSTR)eTag,
        &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pElement;
  }
        
  HRESULT putOnHelp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onhelp(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnHelp()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onhelp(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnClick( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onclick(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnclick()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onclick(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOndblclick( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_ondblclick(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOndblclick()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_ondblclick(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnKeyUp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onkeyup(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnKeyUp()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onkeyup(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnKeyDown( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onkeydown(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnKeyDown()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onkeydown(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnKeyPress( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onkeypress(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnKeyPress()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onkeypress(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnMouseUp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onmouseup(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnMouseUp()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onmouseup(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnMouseDown( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onmousedown(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnMouseDown()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onmousedown(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnMouseMove( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onmousemove(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnMouseMove()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onmousemove(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnMouseOut( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onmouseout(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnMouseOut()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onmouseout(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnMouseOver( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onmouseover(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnMouseOver()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onmouseover(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnReadyStateChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onreadystatechange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnReadyStateChange()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onreadystatechange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnFfterUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onafterupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnAfterUpdate()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onafterupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnRowExit( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onrowexit(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnRowExit()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onrowexit(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnRowEnter( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onrowenter(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnRowEnter()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_onrowenter(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnDragStart( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_ondragstart(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnDragStart()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_ondragstart(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnSelectStart( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onselectstart(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnSelectStart()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument2() -> get_onselectstart(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  IHTMLElement* elementFromPoint( 
            /* [in] */ long x,
            /* [in] */ long y)
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getDocument2() -> elementFromPoint( 
          x,
          y,
          &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pElement;
  }
        
  IHTMLWindow2* getParentWindow()
  {
    IHTMLWindow2* pWindow = NULL;
    HRESULT hr = getDocument2() -> get_parentWindow(&pWindow);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pWindow;
  }
        
  IHTMLStyleSheetsCollection*  getStyleSheets()
  {
    IHTMLStyleSheetsCollection* pCollection = NULL;
    HRESULT hr = getDocument2() -> get_styleSheets(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pCollection;
  }
        
  HRESULT putOnBeforeUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onbeforeupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnBeforeUpdate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_onbeforeupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  HRESULT putOnErrorUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument2() -> put_onerrorupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return hr;
  }
        
  _variant_t getOnErrorUpdate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument2() -> get_onerrorupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return _variant_t(var, false);
  }
        
  _bstr_t toString()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument2() -> toString(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  IHTMLStyleSheet* createStyleSheet( 
            /* [in][defaultvalue] */ _bstr_t bstrHref,
            /* [in][defaultvalue] */ long lIndex)
  {
    IHTMLStyleSheet* pSheet = NULL;
    HRESULT hr = getDocument2() -> createStyleSheet( 
        (BSTR)bstrHref,
        lIndex,
        &pSheet);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    
    return pSheet;
  }
        

//    IHTMLDocument3 : public IDispatch
public:
  IHTMLDocument3* getDocument3()
  {
    HRESULT hr = S_OK;
    if (pDocument3 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument3,
                (void**)&pDocument3)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pDocument3 == NULL) {
      throw NullPointerException("IHTMLDocument3 is NULL");
    }
    return pDocument3;
  }

public:
  HRESULT releaseCapture()
  {
    HRESULT hr = getDocument3() -> releaseCapture();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

  HRESULT recalc( 
            /* [in][defaultvalue] */ VARIANT_BOOL fForce = 0)
  {
    HRESULT hr = getDocument3() -> recalc(fForce);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  IHTMLDOMNode* createTextNode( 
            /* [in] */ _bstr_t text)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getDocument3() -> createTextNode( 
        (BSTR)text,
        &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLElement* getDocumentElement()
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getDocument3() -> get_documentElement(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }
        

  _bstr_t getUniqueID()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument3() -> get_uniqueID(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  bool attachEvent( 
            /* [in] */ _bstr_t event,
            /* [in] */ IDispatch *pDisp)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument3() -> attachEvent( 
        event,
        pDisp,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT detachEvent( 
            /* [in] */ _bstr_t event,
            /* [in] */ IDispatch *pDisp)
  {
    HRESULT hr = getDocument3() -> detachEvent( 
            event,
            pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT putOnRowsDelete( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_onrowsdelete(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        

  _variant_t getOnRowsDelete()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument3() -> get_onrowsdelete(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnRowsInserted( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_onrowsinserted(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnRowsInserted()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_onrowsinserted(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnCellChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_oncellchange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnCellChange()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_oncellchange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDatasetChanged( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() ->  put_ondatasetchanged(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDatasetChanged()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_ondatasetchanged(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDataAvailable( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() ->  put_ondataavailable(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDataAvailable()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() ->  get_ondataavailable(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDatasetComplete( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() ->  put_ondatasetcomplete(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDatasetComplete()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_ondatasetcomplete(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnproPertyChange( 
            /* [in] */ _variant_t v)
   {
    HRESULT hr = getDocument3() -> put_onpropertychange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
       
  _variant_t getOnPropertyChange()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_onpropertychange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putDir( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getDocument3() -> put_dir((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getDir()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument3() -> get_dir(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putOnContextMenu( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_oncontextmenu(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnContextMenu()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_oncontextmenu(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnStop( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_onstop(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnStop()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument3() -> get_onstop(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }

  IHTMLDocument2* createDocumentFragment()
  {
    IHTMLDocument2* pDocument = NULL;
    HRESULT hr = getDocument3() -> createDocumentFragment(&pDocument);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDocument;
  }
        
  IHTMLDocument2* getParentDocument()
  {
    IHTMLDocument2* pDocument = NULL;
    HRESULT hr = getDocument3() -> get_parentDocument(&pDocument);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDocument;
  }
        
  HRESULT putEnableDownload( 
            /* [in] */ bool v)
  {
    HRESULT hr = getDocument3() -> put_enableDownload(toVariantBool(v));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  bool getEnableDownload()
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument3() ->get_enableDownload(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT putBaseUrl( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getDocument3() -> put_baseUrl((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getBaseUrl()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument3() -> get_baseUrl(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  IDispatch* getChildNodes()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getDocument3() ->  get_childNodes(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  HRESULT putInheritStyleSheets( 
            /* [in] */ bool v)
  {
    HRESULT hr = getDocument3() -> put_inheritStyleSheets(toVariantBool(v));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  bool getInheritStyleSheets()
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument3() -> get_inheritStyleSheets(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT putOnBeforeEditFocus( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument3() -> put_onbeforeeditfocus(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforeEditFocus()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument3() -> get_onbeforeeditfocus(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);  
  }
        

  IHTMLElement* getElementById( 
            /* [in] */ _bstr_t v)
   {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getDocument3() -> getElementById( 
        (BSTR)v,
        &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }
       
  IHTMLElementCollection* getElementsByTagName( 
            /* [in] */ _bstr_t v)
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getDocument3() -> getElementsByTagName( 
        (BSTR)v,
        &pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pCollection;
  }
        
    //IHTMLDocument4 : public IDispatch
public:
  IHTMLDocument4* getDocument4()
  {
    HRESULT hr = S_OK;
    if (pDocument4 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument4,
                (void**)&pDocument4)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pDocument4 == NULL) {
      throw NullPointerException("IHTMLDocument4 is NULL");
    }

    return pDocument4;
  }

public:
  HRESULT focus()
  {
    HRESULT hr = getDocument4() -> focus();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

  bool hasFocus()
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument4() -> hasFocus(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT put_onselectionchange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument4() -> put_onselectionchange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnSelectionChange()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument4() -> get_onselectionchange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IDispatch* getNamespaces()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getDocument4() -> get_namespaces(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
     
  IHTMLDocument2* createDocumentFromUrl( 
            /* [in] */ _bstr_t bstrUrl,
            /* [in] */ _bstr_t bstrOptions)
  {
    IHTMLDocument2* pDocument = NULL;
    HRESULT hr = getDocument4() -> createDocumentFromUrl( 
        (BSTR)bstrUrl,
        (BSTR)bstrOptions,
        &pDocument);
  
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      
    return pDocument;
  }

  HRESULT putMedia( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getDocument4() -> put_media((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getMedia()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument4() -> get_media(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  IHTMLEventObj* createEventObject( 
            /* [in][optional] */ VARIANT *pvarEventObject)
  {
    IHTMLEventObj* pObj = NULL;
    HRESULT hr = getDocument4() -> createEventObject( 
        pvarEventObject,
        &pObj);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pObj;
  }
        
  bool fireEvent( 
            /* [in] */ _bstr_t bstrEventName,
            /* [in][optional] */ VARIANT *pvarEventObject)
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getDocument4() -> fireEvent( 
        (BSTR)bstrEventName,
        pvarEventObject,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  IHTMLRenderStyle* createRenderStyle( 
            /* [in] */ _bstr_t v)
  {
    IHTMLRenderStyle* pStyle = NULL;
    HRESULT hr = getDocument4() -> createRenderStyle( 
        (BSTR)v,
        &pStyle);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pStyle;
  }
        
  HRESULT put_oncontrolselect( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument4() -> put_oncontrolselect(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnControlSelect()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument4()-> get_oncontrolselect(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  _bstr_t getURLUnencoded()
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument4() -> get_URLUnencoded(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        

    //IHTMLDocument5 : public IDispatch
public:
  IHTMLDocument5* getDocument5()
  {
    HRESULT hr = S_OK;
    if (pDocument5 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument5,
                (void**)&pDocument5)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pDocument5 == NULL) {
      throw NullPointerException("IHTMLDocument5 is NULL");
    }
    return pDocument5;
  }

public:
  HRESULT putOnMouseWheel( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onmousewheel(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;

  }

  _variant_t getOnMouseWheel()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_onmousewheel(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLDOMNode* getDocType()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getDocument5() -> get_doctype(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMImplementation* getImplementation()
  {
    IHTMLDOMImplementation *pImp = NULL;
    HRESULT hr = getDocument5() -> get_implementation(&pImp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pImp;
  }
        
  IHTMLDOMAttribute* createAttribute( 
            /* [in] */ _bstr_t bstrattrName)
  {
    IHTMLDOMAttribute *pAttr = NULL;
    HRESULT hr = getDocument5() -> createAttribute( 
        (BSTR)bstrattrName,
        &pAttr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }
        
  IHTMLDOMNode* createComment( 
            /* [in] */ _bstr_t bstrdata)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getDocument5() -> createComment( 
        (BSTR)bstrdata,
        &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  HRESULT putOnFocusIn( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onmousewheel(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnFocusIn()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_onfocusin(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnFocusOut( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onfocusout(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnFocusOut()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_onfocusout(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnActivate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onactivate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnActivate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument5() -> get_onactivate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDeactivate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_ondeactivate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDeactivate()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_ondeactivate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnBeforeActivate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onbeforeactivate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforeActivate()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_onbeforeactivate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnBeforeDeactivate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument5() -> put_onbeforedeactivate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforeDeactivate()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument5() -> get_onbeforedeactivate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  _bstr_t getCompatMode( 
            /* [out][retval] */ BSTR *p)
  {
    BSTR bstr = NULL;
    HRESULT hr = getDocument5() -> get_compatMode(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
    
//    IHTMLDocument6 : public IDispatch
    
public:
  IHTMLDocument6* getDocument6()
  {
    HRESULT hr = S_OK;
    if (pDocument6 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDocument6,
                (void**)&pDocument6)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pDocument6 == NULL) {
      throw NullPointerException("IHTMLDocument6 is NULL");
    }
    return pDocument6;
  }

public:
  IHTMLDocumentCompatibleInfoCollection* getCompatible( 
            /* [out][retval] */ IHTMLDocumentCompatibleInfoCollection **p)
  {
    IHTMLDocumentCompatibleInfoCollection* pCollection = NULL;
    HRESULT hr = getDocument6()->get_compatible(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pCollection;
  }

        
  _variant_t getDocumentMode()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getDocument6()->get_documentMode(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }

  HRESULT putOnstorage( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument6()->put_onstorage(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnstorage()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument6()->get_onstorage(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }

  HRESULT putOnstoragecommit( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getDocument6()->put_onstoragecommit(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

        
  _variant_t getOnstoragecommit()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getDocument6()->get_onstoragecommit(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLElement2* getElement2ById( 
            /* [in] */ _bstr_t bstrId)
  {
    IHTMLElement2* pElement = NULL;
    HRESULT hr = getDocument6()->getElementById( 
        (BSTR)bstrId,
        &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }
        
  HRESULT updateSettings()
  {
    HRESULT hr = getDocument6()->updateSettings();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
};

}
