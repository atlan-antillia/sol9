/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenCVApplicationView.h
 *
 *****************************************************************************/

// 2017/03/15

#pragma once

#include <sol/ClientDC.h>
#include <sol/PaintDC.h>
#include <sol/String.h>
#include <sol/Stdio.h>
#include <sol/ApplicationView.h>

#include <sol/opencv/OpenCVApplication.h>

namespace SOL {

#define WM_INITIALIZE_OPENCV_MAINVIEW (WM_USER+2022)

class OpenCVApplicationView :public ApplicationView {
  //Default MENU_IDs
public:
  typedef enum {
    IDM_NEW  =100,
    IDM_OPEN,     //101
    IDM_SAVE,     //102
    IDM_SAVEAS,   //103
  } FILE_MENU;
  
  typedef enum {
  IDM_HELP = 200,
  } HELP_MENU;
  
  //
  static const int IDM_EXIT    = 2015;
  static const int IDM_VERSION = 2016;
  
public:
  String appName;
  
public:
  long eraseBackground(Event& event)
  {
    WPARAM wParam = event.getWParam();
    
    HWND hwnd = getWindow();
    RECT rc;
    GetClientRect(hwnd, &rc); 

    FillRect((HDC)wParam, &rc, (HBRUSH)GetStockObject(COLOR_BTNFACE)); 
    return 1L;    
  }
  
private:
  long init(Event& event)
  {
    initialize();
    return 1L;
  }

//2017/12/01
/*
  long activate(Event& event)
  {

    WPARAM wParam = event.getWParam();
    HWND   hwnd = (HWND)event.getLParam();
    int fActive    =  wParam & 0xFFFF;
    if (fActive == 0) {
      
    }
    if (fActive > 0) {
      ::SetActiveWindow(hwnd);
      ::EnableWindow(hwnd, TRUE);

      return 0; //1L;
    }
    
    return defaultProc(event);
  }
*/
  virtual void initialize()
  {
  }
  
  long paint(Event& event)
  {
    PaintDC dc(this);
    {
    //Call a virtual display method.
      display();
    }
    return 1L;
  }
  
  virtual void display()
  {
  }
  
  long size(Event& event)
  {
    int width = 0;
    int height = 0;
    event.getSize(width, height);
    //Call a virtual resize method.
    if (width > 0 && height > 0) {
      resize(width, height);
    }
    return 1L;
  }

  
  //Please define your own resize method in subclass derived form this class.
  virtual void resize(int w, int h)
  {
  }

  void validateClientSize(int& width, int& height)
  {
    static const int MIN_WIDTH = 8;
    getClientSize(width, height);
    if (width < MIN_WIDTH ) {
      width = MIN_WIDTH;
    }
    if ( height < MIN_WIDTH) {
      height = MIN_WIDTH;
    }
  }
  
  virtual long getMinMaxInfo(Event& event)
  {
    MINMAXINFO* info = (MINMAXINFO*)event.getLParam();
    static const int MIN_WIDTH  = 200;
    static const int MIN_HEIGHT = 200;
    
    info -> ptMinTrackSize.x = MIN_WIDTH;
    info -> ptMinTrackSize.y = MIN_HEIGHT;

    return 0;
  }

  //Default menuCallback for IDM_VERSION
  //Define your own method in a subclass derived from this class.
  virtual void version(Action& action)
  {
     char message[1024];
    sprintf_s(message, CountOf(message), "Major Version: %d  Minor Version: %d  SubMinor_Version: %d",
      CV_MAJOR_VERSION,
      CV_MINOR_VERSION,
      CV_SUBMINOR_VERSION);
     // CV_VERSION

    showMessageDialog("OpenCV Version", message, MB_ICONINFORMATION|MB_OK);
   
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
    showMessageDialog("Help", "Copyright (c) 2017 Antillia.com  ALL RIGHTS RESERVED.", MB_ICONINFORMATION|MB_OK);
  }

  //2017/04/22
  long dropFiles(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();

    //Call XmNdropCallback 
    callCallback(XmNdropCallback, (Key)hwnd, NULL, event);    
 
    event.handled();
    
    return 1;
  }

public:
  //Constructor
  //2017/04/10 Updated
  OpenCVApplicationView(OpenCVApplication& applet, const TCHAR* caption, Args& args)
  :ApplicationView(applet, caption, 
          args.set(XmNclassName, _T("OpenCVApplicationView")) 
          .set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
          .set(XmNexStyle, (LONG_PTR)WS_EX_CONTROLPARENT)
          .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW)
          .set(XmNstyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN) )
  {
    appName = applet.getName();
    
     //Default File menu calllbacks for IDM_EXIT and IDM_VERSION
    addCallback(XmNmenuCallback, IDM_NEW, this,
      (Callback)&OpenCVApplicationView::clear, NULL);
    addCallback(XmNmenuCallback, IDM_OPEN, this,
      (Callback)&OpenCVApplicationView::open, NULL);
    addCallback(XmNmenuCallback, IDM_SAVE, this,
      (Callback)&OpenCVApplicationView::save, NULL);
    addCallback(XmNmenuCallback, IDM_SAVEAS, this,
      (Callback)&OpenCVApplicationView::saveAs, NULL);
    addCallback(XmNmenuCallback, IDM_EXIT, this,
      (Callback)&OpenCVApplicationView::exit, NULL);

    addCallback(XmNmenuCallback, IDM_HELP, this,
      (Callback)&OpenCVApplicationView::help, NULL);

    addCallback(XmNmenuCallback, IDM_VERSION, this,
      (Callback)&OpenCVApplicationView::version, NULL);
    
    addEventHandler(WM_INITIALIZE_OPENCV_MAINVIEW, this,
                    (Handler)&OpenCVApplicationView::init, NULL);
 //2017/12/01
 //   addEventHandler(WM_ACTIVATE, this,
 //                   (Handler)&OpenCVApplicationView::activate, NULL);

    //2017.04.10    
 //   addEventHandler(WM_ERASEBKGND, this,
 //                   (Handler)&OpenCVApplicationView::eraseBackground, NULL);
    
    addEventHandler(WM_PAINT, this,
                    (Handler)&OpenCVApplicationView::paint, NULL);
 
    addEventHandler(WM_GETMINMAXINFO, this,
                    (Handler)&OpenCVApplicationView::getMinMaxInfo, NULL);
    addEventHandler(WM_SIZE, this,
                    (Handler)&OpenCVApplicationView::size, NULL);

    //2 DropFiles event hanlder.    
  //  addEventHandler(WM_DROPFILES, this, 
  //    (Handler)&OpenCVApplicationView::dropFiles, NULL);

    post(WM_INITIALIZE_OPENCV_MAINVIEW);
  }


  ~OpenCVApplicationView()
  {
  }
  
  const char* getAppName()
  {
    return (const char*)appName;
  }
};

}


