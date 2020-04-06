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
 *  Direct2D1Brush.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Resource.h>

namespace SOL {

class Direct2D1Brush : public Direct2D1Resource
{
public:
  Direct2D1Brush()
  :Direct2D1Resource()
  {
  }

  operator ID2D1Brush*()
  {
    return getBrush();
  }

  virtual ID2D1Brush* getBrush()
  {
    ID2D1Brush* brush = (ID2D1Brush*)getIUnknown();
    if (brush) {
      return brush;
    } else {
      throw IException("ID2D1Brush is NULL.");
    }
  }
  

  void setOpacity(
        FLOAT opacity 
        )
  {
    ID2D1Brush* brush = getBrush();
    brush -> SetOpacity(
        opacity 
        );
  }

  void setTransform(
        __in CONST D2D1_MATRIX_3X2_F *transform 
        )
  {
    ID2D1Brush* brush = getBrush();
    brush -> SetTransform(
        transform 
        );
  }

    
  FLOAT getOpacity(
        )
    {
    ID2D1Brush* brush = getBrush();
    return brush -> GetOpacity();
  }

    
  void getTransform(
        __out D2D1_MATRIX_3X2_F *transform 
        )
  {
    ID2D1Brush* brush = getBrush();
    brush -> GetTransform(
        transform 
        );
  }

  void setTransform(
        CONST D2D1_MATRIX_3X2_F &transform 
        )
  {
    ID2D1Brush* brush = getBrush();
    brush -> SetTransform(
        transform 
        );
  }
};

}

