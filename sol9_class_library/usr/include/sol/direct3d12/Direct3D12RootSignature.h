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
 *  Direct3D12RootSignature.h
 *
 *****************************************************************************/

// 2016/10/10
// 2016/12/15 Updated

#pragma once

#include <sol/direct3d12/Direct3D12DeviceChild.h>
#include <sol/direct3d12/Direct3DBlob.h>

namespace SOL {

class Direct3D12RootSignature : public Direct3D12DeviceChild {
  
protected:
  Direct3D12RootSignature()
  :Direct3D12DeviceChild()
  {
  }
  
public:
  Direct3D12RootSignature(
      __in ID3D12Device*              device,
      __in D3D12_ROOT_SIGNATURE_DESC* desc)
  :Direct3D12DeviceChild()
  {
    //1 Check parameteers.
    if (device == nullptr || desc == nullptr) {
      throw IException("Invalid parameters.");
    }
    
    ID3DBlob* blobSignature = NULL;
    ID3DBlob* error         = NULL;
    HRESULT hr = D3D12SerializeRootSignature(desc, 
                    D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &error);
    if (FAILED(hr)) {
      release(error);
      throw IException("Failed to D3D12SerializeRootSignature. HRESULT(0x%lx)", hr);      
    }
    
    UINT nodeMask = 0; //Default nodeMask
    ID3D12RootSignature* signature = NULL;
    hr = device -> CreateRootSignature( 
            nodeMask, 
            blobSignature->GetBufferPointer(), 
            blobSignature->GetBufferSize(), 
            IID_PPV_ARGS(&signature));
   
    release(blobSignature);
    release(error);

    if (SUCCEEDED(hr)) {
        set(signature);
    } else {
      throw IException("Failed to CreateRootSignature. HRESULT(0x%lx)", hr);
    }
  }
  
    
protected:
  //2016/12/15 Modified to use numberOfConstantBufferView and numberOfShaderResourceView.
  //
  //Define your own serializeRootSignature method in the subclass derived from this class.
  virtual void serializeRootSignature(
    ID3DBlob**                  blobSignature, 
    UINT                        numberOfConstantBufferView = 1,
    UINT                        numberOfShaderResourceView = 1,  
    D3D12_DESCRIPTOR_RANGE_TYPE rangeType     = D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 
    D3D12_ROOT_PARAMETER_TYPE   parameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
    D3D12_ROOT_SIGNATURE_FLAGS  signatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
    )  
  {
    D3D12_DESCRIPTOR_RANGE range[2];
    memset(range, 0, sizeof(range));
    int i = 0;
      //ConstantBufferView
      range[i].RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;         
      range[i].NumDescriptors     = numberOfConstantBufferView;//1;
      range[i].BaseShaderRegister = 0;
      range[i].RegisterSpace      = 0;
      range[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    i++;
      //ShaderResourceView
      range[i].RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;       
      range[i].NumDescriptors     = numberOfShaderResourceView;//1;
      range[i].BaseShaderRegister = 0;
      range[i].RegisterSpace      = 0;
      range[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    D3D12_ROOT_PARAMETER param[2];
    memset(&param, 0, sizeof(param));
    i = 0;
      param[i].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
      param[i].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
      param[i].DescriptorTable.NumDescriptorRanges = 1;
      param[i].DescriptorTable.pDescriptorRanges   = &range[i];

    i++;
      param[i].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
      param[i].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
      param[i].DescriptorTable.NumDescriptorRanges = 1;
      param[i].DescriptorTable.pDescriptorRanges   = &range[i];
    
    D3D12_STATIC_SAMPLER_DESC sampler;
    memset(&sampler, 0, sizeof(sampler));
    
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
      sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; //D3D12_SHADER_VISIBILITY_PIXEL;
  
    
    D3D12_ROOT_SIGNATURE_DESC desc;
    memset(&desc, 0, sizeof(desc));
      desc.NumParameters     = _countof(param);
      desc.pParameters       = param;
      desc.NumStaticSamplers = 1;
      desc.pStaticSamplers   = &sampler;
      desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    
    ID3DBlob* errors = NULL;
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
      errors = NULL;
    }
    if (FAILED(hr)) {
      throw IException("Failed to D3D12SerializeRootSignature. HRESULT(0x%lx)", hr);      
    }
  }
  
public:
  //2016/12/15 Modified to take two arguments the number of constantBufferView and
  // the numberof of shaderResourceView
  Direct3D12RootSignature(
      __in ID3D12Device* device,
      __in UINT numberOfConstantBufferView = 1,
      __in UINT numberOfShaderResourceView = 1)
  :Direct3D12DeviceChild()
  {
    if (device == nullptr) {
       throw IException("ID3D12Device is NULL.");
    }
    
    ID3DBlob* blobSignature = NULL;

    //Create a RootSignature blob for ConstantBufferView.
    //2016/12/15 Updated to pass  numberOfConstantBufferView and numberOfShaderResourceView parameters.
    serializeRootSignature(&blobSignature,
                           numberOfConstantBufferView,
                           numberOfShaderResourceView);  
  
    UINT nodeMask = 0; //Default nodeMask
    ID3D12RootSignature* signature = NULL;

    HRESULT hr = device -> CreateRootSignature( 
            nodeMask, 
            blobSignature->GetBufferPointer(), 
            blobSignature->GetBufferSize(), 
            IID_PPV_ARGS(&signature));
      
    release(blobSignature);

    if (SUCCEEDED(hr)) {
      //
      set(signature);
    } else {
      throw IException("Failed to CreateRootSignature. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct3D12RootSignature(
      __in ID3D12Device* device,
      __in  UINT nodeMask,
      __in  const void *pBlobWithRootSignature,
      __in  SIZE_T blobLengthInBytes)
  :Direct3D12DeviceChild()
  {
    if (device == nullptr || pBlobWithRootSignature == nullptr,
       blobLengthInBytes < 1) {
        throw IException("Invalid parameters.");
    }
    
    ID3D12RootSignature* signature = NULL;
    HRESULT hr = device -> CreateRootSignature( 
            nodeMask,
            pBlobWithRootSignature,
            blobLengthInBytes,
           IID_PPV_ARGS(&signature));
    if (SUCCEEDED(hr)) {
      set(signature);
    } else {
      throw IException("Failed to ID3D12Device::CreateRootSignature. HRESULT(0x%lx)", hr);
    }
  }
 
  Direct3D12RootSignature(
    __in ID3D12RootSignature* rootSignature)
  :Direct3D12DeviceChild(rootSignature)
  {
  }
  
  ~Direct3D12RootSignature()
  { 
  }

   
  operator ID3D12RootSignature*()
  {
    return getRootSignature();
  }

  ID3D12RootSignature* getRootSignature()
  {
    ID3D12RootSignature* rootSignature = (ID3D12RootSignature*)getIUnknown();
    if (rootSignature) {
        return rootSignature;
    } else {
      throw IException("ID3D12RootSignature is NULL.");
    }
  }
};

}
    
