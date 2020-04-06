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
 *  DirectWriteGlyphRunAnalysis.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>


namespace SOL {

class DirectWriteGlyphRunAnalysis : public ComIUnknown
{
public:
  DirectWriteGlyphRunAnalysis(IDWriteFactory* factory,
        __in DWRITE_GLYPH_RUN const* glyphRun,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        DWRITE_RENDERING_MODE renderingMode,
        DWRITE_MEASURING_MODE measuringMode,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY)
  {
    IDWriteGlyphRunAnalysis * analysis = NULL;
    HRESULT hr = factory ->CreateGlyphRunAnalysis(
        glyphRun,
        pixelsPerDip,
        transform,
        renderingMode,
        measuringMode,
        baselineOriginX,
        baselineOriginY,
        &analysis
        );
    if (SUCCEEDED(hr)) {
      set(analysis);
    } else {
      throw IException("Failed to CreateGlyphRunAnalysis. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteGlyphRunAnalysis()
  {
  }

  operator IDWriteGlyphRunAnalysis*()
  {
    return getAnalysis();
  }
  
  IDWriteGlyphRunAnalysis* getAnalysis()
  {
    IDWriteGlyphRunAnalysis* analysis = (IDWriteGlyphRunAnalysis*)getIUnknown();
    if (analysis) {
      return analysis;
    } else {
      throw IException("IDWriteGlyphRunAnalysis is NULL.");
    }
  }

  void getAlphaTextureBounds(
        DWRITE_TEXTURE_TYPE textureType,
        __out RECT* textureBounds
        )
  {
    IDWriteGlyphRunAnalysis* analysis = getAnalysis();
    HRESULT hr = analysis -> GetAlphaTextureBounds(
        textureType,
        textureBounds
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetAlphaTextureBounds. HRESULT(0x%lx)", hr);
    }
  }
  
  void createAlphaTexture(
        DWRITE_TEXTURE_TYPE textureType,
        __in RECT const* textureBounds,
        __out BYTE* alphaValues,
        UINT32 bufferSize
        )
  {
    IDWriteGlyphRunAnalysis* analysis = getAnalysis();
    HRESULT hr = analysis -> CreateAlphaTexture(
        textureType,
        textureBounds,
        alphaValues,
        bufferSize
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateAlphaTexture. HRESULT(0x%lx)", hr);
    }
  }

  void getAlphaBlendParams(
        IDWriteRenderingParams* renderingParams,
        __out FLOAT* blendGamma,
        __out FLOAT* blendEnhancedContrast,
        __out FLOAT* blendClearTypeLevel
        )
  {
    IDWriteGlyphRunAnalysis* analysis = getAnalysis();
    HRESULT hr = analysis -> GetAlphaBlendParams(
        renderingParams,
        blendGamma,
        blendEnhancedContrast,
        blendClearTypeLevel
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetAlphaBlendParams. HRESULT(0x%lx)", hr);
    }
  }

};



}
