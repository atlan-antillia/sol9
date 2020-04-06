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
 *  Direct3D12PipelineLibrary.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12DeviceChild.h>

namespace SOL {

class Direct3D12PipelineLibrary : public Direct3D12DeviceChild {
    
public:
  Direct3D12PipelineLibrary(
            __in ID3D12Device1* device1,
            __in  const void *pLibraryBlob,
            __in SIZE_T blobLength,
            __in REFIID riid)
  :Direct3D12DeviceChild()
  {
    ID3D12PipelineLibrary* library = NULL;
    if (device1) {
      HRESULT hr = device1 ->CreatePipelineLibrary( 
            pLibraryBlob,
            blobLength,
            riid,
            &pipelineLibrary);
      if (SUCCEEDED(hr)) {
        set(library);
      } else {
        throw IException("Failed to ID3D12Device1::CreatePipelineLibrary. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("ID3D12Device1 is NULL");
    }
  }
  
  ~Direct3D12PipelineLibrary()
  { 
  }

   
  operator ID3D12PipelineLibrary*()
  {
    return getPipelineLibrary();
  }

  ID3D12PipelineLibrary* getPipelineLibrary()
  {
    ID3D12PipelineLibrary* library = (ID3D12PipelineLibrary*)getIUnknown();
    if (library) {
        return library;
    } else {
      throw IException("ID3D12Device1 is NULL.");
    }
  }

  void storePipeline( 
            _In_opt_  LPCWSTR pName,
            _In_  ID3D12PipelineState *pPipeline)
  {
    ID3D12PipelineLibrary* library = getPipelineLibrary();
    HRESULT hr = library->StorePipeline( 
            pName,
            pPipeline);
    if (FAILED(hr)) {
      throw IException("Faild to ID3D12PipelineState::StorePipeline. HRESULT(0x%lx)", hr);
    }
  }
        
  void loadGraphicsPipeline( 
            _In_  LPCWSTR pName,
            _In_  const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppPipelineState)
  {
    ID3D12PipelineLibrary* library = getPipelineLibrary();
    HRESULT hr = library -> LoadGraphicsPipeline( 
            pName,
            pDesc,
            riid,
            ppPipelineState);
    if (FAILED(hr)) {
     throw IException("Faild to ID3D12PipelineLibrary::LoadGraphicsPipeline. HRESULT(0x%lx)", hr);
    }
  }
        
  void loadComputePipeline( 
            _In_  LPCWSTR pName,
            _In_  const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppPipelineState)
  {
    ID3D12PipelineLibrary* library = getPipelineLibrary();
    HRESULT hr = library -> LoadComputePipeline( 
            pName,
            pDesc,
            riid,
            ppPipelineState);
    if (FAILED(hr)) {
      throw IException("Faild to ID3D12PipelineLibrary::LoadComputePipeline. HRESULT(0x%lx)", hr);
    }
  }
        
  SIZE_T getSerializedSize()
  {
    ID3D12PipelineLibrary* library = getPipelineLibrary();
    return library->GetSerializedSize();
  }
        
  void serialize( 
            _Out_writes_(DataSizeInBytes)  void *pData,
            SIZE_T dataSizeInBytes)
  {
    ID3D12PipelineLibrary* library = getPipelineLibrary();
    HRESULT hr = library -> Serialize( 
            pData,
            dataSizeInBytes);
    if (FAILED(hr)) {
      throw IException("Faild to ID3D12PipelineLibrary::Serialize. HRESULT(0x%lx)", hr);
    }
  }

};

}
    
