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
 *  OpenGLQuadSurfaces.h
 *
 *****************************************************************************/

//2016/09/10 On calculateSurfaceNormals method, see: https://www.opengl.org/wiki/Calculating_a_Surface_Normal

#pragma once

#include <sol/Stdio.h>
#include <sol/opengl/Normal3.h>
#include <sol/Vertex.h>
#include <sol/opengl/QuadIndices.h>
#include <sol/Vector3f.h>
#include <sol/opengl/FaceIndices.h>

namespace SOL {
  
class OpenGLQuadSurfaces {
private:
  const Vertex<3>* vertexArray;
  size_t         numberOfVertices;
  const FaceIndices<4>* faceArray;
  size_t         numberOfFaces;
  
  Normal3*       normals;
  size_t         numberOfNormals;
  
public:
  OpenGLQuadSurfaces(__in const Vertex<3>* vertices, __in size_t numVertices, 
              __in const FaceIndices<4>* faces, __in size_t numFaces)
  :vertexArray(NULL),
  numberOfVertices(numVertices),
  faceArray(NULL),
  numberOfFaces(numFaces),
  normals(NULL),
  numberOfNormals(0)
  {
    //Deep copy
    if (vertices && numVertices >0) {
      vertexArray = new Vertex<3>[numVertices];
      memcpy((void*)vertexArray, (const void*)vertices, sizeof(Vertex3)* numVertices);
    } else {
      throw IException("Invalid vertices parameters.");
    }
    if (faces && numFaces >0) {
      faceArray = new FaceIndices<4>[numFaces];
      memcpy((void*)faceArray, (const void*)faces, sizeof(FaceIndices<4>)* numFaces);
    } else {
      throw IException("Invalid faces parameters.");
    }
  }
  
  
  ~OpenGLQuadSurfaces()
  {
    delete [] vertexArray;
    vertexArray = NULL;
    delete [] faceArray;
    faceArray   = NULL;
    delete [] normals;
    normals = NULL;
  }
  

  Normal3* calculateSurfaceNormals(__out size_t& numNormals) //,
  {
    numberOfNormals = numberOfFaces;
    if (normals == NULL) {
      normals = new Normal3[numberOfFaces];
    }
      
    for (int s = 0; s<numberOfFaces; s++) {
      FaceIndices<4> quad = faceArray[s];
      Vector3f v[4] = {
        Vector3f(vertexArray[ quad.index[0]]),
        Vector3f(vertexArray[ quad.index[1]]),
        Vector3f(vertexArray[ quad.index[2]]),
        Vector3f(vertexArray[ quad.index[3]]),
      };
      
      Vector3f normal;
      
      for (int i=0; i<4; i++) {
        int j = (i+1) % 4;
        normal[0] += (v[i][1] - v[j][1]) * (v[i][2] + v[j][2]);
        normal[1] += (v[i][2] - v[j][2]) * (v[i][0] + v[j][0]);
        normal[2] += (v[i][0] - v[j][0]) * (v[i][1] + v[j][1]);
      }
      normal.normalize();
        
      normals[s].x = normal[0];
      normals[s].y = normal[1];
      normals[s].z = normal[2];
    } 
    numNormals = numberOfNormals;
    return normals;    
  }
  
  void displayNormals()
  {
    for (int i =0; i<numberOfFaces; i++) {
      Printf("%d x=%f, y=%f, z=%f\n", i, 
         normals[i].x, normals[i].y, normals[i].z);      
    }
  }
  
};

}

    