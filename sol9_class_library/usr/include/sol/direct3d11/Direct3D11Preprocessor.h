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
 *  Direct3D11Preprocessor.h
 *
 *****************************************************************************/

//2016/02/27

#pragma once

#include <sol/CharFileReader.h>
#include <sol/direct3d11/Direct3D11Blob.h>
#include <d3dcompiler.h>

/*
HRESULT WINAPI
D3DPreprocess(__in_bcount(SrcDataSize) LPCVOID pSrcData,
              __in SIZE_T SrcDataSize,
              __in_opt LPCSTR pSourceName,
              __in_opt CONST D3D_SHADER_MACRO* pDefines,
              __in_opt ID3DInclude* pInclude,
              __out ID3DBlob** ppCodeText,
              __out_opt ID3DBlob** ppErrorMsgs);

*/

namespace SOL {

class Direct3D11Preprocessor :public Direct3D11Blob {

public:
  Direct3D11Preprocessor(
              __in  const void*  data,
              __in  size_t dataSize,
              __in_opt LPCSTR pSourceName = NULL,
              __in_opt CONST D3D_SHADER_MACRO* pDefines = NULL,
              __in_opt ID3DInclude* pInclude = NULL)
  :Direct3D11Blob()
  {
    ID3DBlob* preprocessed = NULL;
    ID3DBlob* errors       = NULL;
    
    HRESULT hr = D3DPreprocess(
                data,
                dataSize,
                pSourceName,
                pDefines,
                pInclude,
                &preprocessed,
                &errors);

    if (errors) {
      const char* message = (const char*)errors->GetBufferPointer();
      char* title = "Error";
      if (strstr(message, "warning")) {
        title = "Warning";
      }
      MessageBoxA(NULL, message, title, MB_OK);
      errors -> Release();
    }
    if (SUCCEEDED(hr)) {
      set(preprocessed);
    } else {
      throw IException("Failed to D3DPreprocess.");
    }
  }
  
public:
  Direct3D11Preprocessor(
              __in const CharFileReader* fileReader,
              __in_opt LPCSTR pSourceName = NULL,
              __in_opt CONST D3D_SHADER_MACRO* pDefines = NULL,
              __in_opt ID3DInclude* pInclude = NULL)
  :Direct3D11Blob()
  {
    if (fileReader == NULL) {
      throw IException("Invalid fileReader parameter.");  
    }
    
    ID3DBlob* preprocessed = NULL;
    ID3DBlob* errors        = NULL;
    
    HRESULT hr = D3DPreprocess(
                fileReader->getData(),
                fileReader->getDataSize(),
                pSourceName,
                pDefines,
                pInclude,
                &preprocessed,
                &errors);

    if (errors) {
      const char* message = (const char*)errors->GetBufferPointer();
      char* title = "Error";
      if (strstr(message, "warning")) {
        title = "Warning";
      }
      MessageBoxA(NULL, message, title, MB_OK);
      errors -> Release();
    }
    if (SUCCEEDED(hr)) {
      set(preprocessed);
    } else {
      throw IException("Failed to D3DPreprocess.");
    }
  }
  
  
  ~Direct3D11Preprocessor()
  {
  }
  

};

}


