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
 *  HTMLTreeWalker.h
 *
 *****************************************************************************/

// SOL9
// 2012/02/24

#include <sol/COMInitializer.h>
#include <sol/Locale.h>
#include <sol/html/HTMLDocument.h>
#include <sol/html/HTMLElement.h>
#include <sol/html/HTMLDOMNode.h>
#include <sol/Writer.h>

namespace SOL {

class HTMLTreeWalker :public HTMLDocument {

public:
  HTMLTreeWalker()
  {
    createDocument();
  }

public:
  void walk()
  {
    HTMLElement docElement = getDocumentElement();
    HTMLDOMNode domNode = docElement.getDOMNode();
    int n = 0;  
    walk(domNode, n);
  }

public:
  void walk(HTMLDOMNode& domNode, int n)
  {
    _bstr_t name = domNode.getName();
    long nodeType = domNode.getNodeType();

    indent(n);
    domNode.display();

    IHTMLDOMNode* pNode = domNode.getFirstChild();

    while (pNode) {
      try {
        HTMLDOMNode node(pNode);
        walk(node, n+1);
      
        pNode = node.getNextSibling();
      } catch (...) {
        break;
      }
    }
    if (nodeType == HTMLDOMNode::NODE_ELEMENT) {
      indent(n);
      _tprintf(_T("</%s>\n"), (const TCHAR*)name);
    }
  }

private:
  void indent(int n) 
  {
    for (int i = 0; i<n; i++) {
      _tprintf(_T(" "));
    }
  }
};

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


