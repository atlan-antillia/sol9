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
 *  DirectWriteFactory.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "dwrite.lib")

namespace SOL {

class DirectWriteFactory : public ComIUnknown
{
public:
  DirectWriteFactory(
    __in DWRITE_FACTORY_TYPE factoryType = DWRITE_FACTORY_TYPE_SHARED,
    __in REFIID iid = __uuidof(IDWriteFactory)  )
  :ComIUnknown()
  {
    IDWriteFactory* factory = NULL;
    HRESULT hr = DWriteCreateFactory(
    factoryType,
    iid,
    (IUnknown**)&factory
    );
    if (SUCCEEDED(hr)) {
      set(factory);
    } else {
      throw IException("Failed to DWriteCreateFactory. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteFactory()
  {
  }

  operator IDWriteFactory*()
  {
    return getFactory();
  }
  
  IDWriteFactory* getFactory()
  {
    IDWriteFactory* factory = (IDWriteFactory*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("IDWriteFactory is NULL.");
    }
  }
  
  void getSystemFontCollection(
        __out IDWriteFontCollection** fontCollection,
        BOOL checkForUpdates = FALSE
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> GetSystemFontCollection(
        fontCollection,
        checkForUpdates
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetSystemFontCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  void createCustomFontCollection(
        IDWriteFontCollectionLoader* collectionLoader,
        __in void const* collectionKey,
        UINT32 collectionKeySize,
        __out IDWriteFontCollection** fontCollection
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateCustomFontCollection(
        collectionLoader,
        collectionKey,
        collectionKeySize,
        fontCollection
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCustomFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  void registerFontCollectionLoader(
        IDWriteFontCollectionLoader* fontCollectionLoader
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> RegisterFontCollectionLoader(
        fontCollectionLoader
        );
    if (FAILED(hr)) {
      throw IException("Failed to RegisterFontCollectionLoader. HRESULT(0x%lx)", hr);
    }
  }

  void unregisterFontCollectionLoader(
        IDWriteFontCollectionLoader* fontCollectionLoader
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> UnregisterFontCollectionLoader(
        fontCollectionLoader
        );
    if (FAILED(hr)) {
      throw IException("Failed to UnregisterFontCollectionLoader. HRESULT(0x%lx)", hr);
    }
  }

  void createFontFileReference(
        __in_z WCHAR const* filePath,
        __in FILETIME const* lastWriteTime,
        __out IDWriteFontFile** fontFile
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateFontFileReference(
        filePath,
        lastWriteTime,
        fontFile
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateFontFileReference. HRESULT(0x%lx)", hr);
    }
  }

  void createCustomFontFileReference(
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        IDWriteFontFileLoader* fontFileLoader,
        __out IDWriteFontFile** fontFile
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateCustomFontFileReference(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        fontFileLoader,
        fontFile
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCustomFontFileReference. HRESULT(0x%lx)", hr);
    }
  }

  void createFontFace(
        DWRITE_FONT_FACE_TYPE fontFaceType,
        UINT32 numberOfFiles,
        __in IDWriteFontFile* const* fontFiles,
        UINT32 faceIndex,
        DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags,
        __out IDWriteFontFace** fontFace
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateFontFace(
        fontFaceType,
        numberOfFiles,
        fontFiles,
        faceIndex,
        fontFaceSimulationFlags,
        fontFace
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateFontFace. HRESULT(0x%lx)", hr);
    }
  }

  void createRenderingParams(
        __out IDWriteRenderingParams** renderingParams
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateRenderingParams(
        renderingParams
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRenderingParams. HRESULT(0x%lx)", hr);
    }
  }

  void createMonitorRenderingParams(
        HMONITOR monitor,
        __out IDWriteRenderingParams** renderingParams
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateMonitorRenderingParams(
        monitor,
        renderingParams
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateMonitorRenderingParams. HRESULT(0x%lx)", hr);
    }
  }

  void createCustomRenderingParams(
        FLOAT gamma,
        FLOAT enhancedContrast,
        FLOAT clearTypeLevel,
        DWRITE_PIXEL_GEOMETRY pixelGeometry,
        DWRITE_RENDERING_MODE renderingMode,
        __out IDWriteRenderingParams** renderingParams
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateCustomRenderingParams(
        gamma,
        enhancedContrast,
        clearTypeLevel,
        pixelGeometry,
        renderingMode,
        renderingParams
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCustomRenderingParams. HRESULT(0x%lx)", hr);
    }
  }

  void registerFontFileLoader(
        IDWriteFontFileLoader* fontFileLoader
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> RegisterFontFileLoader(
        fontFileLoader
        );
    if (FAILED(hr)) {
      throw IException("Failed to RegisterFontFileLoader. HRESULT(0x%lx)", hr);
    }
  }

  void unregisterFontFileLoader(
        IDWriteFontFileLoader* fontFileLoader
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> UnregisterFontFileLoader(
        fontFileLoader
        );
    if (FAILED(hr)) {
      throw IException("Failed to UnregisterFontFileLoader. HRESULT(0x%lx)", hr);
    }
  }

  void createTextFormat(
        __in_z WCHAR const* fontFamilyName,
        IDWriteFontCollection* fontCollection,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_FONT_STYLE fontStyle,
        DWRITE_FONT_STRETCH fontStretch,
        FLOAT fontSize,
        __in_z WCHAR const* localeName,
        __out IDWriteTextFormat** textFormat
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateTextFormat(
        fontFamilyName,
        fontCollection,
        fontWeight,
        fontStyle,
        fontStretch,
        fontSize,
        localeName,
        textFormat
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTextFormat. HRESULT(0x%lx)", hr);
    }
  }

  void createTypography(
        __out IDWriteTypography** typography
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateTypography(
        typography
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTypography. HRESULT(0x%lx)", hr);
    }
  }

  void getGdiInterop(
        __out IDWriteGdiInterop** gdiInterop
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> GetGdiInterop(
        gdiInterop
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetGdiInterop. HRESULT(0x%lx)", hr);
    }
  }

  void createTextLayout(
        __in WCHAR const* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT maxWidth,
        FLOAT maxHeight,
        __out IDWriteTextLayout** textLayout
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateTextLayout(
        string,
        stringLength,
        textFormat,
        maxWidth,
        maxHeight,
        textLayout
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTextLayout. HRESULT(0x%lx)", hr);
    }
  }

  void createGdiCompatibleTextLayout(
        __in WCHAR const* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT layoutWidth,
        FLOAT layoutHeight,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        BOOL useGdiNatural,
        __out IDWriteTextLayout** textLayout
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateGdiCompatibleTextLayout(
        string,
        stringLength,
        textFormat,
        layoutWidth,
        layoutHeight,
        pixelsPerDip,
        transform,
        useGdiNatural,
        textLayout
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateGdiCompatibleTextLayout. HRESULT(0x%lx)", hr);
    }
  }

  void createEllipsisTrimmingSign(
        IDWriteTextFormat* textFormat,
        __out IDWriteInlineObject** trimmingSign
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateEllipsisTrimmingSign(
        textFormat,
        trimmingSign
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateEllipsisTrimmingSign. HRESULT(0x%lx)", hr);
    }
  }

  void createTextAnalyzer(
        __out IDWriteTextAnalyzer** textAnalyzer
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateTextAnalyzer(
        textAnalyzer
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTextAnalyzer. HRESULT(0x%lx)", hr);
    }
  }

  void createNumberSubstitution(
        __in DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod,
        __in_z WCHAR const* localeName,
        __in BOOL ignoreUserOverride,
        __out IDWriteNumberSubstitution** numberSubstitution
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateNumberSubstitution(
        substitutionMethod,
        localeName,
        ignoreUserOverride,
        numberSubstitution
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateNumberSubstitution. HRESULT(0x%lx)", hr);
    }
  }

  void createGlyphRunAnalysis(
        __in DWRITE_GLYPH_RUN const* glyphRun,
        FLOAT pixelsPerDip,
        __in DWRITE_MATRIX const* transform,
        DWRITE_RENDERING_MODE renderingMode,
        DWRITE_MEASURING_MODE measuringMode,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        __out IDWriteGlyphRunAnalysis** glyphRunAnalysis
        )
  {
    IDWriteFactory* factory = getFactory();
    HRESULT hr = factory -> CreateGlyphRunAnalysis(
        glyphRun,
        pixelsPerDip,
        transform,
        renderingMode,
        measuringMode,
        baselineOriginX,
        baselineOriginY,
        glyphRunAnalysis
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateGlyphRunAnalysis. HRESULT(0x%lx)", hr);
    }
  }

}; 

}
