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
 *  OpenGLGC.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Exception.h>
//#include <sol/ArrayT.h>
#include <sol/opengl/OpenGLObject.h>
#include <math.h>

#include <sol/opengl/OpenGLFace.h>
#include <sol/opengl/Color3.h>
#include <sol/opengl/Color4.h>

#include <sol/opengl/Normal3.h>
#include <sol/opengl/Vertex3.h>
#include <sol/opengl/Vertex3Triplet.h>

#include <sol/Vertex.h>

namespace SOL {

class OpenGLGC :public OpenGLObject {
  
public:
  OpenGLGC()
  :OpenGLObject()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  } 

  ~OpenGLGC()
  {
    glEnd();  
    glFlush();
  }

  void frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble znear, GLdouble zfar)
  {
    glFrustum(left, right, bottom, top, znear, zfar); 
  }
  
  void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
  {
    gluPerspective(fovy, aspect, zNear, zFar); 
  }
  
  void clearColor(float red, float green, float blue, float alpha)
  {
    glClearColor(red, green, blue, alpha);
  }

  void clearDepth(float depth)
  {
    glClearDepth(depth);
  }

  void backgroundColor(float red, float green, float blue, float alpha)
  {
    glClearColor(red, green, blue, alpha);
  }

  void enable(GLenum mode)
  {
    glEnable(mode);
  }
  
  void clear(int mode)
  {
    glClear(mode); 
  }
  
  void begin(GLenum mode )
  {
    glBegin(mode);
  }

  void end()
  {
    glEnd();
  }

  void loadIdentity()
  {
    glLoadIdentity();
  }
  
  void matrixMode(int mode)
  {
    glMatrixMode(mode);   
  }
 
  void viewport(int x, int y, int width, int height)
  {
    glViewport(x, y, width, height);
  }
  
  void viewport(GLsizei size, GLint* values)
  {
    if (size == 4 && values) {
      glViewport(values[0], values[1], values[2], values[3]);
    }
  }

  void ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, 
   GLdouble nearv, GLdouble farv)
  {
    glOrtho(left, right, bottom, top, nearv, farv);
  }

  void ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) 
  {
    gluOrtho2D(left, right, bottom,  top); 
  }

  void lookAt(GLdouble ex,GLdouble ey,GLdouble ez,
      GLdouble cx,GLdouble cy,GLdouble cz,
      GLdouble ux,GLdouble uy,GLdouble uz)
  {
    gluLookAt(ex, ey,ez,
    cx, cy, cz,
    ux, uy, uz);
  }
  
