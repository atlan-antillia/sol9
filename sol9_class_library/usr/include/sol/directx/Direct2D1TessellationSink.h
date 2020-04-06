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
 *  Direct2D1TessellationSink.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Mesh.h>

namespace SOL {

class Direct2D1TessellationSink : public ComIUnknown
{
public:
  Direct2D1TessellationSink(ID2D1Mesh* mesh)
  {
    ID2D1TessellationSink* sink = NULL;
    HRESULT hr = mesh -> Open(&sink);
    if (SUCCEEDED(hr)) {
      set(sink);
    } else {
      throw IException("Failed to Open. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1TessellationSink()
  {
  }
  
  operator ID2D1TessellationSink*()
  {
    return getSink();
  }
  
  ID2D1TessellationSink* getSink()
  {
    ID2D1TessellationSink* sink = (ID2D1TessellationSink*)getIUnknown();
    if (sink) {
      return sink;
    } else {
      throw IException("ID2D1TessellationSink is NULL.");
    }
  }
  

  void addTriangles(
        __in_ecount(trianglesCount) CONST D2D1_TRIANGLE *triangles,
        UINT trianglesCount 
        )
  {
    ID2D1TessellationSink* sink = getSink();
    sink -> AddTriangles(
        triangles,
        trianglesCount 
        );
  }
  
  void close(
        )
  {
    ID2D1TessellationSink* sink = getSink();
    HRESULT hr = sink -> Close();
    if (FAILED(hr)) {
      throw IException("Failed to Close. HRESULT(0x%lx)", hr);
    }
  }

};

}
