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
#include <sol/directx/DirectWritePixelSnapping.h>

//-----------------
namespace SOL {

class DirectWriteTextRenderer : public DirectWritePixelSnapping
{
public:
  DirectWriteTextRenderer()
  :DirectWritePixelSnapping()
  {
  }

  operator IDWriteTextRenderer*()
  {
    return getRenderer();
  }

  IDWriteTextRenderer* getRenderer()
  {
    IDWriteTextRenderer* renderer = (IDWriteTextRenderer*)getIUnknown();
    if (renderer) {
      return renderer;
    } else {
      throw IException("IDWriteTextRenderer is NULL.");
    }
  }
  
  void drawGlyphRun(
        void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_MEASURING_MODE measuringMode,
        __in DWRITE_GLYPH_RUN const* glyphRun,
        __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
        IUnknown* clientDrawingEffect
        )
  {
    IDWriteTextRenderer* renderer = getRenderer();
    HRESULT hr = renderer -> DrawGlyphRun(
        clientDrawingContext,
        baselineOriginX,
        baselineOriginY,
        measuringMode,
        glyphRun,
        glyphRunDescription,
        clientDrawingEffect
        );
    if (FAILED(hr)) {
      throw IException("Failed to DrawGlyphRun. HRESULT(0x%lx)", hr);
    }
  }
  
  void drawUnderline(
        __maybenull void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        __in DWRITE_UNDERLINE const* underline,
        IUnknown* clientDrawingEffect
        )
  {
    IDWriteTextRenderer* renderer = getRenderer();
    HRESULT hr = renderer -> DrawUnderline(
        clientDrawingContext,
        baselineOriginX,
        baselineOriginY,
        underline,
        clientDrawingEffect
        );
    if (FAILED(hr)) {
      throw IException("Failed to DrawUnderline. HRESULT(0x%lx)", hr);
    }
  }

  void drawStrikethrough(
        void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        __in DWRITE_STRIKETHROUGH const* strikethrough,
        IUnknown* clientDrawingEffect
        )
  {
    IDWriteTextRenderer* renderer = getRenderer();
    HRESULT hr = renderer -> DrawStrikethrough(
        clientDrawingContext,
        baselineOriginX,
        baselineOriginY,
        strikethrough,
        clientDrawingEffect
        );
    if (FAILED(hr)) {
      throw IException("Failed to DrawStrikethrough. HRESULT(0x%lx)", hr);
    }
  }

  void drawInlineObject(
        void* clientDrawingContext,
        FLOAT originX,
        FLOAT originY,
        IDWriteInlineObject* inlineObject,
        BOOL isSideways,
        BOOL isRightToLeft,
        IUnknown* clientDrawingEffect
        )
  {
    IDWriteTextRenderer* renderer = getRenderer();
    HRESULT hr = renderer -> DrawInlineObject(
        clientDrawingContext,
        originX,
        originY,
        inlineObject,
        isSideways,
        isRightToLeft,
        clientDrawingEffect
        );
    if (FAILED(hr)) {
      throw IException("Failed to DrawInlineObject. HRESULT(0x%lx)", hr);
    }
  }

};

}
