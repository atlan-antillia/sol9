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
 *  Direct3DX10Font.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Args.h>
#include <sol/StrDef.h>
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d3d10_1.h>
#include <d3dx10.h>

namespace SOL {

class Direct3DX10Font : public ComIUnknown {
public:
  Direct3DX10Font(ID3D10Device*  pDevice,  
                  INT            height,
                  UINT           width,
                  UINT           weight,
                  UINT           mipLevels,
                  BOOL           italic,
                  UINT           charSet,
                  UINT           outputPrecision,
                  UINT           quality,
                  UINT           pitchAndFamily,
                  const TCHAR*   pFaceName)
  :ComIUnknown()
  {
    ID3DX10Font* font = NULL;
    HRESULT hr = D3DX10CreateFont(
        pDevice,  
        height,
        width,
        weight,
        mipLevels,
        italic,
        charSet,
        outputPrecision,
        quality,
        pitchAndFamily,
        pFaceName,
        &font);
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to D3DX10CreateFont. HRESULT(0x%lx)", hr);
    }
  }
  

public:
  Direct3DX10Font(ID3D10Device*  pDevice,  Args& args)
  :ComIUnknown()
  {
    ID3DX10Font* font = NULL;
    
    HRESULT hr = D3DX10CreateFont(
        pDevice,  
      (INT)args.get(XmNheight),
      (UINT)args.get(XmNwidth),
      (UINT)args.get(XmNweight),
      (UINT)args.get(XmNmipLevels),
      (BOOL)args.get(XmNitalic),
      (UINT)args.get(XmNcharSet),
      (UINT)args.get(XmNoutputPrecision),
      (UINT)args.get(XmNquality),
      (UINT)args.get(XmNpitchAndFamily),
      (const TCHAR*)args.get(XmNfaceName),
        &font);
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to D3DX10CreateFont. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct3DX10Font(ID3D10Device*  pDevice,  
        CONST D3DX10_FONT_DESC*   pDesc) 
  :ComIUnknown()
  {
    ID3DX10Font* font = NULL;
    
    HRESULT hr = D3DX10CreateFontIndirect( 
        pDevice,  
        pDesc, 
        &font);
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to D3DX10CreateFontIndirect. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3DX10Font()
  {
  }
  
  operator ID3DX10Font*()
  {
    return getFont();
  }
  
  ID3DX10Font* getFont()
  {
    ID3DX10Font* font = (ID3DX10Font*)getIUnknown();
    if (font) {
      return font;
    } else {
      throw IException("ID3DX10Font is NULL.");
    }
  }
    // ID3DX10Font
  void getDevice(ID3D10Device** ppDevice)
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font -> GetDevice(ppDevice);
    if (FAILED(hr)) {
      throw IException("Failed to GetDevice. HRESULT(0x%lx)", hr);
    }
  }
  
  void getDesc(D3DX10_FONT_DESC *pDesc)
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  BOOL getTextMetrics(TEXTMETRIC *pTextMetrics) 
  {
    ID3DX10Font* font = getFont();
    return font -> GetTextMetrics(pTextMetrics);

  }
  
//  BOOL GetTextMetricsW(TEXTMETRICW *pTextMetrics) 

  HDC getDC()
   {
     ID3DX10Font* font = getFont();
    return font ->GetDC();
   }

  void getGlyphData(UINT glyph, ID3D10ShaderResourceView** ppTexture, RECT *pBlackBox, POINT *pCellInc) 
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font ->  GetGlyphData(glyph, ppTexture, pBlackBox, pCellInc) ;
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
  
  void preloadCharacters(UINT first, UINT last) 
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font -> PreloadCharacters(first, last);
    if (FAILED(hr)) {
      throw IException("Failed to PreloadCharacters. HRESULT(0x%lx)", hr);
    }
  }
  
  void preloadGlyphs(UINT first, UINT last) 
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font -> PreloadGlyphs(first, last);
    if (FAILED(hr)) {
      throw IException("Failed to PreloadGlyphs. HRESULT(0x%lx)", hr);
    }
  }
  
  void preloadText(const TCHAR* pString, INT count)
  {
    ID3DX10Font* font = getFont();
    HRESULT hr = font -> PreloadText(pString, count);
    if (FAILED(hr)) {
      throw IException("Failed to PreloadText. HRESULT(0x%lx)", hr);
    }
  }
   
 
  INT drawText(LPD3DX10SPRITE pSprite, const TCHAR* pString, INT count, LPRECT pRect, UINT format, D3DXCOLOR color) 
  {
    ID3DX10Font* font = getFont();
    return font -> DrawText(pSprite, pString, count, pRect, format, color) ;
  }
};

}
