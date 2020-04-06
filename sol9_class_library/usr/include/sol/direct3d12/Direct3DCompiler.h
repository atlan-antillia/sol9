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
 *  Direct3DCompiler.h
 *
 *****************************************************************************/

//2016/10/01

#pragma once

#include <sol/direct3d12/Direct3DBlob.h>

/*

HRESULT WINAPI
D3DCompile(__in_bcount(SrcDataSize) LPCVOID pSrcData,
           __in SIZE_T SrcDataSize,
           __in_opt LPCSTR pSourceName,
           __in_xcount_opt(pDefines->Name != NULL) CONST D3D_SHADER_MACRO* pDefines,
           __in_opt ID3DInclude* pInclude,
           __in LPCSTR pEntrypoint,
           __in LPCSTR pTarget,
           __in UINT Flags1,
           __in UINT Flags2,
           __out ID3DBlob** ppCode,
           __out_opt ID3DBlob** ppErrorMsgs);
*/

/*----------------------------------------------------------------------------
C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DCompiler.h
 compileFlags :

 D3DCOMPILE_DEBUG
 D3DCOMPILE_SKIP_VALIDATION
 D3DCOMPILE_SKIP_OPTIMIZATION 
 D3DCOMPILE_PACK_MATRIX_ROW_MAJOR
 D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR
 D3DCOMPILE_PARTIAL_PRECISION
 D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT
 D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT
 D3DCOMPILE_NO_PRESHADER
 D3DCOMPILE_AVOID_FLOW_CONTROL
 D3DCOMPILE_PREFER_FLOW_CONTROL
 D3DCOMPILE_ENABLE_STRICTNESS
 D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY

effectFlags:

 D3DCOMPILE_EFFECT_CHILD_EFFECT
 D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS

*/

namespace SOL {

class Direct3DCompiler :public Direct3DBlob {
public:
  Direct3DCompiler(
          __in    CharFileReader* fileReader,
          __in    const char* entryPoint,
          __in_opt  const char* profile ="fx_5_0", 
          __in_opt  CONST D3D_SHADER_MACRO* pDefines = NULL,
          __in_opt  ID3DInclude* pInclude = NULL,
          __in_opt  DWORD compileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
          __in_opt  DWORD effectFlags = 0)
  :Direct3DBlob(
            fileReader,
            entryPoint,
            profile, 
            pDefines,
            pInclude,
            compileFlags,
            effectFlags)
  {
  }
  
public:  
 Direct3DCompiler(
          __in   LPCTSTR sourceFileName,    
          __in    const char* entryPoint,
          __in_opt  const char* profile ="fx_5_0", 
          __in_opt CONST D3D_SHADER_MACRO *pDefines = NULL, 
          __in_opt ID3DInclude *pInclude  =  NULL, 
          __in_opt UINT shaderCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
          __in_opt UINT effectCompileFlags = 0)
  :Direct3DBlob(
            sourceFileName,    
            entryPoint,  
            profile,        
            pDefines, 
            pInclude, 
            shaderCompileFlags,
            effectCompileFlags)
  {
  }
  
public:
  Direct3DCompiler(
          __in    const char* data,
          __in    size_t dataSize,
          __in    const char* sourceName,
          __in    const char* entryPoint,
          __in_opt  const char* profile ="fx_5_0", 
          __in_opt  CONST D3D_SHADER_MACRO* pDefines = NULL,
          __in_opt  ID3DInclude* pInclude = NULL,
          __in_opt  DWORD shaderCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
          __in_opt  DWORD effectCompileFlags = 0)
  :Direct3DBlob(
            data, 
            dataSize, 
            sourceName, 
            entryPoint,
            profile,
            pDefines, 
            pInclude, 
            shaderCompileFlags ,
            effectCompileFlags)
  {
  }


  ~Direct3DCompiler()
  {
  }


};

}


