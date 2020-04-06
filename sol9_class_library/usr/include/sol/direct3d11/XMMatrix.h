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
 *  XMMatrix.h
 *
 *****************************************************************************/

//2016/03/02
//2016/03/10 Updated.


#pragma once

#include <xnamath.h>

namespace SOL {

class XMMatrix {
private:
  XMFLOAT4X4  matrix;
  
public:
  XMMatrix() 
  {
    XMMATRIX identify = XMMatrixIdentity();
    XMStoreFloat4x4(&matrix, identify);
  }
  
  XMMatrix(const XMMATRIX& mat) 
  {
    XMStoreFloat4x4(&matrix, mat);
  }

  XMMatrix(XMFLOAT4 f1, XMFLOAT4 f2, XMFLOAT4 f3, XMFLOAT4 f4)
  {
    XMMATRIX mat = XMMatrixSet(
          f1.x, f1.y, f1.z, f1.w,
          f2.x, f2.y, f2.z, f2.w,
          f3.x, f3.y, f3.z, f3.w,
          f4.x, f4.y, f4.z, f4.w);

    XMStoreFloat4x4(&matrix, mat);
  }    
  
  XMMatrix(FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
           FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
           FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
           FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33)
  {
    XMMATRIX mat = XMMatrixSet(m00, m01, m02, m03,
                            m10,  m11,  m12,  m13,
                            m20,  m21,  m22,  m23,
                            m30,  m31,  m32,  m33);
    XMStoreFloat4x4(&matrix, mat);
  }

  XMMatrix(const XMFLOAT4X4& float4x4) 
  {
    matrix = float4x4;
  }

  XMMatrix(const XMMatrix& mat) 
  {
    XMMATRIX m = mat.getXMMATRIX();
    XMStoreFloat4x4(&matrix, m);
  }

  operator  XMFLOAT4X4*()
  {
    return &matrix;
  }

  operator  XMFLOAT4X4()
  {
    return matrix;
  }
  
  operator  XMMATRIX() const
  {
    return XMLoadFloat4x4(&matrix);
  }

  XMFLOAT4X4* getXMFLOAT4X4()
  {
    return &matrix;
  }
  
  XMMATRIX  getXMMATRIX() const
  {
    return XMLoadFloat4x4(&matrix);
  }
  
  XMMatrix& operator =(XMMATRIX& mat)
  {
    XMStoreFloat4x4(&matrix, mat);
    return *this;
  }
  
  
  XMMatrix& operator *=(XMMATRIX& y)
  {
    XMMATRIX x = getXMMATRIX();
    x *= y;
    XMStoreFloat4x4(&matrix, x);
    return *this;
  }

  XMMatrix& operator *=(XMMatrix& mat)
  {
    XMMATRIX x = getXMMATRIX();
    XMMATRIX y = mat.getXMMATRIX();
    x *= y;    
    XMStoreFloat4x4(&matrix, x);
    return *this;
  }
  
  XMFLOAT4X4 operator *(XMMatrix& mat)
  {
    XMMATRIX x = getXMMATRIX();
    XMMATRIX y = mat.getXMMATRIX();
    x *= y; 
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, x);
    return float4x4;
  }
  
  //2016/03/10
  XMMatrix& operator +=(XMMatrix& mat)
  {
    XMMATRIX x = getXMMATRIX();
    XMMATRIX y = mat.getXMMATRIX();
    
    for (int s = 0; s<4; s++) {
      x.r[s] = x.r[s] + y.r[s];
    }
    XMStoreFloat4x4(&matrix, x);
    return *this;
  }

