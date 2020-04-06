#pragma once

#include <sol/ArrayT.h>
#include <sol/opengl/Color4.h>
#include <sol/opengl/Normal3.h>
#include <sol/opengl/Vertex3.h>
#include <sol/opengl/TriangleIndices.h>

namespace SOL {
/*
typedef ArrayT<Color4>  Colors;
typedef ArrayT<Normal3> Normals;
typedef ArrayT<Vertex3> Vertices;
*/

class OpenGLColorsNormalsVertices {
private:
  ArrayT<Color4>*   colors;

  ArrayT<Normal3>*  normals;

  ArrayT<Vertex3>* vertices;
  
public;
  OpenGLColorsNormalsVertices(Vertex3* array=NULL, size_t number=0)
  :colors(NULL),
  normals(NULL),
  vertices(NULL)
  {
    if (array && number > 0) {
      vertices = new ArrayT<Vertex3>(array, numVert);
    }
  }

  ~OpenGLColorsNormalsVertices()
  {
    delete  colors;
    colors  = NULL;

    delete  normals;
    normals = NULL;

    delete  vertices;
    vertices = NULL;
  }

  void clearNormals()
  {
    delete  normals;
    normals = NULL;
    normals = new ArrayT<Normal3>();
  }
  
  void setColors(const Color4* array, size_t number)
  {
    if (array && number > 0) {
      delete colors;
      colors = new ArrayT<Color4>(array, number;
    } else {
      throw IException("Invalid parameter.");
    }
  }

  void setNormals(const Normal3* array, size_t number)
  {
    if (array && number > 0) {
      delete normals;
      normals = new ArrayT<Normal3>(array, number);
    } else {
      throw IException("Invalid parameter.");
    }
  }
  void setVertices(const Vertex3* array, size_t number)
  {
    if (array && number > 0) {
      delete vertices;
      vertices = new ArrayT<Vertex3>(array, number);
    } else {
      throw IException("Invalid parameter.");
    }
  }

  void calculateFaceNormals(ArrayT<TriangleIndices>* triangles) //Easy going way.
  {
    if (verices && triangles) {
      clearNormals();
      
      size_t number = triangles->getSize();
      for (int i = 0; i<number; i++) {
        Triangle* tri = triangles[i];
        Vector3f v1 = vertices[tri->n1];
        Vector3f v2 = vertices[tri->n2];
        Vector3f v3 = vertices[tri->n3];
        Vector3f normal = Vector3f::crossProduct(v1 - v0, v2 - v0);
        normal.normalize();
        normals[i] = new Normal3(normal[0], normal[1], normal[2]);
      }
      //vertices
    }
    
  }
    
};

}


