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
 *  DirectWriteTextFormat.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteTextFormat : public ComIUnknown
{
public:
  DirectWriteTextFormat()
  :ComIUnknown()
  {
  }
  
  DirectWriteTextFormat(IDWriteFactory* factory,
        __in_z WCHAR const* fontFamilyName,
        IDWriteFontCollection* fontCollection,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_FONT_STYLE fontStyle,
        DWRITE_FONT_STRETCH fontStretch,
        FLOAT fontSize,
        __in_z WCHAR const* localeName    
       )
  :ComIUnknown()
  {
    IDWriteTextFormat* format = NULL;
    
    HRESULT hr = factory -> CreateTextFormat(
        fontFamilyName,
        fontCollection,
        fontWeight,
        fontStyle,
        fontStretch,
        fontSize,
        localeName,
        &format
        );
    if (SUCCEEDED(hr)) {
      set(format);
    } else {
      throw IException("Failed to CreateTextFormat. HRESULT(0x%lx)", hr);
    }
  }

  
  ~DirectWriteTextFormat()
  {
  }
  
  operator IDWriteTextFormat*()
  {
    return getFormat();
  }

  IDWriteTextFormat* getFormat()
  {
    IDWriteTextFormat* format = (IDWriteTextFormat*)getIUnknown();
    if (format) {
      return format;
    } else {
      throw IException("IDWriteTextFormat is NULL.");
    }
  }
    
  void setTextAlignment(
        DWRITE_TEXT_ALIGNMENT textAlignment
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetTextAlignment(
        textAlignment
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetTextAlignment. HRESULT(0x%lx)", hr);
    }
  }
    
  void setParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetParagraphAlignment(
        paragraphAlignment
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetParagraphAlignment. HRESULT(0x%lx)", hr);
    }
  }

  void setWordWrapping(
        DWRITE_WORD_WRAPPING wordWrapping
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetWordWrapping(
        wordWrapping
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetWordWrapping. HRESULT(0x%lx)", hr);
    }
  }

  void setReadingDirection(
        DWRITE_READING_DIRECTION readingDirection
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetReadingDirection(
        readingDirection
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetReadingDirection. HRESULT(0x%lx)", hr);
    }
  }

  void setFlowDirection(
        DWRITE_FLOW_DIRECTION flowDirection
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetFlowDirection(
        flowDirection
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetFlowDirection. HRESULT(0x%lx)", hr);
    }
  }

  void setIncrementalTabStop(
        FLOAT incrementalTabStop
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetIncrementalTabStop(
        incrementalTabStop
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetIncrementalTabStop. HRESULT(0x%lx)", hr);
    }
  }

  void setTrimming(
        __in DWRITE_TRIMMING const* trimmingOptions,
        IDWriteInlineObject* trimmingSign
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetTrimming(
        trimmingOptions,
        trimmingSign
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetTrimming. HRESULT(0x%lx)", hr);
    }
  }

  void setLineSpacing(
        DWRITE_LINE_SPACING_METHOD lineSpacingMethod,
        FLOAT lineSpacing,
        FLOAT baseline
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> SetLineSpacing(
        lineSpacingMethod,
        lineSpacing,
        baseline
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetLineSpacing. HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_TEXT_ALIGNMENT getTextAlignment()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetTextAlignment();
  }

  DWRITE_PARAGRAPH_ALIGNMENT getParagraphAlignment()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetParagraphAlignment();
  }

  DWRITE_WORD_WRAPPING getWordWrapping()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetWordWrapping();
  }

  DWRITE_READING_DIRECTION getReadingDirection()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetReadingDirection();
  }

  DWRITE_FLOW_DIRECTION getFlowDirection()
  {
    IDWriteTextFormat* format = getFormat();
    return format ->  GetFlowDirection();
  }

  FLOAT getIncrementalTabStop()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetIncrementalTabStop();
  }

  void GetTrimming(
        __out DWRITE_TRIMMING* trimmingOptions,
        __out IDWriteInlineObject** trimmingSign
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> GetTrimming(
        trimmingOptions,
        trimmingSign
        ) ;
    if (FAILED(hr)) {
      throw IException("Failed to GetTrimming. HRESULT(0x%lx)", hr);
    }
  }

  void getLineSpacing(
        __out DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,
        __out FLOAT* lineSpacing,
        __out FLOAT* baseline
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> GetLineSpacing(
        lineSpacingMethod,
        lineSpacing,
        baseline
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLineSpacing. HRESULT(0x%lx)", hr);
    }
  }

  void getFontCollection(
        __out IDWriteFontCollection** fontCollection
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> GetFontCollection(
        fontCollection
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  UINT32 getFontFamilyNameLength()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetFontFamilyNameLength();
  }

  void getFontFamilyName(
        __out_ecount_z(nameSize) WCHAR* fontFamilyName,
        UINT32 nameSize
        )
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> GetFontFamilyName(
        fontFamilyName,
        nameSize
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFamilyName. HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_FONT_WEIGHT getFontWeight()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetFontWeight();
  }

  DWRITE_FONT_STYLE getFontStyle()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetFontStyle();
  }

  DWRITE_FONT_STRETCH getFontStretch()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetFontStretch();
  }

  FLOAT getFontSize()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetFontSize();
  }

  UINT32 getLocaleNameLength()
  {
    IDWriteTextFormat* format = getFormat();
    return format -> GetLocaleNameLength();
  }

  void getLocaleName(
        __out_ecount_z(nameSize) WCHAR* localeName,
        UINT32 nameSize)
  {
    IDWriteTextFormat* format = getFormat();
    HRESULT hr = format -> GetLocaleName(
        localeName,
        nameSize);
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleName. HRESULT(0x%lx)", hr);
    }
  }
};

}
