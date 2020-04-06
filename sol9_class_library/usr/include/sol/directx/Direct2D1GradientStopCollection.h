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
 *  Direct2D1GradientStopCollection.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1LinearGradientBrush.h>

namespace SOL {

class Direct2D1GradientStopCollection : public Direct2D1Resource 
{
public:
  Direct2D1GradientStopCollection(ID2D1RenderTarget* target,
        __in CONST D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount)
  :Direct2D1Resource()
  {
    ID2D1GradientStopCollection* collection = NULL;
    HRESULT hr = target -> CreateGradientStopCollection(
                gradientStops,
                gradientStopsCount,
              &collection);
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to CreateGradientStopCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct2D1GradientStopCollection(ID2D1RenderTarget* target,
        __in CONST D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode)
  :Direct2D1Resource()
  {
    ID2D1GradientStopCollection* collection = NULL;
    HRESULT hr = target -> CreateGradientStopCollection(
        gradientStops,
        gradientStopsCount,
        colorInterpolationGamma,
        extendMode,
        &collection
    );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to CreateGradientStopCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  operator ID2D1GradientStopCollection*()
  {
    return getCollection();
  }

  ID2D1GradientStopCollection* getCollection()
  {
    ID2D1GradientStopCollection* collection = (ID2D1GradientStopCollection*)getIUnknown();
    if (collection) {
      return collection;
    } else {
      throw IException("ID2D1GradientStopCollection is NULL.");
    }
  }
  
  UINT32 getGradientStopCount(
        )
  {
    ID2D1GradientStopCollection* collection = getCollection();
    return collection -> GetGradientStopCount();
  }
  
  void getGradientStops(
        __out D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount 
        )
  {
    ID2D1GradientStopCollection* collection = getCollection();
    collection -> GetGradientStops(
        gradientStops,
        gradientStopsCount 
        );
  }
    
    
  D2D1_GAMMA getColorInterpolationGamma(
        )
  {
    ID2D1GradientStopCollection* collection = getCollection();
    return collection -> GetColorInterpolationGamma();
  }
    
  D2D1_EXTEND_MODE getExtendMode(
        )
  {
    ID2D1GradientStopCollection* collection = getCollection();
    return collection ->  GetExtendMode();
  }
};

}

