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
 *  OpenGLTexture2D.h
 *
 *****************************************************************************/

//2015/07/28 Added methods imageFromFile, imageFromJPGFile and imageFromPNGFile.
//2015/08/22 Added methods subImage, subImageFromFile, subImageFromJPGFile and subImageFromPNGFile.
//2015/08/22 Added methods mipmap, mipmapFromFile, mipmapFromJPGFile and mipmapFromPNGFile.
//2017/09/10 Added a new method image which takes an OpenGLImageInfo argument.
#pragma once

#include <sol/String.h>
#include <sol/Exception.h>
#include <sol/opengl/OpenGLImageInfo.h>

#include <sol/opengl/OpenGLTexture.h>
#include <sol/JPGFileReader.h>
#include <sol/PNGFileReader.h>
#define GL_BGR  0x80E0 
#define GL_BGRA 0x80E1

namespace SOL {

class OpenGLTexture2D :public OpenGLTexture {

public:
  //Modified this constructor to take a target argument.
  OpenGLTexture2D(GLenum target = GL_TEXTURE_2D)
  :OpenGLTexture(target)
  {
  } 

  ~OpenGLTexture2D()
  {
  }
  
  //2016/07/20  
  void image(GLenum target, GLint level, GLint components,
       GLsizei width, GLsizei height, GLint border,
       GLenum format, GLenum type, const GLvoid *pixels)
  { 
    glTexImage2D(target,
        level, components,
        width, height, border,
        format, type, pixels); 
  }
  
  void image(GLint level, GLint components,
       GLsizei width, GLsizei height, GLint border,
       GLenum format, GLenum type, const GLvoid *pixels)
  { 
    glTexImage2D(getTarget(),
        level, components,
        width, height, border,
        format, type, pixels); 
  }
  
  //2017/08/30
  void image(OpenGLImageInfo& imageInfo)
  {
    glTexImage2D(getTarget(),
        0, 
        imageInfo.internalFormat,
        imageInfo.width, 
        imageInfo.height, 
        0,
        (GLenum)imageInfo.format, 
        (GLenum)imageInfo.type, 
        (uint32_t*)imageInfo.imageData);
  }
  
/*
  void subImage(GLint level,  
                GLint xoffset,  
                GLint yoffset,  
                GLsizei width,  
                GLsizei height,  
                GLenum format,  
                GLenum type,  
                const GLvoid * data)
  {
    glTexSubImage2D(getTarget(),  
        level,  
        xoffset,  
        yoffset,  
        width,  
        height,  
        format,  
        type,  
       data); 
  }
*/  
  void imageFromFile(const char* filename, GLint level=0, GLint border=0)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    if (String::endsWithIgnoreCase(filename, ".png")) {
      imageFromPNGFile(filename, level, border);
    } else if (String::endsWithIgnoreCase(filename, ".jpg")) {
      imageFromJPGFile(filename, level, border);
    } else {
      ;//Unsupported file types
      throw IException("Invalid file types");  
    }
  }

