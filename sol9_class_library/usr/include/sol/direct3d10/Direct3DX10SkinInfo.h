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
 *  Direct3DX10SkinInfo.h
 *
 *****************************************************************************/

#pragma once


#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d3d10_1.h>
#include <d3dx10.h>

namespace SOL {

class Direct3DX10SkinInfo : public ComIUnknown {
public:
  Direct3DX10SkinInfo() 
  :ComIUnknown()
  {
    ID3DX10SkinInfo* skinInfo = NULL;
    HRESULT hr = D3DX10CreateSkinInfo(&skinInfo);
    if (SUCCEEDED(hr)) {
      set(skinInfo);
    } else {
      throw IException("Failed to D3DX10CreateSkinInfo. HRESULT(0x%lx)", hr);
    }    
  }
  
  ~Direct3DX10SkinInfo() 
  {
  }
  
  operator  ID3DX10SkinInfo*()
  {
    return getSkinInfo();
  }
  
  
  ID3DX10SkinInfo* getSkinInfo()
  {
    ID3DX10SkinInfo* info = (ID3DX10SkinInfo*)getIUnknown();
    if (info) {
      return info;
    } else {
      throw IException("ID3DX10SkinInfo is NULL.");
    }
  }
    
   
  UINT getNumVertices()
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    return info -> GetNumVertices();
  }
  
  UINT getNumBones()
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    return info -> GetNumBones();
  }
  
  UINT getMaxBoneInfluences()
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    return info -> GetMaxBoneInfluences();
  }

  void addVertices(UINT  count)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> AddVertices(count);
    if (FAILED(hr)) {
      throw IException("Failed to AddVertices. HRESULT(0x%lx)", hr); 
    }
  }
  
  void remapVertices(UINT newVertexCount, UINT  *pVertexRemap)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> RemapVertices(newVertexCount, pVertexRemap);
    if (FAILED(hr)) {
      throw IException("Failed to RemapVertices. HRESULT(0x%lx)", hr); 
    }
  }

  void addBones(UINT count)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> AddBones(count);
    if (FAILED(hr)) {
      throw IException("Failed to AddBones. HRESULT(0x%lx)", hr); 
    }
  }
  
  void removeBone(UINT  index)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> RemoveBone(index);
    if (FAILED(hr)) {
      throw IException("Failed to RemoveBone. HRESULT(0x%lx)", hr); 
    }
  }
  
  void remapBones(UINT  newBoneCount, UINT  *pBoneRemap)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> RemapBones(newBoneCount, pBoneRemap);
    if (FAILED(hr)) {
      throw IException("Failed to RemapBones. HRESULT(0x%lx)", hr); 
    }
  }

  void addBoneInfluences(UINT  boneIndex, UINT  influenceCount, UINT  *pIndices, float *pWeights)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> AddBoneInfluences(boneIndex, influenceCount, pIndices, pWeights);
    if (FAILED(hr)) {
      throw IException("Failed to AddBoneInfluences. HRESULT(0x%lx)", hr); 
    }
  }
  
  void clearBoneInfluences(UINT  boneIndex)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> ClearBoneInfluences(boneIndex);
    if (FAILED(hr)) {
      throw IException("Failed to ClearBoneInfluences. HRESULT(0x%lx)", hr); 
    }
  }
  
  UINT getBoneInfluenceCount(UINT  boneIndex)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    return info -> GetBoneInfluenceCount(boneIndex);
  }
  
  void getBoneInfluences(UINT  boneIndex, UINT  offset, UINT  count, UINT  *pDestIndices, float *pDestWeights)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> GetBoneInfluences(boneIndex, offset,  count, pDestIndices, pDestWeights);
    if (FAILED(hr)) {
      throw IException("Failed to GetBoneInfluences. HRESULT(0x%lx)", hr); 
    }
  }
  
  void findBoneInfluenceIndex(UINT  boneIndex, UINT  vertexIndex, UINT  *pInfluenceIndex)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> FindBoneInfluenceIndex(boneIndex, vertexIndex, pInfluenceIndex);
    if (FAILED(hr)) {
      throw IException("Failed to FindBoneInfluenceIndex. HRESULT(0x%lx)", hr); 
    }
  }
  
  void setBoneInfluence(UINT  boneIndex, UINT  influenceIndex, float weight)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> SetBoneInfluence(boneIndex, influenceIndex, weight);
    if (FAILED(hr)) {
      throw IException("Failed to SetBoneInfluence. HRESULT(0x%lx)", hr); 
    }
  }
  
  void getBoneInfluence(UINT  boneIndex, UINT  influenceIndex, float *pWeight)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> GetBoneInfluence(boneIndex, influenceIndex, pWeight);
    if (FAILED(hr)) {
      throw IException("Failed to GetBoneInfluence. HRESULT(0x%lx)", hr); 
    }
  }

  void compact(UINT  maxPerVertexInfluences, UINT  scaleMode, float minWeight)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> Compact(maxPerVertexInfluences, scaleMode, minWeight);
    if (FAILED(hr)) {
      throw IException("Failed to Compact. HRESULT(0x%lx)", hr); 
    }
  }
  
  void doSoftwareSkinning(
        UINT  startVertex, 
        UINT  vertexCount, 
        void *pSrcVertices, 
        UINT  srcStride, 
        void *pDestVertices, 
        UINT  destStride, 
        D3DXMATRIX *pBoneMatrices, 
        D3DXMATRIX *pInverseTransposeBoneMatrices, 
        D3DX10_SKINNING_CHANNEL *pChannelDescs, 
        UINT  numChannels)
  {
    ID3DX10SkinInfo* info = getSkinInfo();
    HRESULT hr = info -> DoSoftwareSkinning(
          startVertex, 
          vertexCount, 
          pSrcVertices, 
          srcStride, 
          pDestVertices, 
          destStride, 
          pBoneMatrices, 
          pInverseTransposeBoneMatrices, 
          pChannelDescs, 
          numChannels);
    if (FAILED(hr)) {
      throw IException("Failed to DoSoftwareSkinning. HRESULT(0x%lx)", hr); 
    }
  }
};

}
