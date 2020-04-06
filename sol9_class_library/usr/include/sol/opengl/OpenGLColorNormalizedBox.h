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
 *  OpenGLColoredBox.h 
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLIndexedVertices.h>
#include <sol/opengl/Color3.h>


namespace SOL {
    
class OpenGLColoredBox : public OpenGLIndexedVertices {
private:
  GLfloat* vertices;
  int      verticesDataSize;
  int      numberOfVertices;
  
  GLuint* indices;
  int     indicesDataSize;
  int     numberOfIndices;

  static const int STRIDE   = 6;
  static const int FACES    = 6;
  static const int VERTICES = 24;
  static const int VERTICES_PER_FACE = 24;
public:
  OpenGLColoredBox(Color3<GLfloat>* colors=NULL, int numColors=0, GLfloat x=1.0f, GLfloat y=1.0f, GLfloat z=1.0f)
  :OpenGLIndexedVertices(),
  vertices(NULL),
  verticesDataSize(0),
  indices(NULL),
  indicesDataSize(0)
  {    
    GLfloat box[] = {
    // R,   G,    B,      X,  Y,  Z
      // face 1: 
      1.0f, 0.0f, 0.0f,   x,  y,  z,
      1.0f, 0.0f, 0.0f,  -x,  y,  z,
      1.0f, 0.0f, 0.0f,   x, -y,  z,
      1.0f, 0.0f, 0.0f,  -x, -y,  z,

      // face 2: 
      0.0f, 1.0f, 0.0f,   x,  y,  z,
      0.0f, 1.0f, 0.0f,   x, -y,  z,
      0.0f, 1.0f, 0.0f,   x,  y, -z,
      0.0f, 1.0f, 0.0f,   x, -y, -z,
   
      // face 3: 
      0.0f, 0.0f, 1.0f,   x,  y,   z,
      0.0f, 0.0f, 1.0f,   x,  y,  -z,
      0.0f, 0.0f, 1.0f,  -x,  y,   z,
      0.0f, 0.0f, 1.0f,  -x,  y,  -z,
        
      // face 4: 
      1.0f, 1.0f, 0.0f,   x,  y,  -z,
      1.0f, 1.0f, 0.0f,   x, -y,  -z,
      1.0f, 1.0f, 0.0f,  -x,  y,  -z,
      1.0f, 1.0f, 0.0f,  -x, -y,  -z,
   
      // face 5: 
      0.0f, 1.0f, 1.0f,  -x,  y,  z,
      0.0f, 1.0f, 1.0f,  -x,  y, -z,
      0.0f, 1.0f, 1.0f,  -x, -y,  z,
      0.0f, 1.0f, 1.0f,  -x, -y, -z,
   
      // face 6: 
      1.0f, 0.0f, 1.0f,   x, -y,  z,
      1.0f, 0.0f, 1.0f,  -x, -y,  z,
      1.0f, 0.0f, 1.0f,   x, -y, -z,
      1.0f, 0.0f, 1.0f,  -x, -y, -z,
    };
 
    verticesDataSize = sizeof(box);
    vertices = new GLfloat[CountOf(box)];
    memcpy(vertices, box, verticesDataSize);
    numberOfVertices = CountOf(box);

    if (colors && numColors == FACES) {
      setFaceColors(colors, numColors);
    }
    if (colors && numColors == VERTICES) {
      setVerticesColors(colors, numColors);
    }
    
    GLuint indexData[] = { 
      // face 1: 
       0, 1, 2,  2, 1, 3,  
      // face 2: 
       4, 5, 6,  6, 5, 7, 
      // face 3: 
       8, 9,10, 10,9,11, 
      // face 4: 
      12,13,14, 14,13,15,
      // face 5: 
      16,17,18, 18,17,19,  
      // face 6: 
      20,21,22, 22,21,23,  
    }; 
    indicesDataSize = sizeof(indexData);
    
    indices = new GLuint[CountOf(indexData)];
    memcpy(indices, indexData, indicesDataSize);
    numberOfIndices = CountOf(indexData);
  }
  
  ~OpenGLColoredBox()
  {
    delete [] vertices;
    delete [] indices;
    vertices  = NULL;
    indices = NULL;
  }
  
  void setFaceColors(Color3<GLfloat>* colors, int numColors)
  {
   
    if (colors && numColors == FACES) {
      for (int i = 0; i<numColors; i++) {
       for (int j = 0; j<4; j++) {
        vertices[i * VERTICES_PER_FACE + j* STRIDE + 0] = colors[i].r;
        vertices[i * VERTICES_PER_FACE + j* STRIDE + 1] = colors[i].g;
        vertices[i * VERTICES_PER_FACE + j* STRIDE + 2] = colors[i].b;
       }
      }  
    }
  }
  
  void setVerticesColors(Color3<GLfloat>* colors, int numColors)
  {
    if (colors && numColors == VERTICES) {
      for (int i = 0; i<numColors; i++) {
        vertices[i * STRIDE + 0] = colors[i].r;
        vertices[i * STRIDE + 1] = colors[i].g;
        vertices[i * STRIDE + 2] = colors[i].b;
      }  
    }
  }
    
  GLenum getInterleavedArraysFormat()
  {
    return GL_C3F_V3F;
  }
  
  GLenum getPrimitiveType()
  {
    return GL_TRIANGLES;
  }
  
  GLfloat* getVertices()
  {
    return vertices;
  }
  int getVerticesDataSize()
  {
    return verticesDataSize;
  }

  int getNumberOfVertices()
  {
    return numberOfVertices;
  }

  GLuint* getIndices()
  {
    return indices;
  }

  int getIndicesDataSize()
  {
    return indicesDataSize;
  }
  
  int getNumberOfIndices()
  {
    return numberOfIndices;
  }
  
  void draw(OpenGLGC* gc)
  {
    gc -> interleavedArrays(getInterleavedArraysFormat(), 0, NULL);
    gc -> drawElements(getPrimitiveType(), getNumberOfIndices(), GL_UNSIGNED_INT, NULL);
  }
};
  
}
  