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
 *  Direct3DX11EffectVariablesTable.h
 *
 *****************************************************************************/
 
//2015/12/01
// This is a simple HashTable based effect variables manager.

#pragma once

#include <sol/HashTable.h>
#include <sol/Pair.h>

#include <sol/direct3d11/Direct3DX11Effect.h>

#include <sol/direct3d11/Direct3DX11EffectTechnique.h>
#include <sol/direct3d11/Direct3DX11EffectConstantBuffer.h>

#include <sol/direct3d11/Direct3DX11EffectBlendVariable.h>
#include <sol/direct3d11/Direct3DX11EffectDepthStencilVariable.h>
#include <sol/direct3d11/Direct3DX11EffectDepthStencilViewVariable.h>
#include <sol/direct3d11/Direct3DX11EffectMatrixVariable.h>
#include <sol/direct3d11/Direct3DX11EffectRasterizerVariable.h>
#include <sol/direct3d11/Direct3DX11EffectRenderTargetViewVariable.h>
#include <sol/direct3d11/Direct3DX11EffectSamplerVariable.h>
#include <sol/direct3d11/Direct3DX11EffectScalarVariable.h>
#include <sol/direct3d11/Direct3DX11EffectShaderResourceVariable.h>
#include <sol/direct3d11/Direct3DX11EffectShaderVariable.h>
#include <sol/direct3d11/Direct3DX11EffectStringVariable.h>
#include <sol/direct3d11/Direct3DX11EffectVariable.h>
#include <sol/direct3d11/Direct3DX11EffectVectorVariable.h>

namespace SOL {

class Direct3DX11EffectVariablesTable : public Direct3DX11Effect {

private:
  HashTable* hashTable;

public:
  //Constructor 
  
  Direct3DX11EffectVariablesTable(ID3D11Device* device, 
      const TCHAR* filename,
      Pair<const TCHAR*, const char*>* pairs, int count)
  
