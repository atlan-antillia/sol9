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
 *  SchemaComplexType.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaType.h>
#include <sol/xml/SchemaItemCollection.h>
#include <sol/xml/SchemaAny.h>
#include <sol/xml/SchemaModelGroup.h>
#include <sol/xml/SchemaConstant.h>
#include <sol/xml/SOMItemType.h>
#include <sol/xml/SchemaConstant.h>

namespace SOL {

class SchemaComplexType : public SchemaType
{
public:
  SchemaComplexType(MSXML2::ISchemaComplexTypePtr pType)
  :SchemaType((MSXML2::ISchemaTypePtr)pType)
  {
  }

public:
  MSXML2::ISchemaComplexTypePtr getTypePtr()
  {
    return(MSXML2::ISchemaComplexTypePtr)SchemaType::getTypePtr();
  }

  VARIANT_BOOL getIsAbstract()
  {
    return getTypePtr()->GetisAbstract();
  }

  MSXML2::ISchemaAnyPtr getAnyAttribute()
  {
    return getTypePtr()->GetanyAttribute();
  }

  MSXML2::ISchemaItemCollectionPtr getAttributes()
  {
    return getTypePtr()->Getattributes();
  }

  SCHEMACONTENTTYPE getContentType()
  {
    return getTypePtr()->GetcontentType();
  }

  MSXML2::ISchemaModelGroupPtr getContentModel()
  {
    return getTypePtr()->GetcontentModel();
  }

  SCHEMADERIVATIONMETHOD getProhibitedSubstitutions()
  {
    return getTypePtr()->GetprohibitedSubstitutions();
  }
public:
  void display(const TCHAR* name)
  {
    if (name == NULL) {
      name = _T("SchemaComplexType");
    }
    _tprintf(_T("<%s>\n"), name);
    try {
      SchemaItemCollection pCollection = getAttributes();
      pCollection.display(_T("Attributes"));
    } catch (...) {
    }

    try {
      SchemaAny any = getAnyAttribute();
      any.display();
    } catch (...) {
    }

    try {
      SchemaModelGroup group = getContentModel();
      group.display(_T("ContentModel"));
    } catch (...) {
    }

    SOMItemType type;
    try {
      _tprintf(_T("<CotentType>%s</CotentType>\n"),
        type.getType(getContentType()));
    } catch (...) {
    }

    SchemaConstant constant;
    try {
      _tprintf(_T("<ProhibitedSubstitutions>%s</ProhibitedSubstitutions>\n"),
        constant.getDerivationMethod(getProhibitedSubstitutions()));
    } catch (...) {
    }

    _tprintf(_T("</%s>\n"), name);
  }

};


}
