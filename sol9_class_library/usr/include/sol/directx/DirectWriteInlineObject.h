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
 *  DirectWriteInlineObject.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteInlineObject : public ComIUnknown
{
public:
  //Call IDWriteFactory::CreateEllipsisTrimmingSign,
  DirectWriteInlineObject(IDWriteFactory* factory,
      IDWriteTextFormat* textFormat)
  :ComIUnknown()
  {
    IDWriteInlineObject* trimmingSign = NULL;
    HRESULT hr = factory -> CreateEllipsisTrimmingSign(
        textFormat,
        &trimmingSign
        );
    if (SUCCEEDED(hr)) {
      set(trimmingSign);
    } else  {
      throw IException("Failed to CreateEllipsisTrimmingSign. HRESULT(0x%lx)", hr);
    }
  }

public:
  DirectWriteInlineObject(IDWriteTextFormat* format,
      __out DWRITE_TRIMMING* trimmingOptions)
  :ComIUnknown()
  {
    IDWriteInlineObject* trimmingSign = NULL;
    HRESULT hr = format -> GetTrimming(
        trimmingOptions,
        &trimmingSign
        );
    if (SUCCEEDED(hr)) {
      set(trimmingSign);
    } else  {
      throw IException("Failed to CreateEllipsisTrimmingSign. HRESULT(0x%lx)", hr);
    }
  }

public:
  DirectWriteInlineObject(IDWriteTextLayout* layout,
       UINT32 currentPosition,
        __out DWRITE_TEXT_RANGE* textRange = NULL)
  :ComIUnknown()
  {
    IDWriteInlineObject* inlineObject = NULL;
    HRESULT hr = layout ->GetInlineObject(
        currentPosition,
        &inlineObject,
        textRange
        );
    if (SUCCEEDED(hr)) {
      set(inlineObject);
    } else  {
      throw IException("Failed to GetInlineObject. HRESULT(0x%lx)", hr);
    }
  }

  operator IDWriteInlineObject*()
  {
    return getInlineObject();
  }

  IDWriteInlineObject* getInlineObject()
  {
    IDWriteInlineObject* object = (IDWriteInlineObject*)getIUnknown();
    if (object) {
      return object;
    } else {
      throw IException("IDWriteInlineObject is NULL."); 
    }
  }
  
  void draw(
        void* clientDrawingContext,
        IDWriteTextRenderer* renderer,
        FLOAT originX,
        FLOAT originY,
        BOOL isSideways,
        BOOL isRightToLeft,
        IUnknown* clientDrawingEffect
        )
  {
    IDWriteInlineObject* object = getInlineObject();
    HRESULT hr = object -> Draw(
        clientDrawingContext,
        renderer,
        originX,
        originY,
        isSideways,
        isRightToLeft,
        clientDrawingEffect
        );
    if (FAILED(hr)) {
      throw IException("Failed to Draw. HRESULT(0x%lx)", hr);
    }
  }
  
  void getMetrics(
        __out DWRITE_INLINE_OBJECT_METRICS* metrics
        )
  {
    IDWriteInlineObject* object = getInlineObject();
    HRESULT hr = object -> GetMetrics(
        metrics
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getOverhangMetrics(
        __out DWRITE_OVERHANG_METRICS* overhangs
        )
  {
    IDWriteInlineObject* object = getInlineObject();
    HRESULT hr = object -> GetOverhangMetrics(
        overhangs
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetOverhangMetrics. HRESULT(0x%lx)", hr);
    }
  }

  void getBreakConditions(
        __out DWRITE_BREAK_CONDITION* breakConditionBefore,
        __out DWRITE_BREAK_CONDITION* breakConditionAfter
        )
  {
    IDWriteInlineObject* object = getInlineObject();
    HRESULT hr = object -> GetBreakConditions(
        breakConditionBefore,
        breakConditionAfter
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetBreakConditions. HRESULT(0x%lx)", hr);
    }
  }

};

}
