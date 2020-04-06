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
 *  Direct2D1SimplifiedGeometrySink.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1RenderTarget.h>

#include <sol/directx/Direct2D1Geometry.h>
#include <sol/directx/Direct2D1Resource.h>


namespace SOL {

class Direct2D1SimplifiedGeometrySink : public ComIUnknown
{
public:
  Direct2D1SimplifiedGeometrySink()
  :ComIUnknown()
  {
  }

  ~Direct2D1SimplifiedGeometrySink()
  {
  }

  operator ID2D1SimplifiedGeometrySink*()
  {
    return getSink();
  }

  virtual ID2D1SimplifiedGeometrySink* getSink()
  {
    ID2D1SimplifiedGeometrySink* sink = (ID2D1SimplifiedGeometrySink*)getIUnknown();
    if (sink) {
      return sink;
    } else {
      throw IException("ID2D1SimplifiedGeometrySink is NULL.");
    }
  }


  void setFillMode(
        D2D1_FILL_MODE fillMode 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> SetFillMode(
        fillMode 
        );
  }
  
  void setSegmentFlags(
        D2D1_PATH_SEGMENT vertexFlags 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> SetSegmentFlags(
        vertexFlags 
        );
  }
    
  void beginFigure(
        D2D1_POINT_2F startPoint,
        D2D1_FIGURE_BEGIN figureBegin 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> BeginFigure(
        startPoint,
        figureBegin 
        );
  }
    
  void addLines(
        __in CONST D2D1_POINT_2F *points,
        UINT pointsCount 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> AddLines(
        points,
        pointsCount 
        );
  }
    
  void addBeziers(
        __in CONST D2D1_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> AddBeziers(
        beziers,
        beziersCount 
        );
  }
    
  void endFigure(
        D2D1_FIGURE_END figureEnd 
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    sink -> EndFigure(
        figureEnd 
        );
  }
    
  void close(
        )
  {
    ID2D1SimplifiedGeometrySink* sink = getSink();
    HRESULT hr = sink -> Close();
    if (FAILED(hr)) {
      throw IException("Failed to Close. HRESULT(0x%lx)", hr);
    }
  }
 
}; 
}

