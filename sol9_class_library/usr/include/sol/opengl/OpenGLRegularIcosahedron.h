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
 *  OpenGLRegularIcosahedron.h 
 *
 *****************************************************************************/

// 2016/08/10 Icosahedron's vertices data used here is based on the following webstie 
//
// https://en.wikipedia.org/wiki/Platonic_solid

#pragma once

#include <sol/opengl/OpenGLIndexedVertices.h>
#include <sol/opengl/Color3.h>
#include <math.h>

namespace SOL {
    
class OpenGLRegularIcosahedron : public OpenGLIndexedVertices {
private:
  SmartPtrs<GLfloat> vertices;
  int      verticesDataSize;
  int      numberOfVertices;
  
  SmartPtrs<GLuint> indices;
  int     indicesDataSize;
  int     numberOfIndices;

  static const int STRIDE   = 6;
  static const int FACES    = 20;
  static const int VERTICES = 12;
public:
  OpenGLRegularIcosahedron()
  :OpenGLIndexedVertices(),
  vertices(NULL),
  verticesDataSize(0),
  indices(NULL),
  indicesDataSize(0)
  {    
    GLfloat g = (1.0f + sqrt(5.0f))/2.0f; //golden ratio

    GLfloat hedron[] = {
      // X,      Y,  Z
      // 12 vertices
      0.0f, -1.0f,  -g   ,
      0.0f, +1.0f,  -g   , 
      0.0f, -1.0f,  +g   , 
      0.0f, +1.0f,  +g   ,
      
      -g,     0.0f, -1.0f, 
      -g,     0.0f, +1.0f, 
      +g,     0.0f, -1.0f, 
      +g,     0.0f, +1.0f,
      
      -1.0f, -g,     0.0f, 
      +1.0f, -g,     0.0f, 
      -1.0f, +g,     0.0f, 
      +1.0f, +g,     0.0f,
    };
    
    verticesDataSize = sizeof(hedron);
    vertices = new GLfloat[CountOf(hedron)];
    memcpy(vertices, hedron, verticesDataSize);
    numberOfVertices = CountOf(hedron);

       
    GLuint indexData[] = {    
    //20 faces
     0,  1,  6,
     1,  0,  4,
     2,  3,  5,
     3,  2,  7,
     4,  5, 10,
     5,  4,  8,
     6,  7,  9,
     7,  6, 11,
     8,  9,  2,
     9,  8,  0, 
    10, 11,  1,
    11, 10,  3,
      
     0,  6,  9,
     0,  8,  4, 
     1,  4, 10,
     1, 11,  6,
     2,  5,  8,
     2,  9,  7, 
     3,  7, 11,
     3, 10,  5
    };
    
    indicesDataSize = sizeof(indexData);
    
    indices = new GLuint[CountOf(indexData)];
    memcpy(indices, indexData, indicesDataSize);
    numberOfIndices = CountOf(indexData);
  }
  
  ~OpenGLRegularIcosahedron()
  {
/*    delete [] vertices;
    delete [] indices;
    vertices  = NULL;
    indices = NULL; */
  }
    
    
  GLenum getInterleavedArraysFormat()
  {
    return GL_V3F;
  }
  
  GLenum getPrimitiveType()
  {
    return GL_POLYGON;
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
  