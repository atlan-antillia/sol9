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
 *  XMLDOMParseErrorCollection.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/23 Base class for XMLSomthing classes

#pragma once
#include <sol/xml/XMLObject.h>

namespace SOL {

class XMLDOMParseErrorCollection : public XMLObject {
private:

  MSXML2::IXMLDOMParseErrorCollectionPtr pCollection;

public:
  XMLDOMParseErrorCollection(MSXML2::IXMLDOMParseErrorCollectionPtr collection)
  :pCollection(collection)
  {
  }
public:
  MSXML2::IXMLDOMParseErrorCollectionPtr getCollectionPtr ()
  {
    return pCollection;
  }

public:
  IXMLDOMParseError2Ptr getItem (long index )
  {
    return getCollectionPtr()->Getitem (
        index );
  }

  long getLength ( )
  {
    return getCollectionPtr()->Getlength ();
  }
  
  IXMLDOMParseError2Ptr getNext ( )
  {
    return getCollectionPtr()->Getnext ();
  }
  
  HRESULT reset ( )
  {
    return getCollectionPtr()->reset ( );
  }
  
  IUnknownPtr getNewEnum ( )
  {
    return getCollectionPtr()->Get_newEnum ( )
  }

};


}
