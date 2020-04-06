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
 *  DirectXVector.h
 *
 *****************************************************************************/


//2016/03/10 Updated.

#pragma once

#include <DirectXMath.h>

namespace SOL {

class DirectXVector {
private:
  XMVECTOR vector;

public:
  DirectXVector(float x=0.0f, float y=0.0f, float z=0.0f, float w=0.0f)
  {
    XMFLOAT4 float4(x, y, z, w); 
    vector = XMLoadFloat4(&float4);
  }

public:
  DirectXVector(const XMFLOAT4& float4)
  {
    vector = XMLoadFloat4(&float4);
  }
  

  DirectXVector(const DirectXVector& v)
  {
    vector = v.vector;
  }
  
  operator XMVECTOR()
  {
    return vector;
  }
  
  void operator=(XMVECTOR& float4)
  {
    vector = float4;
  }

  void operator=(XMFLOAT4& float4)
  {
    vector = XMLoadFloat4(&float4);
  }

  BOOL d3Equal(FXMVECTOR v2) const
  {
    return XMVector3Equal(vector, v2);
  }
  
  
  UINT d3EqualR(FXMVECTOR v2) const
  {
    return XMVector3EqualR(vector, v2);
  }
  
  BOOL d3EqualInt(FXMVECTOR v2) const
  {
    return XMVector3EqualInt(vector, v2);
  }
  
  UINT d3EqualIntR(FXMVECTOR v2) const
  {
    return XMVector3EqualIntR(vector, v2);
  }
  
  BOOL d3NearEqual(FXMVECTOR v2, FXMVECTOR epsilon) const
  {
    return XMVector3NearEqual(vector, v2, epsilon);
  }
  
  BOOL d3NotEqual(FXMVECTOR v2) const
  {
    return XMVector3NotEqual(vector, v2);
  }
  
  BOOL d3NotEqualInt(FXMVECTOR v2) const
  {
    return XMVector3NotEqualInt(vector, v2);
  }
  
  BOOL d3Greater(FXMVECTOR v2) const
  {
    return XMVector3Greater(vector, v2);
  }
  
  UINT d3GreaterR(FXMVECTOR v2) const
  {
    return XMVector3GreaterR(vector, v2);
  }

  BOOL d3GreaterOrEqual(FXMVECTOR v2) const
  {
    return XMVector3GreaterOrEqual(vector, v2);
  }

  UINT d3GreaterOrEqualR(FXMVECTOR v2)
  {
    return XMVector3GreaterOrEqualR(vector, v2);
  }

  BOOL d3Less(FXMVECTOR v2) const
  {
    return XMVector3Less(vector, v2);
  }

  BOOL d3LessOrEqual(FXMVECTOR v2) const
  {
    return XMVector3LessOrEqual(vector, v2);
  }

  BOOL d3InBounds(FXMVECTOR bounds) const
  {
    return XMVector3InBounds(vector, bounds);
  }
  
  UINT d3InBoundsR(FXMVECTOR bounds) const
  {
    return XMVector3InBoundsR(vector, bounds);
  }

  BOOL d3IsNaN() const
  {
    return XMVector3IsNaN(vector);
  }

  BOOL d3IsInfinite() const
  {
    return XMVector3IsInfinite(vector);
  }

