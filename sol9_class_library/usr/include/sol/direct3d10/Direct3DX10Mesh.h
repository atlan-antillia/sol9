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
 *  Direct3DX10Mesh.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>
#include <sol/direct3d10/Direct3D10EffectTechnique.h>
#include <sol/direct3d10/Direct3D10EffectPass.h>

namespace SOL {
  
class Direct3DX10Mesh : public ComIUnknown {
public:
  Direct3DX10Mesh()
  :ComIUnknown()
  {
  }
  
  
  Direct3DX10Mesh(
        __in  ID3D10Device *pDevice,
        __in  CONST D3D10_INPUT_ELEMENT_DESC *pDeclaration, 
        __in  UINT  declCount,
        __in  LPCSTR pPositionSemantic,
        __in  UINT  vertexCount,
        __in  UINT  faceCount,
        __in  UINT  options) 
        
  :ComIUnknown()
  {
    ID3DX10Mesh *mesh = NULL;
    HRESULT hr = D3DX10CreateMesh(
        pDevice,
        pDeclaration, 
        declCount,
        pPositionSemantic,
        vertexCount,
        faceCount,
        options, 
        &mesh);
    if (SUCCEEDED(hr)) {
      set(mesh);
    } else {
      throw IException("Failed to D3DX10CreateMesh. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3DX10Mesh()
  {
  }
  
  operator ID3DX10Mesh*()
  {
    return getMesh();
  }
  

  ID3DX10Mesh* getMesh()
  {
    ID3DX10Mesh* mesh = (ID3DX10Mesh*)getIUnknown();
    if (mesh) {
      return mesh;
    } else {
      throw IException("ID3DX10Mesh is NULL.");
    }
  }
  
    // ID3DX10Mesh
  UINT getFaceCount()
  {
    ID3DX10Mesh* mesh = getMesh();
    return mesh -> GetFaceCount();
  }
  
  UINT getVertexCount()
  {
    ID3DX10Mesh* mesh = getMesh();
    return mesh -> GetVertexCount();
  }

  UINT getVertexBufferCount()
  {
    ID3DX10Mesh* mesh = getMesh();
    return mesh -> GetVertexBufferCount();
  }

  UINT getFlags()
  {
    ID3DX10Mesh* mesh = getMesh();
    return mesh -> GetFlags();
  }

  void  getVertexDescription(CONST D3D10_INPUT_ELEMENT_DESC **ppDesc, UINT *pDeclCount)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetVertexDescription(ppDesc, pDeclCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetVertexDescription. HRESULT(0x%lx)", hr);
    }
  }

  void  setVertexData(UINT iBuffer, CONST void *pData)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> SetVertexData(iBuffer, pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetVertexData. HRESULT(0x%lx)", hr);
    }
  }

  void  getVertexBuffer(UINT iBuffer, ID3DX10MeshBuffer **ppVertexBuffer)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetVertexBuffer(iBuffer, ppVertexBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetVertexBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void  setIndexData(CONST void *pData, UINT cIndices)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh ->  SetIndexData(pData, cIndices);
    if (FAILED(hr)) {
      throw IException("Failed to SetIndexData. HRESULT(0x%lx)", hr);
    }
  }

  void  getIndexBuffer(ID3DX10MeshBuffer **ppIndexBuffer)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetIndexBuffer(ppIndexBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetIndexBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void  setAttributeData(CONST UINT *pData)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> SetAttributeData(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetAttributeData. HRESULT(0x%lx)", hr);
    }
  }

  void  getAttributeBuffer(ID3DX10MeshBuffer **ppAttributeBuffer)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetAttributeBuffer(ppAttributeBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetAttributeBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void  setAttributeTable(CONST D3DX10_ATTRIBUTE_RANGE *pAttribTable, UINT  cAttribTableSize)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> SetAttributeTable(pAttribTable, cAttribTableSize);
    if (FAILED(hr)) {
      throw IException("Failed to SetAttributeTable. HRESULT(0x%lx)", hr);
    }
  }

  void  getAttributeTable(D3DX10_ATTRIBUTE_RANGE *pAttribTable, UINT  *pAttribTableSize)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetAttributeTable(pAttribTable,pAttribTableSize);
    if (FAILED(hr)) {
      throw IException("Failed to GetAttributeTable. HRESULT(0x%lx)", hr);
    }
  }

  void  generateAdjacencyAndPointReps(FLOAT epsilon)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GenerateAdjacencyAndPointReps(epsilon);
    if (FAILED(hr)) {
      throw IException("Failed to GenerateAdjacencyAndPointReps. HRESULT(0x%lx)", hr);
    }
  }

