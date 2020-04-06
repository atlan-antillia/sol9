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
 *  Direct3D10Asynchronous.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10DeviceChild.h>

namespace SOL {
  
class Direct3D10Asynchronous : public Direct3D10DeviceChild {
public:
  Direct3D10Asynchronous()
  :Direct3D10DeviceChild()
  {

  }
  ~Direct3D10Asynchronous ()
  { 
  }

  operator ID3D10Asynchronous*()
  {
    return getAsynchronous();
  }

  ID3D10Asynchronous* getAsynchronous()
  {
    ID3D10Asynchronous* asynchronous = (ID3D10Asynchronous*)getIUnknown();
    if (asynchronous) {
      return asynchronous;
    } else {
      throw IException("ID3D10Asynchronous is NULL.")
    }
  }

  void begin( )
  {
    ID3D10Asynchronous* asyncronous = getAsynchronous();
    asyncronous -> Begin(); 
  }       

  void  end()
  {
    ID3D10Asynchronous* asyncronous = getAsynchronous();
    asyncronous -> End(); 
  }       
  
        
  void  getData( 
            __out void *pData,
            __in  UINT dataSize,
            __in  UINT getDataFlags)
  {
    ID3D10Asynchronous* asyncronous = getAsynchronous();
    HRESULT hr = asyncronous ->  GetData( 
            pData,
            dataSize,
            getDataFlags); 
    if (FAILED(hr)) {
      throw IException("Failed to GetData. HRESULT(0x%lx)", hr)
    }
  }

  UINT  getDataSize()
  {
    ID3D10Asynchronous* asyncronous = getAsynchronous();
    return asyncronous -> GetDataSize(); 
  }
};

}
