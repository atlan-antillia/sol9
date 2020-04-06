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
 *  Direct3D12VersionedRootSignatureDeserializer.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12RootSignature.h>

namespace SOL {

class Direct3D12VersionedRootSignatureDeserializer : public Direct3D12RootSignature {
    
public:
  Direct3D12VersionedRootSignatureDeserializer(
           __in LPCVOID  pSrcData,
           __in SIZE_T   srcDataSizeInBytes,
           __in REFIID   pRootSignatureDeserializerInterface)
  :Direct3D12RootSignature()
  {
    ID3D12VersionedRootSignatureDeserializer* rootSignatureDeserializer = NULL;
    HRESULT hr = D3D12CreateVersionedRootSignatureDeserializer(
             pSrcData,
             srcDataSizeInBytes,
             pRootSignatureDeserializerInterface,
             &rootSignatureDeserializer);
    if (SUCCEEDED(hr) {
      set(rootSignatureDeserializer);
    } else {
      throw IException("Faield to D3D12CreateVersionedRootSignatureDeserializer. HRESULT(0x%lx)", h);
    } 
  }

  Direct3D12VersionedRootSignatureDeserializer(
    __in ID3D12VersionedRootSignatureDeserializer* versionedRootSignatureDeserializer)
  :Direct3D12RootSignature(versionedRootSignatureDeserializer)
  {
  }
  
  
  ~Direct3D12VersionedRootSignatureDeserializer()
  { 
  }

   
  operator ID3D12VersionedRootSignatureDeserializer*()
  {
    return getVersionedRootSignatureDeserializer();
  }

  ID3D12VersionedRootSignatureDeserializer* getVersionedRootSignatureDeserializer()
  {
    ID3D12VersionedRootSignatureDeserializer* versionedRootSignatureDeserializer = (ID3D12VersionedRootSignatureDeserializer*)getIUnknown();
    if (versionedRootSignatureDeserializer) {
        return versionedRootSignatureDeserializer;
    } else {
      throw IException("ID3D12VersionedRootSignatureDeserializer is NULL.");
    }
  }

  void getRootSignatureDescAtVersion( 
            D3D_ROOT_SIGNATURE_VERSION convertToVersion,
            _Out_  const D3D12_VERSIONED_ROOT_SIGNATURE_DESC **ppDesc)
  {
    ID3D12VersionedRootSignatureDeserializer* versionedRootSignatureDeserializer = getVersionedRootSignatureDeserializer();
    HRESULT hr = versionedRootSignatureDeserializer -> GetRootSignatureDescAtVersion( 
            convertToVersion,
            ppDesc);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12VersionedRootSignatureDeserializer::GetRootSignatureDescAtVersion. HRESULT(0x%lx)", hr);
    }
  }
  
  const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* getUnconvertedRootSignatureDesc()
  {
    D3D1Versioned2RootSignatureDeserializer* versionedRootSignatureDeserializer = getVersionedRootSignatureDeserializer();
    return versionedRootSignatureDeserializer-> GetUnconvertedRootSignatureDesc();
  }
};

}
    
