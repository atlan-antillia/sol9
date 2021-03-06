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
 *  OpenGLMultiTexturedCube.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/opengl/OpenGLImageInfo.h>
#include <sol/opengl/OpenGLTexture2D.h>
#include <sol/opengl/TextureCoord2Vertex3.h>
#include <sol/opengl/TextureCoordTriangularCube.h>

namespace SOL {

class OpenGLMultiTexturedCube : public OpenGLObject {
private:
  static const int FACES = 6;
  OpenGLTexture2D* textures[FACES];
  
protected:
  OpenGLMultiTexturedCube()
  :OpenGLObject()
  {    
    for (int i = 0; i<FACES; i++) {
      textures[i] = new OpenGLTexture2D();
    }
  }
  

public:
  OpenGLMultiTexturedCube(size_t size, const char* filenames[])
  :OpenGLObject()
  {
    if (size != FACES) {
      throw IException("Invalid size parameter: %d", size);
    }
    if (filenames == NULL) {
      throw IException("Invalid filenames parameter");
    }
    
    for (int i = 0; i<FACES; i++) {
      textures[i] = new OpenGLTexture2D();
    }
    load(size, filenames);
  }

public:
  OpenGLMultiTexturedCube(size_t size, OpenGLImageInfo imageInfos[])
  :OpenGLObject()
  {
    if (size != FACES) {
      throw IException("Invalid size parameter: %d", size);
    }
    if (imageInfos == NULL) {
      throw IException("Invalid imageInfo parameter");
    }
    
    for (int i = 0; i<FACES; i++) {
      textures[i] = new OpenGLTexture2D();
    }
    setImageInfo(size, imageInfos);
  }
  
  public:
  ~OpenGLMultiTexturedCube()
  {
    for (int i = 0; i<FACES; i++) {
      textures[i] -> unbind(); 
      delete textures[i];
      textures[i] = NULL;
    }
  }
  
  virtual void load(size_t size, const char* filenames[])
  {
    if (size != FACES) {
      throw IException("Invalid size parameter: %d", size);
    }
    if (filenames == NULL) {
      throw IException("Invalid filenames parameter");
    }

    for (int i = 0; i<FACES; i++) { 
      textures[i] -> bind();

      textures[i] -> pixelStore(GL_UNPACK_ALIGNMENT, 4);

      textures[i] -> parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      textures[i] -> parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      textures[i] -> env(GL_TEXTURE_ENV_MODE, GL_MODULATE);

      textures[i] -> generate(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
      textures[i] -> generate(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);

      textures[i] -> parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      textures[i] -> parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      try {
        textures[i] -> imageFromFile(filenames[i]);//, GL_TEXTURE_2D);
      } catch (Exception& ex) {
        ex.display();
      }
    
      textures[i] -> unbind();
    }
  }
  
  virtual void setImageInfo(size_t size, OpenGLImageInfo imageInfos[])
  {
    if (size != FACES) {
      throw IException("Invalid size parameter: %d", size);
    }
    if (imageInfos == NULL) {
      throw IException("Invalid imageInfos parameter");
    }

    for (int i = 0; i<FACES; i++) { 
      textures[i] -> bind();

      textures[i] -> pixelStore(GL_UNPACK_ALIGNMENT, 4);

      textures[i] -> parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      textures[i] -> parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      textures[i] -> env(GL_TEXTURE_ENV_MODE, GL_MODULATE);

      textures[i] -> generate(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
      textures[i] -> generate(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);

      textures[i] -> parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      textures[i] -> parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      try {
        textures[i] -> image(imageInfos[i]);//, GL_TEXTURE_2D);
      } catch (Exception& ex) {
        ex.display();
      }
    
      textures[i] -> unbind();
    }
  }
  
  public:
  virtual void draw(OpenGLGC* gc)
  {
      TextureCoordTriangularCube ttc;

      TextureCoord2Vertex3* cube = ttc.getData();;
      
      int numFaces = ttc.getNumberOfFaces();
      int numVerticesPerFace = ttc.getNumberOfVerticesPerFace();
      
      if (gc) { 
        gc -> enable(GL_NORMALIZE);
        //gc -> enable( GL_CULL_FACE );
        //gc -> cullFace ( GL_FRONT );
        gc -> enable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gc -> enable(GL_TEXTURE_2D);
        
        for (int i = 0; i<numFaces; i++) {
          
        
          textures[i] -> bind();
          gc -> begin(GL_TRIANGLES);

          for (int j = 0; j<numVerticesPerFace; j++) {
            textures[i] -> coordVertex(cube[i*numFaces + j]);
          }
       
          textures[i] -> unbind();
          gc ->flush();

          gc -> end();
        }
        gc ->disable(GL_TEXTURE_2D);
      }
   }
 
 };
}
 