public:
  void red()
  {
    glColor3f(1.0f, 0.0f, 0.0f);  
  }

  void green()
  {
    glColor3f(0.0f, 1.0f, 0.0f);  
  }
  void blue()
  {
    glColor3f(0.0f, 0.0f, 1.0f);  
  }
  
  void color(GLfloat r, GLfloat g, GLfloat b)
  {
    glColor3f(r, g, b);  
  }

  void color(Color3<GLint>& color)
  {
    glColor3iv((GLint*)&color); 
  }
  
  void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    glColor4f(r, g, b, a);  
  }

  void color(Color3<GLfloat>& color)
  {
    glColor3fv((GLfloat*)&color); 
  }

  void foregroundColor(float r, float g, float b)
  {
    glColor3f(r, g, b);
  }

  //<Vertex2>
  void redVertex(float x, float y)
  {
    red();
    glVertex2f(x, y);
  }
  
  void greenVertex(float x, float y)
  {
    green();
    glVertex2f(x, y);
  }
  
  void blueVertex(float x, float y)
  {
    blue();
    glVertex2f(x, y);
  }

  void coloredVertex(GLdouble r, GLdouble  g, GLdouble b, GLdouble x, GLdouble y)
  {
    glColor3f(r, g, b);
    glVertex2f(x, y);
  }
  
  void vertex(GLdouble x, GLdouble y)
  {
    glVertex2d(x, y);
  }

  void vertex(GLfloat x, GLfloat y)
  {
    glVertex2f(x, y);
  }

  void coloredVertex(int r,int  g, int b, float x, float y)
  {
    glColor3d(r, g, b);
    glVertex2f(x, y);
  }
  //</VerTex2>
  
  //<Vertex3>
  void redVertex(float x, float y, float z)
  {
    red();
    glVertex3f(x, y, z);
  }
  
  void greenVertex(float x, float y, float z)
  {
    green();
    glVertex3f(x, y, z);
  }
  
  void blueVertex(float x, float y, float z)
  {
    blue();
    glVertex3f(x, y, z);
  }
  
  void coloredVertex(float r, float g, float b, double x, double y, double z)
  {
    glColor3f(r, g, b);
    glVertex3d(x, y, z);
  }

  void coloredVertex(int r,int g, int b, float x, float y, float z)
  {
    glColor3d(r, g, b);
    glVertex3f(x, y, z);
  }

  void vertex(GLfloat x, GLfloat y, GLfloat z)
  {
    glVertex3f(x, y, z);
  }

  //2017/02/15
  void vertex(Vertex3& v)
  {
    glVertex3f(v.x, v.y, v.z);
  }
  
  void triangles(Vertex3Triplet* triplets, size_t count)
  {
    for (size_t i = 0; i<count; i++) {
    glBegin(GL_TRIANGLES);

      glVertex3f(triplets[i].a.x, triplets[i].a.y, triplets[i].a.z);
      glVertex3f(triplets[i].b.x, triplets[i].b.y, triplets[i].b.z);
      glVertex3f(triplets[i].c.x, triplets[i].c.y, triplets[i].c.z);    
    glEnd();

    }
  }
  
  //2017/02/15
  void triangle(Vertex3& a, Vertex3& b, Vertex3& c)
  {
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);    
  }
  
  void vertex(GLdouble x, GLdouble y, GLdouble z)
  {
    glVertex3d(x, y, z);
  }

  void texCoordVertex(GLfloat tx, GLfloat ty, GLfloat tz,
               GLfloat x, GLfloat y, GLfloat z)
  {
    glTexCoord3f(tx, ty, tz);
    glVertex3f(x, y, z);
  }

  //</VerTex3>

  //<Vertex4>
  void redVertex(float x, float y, float z, float w)
  {
    red();
    glVertex4f(x, y, z, w);
  }
  
  void greenVertex(float x, float y, float z, float w)
  {
    green();
    glVertex4f(x, y, z, w);
  }
  
  void blueVertex(float x, float y, float z, float w)
  {
    blue();
    glVertex4f(x, y, z, w);
  }
  
  void coloredVertex(float r, float g, float b, float x, float y, float z, float w)
  {
    glColor3f(r, g, b);
    glVertex4f(x, y, z, w);
  }

  void coloredVertex(int r,int  b, int g, float x, float y, float z, float w)
  {
    glColor3d(r, g, b);
    glVertex4f(x, y, z, w);
  }
  //</VerTex4>

  void coloredRectangle(int r, int g, int b, float x1, float y1, float x2, float y2)
  {
    glColor3d(r, g, b);
    glRectf(x1, y1, x2, y2);
  }
 
  
  void coloredRectangle(float r, float g, float b, float x1, float y1, float x2, float y2)
  {
    glColor3f(r, g, b);
    glRectf(x1, y1, x2, y2);
  }

  void translate( GLdouble x, GLdouble y, GLdouble z)
  {
    glTranslated(x, y, z);
  }
  
  void translate(GLfloat x, GLfloat y, GLfloat z) 
  {
    glTranslatef(x, y, z);
  }
    
  void normal(GLbyte nx , GLbyte ny , GLbyte nz)
  {
     glNormal3b(nx, ny, nz);
  }
  
  void normal(GLdouble nx, GLdouble ny, GLdouble nz)
  {
    glNormal3d(nx, ny, nz);
  }
  
  void normal(GLfloat nx, GLfloat ny, GLfloat nz)
  {
    glNormal3f(nx, ny, nz);
  }

  void normal(GLint nx , GLint ny , GLint nz)
  {
    glNormal3i(nx , ny, nz);
  }
  
  //void glNormal3s(GLshort nx , GLshort ny , GLshort nz);

  void normal(const GLbyte *v)
  {
    assert(v);
    glNormal3bv(v);
  }
  
  void normal(const GLdouble *v)
  {
    assert(v);
    glNormal3dv(v);
  }

  void normal(const GLfloat *v)
  {
    assert(v);
    glNormal3fv(v);
  }
  
  void normal(const GLint *v)
  {
    assert(v);
    glNormal3iv(v);
  }
