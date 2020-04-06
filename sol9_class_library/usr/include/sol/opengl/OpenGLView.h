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
 *  OpenGLView.h
 *
 *****************************************************************************/

// 2015/07/22
// 2015/08/22 Added save, saveAsJPG, saveAsPNG methods to save OpenGL framebuffer to jpg or png files.
// 2016/07/10 Modified to use majorVersion and minorVersion of OpenGL to create an instance
//            of OpenGLRenderContext.
// 2020/02/10 Fixed a bug of paint method to check whether clientDC is NULL or not.

#pragma once

#include <sol/Stdio.h>
#include <sol/ClientDC.h>
#include <sol/SmartPtr.h>

#include <sol/Primitive.h>
#include <sol/PaintDC.h>
#include <sol/opengl/OpenGLPixelFormatRGBA.h>
#include <sol/opengl/OpenGLPalette.h>
#include <sol/opengl/OpenGLRenderContext.h>
#include <sol/opengl/OpenGLBitmap.h> //2015/08/22
#include <sol/Stdio.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#include <sol/opengl/OpenGLProfile.h>

#define WM_INITIALIZE (WM_USER+2015)

namespace SOL {

class OpenGLView :public Primitive {

private:
  SmartPtr<ClientDC>              clientDC;
  SmartPtr<OpenGLPixelFormatRGBA> pixelFormat;
  SmartPtr<OpenGLPalette>         palette;
  SmartPtr<OpenGLRenderContext>   context;

  //2016/07/10
  int  majorVersion;
  int  minorVersion;
  static const int DEFAULT_MAJOR_VERSION = 3;
  static const int DEFAULT_MINOR_VERSION = 1;
  
private:
  long initialize(Event& event)
  {
    clientDC = new ClientDC(this);
    
    Printf("intialized 1\r\n");
    
    pixelFormat = new OpenGLPixelFormatRGBA(clientDC);
    Printf("intialized 2\r\n");
    
    pixelFormat -> setPixelFormat();
    Printf("intialized 3\r\n");

    palette     = new OpenGLPalette(clientDC);
    Printf("intialized 4\r\n");

    context     = new OpenGLRenderContext(clientDC, majorVersion, minorVersion);
    Printf("intialized 5\r\n");
    if (context == nullptr) {
      throw IException("Failed to create OpenGLRenderContext");
    }
    //Call a virtual initialize method.
    initialize();
    
    //2016/07/03 Added the following line to post WM_PAINT message.
    postRenderRequest();
    
    return 0L;
  }
  
  long eraseBackground(Event& event)
  {
    return 1L;
  }

  long paint(Event& event)
  {
    PaintDC dc(this);
  	try {
      //Call a virtual display method.
      display();
        
      glFinish();
  	  //2020/2/10
      if (clientDC) {
        clientDC -> swapBuffer();
      }
    } catch (Exception& ex) {
      caught(ex);
    } catch (...) {
      ;
  	}
    return 1L;
  }


  long size(Event& event)
  {
    
    int w = 0;
    int h = 0;
    event.getSize(w, h);
    glViewport(0, 0, w, h);

    //Call a virtual resize method.
    resize(w, h);
    return 1L;
  }

  long lButtonDown(Event& event)
  {
    leftButtonDown(event);
    return 0L;
  }


  long lButtonUp(Event& event)
  {
    leftButtonUp(event);
    return 0L;
  }

  long kDown(Event& event)
  {
    keyDown(event);
    return 0L;
  }

  long kUp(Event& event)
  {
    keyUp(event);
    return 0L;
  }

   //Please define your own display method in subclass derived form this class.
public:
  virtual void display()
  {
  }

   //Please define your own resize method in subclass derived form this class.
  virtual void resize(int w, int h)
  {
  }

  //Please define your own initialize method in subclass derived form this class.
  virtual void initialize()
  {
  }
  
  //Please define your own method in subclass derived form this class.
  virtual void leftButtonUp(Event& event)
  {
  }
  
  virtual void leftButtonDown(Event& event)
  {
  }

  //Please define your own method in subclass derived form this class.
  virtual void keyDown(Event& event)
  {
  }
  
  virtual void keyUp(Event& event)
  {
  }

private:
  void setContextVersion(Args& args)
  {
    OpenGLProfile profile;
    if (profile.exists() ) {
      profile.read();
      int major = profile.getMajorVersion();
      //char v[128];
      //sprintf(v, "major %d", major);
      //MessageBox(NULL, v, "Debug", MB_OK);
      int minor = profile.getMinorVersion();
      //sprintf(v, "minor %d", minor);
      //MessageBox(NULL, v, "Debug", MB_OK);
      setVersion(major, minor);
    }
    
    if (args.has(XmNmajorVersion) &&
        args.has(XmNminorVersion) ) {
      int major = (int)args.get(XmNmajorVersion);
      int minor = (int)args.get(XmNminorVersion);
      setVersion(major, minor);
    }
  }
  
