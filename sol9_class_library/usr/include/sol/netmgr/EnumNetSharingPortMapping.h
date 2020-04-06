/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  EnumNetSharingPortMapping.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIUnknown.h>
#include <netcon.h>

namespace SOL {

class EnumNetSharingPortMapping : public ComIUnknown
{

public:
  EnumNetSharingPortMapping(IEnumNetSharingPortMapping* pMapping)
    :ComIUnknown(pMapping)
  {
  }

private:
  IEnumNetSharingPortMapping* getMapping()
  {
    return (IEnumNetSharingPortMapping*) getIUnknown();
  }

public:
  HRESULT next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ VARIANT *rgVar,
            /* [out] */ ULONG *pceltFetched)
  {
    HRESULT hr = getMapping() -> Next( 
      celt,
      rgVar,
      pceltFetched);
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }


  HRESULT skip( 
            /* [in] */ ULONG celt)
  {
    HRESULT hr = getMapping() -> Skip( 
        celt);
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT reset()
  {
    HRESULT hr = getMapping() -> Reset();
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT clone( 
            /* [out] */ IEnumNetSharingPortMapping **ppenum)
  {
    HRESULT hr = getMapping() -> Clone( 
        ppenum);
    if (hr != S_OK) {
      throw hr;
    }
    return hr;
  }
        
};

    
