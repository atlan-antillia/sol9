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
 *  Direct3DX12Torus.h
 *
 *****************************************************************************/

//2016/10/10
//This is based on MakeTorus function in the following code.
// C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp


#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>


namespace SOL {

class Direct3DX12Torus : public Direct3DX12Shape {
public:
  Direct3DX12Torus(
        __in ID3D12Device*        device, 
        __in float fInnerRadius = 1.0f, 
        __in float fOuterRadius = 2.0f, 
        __in UINT uSides        = 8,
        __in UINT uRings        = 15)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
        
    if (fInnerRadius < 0.0f || fOuterRadius < 0.0f || uSides < 3 || uRings < 3) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createTorus(fInnerRadius, fOuterRadius, uSides, uRings);

  }
  //The following createTorus is based on MakeTorus function in the following code.
  //
  //C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp
  //--------------------------------------------------------------------------------------
  // File: DXUTShapes.cpp
  //
  // Shape creation functions for DXUT
  //
  // Copyright (c) Microsoft Corporation. All rights reserved
  //--------------------------------------------------------------------------------------
  void createTorus( float fInnerRadius, float fOuterRadius, UINT uSides,
                                UINT uRings )
  { 
    UINT cFaces = 2 * uSides * uRings;
    UINT cVertices = uRings * uSides;
    
    D3D12PosNormalVertex* vertices = new D3D12PosNormalVertex[cVertices];

    UINT i, j;

    // Generate vertices
    D3D12PosNormalVertex* pVertex = vertices;

    for( i = 0; i < uRings; i++ )
    {
        float theta = ( float )i * 2.0f * (float)MATH_PI / ( float )uRings;
        float st = sinf(theta);
        float ct = cosf(theta);

        //sincosf( theta, &st, &ct );

        for( j = 0; j < uSides; j++ )
        {
            float phi = ( float )j * 2.0f * (float)MATH_PI / (float)uSides;
            float sp = sinf(phi);
            float cp = cosf(phi);

            //sincosf( phi, &sp, &cp );

            pVertex->pos.x = ct * ( fOuterRadius + fInnerRadius * cp );
            pVertex->pos.y = -st * ( fOuterRadius + fInnerRadius * cp );
            pVertex->pos.z = sp * fInnerRadius;

            pVertex->normal.x = ct * cp;
            pVertex->normal.y = -st * cp;
            pVertex->normal.z = sp;

            pVertex++;
        }
    }

    uint16_t* indices = new uint16_t[ cFaces * 3 ];

    // Generate indices
    uint16_t* pwFace = indices;

    for( i = 0; i < uRings - 1; i++ )
    {
        for( j = 0; j < uSides - 1; j++ )
        {

            // Tri 1 (Top-Left tri, CCW)
            pwFace[0] = ( WORD )( i * uSides + j );
            pwFace[1] = ( WORD )( i * uSides + j + 1 );
            pwFace[2] = ( WORD )( ( i + 1 ) * uSides + j );
            pwFace += 3;

            // Tri 2 (Bottom-Right tri, CCW)
            pwFace[0] = ( WORD )( ( i + 1 ) * uSides + j );
            pwFace[1] = ( WORD )( i * uSides + j + 1 );
            pwFace[2] = ( WORD )( ( i + 1 ) * uSides + j + 1 );
            pwFace += 3;
        }

        // Tri 1 (Top-Left tri, CCW)
        pwFace[0] = ( WORD )( i * uSides + j );
        pwFace[1] = ( WORD )( i * uSides );
        pwFace[2] = ( WORD )( ( i + 1 ) * uSides + j );
        pwFace += 3;

        // Tri 2 (Bottom-Right tri, CCW)
        pwFace[0] = ( WORD )( ( i + 1 ) * uSides + j );
        pwFace[1] = ( WORD )( i * uSides + 0 );
        pwFace[2] = ( WORD )( ( i + 1 ) * uSides + 0 );
        pwFace += 3;
    }


    // join the two ends of the tube
    for( j = 0; j < uSides - 1; j++ )
    {
        // Tri 1 (Top-Left tri, CCW)
        pwFace[0] = ( WORD )( i * uSides + j );
        pwFace[1] = ( WORD )( i * uSides + j + 1 );
        pwFace[2] = ( WORD )( j );
        pwFace += 3;

        // Tri 2 (Bottom-Right tri, CCW)
        pwFace[0] = ( WORD )( j );
        pwFace[1] = ( WORD )( i * uSides + j + 1 );
        pwFace[2] = ( WORD )( j + 1 );
        pwFace += 3;
    }

    // Tri 1 (Top-Left tri, CCW)
    pwFace[0] = ( WORD )( i * uSides + j );
    pwFace[1] = ( WORD )( i * uSides );
    pwFace[2] = ( WORD )( j );
    pwFace += 3;

    // Tri 2 (Bottom-Right tri, CCW)
    pwFace[0] = ( WORD )( j );
    pwFace[1] = ( WORD )( i * uSides );
    pwFace[2] = ( WORD )( 0 );
    pwFace += 3;
  
    createVertexBuffer(vertices, sizeof(D3D12PosNormalVertex) * cVertices, sizeof(D3D12PosNormalVertex), cVertices);
    createIndexBuffer(indices, sizeof(uint16_t) * cFaces * 3, cFaces * 3 );
    
    delete[] vertices;
    delete[] indices;
  }


  ~Direct3DX12Torus()
  {
  }
  
};

}

