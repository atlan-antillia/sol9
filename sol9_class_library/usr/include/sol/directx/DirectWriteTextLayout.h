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
 *  DirectWriteTextLayout.h
 *
 *****************************************************************************/

#pragma once
#include <sol/directx/DirectWriteTextFormat.h>


namespace SOL {

class DirectWriteTextLayout : public DirectWriteTextFormat
{
public:
  DirectWriteTextLayout(IDWriteFactory* factory,
        __in WCHAR const* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT maxWidth,
        FLOAT maxHeight)
  :DirectWriteTextFormat()
  {
    IDWriteTextLayout* layout = NULL;
    HRESULT hr = factory -> CreateTextLayout(
        string,
        stringLength,
        textFormat,
        maxWidth,
        maxHeight,
        &layout
        );
    if(SUCCEEDED(hr)) {
      set(layout);
    } else {
      throw IException("Failed to CreateTextLayout. HRESULT(0x%lx)", hr);
    }
  }

public:
  DirectWriteTextLayout(IDWriteFactory* factory,
        __in WCHAR const* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT layoutWidth,
        FLOAT layoutHeight,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        BOOL useGdiNatural)
  :DirectWriteTextFormat()
  {
    IDWriteTextLayout* layout = NULL;

    HRESULT hr = factory -> CreateGdiCompatibleTextLayout(
        string,
        stringLength,
        textFormat,
        layoutWidth,
        layoutHeight,
        pixelsPerDip,
        transform,
        useGdiNatural,
        &layout
        );
    if (SUCCEEDED(hr)) {
      set(layout);
    } else {
      throw IException("Failed to CreateGdiCompatibleTextLayout. HRESULT(0x%lx)", hr);
    }  }

  ~DirectWriteTextLayout()
  {
  }

  operator IDWriteTextLayout*()
  {
    return getLayout();
  }

  IDWriteTextLayout* getLayout()
  {
    IDWriteTextLayout* layout = (IDWriteTextLayout*)getIUnknown();
    if (layout) {
      return layout;
    } else {
      throw IException("IDWriteTextLayout is NULL.");
    }
  }
  
  void setMaxWidth(
        FLOAT maxWidth
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetMaxWidth(
        maxWidth
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetMaxWidth. HRESULT(0x%lx)", hr);
    }
  }
  
  void setMaxHeight(
        FLOAT maxHeight
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetMaxHeight(
        maxHeight
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetMaxHeight. HRESULT(0x%lx)", hr);
    }
  }

