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
 *  SchemaType.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaItem.h>
#include <sol/xml/SchemaStringCollection.h>
#include <sol/xml/SchemaConstant.h>

namespace SOL {

class SchemaType : public SchemaItem {

public:
  SchemaType(MSXML2::ISchemaTypePtr pType)
  :SchemaItem((MSXML2::ISchemaItemPtr)pType)
  {

  }

public:
  MSXML2::ISchemaTypePtr getTypePtr()
  {
    return(MSXML2::ISchemaTypePtr)SchemaItem::getItemPtr();
  }

public:

  MSXML2::ISchemaItemCollectionPtr getBaseTypes()
  {
    return getTypePtr()->GetbaseTypes();
  }

  SCHEMADERIVATIONMETHOD getFinal()
  {
    return getTypePtr()->Getfinal();
  }

  SCHEMATYPEVARIETY getVariety()
  {
    return getTypePtr()->Getvariety();
  }

  SCHEMADERIVATIONMETHOD getDerivedBy()
  {
    return getTypePtr()->GetderivedBy();
  }

  VARIANT_BOOL isValid(_bstr_t data)
  {
    return getTypePtr()->isValid(data);
  }

  _bstr_t getMinExclusive()
  {
    return getTypePtr()->GetminExclusive();
  }
    
  _bstr_t getMinInclusive()
  {
    return getTypePtr()->GetminInclusive();
  }
     
  _bstr_t getMaxExclusive()
  {
    return getTypePtr()->GetmaxExclusive();
  }
    
  _bstr_t getMaxInclusive()
  {
    return getTypePtr()->GetmaxInclusive();
  }
    
  _variant_t getTotalDigits()
  {
    return getTypePtr()->GettotalDigits();
  }
    
  _variant_t getFractionDigits()
  {
    return getTypePtr()->GetfractionDigits();
  }
    
  _variant_t getLength()
  {
    return getTypePtr()->Getlength();
  }
    
  _variant_t getMinLength()
  {
    return getTypePtr()->GetminLength();
  }
    
  _variant_t getMaxLength()
  {
    return getTypePtr()->GetmaxLength();
  }
    
  MSXML2::ISchemaStringCollectionPtr getEnumeration()
  {
    return getTypePtr()->Getenumeration();
  }
    
  SCHEMAWHITESPACE getWhitespace()
  {
    return getTypePtr()->Getwhitespace();
  }
    
  MSXML2::ISchemaStringCollectionPtr getPatterns()
  {
    return getTypePtr()->Getpatterns();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    if (name == NULL) {
      name = _T("SchemaType");
    }
    _tprintf(_T("<%s>\n"), name);
      
    SchemaItem::display();

    try {
      _tprintf(_T("<MinExclusive>%s</MinExclusive>\n"), (const TCHAR*)getMinExclusive());
      _tprintf(_T("<MinInclusive>%s</MinInclusive>\n"), (const TCHAR*)getMinInclusive());
      _tprintf(_T("<MaxExclusive>%s</MaxExclusive>\n"), (const TCHAR*)getMaxExclusive());
      _tprintf(_T("<MaxInclusive>%s</MaxInclusive>\n"), (const TCHAR*)getMaxInclusive());

      try {  
        SchemaItemCollection baseTypes = getBaseTypes();
        baseTypes.display(_T("BaseTypes"));
      } catch (...) {
      }

      try {
        SchemaStringCollection strings =  getEnumeration();
        strings.display(_T("Enumeration"));
      } catch (...) {
      }

      try {
        SchemaStringCollection strings =  getPatterns();
        strings.display(_T("Patterns"));
      } catch (...) {
      }
        
      SchemaConstant constant;
      try {
        _tprintf(_T("<Final>%s</Final>\n"), constant.getDerivationMethod(getFinal()) );
      } catch (...) {
      }

      try {
        _tprintf(_T("<Variety>%s</Variety>\n"), constant.getTypeVariety(getVariety()));
      } catch (...) {
      }

    try {
        _tprintf(_T("<DerivedBy>%s</DerivedBy>\n"), constant.getDerivationMethod(getDerivedBy()));
      } catch (...) {
      }

    } catch (...) {
    }
    _tprintf(_T("</%s>\n"), name);
  }
};


}
