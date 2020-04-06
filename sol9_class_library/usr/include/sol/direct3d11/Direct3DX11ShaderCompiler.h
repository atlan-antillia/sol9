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
 *  Direct3DX11ShaderCompiler.h
 *
 *****************************************************************************/

//2016/03/02 Updated

#pragma once

#include <sol/direct3d11/Direct3D11Blob.h>

namespace SOL {

class Direct3DX11ShaderCompiler :public Direct3D11Blob {
public:
  Direct3DX11ShaderCompiler(const TCHAR* filepath, 
            const char* profile ="fx_5_0",
            DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS)
  :Direct3D11Blob(
                filepath,     // LPCTSTR sourceFileName
                  NULL,       //LPCSTR  entryPoint,
                  profile,    // LPCSTR  profile
                  NULL,       //CONST D3D_SHADER_MACRO *pDefines
                  NULL,       //ID3DInclude *pInclude
                  shaderFlags,  //UINT aderCompileFlags
                  0)          // UINT effectCompileFlags
  
  { 
  }
  
  ~Direct3DX11ShaderCompiler()
  {
  }

};

}