//  void glNormal3sv(const GLshort *v);
  
  void lineWidth(GLfloat width)
  {
    glLineWidth(width);
  }

  void hint(GLenum name, GLenum value)
  {
    glHint(name,  value);
  }
  
  void blendFunc(GLenum name, GLenum value)
  {
    glBlendFunc(name, value);
  }
  
  void disable(GLenum capability)
  {
    glDisable(capability);
  }

  void point(GLfloat x, GLfloat y)
  {
    begin(GL_POINTS);
    glPointSize(0.02f);
    vertex(x, y);
//    vertex(x+0.02f, y);
//    vertex(x, y+0.02f);
    vertex(x+0.02f, y+0.02f);
    end();
    
  }
  
  void smoothLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width)
  {
    enable(GL_LINE_SMOOTH);

    enable(GL_BLEND);
    blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    hint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
    lineWidth(width);

    begin(GL_LINES);
    vertex(x1, y1);
    vertex(x2, y2);
    end();
    disable(GL_BLEND);
    disable(GL_LINE_SMOOTH);
  }

  void shadeModel(GLenum mode)
  {
    glShadeModel(mode);
  }

  void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width)
  {
    lineWidth(width);

    begin(GL_LINES);
    vertex(x1, y1);
    vertex(x2, y2);
    end();
    lineWidth(0.0);
  }
  
  void vertexPointer(
    GLint size, GLenum type, GLsizei stride,
    const GLvoid *pointer)
  {
    //assert(pointer);
    glVertexPointer(size, type, stride, pointer);
  }   

  void polygonMode(GLenum face, GLenum mode)
  {
    glPolygonMode(face,  mode); 
  }

  //2016/07/04 Removed assert(indices).
  void drawElements(
    GLenum mode , GLsizei count ,
    GLenum type , const GLvoid *indices)
  {
    glDrawElements(mode, count, type, indices);
  }

  void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
  {
    glRotatef(angle, x, y, z);
  }

  void draw(OpenGLVertex3& v)
  {
    vertex(v.x, v.y, v.z); 
  }

  void draw(Normal3& n, Vertex3& v1, Vertex3& v2, Vertex3& v3)
  {
    normal(n.x, n.y, n.z);
    vertex(v1.x, v1.y, v1.z); 
    vertex(v2.x, v2.y, v2.z); 
    vertex(v3.x, v3.y, v3.z);
  }

  void draw(Normal3& n, Vertex<3>& v1)
  {
    normal(n.x, n.y, n.z);
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
  }
  
  void draw(Normal3& n, Vertex<3>& v1, Vertex<3>& v2, Vertex<3>& v3)
  {
    normal(n.x, n.y, n.z);
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
    
    vertex(v2.value[0], v2.value[1], v2.value[2]); 

    vertex(v3.value[0], v3.value[1], v3.value[2]); 
  }

  void draw(Normal3& n, Vertex<3>& v1, Vertex<3>& v2, Vertex<3>& v3, Vertex<3>& v4)
  {
    normal(n.x, n.y, n.z);
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
    vertex(v2.value[0], v2.value[1], v2.value[2]); 
    vertex(v3.value[0], v3.value[1], v3.value[2]); 
    vertex(v4.value[0], v4.value[1], v4.value[2]); 
  }

  void draw(Color4& c, Normal3& n, Vertex<3>& v1)
  {
    normal(n.x, n.y, n.z);

    color(c.r, c.g, c.b, c.a);
    
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
  }

  void draw(Color4& c, Normal3& n, Vertex<3>& v1, Vertex<3>& v2, Vertex<3>& v3)
  {
    normal(n.x, n.y, n.z);

    color(c.r, c.g, c.b, c.a);
    
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
    vertex(v2.value[0], v2.value[1], v2.value[2]); 
    vertex(v3.value[0], v3.value[1], v3.value[2]); 
  }

  void draw(Color4& c, Vertex<3>& v1, Vertex<3>& v2, Vertex<3>& v3)
  {
    color(c.r, c.g, c.b, c.a);
    
    vertex(v1.value[0], v1.value[1], v1.value[2]); 
    vertex(v2.value[0], v2.value[1], v2.value[2]); 
    vertex(v3.value[0], v3.value[1], v3.value[2]); 
  }

  void draw(Vertex3& v1, Vertex3& v2, Vertex3& v3)
  {    
    vertex(v1.x, v1.y, v1.z); 
    vertex(v2.x, v2.y, v2.z); 
    vertex(v3.x, v3.y, v3.z); 
  }

  //2015/05/10
  void draw(OpenGLFace& face)
  {
    draw(face.v1);
    draw(face.v2);
    draw(face.v3);
    draw(face.v4);
  }

  //2015/06/10
  void draw(OpenGLVertex3* vertices, size_t size)
  {
    if (vertices && size > 0) {
      for (size_t i = 0; i < size; i++) {
         draw(vertices[i]);
      }
    }
  }

  void scale(GLfloat x, GLfloat y, GLfloat z)
  {
    glScalef(x, y, z);
  }

  void scale(GLdouble x, GLdouble y, GLdouble z)
  {
    glScaled(x, y, z);
  }

  void pushMatrix()
  {
    glPushMatrix();
  }

  void popMatrix()
  {
    glPopMatrix();
  }

  void rasterPos(GLint x, GLint y)
  {
    glRasterPos2i(x, y);
  }

  void rasterPos(GLfloat x, GLfloat y)
  {
    glRasterPos2f(x, y);
  }