  :Direct3DX11Effect( device, filename),
  hashTable(NULL)
  {
    hashTable = new HashTable(117);
    try {
          
        for (int i = 0; i < count; i++) {
          Pair<const TCHAR*, const char*> pair = pairs[i];
          const TCHAR* type = pair.first;
          const char*  name = pair.second;
          if (type != NULL && name != NULL) {
            
            if (type == XmNtechnique) {
              Direct3DX11EffectTechnique* technique = new Direct3DX11EffectTechnique( getTechniqueByName(name) );
              hashTable -> add(name, technique);
            
            }
            else if (type == XmNasMatrix) {
              Direct3DX11EffectMatrixVariable* variable = new Direct3DX11EffectMatrixVariable( getVariableByName(name)->AsMatrix());  
              hashTable -> add(name, variable);
            }
           
            else if (type == XmNasVector) {
              Direct3DX11EffectVectorVariable* variable = new Direct3DX11EffectVectorVariable( getVariableByName(name)->AsVector());
              hashTable -> add(name, variable);
            }
            else if (type == XmNasScalar) {
              Direct3DX11EffectScalarVariable* scalar = new Direct3DX11EffectScalarVariable( getVariableByName(name)->AsScalar());  
              hashTable -> add(name, scalar);
            }
            else if (type == XmNasShaderResource) {
              Direct3DX11EffectShaderResourceVariable* shaderResource = new Direct3DX11EffectShaderResourceVariable( getVariableByName(name) -> AsShaderResource() );    
              hashTable -> add(name, shaderResource);
            }
            else if (type == XmNasString) {
              Direct3DX11EffectStringVariable* variable = new Direct3DX11EffectStringVariable( getVariableByName(name) -> AsString() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasRenderTargetView) {
              Direct3DX11EffectRenderTargetViewVariable* variable = new Direct3DX11EffectRenderTargetViewVariable( getVariableByName(name) -> AsRenderTargetView() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasDepthStencilView) {
              Direct3DX11EffectDepthStencilViewVariable* variable = new Direct3DX11EffectDepthStencilViewVariable( getVariableByName(name) -> AsDepthStencilView() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasConstantBuffer) {
              Direct3DX11EffectConstantBuffer* variable = new Direct3DX11EffectConstantBuffer( getVariableByName(name) -> AsConstantBuffer() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasShader) {
              Direct3DX11EffectShaderVariable* variable = new Direct3DX11EffectShaderVariable( getVariableByName(name) -> AsShader() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasBlend) {
              Direct3DX11EffectBlendVariable* variable = new Direct3DX11EffectBlendVariable( getVariableByName(name) -> AsBlend() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasDepthStencil) {
              Direct3DX11EffectDepthStencilVariable* variable = new Direct3DX11EffectDepthStencilVariable( getVariableByName(name) -> AsDepthStencil() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasRasterizer) {
              Direct3DX11EffectRasterizerVariable* variable = new Direct3DX11EffectRasterizerVariable( getVariableByName(name) -> AsRasterizer() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasSampler) {
              Direct3DX11EffectSamplerVariable* variable = new Direct3DX11EffectSamplerVariable( getVariableByName(name) -> AsSampler() );    
              hashTable -> add(name, variable);
            }
          
        }
      }
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  ~Direct3DX11EffectVariablesTable()
  {
    delete hashTable;
  }
  
  Direct3DX11EffectTechnique* getTechnique(const char* name)
  {
    return (Direct3DX11EffectTechnique*) hashTable ->lookup(name);
  }

  Direct3DX11EffectMatrixVariable*  getMatrix(const char* name)
  {
    return (Direct3DX11EffectMatrixVariable*) hashTable->lookup(name);
  }

  Direct3DX11EffectVectorVariable* getVector(const char* name)
  {
    return (Direct3DX11EffectVectorVariable*) hashTable ->lookup(name);
  }
  Direct3DX11EffectScalarVariable* getScalar(const char* name)
  {
    return (Direct3DX11EffectScalarVariable*) hashTable -> lookup(name);  
  }
    
  Direct3DX11EffectShaderResourceVariable* getShaderResource(const char* name)
  {
    return (Direct3DX11EffectShaderResourceVariable*) hashTable ->lookup(name);
  }
  
  Direct3DX11EffectStringVariable* getString(const char name)
  {
    return (Direct3DX11EffectStringVariable*) hashTable -> lookup(name);
  }

  Direct3DX11EffectRenderTargetViewVariable* getRenderTargetView(const char* name)
  {
    return (Direct3DX11EffectRenderTargetViewVariable*) hashTable -> lookup(name);
  }

  Direct3DX11EffectDepthStencilViewVariable* getepthStencilView(const char* name)
  {
    return (Direct3DX11EffectDepthStencilViewVariable*) hashTable -> lookup(name);
  }
  
  Direct3DX11EffectConstantBuffer* getConstantBuffer(const char* name)
  {
    return  (Direct3DX11EffectConstantBuffer*) hashTable -> lookup(name);
  }
  
  Direct3DX11EffectShaderVariable*  getShader(const char* name)
  {
    return (Direct3DX11EffectShaderVariable*) hashTable -> lookup(name);
  }
    
  Direct3DX11EffectBlendVariable* getBlend(const char* name)
  {
    return (Direct3DX11EffectBlendVariable*) hashTable -> lookup(name);
  }
  
  Direct3DX11EffectDepthStencilVariable* getDepthStencil(const char* name)
  {
    return (Direct3DX11EffectDepthStencilVariable*) hashTable -> lookup(name);
  }
  

  Direct3DX11EffectRasterizerVariable* getRasterizer(const char* name)
  {
    return (Direct3DX11EffectRasterizerVariable*) hashTable -> lookup(name);
  }
  
  Direct3DX11EffectSamplerVariable* getSampler(const char* name)
  {
    return (Direct3DX11EffectSamplerVariable*) hashTable -> lookup(name);
  }
  
};

}

