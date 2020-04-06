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
 *  SchemaAttribute.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaItem.h>
#include <sol/xml/SOMItemType.h>

namespace SOL {

class SchemaAttribute : public SchemaItem
{
public:
  SchemaSchemaAttribute(MSXML2::ISchemaAttributePtr pAttr)
  :SchemaItem((MSXML2::ISchemaItemPtr)pAttr)
  {
  }
public:
  MSXML2::ISchemaAttributePtr getAttributePtr()
  {
    return(MSXML2::ISchemaAttributePtr)SchemaItem::getItemPtr();
  }
    
  MSXML2::ISchemaTypePtr getType()
  {
    return getAttributePtr()->Gettype();
  }
    
  MSXML2::ISchemaComplexTypePtr getScope()
  {
    return getAttributePtr()->Getscope();
  }
    
  _bstr_t getDefaultValue()
  {
    return getAttributePtr()->GetdefaultValue ();
  }
    
  _bstr_t getFixedValue()
  {
    return getAttributePtr()->GetfixedValue();
  }
    
  SCHEMAUSE getUse()
  {
    return getAttributePtr()->Getuse();
  }
    
  VARIANT_BOOL getIsReference()
  {
    return getAttributePtr()->GetisReference();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    if (name == NULL) {
      name = _T("SchemaAttribute");
    }
    _tprintf(_T("<%s>\n"), name);
    SchemaItem::display();

    SOMItemType type;
    try {
      _tprintf(_T("<Use>%s<\Use>\n"), type.getType(getUse()));
    } catch (...) {
    }

    try {
      SchemaType type = getType();
      type.display(_T("Type"));
    } catch (...) {
    }
    try {
      SchemaComplexType ctype = getScope();
      ctype.display(_T("Scope"));
    } catch (...) {
    }
    try {
      _bstr_t defValue = getDefaultValue();
      _tprintf(_T("<DefaultValue>%s</DefaultValue>\n"), (const TCHAR*)defValue);
    } catch (...) {
    }

    try {
    _bstr_t fixedValue = getFixedValue();
      _tprintf(_T("<FixedValue>%s</FixedValue>\n"), (const TCHAR*)fixedValue);
    } catch (...) {
    }      
    _tprintf(_T("</%s>\n"), name);

  }

};


}
