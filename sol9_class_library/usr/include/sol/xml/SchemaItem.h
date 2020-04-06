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
 *  SchemaItem.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/xml/SOMItemType.h>
//#include <sol/xml/SchemaItemCollection.h>


namespace SOL {

class SchemaItem : public XMLObject 
{
private:
  MSXML2::ISchemaItemPtr pItem;

public:
  SchemaItem(MSXML2::ISchemaItemPtr item)
  :pItem(item)
  {
  }

public:
  ~SchemaItem()
  {
    pItem = NULL;
  }

public:
  MSXML2::ISchemaItemPtr getItemPtr()
  {
    if (pItem == NULL) {
      throw Exception(E_FATAL, "Error: SchemaItem is NULL");
    }
    return pItem;
  }

public:
  _bstr_t getName()
  {
    return getItemPtr()->Getname();
  }

  _bstr_t getNamespaceURI()
  {
    return getItemPtr()->GetnamespaceURI();
  }

  MSXML2::ISchemaPtr getSchema()
  {
    return getItemPtr()->Getschema();
  }

  _bstr_t getId()
  {
    return getItemPtr()->Getid();
  }

  SOMITEMTYPE getItemType()
  {
    return getItemPtr()->GetitemType();
  }

  IVBSAXAttributesPtr getUnhandledAttributes()
  {
    return getItemPtr()->GetunhandledAttributes();
  }

  VARIANT_BOOL writeAnnotation(
    IUnknown * annotationSink)
  {
    return getItemPtr()->writeAnnotation(
      annotationSink);
  }

public:
  void display(const TCHAR* name=NULL)
  {
    if (name ==NULL) {
      name = _T("SchemaItem");
    }
    _tprintf(_T("<%s>\n"), name);

    try {
      SOMItemType type;
      //_tprintf(_T("SchemaItem: Name=%s NamespaceURI=%s Id=%s\n"),
      _tprintf(_T("<%s NamespaceURI=\"%s\" Id=\"%s\" ItemType=\"%s\" />\n"),

      (const TCHAR*)getName(),
      (const TCHAR*)getNamespaceURI(),
      (const TCHAR*)getId(),
      type.getType(getItemType()) );
    } catch (...) {
    }
    _tprintf(_T("</%s>\n"), name);
  }

public:
  void display(MSXML2::ISchemaItemCollectionPtr pCollection, const TCHAR* name)
  {
    try {
      long len = pCollection->Getlength();
      if (len>0) {
        const TCHAR* xname=name;
        if (xname == NULL) {
          xname = _T("SchemaItemCollection");
        }

        _tprintf(_T("<%s length=\"%d\">\n"), xname, len);
        for (long i = 0; i<len; i++) {
          try {
            SchemaItem item = pCollection->Getitem(i);
            item.display();
          } catch (...) {
          }
        }
        _tprintf(_T("</%s>\n"), xname);
      }

    } catch (...) {
    }
  }

};

}

