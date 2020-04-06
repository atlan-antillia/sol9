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
 *  OpenGLMainView.h
 *
 *****************************************************************************/

// 2015/07/22

#pragma once

#include <sol/ApplicationView.h>
#include <sol/String.h>
#include <sol/Stdio.h>
//2016/07/01
#include <GL/glew.h>
#include <GL/wglew.h>

#include <GL/gl.h>
#include <GL/glu.h>

namespace SOL {

class OpenGLMainView :public ApplicationView {
  //Default MENU_IDs
public:
  typedef enum {
    IDM_NEW  =100,
    IDM_OPEN,     //101
    IDM_SAVE,     //102
    IDM_SAVEAS,   //103
  } FILE_MENU;
  
  typedef enum {
  IDM_HELP = 200  
  } HELP_MENU;
  
  //
  static const int IDM_EXIT    = 2015;
  static const int IDM_VERSION = 2016;
  
public:
  String appName;
  
public:
  //Default menuCallback for IDM_VERSION
  //Define your own method in a subclass derived from this class.
  virtual void version(Action& action)
  {
    char message[1024];
    memset(message, 0, sizeof(message));
    const GLubyte *vendor     = glGetString(GL_VENDOR);
    const GLubyte *renderer   = glGetString(GL_RENDERER);
    const GLubyte *version    = glGetString(GL_VERSION);
    const GLubyte *glsl       = glGetString(GL_SHADING_LANGUAGE_VERSION);

    sprintf(message, 
      "%s \r\n Copyright(c) 2016 Antillia.com\n\n" 
      "GL_VENDOR                   :%s\n"
      "GL_RENDERER                 :%s\n"
      "GL_VERSION                  :%s\n"
      "GL_SHADING_LANGUAGE_VERSION :%s\n",
          (const char*)appName,
          (const char*)vendor,
          (const char*)renderer,
          (const char*)version,
          (const char*)glsl
      );

    showMessageDialog("Version", message, MB_ICONINFORMATION|MB_OK);
  }

public:
  //Default virtual menu callbacks.
  //Please define your own callbacks in your subclass derived from this class.
  virtual void clear(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: New", MB_ICONINFORMATION|MB_OK);
  }
  
  virtual void open(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Open", MB_ICONINFORMATION|MB_OK);
  }

  virtual void save(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Save", MB_ICONINFORMATION|MB_OK);
  }

  virtual void saveAs(Action& action)
  {
    showMessageDialog("Menu", "Default enu callack: SaveAs", MB_ICONINFORMATION|MB_OK);
  }
    
  virtual void help(Action& action)
  {
    showMessageDialog("Menu", "Default menu callack: Help", MB_ICONINFORMATION|MB_OK);
  }

public:
  //Constructor
  OpenGLMainView(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN))
  {
    appName = applet.getName();
    
     //Default File menu calllbacks for IDM_EXIT and IDM_VERSION
    addCallback(XmNmenuCallback, IDM_NEW, this,
      (Callback)&OpenGLMainView::clear, NULL);
    addCallback(XmNmenuCallback, IDM_OPEN, this,
      (Callback)&OpenGLMainView::open, NULL);
    addCallback(XmNmenuCallback, IDM_SAVE, this,
      (Callback)&OpenGLMainView::save, NULL);
    addCallback(XmNmenuCallback, IDM_SAVEAS, this,
      (Callback)&OpenGLMainView::saveAs, NULL);
    addCallback(XmNmenuCallback, IDM_EXIT, this,
      (Callback)&OpenGLMainView::exit, NULL);

    addCallback(XmNmenuCallback, IDM_HELP, this,
      (Callback)&OpenGLMainView::help, NULL);

    addCallback(XmNmenuCallback, IDM_VERSION, this,
      (Callback)&OpenGLMainView::version, NULL);
  }

  ~OpenGLMainView()
  {
  }
  
  const char* getAppName()
  {
    return (const char*)appName;
  }
  
  
  //2017/09/10
protected:
  virtual long size(Event& event)
  {
    int  w, h;
    event.getSize(w, h);
    resize(w, h);
    return 1L;
  }
  
  //Define your own resize method in a subclass derived from this class.
  virtual void resize(int w, int h)
  {
  }
  
};

}


