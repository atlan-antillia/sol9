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
 *  SchemaElement.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaParticle.h>
#include <sol/xml/SchemaType.h>
#include <sol/xml/SchemaComplexType.h>
#include <sol/xml/SchemaConstant.h>


namespace SOL {

class SchemaElement : public SchemaParticle
{
public:
  SchemaElement(MSXML2::ISchemaElementPtr pElement)
  :SchemaParticle((MSXML2::ISchemaParticlePtr)pElement)
  {

  }

public:
  MSXML2::ISchemaElementPtr getElementPtr()
  {
    return(MSXML2::ISchemaElementPtr)SchemaParticle::getParticlePtr();
  }

  MSXML2::ISchemaTypePtr getType()
  {
    return getElementPtr()->Gettype();
  }

  MSXML2::ISchemaComplexTypePtr getScope()
  {
    return getElementPtr()->Getscope();
  }

  _bstr_t getDefaultValue()
  {
    return getElementPtr()->GetdefaultValue();
  }
/*
  _bstr_t getFixedValue()
  {
    return getElementPtr()-GetfixedValue();
  }
*/
  VARIANT_BOOL getIsNillable()
  {
    return getElementPtr()->GetisNillable();
  }

  MSXML2::ISchemaItemCollectionPtr getIdentityConstraints()
  {
    return getElementPtr()->GetidentityConstraints();
  }

  MSXML2::ISchemaElementPtr getSubstitutionGroup()
  {
    return getElementPtr()->GetsubstitutionGroup();
  }

  SCHEMADERIVATIONMETHOD getSubstitutionGroupExclusions()
  {
    return getElementPtr()->GetsubstitutionGroupExclusions();
  }

  SCHEMADERIVATIONMETHOD getDisallowedSubstitutions()
  {
    return getElementPtr()->GetdisallowedSubstitutions();
  }

  VARIANT_BOOL getIsAbstract()
  {
    return getElementPtr()->GetisAbstract();
  }

  VARIANT_BOOL getIsReference()
  {
    return getElementPtr()->GetisReference();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    if (name==NULL) {
      name = _T("SchemaElement");
    }
    _tprintf(_T("<%s>\n"), name);

    SchemaParticle::display();

    try {
      _tprintf(_T("<DefaultValue>%s</DefaultValue>\n"),  (const TCHAR*)getDefaultValue() );
      _tprintf(_T("<IsNillable>%d</IsNillable>\n"),  getIsNillable());
      _tprintf(_T("<IsAbstract>%d</IsAbstract>\n"),  getIsAbstract());
      _tprintf(_T("<IsReference>%d</IsReference>\n"),  getIsReference());

      SchemaConstant constant;
      try {
        _tprintf(_T("<SubstitutionGroupExclusions>%s</SubstitutionGroupExclusions>\n"),
          constant.getDerivationMethod(getSubstitutionGroupExclusions()) );
      } catch (...) {
      }

      try {
        _tprintf(_T("<DisallowedSubstitutions>%s</DisallowedSubstitutions>\n"),
          constant.getDerivationMethod(getDisallowedSubstitutions()) );
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
        SchemaItemCollection constraints = getIdentityConstraints();
        constraints.display(_T("IdentityConstraints"));
      } catch (...) {
      }

      try {
        SchemaElement subsGroup = getSubstitutionGroup();
        subsGroup.display(_T("SubstitutionGroup"));
      } catch (...) {
      }
    } catch (...) {

    }
    _tprintf(_T("</%s>\n"), name);
  }

};

}
