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
 *  SAXSchemaReader.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once
#include <sol/xml/SAXXMLReader.h>
#include <sol/xml/SAXAttributes.h>

namespace SOL {

// Read xsd file an extrace the data of 'schema' element.
class SAXSchemaReader :public SAXXMLReader {

private:
  //<InternalClass> ---------------------------------------------
  //Derive your own Contenthandler class from SAXContentHandlerImpl.
  class SAXSchemaContentHandler: public SAXContentHandlerImpl {

  public:
    //<xsd:schema> attribute values
    _bstr_t values[9];
    
  public:
    static enum {
      targetNamespace,
      version,
      xmlns,
      finalDefault,
      blockDefault,
      id,
      elementFormDefault,
      attributeFormDefault,
      xml_lang
    } ATTRIBUTES;

  public:
    SAXSchemaContentHandler()
    {
    }

  public:
    virtual void startElement(
      __in const _bstr_t uri,
      __in const _bstr_t localName,
      __in const _bstr_t qName,
      __in struct MSXML2::ISAXAttributes * pAttributes)
    {
      static const char* names[] ={
      "targetNamespace",
      "version",
      "xmlns",
      "finalDefault",
      "blockDefault",
      "id",  
      "elementFormDefault",
      "attributeFormDefault",
      "xml:lang"};

      if (localName == _bstr_t("schema")) {
        _tprintf(_T("SAXSchemaReader::SAXSchemaContentHandlerstartElement() uri=%s localName=%s qName=%s\n"),
          (const TCHAR*) uri,
          (const TCHAR*)localName,
          (const TCHAR*)qName);
        
        SAXAttributes attributes = pAttributes;
        for (int i = 0; i<CountOf(names); i++) {
          _bstr_t value = "";
          values[i] = "";
          try {
            attributes.getValueFromQName(names[i], value);
            values[i] = value;
          } catch (...) {
          }
        }
      }
    }
  };
/*
<!ATTLIST %schema;
   targetNamespace      %URIref;               #IMPLIED
   version              CDATA                  #IMPLIED
   %nds;                %URIref;               #FIXED 'http://www.w3.org/2001/XMLSchema'
   xmlns                CDATA                  #IMPLIED
   finalDefault         %complexDerivationSet; ''
   blockDefault         %blockSet;             ''
   id                   ID                     #IMPLIED
   elementFormDefault   %formValues;           'unqualified'
   attributeFormDefault %formValues;           'unqualified'
   xml:lang             CDATA                  #IMPLIED
   %schemaAttrs;>
*/
  //</InternalClass> --------------------------------------------
      
private:
  SAXSchemaContentHandler schemaContentHandler;

public:
  /**
   */
  SAXSchemaReader()
  {
    putContentHandler(&schemaContentHandler);
  }


public:
  bool read(_bstr_t xsdFile)
  {
    bool rc = true;
    HRESULT hr = parseURL(xsdFile);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return rc;
  }

public:
  _bstr_t& getTargetNamespace()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::targetNamespace];
  }

public:
  _bstr_t& getVersion()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::version];
  }

public:
  _bstr_t& getXmlns()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::xmlns];
  }

public:
  _bstr_t& getFinalDefault()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::finalDefault];
  }

public:
  _bstr_t& getBlockDefault()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::blockDefault];
  }
public:
  _bstr_t& getId()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::id];
  }

public:
  _bstr_t& getElementFormDefault()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::elementFormDefault];
  }
public:
  _bstr_t& getAttributeFormDefault()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::attributeFormDefault];
  }

public:
  _bstr_t& getXmlLang()
  {
    return  schemaContentHandler.values[SAXSchemaContentHandler::xml_lang];
  }

public:
  void display()
  {
    _tprintf(_T("<SAXSchemaReader>\n"));
    
    _tprintf(_T(
"<schema TargetNamespace=\"%s\" xmlns=\"%s\" version=\"%s\" xmlns=\"%s\"  finalDefault=\"%s\" blockDefault=\"%s\" id=\"%s\" elementFormDefault=\"%s\" attributeFormDefault=\"%s\" xml:lang=\"%s\" />\n"),
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::targetNamespace],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::xmlns],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::version],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::xmlns],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::finalDefault],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::blockDefault],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::id],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::elementFormDefault],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::attributeFormDefault],
      (const TCHAR*)schemaContentHandler.values[SAXSchemaContentHandler::xml_lang]);
    _tprintf(_T("</SAXSchemaReader>\n"));
  }

};

}