  void imageFromFile(const char* filename, GLenum target, GLint level=0, GLint border=0)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    if (String::endsWithIgnoreCase(filename, ".png")) {
      imageFromPNGFile(filename, target, level, border);
    } else if (String::endsWithIgnoreCase(filename, ".jpg")) {
      imageFromJPGFile(filename, target, level, border);
    } else {
      ;//Unsupported file types
      throw IException("Invalid file types");  
    }
  }

  void imageFromPNGFile(const char* filename, GLint level=0, GLint border=0)
  {
    //As you know, in general, an image width or height must be the power of 2.
    PNGFileReader* reader = NULL;
    try {
      reader = new PNGFileReader(filename); 
      reader -> version();
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        //reader -> properties();
        int format = GL_RGB;
        if (reader -> getColorType() == PNG_COLOR_TYPE_RGB_ALPHA) {
          format = GL_RGBA;
        } else if (reader -> getColorType() == PNG_COLOR_TYPE_RGB) {
          format = GL_RGB;
        }
        this -> image(level, GL_RGBA, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    border, format, GL_UNSIGNED_BYTE, image);

        } else {
          throw IException("Image data is NULL");
        }
        
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  void imageFromPNGFile(const char* filename, GLenum target, GLint level=0, GLint border=0)
  {
    //As you know, in general, an image width or height must be the power of 2.
    PNGFileReader* reader = NULL;
    try {
      reader = new PNGFileReader(filename); 
      reader -> version();
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        //reader -> properties();
        int format = GL_RGB;
        if (reader -> getColorType() == PNG_COLOR_TYPE_RGB_ALPHA) {
          format = GL_RGBA;
        } else if (reader -> getColorType() == PNG_COLOR_TYPE_RGB) {
          format = GL_RGB;
        }
        this -> image(target, level, GL_RGBA, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    border, format, GL_UNSIGNED_BYTE, image);

        } else {
          throw IException("Image data is NULL");
        }
        
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }
 
  void imageFromJPGFile(const char* filename, GLenum target, GLint level = 0, GLint border=0)
  {
    //As you know, in general, an image width or height must be the power of 2.
    JPGFileReader* reader = NULL;
    try {
      reader = new JPGFileReader(filename); 
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        //int format = GL_BGR;
        int format = GL_BGRA;

        this -> image(target, level, GL_RGBA, reader -> getImageWidth(), 
        //this -> image(target, level, GL_RGB, reader -> getImageWidth(), 

          reader -> getImageHeight(), 
                    border, format, GL_UNSIGNED_BYTE, image);
      } else {
        throw IException("Image data is NULL");
      }
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  void imageFromJPGFile(const char* filename, GLint level = 0, GLint border=0)
  {
    //As you know, in general, an image width or height must be the power of 2.
    JPGFileReader* reader = NULL;
    try {
      reader = new JPGFileReader(filename); 
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        int format = GL_BGRA;
        this -> image(level, GL_RGBA, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    border, format, GL_UNSIGNED_BYTE, image);
      } else {
        throw IException("Image data is NULL");
      }
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  void subImage(GLint level,  
                GLint xoffset,  
                GLint yoffset,  
                GLsizei width,  
                GLsizei height,  
                GLenum format,  
                GLenum type,  
                const GLvoid * data)
  {
    glTexSubImage2D(getTarget(),  
        level,  
        xoffset,  
        yoffset,  
        width,  
        height,  
        format,  
        type,  
       data); 
  }
  
  void subImageFromFile(const char* filename, GLint level, GLint xoffset, GLint yoffset)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    if (String::endsWithIgnoreCase(filename, ".png")) {
      subImageFromPNGFile(filename, level, xoffset, yoffset);
    } else if (String::endsWithIgnoreCase(filename, ".jpg")) {
      subImageFromJPGFile(filename, level, xoffset, yoffset);
    } else {
      ;//Unsupported file types
      throw IException("Invalid file types");  
    }
  }

  void subImageFromPNGFile(const char* filename, GLint level, GLint xoffset, GLint yoffset)
  {
    //As you know, in general, an image width or height must be the power of 2.
    PNGFileReader* reader = NULL;
    try {
      reader = new PNGFileReader(filename); 
      reader -> version();
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        //reader -> properties();
        int format = GL_RGB;
        if (reader -> getColorType() == PNG_COLOR_TYPE_RGB_ALPHA) {
          format = GL_RGBA;
        } else if (reader -> getColorType() == PNG_COLOR_TYPE_RGB) {
          format = GL_RGB;
        }
        this -> subImage(level, xoffset, yoffset, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    format, GL_UNSIGNED_BYTE, image);

        } else {
          throw IException("Image data is NULL");
        }
        
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  void subImageFromJPGFile(const char* filename, GLint level, GLint xoffset, GLint yoffset)
  {
    //As you know, in general, an image width or height must be the power of 2.
    JPGFileReader* reader = NULL;
    try {
      reader = new JPGFileReader(filename); 
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        int format = GL_BGRA;
        this -> subImage(level, xoffset, yoffset, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    format, GL_UNSIGNED_BYTE, image);

      } else {
        throw IException("Image datais NULL");
      }
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  //2015/08/22
  //See  https://www.opengl.org/sdk/docs/man2/xhtml/gluBuild2DMipmaps.xml
  void mipmap(GLint internalFormat,  //GL_RGB
        GLsizei width,  
        GLsizei height,  
        GLenum format,               //GL_RGB
        GLenum type,                 //GL_UNSIGNED_BYTE
        const void * data) 
  {  
    gluBuild2DMipmaps(getTarget(), 
        internalFormat,  
        width,  
        height,  
        format,  
        type,  
        data);
  }

  void mipmapFromFile(const char* filename)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    if (String::endsWithIgnoreCase(filename, ".png")) {
      mipmapFromPNGFile(filename);
    } else if (String::endsWithIgnoreCase(filename, ".jpg")) {
      mipmapFromJPGFile(filename);
    } else {
      ;//Unsupported file types
      throw IException("Invalid file types");  
    }
  }

  void mipmapFromPNGFile(const char* filename)
  {
    //As you know, in general, an image width or height must be the power of 2.
    PNGFileReader* reader = NULL;
    try {
      reader = new PNGFileReader(filename); 
      reader -> version();
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        //reader -> properties();
        int format = GL_RGB;
        if (reader -> getColorType() == PNG_COLOR_TYPE_RGB_ALPHA) {
          format = GL_RGBA;
        } else if (reader -> getColorType() == PNG_COLOR_TYPE_RGB) {
          format = GL_RGB;
        }
        this -> mipmap(GL_RGBA, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    format, GL_UNSIGNED_BYTE, image);

        } else {
          throw IException("Image data is NULL");
        }
        
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }

  void mipmapFromJPGFile(const char* filename)
  {
    //As you know, in general, an image width or height must be the power of 2.
    JPGFileReader* reader = NULL;
    try {
      reader = new JPGFileReader(filename); 
      reader -> read();

      GLvoid* image = reader -> getImageData(); 
      if (image) {
        int format = GL_BGRA;
        this -> mipmap(GL_RGBA, reader -> getImageWidth(), 
                    reader -> getImageHeight(), 
                    format, GL_UNSIGNED_BYTE, image);
      } else {
        throw IException("Image datais NULL");
      }
    } catch (Exception& ex) {
      ex.display();
    }
    delete reader;
  }


};

}


