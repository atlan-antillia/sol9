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
 *  Direct3DBlob.h
 *
 *****************************************************************************/

//2016/10/01

#pragma once

#include <sol/CharFileReader.h>
#include <sol/FileAttributes.h>
#include <sol/com/ComIUnknown.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

namespace SOL {

class Direct3DBlob : public ComIUnknown {
protected:
  Direct3DBlob()
  :ComIUnknown()
  {
  }
  
public:
  Direct3DBlob(__in ID3DBlob* blob)
  :ComIUnknown()
  {
    if (blob) {
      set(blob);
    } else {
      throw IException("Invalid argument. ID3DBlob is NULL.");
    }
  }

public:
  Direct3DBlob(
      __in     CharFileReader* fileReader,
      __in     LPCSTR  entryPoint,  
      __in     LPCSTR  profile,        
      __in_opt    CONST D3D_SHADER_MACRO *pDefines = NULL, 
      __in_opt    ID3DInclude *pInclude  =  NULL, 
      __in_opt    UINT shaderCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
      __in_opt    UINT effectCompileFlags = 0)

  :ComIUnknown()
  {
    if (fileReader == NULL) {
      throw IException("Invalid fileReader parameter.");
    }
        
    compile(
            fileReader->getData(),     
            fileReader->getDataSize(), 
            NULL,          
            entryPoint,    
            profile,       
            pDefines,      
            pInclude,      
            shaderCompileFlags, 
            effectCompileFlags);
  }
  
public:
  Direct3DBlob(
          __in   LPCTSTR sourceFileName,    
          __in   LPCSTR  entryPoint,  
          __in   LPCSTR  profile,        
          __in_opt CONST D3D_SHADER_MACRO *pDefines = NULL, 
          __in_opt ID3DInclude *pInclude  =  NULL, 
          __in_opt UINT shaderCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
          __in_opt UINT effectCompileFlags = 0)

  :ComIUnknown()
  {
    CharFileReader fileReader(sourceFileName);

    compile(
            fileReader.getData(),            
            fileReader.getDataSize(),
            NULL,      
            entryPoint,      
            profile,         
            pDefines,        
            pInclude,        
            shaderCompileFlags, 
            effectCompileFlags);
  }
    
public:
  Direct3DBlob(
          __in   LPCSTR data, 
          __in   SIZE_T dataLength, 
          __in   LPCSTR sourceName, 
          __in   LPCSTR entryPoint,
          __in   LPCSTR profile,
          __in_opt  CONST D3D_SHADER_MACRO *pDefines = NULL, 
          __in_opt  ID3DInclude *pInclude = NULL, 
          __in_opt  UINT shaderCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS,
          __in_opt  UINT effectCompileFlags = 0)
  :ComIUnknown()
  {
    if (data == NULL) {
      throw IException("Invalid data parameter.");
    }
    
    compile(
            data,            
            dataLength,      
            sourceName,   
            entryPoint,
            profile,
            pDefines,        
            pInclude,        
            shaderCompileFlags, 
            effectCompileFlags);
  }
  
  
  ~Direct3DBlob()
  {
  }

  void compile(
          __in   LPCVOID data,       
          __in   SIZE_T dataLength, 
          __in   LPCSTR sourceName, 
          __in   LPCSTR entryPoint,
          __in   LPCSTR profile,
          __in  CONST D3D_SHADER_MACRO* pDefines, 
          __in  ID3DInclude* pInclude, 
          __in  UINT shaderCompileFlags,
          __in  UINT effectCompileFlags)
  {  
    ID3DBlob *shader = NULL;
    ID3DBlob *errors = NULL;
    HRESULT hr = D3DCompile(
            data,            
            dataLength,      
            sourceName,      
            pDefines,        
            pInclude,        
            entryPoint,      
            profile,         
            shaderCompileFlags,
            effectCompileFlags,
            &shader,
            &errors);
    if (errors) {
      const char* msg = (const char*)errors->GetBufferPointer();
      const char* title = "Error";
      if (strstr(msg, "warning")) {
        title = "Warning";
      }
      MessageBoxA(NULL,(const char*)msg, title, MB_OK);
      errors->Release();
      errors = NULL;
    }
    
    if (SUCCEEDED(hr)) {
      set(shader);
    } else {
      throw IException("Failed to D3DCompile. HRESULT(0x%lx)", hr);
    }
  }
    
  operator   ID3DBlob*()
  {
    return getBlob();
  }

  ID3DBlob* getBlob()
  {
    ID3DBlob* blob = (ID3DBlob*)getIUnknown();
    if (blob) {
        return blob;
    } else {
        throw IException("ID3DBlob is NULL.")
    }
  }

  void*  getBufferPointer()
  {
    ID3DBlob* blob = getBlob();
    return blob -> GetBufferPointer();
  }

  SIZE_T getBufferSize()
  {
    ID3DBlob* blob = getBlob();
    return blob -> GetBufferSize();
  }

//2015/03/03
  void getInputSignature(__out ID3DBlob** ppSignature)
  {
    HRESULT hr = D3DGetInputSignatureBlob(
            getBufferPointer(),
            getBufferSize(),
            ppSignature);
    if (FAILED(hr)) {
      throw IException("Failed to D3DGetInputSignatureBlob"); 
    }
  }
  
  void getOutputSignature(__out ID3DBlob** ppSignature)
  {
    HRESULT hr = D3DGetOutputSignatureBlob(
            getBufferPointer(),
            getBufferSize(),
            ppSignature);
    if (FAILED(hr)) {
      throw IException("Failed to D3DGetInputSignatureBlob"); 
    }

  }
  

  void getInputAndOutputSignature(__out ID3DBlob** ppSignature)
  {
    HRESULT hr = D3DGetInputAndOutputSignatureBlob(
            getBufferPointer(),
            getBufferSize(),
            ppSignature);
    if (FAILED(hr)) {
      throw IException("Failed to D3DGetInputAndOutputSignatureBlob"); 
    }
  }
  
/*
typedef enum D3D_BLOB_PART
{
    D3D_BLOB_INPUT_SIGNATURE_BLOB,
    D3D_BLOB_OUTPUT_SIGNATURE_BLOB,
    D3D_BLOB_INPUT_AND_OUTPUT_SIGNATURE_BLOB,
    D3D_BLOB_PATCH_CONSTANT_SIGNATURE_BLOB,
    D3D_BLOB_ALL_SIGNATURE_BLOB,
    D3D_BLOB_DEBUG_INFO,
    D3D_BLOB_LEGACY_SHADER,
    D3D_BLOB_XNA_PREPASS_SHADER,
    D3D_BLOB_XNA_SHADER,

    // Test parts are only produced by special compiler versions and so
    // are usually not present in shaders.
    D3D_BLOB_TEST_ALTERNATE_SHADER = 0x8000,
    D3D_BLOB_TEST_COMPILE_DETAILS,
    D3D_BLOB_TEST_COMPILE_PERF,
} D3D_BLOB_PART;  
  */

  void getBlobPart(
               __in D3D_BLOB_PART part,
               __in UINT flags,
               __out ID3DBlob** ppPart)
  {
    HRESULT hr = D3DGetBlobPart(
            getBufferPointer(),
            getBufferSize(),

            part,
            flags,
            ppPart);
    if (FAILED(hr)) {
      throw IException("Failed to D3DGetBlobPart."); 
    }
  }

};

}
