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
 *  DirectWriteRenderingParams.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteRenderingParams : public ComIUnknown
{
public:
  DirectWriteRenderingParams(ID2D1DrawingStateBlock* block)
  :ComIUnknown()
  {
    IDWriteRenderingParams* params = NULL;
    block -> GetTextRenderingParams(
        &params 
        );
  }

  DirectWriteRenderingParams(ID2D1RenderTarget* target)
  :ComIUnknown()
  {
    IDWriteRenderingParams* params = NULL;
    target -> GetTextRenderingParams(
        &params);
  }

  DirectWriteRenderingParams(IDWriteFactory* factory)
  :ComIUnknown()
  {
    IDWriteRenderingParams* params = NULL;
    HRESULT hr = factory -> CreateRenderingParams(
        &params
        );
    if (SUCCEEDED(hr)) {
      set(params);
    } else {
      throw IException("Failed to CreateRenderingParams. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteRenderingParams(IDWriteFactory* factory, HMONITOR monitor)
  :ComIUnknown()
  {
    IDWriteRenderingParams* params = NULL;
    HRESULT hr = factory -> CreateMonitorRenderingParams(
        monitor,
        &params
        );
    if (SUCCEEDED(hr)) {
      set(params);
    } else {
      throw IException("Failed to CreateMonitorRenderingParams. HRESULT(0x%lx)", hr);
    }
  }
    
  DirectWriteRenderingParams(IDWriteFactory* factory,
        FLOAT gamma,
        FLOAT enhancedContrast,
        FLOAT clearTypeLevel,
        DWRITE_PIXEL_GEOMETRY pixelGeometry,
        DWRITE_RENDERING_MODE renderingMode)
  :ComIUnknown()
  {
    IDWriteRenderingParams* params = NULL;
    HRESULT hr = factory -> CreateCustomRenderingParams(
        gamma,
        enhancedContrast,
        clearTypeLevel,
        pixelGeometry,
        renderingMode,
        &params
        );
    
    if (SUCCEEDED(hr)) {
      set(params);
    } else {
      throw IException("Failed to CreateCustomRenderingParams. HRESULT(0x%lx)", hr);
    }
  }
    
  operator IDWriteRenderingParams*()
  {
    return getParams();
  }

  IDWriteRenderingParams* getParams()
  {
    IDWriteRenderingParams* params = (IDWriteRenderingParams*)getIUnknown();
    if (params) {
      return params;
    } else {
      throw IException("IDWriteRenderingParams is NULL.");
    }
  }
    
  FLOAT getGamma()
  {
    IDWriteRenderingParams* params = getParams();
    return params -> GetGamma();
  }
    
  FLOAT getEnhancedContrast()
  {
    IDWriteRenderingParams* params = getParams();
    return params -> GetEnhancedContrast();
  }

  FLOAT getClearTypeLevel()
  {
    IDWriteRenderingParams* params = getParams();
    return params -> GetClearTypeLevel();
  }

  DWRITE_PIXEL_GEOMETRY getPixelGeometry()
  {
    IDWriteRenderingParams* params = getParams();
    return params -> GetPixelGeometry();
  }

  DWRITE_RENDERING_MODE getRenderingMode()
  {
    IDWriteRenderingParams* params = getParams();
    return params -> GetRenderingMode();
  }

};

}
