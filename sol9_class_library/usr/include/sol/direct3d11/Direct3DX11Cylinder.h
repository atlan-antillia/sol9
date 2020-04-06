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
 *  Direct3DX11Sphere.h
 *
 *****************************************************************************/

//2016/0/20
//This is based on MakeCylinder function in the following code.
// C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp


#pragma once
#include <math.h>
#include <sol/direct3d11/Direct3DX11Shape.h>


namespace SOL {

class Direct3DX11Cylinder : public Direct3DX11Shape {
public:
  Direct3DX11Cylinder(
        __in Direct3D11Device*        device, 
        __in Direct3D11DeviceContext* context,
        __in float fRadius1 = 1.0f, 
        __in float fRadius2 = 1.0f, 
        __in float fLength  = 1.0f, 
        __in UINT uSlices   = 8,
        __in UINT uStacks   = 8 )
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (context == NULL ) {
      throw IException("Invalid devieContex.t");
    }
     
    if (fRadius1 < 0.0f || fRadius2 < 0.0f || fLength < 0.0f || uSlices < 2 || uStacks < 2) {
      throw IException("Invalid parameter"); 
    }

    // Create a vertexBuffer and an indexBuffer
    createCylinder(fRadius1, fRadius2, fLength, uSlices, uStacks);
    
  }

public:
  Direct3DX11Cylinder(
        __in Direct3D11Device*        device, 
        __in Direct3D11DeviceContext* context,
        __in Direct3D11Blob*          vertexShaderBlob,
        __in float fRadius1 = 1.0f, 
        __in float fRadius2 = 1.0f, 
        __in float fLength  = 1.0f, 
        __in UINT uSlices   = 8,
        __in UINT uStacks   = 8 )
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (context == NULL ) {
      throw IException("Invalid devieContex.t");
    }
     
    if (vertexShaderBlob == NULL) {
      throw IException("Invalid vertexShaderBlob");
    }     

    if (fRadius1 < 0.0f || fRadius2 < 0.0f || fLength < 0.0f || uSlices < 2 || uStacks < 2) {
      throw IException("Invalid parameter"); 
    }

    // Create a vertexBuffer and an indexBuffer
    createCylinder(fRadius1, fRadius2, fLength, uSlices, uStacks);
    
