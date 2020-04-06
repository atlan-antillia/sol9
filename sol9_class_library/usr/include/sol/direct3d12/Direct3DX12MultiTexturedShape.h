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
 *  Direct3DX12MultiTexturedShape.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d12/Direct3D12Object.h>
#include <sol/direct3d12/Direct3D12Texture2D.h>
#include <sol/direct3d12/Direct3D12Subresources.h>
#include <sol/direct3d12/D3D12SubresourceData.h>
#include <sol/direct3d12/Direct3D12ShaderResourceView.h>

#include <sol/direct3d12/Direct3DX12MultiTexturedShape.h>
#include <sol/direct3d12/Direct3DX12TexturedFace.h>

namespace SOL {

template <size_t NUMBER_OF_FACES> class Direct3DX12MultiTexturedShape :public Direct3D12Object {

protected:
  ID3D12Device* device;
  UINT                                   descriptorHeapStart;
  SmartPtr<Direct3DX12TexturedFace>      faces[NUMBER_OF_FACES];
  SmartPtr<Direct3D12Texture2D>          texture2Ds         [NUMBER_OF_FACES];
  SmartPtr<Direct3D12Subresources>       subresources       [NUMBER_OF_FACES];
  SmartPtr<D3D12SubresourceData>         subresourceData    [NUMBER_OF_FACES];
  SmartPtr<Direct3D12ShaderResourceView> shaderResourceViews[NUMBER_OF_FACES];
  
public:
  Direct3DX12MultiTexturedShape(ID3D12Device* device,
                            int& width,
                            int& height,
                            
                            const wchar_t* filenames[],
                            size_t         countOfFilenames)
  :Direct3D12Object(),
    device(device)
  {
    if (device == NULL) {
      throw IException("Invalid parameter.");
    }
    if (filenames == NULL || countOfFilenames != NUMBER_OF_FACES) {
      throw IException("Invalid filenames parameters.");
    }
         
    for (size_t i = 0; i < NUMBER_OF_FACES; i++) {
      subresourceData[i] = createSubresourceData((UINT&)width, (UINT&)height, filenames[i]);
        
      texture2Ds[i]      = new Direct3D12Texture2D(device, width, height);
        
      subresources[i]    = new Direct3D12Subresources(device, *texture2Ds[i]);
    }    
  }

  D3D12SubresourceData* createSubresourceData(int width, int height, 
                      const wchar_t* filename)
  {
    D3D12SubresourceData* subresourceData = new D3D12SubresourceData();
    
    WCharModuleFileName moduleFileName;
    const wchar_t* dir = moduleFileName.getDir();
    wchar_t path[MAX_PATH];
    //swprintf_s(path, CountOf(path), L"%s\\..\\image\\%s", dir, filename);
    swprintf_s(path, CountOf(path), L"%s\\image\\%s", dir, filename);

    WICImagingFactory factory;
    WICBitmapFileReader reader(factory, (const wchar_t*)path);
      
    reader.read(width, height, *subresourceData);
    return subresourceData;
  }
    
  void update(ID3D12GraphicsCommandList* graphicsCommandList,
              ID3D12CommandAllocator*    commandAllocator,
              ID3D12CommandQueue*        commandQueue,
              Direct3D12CommonDescriptorHeap* commonDescriptrHeap,
              UINT                       heapStart,  //For example, specify SRV_HANDLE 
              Direct3D12Synchronizer*    synchronizer  )
  {       
    descriptorHeapStart = heapStart;
    for (size_t i = 0; i<NUMBER_OF_FACES; i++) {       
    
      subresources[i] -> update(graphicsCommandList,
                  commandAllocator,
                  commandQueue,
                  *subresourceData[i],
                  synchronizer);
        
      shaderResourceViews[i]  = new Direct3D12ShaderResourceView(device, 
                  commonDescriptrHeap->getCPUHandle(descriptorHeapStart + i),
                  *texture2Ds[i]);
      subresourceData[i] = NULL;
    }
  }
   

  virtual void draw(Direct3D12GraphicsCommandList* graphicsCommandList,
            Direct3D12CommonDescriptorHeap* commonDescriptorHeap)
  {
    try {
      for (size_t i = 0; i<NUMBER_OF_FACES; i++) {
        graphicsCommandList->setGraphicsRootDescriptorTable(SRV_HANDLE,
                  commonDescriptorHeap->getGPUHandle(descriptorHeapStart + i)); 
        faces[i] -> drawIndexedInstanced(graphicsCommandList);
      }
    } catch (Exception& ex) {
      ex.display();
    }
  }        
  
};

}
        