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
 *  SAXXMLReader.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
// 2015/12/19 Modifed SAXXMLReader construcotr

#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/xml/SAXLocator.h>
#include <sol/xml/SAXContentHandlerImpl.h>
#include <sol/xml/SAXErrorHandlerImpl.h>
#include <sol/xml/SAXDTDHandlerImpl.h>
#include <sol/xml/SAXDeclHandlerImpl.h>
#include <sol/xml/SAXLexicalHandlerImpl.h>
#include <sol/xml/SAXSchemaDeclHandlerImpl.h>

#include <sol/xml/XMLDOMSchemaCollection.h>

namespace SOL {

class SAXXMLReader : public XMLObject {
private:
  MSXML2::ISAXXMLReaderPtr pReader;

public:
  SAXXMLReader(
#ifdef XML4
    const GUID clsId=__uuidof(MSXML2::SAXXMLReader40))
#endif
#ifdef XML6
    const GUID clsId=__uuidof(MSXML2::SAXXMLReader60))
#endif
  :pReader(NULL)
  {
    HRESULT hr = pReader.CreateInstance(clsId);
    //2015/12/19 Modified 
    if(FAILED(hr)) {
      throw Exception(E_FAIL, "Failed to create an instance of SAXXMLReader\n", hr);
    }
  }

public:
  ~SAXXMLReader()
  {
    pReader = NULL;
  }

public:
  MSXML2::ISAXXMLReaderPtr getReaderPtr()
  {
    if(pReader ==NULL) {
      throw Exception(E_FATAL, "Error: SAXXMLReader is NULL");
    }
    return pReader;
  }

public:
  unsigned short* toShort(const wchar_t* pwchName)
  {
    return(unsigned short*)(void*)pwchName;
  }

public:
  wchar_t* toWchar(const unsigned short* pwchName)
  {
    return(wchar_t*)(void*)pwchName;
  }

public:

  VARIANT_BOOL getFeature(const wchar_t * pwchName)
  {
    return getReaderPtr() -> getFeature(toShort(pwchName));
  }

  HRESULT putFeature(const wchar_t* pwchName, VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(pwchName), vfValue);
  }

  _variant_t getProperty(const wchar_t* pwchName)
  {
    return getReaderPtr() -> getProperty(toShort(pwchName));
  }

  HRESULT putProperty(const wchar_t* pwchName, const _variant_t & varValue)
  {
    return getReaderPtr() -> putProperty(toShort(pwchName), varValue);
  }
  
  MSXML2::ISAXEntityResolverPtr getEntityResolver()
  {
    return getReaderPtr() -> getEntityResolver();
  }

  HRESULT putEntityResolver(MSXML2::ISAXEntityResolver * pResolver)
  {
    return getReaderPtr() -> putEntityResolver(pResolver);
  }

  MSXML2::ISAXContentHandlerPtr getContentHandler()
  {
    return getReaderPtr() -> getContentHandler();
  }

  HRESULT putContentHandler(MSXML2::ISAXContentHandler * pHandler)
  {
    return getReaderPtr() -> putContentHandler(pHandler);
  }

  MSXML2::ISAXDTDHandlerPtr getDTDHandler()
  {
    return getReaderPtr() -> getDTDHandler();
  }

  HRESULT putDTDHandler(MSXML2::ISAXDTDHandler * pHandler)
  {
    return getReaderPtr() -> putDTDHandler(pHandler);
  }

  MSXML2::ISAXErrorHandlerPtr getErrorHandler()
  {
    return getReaderPtr() -> getErrorHandler();
  }

  HRESULT putErrorHandler(MSXML2::ISAXErrorHandler * pHandler)
  {
    return getReaderPtr() -> putErrorHandler(pHandler);
  }

  //SOL specific method
  HRESULT putDeclHandler(SAXDeclHandlerImpl* declHandler)
  {
    return putProperty(L"http://xml.org/sax/properties/declaration-handler",
      _variant_t((IUnknown*)declHandler) );
  }

  //SOL specific method
  HRESULT putLexicalHandler(SAXLexicalHandlerImpl* lexicalHandler)
  {
    return putProperty(L"http://xml.org/sax/properties/lexical-handler",
      _variant_t((IUnknown*)lexicalHandler));
  }

  //SOL specific method
  HRESULT putSchemaCollection(XMLDOMSchemaCollection* schemaCollection)
  {
    return putProperty(L"schemas", _variant_t((IUnknown*)(*schemaCollection)) );
  }

  HRESULT putSchemaCollection(MSXML2::IXMLDOMSchemaCollection* schemaCollection)
  {
    return putProperty(L"schemas", _variant_t((IUnknown*)schemaCollection) );
  }

  //SOL specific method
  HRESULT putSchemaDeclHandler(SAXSchemaDeclHandlerImpl* schemaDeclHandler)
  {
    return putProperty(L"schema-declaration-handler", _variant_t((IDispatch*)schemaDeclHandler) );
  }

  HRESULT enableSchemaValidation(VARIANT_BOOL flag=VARIANT_TRUE)
  {
    return putFeature (L"schema-validation", flag);
  }

  wchar_t* getBaseURL()
  {
    return toWchar(getReaderPtr() -> getBaseURL());
  }

  HRESULT putBaseURL(const wchar_t * pwchBaseUrl)
  {
    return getReaderPtr() -> putBaseURL(toShort(pwchBaseUrl));
  }

  //unsigned short * getSecureBaseURL();
  wchar_t* getSecureBaseURL()
  {
    return toWchar(getReaderPtr() -> getSecureBaseURL());
  }

  HRESULT putSecureBaseURL(const wchar_t* pwchSecureBaseUrl)
  {
    return getReaderPtr() -> putSecureBaseURL(toShort(pwchSecureBaseUrl));
  }
  
  HRESULT parse(const _variant_t & varInput = vtMissing)
  {
    return getReaderPtr() -> parse(varInput);
  }
  
  HRESULT parseURL(const wchar_t* pwchUrl)
  {
    return getReaderPtr() -> parseURL(toShort(pwchUrl));
  }

//2011/02/18
  HRESULT putFeatureNamespaces(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"http://xml.org/sax/features/namespaces"), vfValue);
  }

  HRESULT putFeatureNamespacePrefixes(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"http://xml.org/sax/features/namespace-prefixes"), vfValue);
  }

  HRESULT putFeatureExternalGeneralEntities(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"http://xml.org/sax/features/external-general-entities"), vfValue);
  }

  HRESULT putFeatureExternalParameterEntities(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"http://xml.org/sax/features/external-parameter-entities"), vfValue);
  }

  HRESULT putFeatureNormalizeLineBreaks(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"normalize-line-breaks"), vfValue);
  }

  HRESULT putFeatureServerHttpRequest(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"server-http-request"), vfValue);
  }

  HRESULT putFeatureProhibitDTD(VARIANT_BOOL vfValue)
  {
    return getReaderPtr() -> putFeature(toShort(L"prohibit-dtd"), vfValue);
  }

};

}
