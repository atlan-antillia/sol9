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
 *  HTMLDOMAttribute.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/html/HTMLObject.h>

namespace SOL {

class HTMLDOMAttribute : public HTMLObject {

private:
  IHTMLDOMAttribute* pAttr;
  IHTMLDOMAttribute2* pAttr2;
  IHTMLDOMAttribute3* pAttr3;

public:
  HTMLDOMAttribute(IDispatch* pDisp)
  :HTMLObject(pDisp),
  pAttr(NULL), pAttr2(NULL), pAttr3(NULL)
  {

  }

public:
  ~HTMLDOMAttribute()
  {
    if (pAttr) {
      pAttr -> Release();
      pAttr = NULL;
    }
    if (pAttr2) {
      pAttr2 -> Release();
      pAttr2 = NULL;
    }
    if (pAttr3) {
      pAttr3 -> Release();
      pAttr3 = NULL;
    }
  }

public:
  IHTMLDOMAttribute* getAttr()
  {
    HRESULT hr = S_OK;
    if (pAttr == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMAttribute,
                (void**)&pAttr)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pAttr == NULL) {
      throw NullPointerException("IHTMLDOMAttribute is NULL");
    }
    return pAttr;
  }

public:
  IHTMLDOMAttribute2* getAttr2()
  {
    HRESULT hr = S_OK;
    if (pAttr2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMAttribute2,
                (void**)&pAttr2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pAttr2 == NULL) {
      throw NullPointerException("IHTMLDOMAttribute2 is NULL");
    }
    return pAttr2;
  }

public:
  IHTMLDOMAttribute3* getAttr3()
  {
    HRESULT hr = S_OK;
    if (pAttr3 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMAttribute3,
                (void**)&pAttr3)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pAttr3 == NULL) {
      throw NullPointerException("IHTMLDOMAttribute3 is NULL");
    }
    return pAttr3;
  }

public:
  _bstr_t getNodeName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getAttr() -> get_nodeName(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putNodeValue( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getAttr() -> put_nodeValue(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getNodeValue()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getAttr() -> get_nodeValue(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  bool getSpecified()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getAttr() ->get_specified(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
//    IHTMLDOMAttribute2 : public IDispatch
public:
  _bstr_t getName()
  {
    BSTR bstr = NULL;

    HRESULT hr = getAttr2() -> get_name(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putValue( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getAttr2() -> put_value(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getValue()
  {
    BSTR bstr = NULL;
    HRESULT hr = getAttr2() -> get_value(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  bool getExpando()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getAttr2() -> get_expando(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  long getNodeType()
  {
    long value = 0;
    HRESULT hr = getAttr2() ->get_nodeType(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  IHTMLDOMNode* getParentNode()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> get_parentNode(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IDispatch* getChildNodes()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getAttr2() -> get_childNodes(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  IHTMLDOMNode* getFirstChild()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> get_firstChild(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* getLastChild()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> get_lastChild(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* getPreviousSibling()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> get_previousSibling(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* getNextSibling()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> get_nextSibling(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IDispatch* getAttributes()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getAttr2() -> get_attributes(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  IDispatch* getOwnerDocument()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getAttr2() ->  get_ownerDocument(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  IHTMLDOMNode* insertBefore( 
            /* [in] */ IHTMLDOMNode *newChild,
            /* [in][optional] */ _variant_t refChild)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> insertBefore( 
        newChild,
        refChild,
        &pNode);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* replaceChild( 
            /* [in] */ IHTMLDOMNode *newChild,
            /* [in] */ IHTMLDOMNode *oldChild)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> replaceChild( 
        newChild,
        oldChild,
        &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* removeChild( 
            /* [in] */ IHTMLDOMNode *oldChild)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> removeChild( 
        oldChild, &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* appendChild( 
            /* [in] */ IHTMLDOMNode *newChild)
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getAttr2() -> appendChild( 
        newChild, &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  bool hasChildNodes()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getAttr2() -> hasChildNodes(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  IHTMLDOMAttribute* cloneNode( 
            /* [in] */ bool fDeep)
  {
    IHTMLDOMAttribute* pAttr = NULL;
    HRESULT hr = getAttr2() -> cloneNode(toVariantBool(fDeep), &pAttr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }

//    IHTMLDOMAttribute3 : public IDispatch
public:        
  IHTMLElement2* getOwnerElement()
  {
    IHTMLElement2* pElement = NULL;
    HRESULT hr = getAttr3() -> get_ownerElement(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }      
};

}