  XMFLOAT4  d3Dot(FXMVECTOR v2) const
  {
    XMVECTOR v = XMVector3Dot(vector, v2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }

  XMFLOAT4 d3Cross(FXMVECTOR v2) const
  {
    XMVECTOR v = XMVector3Cross(vector, v2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }
    
  XMFLOAT4 d3LengthSq() const
  {
    XMVECTOR v = XMVector3LengthSq(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }
  
  XMFLOAT4 d3ReciprocalLengthEst() const
  {  
    XMVECTOR v = XMVector3ReciprocalLengthEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }
  
  XMFLOAT4 d3ReciprocalLength() const
  {
    XMVECTOR v = XMVector3ReciprocalLength(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }
  
  XMFLOAT4 d3LengthEst() const
  {
    XMVECTOR v = XMVector3LengthEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4; 
  }

  XMFLOAT4 d3dTrasformCoord(CXMMATRIX m) const
  {
    XMVECTOR v = XMVector3TransformCoord(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d3dTrasformNormal(CXMMATRIX m) const
  {
    XMVECTOR v = XMVector3TransformNormal(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }


  XMFLOAT4 d3Transform(CXMMATRIX m) const
  {
    XMVECTOR	v = XMVector3Transform(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  } 
  
  XMFLOAT4 d3Length() const
  {  
    XMVECTOR v = XMVector3Length(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  XMFLOAT4 d3NormalizeEst() const
  {
    XMVECTOR v = XMVector3NormalizeEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  XMFLOAT4 d3Normalize() const
  {
    XMVECTOR v= XMVector3Normalize(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d3ClampLength(FLOAT lengthMin, FLOAT lengthMax) const
  {    
    XMVECTOR v = XMVector3ClampLength(vector, lengthMin, lengthMax);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
    
  XMFLOAT4  d3ClampLengthV(FXMVECTOR lengthMin, FXMVECTOR lengthMax) const
  {
    XMVECTOR v = XMVector3ClampLengthV(vector, lengthMin, lengthMax);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }    
    
  XMFLOAT4  d3Reflect(FXMVECTOR normal, FLOAT refractionIndex) const
  {
    XMVECTOR v = XMVector3Refract(vector, normal, refractionIndex);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  XMFLOAT4 d3RefractV(FXMVECTOR normal, FXMVECTOR refractionIndex) const
  {
    XMVECTOR v = XMVector3RefractV(vector, normal, refractionIndex);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4  d3Orthogonal() const
  {
    XMVECTOR v = XMVector3Orthogonal(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
    
  XMFLOAT4  d3AngleBetweenNormalsEst(FXMVECTOR n2) const
  {
    XMVECTOR v = XMVector3AngleBetweenNormalsEst(vector, n2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d3AngleBetweenNormals(FXMVECTOR n2) const
  {
    XMVECTOR v = XMVector3AngleBetweenNormals(vector, n2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
    
  XMFLOAT4 d3AngleBetweenVectors(FXMVECTOR v2)  const
  {  
    XMVECTOR v = XMVector3AngleBetweenVectors(vector, v2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
    
  XMFLOAT4 d3LinePointDistance(FXMVECTOR linePoint2, FXMVECTOR point) const
  {
    XMVECTOR v = XMVector3LinePointDistance(vector, linePoint2, point);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d3Rotate(FXMVECTOR rotationQuaternion) const
  {
    XMVECTOR v = XMVector3Rotate(vector, rotationQuaternion);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d3InverseRotate(FXMVECTOR rotationQuaternion) const
  {
    XMVECTOR v = XMVector3InverseRotate(vector, rotationQuaternion);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
      
  XMFLOAT4 d3TransformCoord(CXMMATRIX m) const
  {
    XMVECTOR v = XMVector3TransformCoord(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }


  XMFLOAT4 d3TransformNormal(CXMMATRIX m) const
  {
    XMVECTOR v = XMVector3TransformNormal(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
    
  XMFLOAT4  d3Project(FLOAT viewportX, 
                FLOAT viewportY, FLOAT viewportWidth, FLOAT viewportHeight, 
                FLOAT viewportMinZ, FLOAT viewportMaxZ, 
                CXMMATRIX projection, CXMMATRIX view, CXMMATRIX world)  const
  {  
    XMVECTOR v = XMVector3Project(vector, viewportX, 
                viewportY, viewportWidth, viewportHeight, 
                viewportMinZ, viewportMaxZ, 
                projection, view, world);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  XMFLOAT4  d3Unproject(FLOAT viewportX, 
                FLOAT viewportY, FLOAT viewportWidth, FLOAT viewportHeight, 
                FLOAT viewportMinZ, FLOAT viewportMaxZ, 
                CXMMATRIX projection, CXMMATRIX view, CXMMATRIX world) const
  {                  
    XMVECTOR v = XMVector3Unproject(vector, viewportX, 
                viewportY, viewportWidth, viewportHeight, 
                viewportMinZ, viewportMaxZ, 
                projection, view, world);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  BOOL d4Equal(FXMVECTOR v2) const
  {
    return XMVector4Equal(vector, v2);
  }
  
  UINT d4EqualR(FXMVECTOR v2) const
  {
    return XMVector4EqualR(vector, v2);
  }
  
  BOOL d4EqualInt(FXMVECTOR v2) const
  {
    return XMVector4EqualInt(vector, v2);
  }
  
  UINT d4EqualIntR(FXMVECTOR v2) const
  {
    return XMVector4EqualIntR(vector, v2);
  }
  
  BOOL d4NearEqual(FXMVECTOR v2, FXMVECTOR epsilon) const
  {
    return XMVector4NearEqual(vector, v2, epsilon);
  }
  
  BOOL d4NotEqual(FXMVECTOR v2) const
  {
    return XMVector4NotEqual(vector, v2);
  }
  
  BOOL d4NotEqualInt(FXMVECTOR v2) const
  {
    return XMVector4NotEqualInt(vector, v2);
  }
  
  BOOL d4Greater(FXMVECTOR v2) const
  {
    return XMVector4Greater(vector, v2);
  }
  
  UINT d4GreaterR(FXMVECTOR v2) const
  {
    return XMVector4GreaterR(vector, v2);
  }
  
  BOOL d4GreaterOrEqual(FXMVECTOR v2) const
  {
    return XMVector4GreaterOrEqual(vector, v2);
  }
  
  UINT d4GreaterOrEqualR(FXMVECTOR v2) const
  {
    return XMVector4GreaterOrEqualR(vector, v2);
  }
  
  BOOL d4Less(FXMVECTOR v2) const
  {
    return XMVector4Less(vector, v2);
  }
  
  BOOL d4LessOrEqual(FXMVECTOR v2) const
  {
    return XMVector4LessOrEqual(vector, v2);
  }
  
  BOOL d4InBounds(FXMVECTOR bounds) const
  {
    return XMVector4InBounds(vector, bounds);
  }
  
  UINT d4InBoundsR(FXMVECTOR bounds) const
  {
    return XMVector4InBoundsR(vector, bounds);
  }

  BOOL d4IsNaN() const
  {
    return XMVector4IsNaN(vector);
  }
  
  BOOL d4IsInfinite() const
  {
    return XMVector4IsInfinite(vector);
  }

  XMFLOAT4 d4Dot(FXMVECTOR v2) const
  {
    XMVECTOR v = XMVector4Dot(vector, v2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Cross(FXMVECTOR v2, FXMVECTOR v3) const
  {  
    XMVECTOR v = XMVector4Cross(vector, v2, v3);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4LengthSq() const
  {
    XMVECTOR v = XMVector4LengthSq(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4ReciprocalLengthEst() const
  {
    XMVECTOR v = XMVector4ReciprocalLengthEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4ReciprocalLength() const
  {
    XMVECTOR v = XMVector4ReciprocalLength(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4LengthEst() const
  {
    XMVECTOR v = XMVector4LengthEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Length() const
  {
    XMVECTOR v = XMVector4Length(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4NormalizeEst() const
  {  
    XMVECTOR v = XMVector4NormalizeEst(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Normalize() const
  {
    XMVECTOR v =XMVector4Normalize(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4ClampLength(FLOAT lengthMin, FLOAT lengthMax) const
  {
    XMVECTOR v = XMVector4ClampLength(vector, lengthMin, lengthMax);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4ClampLengthV(FXMVECTOR lengthMin, FXMVECTOR lengthMax) const
  {
    XMVECTOR v = XMVector4ClampLengthV(vector, lengthMin, lengthMax);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Reflect(FXMVECTOR normal) const
  {
    XMVECTOR v = XMVector4Reflect(vector, normal);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Refract(FXMVECTOR normal, FLOAT refractionIndex) const
  {
    XMVECTOR v = XMVector4Refract(vector, normal, refractionIndex);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4RefractV(FXMVECTOR normal, FXMVECTOR refractionIndex) const
  {
    XMVECTOR v = XMVector4RefractV(vector, normal, refractionIndex);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Orthogonal() const
  {
    XMVECTOR v = XMVector4Orthogonal(vector);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }
  
  XMFLOAT4 d4AngleBetweenNormalsEst(FXMVECTOR n2) const
  {
    XMVECTOR v = XMVector4AngleBetweenNormalsEst(vector, n2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4AngleBetweenNormals(FXMVECTOR n2) const
  {
    XMVECTOR v = XMVector4AngleBetweenNormals(vector, n2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4AngleBetweenVectors(FXMVECTOR v2) const
  {  
    XMVECTOR v = XMVector4AngleBetweenVectors(vector, v2);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

  XMFLOAT4 d4Transform(CXMMATRIX m) const
  {
    XMVECTOR v = XMVector4Transform(vector, m);
    XMFLOAT4 float4;
    XMStoreFloat4(&float4, v);
    return float4;
  }

};

}

