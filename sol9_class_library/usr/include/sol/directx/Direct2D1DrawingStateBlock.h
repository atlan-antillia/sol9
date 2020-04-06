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
 *  Direct2D1DrawingStateBlock.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Factory.h>

#include <sol/directx/Direct2D1Resource.h>

namespace SOL {


class Direct2D1DrawingStateBlock: public Direct2D1Resource
{
public:
  Direct2D1DrawingStateBlock(ID2D1Factory* factory,
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
        __in IDWriteRenderingParams *textRenderingParams)
  :Direct2D1Resource()
  {
    ID2D1DrawingStateBlock* block = NULL;
    HRESULT hr = factory ->  CreateDrawingStateBlock(
        drawingStateDescription,
        textRenderingParams,
        &block 
        );
    if (SUCCEEDED(hr)) {
      set(block);
    } else {
      throw IException("Failed to CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct2D1DrawingStateBlock(ID2D1Factory* factory,
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription)
       // __in IDWriteRenderingParams *textRenderingParams)
  :Direct2D1Resource()
  {
    ID2D1DrawingStateBlock* block = NULL;
    HRESULT hr = factory ->  CreateDrawingStateBlock(
        drawingStateDescription,
        //textRenderingParams,
        &block 
        );
    if (SUCCEEDED(hr)) {
      set(block);
    } else {
      throw IException("Failed to CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1DrawingStateBlock(ID2D1Factory* factory)
  :Direct2D1Resource()
  {
    ID2D1DrawingStateBlock* block = NULL;
    HRESULT hr = factory ->  CreateDrawingStateBlock(
        &block 
    );
    if (SUCCEEDED(hr)) {
      set(block);
    } else {
      throw IException("CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct2D1DrawingStateBlock()
  {
  }
  
  operator ID2D1DrawingStateBlock*()
  {
    return getBlock();
  }

  ID2D1DrawingStateBlock* getBlock()
  {
    ID2D1DrawingStateBlock* block = (ID2D1DrawingStateBlock*)getIUnknown();
    if (block) {
      return block;
    } else {
      throw IException("ID2D1DrawingStateBlock is NULL.");
    }
  }

  void getDescription(
        __out D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        )
  {
    ID2D1DrawingStateBlock* block = getBlock();
    block -> GetDescription(
        stateDescription 
        );
  }
  

   void setDescription(
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        )
  {
    ID2D1DrawingStateBlock* block = getBlock();
    block -> SetDescription(
        stateDescription 
        );
  }
        
  void setTextRenderingParams(
        __in_opt IDWriteRenderingParams *textRenderingParams = NULL 
        )
  {
    ID2D1DrawingStateBlock* block = getBlock();
    block -> SetTextRenderingParams(
        textRenderingParams 
        );
  }
    
  void getTextRenderingParams(
        __out IDWriteRenderingParams **textRenderingParams 
        )
  {
    ID2D1DrawingStateBlock* block = getBlock();
    block -> GetTextRenderingParams(
        textRenderingParams 
        );
  }
    
  void setDescription(
        CONST D2D1_DRAWING_STATE_DESCRIPTION &stateDescription 
        )
  {
    ID2D1DrawingStateBlock* block = getBlock();
    block -> SetDescription(
        stateDescription 
        );
  }
}; 

}
