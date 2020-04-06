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
 *  Direct3D10EffectVariablesTable.h
 *
 *****************************************************************************/
 
//2015/12/01
// This is a simple HashTable based effect variables manager.

#pragma once

#include <sol/HashTable.h>
#include <sol/Pair.h>

#include <sol/direct3d10/Direct3D10Effect.h>

#include <sol/direct3d10/Direct3D10EffectTechnique.h>
#include <sol/direct3d10/Direct3D10EffectConstantBuffer.h>

#include <sol/direct3d10/Direct3D10EffectBlendVariable.h>
#include <sol/direct3d10/Direct3D10EffectDepthStencilVariable.h>
#include <sol/direct3d10/Direct3D10EffectDepthStencilViewVariable.h>
#include <sol/direct3d10/Direct3D10EffectMatrixVariable.h>
#include <sol/direct3d10/Direct3D10EffectRasterizerVariable.h>
#include <sol/direct3d10/Direct3D10EffectRenderTargetViewVariable.h>
#include <sol/direct3d10/Direct3D10EffectSamplerVariable.h>
#include <sol/direct3d10/Direct3D10EffectScalarVariable.h>
#include <sol/direct3d10/Direct3D10EffectShaderResourceVariable.h>
#include <sol/direct3d10/Direct3D10EffectShaderVariable.h>
#include <sol/direct3d10/Direct3D10EffectStringVariable.h>
#include <sol/direct3d10/Direct3D10EffectVariable.h>
#include <sol/direct3d10/Direct3D10EffectVectorVariable.h>

namespace SOL {

class Direct3D10EffectVariablesTable : public Direct3D10Effect {

private:
  HashTable* hashTable;

public:
  //Constructor 
  
  Direct3D10EffectVariablesTable(ID3D10Device* device, 
      const TCHAR* filename,
      Pair<const TCHAR*, const char*>* pairs, int count)
  
  :Direct3D10Effect( device, filename),
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
              Direct3D10EffectTechnique* technique = new Direct3D10EffectTechnique( getTechniqueByName(name) );
              hashTable -> add(name, technique);
            
            }
            else if (type == XmNasMatrix) {
              Direct3D10EffectMatrixVariable* variable = new Direct3D10EffectMatrixVariable( getVariableByName(name)->AsMatrix());  
              hashTable -> add(name, variable);
            }
           
            else if (type == XmNasVector) {
              Direct3D10EffectVectorVariable* variable = new Direct3D10EffectVectorVariable( getVariableByName(name)->AsVector());
              hashTable -> add(name, variable);
            }
            else if (type == XmNasScalar) {
              Direct3D10EffectScalarVariable* scalar = new Direct3D10EffectScalarVariable( getVariableByName(name)->AsScalar());  
              hashTable -> add(name, scalar);
            }
            else if (type == XmNasShaderResource) {
              Direct3D10EffectShaderResourceVariable* shaderResource = new Direct3D10EffectShaderResourceVariable( getVariableByName(name) -> AsShaderResource() );    
              hashTable -> add(name, shaderResource);
            }
            else if (type == XmNasString) {
              Direct3D10EffectStringVariable* variable = new Direct3D10EffectStringVariable( getVariableByName(name) -> AsString() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasRenderTargetView) {
              Direct3D10EffectRenderTargetViewVariable* variable = new Direct3D10EffectRenderTargetViewVariable( getVariableByName(name) -> AsRenderTargetView() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasDepthStencilView) {
              Direct3D10EffectDepthStencilViewVariable* variable = new Direct3D10EffectDepthStencilViewVariable( getVariableByName(name) -> AsDepthStencilView() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasConstantBuffer) {
              Direct3D10EffectConstantBuffer* variable = new Direct3D10EffectConstantBuffer( getVariableByName(name) -> AsConstantBuffer() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasShader) {
              Direct3D10EffectShaderVariable* variable = new Direct3D10EffectShaderVariable( getVariableByName(name) -> AsShader() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasBlend) {
              Direct3D10EffectBlendVariable* variable = new Direct3D10EffectBlendVariable( getVariableByName(name) -> AsBlend() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasDepthStencil) {
              Direct3D10EffectDepthStencilVariable* variable = new Direct3D10EffectDepthStencilVariable( getVariableByName(name) -> AsDepthStencil() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasRasterizer) {
              Direct3D10EffectRasterizerVariable* variable = new Direct3D10EffectRasterizerVariable( getVariableByName(name) -> AsRasterizer() );    
              hashTable -> add(name, variable);
            }
            else if (type == XmNasSampler) {
              Direct3D10EffectSamplerVariable* variable = new Direct3D10EffectSamplerVariable( getVariableByName(name) -> AsSampler() );    
              hashTable -> add(name, variable);
            }
          
        }
      }
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  ~Direct3D10EffectVariablesTable()
  {
    delete hashTable;
  }
  
  Direct3D10EffectTechnique* getTechnique(const char* name)
  {
    return (Direct3D10EffectTechnique*) hashTable ->lookup(name);
  }

  Direct3D10EffectMatrixVariable*  getMatrix(const char* name)
  {
    return (Direct3D10EffectMatrixVariable*) hashTable->lookup(name);
  }

  Direct3D10EffectVectorVariable* getVector(const char* name)
  {
    return (Direct3D10EffectVectorVariable*) hashTable ->lookup(name);
  }
  Direct3D10EffectScalarVariable* getScalar(const char* name)
  {
    return (Direct3D10EffectScalarVariable*) hashTable -> lookup(name);  
  }
    
  Direct3D10EffectShaderResourceVariable* getShaderResource(const char* name)
  {
    return (Direct3D10EffectShaderResourceVariable*) hashTable ->lookup(name);
  }
  
  Direct3D10EffectStringVariable* getString(const char name)
  {
    return (Direct3D10EffectStringVariable*) hashTable -> lookup(name);
  }

  Direct3D10EffectRenderTargetViewVariable* getRenderTargetView(const char* name)
  {
    return (Direct3D10EffectRenderTargetViewVariable*) hashTable -> lookup(name);
  }

  Direct3D10EffectDepthStencilViewVariable* getepthStencilView(const char* name)
  {
    return (Direct3D10EffectDepthStencilViewVariable*) hashTable -> lookup(name);
  }
  
  Direct3D10EffectConstantBuffer* getConstantBuffer(const char* name)
  {
    return  (Direct3D10EffectConstantBuffer*) hashTable -> lookup(name);
  }
  
  Direct3D10EffectShaderVariable*  getShader(const char* name)
  {
    return (Direct3D10EffectShaderVariable*) hashTable -> lookup(name);
  }
    
  Direct3D10EffectBlendVariable* getBlend(const char* name)
  {
    return (Direct3D10EffectBlendVariable*) hashTable -> lookup(name);
  }
  
  Direct3D10EffectDepthStencilVariable* getDepthStencil(const char* name)
  {
    return (Direct3D10EffectDepthStencilVariable*) hashTable -> lookup(name);
  }
  

  Direct3D10EffectRasterizerVariable* getRasterizer(const char* name)
  {
    return (Direct3D10EffectRasterizerVariable*) hashTable -> lookup(name);
  }
  
  Direct3D10EffectSamplerVariable* getSampler(const char* name)
  {
    return (Direct3D10EffectSamplerVariable*) hashTable -> lookup(name);
  }
  
};

}

