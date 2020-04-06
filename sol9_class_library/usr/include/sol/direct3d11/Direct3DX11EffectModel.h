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
 *  Direct3DX11EffectModel.h
 *
 *****************************************************************************/
 
// 2015/11/20 This is a very simple effect color and light model class based on Direct3DX11Effect.
// 2015/11/24 Updated to be able XmNrenderTechnique and XmNrenderLightTechnique.

#pragma once

#include <sol/direct3d11/Direct3DX11Effect.h>

#include <sol/direct3d11/Direct3DX11EffectTechnique.h>
#include <sol/direct3d11/Direct3DX11EffectMatrixVariable.h>

#include <sol/direct3d11/Direct3DX11EffectVectorVariable.h>
#include <sol/direct3d11/Direct3DX11EffectShaderResourceVariable.h>
#include <sol/direct3d11/Direct3DX11EffectScalarVariable.h>

namespace SOL {

class Direct3DX11EffectModel : public Direct3DX11Effect {

private:
  Direct3DX11EffectTechnique*       effectTechnique;       // This may be used to refer  technique10 Render { }

  Direct3DX11EffectTechnique*       renderTechnique;       // To refer technique10 Render { }

  Direct3DX11EffectTechnique*       renderLightTechnique;  // To refer technique10 RenderLight { }
  
  Direct3DX11EffectMatrixVariable*  viewMatrix;  
  Direct3DX11EffectMatrixVariable*  worldMatrix;
  Direct3DX11EffectMatrixVariable*  projectionMatrix;
    
  Direct3DX11EffectShaderResourceVariable* shaderTexture;
  Direct3DX11EffectVectorVariable*   lightDirection;
  Direct3DX11EffectVectorVariable*   lightColor;
  Direct3DX11EffectVectorVariable*   outputColor;
  
  Direct3DX11EffectVectorVariable*   ambientColor;
  Direct3DX11EffectVectorVariable*   diffuseColor;


  Direct3DX11EffectVectorVariable*   cameraPosition;
  Direct3DX11EffectVectorVariable*   specularColor;
  Direct3DX11EffectScalarVariable*   specularPower;

  
public:
  //Constructor 
  
  Direct3DX11EffectModel(ID3D11Device* device, 
      const TCHAR* filename,
      Args& args)
  :Direct3DX11Effect( device, filename),
  effectTechnique(NULL),
  viewMatrix(NULL),  
  worldMatrix(NULL),
  projectionMatrix(NULL),
  
