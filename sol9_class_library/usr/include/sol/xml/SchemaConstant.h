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
 *  SchemaConstant.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/13
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/ArgListT.h>

namespace SOL {

class SchemaConstant :public Object {

public:
  const TCHAR* getDerivationMethod(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("DerivationMethod_Empty"),  SCHEMADERIVATIONMETHOD_EMPTY},
      {_T("DerivationMethod_Substitution"),SCHEMADERIVATIONMETHOD_SUBSTITUTION},
      {_T("DerivationMethod_Extension"), SCHEMADERIVATIONMETHOD_EXTENSION},
      {_T("DerivationMethod_Restriction"), SCHEMADERIVATIONMETHOD_RESTRICTION},
      {_T("DerivationMethod_List"), SCHEMADERIVATIONMETHOD_LIST},
      {_T("DerivationMethod_Union"), SCHEMADERIVATIONMETHOD_UNION},
      {_T("DerivationMethod_All"), SCHEMADERIVATIONMETHOD_ALL},
      {_T("DerivationMethod_None"), SCHEMADERIVATIONMETHOD_NONE}
      };

    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

  const TCHAR* getTypeVariety(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("TypeVariety_None"),   (LONG_PTR)SCHEMATYPEVARIETY_NONE},
      {_T("TypeVariety_Atomic"), SCHEMATYPEVARIETY_ATOMIC},
      {_T("TypeVariety_List"), SCHEMATYPEVARIETY_LIST},
      {_T("TypeVariety_Union"), SCHEMATYPEVARIETY_UNION}
      };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

  const TCHAR* getWhitespace(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("Whitespace_None"), (LONG_PTR)SCHEMAWHITESPACE_NONE},
      {_T("Whitespace_None"), SCHEMAWHITESPACE_PRESERVE},
      {_T("Whitespace_None"), SCHEMAWHITESPACE_REPLACE},
      {_T("Whitespace_None"), SCHEMAWHITESPACE_COLLAPSE}
      };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

  const TCHAR* getProcessContents(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("ProcessContents_None"), SCHEMAPROCESSCONTENTS_NONE},
      {_T("ProcessContents_Skip"), SCHEMAPROCESSCONTENTS_SKIP},
      {_T("ProcessContents_Lax"), SCHEMAPROCESSCONTENTS_LAX},
      {_T("ProcessContents_Strict"), SCHEMAPROCESSCONTENTS_STRICT}
      };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

  const TCHAR* getContentType(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("ContentType_Empty"), SCHEMACONTENTTYPE_EMPTY},
      {_T("ContentType_TextOnly"), SCHEMACONTENTTYPE_TEXTONLY},
      {_T("ContentType_ElementOnly"), SCHEMACONTENTTYPE_ELEMENTONLY},
      {_T("ContentType_Mixed"), SCHEMACONTENTTYPE_MIXED}
      };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

  const TCHAR* getUse(int value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("Use_Optional"), SCHEMAUSE_OPTIONAL},
      {_T("Use_Prohibited"), SCHEMAUSE_PROHIBITED},
      {_T("Use_Required"), SCHEMAUSE_REQUIRED}
      };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }

};


}