  void setVersion(int major, int minor)
  {
    if (major >= 1  && major <= 5 &&
      minor >= 0  && minor <= 5) {
      majorVersion = major;
      minorVersion = minor;
    }
  }
  
public:
  //Constructor
  OpenGLView()
  :Primitive(),
	/*
  clientDC(NULL),
  pixelFormat(NULL),
  palette(NULL),
  context(NULL),
	*/
  majorVersion(DEFAULT_MAJOR_VERSION),
  minorVersion(DEFAULT_MINOR_VERSION)
  { 
  }

public:
  //Constructor
  OpenGLView(View* parent, const TCHAR* caption, Args& args)
  :Primitive(),
/*  clientDC(NULL),
  pixelFormat(NULL),
  palette(NULL),
  context(NULL),*/
  majorVersion(DEFAULT_MAJOR_VERSION),
  minorVersion(DEFAULT_MINOR_VERSION)  
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    //2016/07/10
    setContextVersion(args);

    Boolean rc = Primitive::create(parent, caption,  
      args.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE)
          .set(XmNclassName, _T("OpenGLView")) 
          .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));

    addEventHandler(WM_INITIALIZE, this,
                    (Handler)&OpenGLView::initialize, NULL);

    addEventHandler(WM_ERASEBKGND, this,
                    (Handler)&OpenGLView::eraseBackground, NULL);
  
    addEventHandler(WM_PAINT, this,
                    (Handler)&OpenGLView::paint, NULL);
    
    addEventHandler(WM_SIZE, this,
                    (Handler)&OpenGLView::size, NULL);
    
    addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&OpenGLView::lButtonDown, NULL);
  //  addEventHandler(WM_MOUSEMOVE, this,
  //                  (Handler)&OpenGLView::mMove, NULL);
    addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&OpenGLView::lButtonUp, NULL);
    
    addEventHandler(WM_KEYDOWN, this,
                    (Handler)&OpenGLView::kDown, NULL);
    addEventHandler(WM_KEYUP, this,
                    (Handler)&OpenGLView::kUp, NULL);

    post(WM_INITIALIZE, 0, 0);
    
    return rc;
  }

  ~OpenGLView()
  {
/*    delete pixelFormat;
    delete palette;
    delete context;
    delete clientDC;
    */
  }

public:
  ClientDC* getClientDC()
  {
    return clientDC;
  }
  
  void postResizeRequest(int width, int height)
  {
    post(WM_SIZE, 0, MAKELPARAM(width, height));  
  }
  
  //2016/07/03
  void postRenderRequest()
  {
    invalidateAll();
    update();
    post(WM_PAINT);
  }
  
  //2015/08/22
  virtual void save(const char* filename)
  {
    if (StringT<char>::endsWithIgnoreCase(filename, ".jpg")) {
      saveAsJPG(filename);
    } 
    else if (StringT<char>::endsWithIgnoreCase(filename, ".png")) {
      saveAsPNG(filename);
    } else {
        //Ignore
    }
  }

  virtual void saveAsJPG(const char* filename)
  {
    try {
      int width = 0;
      int height = 0;
      get(XmNwidth,  (LONG_PTR*)&width);
      get(XmNheight, (LONG_PTR*)&height);
      int rw = (width / 8) * 8;
          
      OpenGLBitmap bitmap(0, 0, rw, height, 24, GL_RGB);

      bitmap.read(GL_FRONT);
      bitmap.saveAsJPG(filename);
    } catch (Exception& ex) {
           ;//  
    }      
  }

  virtual void saveAsPNG(const char* filename)
  {
    try {
      int width = 0;
      int height = 0;
      get(XmNwidth,  (LONG_PTR*)&width);
      get(XmNheight, (LONG_PTR*)&height);
      int rw = (width / 8) * 8;
          
      OpenGLBitmap bitmap(0, 0, width, height, 8, GL_RGBA);
      bitmap.read(GL_FRONT);
      bitmap.saveAsPNG(filename);
    } catch (Exception& ex) {
           ;//  
    }      
  }
  
  int getMajorVersion()
  {
    return majorVersion;
  }
  
  int getMinorVersion()
  {
    return minorVersion;
  }
  
  //2017/03/01
  void setPerspective(GLdouble fovy=16.0,
        GLdouble zNear=0.5,
        GLdouble zFar =100.0f)
  {
     //Set a proportional perspective.
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     int w = width();
     int h = height();
     if (h > 0) {
       GLdouble aspect = (GLdouble)w / (GLdouble)h;
       gluPerspective(fovy, aspect, zNear, zFar);
     }
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
  }

};

}


