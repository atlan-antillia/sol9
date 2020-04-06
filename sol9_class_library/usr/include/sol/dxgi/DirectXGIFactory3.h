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
 *  DirectXGIFactory3.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIFactory2.h>
#ifdef WIN10
#include <dxgi1_3.h>  //C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared
#endif

namespace SOL {

class DirectXGIFactory3 : public DirectXGIFactory2 {

public:
  DirectXGIFactory3()
  :DirectXGIFactory2()
  {
    IDXGIFactory3* factory3 = NULL;
	  HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory3), (void**)&factory3);
    if (SUCCEEDED(hr)) {
      set(factory3);
    } else {
		  throw IException("Failed to Get IDXGIFactory3. HRESULT(0x%lx)", hr);
    }
  }
  
  
  operator IDXGIFactory3*()
  {
    return getFactory3();
  }
  
  IDXGIFactory3* getFactory3()
  {
    IDXGIFactory3* factory3 = (IDXGIFactory3*)getIUnknown();
    if (factory3) {
      return factory3;
    } else {
      throw IException("IDXGIFactory3 is NULL.");
    }
  }
 
  UINT getCreationFlags()
  {
    IDXGIFactory3* factory3 = getFactory3();
    return factory3 -> GetCreationFlags();
  }
  
};

}
            