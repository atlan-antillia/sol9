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

#include <sol/xml/SchemaParticle.h>
#include <sol/xml/SchemaStringCollection.h>

namespace SOL {

class SchemaAny : public SchemaParticle {

public:
  SchemaAny(MSXML2::ISchemaAnyPtr pAny)
  :SchemaParticle((MSXML2::ISchemaParticlePtr)pAny)
  {

  }

public:
  MSXML2::ISchemaAnyPtr getAnyPtr()
  {
    return(MSXML2::ISchemaAnyPtr)SchemaParticle::getParticlePtr();
  }

  MSXML2::ISchemaStringCollectionPtr getNamespaces()
  {
    return getAnyPtr()->Getnamespaces();
  }

  SCHEMAPROCESSCONTENTS getProcessContents()
  {
    return getAnyPtr()->GetprocessContents ();
  }

public:
  void display(const TCHAR* name=NULL)
  {
    if (name == NULL) {
      name = _T("SchemaAny");
    }
    _tprintf(_T("<%s>\n"), name);

    try {
      SchemaStringCollection collection = getNamespaces();
      collection.display(_T("Namespaces"));

    } catch (...) {

    }
    _tprintf(_T("</%s>\n"), name);

  }
};

}
