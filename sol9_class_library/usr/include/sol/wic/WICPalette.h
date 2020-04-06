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
 *  WICPalette.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>

namespace SOL {

class WICPalette: public ComIUnknown {
  
public:
  WICPalette(IWICImagingFactory* factory)
  :ComIUnknown()
  {
    IWICPalette* palette = NULL;
    HRESULT hr = factory -> CreatePalette(&palette);
    if (SUCCEEDED(hr)) {
      set(palette);
    } else {
      throw IException("Failed to CreatePalette. HRESULT(0x%lx)", hr);  
    }
  }

  ~WICPalette()
  {
  }

  operator IWICPalette*()
  {
    return getPalette();
  }

  IWICPalette* getPalette()
  {
    IWICPalette* palette = (IWICPalette*)getIUnknown();
    if (palette) {
      return palette;
    } else {
      throw IException("IWICPalette is NULL.");
    }
  }
  
  void  initializePredefined( 
            __in WICBitmapPaletteType ePaletteType,
            __in BOOL fAddTransparentColor) 
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> InitializePredefined( 
            ePaletteType,
            fAddTransparentColor);
    if (FAILED(hr)) {
      throw IException("Failed to InitializePredefined. HRESULT(0x%lx)", hr);
    }
  }
  
  void  initializeCustom( 
            __in WICColor *pColors,
            __in UINT cCount)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> InitializeCustom( 
            pColors,
            cCount);
    if (FAILED(hr)) {
      throw IException("Failed to InitializeCustom. HRESULT(0x%lx)", hr);
    }
  }
        
  void  initializeFromBitmap( 
            __in IWICBitmapSource *pISurface,
            __in UINT cCount,
            __in BOOL fAddTransparentColor)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> InitializeFromBitmap( 
            pISurface,
            cCount,
            fAddTransparentColor);
    if (FAILED(hr)) {
      throw IException("Failed to InitializeFromBitmap. HRESULT(0x%lx)", hr);
    }
  }
        
  void  initializeFromPalette( 
            __in _opt IWICPalette *pIPalette)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> InitializeFromPalette( 
            pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to InitializeFromPalette. HRESULT(0x%lx)", hr);
    }
  }
        
  void  getType( 
            __out  WICBitmapPaletteType *pePaletteType)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> GetType( 
            pePaletteType);
    if (FAILED(hr)) {
      throw IException("Failed to GetType. HRESULT(0x%lx)", hr);
    }
  }
        
  void  getColorCount( 
            __out  UINT *pcCount)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> GetColorCount( 
            pcCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetColorCount. HRESULT(0x%lx)", hr);
    }
  }
        
  void  getColors( 
            __in UINT cCount,
            __out WICColor *pColors,
            __out  UINT *pcActualColors)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> GetColors( 
            cCount,
            pColors,
            pcActualColors);
    if (FAILED(hr)) {
      throw IException("Failed to GetColors. HRESULT(0x%lx)", hr);
    }
  }
        
  void  isBlackWhite( 
            __out  BOOL *pfIsBlackWhite)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> IsBlackWhite( 
            pfIsBlackWhite);
    if (FAILED(hr)) {
      throw IException("Failed to IsBlackWhite. HRESULT(0x%lx)", hr);
    }
  }
        
  void  isGrayscale( 
            __out  BOOL *pfIsGrayscale)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> IsGrayscale( 
            pfIsGrayscale);
    if (FAILED(hr)) {
      throw IException("Failed to IsGrayscale. HRESULT(0x%lx)", hr);
    }
  }
        
  void  hasAlpha( 
            __out  BOOL *pfHasAlpha)
  {
    IWICPalette* palette = getPalette();
    HRESULT hr = palette -> HasAlpha( 
            pfHasAlpha);
    if (FAILED(hr)) {
      throw IException("Failed to HasAlpha. HRESULT(0x%lx)", hr);
    }
  }
};

}
