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
 *  XMLDOMElement.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLDOMNode.h>
#include <sol/xml/XMLDOMParseError.h>

namespace SOL {

class XMLDOMElement : public XMLDOMNode {
public:
  XMLDOMElement(MSXML2::IXMLDOMElementPtr pElement=NULL)
    :XMLDOMNode((MSXML2::IXMLDOMNodePtr)pElement)
  {
  }

public:
  MSXML2::IXMLDOMElementPtr getElementPtr()
  {
    return(MSXML2::IXMLDOMElementPtr)XMLDOMNode::getNodePtr();
  }

  _bstr_t GettagName()
  {
    return getElementPtr()->GettagName();
  }

  _variant_t getAttribute(_bstr_t name)
  {
    return getElementPtr()->getAttribute(name);
  }

  HRESULT setAttribute(_bstr_t name, const _variant_t & value)
  {
    return getElementPtr()->setAttribute(name, value);
  }

  HRESULT removeAttribute(_bstr_t name)
  {
    return getElementPtr()->removeAttribute(name);
  }

  MSXML2::IXMLDOMAttributePtr getAttributeNode(_bstr_t name)
  {
    return getElementPtr()->getAttributeNode(name);
  }

  MSXML2::IXMLDOMAttributePtr setAttributeNode(struct MSXML2::IXMLDOMAttribute * attribute)
  {
    return getElementPtr()->setAttributeNode(attribute);
  }

  MSXML2::IXMLDOMAttributePtr removeAttributeNode(struct MSXML2::IXMLDOMAttribute * attribute)
  {
    return getElementPtr()->removeAttributeNode(attribute );
  }

  MSXML2::IXMLDOMNodeListPtr getElementsByTagName(_bstr_t tagName)
  {
    return getElementPtr()->getElementsByTagName(tagName);
  }

  HRESULT normalize()
  {
    return getElementPtr()->normalize();
  }

};

}
