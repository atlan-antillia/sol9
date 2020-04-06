/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  Direct3D10Predicate.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10Query.h>

namespace SOL {

class Direct3D10Predicate : public Direct3D10Query {
public:
  Direct3D10Predicate(
      __in ID3D10Device* device,
      __in  const D3D10_QUERY_DESC *pPredicateDesc)
    
  :Direct3D10Query()
  {
    ID3D10Predicate *predicate = NULL;
    HRESULT hr = device -> CreatePredicate( 
        pPredicateDesc,
        &predicate);
    if (FAILED(hr)) {
      set(predicate);
    } else {
      throw IException("Failed to CreatePredicate. HRESULT(0x%lx)", hr)
    }
  }

  ~Direct3D10Predicate()
  {

  }

  operator ID3D10Predicate*()
  {
    return getPredicate();
  }

  ID3D10Predicate* getPredicate()
  {
    ID3D10Predicate* predicate = (ID3D10Predicate* )getIUnknown();
    if (predicate) {
      return predicate;
    } else {
      throw IException("D3D10Predicate is NULL.")
    }
  }
};

}
    
    
