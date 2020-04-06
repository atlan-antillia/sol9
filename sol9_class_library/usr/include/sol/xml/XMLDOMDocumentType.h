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
 *  XMLDOMDocumentType.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once
#include <sol/xml/XMLDOMNode.h>

namespace SOL {

class XMLDOMDocumentType : public XMLDOMNode {
public:
  XMLDOMDocumentType(MSXML2::IXMLDOMDocumentTypePtr pType)
    :XMLDOMNode((MSXML2::IXMLDOMNodePtr)pType)
  {
  }

public:
  MSXML2::IXMLDOMDocumentTypePtr getTypePtr()
  {
    return(MSXML2::IXMLDOMDocumentTypePtr)XMLDOMNode::getNodePtr();
  }

  _bstr_t getName()
  {
    return getTypePtr()->Getname();
  }

  
  MSXML2::IXMLDOMNamedNodeMapPtr getEntities()
  {
    return getTypePtr()->Getentities();
  }

  MSXML2::IXMLDOMNamedNodeMapPtr getNotations()
  {
    return getTypePtr()->Getnotations();
  }

};

}
