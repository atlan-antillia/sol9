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
 *  D3D12SubresourceData.h
 *
 *****************************************************************************/

// 2016/11/20

#pragma once

#include <d3d12.h>

namespace SOL {

class D3D12SubresourceData {
  UINT                   twidth;
  UINT                   theight;
private:
  DXGI_FORMAT            format; //2016/11/21
  
  D3D12_SUBRESOURCE_DATA subresource;
  
public:
  D3D12SubresourceData()
  {
    memset(&subresource, 0, sizeof(subresource));

  }
  
  ~D3D12SubresourceData()
  {
    uint8_t* data = (uint8_t*)subresource.pData;
    if (data) {
      delete [] data;
      subresource.pData = nullptr;
    }
  }

  void set(UINT rowPitch, UINT imageSize, uint8_t* data, DXGI_FORMAT f=DXGI_FORMAT_R8G8B8A8_UNORM)
  {
    format                 = f;
    subresource.pData      = data;
    subresource.RowPitch   = rowPitch;
    subresource.SlicePitch = imageSize;
  }
  
  void set(UINT w, UINT h, UINT rowPitch, UINT imageSize, uint8_t* data, DXGI_FORMAT f=DXGI_FORMAT_R8G8B8A8_UNORM)
  {
    twidth                 = w;
    theight                = h;
    format                 = f;
    subresource.pData      = data;
    subresource.RowPitch   = rowPitch;
    subresource.SlicePitch = imageSize;
  }
  
  operator D3D12_SUBRESOURCE_DATA()
  {
    return subresource;
  }

  operator D3D12_SUBRESOURCE_DATA&()
  {
    return subresource;
  }

  operator D3D12_SUBRESOURCE_DATA*()
  {
    return &subresource;
  }

  UINT getWidth()
  {
    return twidth;
  }
  
  UINT getHeight()
  {
    return theight;
  }
  
  DXGI_FORMAT getFormat()
  {
    return format;
  }
};

}

