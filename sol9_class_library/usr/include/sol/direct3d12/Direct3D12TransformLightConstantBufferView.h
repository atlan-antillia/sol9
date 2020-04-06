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
 *  Direct3D12TransformLightConstantBufferView.h
 *
 *****************************************************************************/

// 2016/10/15
// Simple constBufferView for D3D12ConstantBuffer (worldViewProject)
#pragma once

#include <sol/direct3d12/Direct3D12ConstantBufferView.h>

#include <sol/direct3d12/D3D12TransformLight.h>
#include <sol/direct3d12/DirectXTransformLight.h>

namespace SOL {

class Direct3D12TransformLightConstantBufferView : public Direct3D12ConstantBufferView {

public:
  Direct3D12TransformLightConstantBufferView(
    __in ID3D12Device* device,
    __in D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle //Handle gotten from Direct3D12CommonDescriptorHeap
     )
    :Direct3D12ConstantBufferView(
        device,
        cbvHandle,
        sizeof(D3D12TransformLight))
  {
  }

  ~Direct3D12TransformLightConstantBufferView()
  {
  }
  
  
  //Transformation for World, View, Projection, LightDirection, LightColor and OutputColor. 
  void update(DirectXTransformLight& lwvp)
  {
    D3D12TransformLight constantBuffer;
   
    constantBuffer.world          = DirectXMatrix::transpose(lwvp.world);
    constantBuffer.view           = DirectXMatrix::transpose(lwvp.view);
    constantBuffer.projection     = DirectXMatrix::transpose(lwvp.projection);

    constantBuffer.lightDirection = lwvp.lightDirection;
	  constantBuffer.lightColor     = lwvp.lightColor;
    
    Direct3D12ConstantBufferView::update((void*)&constantBuffer, sizeof(constantBuffer));
    
  }

};

}

