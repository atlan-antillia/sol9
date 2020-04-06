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
 *  DirectWriteTextAnalyzer.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteTextAnalyzer : public ComIUnknown
{
public:
  DirectWriteTextAnalyzer(IDWriteFactory* factory)
  {
    IDWriteTextAnalyzer* analyzer = NULL;
    
    HRESULT hr = factory -> CreateTextAnalyzer(
        &analyzer
        );
    if (SUCCEEDED(hr)) {
      set(analyzer);
    } else {
      throw IException("Failed to CreateTextAnalyzer. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteTextAnalyzer()
  {
  }

  operator IDWriteTextAnalyzer*()
  {
    return getAnalyzer();
  }

  IDWriteTextAnalyzer* getAnalyzer()
  {
    IDWriteTextAnalyzer* analyzer = (IDWriteTextAnalyzer*)getIUnknown();
    if (analyzer) {
      return analyzer;
    } else {
      throw IException("IDWriteTextAnalyzer is NULL.");
    }
  }
  
  void analyzeScript(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> AnalyzeScript(
        analysisSource,
        textPosition,
        textLength,
        analysisSink
        );
    if (FAILED(hr)) {
      throw IException("Failed to AnalyzeScript. HRESULT(0x%lx)", hr);
    }
  }
  
  void analyzeBidi(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> AnalyzeBidi(
        analysisSource,
        textPosition,
        textLength,
        analysisSink
        );
    if (FAILED(hr)) {
      throw IException("Failed to AnalyzeBidi. HRESULT(0x%lx)", hr);
    }
  }

  void analyzeNumberSubstitution(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> AnalyzeNumberSubstitution(
        analysisSource,
        textPosition,
        textLength,
        analysisSink
        );
    if (FAILED(hr)) {
      throw IException("Failed to AnalyzeNumberSubstitution. HRESULT(0x%lx)", hr);
    }
  }

  void analyzeLineBreakpoints(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> AnalyzeLineBreakpoints(
        analysisSource,
        textPosition,
        textLength,
        analysisSink
        );
    if (FAILED(hr)) {
      throw IException("Failed to AnalyzeLineBreakpoints. HRESULT(0x%lx)", hr);
    }
  }

  void getGlyphs(
        __in WCHAR const* textString,
        UINT32 textLength,
        IDWriteFontFace* fontFace,
        BOOL isSideways,
        BOOL isRightToLeft,
        __in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
        __in_z_opt WCHAR const* localeName,
        IDWriteNumberSubstitution* numberSubstitution,
        __in DWRITE_TYPOGRAPHIC_FEATURES const** features,
        __in UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        UINT32 maxGlyphCount,
        __out UINT16* clusterMap,
        __out DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
        __out UINT16* glyphIndices,
        __out DWRITE_SHAPING_GLYPH_PROPERTIES* glyphProps,
        __out UINT32* actualGlyphCount
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> GetGlyphs(
        textString,
        textLength,
        fontFace,
        isSideways,
        isRightToLeft,
        scriptAnalysis,
        localeName,
        numberSubstitution,
        features,
        featureRangeLengths,
        featureRanges,
        maxGlyphCount,
        clusterMap,
        textProps,
        glyphIndices,
        glyphProps,
        actualGlyphCount
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGlyphs. HRESULT(0x%lx)", hr);
    }
  }

  void getGlyphPlacements(
        __in WCHAR const* textString,
        __in UINT16 const* clusterMap,
        __in DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
        UINT32 textLength,
        __in UINT16 const* glyphIndices,
        __in DWRITE_SHAPING_GLYPH_PROPERTIES const* glyphProps,
        UINT32 glyphCount,
        IDWriteFontFace * fontFace,
        FLOAT fontEmSize,
        BOOL isSideways,
        BOOL isRightToLeft,
        __in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
        __in_z_opt WCHAR const* localeName,
        __in DWRITE_TYPOGRAPHIC_FEATURES const** features,
        __in UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        __out FLOAT* glyphAdvances,
        __out DWRITE_GLYPH_OFFSET* glyphOffsets
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> GetGlyphPlacements(
        textString,
        clusterMap,
        textProps,
        textLength,
        glyphIndices,
        glyphProps,
        glyphCount,
        fontFace,
        fontEmSize,
        isSideways,
        isRightToLeft,
        scriptAnalysis,
        localeName,
        features,
        featureRangeLengths,
        featureRanges,
        glyphAdvances,
        glyphOffsets
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGlyphPlacements. HRESULT(0x%lx)", hr);
    }
  }

  void getGdiCompatibleGlyphPlacements(
        __in WCHAR const* textString,
        __in UINT16 const* clusterMap,
        __in DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
        UINT32 textLength,
        __in UINT16 const* glyphIndices,
        __in DWRITE_SHAPING_GLYPH_PROPERTIES const* glyphProps,
        UINT32 glyphCount,
        IDWriteFontFace * fontFace,
        FLOAT fontEmSize,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        BOOL useGdiNatural,
        BOOL isSideways,
        BOOL isRightToLeft,
        __in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
        __in_z_opt WCHAR const* localeName,
        __in DWRITE_TYPOGRAPHIC_FEATURES const** features,
        __in UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        __out FLOAT* glyphAdvances,
        __out DWRITE_GLYPH_OFFSET* glyphOffsets
        )
  {
    IDWriteTextAnalyzer* analyzer = getAnalyzer();
    HRESULT hr = analyzer -> GetGdiCompatibleGlyphPlacements(
        textString,
        clusterMap,
        textProps,
        textLength,
        glyphIndices,
        glyphProps,
        glyphCount,
        fontFace,
        fontEmSize,
        pixelsPerDip,
        transform,
        useGdiNatural,
        isSideways,
        isRightToLeft,
        scriptAnalysis,
        localeName,
        features,
        featureRangeLengths,
        featureRanges,
        glyphAdvances,
        glyphOffsets
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGdiCompatibleGlyphPlacements. HRESULT(0x%lx)", hr);
    }
  }

};

}