  void  generateGSAdjacency()
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GenerateGSAdjacency();
    if (FAILED(hr)) {
      throw IException("Failed to GenerateGSAdjacency. HRESULT(0x%lx)", hr);
    }
  }

  void  setAdjacencyData(CONST UINT *pAdjacency)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh ->  SetAdjacencyData(pAdjacency);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }

  void  getAdjacencyBuffer(ID3DX10MeshBuffer **ppAdjacency)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetAdjacencyBuffer(ppAdjacency);
    if (FAILED(hr)) {
      throw IException("Failed to GetAdjacencyBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void  setPointRepData(CONST UINT *pPointReps)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> SetPointRepData(pPointReps);
    if (FAILED(hr)) {
      throw IException("Failed to SetPointRepData. HRESULT(0x%lx)", hr);
    }
  }

  void  getPointRepBuffer(ID3DX10MeshBuffer **ppPointReps)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetPointRepBuffer(ppPointReps);
    if (FAILED(hr)) {
      throw IException("Failed to GetPointRepBuffer. HRESULT(0x%lx)", hr);
    }
  }
    
  void  discard(D3DX10_MESH_DISCARD_FLAGS dwDiscard)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> Discard(dwDiscard);
    if (FAILED(hr)) {
      throw IException("Failed to Discard. HRESULT(0x%lx)", hr);
    }
  }

  void  cloneMesh(UINT flags, LPCSTR pPosSemantic, CONST D3D10_INPUT_ELEMENT_DESC *pDesc,
          UINT  declCount, ID3DX10Mesh** ppCloneMesh)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> CloneMesh(flags, pPosSemantic, pDesc,
            declCount, ppCloneMesh);
    if (FAILED(hr)) {
      throw IException("Failed to CloneMesh. HRESULT(0x%lx)", hr);
    }
  }

  void  optimize(UINT flags, UINT * pFaceRemap, LPD3D10BLOB *ppVertexRemap)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> Optimize(flags, pFaceRemap, ppVertexRemap);
    if (FAILED(hr)) {
      throw IException("Failed to Optimize. HRESULT(0x%lx)", hr);
    }
  }

  void  generateAttributeBufferFromTable()
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GenerateAttributeBufferFromTable();
    if (FAILED(hr)) {
      throw IException("Failed to GenerateAttributeBufferFromTable. HRESULT(0x%lx)", hr);
    }
  }
    
  void  intersect(D3DXVECTOR3 *pRayPos, D3DXVECTOR3 *pRayDir, 
        UINT *pHitCount, UINT *pFaceIndex, float *pU, float *pV, 
        float *pDist, ID3D10Blob **ppAllHits)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> Intersect(pRayPos, pRayDir, 
        pHitCount, pFaceIndex, pU, pV, 
        pDist, ppAllHits);
    if (FAILED(hr)) {
      throw IException("Failed to Intersect. HRESULT(0x%lx)", hr);
    }
  }

  void  intersectSubset(UINT attribId, D3DXVECTOR3 *pRayPos, D3DXVECTOR3 *pRayDir, 
          UINT *pHitCount, UINT *pFaceIndex, float *pU, float *pV, 
          float *pDist, ID3D10Blob **ppAllHits)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> IntersectSubset(attribId, pRayPos, pRayDir, 
            pHitCount, pFaceIndex, pU, pV, 
            pDist, ppAllHits);;
    if (FAILED(hr)) {
      throw IException("Failed to IntersectSubset. HRESULT(0x%lx)", hr);
    }
  }
    
    // ID3DX10Mesh - Device functions
  void  commitToDevice()
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> CommitToDevice();
    if (FAILED(hr)) {
      throw IException("Failed to CommitToDevice. HRESULT(0x%lx)", hr);
    }
  }

  void  drawSubset(UINT attribId)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> DrawSubset(attribId);
    if (FAILED(hr)) {
      throw IException("Failed to DrawSubset. HRESULT(0x%lx)", hr);
    }
  }

  void  drawSubsetInstanced(UINT attribId, UINT instanceCount, UINT startInstanceLocation)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> DrawSubsetInstanced(attribId, instanceCount, startInstanceLocation);
    if (FAILED(hr)) {
      throw IException("Failed to DrawSubsetInstanced. HRESULT(0x%lx)", hr);
    }
  }

  void  getDeviceVertexBuffer(UINT iBuffer, ID3D10Buffer **ppVertexBuffer)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetDeviceVertexBuffer(iBuffer, ppVertexBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetDeviceVertexBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void  getDeviceIndexBuffer(ID3D10Buffer **ppIndexBuffer)
  {
    ID3DX10Mesh* mesh = getMesh();
    HRESULT hr = mesh -> GetDeviceIndexBuffer(ppIndexBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetDeviceIndexBuffer. HRESULT(0x%lx)", hr);
    }
  }

  void draw(ID3D10EffectTechnique* pTechnique)
  {
    if (pTechnique) {
      Direct3D10EffectTechnique technique(pTechnique);
      D3D10_TECHNIQUE_DESC techDesc;
      technique.getDesc(techDesc);  
      for( UINT i = 0; i < techDesc.Passes; i++ ){
        Direct3D10EffectPass pass = technique.getPassByIndex(i);
        pass.apply(0);
        this->drawSubset(0);
      }
    } else {
      throw IException("Invalid argument. ID3D10EffectTechnique is NULL."); 
    }
  }
  
};

}
