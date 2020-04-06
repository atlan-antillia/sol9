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
 *  Direct2D1GeometrySink.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1SimplifiedGeometrySink.h>

namespace SOL {

class Direct2D1GeometrySink :public Direct2D1SimplifiedGeometrySink
{
public:
  Direct2D1GeometrySink(ID2D1PathGeometry* geometry)
  :Direct2D1SimplifiedGeometrySink()
  {
    ID2D1GeometrySink* sink = NULL;
    HRESULT hr = geometry -> Open(&sink);
    
    if (SUCCEEDED(hr)) {
      set(sink);
    } else {
      throw IException("Failed to Open. HRESULT(0x%lx)", hr);
    }
  }

  operator ID2D1GeometrySink*()
  {
    return getSink();
  }

  ID2D1GeometrySink* getSink()
  {
    ID2D1GeometrySink* sink = (ID2D1GeometrySink*)getIUnknown();
    if (sink) {
      return sink;
    } else {
      throw IException("ID2D1GeometrySink is NULL.");
    }
  }
  

  void addLine(
        D2D1_POINT_2F point 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddLine(point);
  }
    
  void addBezier(
        __in CONST D2D1_BEZIER_SEGMENT *bezier 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddBezier(bezier);
  }
    
  void addQuadraticBezier(
        __in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddQuadraticBezier(bezier);
  }

  void addQuadraticBeziers(
        __in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddQuadraticBeziers(
                    beziers,
                    beziersCount 
                   );
  }

  void addArc(
        __in CONST D2D1_ARC_SEGMENT *arc 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddArc(arc);
  }

  void addBezier(
        CONST D2D1_BEZIER_SEGMENT &bezier 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddBezier(bezier);
  }
    
  void addQuadraticBezier(
        CONST D2D1_QUADRATIC_BEZIER_SEGMENT &bezier 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddQuadraticBezier(bezier);
  }
        
    
  void addArc(
        CONST D2D1_ARC_SEGMENT &arc 
        )
  {
    ID2D1GeometrySink* sink = getSink();
    sink -> AddArc(arc);
  }
}; 

}