  shaderTexture(NULL),
  lightDirection(NULL),
  lightColor(NULL),
  outputColor(NULL),
  ambientColor(NULL),
  diffuseColor(NULL),
  cameraPosition(NULL),
  specularColor(NULL),
  specularPower(NULL)
  {
    try {
      {     
        const char* name = (const char*)args.get(XmNtechnique);
        if (name && strlen(name) ) {
          effectTechnique = new Direct3DX11EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }
      {     
        //2015/11/24
        const char* name = (const char*)args.get(XmNrenderTechnique);
        if (name && strlen(name) ) {
          renderTechnique = new Direct3DX11EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }
      { 
        //2015/11/24
        const char* name = (const char*)args.get(XmNrenderLightTechnique);
        if (name && strlen(name) ) {
          renderLightTechnique = new Direct3DX11EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }

      {
        const char* name      = (const char*)args.get(XmNview);
        if (name && strlen(name) ) {
          viewMatrix       = new Direct3DX11EffectMatrixVariable(this->getVariableByName( name )->AsMatrix() );
        }
      }
      {
        const char* name = (const char*)args.get(XmNprojection);
        if (name && strlen(name)) {
          projectionMatrix = new Direct3DX11EffectMatrixVariable(this->getVariableByName(name)->AsMatrix());
        }
      }
      {
        const char* name  = (const char*)args.get(XmNworld);    
        if (name && strlen(name)) {
          worldMatrix      = new Direct3DX11EffectMatrixVariable(this->getVariableByName(name)->AsMatrix());  
        }
      }

      
      {
        const char* name = (const char*)args.get(XmNshaderTexture);
        if (name && strlen(name) ) {
          shaderTexture = new Direct3DX11EffectShaderResourceVariable( this -> getVariableByName(name) -> AsShaderResource() );    
        }
      }
      
      {
        const char* name = (const char*)args.get(XmNlightDirection);
        if (name && strlen(name) ) {
          lightDirection       = new Direct3DX11EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }

      {
        const char* name = (const char*)args.get(XmNlightColor);
        if (name && strlen(name) ) {
          lightColor       = new Direct3DX11EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }

      {
        const char* name = (const char*)args.get(XmNoutputColor);
        if (name && strlen(name) ) {
          outputColor       = new Direct3DX11EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }
      {
        const char* name = (const char*)args.get(XmNambientColor);
        if (name && strlen(name)) {
          ambientColor = new Direct3DX11EffectVectorVariable(this->getVariableByName(name)->AsVector());
        }
      }
      {
        const char* name  = (const char*)args.get(XmNdiffuseColor);    
        if (name && strlen(name)) {
          diffuseColor      = new Direct3DX11EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      {
        const char* name  = (const char*)args.get(XmNcameraPosition);    
        if (name && strlen(name)) {
          cameraPosition      = new Direct3DX11EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      
      {
        const char* name  = (const char*)args.get(XmNspecularColor);    
        if (name && strlen(name)) {
          specularColor      = new Direct3DX11EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      {
        const char* name  = (const char*)args.get(XmNspecularPower);    
        if (name && strlen(name)) {
          specularPower      = new Direct3DX11EffectScalarVariable(this->getVariableByName(name)->AsScalar());  
        }
      }
           
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  
  
  ~Direct3DX11EffectModel()
  {
    delete effectTechnique;
    delete renderTechnique;
    delete renderLightTechnique;
    
    delete viewMatrix;  
    delete worldMatrix;
    delete projectionMatrix;

    delete shaderTexture;
    delete lightDirection;
    delete lightColor;
    delete outputColor;

    delete ambientColor;
    delete diffuseColor;


    delete cameraPosition;
    delete specularColor;
    delete specularPower;

  }

  Direct3DX11EffectTechnique* getTechnique()
  {
    return effectTechnique;
  }

  //2015/11/24
  Direct3DX11EffectTechnique* getRenderTechnique()
  {
    return renderTechnique;
  }
  
  //2015/11/24
  Direct3DX11EffectTechnique* getRenderLightTechnique()
  {
    return renderLightTechnique;
  }

  Direct3DX11EffectMatrixVariable*  getView()
  {
    return viewMatrix;
  }
  
  Direct3DX11EffectMatrixVariable*  getWorld()
  {
    return worldMatrix;
  }
  
  Direct3DX11EffectMatrixVariable*  getProjection()
  {
    return projectionMatrix;
  }
  
  void setWorld(XMFLOAT4X4* world) //XMMATRIX* world)
  {
    if (worldMatrix) {
      worldMatrix -> setMatrix((float*)world); 
    }
  }
  
  void setView(XMFLOAT4X4* view) //XMMATRIX* view)
  {
    if (viewMatrix) {
      viewMatrix -> setMatrix((float*)view);
    }
  }
  
  void setProjection(XMFLOAT4X4* projection) //XMMATRIX* projection)
  {
    if (projectionMatrix) {
      projectionMatrix -> setMatrix((float*)projection);
    }
  }
  
 void setWorld(XMMATRIX* world)
  {
    if (worldMatrix) {
      worldMatrix -> setMatrix((float*)world); 
    }
  }
  
  void setView(XMMATRIX* view)
  {
    if (viewMatrix) {
      viewMatrix -> setMatrix((float*)view);
    }
  }
  
  void setProjection(XMMATRIX* projection)
  {
    if (projectionMatrix) {
      projectionMatrix -> setMatrix((float*)projection);
    }
  }
  
   
  
  Direct3DX11EffectShaderResourceVariable* getShaderTexture()
  {
    return shaderTexture;
  }
  
  Direct3DX11EffectVectorVariable*   getLightDirection()
  {
    return lightDirection;
  }
  Direct3DX11EffectVectorVariable*   getLightColor()
  {
    return lightColor;
  }
  //2015/11/25
  Direct3DX11EffectVectorVariable*   getOutputColor()
  {
    return outputColor;
  }
  
  Direct3DX11EffectVectorVariable*   getAmbientColor()
  {
    return ambientColor;
  }
  
  Direct3DX11EffectVectorVariable*   getDiffuseColor()
  {
    return diffuseColor;
  }

  Direct3DX11EffectVectorVariable*   getCameraPosition()
  {
    return cameraPosition;
  }
  
  Direct3DX11EffectVectorVariable*   getSpecularColor()
  {
    return specularColor;
  }
  
  Direct3DX11EffectScalarVariable*   getSpecularPower()
  {
    return specularPower;
  }
};

}

