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
 *  HTMLElementCollection.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/Object.h>
#include <sol/html/HTMLObject.h>
#include <sol/html/HTMLElement.h>
#include <sol/html/HTMLDOMNode.h>

namespace SOL {

class HTMLElementCollection : public HTMLObject {

private:
  IHTMLElementCollection* pCollection;
  IHTMLElementCollection2* pCollection2;
  IHTMLElementCollection3* pCollection3;
  IHTMLElementCollection4* pCollection4;
  
public:
  HTMLElementCollection(IDispatch* pDisp)
  :HTMLObject(pDisp),
  pCollection (NULL), pCollection2(NULL),
  pCollection3(NULL), pCollection4(NULL)
  {

  }

public:
  ~HTMLElementCollection()
  {
    if (pCollection) {
      pCollection -> Release();
      pCollection = NULL;
    }
    if (pCollection2) {
      pCollection2 -> Release();
      pCollection2 = NULL;
    }
    if (pCollection3) {
      pCollection3 -> Release();
      pCollection3 = NULL;
    }
    if (pCollection4) {
      pCollection4 -> Release();
      pCollection4 = NULL;
    }
  }

private:
  IHTMLElementCollection* getCollection()
  {
    HRESULT hr = S_OK;
    if (pCollection == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElementCollection,
                (void**)&pCollection)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pCollection == NULL) {
      throw NullPointerException("IHTMLElementCollection is NULL");
    }
    return pCollection;
  }

public:

  _bstr_t toString()
  {
    BSTR bstr = NULL;
    HRESULT hr = getCollection() -> toString(&bstr);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return _bstr_t(bstr, false);
  }        

  HRESULT putLength( 
            /* [in] */ long v)
  {
    HRESULT hr = getCollection() -> put_length(v);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  long getLength()
  {
    long value;
    HRESULT hr = getCollection() -> get_length(&value);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return value;
  }        
        
  IUnknown* getNewEnum()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = getCollection() -> get__newEnum(&pUnk);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pUnk;
  }        
        
  IDispatch* item( 
            /* [in][optional] */ _variant_t name,
            /* [in][optional] */ _variant_t index)
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getCollection() -> item( 
      name,
      index,
      &pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
        
  IDispatch* tags( 
            /* [in] */ _variant_t tagName)
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getCollection() ->tags( 
      tagName,
      &pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
        


//    IHTMLElementCollection2 : public IDispatch
private:
  IHTMLElementCollection2* getCollection2()
  {
    HRESULT hr = S_OK;
    if (pCollection2 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElementCollection2,
                (void**)&pCollection2)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pCollection2 == NULL) {
      throw NullPointerException("IHTMLElementCollection2 is NULL");
    }
    return pCollection2;
  }

public:
  IDispatch* urns( 
            /* [in] */ _variant_t urn)
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getCollection2() -> urns( 
      urn,
      &pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
        

//    IHTMLElementCollection3 : public IDispatch
private:
  IHTMLElementCollection3* getCollection3()
  {
    HRESULT hr = S_OK;
    if (pCollection3 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElementCollection3,
                (void**)&pCollection3)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pCollection3 == NULL) {
      throw NullPointerException("IHTMLElementCollection3 is NULL");
    }
    return pCollection3;
  }

public:
  IDispatch* namedItem( 
            /* [in] */ _bstr_t name)
        
  {
    IDispatch* pDisp = NULL;
    HRESULT hr = getCollection3() -> namedItem( 
      name,
      &pDisp);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pDisp;
  }        
    

//    IHTMLElementCollection4 : public IDispatch
private:
  IHTMLElementCollection4* getCollection4()
  {
    HRESULT hr = S_OK;
    if (pCollection4 == NULL) {
      IDispatch* pDisp = getIDispatch();

      if ( FAILED(hr = pDisp->QueryInterface(IID_IHTMLElementCollection4,
                (void**)&pCollection4)) ) {
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
    }

    if (pCollection4 == NULL) {
      throw NullPointerException("IHTMLElementCollection4 is NULL");
    }
    return pCollection4;
  }

public:
  HRESULT getLength(long* p)
  {
    //long value = 0;
    HRESULT hr = getCollection4() -> get_length(p);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return hr;
  }        
        
  //2012/03/23 Updated
  IHTMLElement2* item( 
            /* [in] */ long index)        
  {
    IHTMLElement2* pNode = NULL;
    HRESULT hr = getCollection4() -> item( 
      index,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }        

  //2012/03/23 Updated
  IHTMLElement2* getNamedItem( 
            /* [in] */ _bstr_t name)
  {
    IHTMLElement2* pNode = NULL;
    HRESULT hr = getCollection4() -> namedItem( 
      name,
      &pNode);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pNode;
  }        

public:
  void display()
  {
    long length = getLength();
    for (long i = 0; i<length; i++) {
      SOL::HTMLElement element = (IHTMLElement*)item(i);
      SOL::HTMLDOMNode node = element.getDOMNode();
      node.display();
    }
  }
};
    
}
