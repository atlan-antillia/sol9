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
 *  XMLDOMNamedNodeMap.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>

namespace SOL {

class XMLDOMNamedNodeMap : public XMLObject {
private:
  MSXML2::IXMLDOMNamedNodeMapPtr pMap;

public:
  XMLDOMNamedNodeMap(MSXML2::IXMLDOMNamedNodeMapPtr map=NULL)
    :pMap(map)
  {
  }

public:
  ~XMLDOMNamedNodeMap()
  {
    pMap = NULL;
  }

public:
  MSXML2::IXMLDOMNamedNodeMapPtr getMapPtr()
  {
    if(pMap == NULL) {
      throw Exception(E_FATAL, "Error: XMLDOMNamedNodeMapPtr is NULL");
    }

    return pMap;
  }

  MSXML2::IXMLDOMNodePtr getNamedItem(_bstr_t name)
  {
    return getMapPtr()->getNamedItem(name);
  }

  MSXML2::IXMLDOMNodePtr setNamedItem(struct MSXML2::IXMLDOMNode * newItem)
  {
    return getMapPtr()->setNamedItem(newItem);
  }
    
  MSXML2::IXMLDOMNodePtr removeNamedItem(_bstr_t name)
  {
    return getMapPtr()->removeNamedItem(name);
  }
    
  MSXML2::IXMLDOMNodePtr getItem(long index)
  {
    return getMapPtr()->Getitem(index);
  }
    
  long getLength()
  {
    return getMapPtr()->Getlength();
  }
    
  MSXML2::IXMLDOMNodePtr getQualifiedItem(_bstr_t baseName, _bstr_t namespaceURI)
  {
    return getMapPtr()->getQualifiedItem(baseName , namespaceURI);
  }
    
  MSXML2::IXMLDOMNodePtr removeQualifiedItem(_bstr_t baseName, _bstr_t namespaceURI)
  {
    return getMapPtr()->removeQualifiedItem(baseName , namespaceURI);
  }
    
  MSXML2::IXMLDOMNodePtr nextNode()
  {
    return getMapPtr()->nextNode();
  }
    
  HRESULT reset()
  {
    return getMapPtr()->reset();
  }
    
  IUnknownPtr getNewEnum()
  {
    return getMapPtr()->Get_newEnum();
  }

};

}
