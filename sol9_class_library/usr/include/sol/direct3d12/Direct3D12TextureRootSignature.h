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
 *  Direct3D12TextureRootSignature.h
 *
 *****************************************************************************/

// 2016/10/10

#pragma once

#include <sol/direct3d12/Direct3D12RootSignature.h>
#include <sol/direct3d12/Direct3DBlob.h>

namespace SOL {

class Direct3D12TextureRootSignature : public Direct3D12RootSignature {
    
  
protected:
  //Define your own serializeRootSignature method in the subclass derived from this class.
  virtual void serializeRootSignature(ID3DBlob** blobSignature)
  {
    
    D3D12_DESCRIPTOR_RANGE range[2];
    ZeroMemory(range, sizeof(range));
    int i = 0;
        range[i].RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
        range[i].NumDescriptors     = 1;
        range[i].BaseShaderRegister = 0;
        range[i].RegisterSpace      = 0;
        range[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    i++;
        range[i].RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
        range[i].NumDescriptors     = 1;
        range[i].BaseShaderRegister = 0;
        range[i].RegisterSpace      = 0;
        range[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    D3D12_ROOT_PARAMETER param[2];
    ZeroMemory(param, sizeof(param));
    i = 0;
        param[i].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        param[i].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_VERTEX; //D3D12_SHADER_VISIBILITY_ALL;//D3D12_SHADER_VISIBILITY_VERTEX;
        param[i].DescriptorTable.NumDescriptorRanges = 1;
        param[i].DescriptorTable.pDescriptorRanges   = &range[0];
    i++;
        param[i].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        param[i].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_PIXEL;//D3D12_SHADER_VISIBILITY_ALL;;//D3D12_SHADER_VISIBILITY_PIXEL;
        param[i].DescriptorTable.NumDescriptorRanges = 1;
        param[i].DescriptorTable.pDescriptorRanges   = &range[1];

   
    D3D12_STATIC_SAMPLER_DESC sampler = {};
        sampler.Filter           = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        sampler.AddressU         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        sampler.AddressV         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        sampler.AddressW         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        sampler.MipLODBias       = 0;
        sampler.MaxAnisotropy    = 0;
        sampler.ComparisonFunc   = D3D12_COMPARISON_FUNC_NEVER;
        sampler.BorderColor      = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
        sampler.MinLOD           = 0.0f;
        sampler.MaxLOD           = D3D12_FLOAT32_MAX;
        sampler.ShaderRegister   = 0;
        sampler.RegisterSpace    = 0;
        sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

    D3D12_ROOT_SIGNATURE_DESC desc;
    ZeroMemory(&desc, sizeof(desc));

    desc.NumParameters     = _countof(param);
        desc.pParameters       = param;
        desc.NumStaticSamplers = 1;
        desc.pStaticSamplers   = &sampler;
        desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    
    ID3DBlob* errors         = NULL;
    HRESULT hr = D3D12SerializeRootSignature(&desc, 
                    D3D_ROOT_SIGNATURE_VERSION_1, blobSignature, &errors);
    if (errors) {
      const char* msg = (const char*)errors->GetBufferPointer();
      const char* title = "Error";
      if (strstr(msg, "warning")) {
        title = "Warning";
      }
      MessageBoxA(NULL,(const char*)msg, title, MB_OK);
      errors->Release();
    }
    if (FAILED(hr)) {
      throw IException("Failed to D3D12SerializeRootSignature. HRESULT(0x%lx)", hr);      
    }
  }

public:
  Direct3D12TextureRootSignature(
      __in ID3D12Device* device)
  :Direct3D12RootSignature(device)
  {

  }

  
  Direct3D12TextureRootSignature(
    __in ID3D12RootSignature* rootSignature)
  :Direct3D12RootSignature(rootSignature)
  {
  }
  
  ~Direct3D12TextureRootSignature()
  { 
  }
  
};

}
    
