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
 *  Direct2D1Layer.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1RenderTarget.h>


namespace SOL {

class Direct2D1Layer : public Direct2D1Resource
{
public:
  Direct2D1Layer(ID2D1RenderTarget* target, __in CONST D2D1_SIZE_F *size)
  :Direct2D1Resource()
  {
    ID2D1Layer* layer = NULL;
    HRESULT hr = target -> CreateLayer(size, &layer);

    if (SUCCEEDED(hr)) {
      set(layer);
    } else {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1Layer(ID2D1RenderTarget* target, D2D1_SIZE_F size)
  :Direct2D1Resource()
  {
    ID2D1Layer* layer = NULL;
    HRESULT hr = target -> CreateLayer(size, &layer);    
    if (SUCCEEDED(hr)) {
      set(layer);
    } else {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1Layer(ID2D1RenderTarget* target)
  :Direct2D1Resource()
  {
    ID2D1Layer* layer = NULL;
    HRESULT hr = target -> CreateLayer(&layer);
    if (SUCCEEDED(hr)) {
      set(layer);
    } else {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1Layer()
  {
  }
  
  operator ID2D1Layer*()
  {
    return getLayer();
  }

  ID2D1Layer* getLayer()
  {
    ID2D1Layer* layer = (ID2D1Layer*)getIUnknown();
    if (layer) {
      return layer;
    } else {
      throw IException("ID2D1Layer is NULL.");
    }
  }
  

  D2D1_SIZE_F getSize(
        )
  {
    ID2D1Layer* layer = getLayer();
    return layer -> GetSize();
  }
};

}

