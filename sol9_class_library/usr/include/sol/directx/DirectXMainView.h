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
 *  DirectXMainView.h
 *
 *****************************************************************************/

// 2015/10/01

#pragma once

#include <sol/ApplicationView.h>
#include <sol/String.h>
#include <sol/Stdio.h>
#include <sol/wic/WICImagingFactory.h>
#include <sol/directx/Direct2D1Factory.h>
#include <sol/directx/DirectWriteFactory.h>

namespace SOL {

class DirectXMainView :public ApplicationView {
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
  StringT<TCHAR> appName;

  WICImagingFactory*  imagingFactory;
  Direct2D1Factory*   d2d1Factory;
  DirectWriteFactory* writeFactory;
  
public:
  //Default menuCallback for IDM_VERSION
  //Define your own method in a subclass derived from this class.
  virtual void version(Action& action)
  {
    TCHAR message[256];
    _stprintf_s(message, CountOf(message), _T("%s \r\n Copyright(c) 2015 Antillia.com"), (const TCHAR*)appName);
 
    showMessageDialog(_T("Version"), message, MB_ICONINFORMATION|MB_OK);
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
  WICImagingFactory* getImagingFactory()
  {
    return imagingFactory;
  }

  Direct2D1Factory* getD2D1Factory()
  {
    return d2d1Factory;
  }
  
  DirectWriteFactory* getWriteFactory()
  {
    return writeFactory;
  }
  
  const TCHAR* getAppName()
  {
    return (const TCHAR*)appName;
  }
  
public:
  //Constructor
  DirectXMainView(Application& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, args.set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
  
  imagingFactory(NULL),
  d2d1Factory(NULL),
  writeFactory(NULL)
  {
    try {
      imagingFactory     = new WICImagingFactory();
      d2d1Factory   = new Direct2D1Factory();
      writeFactory = new DirectWriteFactory();
       
    } catch (Exception& ex) {
      ex.display();
    }

    appName = applet.getName();
    
     //Default File menu calllbacks for IDM_EXIT and IDM_VERSION
    addCallback(XmNmenuCallback, IDM_NEW, this,
      (Callback)&DirectXMainView::clear, NULL);
    addCallback(XmNmenuCallback, IDM_OPEN, this,
      (Callback)&DirectXMainView::open, NULL);
    addCallback(XmNmenuCallback, IDM_SAVE, this,
      (Callback)&DirectXMainView::save, NULL);
    addCallback(XmNmenuCallback, IDM_SAVEAS, this,
      (Callback)&DirectXMainView::saveAs, NULL);
    addCallback(XmNmenuCallback, IDM_EXIT, this,
      (Callback)&DirectXMainView::exit, NULL);

    addCallback(XmNmenuCallback, IDM_HELP, this,
      (Callback)&DirectXMainView::help, NULL);

    addCallback(XmNmenuCallback, IDM_VERSION, this,
      (Callback)&DirectXMainView::version, NULL);
    
  }

  ~DirectXMainView()
  {
    delete imagingFactory;
    delete d2d1Factory;
    delete writeFactory;

  }
};

}


