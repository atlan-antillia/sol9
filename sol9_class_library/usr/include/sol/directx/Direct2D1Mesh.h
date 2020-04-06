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
 *  Direct2D1Mesh.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1RenderTarget.h>


namespace SOL {

class Direct2D1Mesh : public Direct2D1Resource
{
public:
  Direct2D1Mesh(ID2D1RenderTarget* target )
  :Direct2D1Resource()
  {
    ID2D1Mesh* mesh = NULL;
    HRESULT hr = target -> CreateMesh(&mesh);
    if (SUCCEEDED(hr)) {
      set(mesh);
    } else {
      throw IException("Failed to CreateMesh. HRESULT(0x%lx)", hr);
    }
  }

  operator ID2D1Mesh*()
  {
    return getMesh();
  }
  

  ID2D1Mesh* getMesh()
  {
    ID2D1Mesh* mesh = (ID2D1Mesh*)getIUnknown();
    if (mesh) {
      return mesh;
    } else {
      throw IException("ID2D1Mesh is NULL.");
    }
  }
  

  void open(
        __out ID2D1TessellationSink **tessellationSink 
        )
  {
    ID2D1Mesh* mesh = getMesh();
    HRESULT hr = mesh -> Open(tessellationSink);
    if (FAILED(hr)) {
      throw IException("Failed to Open. HRESULT(0x%lx)", hr);
    }
  }
  
};

}

