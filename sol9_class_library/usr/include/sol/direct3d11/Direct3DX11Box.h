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
 *  Direct3DX11Box.h
 *
 *****************************************************************************/

//This is based on MakeBox function in the following code.
// C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp

#pragma once

#include <sol/direct3d11/Direct3DX11Shape.h>


namespace SOL {

class Direct3DX11Box : public Direct3DX11Shape {
public:
  Direct3DX11Box(
        __in Direct3D11Device*           device, 
        __in Direct3D11DeviceContext*    context,
        __in float                       fWidth  = 1.0f, 
        __in float                       fHeight = 1.0f, 
        __in float                       fDepth  = 1.0f)
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid device.");
    }
    if (context == NULL ) {
      throw IException("Invalid deviceContex.t");
    }
    if (fWidth < 0.0f || fHeight < 0.0f || fDepth < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createBox(fWidth, fHeight, fDepth);    
  }

public:
  Direct3DX11Box(
        __in Direct3D11Device*           device, 
        __in Direct3D11DeviceContext*    context,
        __in Direct3D11Blob*             vertexShaderBlob,
        __in float                       fWidth  = 1.0f, 
        __in float                       fHeight = 1.0f, 
        __in float                       fDepth  = 1.0f)
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid device.");
    }
    if (context == NULL ) {
      throw IException("Invalid deviceContex.t");
    }
   if (vertexShaderBlob == NULL) {
      throw IException("Invalid vertexShaderBlob");
    }        
    if (fWidth < 0.0f || fHeight < 0.0f || fDepth < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createBox(fWidth, fHeight, fDepth);
    
     createInputLayout(vertexShaderBlob); 
  }

  //The following createBox is based on MakeBox function in the following code.
  //
  //C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp
  //--------------------------------------------------------------------------------------
  // File: DXUTShapes.cpp
  //
  // Shape creation functions for DXUT
  //
  // Copyright (c) Microsoft Corporation. All rights reserved
  //--------------------------------------------------------------------------------------
  void createBox( float fWidth, float fHeight, float fDepth)
  {
    static float cubeN[6][3] = {
        {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}
    };

    static WORD cubeF[6][4] = {
        { 0, 1, 5, 4 }, { 4, 5, 6, 7 }, { 7, 6, 2, 3 },
        { 1, 0, 3, 2 }, { 1, 2, 6, 5 }, { 0, 4, 7, 3 }
    };

    static float cubeV[8][3] = {
        // Lower tier (lower in y)
        {-.5f, -.5f, -.5f},
        {-.5f, -.5f,  .5f},
        { .5f, -.5f,  .5f},
        { .5f, -.5f, -.5f},

        // Upper tier
        {-.5f, .5f, -.5f},
        {-.5f, .5f,  .5f},
        { .5f, .5f,  .5f},
        { .5f, .5f, -.5f},
    };

    static float cubeT[4][2] = {
        // Lower tier (lower in y)
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f}
    };

    static WORD cubeFT[6][4] = {
        { 3, 0, 1, 2 }, { 0, 1, 2, 3 }, { 1, 2, 3, 0 },
        { 0, 1, 2, 3 }, { 3, 0, 1, 2 }, { 0, 1, 2, 3 }
    };

    UINT cFaces    = 12;
    UINT cVertices = 24;
    D3D11PosNormalVertex* vertices = new D3D11PosNormalVertex[cVertices];
    
    
    UINT* indices = new UINT[ cFaces * 3 ];

    D3D11PosNormalVertex* pVertex = vertices;
    unsigned int* pwFace    = indices;
    UINT iVertex    = 0;

    // i iterates over the faces, 2 triangles per face
    for( int i = 0; i < 6; i++ ) {
        for( int j = 0; j < 4; j++ ) {
            pVertex->pos.x = cubeV[cubeF[i][j]][0] * fWidth;
            pVertex->pos.y = cubeV[cubeF[i][j]][1] * fHeight;
            pVertex->pos.z = cubeV[cubeF[i][j]][2] * fDepth;

            pVertex->normal.x = cubeN[i][0];
            pVertex->normal.y = cubeN[i][1];
            pVertex->normal.z = cubeN[i][2];
            pVertex++;
        }

        pwFace[0] = ( WORD )( iVertex );
        pwFace[1] = ( WORD )( iVertex + 1 );
        pwFace[2] = ( WORD )( iVertex + 2 );
        pwFace += 3;

        pwFace[0] = ( WORD )( iVertex + 2 );
        pwFace[1] = ( WORD )( iVertex + 3 );
        pwFace[2] = ( WORD )( iVertex );
        pwFace += 3;

        iVertex += 4;
    }
    
    createVertexBuffer(vertices,  sizeof(D3D11PosNormalVertex) * cVertices, cVertices);
    createIndexBuffer(indices, sizeof(UINT) * cFaces * 3, cFaces * 3 );
    
    delete[] vertices;
    delete[] indices;
  }
  
  
  ~Direct3DX11Box()
  {
  }
  
};

}

