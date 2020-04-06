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
 *  HTMLDOMNode.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/23

#pragma once


#include <sol/html/HTMLObject.h>
#include <sol/html/HTMLDOMAttribute.h>
#include <sol/html/HTMLAttributeCollection.h>


namespace SOL {

class HTMLDOMNode : public HTMLObject {
public:
  static const int NODE_ELEMENT = 1;
  static const int NODE_TEXT    = 3;

private:
  IHTMLDOMNode* pNode;
  IHTMLDOMNode2* pNode2;

public:
  HTMLDOMNode(IDispatch* pDisp)
  :HTMLObject(pDisp),
  pNode(NULL), pNode2(NULL)
  {
  }

public:
  ~HTMLDOMNode()
  {
    if (pNode) {
      pNode -> Release();
      pNode = NULL;
    }
    if (pNode2) {
      pNode2 -> Release();
      pNode2 = NULL;
    }
  }


public:
  IHTMLDOMNode* getNode()
  {
    HRESULT hr = S_OK;
    if (pNode == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMNode,
                (void**)&pNode)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pNode == NULL) {
      throw NullPointerException("IHTMLDOMNode is NULL");
    }
    return pNode;
  }


public:
  IHTMLDOMNode2* getNode2()
  {
    HRESULT hr = S_OK;
    if (pNode2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMNode2,
                (void**)&pNode2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pNode2 == NULL) {
      throw NullPointerException("IHTMLDOMNode2 is NULL");
    }
    return pNode2;
  }

public:
  long getNodeType()
  {
    long value = 0;
    HRESULT hr = getNode() -> get_nodeType(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }

  IHTMLDOMNode* getParentNode()
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> get_parentNode(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  bool hasChildNodes()
  {
    VARIANT_BOOL vbool;

    HRESULT hr = getNode() -> hasChildNodes(&vbool);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return toBool(vbool);
  }
        
  IDispatch* getChildNodes()
  {
    IDispatch* pDisp = NULL; 
    HRESULT hr = getNode() -> get_childNodes(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }
        
  IDispatch* getAttributes()
  {
    IDispatch* pDisp = NULL; 
    HRESULT hr = getNode() -> get_attributes(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }

  IHTMLDOMNode* insertBefore( 
            /* [in] */ IHTMLDOMNode *newChild,
            /* [in][optional] */ _variant_t refChild)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> insertBefore( 
      newChild,
      refChild,
      &pNode);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* removeChild( 
            /* [in] */ IHTMLDOMNode *oldChild)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> removeChild( 
      oldChild,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* replaceChild( 
            /* [in] */ IHTMLDOMNode *newChild,
            /* [in] */ IHTMLDOMNode *oldChild)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> replaceChild( 
      newChild,
      oldChild,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* cloneNode( 
            /* [in] */ bool fDeep)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> cloneNode( 
      toVariantBool(fDeep),
               &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* removeNode( 
            /* [in][defaultvalue] */ bool fDeep)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> removeNode( 
      toVariantBool(fDeep),
      &pNode);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* swapNode( 
            /* [in] */ IHTMLDOMNode *otherNode)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> swapNode( 
      otherNode,
      &pNode);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* replaceNode( 
            /* [in] */ IHTMLDOMNode *replacement)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> replaceNode( 
    replacement,
      &pNode);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* appendChild( 
            /* [in] */ IHTMLDOMNode *newChild)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> appendChild( 
      newChild,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }

  _bstr_t getNodeName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getNode() -> get_nodeName(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT putNodeValue( 
            /* [in] */ _variant_t v)
  {
    HRESULT hr = getNode() -> put_nodeValue(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  _variant_t getNodeValue()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getNode() -> get_nodeValue(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _variant_t(var, false);
  }

  _bstr_t getName()
  {
    BSTR bstr = NULL;
    HRESULT hr = getNode() -> get_nodeName(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }


  _bstr_t getValue()
  {
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = getNode() -> get_nodeValue(&var);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    VARIANT dst; 
    VariantInit(&dst); 
    VariantChangeType(&dst, &var, 0, VT_BSTR); 
    return _bstr_t(dst.bstrVal, false);
  }


  IHTMLDOMNode* getFirstChild()
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> get_firstChild(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
        }
        
  IHTMLDOMNode* getLastChild()
  {
    IHTMLDOMNode* pNode = NULL;
    HRESULT hr = getNode() -> get_lastChild(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
        }
        
  IHTMLDOMNode* getPreviousSibling()
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> get_previousSibling(&pNode); 
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
  IHTMLDOMNode* getNextSibling()
  {
    IHTMLDOMNode* pNode = NULL;

    HRESULT hr = getNode() -> get_nextSibling(&pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
//    IHTMLDOMNode2 : public IDispatch
public:
  IDispatch* getOwnerDocument()
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getNode2() -> get_ownerDocument(&pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }

public:
  void display()
  {
    _bstr_t name = getName();

    _bstr_t value = getValue();

    long nodeType = getNodeType();
    //printf("Node_Type = %d\n", nodeType);

    if (nodeType == HTMLDOMNode::NODE_ELEMENT) {
      _tprintf(_T("<%s"), (const TCHAR*)name);
      SOL::HTMLAttributeCollection attributes = getAttributes();
      long len = attributes.getLength();
      for (long i = 0; i<len; i++) {
        SOL::HTMLDOMAttribute attr = attributes.item(i);
        _tprintf(_T(" %s=\"%s\""), 
            (const TCHAR*)attr.getName(), 
            (const TCHAR*)attr.getValue());      }
      _tprintf(_T("> \n"));

    } else {
      _tprintf(_T("%s\n"), (const TCHAR*)value);    
    }
  }

};

}