    createInputLayout(vertexShaderBlob); 
  }

  //The following createCylinder is based on MakeCylinder function in the following code.
  //
  //C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp
  //--------------------------------------------------------------------------------------
  // File: DXUTShapes.cpp
  //
  // Shape creation functions for DXUT
  //
  // Copyright (c) Microsoft Corporation. All rights reserved
  //--------------------------------------------------------------------------------------
  void createCylinder(float fRadius1, 
                      float fRadius2, float fLength, UINT uSlices, UINT uStacks )
  {
    UINT i, j;
    const int CACHE_SIZE = 240*2;
    // Sin/Cos caches
    float sinI[CACHE_SIZE], cosI[CACHE_SIZE];
    
    for( i = 0; i < uSlices; i++ ) {
      sinI[i] = sinf((float)(2.0f * MATH_PI * i / uSlices));
      cosI[i] = cosf((float)(2.0f * MATH_PI * i / uSlices));      
      //  sincosf( 2.0f * D3DX_PI * i / uSlices, sinI + i, cosI + i );
    }
    
    UINT cFaces = ( uStacks + 1 ) * uSlices * 2;
    UINT cVertices = 2 + ( uStacks + 3 ) * uSlices;

    D3D11PosNormalVertex* vertices = new D3D11PosNormalVertex[cVertices];
       
    // Compute side normal angle
    float fDeltaRadius = fRadius2 - fRadius1;
    float fSideLength = sqrtf( fDeltaRadius * fDeltaRadius + fLength * fLength );

    float fNormalXY = ( fSideLength > 0.00001f ) ? ( fLength / fSideLength )       : 1.0f;
    float fNormalZ = ( fSideLength > 0.00001f ) ? ( -fDeltaRadius / fSideLength ) : 0.0f;

    // Generate vertices
    D3D11PosNormalVertex* pVertex = vertices;
    float fZ, fRadius;
    DWORD iVertex;

    // Base cap (uSlices + 1)
    fZ = fLength * -0.5f;
    fRadius = fRadius1;
    iVertex = 0;

    pVertex->pos    = XMFLOAT3( 0.0f, 0.0f, fZ );
    pVertex->normal = XMFLOAT3( 0.0f, 0.0f, -1.0f );
    pVertex++;
    //if( pPointReps != NULL )
    //    pPointReps[iVertex] = iVertex;
    iVertex++;

    for( i = 0; i < uSlices; i++ )
    {
        pVertex->pos    = XMFLOAT3( fRadius * sinI[i], fRadius * cosI[i], fZ );
        pVertex->normal = XMFLOAT3( 0.0f, 0.0f, -1.0f );
        pVertex++;

        // link into stack vertices, which follow
        //if( pPointReps != NULL )
        //    pPointReps[iVertex] = iVertex + uSlices;
        iVertex++;
    }

    // Stacks ((uStacks + 1)*uSlices)
    for( j = 0; j <= uStacks; j++ )
    {
        float f = ( float )j / ( float )uStacks;

        fZ = fLength * ( f - 0.5f );
        fRadius = fRadius1 + f * fDeltaRadius;

        for( i = 0; i < uSlices; i++ )
        {
            pVertex->pos    = XMFLOAT3( fRadius * sinI[i], fRadius * cosI[i], fZ );
            pVertex->normal = XMFLOAT3( fNormalXY * sinI[i], fNormalXY * cosI[i], fNormalZ );
            pVertex++;
            //if( pPointReps != NULL )
            //    pPointReps[iVertex] = iVertex;
            iVertex++;
        }
    }

    // Top cap (uSlices + 1)
    fZ = fLength * 0.5f;
    fRadius = fRadius2;

    for( i = 0; i < uSlices; i++ )
    {
        pVertex->pos    = XMFLOAT3( fRadius * sinI[i], fRadius * cosI[i], fZ );
        pVertex->normal = XMFLOAT3( 0.0f, 0.0f, 1.0f );
        pVertex++;

        // link into stack vertices, which precede
        //if( pPointReps != NULL )
        //    pPointReps[iVertex] = iVertex - uSlices;
        iVertex++;
    }

    pVertex->pos    = XMFLOAT3( 0.0f, 0.0f, fZ );
    pVertex->normal = XMFLOAT3( 0.0f, 0.0f, 1.0f );
    pVertex++;
    //if( pPointReps != NULL )
    //    pPointReps[iVertex] = iVertex;
    iVertex++;

    
    UINT* indices = new UINT[ cFaces * 3 ];
    
    // Generate indices
    UINT* pwFace = indices;
    UINT uRowA, uRowB;

    // Z+ pole (uSlices)
    uRowA = 0;
    uRowB = 1;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB + i );
        pwFace[2] = ( WORD )( uRowB + i + 1 );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA );
    pwFace[1] = ( WORD )( uRowB + i );
    pwFace[2] = ( WORD )( uRowB );
    pwFace += 3;

    // Interior stacks (uStacks * uSlices * 2)
    for( j = 0; j < uStacks; j++ )
    {
        uRowA = 1 + ( j + 1 ) * uSlices;
        uRowB = uRowA + uSlices;

        for( i = 0; i < uSlices - 1; i++ )
        {
            pwFace[0] = ( WORD )( uRowA + i );
            pwFace[1] = ( WORD )( uRowB + i );
            pwFace[2] = ( WORD )( uRowA + i + 1 );
            pwFace += 3;

            pwFace[0] = ( WORD )( uRowA + i + 1 );
            pwFace[1] = ( WORD )( uRowB + i );
            pwFace[2] = ( WORD )( uRowB + i + 1 );
            pwFace += 3;
        }

        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowB + i );
        pwFace[2] = ( WORD )( uRowA );
        pwFace += 3;

        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB + i );
        pwFace[2] = ( WORD )( uRowB );
        pwFace += 3;
    }

    // Z- pole (uSlices)
    uRowA = 1 + ( uStacks + 2 ) * uSlices;
    uRowB = uRowA + uSlices;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowB );
        pwFace[2] = ( WORD )( uRowA + i + 1 );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA + i );
    pwFace[1] = ( WORD )( uRowB );
    pwFace[2] = ( WORD )( uRowA );
    pwFace += 3;
    
    createVertexBuffer(vertices, sizeof(D3D11PosNormalVertex) * cVertices, cVertices);
    createIndexBuffer(indices, sizeof(UINT) * cFaces * 3, cFaces * 3 );
    
    delete[] vertices;
  
    delete[] indices;
    
  }


  ~Direct3DX11Cylinder()
  {
  }
  
};

}

