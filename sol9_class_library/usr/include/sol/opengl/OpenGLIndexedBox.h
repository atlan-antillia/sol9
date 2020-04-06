/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenGLIndexedBox.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Vertex.h>
#include <sol/opengl/Normal3.h>

#include <sol/opengl/FaceIndices.h>

#include <sol/opengl/OpenGLIndexedVertices.h>
#include <sol/opengl/OpenGLQuadSurfaces.h>

namespace SOL {

class OpenGLIndexedBox :public OpenGLIndexedVertices {
private:
  static const int VERTEX_COUNT = 8;
  static const int FACE_COUNT   = 6;
  Vertex<3>                    vertices[VERTEX_COUNT];
  FaceIndices<4>               indices[FACE_COUNT];
  
  SmartPtr<OpenGLQuadSurfaces> surfaces;
  Normal3*                     normals;  //2017/2/27 shallow copy
  size_t                       numNormals;
  
public:
  OpenGLIndexedBox(GLfloat w=1.0f, GLfloat h=1.0f, GLfloat d=1.0f, GLfloat x=0.0f, GLfloat y=0.0f, GLfloat z=0.0f)
  {
    int i = 0;
    vertices[i++] =  {float(0.0*w + x), float(0.0*h + y), float(0.0*d + z)}; 
    vertices[i++] =  {float(1.0*w + x), float(0.0*h + y), float(0.0*d + z)};
    vertices[i++] =  {float(1.0*w + x), float(1.0*h + y), float(0.0*d + z)};
    vertices[i++] =  {float(0.0*w + x), float(1.0*h + y), float(0.0*d + z)}; 
    vertices[i++] =  {float(0.0*w + x), float(0.0*h + y), float(-1.0*d + z)}; 
    vertices[i++] =  {float(1.0*w + x), float(0.0*h + y), float(-1.0*d + z)};
    vertices[i++] =  {float(1.0*w + x), float(1.0*h + y), float(-1.0*d + z)};
    vertices[i  ] =  {float(0.0*w + x), float(1.0*h + y), float(-1.0*d + z)};
    
              
    i = 0;
    indices[i++] = {0, 1, 2, 3};
    indices[i++] = {1, 5, 6, 2};
    indices[i++] = {5, 4, 7, 6};
    indices[i++] = {4, 0, 3, 7};
    indices[i++] = {4, 5, 1, 0};
    indices[i++] = {3, 2, 6, 7};
       
    surfaces = new OpenGLQuadSurfaces(vertices, CountOf(vertices), indices, CountOf(indices));
    normals = surfaces->calculateSurfaceNormals(numNormals);
    //  surfaces->displayNormals();
   }
   

  virtual GLenum getInterleavedArraysFormat()
  {
    return (GLenum)0; //unused
  }
  
  virtual GLenum getPrimitiveType()
  {
    return GL_QUADS;
  }
  
  virtual GLfloat* getVertices()
  {
    return NULL; // unused
  }
  
  virtual int getVerticesDataSize()
  {
    return sizeof(vertices);
  }

  virtual int getNumberOfVertices()
  {
    return CountOf(vertices);
  }
  
  virtual GLuint* getIndices()
  {
    return NULL; //unused
  }
  
  virtual int getIndicesDataSize()
  {
    return sizeof(indices);
  }
  
  virtual int getNumberOfIndices()
  {
    return CountOf(indices);
  }
  
  virtual void draw(OpenGLGC* gc)
  {  
    gc->frontFace(GL_CCW);

    gc->enable(GL_CULL_FACE);
    gc->cullFace(GL_BACK);
    glEnable(GL_NORMALIZE);
        
    for (int i = 0; i< CountOf(indices); i++) {
      gc->begin(GL_QUADS);
      FaceIndices<4> quad = indices[i];
      
      gc->draw( normals[i], 
                    vertices[ quad.index[0] ], 
                    vertices[ quad.index[1] ], 
                    vertices[ quad.index[2] ],
                    vertices[ quad.index[3] ]
      );
      //gc->flush();
      gc ->end();
    }
  }
       
};

}
 
    