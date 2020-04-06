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
 *  Direct3D11DDisassembler.h
 *
 *****************************************************************************/

//2016/02/27

#pragma once

#include <sol/CharFileReader.h>
#include <sol/direct3d11/Direct3D11Blob.h>
#include <d3dcompiler.h>

/*
//----------------------------------------------------------------------------

#define D3D_DISASM_ENABLE_COLOR_CODE            0x00000001
#define D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS  0x00000002
#define D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING 0x00000004
#define D3D_DISASM_ENABLE_INSTRUCTION_CYCLE     0x00000008
#define D3D_DISASM_DISABLE_DEBUG_INFO           0x00000010

HRESULT WINAPI 
D3DDisassemble(__in_bcount(SrcDataSize) LPCVOID pSrcData,
               __in SIZE_T SrcDataSize,
               __in UINT Flags,
               __in_opt LPCSTR szComments,
               __out ID3DBlob** ppDisassembly);


*/

namespace SOL {

class Direct3D11Disassembler :public Direct3D11Blob {

public:
  Direct3D11Disassembler(
            __in  const void*  data,
            __in  size_t dataSize,
            __in UINT flags,
            __in_opt LPCSTR comment="")
  :Direct3D11Blob()
  {
    ID3DBlob* disassembly = NULL;    
    HRESULT hr = D3DDisassemble(
                data,
                dataSize,
                flags,
                comment,
                &disassembly);
    
    if (SUCCEEDED(hr)) {
      set(disassembly);
    } else {
      throw IException("Failed to D3DDisassemble.");
    }
  }
  
  
  
  ~Direct3D11Disassembler()
  {
  }
  

};

}


