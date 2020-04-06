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
 *  DirectXGIKeyedMutex.h
 *
 *****************************************************************************/

#pragma once

#include <sol/dxgi/DirectXGIDeviceSubObject.h>

namespace SOL {

class DirectXGIKeyedMutex : public DirectXGIDeviceSubObject {
public:
  DirectXGIKeyedMutex()
  :DirectXGIDeviceSubObject()
  {
  }
  
  ~DirectXGIKeyedMutex()
  {
  }
  
  operator IDXGIKeyedMutex*()
  {
    return getMutex();
  }
  
  IDXGIKeyedMutex* getMutex()
  {
    IDXGIKeyedMutex* mutex = (IDXGIKeyedMutex*)getIUnknown();
    if (mutex) {
      return mutex;
    } else {
      throw IException("IDXGIKeyedMutex is NULL.");
    }
  }
  
  void acquireSync( 
            __in UINT64 key,
            __in DWORD dwMilliseconds)
  {
    IDXGIKeyedMutex* mutex = getMutex();
    HRESULT hr = mutex -> AcquireSync( 
            key,
            dwMilliseconds);
    if (FAILED(hr)) {
      throw IException("Failed to AcquireSync. HRESULT(0x%lx)", hr);
    }
  }

  void releaseSync( 
            __in UINT64 key)
  {
    IDXGIKeyedMutex* mutex = getMutex();
    HRESULT hr = mutex -> ReleaseSync( 
            key);
    if (FAILED(hr)) {
      throw IException("Failed to ReleaseSync. HRESULT(0x%lx)", hr);
    }
  }
        
};
}
