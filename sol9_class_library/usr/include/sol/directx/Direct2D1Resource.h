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
 *  Direct2D1Resource.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/com/ComIUnknown.h>

#include <d2d1.h>
#include <d2d1Helper.h>

#include <sol/directx/Direct2D1Factory.h>

namespace SOL {

class Direct2D1Resource : public ComIUnknown 
{
public:
  Direct2D1Resource()
  :ComIUnknown()
  {
  }
  
  operator ID2D1Resource*()
  {
    return getResource();
  }

  ID2D1Resource* getResource()
  {
    ID2D1Resource* resource = (ID2D1Resource*)getIUnknown();
    if (resource) {
      return resource;
    } else {
      throw IException("ID2D1Resource is NULL.");
    }
  }

  void getFactory(
        __out ID2D1Factory **factory 
        )
  {
    ID2D1Resource* resource = getResource();
    resource -> GetFactory(
        factory 
        );
  }
}; 

}

