/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  XMLDOMDocument.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
// 2011/02/06 Added  XMLDOMDocument(const GUID clsId)
// 2015/12/19 Modified XMLDOMDocument constructor.

#pragma once

#include <sol/xml/XMLDOMAttribute.h>

#include <sol/xml/XMLDOMAttributes.h>
#include <sol/xml/XMLDOMCDATASection.h>
#include <sol/xml/XMLDOMCharacterData.h>
#include <sol/xml/XMLDOMComment.h>
#include <sol/xml/XMLDOMDocumentFragment.h>
#include <sol/xml/XMLDOMDocumentType.h>
#include <sol/xml/XMLDOMElement.h>
#include <sol/xml/XMLDOMEntity.h>
#include <sol/xml/XMLDOMEntityReference.h>
#include <sol/xml/XMLDOMImplementation.h>
#include <sol/xml/XMLDOMNamedNodeMap.h>
#include <sol/xml/XMLDOMNode.h>
#include <sol/xml/XMLDOMNodeList.h>
#include <sol/xml/XMLDOMNotation.h>
#include <sol/xml/XMLDOMParseError.h>
#include <sol/xml/XMLDOMProcessingInstruction.h>
#include <sol/xml/XMLDOMSchemaCollection.h>
#include <sol/xml/XMLDOMText.h>


namespace SOL {

class XMLDOMDocument : public XMLDOMNode {

public:
  /**
   * Constructor
   */
  XMLDOMDocument(
#ifdef XML4
          const GUID clsId = __uuidof(MSXML2::DOMDocument40) )
#endif
#ifdef XML6
          const GUID clsId = __uuidof(MSXML2::DOMDocument60) )
#endif
  :XMLDOMNode(NULL)
  {
    MSXML2::IXMLDOMDocument2Ptr pDocument;

    HRESULT hr = pDocument.CreateInstance(clsId);

    if(FAILED(hr)) {
          throw Exception("Failed to create an instance of XMLDOMDocument\n", hr);
    }

    hr = pDocument->setProperty(_bstr_t("SelectionLanguage"), variant_t(L"XPath"));
    if(FAILED(hr)) {
      pDocument = NULL;
      throw Exception("Failed to setProperty for SelectionLanguage\n", hr);
    }

    set((MSXML2::IXMLDOMNodePtr)pDocument);
  }


public:
  /**
   * Destructor
   */
  ~XMLDOMDocument()
  {
    //
  }


public:
  virtual MSXML2::IXMLDOMDocument2Ptr getDocumentPtr()
  {
    return(MSXML2::IXMLDOMDocument2Ptr)XMLDOMNode::getNodePtr();
  }

public:
  //2011/02/07
  operator MSXML2::IXMLDOMDocument*()
  {
    return (MSXML2::IXMLDOMDocument*)getDocumentPtr();
  }


public:
  bool setProperty(__in _bstr_t& name, __in _variant_t& value)
  {
    bool rc = false;
    HRESULT  hr = getDocumentPtr()->setProperty(name, value);
    if (FAILED(hr)) {
      throw hr;
    } else {
      rc = true;
    }
    return rc;
  }

public:
  /**
   * Load a text string of a parameter xml and build a XMLDOMDocument object.
   *
   * @param xml  _bstr_t& text string to an XML.
   * @return bool Success or Error
   */
  //bool load(__in const _bstr_t& xml)
  bool loadXML(__in const _bstr_t& xml)
  {  
    bool rc = true;
  
    putAsync(VARIANT_FALSE); // default - true,

    VARIANT_BOOL hr = getDocumentPtr() ->loadXML(xml);
    if (hr != VARIANT_TRUE) {
      throw XMLDOMParseError(getParseError());
    }
    return rc;
  }


public:
  /**
   * Open xml file specified by parameter
   * @filePath  xml file path.
   */
  bool open(__in const TCHAR* filePath) 
  {
    bool rc = true;

    putAsync(VARIANT_FALSE); 
    VARIANT_BOOL hr = getDocumentPtr()->load(_bstr_t(filePath));
  
    if (hr != VARIANT_TRUE){
      throw XMLDOMParseError(getParseError());
    }
    return rc;
  }

public:
  /**
   * Save an xml text of IXMLDOMDocument of xmlDoc to the file of fileName.
   */
  bool save(__in const TCHAR* fileName) 
  {
    bool rc = true;
    if (fileName) {
      _bstr_t bfileName = fileName;
      HRESULT hr = getDocumentPtr()->save(bfileName);
      if (FAILED(hr)) {
        throw hr;
      }
    }
    return rc;
  }

//<IXMDOMDocument>

public:
  MSXML2::IXMLDOMDocumentTypePtr getDoctype()
  {
    return getDocumentPtr()-> Getdoctype();
  }


  MSXML2::IXMLDOMImplementationPtr getImplementation()
  {
    return getDocumentPtr()-> Getimplementation();
  }


  MSXML2::IXMLDOMElementPtr getDocumentElement()
  {
    return getDocumentPtr()-> GetdocumentElement();
  }


  void putRefdocumentElement(struct MSXML2::IXMLDOMElement * DOMElement)
  {
    getDocumentPtr()-> PutRefdocumentElement(DOMElement);
  }


  MSXML2::IXMLDOMElementPtr createElement(_bstr_t tagName)
  {
    return getDocumentPtr()-> createElement(tagName);
  }

