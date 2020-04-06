/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Application.h
 *
 *****************************************************************************/

// SOL++2000
// 2001/04/01 Added a static variable DEFAULT_WIN_CLASS_STYLE
// SOL9 2009/10/08
// 2009/11/04 Modified to use Application.h file.
//  Some methods have been moved to AppEntry class and View class.


#pragma once

#include <sol\Object.h>
#include <sol\Args.h>
#include <sol\HashTable.h>
#include <tchar.h>
#include <sol/Window.h>
#include <sol/ModuleFileName.h>  //2017/01/27

namespace SOL {


/**
 * Application class.
 */
class Application :public Object {
private:
  const TCHAR* name;
  HINSTANCE  instance;
  HINSTANCE  prevInstance;
  HashTable* table;
  LPTSTR  cmdLine;
  int    cmdShow;
  int    argc;
  TCHAR**  argv;
  //Composite* toplevel; 2009/11/04
  Window* toplevel;

private:
  Application()
  {
    //
    MessageBox(NULL, _T("Cannot create an instances for Application class"),
      _T("SOL9"), MB_ICONERROR|MB_OK);
    throw -1;
  }

public:
  /**
   * Contructor
   */
  Application(const TCHAR* name1, int argc1, TCHAR** argv1)
  {
    name   = name1;
    argc   = argc1;
    argv   = argv1;
    table    = new HashTable(113);
    toplevel = NULL;
    instance    = GetModuleHandle(NULL);
    prevInstance= NULL;  
    cmdLine   = NULL;
    cmdShow   = SW_SHOWNORMAL;

    //Set this pointer as a singleton by calling getApplet().
    getApplet(this);
  }

public:
  /** 
   * Destructor
   */
  ~Application()
  {
    //Delete HashTable
    if (table) {
      delete table;
      table = NULL;
    }
  }


public:
  /**
   * If parameter applet is not NULL, 
   * then set an instance of Application class apple to static singleton variable
   * else return a reference to singleton variable.
   */
  static Application& getApplet(__in Application* applet=NULL)
  {
    static Application* singleton = NULL;
    if (applet) {
      if (singleton == NULL) {
        singleton = applet;
      } else {
        //If singleton were not NULL, throw -1
        MessageBox(NULL, _T("Cannot create multiple instances for Application class"),
          _T("SOL9"), MB_ICONERROR|MB_OK);
        throw -1;
      }
    }
    return *singleton;
  }

  static void   add(HWND hwnd, class View* view) {
    Application& applet = Application::getApplet(NULL);
    HashTable* table = applet.getTable();
    table -> add((Key)hwnd, (Object*)view);
  }

  static class View*   lookup(HWND hwnd) {
    //Application& applet = getInstance();
    Application& applet = Application::getApplet(NULL);

    HashTable* table = applet.getTable();
    return (View*)table->lookup((Key)hwnd);
  }

  static BOOL   remove(HWND hwnd) {
    //Application& applet = getInstance();
    Application& applet = Application::getApplet(NULL);

    HashTable* table = applet.getTable();
    return  table->remove((Key)hwnd);
  }

  const TCHAR*  getName() { return name; }

  HashTable* getTable() { return table;}

  HINSTANCE  getInstance() { return instance; }

  HINSTANCE  getPrevInstance() { return prevInstance; } 


  int dialogMessage(MSG* msg)
  {
    BOOL rc = FALSE;

    HWND parent = ::GetParent(msg->hwnd);
    if(parent == NULL) {
      return FALSE;
    }
  
    DWORD style = ::GetWindowLong(parent, GWL_STYLE);
    DWORD exStyle = ::GetWindowLong(parent, GWL_EXSTYLE);
    
    if(((style & WS_POPUP) || (exStyle & WS_EX_CONTROLPARENT )) && 
      ::IsDialogMessage(parent, msg) == TRUE) {

      if(msg->message == WM_KEYDOWN && 
        msg->wParam  == VK_RETURN) {
        if(exStyle & WS_EX_CONTROLPARENT){
          ::DispatchMessage(msg);
        }  
        if(style & WS_POPUP) {
          msg->lParam  = (LPARAM)msg->hwnd;
          msg->message = WM_COMMAND;
          ::DispatchMessage(msg);
        }
      }
      rc = TRUE;
    }
    return rc;
  }

public:
  // Typical message loop
  WPARAM run()
  {
    int rc = 0;

    MSG  msg;
    // 2009/09/03
    while ((rc = GetMessage(&msg, NULL, 0, 0)) !=0) {
      if (rc == -1) {
        //Something error has happened, so break this loop
        break;
      }
      if(dialogMessage(&msg)) {
        continue;
      }
      
      if(toplevel && toplevel->translate(&msg)) {
        continue;
      }
     
      TranslateMessage(&msg);
      //2011/02/23 Added the following 3 lines
      if ( msg.message == WM_KEYDOWN ) {
        toplevel->send(msg.message, msg.wParam, msg.lParam); 
      }

      DispatchMessage(&msg);
    }
    return msg.wParam;
  }

  void run(Window* window)
  {
      // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ) {
      if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )  {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      }
      else {
        if (window) {
        //Call a virtual render method of Window.
          window -> render();
        }
      }
    }
  }
  
  void  setToplevel(class Composite* appview) {
      toplevel = (Window*)appview;
  }

  LPTSTR  getCommandLine() { return cmdLine; }

  int    getShowCommand() { return cmdShow; }
};

}

void  Main(int argc, TCHAR** argv);
