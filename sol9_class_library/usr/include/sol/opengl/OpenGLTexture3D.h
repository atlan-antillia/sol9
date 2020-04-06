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
 *  OpenGLTexture3D.h
 *
 *****************************************************************************/

// See https://www.opengl.org/sdk/docs/man3/xhtml/glTexImage3D.xml

#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLTexture.h>

namespace SOL {

class OpenGLTexture3D :public OpenGLTexture {

public:
  OpenGLTexture3D()
  :OpenGLTexture(GL_TEXTURE_3D)
  {
  } 

  ~OpenGLTexture3D()
  {
  }
  
  void image(GLint level,  
             GLint internalFormat,  
             GLsizei width,  
             GLsizei height,  
             GLsizei depth,  
             GLint border,  
             GLenum format,  
             GLenum type,  
             const GLvoid * data) 
  { 
    glTexImage3D(getTarget(),  
       level,  
       internalFormat,  
       width,  
       height,  
       depth,  
       border,  
       format,  
       type,  
       data); 
  }

/*
level
  Specifies the level-of-detail number. 
  Level 0 is the base image level. Level n is the n th   mipmap reduction image. 

internalFormat
  Specifies the number of color components in the texture. Must be one of 
  the following symbolic constants: 
   GL_RGBA32F, GL_RGBA32I, GL_RGBA32UI, GL_RGBA16, GL_RGBA16F, GL_RGBA16I, GL_RGBA16UI, GL_RGBA8, GL_RGBA8UI, GL_SRGB8_ALPHA8, GL_RGB10_A2, GL_RGB10_A2UI, GL_R11F_G11F_B10F, GL_RG32F, GL_RG32I, GL_RG32UI, GL_RG16, GL_RG16F, GL_RGB16I, GL_RGB16UI, GL_RG8, GL_RG8I, GL_RG8UI, GL_R32F, GL_R32I, GL_R32UI, GL_R16F, GL_R16I, GL_R16UI, GL_R8, GL_R8I, GL_R8UI, GL_RGBA16_SNORM, GL_RGBA8_SNORM, GL_RGB32F, GL_RGB32I, GL_RGB32UI, GL_RGB16_SNORM, GL_RGB16F, GL_RGB16I, GL_RGB16UI, GL_RGB16, GL_RGB8_SNORM, GL_RGB8, GL_RGB8I, GL_RGB8UI, GL_SRGB8, GL_RGB9_E5, GL_RG16_SNORM, GL_RG8_SNORM, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RG_RGTC2, GL_R16_SNORM, GL_R8_SNORM, GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_SIGNED_RED_RGTC1, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT16, GL_DEPTH32F_STENCIL8, GL_DEPTH24_STENCIL8. 

width
  Specifies the width of the texture image. All implementations support 
  3D texture images that are at least 16 texels wide. 

height
  Specifies the height of the texture image. All implementations support 
  3D texture images that are at least 256 texels high. 

depth
 Specifies the depth of the texture image, or the number of layers in a 
 texture array. All implementations support 3D texture images that are 
 at least 256 texels deep, and texture arrays that are at least 256 
  layers deep. 

border
  This value must be 0. 

format
  Specifies the format of the pixel data. The following symbolic values are 
  accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, and GL_BGRA. 

type
  Specifies the data type of the pixel data. The following symbolic values 
  are accepted: 
   GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV. 

data
Specifies a pointer to the image data in memory. 

 */
};

}


