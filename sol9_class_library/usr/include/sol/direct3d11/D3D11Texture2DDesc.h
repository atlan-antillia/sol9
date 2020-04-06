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
 *  D3D101Texture2DDesc.h
 *
 *****************************************************************************/

#pragma once

#include <d3d11.h>
#include <d3dx11.h>

/*
typedef struct DXGI_SAMPLE_DESC
{
    UINT Count;
    UINT Quality;
} DXGI_SAMPLE_DESC;

ypedef struct D3D11_TEXTURE2D_DESC {
  UINT             Width;
  UINT             Height;
  UINT             MipLevels;
  UINT             ArraySize;
  DXGI_FORMAT      Format;
  DXGI_SAMPLE_DESC SampleDesc;
  D3D11_USAGE      Usage;
  UINT             BindFlags;
  UINT             CPUAccessFlags;
  UINT             MiscFlags;
} D3D11_TEXTURE2D_DESC;

*/
class D3D11Texture2DDesc {
public:
  D3D11_TEXTURE2D_DESC desc;
  
public:
  D3D11Texture2DDesc()
  {
    memset(&desc, 0, sizeof(desc));
  }
  
  D3D11Texture2DDesc(
      UINT width,
      UINT height, 
      UINT mipLevels, 
      UINT arraySize,
      DXGI_FORMAT format, 
      UINT sampleDescCount, 
      UINT sampleDescQuality,
      D3D11_USAGE usage,   
      UINT bindFlags,
      UINT cpuAccessFlags,  
      UINT miscFlags)
  {
    memset(&desc, 0, sizeof(desc));
    desc.Width         = width;
    desc.Height        = height;
    desc.MipLevels     = mipLevels;
    desc.ArraySize     = arraySize;
    desc.Format        = format;
    desc.SampleDesc.Count    = sampleDescCount;
    desc.SampleDesc.Quality = sampleDescQuality;

    desc.Usage         = usage;
    desc.BindFlags      = bindFlags;
    desc.CPUAccessFlags = cpuAccessFlags;
    desc.MiscFlags      = miscFlags;
    
  }
  
  void width(UINT w) {
    desc.Width         = w;
  }
  
  void height(UINT h) {
    desc.Height        = h;
  }
  
  void mipLevels(UINT m) {
    desc.MipLevels     = m;
  }
  void arraySize(UINT a) {
   desc.ArraySize     = a;
  }
  
  void format(DXGI_FORMAT f) {
    desc.Format        = f;
  }
  
  void sampleDescCount(UINT count) {
    desc.SampleDesc.Count    = count;
  }
  void sampleDescQuality(UINT quality) {
    desc.SampleDesc.Quality = quality;
  }
  
  void usage(D3D11_USAGE u) {
    desc.Usage         = u;
  }
  void bindFlags(UINT flags) {
    desc.BindFlags      = flags;
  }
  
  void cpuAccessFlags(UINT flags) {
    desc.CPUAccessFlags = flags;
  }
  void miscFlags(UINT flags) {
    desc.MiscFlags      = flags;
  }
  
  
  operator D3D11_TEXTURE2D_DESC*()
  {
    return getDesc();
  }
  
  D3D11_TEXTURE2D_DESC* getDesc()
  {
    return &desc;
  }
  
};

/*
//Usage:
D3D11Texture2DDesc descDepth;
 
descDepth.width(width);
descDepth.height(height);
descDepth.mipLevels(1);
descDepth.arraySize(1);
descDepth.format(DXGI_FORMAT_D24_UNORM_S8_UINT);
descDepth.sampleDescCount(1);
descDepth.sampleDescQuality(0);
descDepth.usage(D3D11_USAGE_DEFAULT);
descDepth.bindFlags(D3D11_BIND_DEPTH_STENCIL);

Direct3D11Texture2D texture2D = new Direct3D11Texture2D(d3d11Device, descDepth);
  */


