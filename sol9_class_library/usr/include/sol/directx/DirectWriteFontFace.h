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
 *  DirectWriteFontFace.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontFace : public ComIUnknown
{
public:
  DirectWriteFontFace(IDWriteFactory* factory,
        DWRITE_FONT_FACE_TYPE fontFaceType,
        UINT32 numberOfFiles,
        __in IDWriteFontFile* const* fontFiles,
        UINT32 faceIndex,
        DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags)
  :ComIUnknown()
  {
    IDWriteFontFace* face = NULL;
    HRESULT hr = factory -> CreateFontFace(
        fontFaceType,
        numberOfFiles,
        fontFiles,
        faceIndex,
        fontFaceSimulationFlags,
        &face);
    if (SUCCEEDED(hr)) {
      set(face);
    } else {
      throw IException("Failed to CreateFontFace. HRESUL(0x%lx", hr);
    }
  }

public:
  DirectWriteFontFace(IDWriteFont* font)
  :ComIUnknown()
  {
    IDWriteFontFace* face = NULL;
    HRESULT hr = font -> CreateFontFace(
        &face
        );
    if (SUCCEEDED(hr)) {
      set(face);
    } else {
      throw IException("Failed to CreateFontFace. HRESUL(0x%lx", hr);
    }
  }

public:
  DirectWriteFontFace(IDWriteGdiInterop* interop, HDC hdc)
  :ComIUnknown()
  {
    IDWriteFontFace* face = NULL;
    HRESULT hr = interop -> CreateFontFaceFromHdc(
        hdc,
        &face
        );
    if (SUCCEEDED(hr)) {
      set(face);
    } else {
      throw IException("Failed to CreateFontFaceFromHdc. HRESUL(0x%lx", hr);
    }
  }
    
  ~DirectWriteFontFace()
  {
  }
    
  operator IDWriteFontFace*()
  {
    return getFace();
  }

  IDWriteFontFace* getFace()
  {
    IDWriteFontFace* face = (IDWriteFontFace*)getIUnknown();
    if (face) {
      return face;
    } else {
      throw IException("IDWriteFontFace is NULL.");
    }
  }
    
  DWRITE_FONT_FACE_TYPE getType()
  {
    IDWriteFontFace* face = getFace();
    return face -> GetType();
  }

  void getFiles(
        __inout UINT32* numberOfFiles,
        __out IDWriteFontFile** fontFiles
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetFiles(
        numberOfFiles,
        fontFiles
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFiles. HRESULT(0x%lx)", hr);
    }
  }
    
  UINT32 GetIndex()
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetIndex();
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_FONT_SIMULATIONS GetSimulations()
  {
    IDWriteFontFace* face = getFace();
    return face -> GetSimulations();
  }

  BOOL isSymbolFont()
  {
    IDWriteFontFace* face = getFace();
    return face -> IsSymbolFont();
  }

  void getMetrics(
        __out DWRITE_FONT_METRICS* fontFaceMetrics
        )
  {
    IDWriteFontFace* face = getFace();
    face -> GetMetrics(
        fontFaceMetrics
        );
  }

  UINT16 getGlyphCount()
  {
    IDWriteFontFace* face = getFace();
    return face -> GetGlyphCount();
  }

  void getDesignGlyphMetrics(
        __in UINT16 const* glyphIndices,
        UINT32 glyphCount,
        __out DWRITE_GLYPH_METRICS* glyphMetrics,
        BOOL isSideways = FALSE
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetDesignGlyphMetrics(
        glyphIndices,
        glyphCount,
        glyphMetrics,
        isSideways
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetDesignGlyphMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getGlyphIndices(
        __in UINT32 const* codePoints,
        UINT32 codePointCount,
        __out UINT16* glyphIndices
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetGlyphIndices(
        codePoints,
        codePointCount,
        glyphIndices
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGlyphIndices. HRESULT(0x%lx)", hr);
    }
  }

  void tryGetFontTable(
        __in UINT32 openTypeTableTag,
        __out const void** tableData,
        __out UINT32* tableSize,
        __out void** tableContext,
        __out BOOL* exists
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> TryGetFontTable(
        openTypeTableTag,
        tableData,
        tableSize,
        tableContext,
        exists
        );
    if (FAILED(hr)) {
      throw IException("Failed to TryGetFontTable. HRESULT(0x%lx)", hr);
    }
  }

  void releaseFontTable(
        __in void* tableContext
        )
  {
    IDWriteFontFace* face = getFace();
    face -> ReleaseFontTable(tableContext);
  }

  void getGlyphRunOutline(
        FLOAT emSize,
        __in UINT16 const* glyphIndices,
        __in FLOAT const* glyphAdvances,
        __in DWRITE_GLYPH_OFFSET const* glyphOffsets,
        UINT32 glyphCount,
        BOOL isSideways,
        BOOL isRightToLeft,
        IDWriteGeometrySink* geometrySink
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetGlyphRunOutline(
        emSize,
        glyphIndices,
        glyphAdvances,
        glyphOffsets,
        glyphCount,
        isSideways,
        isRightToLeft,
        geometrySink
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGlyphRunOutline. HRESULT(0x%lx)", hr);
    }
  }

  void getRecommendedRenderingMode(
        FLOAT emSize,
        FLOAT pixelsPerDip,
        DWRITE_MEASURING_MODE measuringMode,
        IDWriteRenderingParams* renderingParams,
        __out DWRITE_RENDERING_MODE* renderingMode
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetRecommendedRenderingMode(
        emSize,
        pixelsPerDip,
        measuringMode,
        renderingParams,
        renderingMode
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetRecommendedRenderingMode. HRESULT(0x%lx)", hr);
    }
  }

  void getGdiCompatibleMetrics(
        FLOAT emSize,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        __out DWRITE_FONT_METRICS* fontFaceMetrics
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetGdiCompatibleMetrics(
        emSize,
        pixelsPerDip,
        transform,
        fontFaceMetrics
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGdiCompatibleMetrics. HRESULT(0x%lx)", hr);
    }
  }


  void getGdiCompatibleGlyphMetrics(
        FLOAT emSize,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        BOOL useGdiNatural,
        __in UINT16 const* glyphIndices,
        UINT32 glyphCount,
        __out DWRITE_GLYPH_METRICS* glyphMetrics,
        BOOL isSideways = FALSE
        )
  {
    IDWriteFontFace* face = getFace();
    HRESULT hr = face -> GetGdiCompatibleGlyphMetrics(
        emSize,
        pixelsPerDip,
        transform,
        useGdiNatural,
        glyphIndices,
        glyphCount,
        glyphMetrics,
        isSideways
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGdiCompatibleGlyphMetrics. HRESULT(0x%lx)", hr);
    }
  }
};

}
