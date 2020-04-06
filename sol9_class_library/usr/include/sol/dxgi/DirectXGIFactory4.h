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
 *  DirectXGIFactory4.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIFactory3.h>
#ifdef WIN10
#include <dxgi1_4.h>  //C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared
#endif

namespace SOL {

class DirectXGIFactory4 : public DirectXGIFactory3 {

public:
  DirectXGIFactory4()
  :DirectXGIFactory3()
  {
    IDXGIFactory4* factory4 = NULL;
	  //HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&factory4);
	  HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG  ,__uuidof(IDXGIFactory4), (void**)&factory4);

    if (SUCCEEDED(hr)) {
      set(factory4);
    } else {
		  throw IException("Failed to CreateDXGIFactory1. HRESULT(0x%lx)", hr);
    }
  }
  
  
  operator IDXGIFactory4*()
  {
    return getFactory4();
  }
  
  IDXGIFactory4* getFactory4()
  {
    IDXGIFactory4* factory4 = (IDXGIFactory4*)getIUnknown();
    if (factory4) {
      return factory4;
    } else {
      throw IException("IDXGIFactory4 is NULL.");
    }
  }
 
  void enumAdapterByLuid( 
            _In_  LUID adapterLuid,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppvAdapter)
  {
    IDXGIFactory4* factory4 = getFactory4();
    factory4 -> EnumAdapterByLuid( 
            adapterLuid,
            riid,
            ppvAdapter);
  }
  
  void enumWarpAdapter( 
            _In_  REFIID riid,
            _COM_Outptr_  void **ppvAdapter)  
  {
    IDXGIFactory4* factory4 = getFactory4();
    factory4 -> EnumWarpAdapter( 
            riid,
            ppvAdapter);
  }
};

}
