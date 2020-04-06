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
 *  Direct2D1Geometry.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>


namespace SOL {

class Direct2D1Geometry : public Direct2D1Resource
{
public:
  Direct2D1Geometry()
  :Direct2D1Resource()
  {
  }

public:
  Direct2D1Geometry(ID2D1TransformedGeometry* transformGeometry)
  :Direct2D1Resource()
  {
    ID2D1Geometry* geometry = NULL;
    transformGeometry -> GetSourceGeometry(
        &geometry 
        );
  }
  
  operator ID2D1Geometry*()
  {
    return getGeometry();
  }

  virtual ID2D1Geometry* getGeometry()
  {
    ID2D1Geometry* geometry = (ID2D1Geometry*)getIUnknown();
    if (geometry) {
      return geometry;
    } else {
      throw IException("ID2D1Geometry is NULL.");
    }
  }
  
  void getBounds(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out D2D1_RECT_F *bounds 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetBounds(
        worldTransform,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetBounds. HRESULT(0x%lx)", hr);
    }
  }
  
  void getWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out D2D1_RECT_F *bounds 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetWidenedBounds(
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetWidenedBounds. HRESULT(0x%lx)", hr);
    }
  }
    
  void strokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> StrokeContainsPoint(
        point,
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to StrokeContainsPoint. HRESULT(0x%lx)", hr);
    }
  }
    
  void fillContainsPoint(
        D2D1_POINT_2F point,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> FillContainsPoint(
        point,
        worldTransform,
        flatteningTolerance,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to FillContainsPoint. HRESULT(0x%lx)", hr);
    }
  }
    
  void compareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __out D2D1_GEOMETRY_RELATION *relation 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CompareWithGeometry(
        inputGeometry,
        inputGeometryTransform,
        flatteningTolerance,
        relation 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CompareWithGeometry. HRESULT(0x%lx)", hr);
    }
  }
    
  void simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Simplify(
        simplificationOption,
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Simplify. HRESULT(0x%lx)", hr);
    }
  }
    
  void tessellate(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1TessellationSink *tessellationSink 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Tessellate(
        worldTransform,
        flatteningTolerance,
        tessellationSink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Tessellate. HRESULT(0x%lx)", hr);
    }
  }
    
  void combineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CombineWithGeometry(
        inputGeometry,
        combineMode,
        inputGeometryTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CombineWithGeometry. HRESULT(0x%lx)", hr);
    }
  }
    
  void outline(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Outline(
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Outline. HRESULT(0x%lx)", hr);
    }
  }
    
  void computeArea(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *area 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeArea(
        worldTransform,
        flatteningTolerance,
        area 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeArea. HRESULT(0x%lx)", hr);
    }
  }
    
  void computeLength(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *length 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeLength(
        worldTransform,
        flatteningTolerance,
        length 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeLength. HRESULT(0x%lx)", hr);
    }
  }
    
  void computePointAtLength(
        FLOAT length,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputePointAtLength(
        length,
        worldTransform,
        flatteningTolerance,
        point,
        unitTangentVector 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputePointAtLength. HRESULT(0x%lx)", hr);
    }
  }
    
  void widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Widen(
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Widen. HRESULT(0x%lx)", hr);
    }
  }
    
  void getBounds(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out D2D1_RECT_F *bounds 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetBounds(
        worldTransform,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetBounds. HRESULT(0x%lx)", hr);
    }
  }

  void getWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out D2D1_RECT_F *bounds 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetWidenedBounds(
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetWidenedBounds. HRESULT(0x%lx)", hr);
    }
  }

  void getWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out D2D1_RECT_F *bounds 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetWidenedBounds(
        strokeWidth,
        strokeStyle,
        worldTransform,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetWidenedBounds. HRESULT(0x%lx)", hr);
    }
  }

  void getWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out D2D1_RECT_F *bounds 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetWidenedBounds(
        strokeWidth,
        strokeStyle,
        worldTransform,
        bounds 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetWidenedBounds. HRESULT(0x%lx)", hr);
    }
  }

  void strokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        )
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> StrokeContainsPoint(
        point,
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to StrokeContainsPoint. HRESULT(0x%lx)", hr);
    }
  }

    //
  void strokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out BOOL *contains 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> StrokeContainsPoint(
        point,
        strokeWidth,
        strokeStyle,
        worldTransform,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to StrokeContainsPoint. HRESULT(0x%lx)", hr);
    }
  }
    
  void strokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out BOOL *contains 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> StrokeContainsPoint(
        point,
        strokeWidth,
        strokeStyle,
        worldTransform,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to StrokeContainsPoint. HRESULT(0x%lx)", hr);
    }
  }
    
  void fillContainsPoint(
        D2D1_POINT_2F point,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> FillContainsPoint(
        point,
        worldTransform,
        flatteningTolerance,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to FillContainsPoint. HRESULT(0x%lx)", hr);
    }
  }

  void fillContainsPoint(
        D2D1_POINT_2F point,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out BOOL *contains 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> FillContainsPoint(
        point,
        worldTransform,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to FillContainsPoint. HRESULT(0x%lx)", hr);
    }
  }
    
  void fillContainsPoint(
        D2D1_POINT_2F point,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out BOOL *contains 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> FillContainsPoint(
        point,
        worldTransform,
        contains 
        );
    if (FAILED(hr)) {
      throw IException("Failed to FillContainsPoint. HRESULT(0x%lx)", hr);
    }
  }

  void compareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        FLOAT flatteningTolerance,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CompareWithGeometry(
        inputGeometry,
        inputGeometryTransform,
        flatteningTolerance,
        relation 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CompareWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void compareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CompareWithGeometry(
        inputGeometry,
        inputGeometryTransform,
        relation 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CompareWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void compareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CompareWithGeometry(
        inputGeometry,
        inputGeometryTransform,
        relation 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CompareWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Simplify(
        simplificationOption,
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Simplify. HRESULT(0x%lx)", hr);
    }
  }

  void simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Simplify(
        simplificationOption,
        worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Simplify. HRESULT(0x%lx)", hr);
    }
  }

  void simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Simplify(
        simplificationOption,
        worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Simplify. HRESULT(0x%lx)", hr);
    }
  }
    
  void tessellate(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1TessellationSink *tessellationSink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Tessellate(
        worldTransform,
        flatteningTolerance,
        tessellationSink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Tessellate. HRESULT(0x%lx)", hr);
    }
  }

  void tessellate(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1TessellationSink *tessellationSink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Tessellate(
        worldTransform,
        tessellationSink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Tessellate. HRESULT(0x%lx)", hr);
    }
  }

  void tessellate(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1TessellationSink *tessellationSink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Tessellate(
        worldTransform,
        tessellationSink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Tessellate. HRESULT(0x%lx)", hr);
    }
  }

  void combineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CombineWithGeometry(
        inputGeometry,
        combineMode,
        inputGeometryTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CombineWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void combineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CombineWithGeometry(
        inputGeometry,
        combineMode,
        inputGeometryTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CombineWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void combineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> CombineWithGeometry(
        inputGeometry,
        combineMode,
        inputGeometryTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CombineWithGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void outline(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Outline(
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Outline. HRESULT(0x%lx)", hr);
    }
  }

  void outline(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Outline(
        worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Outline. HRESULT(0x%lx)", hr);
    }
  }

  void outline(
         CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Outline(
         worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Outline. HRESULT(0x%lx)", hr);
    }
  }

  void computeArea(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *area 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeArea(
        worldTransform,
        flatteningTolerance,
        area 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeArea. HRESULT(0x%lx)", hr);
    }
  }

  void computeArea(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out FLOAT *area 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeArea(
        worldTransform,
        area 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeArea. HRESULT(0x%lx)", hr);
    }
  }

  void computeArea(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out FLOAT *area 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeArea(
        worldTransform,
        area 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeArea. HRESULT(0x%lx)", hr);
    }
  }

  void computeLength(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *length 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeLength(
        worldTransform,
        flatteningTolerance,
        length 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeLength. HRESULT(0x%lx)", hr);
    }
  }

  void computeLength(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out FLOAT *length 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeLength(
        worldTransform,
        length 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeLength. HRESULT(0x%lx)", hr);
    }
  }

  void computeLength(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out FLOAT *length 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputeLength(
        worldTransform,
        length 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputeLength. HRESULT(0x%lx)", hr);
    }
  }

  void computePointAtLength(
        FLOAT length,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputePointAtLength(
        length,
        worldTransform,
        flatteningTolerance,
        point,
        unitTangentVector 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputePointAtLength. HRESULT(0x%lx)", hr);
    }
  }

  void computePointAtLength(
        FLOAT length,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputePointAtLength(
        length,
        worldTransform,
        point,
        unitTangentVector 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputePointAtLength. HRESULT(0x%lx)", hr);
    }
  }

  void computePointAtLength(
        FLOAT length,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> ComputePointAtLength(
        length,
        worldTransform,
        point,
        unitTangentVector 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ComputePointAtLength. HRESULT(0x%lx)", hr);
    }
  }

  void widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Widen(
        strokeWidth,
        strokeStyle,
        worldTransform,
        flatteningTolerance,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Widen. HRESULT(0x%lx)", hr);
    }
  }

  void widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry ->  Widen(
        strokeWidth,
        strokeStyle,
        worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Widen. HRESULT(0x%lx)", hr);
    }
  }

  void widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) 
  {
    ID2D1Geometry* geometry = getGeometry();
    HRESULT hr = geometry -> Widen(
        strokeWidth,
        strokeStyle,
        worldTransform,
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Widen. HRESULT(0x%lx)", hr);
    }
  }

}; 

}


