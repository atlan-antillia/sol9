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
 *  Schema.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaItem.h>
#include <sol/xml/SchemaItemCollection.h>
#include <sol/xml/SchemaStringCollection.h>

namespace SOL {

class Schema : public SchemaItem {

public:
  Schema(MSXML2::ISchemaPtr pSchema)
  :SchemaItem((MSXML2::ISchemaItemPtr)pSchema)
  {

  }

public:
  MSXML2::ISchemaPtr getSchemaPtr()
  {
    return(MSXML2::ISchemaPtr)SchemaItem::getItemPtr();
  }

public:
  _bstr_t getTargetNamespace()
  {
    return getSchemaPtr()->GettargetNamespace();
  }

  _bstr_t getVersion()
  {
    return getSchemaPtr()->Getversion();
  }
    
  MSXML2::ISchemaItemCollectionPtr getTypes()
  {
    return getSchemaPtr()->Gettypes();
  }
    
  MSXML2::ISchemaItemCollectionPtr getElements()
  {
    return getSchemaPtr()->Getelements();
  }
    
  MSXML2::ISchemaItemCollectionPtr getAttributes()
  {
    return getSchemaPtr()->Getattributes();
  }
    
  MSXML2::ISchemaItemCollectionPtr getAttributeGroups()
  {
    return getSchemaPtr()->GetattributeGroups();
  }
    
  MSXML2::ISchemaItemCollectionPtr getModelGroups()
  {
    return getSchemaPtr()->GetmodelGroups();
  }
    
  MSXML2::ISchemaItemCollectionPtr getNotations()
  {
    return getSchemaPtr()->Getnotations();
  }
    
  MSXML2::ISchemaStringCollectionPtr getSchemaLocations()
  {
    return getSchemaPtr()->GetschemaLocations();
  }

public:
  void display()
  {
    printf("<Schema>\n");
    try {
    _tprintf(_T("<Namespace>%s<Namespace>\n"), (const TCHAR*)getTargetNamespace()); //Modified 2016/09/20
    } catch (...) {
    }

    try {
    _tprintf(_T("<Version>%s</Version>\n"), (const TCHAR*)getVersion() );
    } catch (...) {
    }

    try {
      SchemaItemCollection types = getTypes();
      types.display(_T("Types"));
    } catch (...) {
    }

    try {
      SchemaItemCollection elements = getElements();
      elements.display(_T("Elements"));
    } catch (...) {
    }

    try {
      SchemaItemCollection attr = getAttributes();
      attr.display(_T("Attributes"));
    } catch (...) {
    }

    try {
      SchemaItemCollection attrGroups = getAttributeGroups();
      attrGroups.display(_T("AttributesGroups"));
    } catch (...) {
    }

    try {
      SchemaItemCollection modelGroups = getModelGroups();
      modelGroups.display(_T("ModelGroups"));
    } catch (...) {
    }

    try {
      SchemaItemCollection notations = getNotations();
      notations.display(_T("Notations"));
    } catch (...) {
    }
    try {
      SchemaStringCollection locations =  getSchemaLocations();
      locations.display(_T("Locations"));
    } catch (...) {
    }
    printf("</Schema>\n");

  }


};

}

