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
 *  OpenGLHeightMap.h
 *
 *****************************************************************************/

//2017/02/15 

#pragma once
  
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/Vertex3.h>

namespace SOL {

template <typename int SIZE, typename size_t MAP_MESH_SIZE_X, typename size_t MAP_MESH_SIZE_Y> 
class OpenGLHeightMap {
private:
  float HEIGHT_MAX;
  float HEIGHT_MIN;
  
  //static const size_t MAP_DIMENSION  = 3;
  static const GLenum primitive = GL_TRIANGLE_STRIP;
  
  Vertex3 vertices[MAP_MESH_SIZE_X * MAP_MESH_SIZE_Y ];

  //RAND_MAX=32767
  float generateRandom( float rangeMin, float rangeMax)  
  {  
    float r = (float)rand() /(float) (RAND_MAX  + 1) * (rangeMax - rangeMin)  
            + rangeMin; 
    
    return r; 
  }
  
public:
  OpenGLHeightMap(float zmax, float zmin)
  {
    HEIGHT_MAX = zmax;
    HEIGHT_MIN = zmin;
    
    //Set a seed by using time.
    srand( (unsigned)time( NULL ) );  

    size_t i = 0;
    
    for (int x = 0; x <MAP_MESH_SIZE_X; x++) {
      for (int y = 0; y<MAP_MESH_SIZE_Y; y++) {
          vertices[i].x = (float)x*(float)SIZE/(float)MAP_MESH_SIZE_X - (float)SIZE;
          vertices[i].y = (float)y*(float)SIZE/(float)MAP_MESH_SIZE_Y - (float)SIZE;
          vertices[i].z =  generateRandom(zmax, zmin);
          i++;
      }
    }
  }

  void draw(OpenGLGC* gc)
  {
    size_t i = 0;

    for (int x = 0; x <MAP_MESH_SIZE_X-1; x++) {
     gc-> begin(primitive);

      for (int y = 0; y<MAP_MESH_SIZE_Y; y++) {
/*        gc->vertex(vertices[x].x, vertices[x].y, vertices[x].z);
        gc->vertex(vertices[y+1].x, vertices[y+1].y, vertices[y+1].z);
        gc->vertex(vertices[x+1].x, vertices[x+1].y, vertices[x+1].z);
*/
//        gc->vertex(vertices[x  ].x, vertices[y].y. vertices[x].z);
//        gc->vertex(vertices[x+1].x, vertices[y].y. vertices[x+1].z);
        
        //float h1 = 0.0f; //generateRandom(HEIGHT_MAX, HEIGHT_MIN);
        //float h2 = 0.0f; //generateRandom(HEIGHT_MAX, HEIGHT_MIN);
        float h1 = generateRandom(HEIGHT_MAX, HEIGHT_MIN);
        float h2 = generateRandom(HEIGHT_MAX, HEIGHT_MIN);

        //        if (x >0 || y >0) {
//          h1 = generateRandom(HEIGHT_MAX, HEIGHT_MIN);
//          h2 = generateRandom(HEIGHT_MAX, HEIGHT_MIN);
//        }
        glVertex3f((float)x/(float)SIZE,     h1, (float)y/(float)SIZE);//,   0.0f);//height[x][y])
        glVertex3f((float)(x+1)/(float)SIZE, h2, (float)y/(float)SIZE);//,   0.0f);// height[x+1][y])

        i++;
      }
     gc->end();

    }
  }

  void dump()
  {
    size_t i = 0;
    for (int x = 0; x <MAP_MESH_SIZE_X; x++) {
      
      for (int y = 0; y<MAP_MESH_SIZE_Y; y++) {
        i++;
        printf("(%d %d) = (%lf, %lf, %lf)\n", x, y, vertices[i].x, vertices[i].y, vertices[i].z);
      }
    }

  }
 
};
}

