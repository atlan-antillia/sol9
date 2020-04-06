/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *   XMLDOMSchemaCollection.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/xml/Schema.h>
#include <sol/xml/SchemaItem.h>
#include <sol/xml/XMLDOMNode.h>

namespace SOL {

class XMLDOMSchemaCollection : public XMLObject {

private:
  MSXML2::IXMLDOMSchemaCollection2Ptr pCollection;

public:
  XMLDOMSchemaCollection(MSXML2::IXMLDOMSchemaCollection2Ptr collection=NULL)
  :pCollection(collection)
  {
    if (collection==NULL) {
      //2015/12/19
#ifdef XML4
      HRESULT hr = pCollection.CreateInstance(__uuidof(MSXML2::XMLSchemaCache40));
#endif
#ifdef XML6
      HRESULT hr = pCollection.CreateInstance(__uuidof(MSXML2::XMLSchemaCache60));
#endif
      
      if(FAILED(hr)) {
        throw Exception(E_FAIL, "Failed to create an instance of XMLDOMSchemaCollection", hr);
      }
    }
  }

public:
  ~XMLDOMSchemaCollection()
  {
    pCollection = NULL;
  }

public:
  MSXML2::IXMLDOMSchemaCollection2Ptr getCollectionPtr()
  {
    if (pCollection == NULL) {
      throw Exception(E_FATAL, "Error: XMLDOMSchemaCollection is NULL");
    }
    return pCollection;
  }

public:
  operator IDispatch*()
  {
    return(IDispatch*)getCollectionPtr();
  }

  HRESULT add(_bstr_t namespaceURI, const _variant_t & var)
  {
    return getCollectionPtr()->add(namespaceURI, var);
  }

  MSXML2::IXMLDOMNodePtr get(_bstr_t namespaceURI)
  {
    return getCollectionPtr()->get(namespaceURI);
  }

  HRESULT remove(_bstr_t namespaceURI)
  {
    return getCollectionPtr()->remove(namespaceURI);
  }

  long getLength()
  {
    return getCollectionPtr()-> Getlength();
  }

  _bstr_t getNamespaceURI(long index)
  {
    return getCollectionPtr()->GetnamespaceURI(index);
  }

  HRESULT addCollection(struct MSXML2::IXMLDOMSchemaCollection * otherCollection)
  {
    HRESULT hr = getCollectionPtr()->addCollection(otherCollection);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  IUnknownPtr getNewEnum()
  {
    return getCollectionPtr()->Get_newEnum();
  }

//<IXMLDOMSchemaCollection2>
  HRESULT validate()
  {
    HRESULT hr = getCollectionPtr()->validate();
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  void putValidateOnLoad(VARIANT_BOOL validateOnLoad)
  {
    getCollectionPtr()->PutvalidateOnLoad(
        validateOnLoad);
  }

  VARIANT_BOOL getValidateOnLoad()
  {
    return getCollectionPtr()->GetvalidateOnLoad();
  }

  MSXML2::ISchemaPtr getSchema(_bstr_t namespaceURI)
  {
    return getCollectionPtr()->getSchema(namespaceURI);
  }

  MSXML2::ISchemaItemPtr getDeclaration(struct MSXML2::IXMLDOMNode * node)
  {
    return getCollectionPtr()->getDeclaration(node);
  }
//</IXMLDOMSchemaCollection2>

public:
  void display()
  {
    long length = getLength();
    _tprintf(_T("<XMLDOMSchemaCollection length=\"%d\">\n"), length);
    try {
      const TCHAR* bv = _T("false");
      if (getValidateOnLoad() == VARIANT_TRUE) {
        bv = _T("true");
      }
      _tprintf(_T("<ValidateOnLoad>%s</ValidateOnLoad>\n"), bv);
    } catch (...) {
    }

    for (long i = 0; i<length; i++) {
      _bstr_t uri = getNamespaceURI(i);
      //_tprintf(_T("URI=%s\n"), (const TCHAR*)uri);
      try {
        Schema schema = getSchema(uri);
        schema.display();
      } catch (...) {
      }

      try {
        XMLDOMNode node = get(uri);
        SchemaItem item = getDeclaration((MSXML2::IXMLDOMNode*)node);
        item.display(_T("Declaration"));
      } catch (...) {
      }
    }
    _tprintf(_T("</XMLDOMSchemaCollection>\n"));

  }

};

}
