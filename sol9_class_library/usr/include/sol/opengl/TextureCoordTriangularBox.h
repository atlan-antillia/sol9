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
 *  TextureCoordTriangularBox.h
 *
 *****************************************************************************/
 
#pragma once


#include <sol/Object.h>

#include <sol/opengl/TextureCoord2Vertex3.h>

namespace SOL {

class TextureCoordTriangularBox : public Object {
private:
  TextureCoord2Vertex3* box;
  int numberOfElements;
  int numberOfFaces;
  int numberOfVerticesPerFace;
  
public:
  TextureCoordTriangularBox(GLfloat x=1.0f, GLfloat y=1.0f, GLfloat z=1.0f)
  :box(NULL),
  numberOfElements(0),
  numberOfFaces(0),
  numberOfVerticesPerFace(0)
  {
    TextureCoord2Vertex3 boxData[] = {
        // Front
        // Face 0-1-2
        {{1.0f, 1.0f}, {  x,  y, z}},
        {{0.0f, 1.0f}, { -x,  y, z}},
        {{0.0f, 0.0f}, { -x, -y, z}},
        // Face 2-3-0
        {{0.0f, 0.0f}, { -x, -y, z}},
        {{1.0f, 0.0f}, {  x, -y, z}},
        {{1.0f, 1.0f}, {  x,  y, z}},

        // Right
        // Face 0-3-4
        {{0.0f, 1.0f}, {  x,  y,  z}},
        {{0.0f, 0.0f}, {  x, -y,  z}},
        {{1.0f, 0.0f}, {  x, -y, -z}},
        // Face 4-5-0
        {{1.0f, 0.0f}, {  x, -y, -z}},
        {{1.0f, 1.0f}, {  x,  y, -z}},
        {{0.0f, 1.0f}, {  x,  y,  z}},

        // Top 
        // Face 0-5-6
        {{1.0f, 0.0f}, {  x,  y,  z}},
        {{1.0f, 1.0f}, {  x,  y, -z}},
        {{0.0f, 1.0f}, { -x,  y, -z}},
        // Face 6-1-0
        {{0.0f, 1.0f}, { -x,  y, -z}},
        {{0.0f, 0.0f}, { -x,  y,  z}},
        {{1.0f, 0.0f}, {  x,  y,  z}},

        // Left
        // Face  1-6-7
        {{1.0f, 1.0f}, { -x,  y,  z}},
        {{0.0f, 1.0f}, { -x,  y, -z}},
        {{0.0f, 0.0f}, { -x, -y, -z}},
        // Face 7-2-1
        {{0.0f, 0.0f}, { -x, -y, -z}},
        {{1.0f, 0.0f}, { -x, -y,  z}},
        {{1.0f, 1.0f}, { -x,  y,  z}},

        // Bottom 
        // Face 7-4-3
        {{0.0f, 0.0f}, { -x, -y, -z}},
        {{1.0f, 0.0f}, {  x, -y, -z}},
        {{1.0f, 1.0f}, {  x, -y,  z}},
        // Face 3-2-7
        {{1.0f, 1.0f}, {  x, -y,  z}},
        {{0.0f, 1.0f}, { -x, -y,  z}},
        {{0.0f, 0.0f}, { -x, -y, -z}},

        // Back
        // Face 4-7-6
        {{0.0f, 0.0f}, {  x, -y, -z}},
        {{1.0f, 0.0f}, { -x, -y, -z}},
        {{1.0f, 1.0f}, { -x,  y, -z}},
        // Face 6-5-4
        {{1.0f, 1.0f}, { -x,  y, -z}},
        {{0.0f, 1.0f}, {  x,  y, -z}},
        {{0.0f, 0.0f}, {  x, -y, -z}},
    };
    this->numberOfElements = CountOf(boxData);

    this->box = new TextureCoord2Vertex3[this->numberOfElements];
    memcpy(this->box, boxData, sizeof(boxData));

      
    this->numberOfFaces    = 6;
    this->numberOfVerticesPerFace = 6;
  }

  ~TextureCoordTriangularBox()
  {
    delete [] box;
    box = NULL;
  }
    
  TextureCoord2Vertex3* getData()
  {
    return box;
  }
  
  int getNumberOfElements()
  {
    return numberOfElements;
  }
  
  int getNumberOfFaces()
  {
    return numberOfFaces;
  }
  
  int getNumberOfVerticesPerFace()
  {
    return numberOfVerticesPerFace;
  }
};

}
       
       