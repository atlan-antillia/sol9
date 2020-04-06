
#pragma once

#include <sol/direct3d12/Direct3D12DescriptorHeap.h>

namespace SOL {

class Direct3D12Sampler :public Direct3D12DescriptorHeap {
protected:
  
  //Define your own getSampleDesc method in the subclass derived from this class.
  virtual D3D12_SAMPLER_DESC getSamplerDesc()
  {
    D3D12_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter        = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU      = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressV      = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressW      = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.MinLOD        = 0;
    samplerDesc.MaxLOD        = D3D12_FLOAT32_MAX;
    samplerDesc.MipLODBias    = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    return samplerDesc;
  }
  
public:
  Direct3D12Sampler(
          __in ID3D12Device*               device,
          __in UINT                        bufferCount=1,
          __in D3D12_DESCRIPTOR_HEAP_TYPE  type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
          __in D3D12_DESCRIPTOR_HEAP_FLAGS flag = D3D12_DESCRIPTOR_HEAP_FLAG_NONE)
  :Direct3D12DescriptorHeap(
              device,
              bufferCount,
              type,
              flag)
  {
    Printf(_T("Sampler::Sampler\n"));
    // Describe and create a sampler.
    D3D12_SAMPLER_DESC samplerDesc = getSamplerDesc();
    device->CreateSampler(&samplerDesc, getCPUDescriptorHandleForHeapStart());
  }

public:
  Direct3D12Sampler(
          __in ID3D12Device*               device,
          __in D3D12_SAMPLER_DESC*         samplerDesc,
          __in UINT                        bufferCount=1,
          __in D3D12_DESCRIPTOR_HEAP_TYPE  type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
          __in D3D12_DESCRIPTOR_HEAP_FLAGS flag = D3D12_DESCRIPTOR_HEAP_FLAG_NONE)
  :Direct3D12DescriptorHeap(
              device,
              bufferCount,
              type,
              flag)
  {
    device->CreateSampler(samplerDesc, getCPUDescriptorHandleForHeapStart());
  }

};

}

