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
 *  Direct3DX12MultiTexturedCube.h
 *
 *****************************************************************************/

//2016/12/25 Update to use D3D12Box structure.

#pragma once
#include <sol/direct3d12/Direct3DX12MultiTexturedBox.h>


namespace SOL {

#define NUMBER_OF_BOX_FACES 6

class Direct3DX12MultiTexturedCube : public Direct3DX12MultiTexturedBox {

public:
  Direct3DX12MultiTexturedCube(ID3D12Device* device,
                            int& width,
                            int& height,
                            
                            const wchar_t* filenames[],
                            size_t         countOfFilenames,
                            float x = 0.0f,
                            float y = 0.0f,
                            float z = 0.0f)
                            
  :Direct3DX12MultiTexturedBox(device,
              width,
              height,
              filenames,
              countOfFilenames,
              D3D12Box(x, y, z, 1.0f, 1.0f, 1.0f) )
  {
  }
 
};
}
