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
 *  DirectWriteTextAnalysisSource.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteTextAnalysisSource : public ComIUnknown
{
public:
  DirectWriteTextAnalysisSource()
  :ComIUnknown()
  {
    IDWriteTextAnalysisSource* source = NULL;
  }

  ~DirectWriteTextAnalysisSource()
  {
  }

  operator IDWriteTextAnalysisSource*()
  {
    return getSource();
  }

  IDWriteTextAnalysisSource* getSource()
  {
    IDWriteTextAnalysisSource* source = (IDWriteTextAnalysisSource*)getIUnknown();
    if (source) {
      return source;
    } else {
      throw IException("IDWriteTextAnalysisSource is NULL.");
    }
  }

  void getTextAtPosition(
        UINT32 textPosition,
        __out WCHAR const** textString,
        __out UINT32* textLength
        )
  {
    IDWriteTextAnalysisSource* source = getSource();
    HRESULT hr = source -> GetTextAtPosition(
        textPosition,
        textString,
        textLength
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetTextAtPosition. HRESULT(0x%lx)", hr);
    }
  }
  
  void getTextBeforePosition(
        UINT32 textPosition,
        __out WCHAR const** textString,
        __out UINT32* textLength
        )
  {
    IDWriteTextAnalysisSource* source = getSource();
    HRESULT hr = source -> GetTextBeforePosition(
        textPosition,
        textString,
        textLength
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetTextBeforePosition. HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_READING_DIRECTION GetParagraphReadingDirection()
  {
    IDWriteTextAnalysisSource* source = getSource();
    return source -> GetParagraphReadingDirection();
  }

  void getLocaleName(
        UINT32 textPosition,
        __out UINT32* textLength,
        __out_z WCHAR const** localeName
        )
  {
    IDWriteTextAnalysisSource* source = getSource();
    HRESULT hr = source -> GetLocaleName(
        textPosition,
        textLength,
        localeName
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleName. HRESULT(0x%lx)", hr);
    }
  }
  
  void getNumberSubstitution(
        UINT32 textPosition,
        __out UINT32* textLength,
        __out IDWriteNumberSubstitution** numberSubstitution
        )
  {
    IDWriteTextAnalysisSource* source = getSource();
    HRESULT hr = source -> GetNumberSubstitution(
        textPosition,
        textLength,
        numberSubstitution
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetNumberSubstitution. HRESULT(0x%lx)", hr);
    }
  }

};

}