  void setFontCollection(
        IDWriteFontCollection* fontCollection,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontCollection(
        fontCollection,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  void setFontFamilyName(
        __in_z WCHAR const* fontFamilyName,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontFamilyName(
        fontFamilyName,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontFamilyName. HRESULT(0x%lx)", hr);
    }
  }

  void setFontWeight(
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontWeight(
        fontWeight,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontWeight. HRESULT(0x%lx)", hr);
    }
  }

  void setFontStyle(
        DWRITE_FONT_STYLE fontStyle,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontStyle(
        fontStyle,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontStyle. HRESULT(0x%lx)", hr);
    }
  }

  void setFontStretch(
        DWRITE_FONT_STRETCH fontStretch,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontStretch(
        fontStretch,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontStretch. HRESULT(0x%lx)", hr);
    }
  }

  void setFontSize(
        FLOAT fontSize,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetFontSize(
        fontSize,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFontSize. HRESULT(0x%lx)", hr);
    }
  }

  void setUnderline(
        BOOL hasUnderline,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetUnderline(
        hasUnderline,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetUnderline. HRESULT(0x%lx)", hr);
    }
  }

  void setStrikethrough(
        BOOL hasStrikethrough,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetStrikethrough(
        hasStrikethrough,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetStrikethrough. HRESULT(0x%lx)", hr);
    }
  }

  void setDrawingEffect(
        IUnknown* drawingEffect,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetDrawingEffect(
        drawingEffect,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetDrawingEffect. HRESULT(0x%lx)", hr);
    }
  }

  void setInlineObject(
        IDWriteInlineObject* inlineObject,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetInlineObject(
        inlineObject,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetInlineObject. HRESULT(0x%lx)", hr);
    }
  }

  void setTypography(
        IDWriteTypography* typography,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetTypography(
        typography,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetTypography. HRESULT(0x%lx)", hr);
    }
  }

  void setLocaleName(
        __in_z WCHAR const* localeName,
        DWRITE_TEXT_RANGE textRange
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> SetLocaleName(
        localeName,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetLocaleName. HRESULT(0x%lx)", hr);
    }
  }

  FLOAT getMaxWidth()
  {
    IDWriteTextLayout* layout = getLayout();
    return layout -> GetMaxWidth();
  }

  FLOAT getMaxHeight()
  {
    IDWriteTextLayout* layout = getLayout();
    return layout -> GetMaxHeight();
  }

  void getFontCollection(
        UINT32 currentPosition,
        __out IDWriteFontCollection** fontCollection,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontCollection(
        currentPosition,
        fontCollection,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  void getFontFamilyNameLength(
        UINT32 currentPosition,
        __out UINT32* nameLength,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontFamilyNameLength(
        currentPosition,
        nameLength,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFamilyNameLength. HRESULT(0x%lx)", hr);
    }
  }

  void getFontFamilyName(
        UINT32 currentPosition,
        __out WCHAR* fontFamilyName,
        UINT32 nameSize,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontFamilyName(
        currentPosition,
        fontFamilyName,
        nameSize,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFamilyName. HRESULT(0x%lx)", hr);
    }
  }

  void getFontWeight(
        UINT32 currentPosition,
        __out DWRITE_FONT_WEIGHT* fontWeight,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontWeight(
        currentPosition,
        fontWeight,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontWeight. HRESULT(0x%lx)", hr);
    }
  }

  void getFontStyle(
        UINT32 currentPosition,
        __out DWRITE_FONT_STYLE* fontStyle,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontStyle(
        currentPosition,
        fontStyle,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontStyle. HRESULT(0x%lx)", hr);
    }
  }

  void getFontStretch(
        UINT32 currentPosition,
        __out DWRITE_FONT_STRETCH* fontStretch,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontStretch(
        currentPosition,
        fontStretch,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontStretch. HRESULT(0x%lx)", hr);
    }
  }

  void getFontSize(
        UINT32 currentPosition,
        __out FLOAT* fontSize,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetFontSize(
        currentPosition,
        fontSize,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontSize. HRESULT(0x%lx)", hr);
    }
  }

  void getUnderline(
        UINT32 currentPosition,
        __out BOOL* hasUnderline,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetUnderline(
        currentPosition,
        hasUnderline,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetUnderline. HRESULT(0x%lx)", hr);
    }
  }

  void getStrikethrough(
        UINT32 currentPosition,
        __out BOOL* hasStrikethrough,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetStrikethrough(
        currentPosition,
        hasStrikethrough,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetStrikethrough. HRESULT(0x%lx)", hr);
    }
  }

  void getDrawingEffect(
        UINT32 currentPosition,
        __out IUnknown** drawingEffect,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetDrawingEffect(
        currentPosition,
        drawingEffect,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetDrawingEffect. HRESULT(0x%lx)", hr);
    }
  }

  void getInlineObject(
        UINT32 currentPosition,
        __out IDWriteInlineObject** inlineObject,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetInlineObject(
        currentPosition,
        inlineObject,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetInlineObject. HRESULT(0x%lx)", hr);
    }
  }

  void getTypography(
        UINT32 currentPosition,
        __out IDWriteTypography** typography,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetTypography(
        currentPosition,
        typography,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetTypography. HRESULT(0x%lx)", hr);
    }
  }

  void getLocaleNameLength(
        UINT32 currentPosition,
        __out UINT32* nameLength,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetLocaleNameLength(
        currentPosition,
        nameLength,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleNameLength. HRESULT(0x%lx)", hr);
    }
  }

  void getLocaleName(
        UINT32 currentPosition,
        __out WCHAR* localeName,
        UINT32 nameSize,
        __out DWRITE_TEXT_RANGE* textRange = NULL
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetLocaleName(
        currentPosition,
        localeName,
        nameSize,
        textRange
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleName. HRESULT(0x%lx)", hr);
    }
  }

  void draw(
        void* clientDrawingContext,
        IDWriteTextRenderer* renderer,
        FLOAT originX,
        FLOAT originY
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> Draw(
        clientDrawingContext,
        renderer,
        originX,
        originY
        );
    if (FAILED(hr)) {
      throw IException("Failed to Draw. HRESULT(0x%lx)", hr);
    }
  }

  void getLineMetrics(
        __out DWRITE_LINE_METRICS* lineMetrics,
        UINT32 maxLineCount,
        __out UINT32* actualLineCount
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetLineMetrics(
        lineMetrics,
        maxLineCount,
        actualLineCount
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLineMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getMetrics(
        __out DWRITE_TEXT_METRICS* textMetrics
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetMetrics(
        textMetrics
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getOverhangMetrics(
        __out DWRITE_OVERHANG_METRICS* overhangs
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetOverhangMetrics(
        overhangs
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetOverhangMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getClusterMetrics(
        __out DWRITE_CLUSTER_METRICS* clusterMetrics,
        UINT32 maxClusterCount,
        __out UINT32* actualClusterCount
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> GetClusterMetrics(
        clusterMetrics,
        maxClusterCount,
        actualClusterCount
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetClusterMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void determineMinWidth(
        __out FLOAT* minWidth
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> DetermineMinWidth(
        minWidth
        );
    if (FAILED(hr)) {
      throw IException("Failed to DetermineMinWidth. HRESULT(0x%lx)", hr);
    }
  }

  void hitTestPoint(
        FLOAT pointX,
        FLOAT pointY,
        __out BOOL* isTrailingHit,
        __out BOOL* isInside,
        __out DWRITE_HIT_TEST_METRICS* hitTestMetrics
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> HitTestPoint(
        pointX,
        pointY,
        isTrailingHit,
        isInside,
        hitTestMetrics
        );
    if (FAILED(hr)) {
      throw IException("Failed to HitTestPoint. HRESULT(0x%lx)", hr);
    }
  }

  void hitTestTextPosition(
        UINT32 textPosition,
        BOOL isTrailingHit,
        __out FLOAT* pointX,
        __out FLOAT* pointY,
        __out DWRITE_HIT_TEST_METRICS* hitTestMetrics
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> HitTestTextPosition(
        textPosition,
        isTrailingHit,
        pointX,
        pointY,
        hitTestMetrics
        );
    if (FAILED(hr)) {
      throw IException("Failed to HitTestTextPosition. HRESULT(0x%lx)", hr);
    }
  }

  void hitTestTextRange(
        UINT32 textPosition,
        UINT32 textLength,
        FLOAT originX,
        FLOAT originY,
        __out DWRITE_HIT_TEST_METRICS* hitTestMetrics,
        UINT32 maxHitTestMetricsCount,
        __out UINT32* actualHitTestMetricsCount
        )
  {
    IDWriteTextLayout* layout = getLayout();
    HRESULT hr = layout -> HitTestTextRange(
        textPosition,
        textLength,
        originX,
        originY,
        hitTestMetrics,
        maxHitTestMetricsCount,
        actualHitTestMetricsCount
        );
    if (FAILED(hr)) {
      throw IException("Failed to HitTestTextRange. HRESULT(0x%lx)", hr);
    }
  }

};

}
