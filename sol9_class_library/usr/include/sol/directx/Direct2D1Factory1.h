/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct2D1Factory1.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Factory.h>
#include <d2d1_1.h>


namespace SOL {
  
class Direct2D1Factory1: public Direct2D1Factory  {

public:
  Direct2D1Factory1()
  :Direct2D1Factory()
  {
    ID2D1Factory1* factory1 = NULL;
    //D2D1_DEVICE_CONTEXT_OPTIONS deviceOptions = D2D1_DEVICE_CONTEXT_OPTIONS_NONE;
 
    HRESULT hr = D2D1CreateFactory(
              D2D1_FACTORY_TYPE_SINGLE_THREADED, 
              __uuidof(ID2D1Factory1),
              //&deviceOptions,
              (void**)&factory1);
    
    if (SUCCEEDED(hr)) {
      set(factory1);
    } else {
      throw IException("Failed  to D2D1CreateFactory. HRESULT(0x%lx)", hr);
    } 
  }

  ~Direct2D1Factory1()
  {
  }

  operator ID2D1Factory1*()
  {
    return getFactory1();
  }

  
  ID2D1Factory1* getFactory1()
  {
    ID2D1Factory1* factory = (ID2D1Factory1*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("ID2D1Factory1 is NULL.");
    }
  }
  
/*
  void createDevice(
        _In_ IDXGIDevice*           dxgiDevice,
        _COM_Outptr_ ID2D1Device1** d2dDevice1)
  {
    ID2D1Factory2* factory2 = getFactory2();
    HRESULT hr = factory2 -> CreateDevice(
              dxgiDevice,
              d2dDevice1);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDevice. HRESULT(0x%lx)", hr);
    }
  }
  void CreateDevice(
        _In_ IDXGIDevice *dxgiDevice,
        _COM_Outptr_ ID2D1Device **d2dDevice 
        )
   
  void CreateStrokeStyle(
        _In_ CONST D2D1_STROKE_STYLE_PROPERTIES1 *strokeStyleProperties,
        _In_reads_opt_(dashesCount) CONST FLOAT *dashes,
        UINT32 dashesCount,
        _COM_Outptr_ ID2D1StrokeStyle1 **strokeStyle 
        )
  
  //  using ID2D1Factory::CreateStrokeStyle;
    
  void CreatePathGeometry(
        _COM_Outptr_ ID2D1PathGeometry1 **pathGeometry 
        )
  //using ID2D1Factory::CreatePathGeometry;
    
  void CreateDrawingStateBlock(
        _In_opt_ CONST D2D1_DRAWING_STATE_DESCRIPTION1 *drawingStateDescription,
        _In_opt_ IDWriteRenderingParams *textRenderingParams,
        _COM_Outptr_ ID2D1DrawingStateBlock1 **drawingStateBlock 
        )
  //using ID2D1Factory::CreateDrawingStateBlock;
  */
  
  void createGdiMetafile(
        _In_ IStream *metafileStream,
        _COM_Outptr_ ID2D1GdiMetafile **metafile 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1->CreateGdiMetafile(
      metafileStream,
      metafile
    );
  }
  
  void registerEffectFromStream(
        _In_ REFCLSID classId,
        _In_ IStream *propertyXml,
        _In_reads_opt_(bindingsCount) CONST D2D1_PROPERTY_BINDING *bindings,
        UINT32 bindingsCount,
        _In_ CONST PD2D1_EFFECT_FACTORY effectFactory 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1 ->RegisterEffectFromStream(
          classId,
          propertyXml,
          bindings,
          bindingsCount,
          effectFactory 
        );
  }

  void registerEffectFromString(
        _In_ REFCLSID classId,
        _In_ PCWSTR propertyXml,
        _In_reads_opt_(bindingsCount) CONST D2D1_PROPERTY_BINDING *bindings,
        UINT32 bindingsCount,
        _In_ CONST PD2D1_EFFECT_FACTORY effectFactory 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1 -> RegisterEffectFromString(
          classId,
          propertyXml,
          bindings,
          bindingsCount,
          effectFactory 
        );
  }

  void unregisterEffect(
        _In_ REFCLSID classId 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1 -> UnregisterEffect(
          classId 
        );
  }

  void getRegisteredEffects(
        _Out_writes_to_opt_(effectsCount, *effectsReturned) CLSID *effects,
        UINT32 effectsCount,
        _Out_opt_ UINT32 *effectsReturned,
        _Out_opt_ UINT32 *effectsRegistered 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1 -> GetRegisteredEffects(
          effects,
          effectsCount,
          effectsReturned,
          effectsRegistered 
        );   
  }
  
  void getEffectProperties(
        _In_ REFCLSID effectId,
        _COM_Outptr_ ID2D1Properties **properties 
        )
  {
    ID2D1Factory1* factory1 = getFactory1();
    factory1 -> GetEffectProperties(
        effectId,
        properties 
        );
  }
  
  void  createStrokeStyle(
        CONST D2D1_STROKE_STYLE_PROPERTIES1 &strokeStyleProperties,
        _In_reads_opt_(dashesCount) CONST FLOAT *dashes,
        UINT32 dashesCount,
        _COM_Outptr_ ID2D1StrokeStyle1 **strokeStyle 
        )  
    {
      ID2D1Factory1* factory1 = getFactory1();
      HRESULT hr = factory1 -> CreateStrokeStyle(&strokeStyleProperties, dashes, dashesCount, strokeStyle);
      if (FAILED(hr)) {
        throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
      }
    }
    
  void createDrawingStateBlock(
        CONST D2D1_DRAWING_STATE_DESCRIPTION1 &drawingStateDescription,
        _COM_Outptr_ ID2D1DrawingStateBlock1 **drawingStateBlock 
        )  
    {
      ID2D1Factory1* factory1 = getFactory1();
      HRESULT hr = factory1 -> CreateDrawingStateBlock(&drawingStateDescription, NULL, drawingStateBlock);
      if (FAILED(hr)) {
        throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
      }
    }
    
  void createDrawingStateBlock(
        _COM_Outptr_ ID2D1DrawingStateBlock1 **drawingStateBlock 
        )  
    {
      ID2D1Factory1* factory1 = getFactory1();
      HRESULT hr = factory1 -> CreateDrawingStateBlock(NULL, NULL, drawingStateBlock);
      if (FAILED(hr)) {
        throw IException("Failed to CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
      }
    }
};

  
}
