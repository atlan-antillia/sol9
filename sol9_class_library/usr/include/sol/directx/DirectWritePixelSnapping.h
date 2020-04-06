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
 *  DirectWritePixelSnapping.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>


namespace SOL {

class DirectWritePixelSnapping : public ComIUnknown
{
public:
  DirectWritePixelSnapping()
  :ComIUnknown()
  {
  }
  

  operator IDWritePixelSnapping*()
  {
    return getSnapping();
  }

  IDWritePixelSnapping* getSnapping()
  {
    IDWritePixelSnapping* snapping = (IDWritePixelSnapping*)getSnapping();
    if (snapping) {
      return snapping;
    } else {
      throw IException("IDWritePixelSnapping is NULL.");
    }
  }
  
  void isPixelSnappingDisabled(
        void* clientDrawingContext,
        __out BOOL* isDisabled
        )
  {
    IDWritePixelSnapping* snapping = getSnapping();
    HRESULT hr = snapping -> IsPixelSnappingDisabled(
        clientDrawingContext,
        isDisabled
        );
    if (FAILED(hr)) {
      throw IException("Faield to IsPixelSnappingDisabled. HRESULT(0x%lx)", hr);
    }
  }
  
  void getCurrentTransform(
        void* clientDrawingContext,
        __out DWRITE_MATRIX* transform
        )
  {
    IDWritePixelSnapping* snapping = getSnapping();
    HRESULT hr = snapping -> GetCurrentTransform(
        clientDrawingContext,
        transform
        );
    if (FAILED(hr)) {
      throw IException("Faield to GetCurrentTransform. HRESULT(0x%lx)", hr);
    }
  }

  void getPixelsPerDip(
        void* clientDrawingContext,
        __out FLOAT* pixelsPerDip
        )
  {
    IDWritePixelSnapping* snapping = getSnapping();
    HRESULT hr = snapping -> GetPixelsPerDip(
        clientDrawingContext,
        pixelsPerDip
        );
    if (FAILED(hr)) {
      throw IException("Faield to GetPixelsPerDip. HRESULT(0x%lx)", hr);
    }
  }

};


}
