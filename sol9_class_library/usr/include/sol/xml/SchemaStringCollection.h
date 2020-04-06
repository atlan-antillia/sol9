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
 *  SchemaStringCollection.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/XMLObject.h>

namespace SOL {

class SchemaStringCollection : public XMLObject {

private:
  MSXML2::ISchemaStringCollectionPtr pCollection;

public:
  SchemaStringCollection(MSXML2::ISchemaStringCollectionPtr collection)
    :pCollection(collection)
  {
  }

  ~SchemaStringCollection()
  {
    pCollection = NULL;
  }

public:
  MSXML2::ISchemaStringCollectionPtr getCollectionPtr()
  {
    if (pCollection == NULL) {
      throw Exception(E_FATAL, "Error: SchemaStringCollection is NULL");
    }
    return pCollection;
  }

  _bstr_t getItem (long index )
  {
    return getCollectionPtr()->Getitem (index );
  }

  long getLength ( )
  {
    return getCollectionPtr()->Getlength  ();
  }

  IUnknownPtr getNewEnum ( )
  {
    return getCollectionPtr()->Get_newEnum ();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    try {
    long length = getLength();
    if (length>0) {
      if (name == NULL) {
        name = _T("SchemaStringCollection");
      }
      _tprintf(_T("<%s length=\"%d\">\n"), name, length);
      for (long i=0; i<length; i++) {
        _bstr_t item = getItem(i);
        _tprintf(_T("<Item>%s</Item>\n"), (const TCHAR*)item);
      }
      _tprintf(_T("</%s>\n"), name);

    }
    } catch (...) {

    }
  }


};


}
