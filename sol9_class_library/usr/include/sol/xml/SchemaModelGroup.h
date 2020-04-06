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
 *  SchemaModelGroup.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/06
#pragma once

#include <sol/xml/SchemaParticle.h>

namespace SOL {

class SchemaModelGroup : public SchemaParticle
{
public:
  SchemaModelGroup(MSXML2::ISchemaModelGroupPtr pGroup)
  :SchemaParticle((MSXML2::ISchemaParticlePtr)pGroup)
  {
  }
public:
  MSXML2::ISchemaModelGroupPtr getGroupPtr()
  {
    return(MSXML2::ISchemaModelGroupPtr)SchemaParticle::getParticlePtr();
  }

public:
  MSXML2::ISchemaItemCollectionPtr getParticles()
  {
    return getGroupPtr()->Getparticles();
  }
public:
  void display(const TCHAR* name=NULL)
  {
    if (name == NULL) {
      name = _T("SchemaModelGroup");
    }
    _tprintf(_T("<%s>\n"), name);

    try {
      SchemaItemCollection pCollection = getParticles();
      pCollection.display(_T("Particle"));
    } catch (...) {
    }
    _tprintf(_T("</%s>\n"), name);
  }
};


}
