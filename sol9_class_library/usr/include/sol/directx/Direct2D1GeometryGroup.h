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
 *  Direct2D1GeometryGroup.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Geometry.h>


namespace SOL {

class Direct2D1GeometryGroup : public Direct2D1Geometry
{
public:
  Direct2D1GeometryGroup(ID2D1Factory* factory,        
        D2D1_FILL_MODE fillMode,
        ID2D1Geometry **geometries,
        UINT geometriesCount)
  :Direct2D1Geometry()
  {
    ID2D1GeometryGroup* group = NULL;
    HRESULT hr = factory -> CreateGeometryGroup(
        fillMode,
        geometries,
        geometriesCount,
        &group 
    );
    if (SUCCEEDED(hr)) {
      set(group);
    } else {
      throw IException("Failed to CreateGeometryGroup. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1GeometryGroup()
  {
  }

  operator ID2D1GeometryGroup*()
  {
    return getGroup();
  }

  ID2D1GeometryGroup* getGroup()
  {
    ID2D1GeometryGroup* group = (ID2D1GeometryGroup*)getIUnknown();
    if (group) {
      return group;
    } else {
      throw IException("ID2D1GeometryGroup is NULL");
    }
  }

  D2D1_FILL_MODE getFillMode(
        )
  {
    ID2D1GeometryGroup* group = getGroup();
    return group -> GetFillMode();    
  }
  
  UINT32 getSourceGeometryCount(
        )
  {
    ID2D1GeometryGroup* group = getGroup();
    return group -> GetSourceGeometryCount();    
  }
    
  void getSourceGeometries(
        __out ID2D1Geometry **geometries,
        UINT geometriesCount 
        )
  {
    ID2D1GeometryGroup* group = getGroup();
    group -> GetSourceGeometries(
        geometries,
        geometriesCount 
        );
  }
  
};
  
}