  XMFLOAT4X4 operator +(XMMatrix& mat)
  {
    XMMATRIX x = getXMMATRIX();
    XMMATRIX y = mat.getXMMATRIX();
    
    for (int s = 0; s<4; s++) {
      x.r[s] = x.r[s] + y.r[s];
    }
    
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, x);
    return float4x4;
  }

  XMFLOAT4X4  transpose()
  {
    XMMATRIX mat = XMMatrixTranspose(getXMMATRIX());
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static
  XMFLOAT4X4  multiply(CXMMATRIX m1, CXMMATRIX m2)
  {
    XMMATRIX mat = XMMatrixMultiply(m1, m2);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
    
  static
  XMFLOAT4X4  multiplyTranspose(CXMMATRIX m1, CXMMATRIX m2)
  {
    XMMATRIX mat = XMMatrixMultiplyTranspose(m1, m2);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
    
  static
  XMFLOAT4X4  inverse(_Out_ XMVECTOR* pDeterminant, CXMMATRIX m)
  {
    XMMATRIX mat = XMMatrixInverse(pDeterminant, m);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
   
  static
  XMFLOAT4X4  identity()
  {
    XMMATRIX mat = XMMatrixIdentity();
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
    
  static
  XMFLOAT4X4  set(FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
                         FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
                         FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
                         FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33)
  {
    XMMATRIX mat = XMMatrixSet(m00, m01, m02, m03,
                            m10,  m11,  m12,  m13,
                            m20,  m21,  m22,  m23,
                            m30,  m31,  m32,  m33);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static   
  XMFLOAT4X4  transpose(XMMatrix& m)
  {
    XMMATRIX mat = XMMatrixTranspose((XMMATRIX)m);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }

  //2016/03/10
  static   
  XMFLOAT4X4  transpose(XMMATRIX& m)
  {
    XMMATRIX mat = XMMatrixTranspose(m);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static
  XMFLOAT4X4 translation(XMFLOAT3& point)
  {
    XMMATRIX mat = XMMatrixTranslation(point.x, point.y, point.z);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static
  XMFLOAT4X4 translation(FLOAT x, FLOAT y, FLOAT z)
  {
    XMMATRIX mat = XMMatrixTranslation(x, y, z);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }

  static
  XMFLOAT4X4 scaling(XMFLOAT3& point)
  {
    XMMATRIX mat = XMMatrixScaling(point.x, point.y, point.z);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static
  XMFLOAT4X4 scaling(FLOAT x, FLOAT y, FLOAT z)
  {
    XMMATRIX mat = XMMatrixScaling(x, y, z);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;
  }
  
  static
  XMFLOAT4X4 scalingFromVector(FXMVECTOR scale)
  {
    XMMATRIX mat= XMMatrixScalingFromVector(scale);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;    
  }
  
  static 
  XMFLOAT4X4 translationFromVector(FXMVECTOR vector)
  {
    XMMATRIX mat = XMMatrixTranslationFromVector( vector) ;
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;  
  }
  
  static 
  XMFLOAT4X4 rotationX(FLOAT angle)
  {
    XMMATRIX mat = XMMatrixRotationX(angle);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }

  static 
  XMFLOAT4X4 rotationY(FLOAT angle)
  {
    XMMATRIX mat = XMMatrixRotationY(angle);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }

  static 
  XMFLOAT4X4 rotationZ(FLOAT angle)
  {
    XMMATRIX mat = XMMatrixRotationZ(angle);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 rotationRollPitchYaw(FLOAT pitch, FLOAT yaw, FLOAT roll)
  {
  
    XMMATRIX mat = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
    
  static 
  XMFLOAT4X4 rotationRollPitchYawFromVector(FXMVECTOR angles)
  {
    XMMATRIX mat = XMMatrixRotationRollPitchYawFromVector(angles);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
    
  static 
  XMFLOAT4X4 rotationNormal(FXMVECTOR normalAxis, FLOAT angle)
  {
    XMMATRIX mat = XMMatrixRotationNormal(normalAxis, angle);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
    
  static 
  XMFLOAT4X4 rotationAxis(FXMVECTOR axis, FLOAT angle)
  {
    XMMATRIX mat = XMMatrixRotationAxis(axis, angle);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
    
  static 
  XMFLOAT4X4 rotationQuaternion(FXMVECTOR quaternion)
  {
    XMMATRIX mat = XMMatrixRotationQuaternion(quaternion);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 transformation2D(FXMVECTOR scalingOrigin, FLOAT scalingOrientation, FXMVECTOR scaling, 
                    FXMVECTOR rotationOrigin, FLOAT rotation, CXMVECTOR translation)
  {
    XMMATRIX mat = XMMatrixTransformation2D(scalingOrigin, scalingOrientation, scaling, 
                      rotationOrigin, rotation, translation);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 transformation(FXMVECTOR scalingOrigin, FXMVECTOR scalingOrientationQuaternion, FXMVECTOR scaling, 
                    CXMVECTOR rotationOrigin, CXMVECTOR rotationQuaternion, CXMVECTOR translation)
  {
    XMMATRIX  mat = XMMatrixTransformation(scalingOrigin, scalingOrientationQuaternion, scaling, 
                      rotationOrigin, rotationQuaternion, translation);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 affineTransformation2D(FXMVECTOR scaling, FXMVECTOR rotationOrigin, FLOAT rotation, FXMVECTOR translation)
  {
    XMMATRIX  mat = XMMatrixAffineTransformation2D(scaling, rotationOrigin, rotation, translation);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 affineTransformation(FXMVECTOR scaling, FXMVECTOR rotationOrigin, FXMVECTOR rotationQuaternion, CXMVECTOR translation)
  {
    XMMATRIX  mat = XMMatrixAffineTransformation(scaling, rotationOrigin, rotationQuaternion, translation);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 reflect(FXMVECTOR reflectionPlane)
  {
    XMMATRIX  mat = XMMatrixReflect(reflectionPlane);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 shadow(FXMVECTOR shadowPlane, FXMVECTOR lightPosition)
  {
    XMMATRIX  mat = XMMatrixShadow(shadowPlane, lightPosition);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 lookAtLH(FXMVECTOR eyePosition, FXMVECTOR focusPosition, FXMVECTOR upDirection)
  {
    XMMATRIX  mat = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 lookAtRH(FXMVECTOR eyePosition, FXMVECTOR focusPosition, FXMVECTOR upDirection)
  {
    XMMATRIX  mat = XMMatrixLookAtRH(eyePosition, focusPosition, upDirection);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 lookToLH(FXMVECTOR eyePosition, FXMVECTOR eyeDirection, FXMVECTOR upDirection)
  {
    XMMATRIX  mat = XMMatrixLookToLH(eyePosition, eyeDirection, upDirection);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 lookToRH(FXMVECTOR eyePosition, FXMVECTOR eyeDirection, FXMVECTOR upDirection)
  {
    XMMATRIX  mat = XMMatrixLookToRH(eyePosition, eyeDirection, upDirection);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  static 
  XMFLOAT4X4 perspectiveLH(FLOAT viewWidth, FLOAT viewHeight, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 perspectiveRH(FLOAT viewWidth, FLOAT viewHeight, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 perspectiveFovLH(FLOAT fovAngleY, FLOAT aspectHByW, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveFovLH(fovAngleY, aspectHByW, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 perspectiveFovRH(FLOAT fovAngleY, FLOAT aspectHByW, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveFovRH(fovAngleY, aspectHByW, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 perspectiveOffCenterLH(FLOAT viewLeft, FLOAT viewRight, FLOAT viewBottom, FLOAT viewTop, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 perspectiveOffCenterRH(FLOAT viewLeft, FLOAT viewRight, FLOAT viewBottom, FLOAT viewTop, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 orthographicLH(FLOAT viewWidth, FLOAT viewHeight, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 orthographicRH(FLOAT viewWidth, FLOAT viewHeight, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 orthographicOffCenterLH(FLOAT viewLeft, FLOAT viewRight, FLOAT viewBottom, FLOAT viewTop, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
  
  static 
  XMFLOAT4X4 orthographicOffCenterRH(FLOAT viewLeft, FLOAT viewRight, FLOAT viewBottom, FLOAT viewTop, FLOAT nearZ, FLOAT farZ)
  {
    XMMATRIX  mat = XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
    XMFLOAT4X4 float4x4;
    XMStoreFloat4x4(&float4x4, mat);
    return float4x4;      
  }
};

}

