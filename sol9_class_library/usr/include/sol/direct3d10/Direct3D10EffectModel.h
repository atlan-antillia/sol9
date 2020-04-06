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
 *  Direct3D10EffectModel.h
 *
 *****************************************************************************/
 
// 2015/11/20 This is a very simple effect color and light model class based on Direct3D10Effect.
// 2015/11/24 Updated to be able XmNrenderTechnique and XmNrenderLightTechnique.

#pragma once

#include <sol/direct3d10/Direct3D10Effect.h>

#include <sol/direct3d10/Direct3D10EffectTechnique.h>
#include <sol/direct3d10/Direct3D10EffectMatrixVariable.h>

#include <sol/direct3d10/Direct3D10EffectVectorVariable.h>
#include <sol/direct3d10/Direct3D10EffectShaderResourceVariable.h>
#include <sol/direct3d10/Direct3D10EffectScalarVariable.h>

namespace SOL {

class Direct3D10EffectModel : public Direct3D10Effect {

private:
  Direct3D10EffectTechnique*       effectTechnique;       // This may be used to refer  technique10 Render { }

  Direct3D10EffectTechnique*       renderTechnique;       // To refer technique10 Render { }

  Direct3D10EffectTechnique*       renderLightTechnique;  // To refer technique10 RenderLight { }
  
  Direct3D10EffectMatrixVariable*  viewMatrix;  
  Direct3D10EffectMatrixVariable*  worldMatrix;
  Direct3D10EffectMatrixVariable*  projectionMatrix;
    
  Direct3D10EffectShaderResourceVariable* shaderTexture;
  Direct3D10EffectVectorVariable*   lightDirection;
  Direct3D10EffectVectorVariable*   lightColor;
  Direct3D10EffectVectorVariable*   outputColor;
  
  Direct3D10EffectVectorVariable*   ambientColor;
  Direct3D10EffectVectorVariable*   diffuseColor;


  Direct3D10EffectVectorVariable*   cameraPosition;
  Direct3D10EffectVectorVariable*   specularColor;
  Direct3D10EffectScalarVariable*   specularPower;

  
public:
  //Constructor 
  
  Direct3D10EffectModel(ID3D10Device* device, 
      const TCHAR* filename,
      Args& args)
  :Direct3D10Effect( device, filename),
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
          effectTechnique = new Direct3D10EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }
      {     
        //2015/11/24
        const char* name = (const char*)args.get(XmNrenderTechnique);
        if (name && strlen(name) ) {
          renderTechnique = new Direct3D10EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }
      { 
        //2015/11/24
        const char* name = (const char*)args.get(XmNrenderLightTechnique);
        if (name && strlen(name) ) {
          renderLightTechnique = new Direct3D10EffectTechnique( this -> getTechniqueByName(name) );    
        }
      }

      {
        const char* name      = (const char*)args.get(XmNview);
        if (name && strlen(name) ) {
          viewMatrix       = new Direct3D10EffectMatrixVariable(this->getVariableByName( name )->AsMatrix() );
        }
      }
      {
        const char* name = (const char*)args.get(XmNprojection);
        if (name && strlen(name)) {
          projectionMatrix = new Direct3D10EffectMatrixVariable(this->getVariableByName(name)->AsMatrix());
        }
      }
      {
        const char* name  = (const char*)args.get(XmNworld);    
        if (name && strlen(name)) {
          worldMatrix      = new Direct3D10EffectMatrixVariable(this->getVariableByName(name)->AsMatrix());  
        }
      }

      
      {
        const char* name = (const char*)args.get(XmNshaderTexture);
        if (name && strlen(name) ) {
          shaderTexture = new Direct3D10EffectShaderResourceVariable( this -> getVariableByName(name) -> AsShaderResource() );    
        }
      }
      
      {
        const char* name = (const char*)args.get(XmNlightDirection);
        if (name && strlen(name) ) {
          lightDirection       = new Direct3D10EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }

      {
        const char* name = (const char*)args.get(XmNlightColor);
        if (name && strlen(name) ) {
          lightColor       = new Direct3D10EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }

      {
        const char* name = (const char*)args.get(XmNoutputColor);
        if (name && strlen(name) ) {
          outputColor       = new Direct3D10EffectVectorVariable(this->getVariableByName( name )->AsVector() );
        }
      }
      {
        const char* name = (const char*)args.get(XmNambientColor);
        if (name && strlen(name)) {
          ambientColor = new Direct3D10EffectVectorVariable(this->getVariableByName(name)->AsVector());
        }
      }
      {
        const char* name  = (const char*)args.get(XmNdiffuseColor);    
        if (name && strlen(name)) {
          diffuseColor      = new Direct3D10EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      {
        const char* name  = (const char*)args.get(XmNcameraPosition);    
        if (name && strlen(name)) {
          cameraPosition      = new Direct3D10EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      
      {
        const char* name  = (const char*)args.get(XmNspecularColor);    
        if (name && strlen(name)) {
          specularColor      = new Direct3D10EffectVectorVariable(this->getVariableByName(name)->AsVector());  
        }
      }
      {
        const char* name  = (const char*)args.get(XmNspecularPower);    
        if (name && strlen(name)) {
          specularPower      = new Direct3D10EffectScalarVariable(this->getVariableByName(name)->AsScalar());  
        }
      }
           
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  
  
  ~Direct3D10EffectModel()
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

  Direct3D10EffectTechnique* getTechnique()
  {
    return effectTechnique;
  }

  //2015/11/24
  Direct3D10EffectTechnique* getRenderTechnique()
  {
    return renderTechnique;
  }
  
  //2015/11/24
  Direct3D10EffectTechnique* getRenderLightTechnique()
  {
    return renderLightTechnique;
  }

  Direct3D10EffectMatrixVariable*  getView()
  {
    return viewMatrix;
  }
  
  Direct3D10EffectMatrixVariable*  getWorld()
  {
    return worldMatrix;
  }
  
  Direct3D10EffectMatrixVariable*  getProjection()
  {
    return projectionMatrix;
  }
  
  void setWorld(D3DXMATRIX world)
  {
    if (worldMatrix) {
      worldMatrix -> setMatrix(world); 
    }
  }
  
  void setView(D3DXMATRIX view)
  {
    if (viewMatrix) {
      viewMatrix -> setMatrix(view);
    }
  }
  
  void setProjection(D3DXMATRIX projection)
  {
    if (projectionMatrix) {
      projectionMatrix -> setMatrix(projection);
    }
  }
  
  
  
  Direct3D10EffectShaderResourceVariable* getShaderTexture()
  {
    return shaderTexture;
  }
  
  Direct3D10EffectVectorVariable*   getLightDirection()
  {
    return lightDirection;
  }
  Direct3D10EffectVectorVariable*   getLightColor()
  {
    return lightColor;
  }
  //2015/11/25
  Direct3D10EffectVectorVariable*   getOutputColor()
  {
    return outputColor;
  }
  
  Direct3D10EffectVectorVariable*   getAmbientColor()
  {
    return ambientColor;
  }
  
  Direct3D10EffectVectorVariable*   getDiffuseColor()
  {
    return diffuseColor;
  }

  Direct3D10EffectVectorVariable*   getCameraPosition()
  {
    return cameraPosition;
  }
  
  Direct3D10EffectVectorVariable*   getSpecularColor()
  {
    return specularColor;
  }
  
  Direct3D10EffectScalarVariable*   getSpecularPower()
  {
    return specularPower;
  }
};

}

