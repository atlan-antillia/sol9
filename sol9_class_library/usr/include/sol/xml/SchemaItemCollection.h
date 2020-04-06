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
 *  SchemaItemCollection.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/xml/SchemaItem.h>

namespace SOL {

class SchemaItemCollection : public XMLObject {
private:
  MSXML2::ISchemaItemCollectionPtr pCollection;

public:
  SchemaItemCollection(MSXML2::ISchemaItemCollectionPtr collection)
  :pCollection(collection)
  {
  }

public:
  MSXML2::ISchemaItemCollectionPtr getCollectionPtr()
  {
    if (pCollection==NULL) {
      throw Exception(E_FATAL, "Error: SchemaItemCollection is NULL");
    }
    return pCollection;
  }


public:
  MSXML2::ISchemaItemPtr getItem(long index)
  {
    return getCollectionPtr()->Getitem(index);
  }

  MSXML2::ISchemaItemPtr itemByName(_bstr_t name)
  {
    return getCollectionPtr()->itemByName(name);
  }
    
  MSXML2::ISchemaItemPtr itemByQName(_bstr_t name,_bstr_t namespaceURI)
  {
    return getCollectionPtr()->itemByQName(name, namespaceURI);
  }
    
  long getLength()
  {
    return getCollectionPtr()->Getlength();
  }
    
  IUnknownPtr getNewEnum()
  {
    return getCollectionPtr()->Get_newEnum();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    try {
      long len = getLength();
      if (len>0) {
        if (name == NULL) {
          name = _T("SchemaItemCollection");
        }

        _tprintf(_T("<%s length=\"%d\">\n"), name, len);
        for (long i = 0; i<len; i++) {
          try {
            SchemaItem item = getItem(i);
            item.display();
          } catch (...) {
          }
        }
        _tprintf(_T("</%s>\n"), name);
      }

    } catch (...) {
    }
  }

};


}
