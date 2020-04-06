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
 *  Direct3D10InputLayout.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d10/Direct3D10DeviceChild.h>

namespace SOL {

class Direct3D10InputLayout : public Direct3D10DeviceChild {
public:
 
  Direct3D10InputLayout(
    __in  ID3D10Device* device,
    __in  const D3D10_INPUT_ELEMENT_DESC *pInputElementDescs,
    __in  UINT numElements,
    __in  const void *pShaderBytecodeWithInputSignature,
    __in  SIZE_T bytecodeLength)
  :Direct3D10DeviceChild()
  {
    ID3D10InputLayout *inputLayout = NULL;
    HRESULT hr = device -> CreateInputLayout( 
        pInputElementDescs,
        numElements,
        pShaderBytecodeWithInputSignature,
        bytecodeLength,
        &inputLayout);
    if (SUCCEEDED(hr)) {
      set(inputLayout);
    } else {
      throw IException("Failed to CreateInputLayout. HRESULT(0x%lx)", hr)
    }
  }  

  ~Direct3D10InputLayout()
  {
  }

  operator ID3D10InputLayout*()
  {
    return getInputLayout();
  }

  ID3D10InputLayout* getInputLayout()
  {
    ID3D10InputLayout* inputLayout = (ID3D10InputLayout* )getIUnknown();
    if (inputLayout) {
      return inputLayout;
    } else {
      throw IException("ID3D10InputLayout is NULL.")
    }
  }
  
};

}

    
