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
 *  Direct3D12Object.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <DXGItype.h>
#include <sol/Stdio.h>
#include <sol/com/ComIUnknown.h>

#include <d3d12.h>
#include <dxgi.h>

#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <sol/direct3dcommon/XMColor.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d12.lib")

namespace SOL {

class Direct3D12Object : public ComIUnknown {
    
public:
public:
  Direct3D12Object(
    __in ID3D12Object* object=NULL)
  :ComIUnknown(object)
  {
  }
  
  ~Direct3D12Object()
  { 
  }

   
  operator ID3D12Object*()
  {
    return getObject();
  }

  ID3D12Object* getObject()
  {
    ID3D12Object* object = (ID3D12Object*)getIUnknown();
    if (object) {
        return object;
    } else {
      throw IException("ID3D12Object is NULL.");
    }
  }

  void getPrivateData( 
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData)
  {
    ID3D12Object* object = getObject();
    HRESULT hr = object->GetPrivateData( 
            guid,
            pDataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetPrivateData. hr=%ld", hr);
    }
  }
  
  void setPrivateData( 
            _In_  REFGUID guid,
            _In_  UINT dataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData)
  {
    ID3D12Object* object = getObject();

    HRESULT hr = object -> SetPrivateData( 
            guid,
            dataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateData. hr=%ld", hr);
    }
  }
  
  void setPrivateDataInterface( 
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData)
  {
    ID3D12Object* object = getObject();

    HRESULT hr = object -> SetPrivateDataInterface( 
            guid,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateDataInterface. hr=%ld", hr);
    }    
  }
  
  void setName( 
            _In_z_  LPCWSTR name)
  {
    ID3D12Object* object = getObject();

    HRESULT hr = object-> SetName( 
            name);
    if (FAILED(hr)) {
      throw IException("Failed to SetName. hr=%ld", hr);
    }    
  }
};

}
    

    