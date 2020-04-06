/******************************************************************************
 *
 * Copyright (c) 2009-2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  XMLDOMTreeWalker.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/23
// 2011/01/28 Modified to use XMLDOMDocument

#pragma once

#include <sol/xml/XMLDOMDocument.h>


namespace SOL {

class XMLTreeWalker :public XMLDOMDocument {

public:
  /**
   * Constructor
   */
  XMLTreeWalker()
  {  
  }

public:
  /**
   */
  ~XMLTreeWalker() 
  {
  }

public:
  /**
   * Traverse each tree node of XMLDOM node
   */
  virtual void walk() 
  {
    MSXML2::IXMLDOMElementPtr root = getDocumentElement();
    displayChildren(root, 0);
  }


private:
  void displayChildren(MSXML2::IXMLDOMNodePtr pNode, int n)
  {
     // Display the current node's attributes

     displayChild(pNode, n);

     // Walk all children
    MSXML2::IXMLDOMNodePtr pChild = pNode->firstChild;

    for (pChild; NULL != pChild; pChild = pChild->nextSibling) {
        displayChildren(pChild, n+1);
     }

    if ( pNode->nodeType == MSXML2::NODE_ELEMENT) {
      _bstr_t name = pNode->GetnodeName();
      indent(n);
      _tprintf(_T("</%s>\n"), (const TCHAR*)name);
    }
    pChild = NULL;
  }

private:
  void indent(int n) 
  {
    for (int i = 0; i<n; i++) {
      _tprintf(_T(" "));
    }
  }

private:
  void displayChild(MSXML2::IXMLDOMNodePtr pChild, int n)
  {
    if (pChild) {
      _bstr_t name = pChild->GetnodeName();
      indent(n);

       if (pChild->nodeType == MSXML2::NODE_TEXT) {
        _tprintf(_T("%s\n"), (const TCHAR*)pChild->text);

      } else if (pChild->nodeType == MSXML2::NODE_ELEMENT) {  
        _tprintf(_T("<%s"), (const TCHAR*)name);
        displayAttributes(pChild);      
        _tprintf(_T(">\n"));
      }  else {

      }
    }
  }


private:
  void displayAttributes(MSXML2::IXMLDOMNodePtr pNode)
  {
    MSXML2::IXMLDOMNamedNodeMapPtr map = pNode->Getattributes();
    if (map) {
      for (int n = 0; n<map->Getlength(); n++) {
        MSXML2::IXMLDOMNodePtr attr = map->Getitem(n);
        _bstr_t name  = attr->GetnodeName();
        _bstr_t value = attr->GetnodeValue();
        _tprintf(_T(" %s=\"%s\""), (const TCHAR*)name, (const TCHAR*)value);
      }
      map = NULL;
    }
  }
/*
enum tagDOMNodeType
{
    NODE_INVALID = 0,
    NODE_ELEMENT = 1,
    NODE_ATTRIBUTE = 2,
    NODE_TEXT = 3,
    NODE_CDATA_SECTION = 4,
    NODE_ENTITY_REFERENCE = 5,
    NODE_ENTITY = 6,
    NODE_PROCESSING_INSTRUCTION = 7,
    NODE_COMMENT = 8,
    NODE_DOCUMENT = 9,
    NODE_DOCUMENT_TYPE = 10,
    NODE_DOCUMENT_FRAGMENT = 11,
    NODE_NOTATION = 12
};
*/
};

}

