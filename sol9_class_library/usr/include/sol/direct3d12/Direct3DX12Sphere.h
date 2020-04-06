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
 *  Direct3DX12Sphere.h
 *
 *****************************************************************************/

#pragma once

#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>


namespace SOL {

class Direct3DX12Sphere : public Direct3DX12Shape {
private:
  UINT indicesCount;
  
public:
  Direct3DX12Sphere(
        __in ID3D12Device*        device, 
        __in float fRadius  = 1.0f, 
        __in UINT uSlices   = 8, 
        __in UINT uStacks   = 8)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid device.");
    }

    if (fRadius < 0.0f || uSlices < 2 || uStacks < 2) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createSphere(fRadius, uSlices, uStacks);
  }
  

  
  //The following createBox is based on MakeSphere function in the following code.
  //
  //C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp
  //--------------------------------------------------------------------------------------
  // File: DXUTShapes.cpp
  //
  // Shape creation functions for DXUT
  //
  // Copyright (c) Microsoft Corporation. All rights reserved
  //--------------------------------------------------------------------------------------
  void createSphere( float fRadius, UINT uSlices, UINT uStacks )
  { 
    UINT cFaces = 2 * ( uStacks - 1 ) * uSlices;
    UINT cVertices = ( uStacks - 1 ) * uSlices + 2;

    D3D12PosNormalVertex* vertices = new D3D12PosNormalVertex[cVertices];


    UINT i, j;

    const int CACHE_SIZE = 240*2;

    // Sin/Cos caches
    float sinI[CACHE_SIZE], cosI[CACHE_SIZE];
    float sinJ[CACHE_SIZE], cosJ[CACHE_SIZE];

    for( i = 0; i < uSlices; i++ ) {
      sinI[i] = sinf((float)(2.0f * MATH_PI * i / uSlices));
      cosI[i] = cosf((float)(2.0f * MATH_PI * i / uSlices));
       // sincosf( 2.0f * D3DX_PI * i / uSlices, sinI + i, cosI + i );
    }
    for( j = 0; j < uStacks; j++ ) {
      sinJ[j] = sinf((float)(MATH_PI * j / uStacks));
      cosJ[j] = cosf((float)(MATH_PI * j / uStacks));
       // sincosf( D3DX_PI * j / uStacks, sinJ + j, cosJ + j );
    }

    // Generate vertices
    D3D12PosNormalVertex* pVertex = vertices;

    // +Z pole
    pVertex->pos    = XMFLOAT3( 0.0f, 0.0f, fRadius );
    pVertex->normal = XMFLOAT3( 0.0f, 0.0f, 1.0f );
    pVertex++;

    // Stacks
    for( j = 1; j < uStacks; j++ )
    {
        for( i = 0; i < uSlices; i++ )
        {
            XMFLOAT3 norm( sinI[i]* sinJ[j], cosI[i]* sinJ[j], cosJ[j] );
            XMFLOAT3 pos;
            pos.x = norm.x * fRadius;
            pos.y = norm.y * fRadius;
            pos.z = norm.z * fRadius;

            pVertex->pos = pos; //norm * fRadius;
            pVertex->normal = norm;

            pVertex++;
        }
    }

    // Z- pole
    pVertex->pos    = XMFLOAT3( 0.0f, 0.0f, -fRadius );
    pVertex->normal = XMFLOAT3( 0.0f, 0.0f, -1.0f );
    pVertex++;


    uint16_t* indices = new uint16_t[ cFaces * 3 ];

    // Generate indices
    uint16_t* pwFace = indices;

    // Z+ pole
    UINT uRowA = 0;
    UINT uRowB = 1;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB + i + 1 );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA );
    pwFace[1] = ( WORD )( uRowB );
    pwFace[2] = ( WORD )( uRowB + i );
    pwFace += 3;

    // Interior stacks
    for( j = 1; j < uStacks - 1; j++ )
    {
        uRowA = 1 + ( j - 1 ) * uSlices;
        uRowB = uRowA + uSlices;

        for( i = 0; i < uSlices - 1; i++ )
        {
            pwFace[0] = ( WORD )( uRowA + i );
            pwFace[1] = ( WORD )( uRowA + i + 1 );
            pwFace[2] = ( WORD )( uRowB + i );
            pwFace += 3;

            pwFace[0] = ( WORD )( uRowA + i + 1 );
            pwFace[1] = ( WORD )( uRowB + i + 1 );
            pwFace[2] = ( WORD )( uRowB + i );
            pwFace += 3;
        }

        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowA );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;

        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;
    }

    // Z- pole
    uRowA = 1 + ( uStacks - 2 ) * uSlices;
    uRowB = uRowA + uSlices;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowA + i + 1 );
        pwFace[2] = ( WORD )( uRowB );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA + i );
    pwFace[1] = ( WORD )( uRowA );
    pwFace[2] = ( WORD )( uRowB );
    pwFace += 3;
   
    createVertexBuffer(vertices, sizeof(D3D12PosNormalVertex) * cVertices, sizeof(D3D12PosNormalVertex), cVertices);
    createIndexBuffer(indices, sizeof(uint16_t) * cFaces * 3, cFaces * 3 );
    
    indicesCount = cFaces * 3;
    
    delete[] vertices;
    delete[] indices;
  }


  ~Direct3DX12Sphere()
  {
  }
  
  
  virtual const D3D12_INPUT_ELEMENT_DESC*  getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosNormalDesc(count);
  }
  
  
};

}

