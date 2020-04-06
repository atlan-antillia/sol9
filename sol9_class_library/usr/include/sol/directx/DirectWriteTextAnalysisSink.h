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
 *  DirectWriteTextAnalysisSink.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

//-----------------
namespace SOL {

class DirectWriteTextAnalysisSink : public ComIUnknown
{
public:
  DirectWriteTextAnalysisSink()
  :ComIUnknown()
  {
  }

  ~DirectWriteTextAnalysisSink()
  {
  }

  operator IDWriteTextAnalysisSink*()
  {
    return getSink();
  }

  IDWriteTextAnalysisSink* getSink()
  {
    IDWriteTextAnalysisSink* sink = (IDWriteTextAnalysisSink*)getIUnknown();
    if (sink) {
      return sink;
    } else {
      throw IException("IDWriteTextAnalysisSink is NULL.");
    }
  }
  
  void setScriptAnalysis(
        UINT32 textPosition,
        UINT32 textLength,
        __in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis
        )
  {
    IDWriteTextAnalysisSink* sink = getSink();
    HRESULT hr = sink -> SetScriptAnalysis(
        textPosition,
        textLength,
        scriptAnalysis
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetScriptAnalysis. HRESULT(0x%lx)", hr);
    }
  }
  
  void setLineBreakpoints(
        UINT32 textPosition,
        UINT32 textLength,
        __in DWRITE_LINE_BREAKPOINT const* lineBreakpoints
        )
  {
    IDWriteTextAnalysisSink* sink = getSink();
    HRESULT hr = sink -> SetLineBreakpoints(
        textPosition,
        textLength,
        lineBreakpoints
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetLineBreakpoints. HRESULT(0x%lx)", hr);
    }
  }
  
  void setBidiLevel(
        UINT32 textPosition,
        UINT32 textLength,
        UINT8 explicitLevel,
        UINT8 resolvedLevel
        )
  {
    IDWriteTextAnalysisSink* sink = getSink();
    HRESULT hr = sink -> SetBidiLevel(
        textPosition,
        textLength,
        explicitLevel,
        resolvedLevel
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetBidiLevel. HRESULT(0x%lx)", hr);
    }
  }

  void setNumberSubstitution(
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteNumberSubstitution* numberSubstitution
        )
  {
    IDWriteTextAnalysisSink* sink = getSink();
    HRESULT hr = sink -> SetNumberSubstitution(
        textPosition,
        textLength,
        numberSubstitution
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetNumberSubstitution. HRESULT(0x%lx)", hr);
    }
  }

};

}