/*  void activeTexture(GLenum texture = GL_TEXTURE0)
  {
    glActiveTexture(texture);
  }
*/
  void drawBitmap( GLfloat x, GLfloat y,
                   GLsizei width , GLsizei height , 
                   const GLubyte * bitmap  )
  {
    glRasterPos2f(x, y);
    glBitmap(width, height, 
      0, 0,
      0, 0,
      bitmap );
  }

  void drawBitmap(
        GLfloat x, GLfloat y,
        GLsizei width , GLsizei height ,
        GLfloat xorig , GLfloat yorig ,
        GLfloat xmove , GLfloat ymove ,
        const GLubyte * bitmap  )
  {
    glRasterPos2f(x, y);
    glBitmap(
        width, height, 
        xorig, yorig,
        xmove, ymove,
        bitmap );
  }

  void drawBitmap(
        GLsizei width , GLsizei height ,
        GLfloat xorig , GLfloat yorig ,
        GLfloat xmove , GLfloat ymove ,
        const GLubyte * bitmap  )
  {
    glBitmap(
        width, height,                  
        xorig, yorig,
        xmove, ymove,
        bitmap );
  }

  void drawPixels(
      GLsizei width, GLsizei height,
      GLenum format, GLenum type, const GLvoid *pixels )
  {
    glDrawPixels( width, height, format, type, pixels); 
    /*
    format:
    GL_COLOR_INDEX, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, 
    GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED, GL_GREEN, 
    GL_BLUE, GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA

    type:
    GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, 
    GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, 
    GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, 
    GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, 
    GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, 
    GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
    GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, 
    GL_UNSIGNED_INT_2_10_10_10_REV 
   */
  }
  
  //2016/06/30
  void drawArrays(GLenum mode , GLint first , GLsizei count)
  {
    glDrawArrays(mode , first , count);
  }
  
  void interleavedArrays(GLenum   format,  
       GLsizei   stride,  
       const GLvoid *   pointer)
  {
    
    glInterleavedArrays(format,  
        stride,  
        pointer); 
    /*
     format:
     GL_V2F, 
     GL_V3F, 
     GL_C4UB_V2F, 
     GL_C4UB_V3F, 
     GL_C3F_V3F, 
     GL_N3F_V3F, 
     GL_C4F_N3F_V3F, 
     GL_T2F_V3F, 
     GL_T4F_V4F, 
     GL_T2F_C4UB_V3F, 
     GL_T2F_C3F_V3F, 
     GL_T2F_N3F_V3F, 
     GL_T2F_C4F_N3F_V3F, 
     GL_T4F_C4F_N3F_V4F 
    */
  }
  
  void arrayElement(GLint index)
  {
    glArrayElement(index);
  }