  MSXML2::IXMLDOMDocumentFragmentPtr createDocumentFragment()
  {
    return getDocumentPtr()-> createDocumentFragment();
  }

  MSXML2::IXMLDOMTextPtr createTextNode(_bstr_t data)
  {
    return getDocumentPtr()-> createTextNode(data);
  }

  MSXML2::IXMLDOMCommentPtr createComment(_bstr_t data)
  {
    return getDocumentPtr()-> createComment(data);
  }

  MSXML2::IXMLDOMCDATASectionPtr createCDATASection(_bstr_t data)
  {
    return getDocumentPtr()-> createCDATASection(data);
  }

  MSXML2::IXMLDOMProcessingInstructionPtr createProcessingInstruction(_bstr_t target, _bstr_t data)
  {
    return getDocumentPtr()-> createProcessingInstruction(target, data);
  }

  MSXML2::IXMLDOMAttributePtr createAttribute(_bstr_t name)
  {
    return getDocumentPtr()-> createAttribute(name);
  }

  MSXML2::IXMLDOMEntityReferencePtr createEntityReference(_bstr_t name)
  {
    return getDocumentPtr()-> createEntityReference(name);
  }

  MSXML2::IXMLDOMNodeListPtr getElementsByTagName(_bstr_t tagName)
  {
    return getDocumentPtr()-> getElementsByTagName( tagName);
  }

  MSXML2::IXMLDOMNodePtr createNode(const _variant_t & type, _bstr_t name, _bstr_t namespaceURI)
  {
    return getDocumentPtr()-> createNode(type, name, namespaceURI);
  }

  MSXML2::IXMLDOMNodePtr nodeFromID(_bstr_t idString)
  {
    return getDocumentPtr()-> nodeFromID(idString);
  }

  VARIANT_BOOL load(const _variant_t & xmlSource)
  {
    return getDocumentPtr()-> load(xmlSource);
  }

  long getReadyState()
  {
    return getDocumentPtr()-> GetreadyState();
  }

  MSXML2::IXMLDOMParseErrorPtr getParseError()
  {
    return getDocumentPtr()-> GetparseError();
  }

  _bstr_t getUrl()
  {
    return getDocumentPtr()-> Geturl();
  }

  VARIANT_BOOL getAsync()
  {
    return getDocumentPtr()-> Getasync();
  }

  void putAsync(VARIANT_BOOL isAsync)
  {
    return getDocumentPtr()-> Putasync(isAsync);
  }

  HRESULT abort()
  {
    return getDocumentPtr()-> abort();
  }

  HRESULT save(const _variant_t & destination)
  {
    return getDocumentPtr()-> save(destination);
  }

  VARIANT_BOOL getValidateOnParse()
  {
    return getDocumentPtr()-> GetvalidateOnParse();
  }

  void putValidateOnParse(
    VARIANT_BOOL isValidating)
  {
    getDocumentPtr()-> PutvalidateOnParse(isValidating);
  }

  VARIANT_BOOL getResolveExternals()
  {
    return getDocumentPtr()-> GetresolveExternals();
  }

  void putResolveExternals(VARIANT_BOOL isResolving)
  {
    getDocumentPtr()-> PutresolveExternals(isResolving);
  }

  VARIANT_BOOL getPreserveWhiteSpace()
  {
    return getDocumentPtr()-> GetpreserveWhiteSpace();
  }

  void putPreserveWhiteSpace(VARIANT_BOOL isPreserving)
  {
    getDocumentPtr()-> PutpreserveWhiteSpace(isPreserving);
  }

  void putOnReadyStateChange(const _variant_t & _arg1)
  {
    getDocumentPtr()-> Putonreadystatechange(_arg1);
  }

  void putOnDataAvailable(const _variant_t & _arg1)
  {
    getDocumentPtr()-> Putondataavailable(_arg1);
  }
    
  void putOnTransformNode(const _variant_t & _arg1)
  {
    getDocumentPtr()-> Putontransformnode(_arg1);
  }
//</IXMDOMDocument>

//<IXMDOMDocument2>
public:
  MSXML2::IXMLDOMSchemaCollectionPtr getNamespaces()
  {
    return getDocumentPtr() -> Getnamespaces();
  }

  _variant_t getSchemas()
  {
    return getDocumentPtr() -> Getschemas();
  }

  void  putRefschemas(const _variant_t & otherCollection)
  {
    getDocumentPtr() -> PutRefschemas(otherCollection);
  }


  MSXML2::IXMLDOMParseErrorPtr validate()
  {
    return getDocumentPtr() -> validate();
  }


  HRESULT setProperty(_bstr_t name, const _variant_t & value)
  {
    return getDocumentPtr() -> setProperty(name, value);
  }

  _variant_t getProperty(_bstr_t name)
  {
    return getDocumentPtr() -> getProperty(name);
  }
//</IXMDOMDocument2>


//<IXMDOMDocument3>
public:
/*
  MSXML2::IXMLDOMParseErrorPtr validateNode(struct MSXML2::IXMLDOMNode * node)
  {
    return getDocumentPtr()-> validateNode(node);
  }

    
  MSXML2::IXMLDOMNodePtr importNode(struct MSXML2::IXMLDOMNode * node, VARIANT_BOOL deep)
  {
    return getDocumentPtr()-> importNode(node, deep);
  }
*/
//</IXMDOMDocument3>
};

}
