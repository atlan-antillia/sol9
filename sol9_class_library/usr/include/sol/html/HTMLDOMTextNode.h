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
 *  HTMLDOMTextNode.h
 *
 *****************************************************************************/

// SOL9 
// 2012/03/03

#pragma once


#include <sol/com/ComIDispatch.h>


namespace SOL {

class HTMLDOMTextNode : public ComIDispatch {

private:
  IHTMLDOMTextNode*  pNode;

  IHTMLDOMTextNode2* pNode2;
    
public:
  HTMLDOMTextNode(IDispatch* pDisp)
  :ComIDispatch(pDisp),
  pNode(NULL), pNode2(NULL)
  {

  }

public:
  ~HTMLDOMTextNode()
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
  IHTMLDOMTextNode* getNode()
  {
    HRESULT hr = S_OK;
    if (pNode == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMTextNode,
                (void**)&pNode)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pNode == NULL) {
      throw NullPointerException("IHTMLDOMTextNode is NULL");
    }
    return pNode;
  }


public:
  IHTMLDOMTextNode2* getNode2()
  {
    HRESULT hr = S_OK;
    if (pNode2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLDOMTextNode2,
                (void**)&pNode2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pNode2 == NULL) {
      throw NullPointerException("IHTMLDOMTextNode2 is NULL");
    }
    return pNode2;
  }

public:
  HRESULT putData( 
            /* [in] */ _bstr_t v)
  {
    HRESULT hr = getNode() -> put_data((BSTR)v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);


    return hr;
  }
        
  _bstr_t getData()
  {
    BSTR bstr = NULL;
    HRESULT hr = getNode() ->  get_data(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  _bstr_t toString()
  {
    BSTR bstr = NULL;
    HRESULT hr = getNode() -> toString(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  long getLength()
  {
    long value = 0;
    HRESULT hr = getNode() -> get_length(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
        
  IHTMLDOMNode* splitText( 
            /* [in] */ long offset)
  {
    IHTMLDOMNode* pNode = NULL; 
    HRESULT hr = getNode() -> splitText( 
      offset,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }
        
    
//    IHTMLDOMTextNode2 : public IDispatch    
public:
  _bstr_t substringData( 
            /* [in] */ long offset,
            /* [in] */ long count)
  {
    BSTR bstr = NULL;
    HRESULT hr = getNode2() -> substringData( 
      offset,
      count,
      &bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }
        
  HRESULT appendData( 
            /* [in] */ _bstr_t bstrstring)
  {
    HRESULT hr = getNode2() -> appendData( 
      (BSTR)bstrstring);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT insertData( 
            /* [in] */ long offset,
            /* [in] */ _bstr_t bstrstring)
  {
    HRESULT hr = getNode2() -> insertData( 
        offset,
        (BSTR)bstrstring);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT deleteData( 
            /* [in] */ long offset,
            /* [in] */ long count)
  {
    HRESULT hr = getNode2() -> deleteData( 
      offset,
      count);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
  HRESULT replaceData( 
            /* [in] */ long offset,
            /* [in] */ long count,
            /* [in] */ _bstr_t bstrstring)
  {
    HRESULT hr = getNode2() -> replaceData( 
      offset,
      count,
      (BSTR)bstrstring);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }
        
};
    
}
