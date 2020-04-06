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
 *  HTMLElement.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/html/HTMLObject.h>

#pragma comment (lib, "urlmon.lib")


namespace SOL {

class HTMLElement : public HTMLObject {

private:
    IHTMLElement*  pElement;
  IHTMLElement2* pElement2; 
public:
  HTMLElement(IDispatch* pDisp)
  :HTMLObject(pDisp),
  pElement(NULL), pElement2(NULL)
  {

  }

public:
  ~HTMLElement()
  {
    if (pElement) {
      pElement->Release();
      pElement = NULL;
    }
    if (pElement2) {
      pElement2->Release();
      pElement2 = NULL;
    }
  }

private:
  IHTMLElement* getElement()
  {
    HRESULT hr = S_OK;
    if (pElement == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElement,
                (void**)&pElement)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pElement == NULL) {
      throw NullPointerException("IHTMLElement is NULL");
    }
    return pElement;
  }

public:
  IHTMLDOMNode* getDOMNode()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = S_OK;
    if ( FAILED(hr = getElement() -> QueryInterface(IID_IHTMLDOMNode,
                (void**)&pNode)) ) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pNode;
  }


public:
  HRESULT setAttribute( 
            /* [in] */ _bstr_t strAttributeName,
            /* [in] */ _variant_t AttributeValue,
            /* [in][defaultvalue] */ LONG lFlags = 1)
  {
    HRESULT hr = getElement() -> setAttribute( 
      strAttributeName,
      AttributeValue,
      lFlags);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
      
  _variant_t getAttribute( 
            /* [in] */ _bstr_t strAttributeName,
            /* [in][defaultvalue] */ LONG lFlags)
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> getAttribute( 
      strAttributeName,
      lFlags,
      &var);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  bool removeAttribute( 
            /* [in] */ _bstr_t strAttributeName,
            /* [in][defaultvalue] */ LONG lFlags)
  {
    VARIANT_BOOL vbool;

    HRESULT hr = getElement() -> removeAttribute( 
      strAttributeName,
      lFlags,
      &vbool);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }        
        
  HRESULT putClassName( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_className((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        

  _bstr_t getClassName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_className(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        

  HRESULT putId( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_id((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getId()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_id(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  _bstr_t getTagName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_tagName(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  IHTMLElement* getParentElement()
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getElement() -> get_parentElement(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }        
        
  IHTMLStyle* getStyle()
  {
    IHTMLStyle* pStyle = NULL;
    HRESULT hr = getElement() -> get_style(&pStyle);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pStyle;
  }        
        
  HRESULT putOnhelp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onhelp(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnhelp()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() ->  get_onhelp(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnclick( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onclick(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnclick()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onclick(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnDblClick( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_ondblclick(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnDblClick()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_ondblclick(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnKeydown( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onkeydown(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnKeydown()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onkeydown(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnKeyUp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onkeyup(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnKeyUp()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onkeyup(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnKeyPress( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onkeypress(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnKeyPress()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onkeypress(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnMouseOut( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onmouseout(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnMouseOut()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onmouseout(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnMouseOver( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onmouseover(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnMouseOver()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onmouseover(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnMouseMove( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onmousemove(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnMouseMove()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onmousemove(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnMouseDown( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onmousedown(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnMouseDown()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onmousedown(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnMouseUp( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onmouseup(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnMouseUp()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onmouseup(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  IDispatch* getDocument()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getElement() -> get_document(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
        
  HRESULT putTitle( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_title((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getTitle()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_title(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT putLanguage( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_language((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getLanguage()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_language(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT putOnSelectStart( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onselectstart((VARIANT)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnSelectStart()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_onselectstart(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT scrollIntoView( 
            /* [in][optional] */ _variant_t varargStart)
  {
    HRESULT hr = getElement() -> scrollIntoView(varargStart);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  bool contains( 
            /* [in] */ IHTMLElement *pChild)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement() -> contains( 
      pChild,
      &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }        
        
  long getSourceIndex()
  {
    long value = 0;
    HRESULT hr = getElement() -> get_sourceIndex(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  _variant_t getRecordNumber()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_recordNumber(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putLang( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_lang((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getLang()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_lang(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  long getOffsetLeft()
  {
    long value = 0;
    HRESULT hr = getElement() -> get_offsetLeft(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  long getOffsetTop()
  {
    long value = 0;
    HRESULT hr = getElement() -> get_offsetTop(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  long getOffsetWidth()
  {
    long value = 0;
    HRESULT hr = getElement() -> get_offsetWidth(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  long getOffsetHeight()
  {
    long value = 0;
    HRESULT hr = getElement() -> get_offsetHeight(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  IHTMLElement* getOffsetParent()
  {
    IHTMLElement *pElement = NULL;
    HRESULT hr = getElement() -> get_offsetParent(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }        
        
  HRESULT putInnerHTML( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_innerHTML((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getInnerHTML()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_innerHTML(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT putInnerText( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_innerText((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
                
  _bstr_t getInnerText()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_innerText(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        

  HRESULT putOuterHTML( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_outerHTML((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getOuterHTML()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_outerHTML(&bstr);
     if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT putOuterText( 
            /* [in] */ _bstr_t string)
  {
    HRESULT hr = getElement() -> put_outerText((BSTR)string);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _bstr_t getOuterText()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> get_outerText(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT insertAdjacentHTML( 
            /* [in] */ _bstr_t where,
            /* [in] */ _bstr_t html)
  {
    HRESULT hr = getElement() -> insertAdjacentHTML( 
      (BSTR) where,
      (BSTR) html);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  HRESULT insertAdjacentText( 
            /* [in] */ _bstr_t where,
            /* [in] */ _bstr_t text)
  {
    HRESULT hr = getElement() -> insertAdjacentText( 
      (BSTR) where,
      (BSTR) text);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  IHTMLElement* getParentTextEdit()
  {
    IHTMLElement *pElement = NULL;
    HRESULT hr = getElement() -> get_parentTextEdit(&pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }        

  bool getIsTextEdit()
  {
    VARIANT_BOOL vbool;  
    HRESULT hr = getElement() -> get_isTextEdit(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }        
        
  HRESULT click()
  {
    HRESULT hr = getElement() -> click();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  IHTMLFiltersCollection* getFilters()
  {
    IHTMLFiltersCollection* pCollection = NULL;
    HRESULT hr = getElement() -> get_filters(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pCollection;
  }        
        
  HRESULT putOnDragStart( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_ondragstart(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnDragStart()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement() -> get_ondragstart(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  _bstr_t toString()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement() -> toString(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        
        
  HRESULT putOnBeforeUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onbeforeupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnBeforeUpdate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() ->  get_onbeforeupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnAfterUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onafterupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnAfterUpdate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onafterupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnErrorUpdate( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onerrorupdate(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnErrorUpdate()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onerrorupdate(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnRowExit( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onrowexit(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnRowExit()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onrowexit(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnRowEnter( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onrowenter(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnRowEnter()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onrowenter(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnDatasetChanged( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_ondatasetchanged(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnDatasetChanged()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_ondatasetchanged(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnDataAvailable( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_ondataavailable(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnDataAvailable()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_ondataavailable(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnDatasetComplete( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_ondatasetcomplete(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnDatasetComplete()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_ondatasetcomplete(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  HRESULT putOnFilterChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement() -> put_onfilterchange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  _variant_t getOnFilterChange()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement() -> get_onfilterchange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }        
        
  IDispatch* getChildren()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getElement() -> get_children(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
        
  IDispatch* getAll()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getElement() -> get_all(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        

  //IHTMLElement2 interface 
private:
  IHTMLElement2* getElement2()
  {
    HRESULT hr = S_OK;
    if (pElement2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElement2,
                (void**)&pElement2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pElement2 == NULL) {
      throw NullPointerException("IHTMLElement2 is NULL");
    }
    return pElement2;
  }

public:
  _bstr_t getScopeName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> get_scopeName(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT setCapture( 
            /* [in][defaultvalue] */ VARIANT_BOOL containerCapture = -1)
  {
    HRESULT hr = getElement2() -> setCapture(containerCapture);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT releaseCapture()
  {
    HRESULT hr = getElement2() -> releaseCapture();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT putOnLoseCapture( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onlosecapture(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnLoseCapture()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement2() -> get_onlosecapture(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  _bstr_t componentFromPoint( 
            /* [in] */ long x,
            /* [in] */ long y)
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> componentFromPoint( 
        x,
        y,
        &bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT doScroll( 
            /* [in][optional] */ _variant_t component)
  {
    HRESULT hr = getElement2() -> doScroll(component);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT putOnScroll( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onscroll(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnScroll()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement2() -> get_onscroll(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDrag( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondrag(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDrag()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement2() -> get_ondrag(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDragEnd( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondragend(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDragEnd()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_ondragend(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }

  HRESULT putOnDragEnter( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondragenter(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDragEnter()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_ondragenter(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDragOver( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondragover(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDragOver()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_ondragover(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDragLeave( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondragleave(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDragLeave()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_ondragleave(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnDrop( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_ondrop(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnDrop()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_ondrop(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnBeforeCut( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onbeforecut(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforeCut()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onbeforecut(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnCut( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_oncut(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnCut()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_oncut(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnBeforeCopy( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onbeforecopy(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforeCopy()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onbeforecopy(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnCopy( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_oncopy(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnCopy()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_oncopy(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnBeforePaste( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onbeforepaste(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBeforePaste()
   {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onbeforepaste(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
       
  HRESULT putOnPaste( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onpaste(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnPaste()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement2() -> get_onpaste(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLCurrentStyle* getCurrentStyle()
  {
    IHTMLCurrentStyle* pStyle = NULL;
    HRESULT hr = getElement2() -> get_currentStyle(&pStyle);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pStyle;
  }
        
  HRESULT putOnPropertyChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onpropertychange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnPropertyChange()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getElement2() -> get_onpropertychange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLRectCollection* getClientRects()
  {
    IHTMLRectCollection* pCollection = NULL;
    HRESULT hr = getElement2() -> getClientRects(&pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pCollection;
  }
        
  IHTMLRect* getBoundingClientRect()
  {
    IHTMLRect* pRect = NULL;
    HRESULT hr = getElement2() -> getBoundingClientRect(&pRect);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pRect;
  }
        
  HRESULT setExpression( 
            /* [in] */ _bstr_t propname,
            /* [in] */ _bstr_t expression,
            /* [in][defaultvalue] */ _bstr_t language = L"")
  {
    HRESULT hr = getElement2() -> setExpression( 
        (BSTR)propname,
        (BSTR)expression,
        (BSTR)language);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getExpression( 
            /* [in] */ _bstr_t propname)
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> getExpression( 
        propname,
        &var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  bool removeExpression( 
            /* [in] */ _bstr_t propname)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement2() -> removeExpression( 
        propname,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  HRESULT putTabIndex( 
            /* [in] */ short v)
  {
    HRESULT hr = getElement2() -> put_tabIndex(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  short getTabIndex()
  {
    short value = 0;
    HRESULT hr = getElement2() -> get_tabIndex(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  HRESULT focus()
  {
    HRESULT hr = getElement2() -> focus();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT putAccessKey( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement2() -> put_accessKey(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getAccessKey()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> get_accessKey(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putOnBlur( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onblur(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnBlur()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onblur(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnFocus( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onfocus(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnFocus()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onfocus(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnResize( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onresize(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnResize()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onresize(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT blur()
  {
    HRESULT hr = getElement2() -> blur();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT addFilter( 
            /* [in] */ IUnknown *pUnk)
  {
    HRESULT hr = getElement2() -> addFilter(pUnk);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT removeFilter( 
            /* [in] */ IUnknown *pUnk)
  {
    HRESULT hr = getElement2() -> removeFilter(pUnk);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  long getClientHeight()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_clientHeight(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  long getClientWidth()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_clientWidth(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  long getClientTop()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_clientTop(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  long getClientLeft()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_clientLeft(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  bool attachEvent( 
            /* [in] */ BSTR event,
            /* [in] */ IDispatch *pDisp)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement2() -> attachEvent( 
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
    HRESULT hr = getElement2() -> detachEvent(event, pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }

  _variant_t getReadyState()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_readyState(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnReadyStateChange( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onreadystatechange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnReadyStateChange()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onreadystatechange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnRowsDelete( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onrowsdelete(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnRowsDelete()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onrowsdelete(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putOnRowsInserted( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onrowsinserted(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnRowsInserted()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onrowsinserted(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
       
    
  HRESULT putOnCellChange( 
           _variant_t v)
  {
    HRESULT hr = getElement2() -> put_oncellchange(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnCellChange()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_oncellchange(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  HRESULT putDir( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement2() -> put_dir(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getDir()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> get_dir(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  IDispatch* createControlRange()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getElement2() -> createControlRange(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  long getScrollHeight()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_scrollHeight(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  long getScrollWidth()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_scrollWidth(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  HRESULT putScrollTop( 
            /* [in] */ long v)
  {
    HRESULT hr = getElement2() -> put_scrollTop(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  long getScrollTop()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_scrollTop(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  HRESULT putScrollLeft( 
            /* [in] */ long v)
  {
    HRESULT hr = getElement2() -> put_scrollLeft(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  long getScrollLeft()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_scrollLeft(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  HRESULT clearAttributes()
  {
    HRESULT hr = getElement2() -> clearAttributes();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT mergeAttributes( 
            /* [in] */ IHTMLElement *mergeThis)
  {
    HRESULT hr = getElement2() -> mergeAttributes(mergeThis);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT putOnContextMenu( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_oncontextmenu(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getOnContextMenu()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> releaseCapture();
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  IHTMLElement* insertAdjacentElement( 
            /* [in] */ _bstr_t where,
            /* [in] */ IHTMLElement *insertedElement)
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getElement2() -> insertAdjacentElement( 
        where,
        insertedElement,
        &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }
        
  IHTMLElement* applyElement( 
            /* [in] */ IHTMLElement *apply,
            /* [in] */ _bstr_t where)
  {
    IHTMLElement* pElement = NULL;
    HRESULT hr = getElement2() -> applyElement( 
        apply,
        where,
        &pElement);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pElement;
  }
        
  _bstr_t getAdjacentText( 
            /* [in] */ _bstr_t where)
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> getAdjacentText( 
        (BSTR)where,
        &bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  _bstr_t replaceAdjacentText( 
            /* [in] */ _bstr_t where,
            /* [in] */ _bstr_t newText)
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> replaceAdjacentText( 
        (BSTR)where,
        (BSTR)newText,
        &bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  bool getCanHaveChildren()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement2() -> get_canHaveChildren( 
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  long addBehavior( 
            /* [in] */ _bstr_t bstrUrl,
            /* [in][optional] */ VARIANT *pvarFactory)
  {
    long cookie = 0;
    HRESULT hr = getElement2() -> addBehavior( 
        (BSTR)bstrUrl,
        pvarFactory,
        &cookie);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return cookie;
  }
        
  bool removeBehavior( 
            /* [in] */ long cookie)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getElement2() -> removeBehavior( 
        cookie,
        &vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
        
  IHTMLStyle* getRuntimeStyle()
  {
    IHTMLStyle* pStyle = NULL;
    HRESULT hr = getElement2() -> get_runtimeStyle(&pStyle);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pStyle;
  }
        
  IDispatch* getBehaviorUrns()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getElement2() -> get_behaviorUrns(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  HRESULT putTagUrn( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getElement2() -> put_tagUrn(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _bstr_t getTagUrn()
  {
    BSTR bstr = NULL;
    HRESULT hr = getElement2() -> get_tagUrn(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putOnBeforeEditFocus( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getElement2() -> put_onbeforeeditfocus(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
         
  _variant_t getOnBeforeEditFocus()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getElement2() -> get_onbeforeeditfocus(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }
        
  long getReadyStateValue()
  {
    long value = 0;
    HRESULT hr = getElement2() -> get_readyStateValue(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  IHTMLElementCollection* getElementsByTagName( 
            /* [in] */ _bstr_t v)
  {
    IHTMLElementCollection* pCollection = NULL;
    HRESULT hr = getElement2() -> getElementsByTagName( 
        v, &pCollection);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pCollection;
  }

public:
  void display()
  {

  }

};
    
}
