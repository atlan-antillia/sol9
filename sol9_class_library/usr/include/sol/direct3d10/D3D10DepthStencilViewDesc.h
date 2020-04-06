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
 *  D3D10DepthStencilViewDesc.h
 *
 *****************************************************************************/

#pragma once

#include <d3d10_1.h>
#include <d3dx10.h>
 
/*

typedef struct D3D10_DEPTH_STENCIL_VIEW_DESC
    {
    DXGI_FORMAT Format;
    D3D10_DSV_DIMENSION ViewDimension;
    union 
        {
        D3D10_TEX1D_DSV Texture1D;
        D3D10_TEX1D_ARRAY_DSV Texture1DArray;
        D3D10_TEX2D_DSV Texture2D;
        D3D10_TEX2D_ARRAY_DSV Texture2DArray;
        D3D10_TEX2DMS_DSV Texture2DMS;
        D3D10_TEX2DMS_ARRAY_DSV Texture2DMSArray;
        }   ;
    }   D3D10_DEPTH_STENCIL_VIEW_DESC;


*/

namespace SOL {
  
class D3D10DepthStencilViewDesc {
public:
  D3D10_DEPTH_STENCIL_VIEW_DESC desc;
public:
  D3D10DepthStencilViewDesc()
  {
    memset(&desc, 0, sizeof(desc));
  }
  
public:
  D3D10DepthStencilViewDesc(DXGI_FORMAT format, D3D10_DSV_DIMENSION viewDimension)
  {
    memset(&desc, 0, sizeof(desc));
    
    desc.Format = format;
    desc.ViewDimension = viewDimension;
    
  }
  
  void format(DXGI_FORMAT f) {
    desc.Format = f;
  }
  
  void viewDimension(D3D10_DSV_DIMENSION viewDimension) {
    desc.ViewDimension = viewDimension;
  }
  
  void texture1D(D3D10_TEX1D_DSV texture1D) {
    desc.Texture1D = texture1D;
  }
  
  void texture1DArray(D3D10_TEX1D_ARRAY_DSV texture1DArray) {
    desc.Texture1DArray = texture1DArray;
  }
  
  void texture2D(D3D10_TEX2D_DSV texture2D) {
    desc.Texture2D = texture2D;
  }
  void Texture2DArray(D3D10_TEX2D_ARRAY_DSV texture2DArray) {
    desc.Texture2DArray = texture2DArray;
  }
  
  void texture2DMS(D3D10_TEX2DMS_DSV texture2DMS) {
    desc.Texture2DMS = texture2DMS;
  }
  void texture2DMSArray(D3D10_TEX2DMS_ARRAY_DSV texture2DMSArray) {
    desc.Texture2DMSArray = texture2DMSArray;
  }
  
  operator D3D10_DEPTH_STENCIL_VIEW_DESC*()
  {
    return getDesc();
  }
  
  D3D10_DEPTH_STENCIL_VIEW_DESC* getDesc()
  {
    return &desc;
  }
};

}

/*
D3D10DepthStencilViewDesc descSVD(
    DXGI_FORMAT_D32_FLOAT, 
    D3D10_DSV_DIMENSION_TEXTURE2D);

Direct3D10DepthStencilView* stencilView = new Direct3D10DepthStencilView(d3d10Device, depthStencil, descSVD);

*/

