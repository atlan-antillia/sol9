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
 *  Direct3D12RootSignatureDeserializer.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12RootSignature.h>

namespace SOL {

class Direct3D12RootSignatureDeserializer : public Direct3D12RootSignature {
    
public:
  Direct3D12RootSignatureDeserializer(
      _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
      _In_ SIZE_T srcDataSizeInBytes,
      _In_ REFIID pRootSignatureDeserializerInterface)
  :Direct3D12RootSignature()
  {
    ID3D12RootSignatureDeserializer* rootSignatureDeserializer = NULL;
    HRESULT hr = D3D12CreateRootSignatureDeserializer(
                   pSrcData,
                   srcDataSizeInBytes,
                   pRootSignatureDeserializerInterface,
                   &rootSignatureDeserializer);
    if (SUCCEEDED(hr)) {
      set(rootSignatureDeserializer);
    } else {
      throw IException("Failed to D3D12CreateRootSignatureDeserializer. HRESULT(0x%lx)", hr);
    }
  }

  Direct3D12RootSignatureDeserializer(
    __in ID3D12RootSignatureDeserializer* rootSignatureDeserializer)
  :Direct3D12RootSignature(rootSignatureDeserializer)
  {
  }
  
  ~Direct3D12RootSignatureDeserializer()
  { 
  }

   
  operator ID3D12RootSignatureDeserializer*()
  {
    return getRootSignatureDeserializer();
  }

  ID3D12RootSignatureDeserializer* getRootSignatureDeserializer()
  {
    ID3D12RootSignatureDeserializer* rootSignatureDeserializer = (ID3D12RootSignatureDeserializer*)getIUnknown();
    if (rootSignatureDeserializer) {
        return rootSignatureDeserializer;
    } else {
      throw IException("ID3D12RootSignatureDeserializer is NULL.");
    }
  }

  const D3D12_ROOT_SIGNATURE_DESC * getRootSignatureDesc()
  {
    D3D12RootSignatureDeserializer* rootSignatureDeserializer = getRootSignatureDeserializer();
    return rootSignatureDeserializer-> GetRootSignatureDesc();
  }
};

}
    
