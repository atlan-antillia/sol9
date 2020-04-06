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
 *  OpenGLBitmap.h
 *
 *****************************************************************************/

#include <sol/opengl/OpenGLObject.h>
#include <sol/JPGFileWriter.h>
#include <sol/PNGFileWriter.h>

namespace SOL {

class OpenGLBitmap :public OpenGLObject {
private:
  GLint x;
  GLint y;
  GLsizei width;
  GLsizei height;
  GLenum  format;
  GLenum  type;
  GLvoid* pixels;
  int channels;
  int depth;
  
public:
  OpenGLBitmap(GLint x, GLint y, GLsizei width, GLsizei height, 
                    int depth, GLenum format=GL_RGB, GLenum type = GL_UNSIGNED_BYTE)
  :x(x),
   y(x),
   width(width),
   height(height),
   format(format),
   type(type),
   pixels(NULL),
   channels(0),
   depth(depth)
  {
    channels = 1;
    switch (format) {
    //case GL_BGR:
    case GL_RGB:
      channels = 3;
      break;
    case GL_RGBA:
      channels = 4;
      break;
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
     channels = 1;
     break;
    }
    size_t size = width*height*channels;
    pixels = new GLubyte[size];
    memset(pixels, '\0', size);

  }

  ~OpenGLBitmap()
  {
    delete [] pixels;
    pixels = NULL;
  }  

  GLvoid* read(GLenum buffer=GL_BACK)
  {
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(buffer);
    glReadPixels(x, y, width, height, format, type, pixels);
    return pixels;
  }

  bool saveAsJPG(const char* filename, bool vertFlip=true)
  {
    bool rc = false;
    try {
      JPGFileWriter writer(filename);
      int quality   = 100;
      writer.write(width, height, depth, channels,(unsigned char*)pixels, quality, vertFlip);
      rc = true;
    } catch (Exception& ex) {
      ex.display();
    }
    return rc;   
  }

  bool saveAsPNG(const char* filename, bool vertFlip=true)
  {
    bool rc = false;
    try {
      PNGFileWriter writer(filename);
     
      writer.write(width, height, depth, channels, (unsigned char*)pixels, vertFlip);
      rc = true;
    } catch (Exception& ex) {
      ex.display();
    }
    return rc;   
  }

};

}
