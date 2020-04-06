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
 *  XMLDOMNodeList.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once
#include <sol/xml/XMLObject.h>
#include <sol/xml/XMLDOMNode.h>

namespace SOL {

class XMLDOMNodeList : public XMLObject{
private:
  MSXML2::IXMLDOMNodeListPtr pNodeList;

public:
  XMLDOMNodeList(MSXML2::IXMLDOMNodeListPtr list=NULL)
    :pNodeList(list)
  {
    //printf("XMLDOMNodeList::XMLDOMNodeList\n");
  }

public:
  ~XMLDOMNodeList()
  {
    pNodeList = NULL;
  }

public:
  MSXML2::IXMLDOMNodeListPtr getNodeList()
  {
    if(pNodeList == NULL) {
      throw Exception(E_FATAL, "Error: XMLDOMNodeListPtr is NULL");
    }
    return pNodeList;
  }

public:
  MSXML2::IXMLDOMNodePtr getItem(long index)
  {
    return getNodeList()->Getitem(index);
  }

  long getLength()
  {
    return getNodeList()->Getlength();
  }

  MSXML2::IXMLDOMNodePtr nextNode()
  {
    return getNodeList()->nextNode();
  }

  HRESULT reset()
  {
    return getNodeList()->reset();
  }

  IUnknownPtr getNewEnum()
  {
    return getNodeList()->Get_newEnum ();

  }
public:
  void dump()
  {
    int len = getLength();
    printf("XMLDOMNodeList::dump() Length = %d\n", len);
    for (int i = 0; i<len; i++) {
      XMLDOMNode node = getItem(i);
      node.dump();
    }
  }
};

}

