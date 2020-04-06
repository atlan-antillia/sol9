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
 *  XMLDOMNode.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once
#include <sol/xml/XMLObject.h>

namespace SOL {

class XMLDOMNode : public XMLObject {
private:
  MSXML2::IXMLDOMNodePtr pNode;

public:
  XMLDOMNode(MSXML2::IXMLDOMNodePtr aNode=NULL)
    :pNode(aNode)
  {
    //printf("XMLDOMNode::XMLDOMNode\n");
  }

public:
  void set(__in MSXML2::IXMLDOMNodePtr aNode)
  {
    this->pNode = aNode;
  }


public:
  MSXML2::IXMLDOMNodePtr getNodePtr()
  {
    if(pNode == NULL) {
      throw Exception(E_FATAL, "Error: XMLDOMNodePtr is NULL");
    }
    return pNode;
  }

public:
  //2011/02/07
  operator MSXML2::IXMLDOMNode*()
  {
    return (MSXML2::IXMLDOMNode*)pNode;
  }

public:
  //2011/02/07
  operator IUnknown*()
  {
    return (IUnknown*)pNode;
  }

public:
  _bstr_t getNodeName()
  {
    return getNodePtr() -> GetnodeName();
  }

  _variant_t getNodeValue()
  {
    return getNodePtr() -> GetnodeValue();
  }


  void putNodeValue(const _variant_t & value)
  {
    getNodePtr() -> PutnodeValue(value);
  }

  MSXML2::DOMNodeType getNodeType()
  {
    return getNodePtr() -> GetnodeType();
  }


  MSXML2::IXMLDOMNodePtr getParentNode()
  {
    return getNodePtr() -> GetparentNode();
  }

  MSXML2::IXMLDOMNodeListPtr getChildNodes()
  {
    return getNodePtr() -> GetchildNodes();
  }

  MSXML2::IXMLDOMNodePtr getFirstChild()
  {
    return getNodePtr() -> GetfirstChild();
  }

  MSXML2::IXMLDOMNodePtr getLastChild()
  {
    return getNodePtr() -> GetlastChild();
  }

  MSXML2::IXMLDOMNodePtr getPreviousSibling()
  {
    return getNodePtr() -> GetpreviousSibling();
  }

  MSXML2::IXMLDOMNodePtr getNextSibling()
  {
    return getNodePtr() -> GetnextSibling();
  }

  MSXML2::IXMLDOMNamedNodeMapPtr getAttributes()
  {
    return getNodePtr() -> Getattributes();
  }

  MSXML2::IXMLDOMNodePtr insertBefore(struct MSXML2::IXMLDOMNode * newChild, const _variant_t & refChild)
  {
    return getNodePtr() -> insertBefore(newChild, refChild);
  }

  MSXML2::IXMLDOMNodePtr replaceChild(struct MSXML2::IXMLDOMNode * newChild, struct MSXML2::IXMLDOMNode * oldChild)
  {
    return getNodePtr() -> replaceChild(newChild, oldChild);
  }

  MSXML2::IXMLDOMNodePtr removeChild(struct MSXML2::IXMLDOMNode * childNode)
  {
    return getNodePtr() -> removeChild(childNode);
  }

  MSXML2::IXMLDOMNodePtr appendChild(struct MSXML2::IXMLDOMNode * newChild)
  {
    return getNodePtr() -> appendChild( newChild);
  }

  VARIANT_BOOL hasChildNodes()
  {
    return getNodePtr() -> hasChildNodes();
  }

  MSXML2::IXMLDOMDocumentPtr getOwnerDocument()
  {
    return getNodePtr() -> GetownerDocument();
  }
  
  MSXML2::IXMLDOMNodePtr cloneNode(VARIANT_BOOL deep)
  {
    return getNodePtr() -> cloneNode(deep);
  }

  _bstr_t getNodeTypeString()
  {
    return getNodePtr() -> GetnodeTypeString();
  }

  _bstr_t getText()
  {
    return getNodePtr() -> Gettext();
  }

  void putText(_bstr_t text)
  {
    getNodePtr() -> Puttext(text);
  }

  VARIANT_BOOL getSpecified()
  {
    return getNodePtr() -> Getspecified();
  }

  MSXML2::IXMLDOMNodePtr getDefinition()
  {
    return getNodePtr() -> Getdefinition();
  }

  _variant_t getNodeTypedValue()
  {
    return getNodePtr() -> GetnodeTypedValue();
  }

  void putNodeTypedValue( const _variant_t & typedValue)
  {
    return getNodePtr() -> PutnodeTypedValue(typedValue);
  }

  _variant_t getDataType()
  {
    return getNodePtr() -> GetdataType();
  }

  void putDataType(_bstr_t dataTypeName)
  {
    getNodePtr() -> PutdataType(dataTypeName);
  }

  _bstr_t getXML()
  {
    return getNodePtr() -> Getxml();
  }

  _bstr_t transformNode(struct MSXML2::IXMLDOMNode * stylesheet)
  {
    return getNodePtr() -> transformNode(stylesheet);
  }

  MSXML2::IXMLDOMNodeListPtr selectNodes(_bstr_t queryString)
  {
    return getNodePtr() -> selectNodes(queryString);
  }

  MSXML2::IXMLDOMNodePtr selectSingleNode(_bstr_t queryString)
  {
    return getNodePtr() -> selectSingleNode(queryString);
  }

  VARIANT_BOOL getParsed()
  {
    return getNodePtr() -> Getparsed();
  }

  _bstr_t getNamespaceURI()
  {
    return getNodePtr() -> GetnamespaceURI();
  }

  _bstr_t getPrefix()
  {
    return getNodePtr() -> Getprefix();
  }

  _bstr_t getBaseName()
  {
    return getNodePtr() -> GetbaseName();
  }

  HRESULT transformNodeToObject(struct MSXML2::IXMLDOMNode * stylesheet, const _variant_t & outputObject)
  {
    return getNodePtr() -> transformNodeToObject(stylesheet, outputObject);
  }

public:
  void dump()
  {
    MSXML2::IXMLDOMNodePtr pNode = getNodePtr();

    if (pNode) {
      _bstr_t name = getNodeName();

      _tprintf(_T("<%s"), (const TCHAR*)name);

      MSXML2::IXMLDOMNamedNodeMapPtr map = pNode->Getattributes();
      if (map) {
        for (int n = 0; n<map->Getlength(); n++) {
          MSXML2::IXMLDOMNodePtr aNode = map->Getitem(n);
          _bstr_t name  = aNode->GetnodeName();
          _bstr_t value = aNode->GetnodeValue();
          _tprintf(_T(" %s=\"%s\""), (const TCHAR*)name, (const TCHAR*)value);
        }
        //map = NULL;
      }
      _tprintf(_T(">\n"));
    }
  }
};

}