//glClientActiveTexture is supported only if the GL version is 1.3 or greater, or ARB_multitexture 

  void colorPointer( GLint size,  
    GLenum type,  
    GLsizei stride,  
    const GLvoid * pointer)
  { 
    glColorPointer(size,  
     	type,  
  		stride,  
  		pointer); 
  }
 
  void edgeFlagPointer( GLsizei   stride,  
             const GLvoid *   pointer)
  {
    glEdgeFlagPointer(stride,  
    	pointer); 
  }
  
//glEnableClientState, 


  void getPointerv( GLenum pname,  
    GLvoid ** params)
  { 
    glGetPointerv(pname,  
        params); 
  }

  void indexPointer( GLenum type,  
    GLsizei stride,  
    const GLvoid * pointer)
  { 
     glIndexPointer(type,  
       stride,  
       pointer); 
  }
  
 
  void normalPointer(GLenum   type,  
    GLsizei   stride,  
    const GLvoid *   pointer)
  {
    glNormalPointer(type,  
        stride,  
        pointer); 
  }
  
//glSecondaryColorPointer is available only if the GL version is 1.4 or greater. 

  void texCoordPointer( GLint size,  
    GLenum type,  
    GLsizei stride,  
    const GLvoid * pointer)
  {
    glTexCoordPointer(size,  
      type,  
      stride,  
      pointer); 
  }

  void  getViewport(GLsizei size, GLint* viewport)
  {
    if (size == 4 && viewport) {
      glGetIntegerv( GL_VIEWPORT, viewport);
    }
  }
  
  void  getInteger(GLenum name, GLint* values)
  {
    if (values) {
      glGetIntegerv(name, values);
    }
  }

  void flush()
  {
    glFlush();
  }
  
  void frontFace(GLenum c)
  {
    glFrontFace(c);
  }
  
  void cullFace(GLenum c)
  {
    glCullFace(c);
  }

#ifdef GL_VERSION_3_1
  void drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
  {
    static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced =NULL;
    if (glDrawArraysInstanced == NULL) {
      glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)load("glDrawArraysInstanced");
    }
    
    glDrawArraysInstanced(mode, first, count, primcount);
  }
  
  void drawElementsInstanced(GLenum mode,  GLsizei count,  GLenum type,  const void * indices,  GLsizei primcount)
  {
    static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
    if (glDrawElementsInstanced == NULL) {
      glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)load("glDrawElementsInstanced");
    }
    glDrawElementsInstanced(mode, count, type, indices, primcount);
  }
  
  void primitiveRestartIndex(GLuint buffer)
  {
    static PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = NULL;
    if (glPrimitiveRestartIndex == NULL) {
      glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)load("glPrimitiveRestartIndex");
    }
    glPrimitiveRestartIndex(buffer);
  }
  
  
#endif
 
};

}

