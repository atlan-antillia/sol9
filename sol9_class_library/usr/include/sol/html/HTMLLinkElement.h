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
 *  HTMLLinkElement.h
 *
 *****************************************************************************/

// SOL9 
// 2012/03/03

#pragma once

#include <sol/com/ComIDispatch.h>

namespace SOL {

class HTMLLinkElement :public ComIDispatch {

private:
  IHTMLLinkElement*  pElement;
  IHTMLLinkElement2* pElement2;
  IHTMLLinkElement3* pElement3;
  IHTMLLinkElement4* pElement4;

public:
  HTMLLinkElement(IDispatch* pDisp)
  :ComIDispatch(pDisp),
  pElement(NULL),  pElement2(NULL),
  pElement3(NULL), pElement4(NULL)
    {
  }

public:
  ~HTMLLinkElement()
  {
    if (pElement) {
      pElement -> Release();
      pElement = NULL;
    }
    if (pElement2) {
      pElement2 -> Release();
      pElement2 = NULL;
    }
    if (pElement3) {
      pElement3 -> Release();
      pElement3 = NULL;
    }
    if (pElement4) {
      pElement4 -> Release();
      pElement4 = NULL;
    }
  }

public:
   IHTMLLinkElement* getElement()
   {
    HRESULT hr = S_OK;
    if (pElement == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLLinkElement,
                (void**)&pElement)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pElement == NULL) {
      throw NullPointerException("IHTMLLinkElement is NULL");
    }
    return pElement;
   }

public:
  HRESULT  putHref( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement() -> put_href((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

  _bstr_t  getHref()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_href(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT  putRel( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement() -> put_rel(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getRel()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_rel(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT  putRev( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement() -> put_rev((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getRev()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_rev(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT  putType( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement() -> put_type((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getType()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_type(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  _bstr_t  getReadyState()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_readyState(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT  putOnReadyStateChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onreadystatechange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t  getOnReadyStateChange()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onreadystatechange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT  putOnLoad( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onload(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t  getOnLoad()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onload(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT  putOnError( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onerror(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t  getOnError()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onerror(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLStyleSheet*  getStyleSheet()
  {
    IHTMLStyleSheet* pSheet = NULL;
    HRESULT hr = getElement() -> get_styleSheet(&pSheet);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pSheet;
  }
        
  HRESULT  putDisabled( 
            /* [in] */ bool v)
  {
    HRESULT hr = getElement() -> put_disabled( toVariantBool(v) );
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  bool  getDisabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement() -> get_disabled(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT  putMedia( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement() -> put_media((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getMedia()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_media(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
    
  //IHTMLLinkElement2 : public IDispatch
public:
   IHTMLLinkElement2* getElement2()
   {
    HRESULT hr = S_OK;
    if (pElement2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLLinkElement2,
                (void**)&pElement2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pElement2 == NULL) {
      throw NullPointerException("IHTMLLinkElement2 is NULL");
    }
    return pElement2;
   }

public:

  HRESULT  putTarget( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement2() -> put_target((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getTarget()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> get_target(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        

  //IHTMLLinkElement3 : public IDispatch
public:
   IHTMLLinkElement3* getElement3()
   {
    HRESULT hr = S_OK;
    if (pElement3 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLLinkElement3,
                (void**)&pElement3)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pElement3 == NULL) {
      throw NullPointerException("IHTMLLinkElement3 is NULL");
    }
    return pElement3;
   }

public:
  HRESULT  putCharset( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement3() -> put_charset((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getCharset()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement3() -> get_charset(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT  putHrefLang( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement3() -> put_hreflang((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getHrefLang()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement3() -> get_hreflang(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }


    
  /*
  //IHTMLLinkElement4 : public IDispatch
public:
   IHTMLLinkElement4* getElement()
   {
    HRESULT hr = S_OK;
    if (pElement4 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLLinkElement4,
                (void**)&pElement4)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pElement4 == NULL) {
      throw NullPointerException("IHTMLLinkElement4 is NULL");
    }
    return pElement4;
   }

public:
  HRESULT  putHref( 
            _bstr_t v)
  {
    HRESULT hr = getElement4() -> put_href((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t  getHref()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement4() -> get_href(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
  */  

public:
  virtual void display()
  {
    _tprintf(_T("Href = %s\n"), (const TCHAR*)getHref());
        
    _tprintf(_T("Rel = %s\n"), (const TCHAR*)getRel());
        
    _tprintf(_T("Rev = %s\n"), (const TCHAR*)getRev());        
    _tprintf(_T("Type = %s\n"), (const TCHAR*)getType());        
        
    _tprintf(_T("ReadyState = %s\n"), (const TCHAR*)getReadyState());        
    _tprintf(_T("Media = %s\n"), (const TCHAR*)getMedia());        
        
    _tprintf(_T("Target = %s\n"), (const TCHAR*)getTarget());        
    
    _tprintf(_T("Charset = %s\n"), (const TCHAR*)getCharset());   
  }
};
    
}



