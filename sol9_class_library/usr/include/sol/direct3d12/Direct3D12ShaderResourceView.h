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
 *  Direct3D12ShaderResourceView.h
 *
 *****************************************************************************/

// 2016/10/15

#pragma once

#include <sol/direct3d12/Direct3D12View.h>
#include <sol/direct3d12/Direct3D12CommonDescriptorHeap.h>

namespace SOL {

class Direct3D12ShaderResourceView : public Direct3D12View {
private:  
  D3D12_CPU_DESCRIPTOR_HANDLE  handle;
  
public:  
  Direct3D12ShaderResourceView(
      __in ID3D12Device*     device,
      __in D3D12_CPU_DESCRIPTOR_HANDLE srvHandle,  //Handle gotten from Direct3D12CommonDescriptorHeap
      __in ID3D12Resource*   texturedResource)
  :Direct3D12View(),
  handle(srvHandle)
  {
    if (device == nullptr || texturedResource == nullptr) {
      throw IException("Invalid parameter. ID3D12Device or ID3D12Resource is NULL.");
    }

    D3D12_RESOURCE_DESC textureDesc = texturedResource->GetDesc();
    
    //1 Define a shaderResourceViewDesc        
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));

    srvDesc.Format                    = textureDesc.Format; // DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension             = D3D12_SRV_DIMENSION_TEXTURE2D;   //SRV for texture2D
    srvDesc.Texture2D.MipLevels       = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.PlaneSlice      = 0;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0F;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    
    //2 Create a shaderResourceView from the texturedResource and shaderResourceViewDesc, and cpuHandle,
    device ->CreateShaderResourceView(
            texturedResource,
            &srvDesc,
            handle);
  }


  ~Direct3D12ShaderResourceView()
  {
  }

  operator D3D12_CPU_DESCRIPTOR_HANDLE()
  {
    return handle;
  }
  
  D3D12_CPU_DESCRIPTOR_HANDLE  getHandle()
  {
    return handle;
  }
};

}

