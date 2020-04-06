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
 *  DirectXGIObject.h
 *
 *****************************************************************************/

// 2016/11/25 Added the following line
//#pragma comment(lib,"dxguid.lib")

#pragma once

#include <sol/Exception.h>
#include <sol/com/ComIUnknown.h>
#include <dxgi.h>
#ifdef WIN10
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#endif

#pragma comment(lib, "dxgi.lib" )

#pragma comment(lib,"dxguid.lib")

namespace {

class DirectXGIObject : public ComIUnknown {

public:
  DirectXGIObject()
  {
  }
  
  ~DirectXGIObject()
  {
  }

  operator IDXGIObject*()
  {
    return getGIObject();
  }
  
  IDXGIObject* getGIObject()
  {
    IDXGIObject* object = (IDXGIObject*)getIUnknown();
    if (object) {
      return object;
    } else {
      throw IException("IDXGIObject is NULL.");
    }
  }
  
  void setPrivateData( 
            __in REFGUID name,
            __in UINT dataSize,
            __in const void *pData) 
  {
    IDXGIObject* object = getGIObject();
    HRESULT hr = object -> SetPrivateData( 
            name,
            dataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateData. HRESULT(0x%lx)", hr);
    }
  }
      
  void setPrivateDataInterface( 
            __in REFGUID name,
            __in const IUnknown *pUnknown) 
  {
    IDXGIObject* object = getGIObject();
    HRESULT hr = object -> SetPrivateDataInterface( 
            name,
            pUnknown);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateDataInterface. HRESULT(0x%lx)", hr);
    }
  }
        
  void getPrivateData( 
            __in REFGUID name,
            __inout UINT *pDataSize,
            __out void *pData) 
  {
    IDXGIObject* object = getGIObject();
    HRESULT hr = object -> GetPrivateData( 
            name,
            pDataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetPrivateData. HRESULT(0x%lx)", hr);
    }
  }
        
  void getParent( 
            __in REFIID riid,
            __out void **ppParent) 
  {
    IDXGIObject* object = getGIObject();
    HRESULT hr = object -> GetParent( 
              riid,
              ppParent);
    if (FAILED(hr)) {
      throw IException("Failed to GetParent. HRESULT(0x%lx)", hr);
    }
  }
};
    
}
