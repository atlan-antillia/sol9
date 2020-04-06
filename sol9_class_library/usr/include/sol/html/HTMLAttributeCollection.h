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
 *  HTMLAttributeCollection.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/html/HTMLObject.h>

namespace SOL {

class HTMLAttributeCollection :public HTMLObject {

private:
  IHTMLAttributeCollection3* pCollection3;

public:
  HTMLAttributeCollection(IDispatch* pDisp)
  :HTMLObject(pDisp),
  pCollection3(NULL)
  {
    
  }

public:
  ~HTMLAttributeCollection()
  {
    if (pCollection3) {
      pCollection3 -> Release();
      pCollection3 = NULL;
    }
  }

public:
  IHTMLAttributeCollection3* getCollection3()
  {
    HRESULT hr = S_OK;
    if (pCollection3 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLAttributeCollection3,
                (void**)&pCollection3)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }
    if (pCollection3 == NULL) {
      throw NullPointerException("IHTMLAttributeCollection3 is NULL");
    }
    return pCollection3;
  }

public:
  IHTMLDOMAttribute* getNamedItem( 
            /* [in] */ _bstr_t bstrName)
  {
    IHTMLDOMAttribute* pAttr = NULL; 
    HRESULT hr = getCollection3() -> getNamedItem( 
      bstrName,
      &pAttr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }
          
  IHTMLDOMAttribute* setNamedItem( 
            /* [in] */ IHTMLDOMAttribute *pNodeIn)
  {
    IHTMLDOMAttribute* pAttr = NULL; 
    HRESULT hr = getCollection3() -> setNamedItem( 
      pNodeIn,
      &pAttr);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }
        
  IHTMLDOMAttribute* removeNamedItem( 
            /* [in] */ _bstr_t bstrName)
  {
    IHTMLDOMAttribute* pAttr = NULL; 
    HRESULT hr = getCollection3() -> removeNamedItem( 
      bstrName,
      &pAttr);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }
        
  IHTMLDOMAttribute* item( 
            /* [in] */ long index)
  {
    IHTMLDOMAttribute* pAttr = NULL; 
    HRESULT hr = getCollection3() -> item( 
      index,
      &pAttr);

    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pAttr;
  }
        
  long getLength()
  {
    long value = 0;
    HRESULT hr = getCollection3() -> get_length(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }
};
    
}

