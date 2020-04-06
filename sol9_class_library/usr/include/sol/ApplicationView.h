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
 *  ApplicationView.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/13
// 2008/09/16 Added Profile instance variable to store user's application setting
// such as a window's geomery, a file folder selected in FileDialog.
//  Two methods saveFileFolder/restoreFileFolder, and modified savePlacement and restorePlacement
// methods not to take any arguments.
// 2017/01/29 Updated Constructor to use the following XmNclassName:
//         .set(XmNclassName, _T("ApplicationView") )), //2017/01/29

#pragma once

#include <sol\Application.h>
#include <sol\Composite.h>
#include <sol\MenuBar.h>
#include <sol\Accelerator.h>
#include <sol\ToolBar.h>
#include <sol\StatusBar.h>
#include <sol\DefaultLayout.h>
//2008/09/16
#include <sol\Profile.h>

//2009/10/08
#include <sol/AppEntry.h>



/**
 * ApplicationView class.
 */
namespace SOL {

class ApplicationView :public Composite {
private:
  Application&   application;
  MenuBar*       menuBar;
  Accelerator*   accel;
  ToolBar*    toolBar;
  StatusBar*    statusBar;
  DefaultLayout*  defaultLayout;
  //2008/09/16
  Profile      profile;

protected:
//    virtual long size(Event& event);
  virtual long size(Event& event)
  {
    int  w, h;
    event.getSize(w, h);

    int  top = 0;
    if (toolBar) {
      toolBar -> send(event.getMessage(), 
      event.getWParam(), event.getLParam());
      top = toolBar -> getHeight();
    }

    if(statusBar) {
      statusBar -> send(event.getMessage(),
      event.getWParam(), event.getLParam());
      h = h - top - statusBar -> getHeight();
    }
    justifyScrollRange();
    layout(0, top, w, h);
    return 0L;
  }


public:
  //2017/03/10
  ApplicationView(Application& applet)
  :Composite(NULL),
  application(applet),
    menuBar(NULL),
    accel(NULL),
    toolBar(NULL),
    statusBar(NULL),
    defaultLayout(NULL)
  {
  }
  
public:
  ApplicationView(Application& applet, const TCHAR* name,
        Args& args)
  :Composite(NULL, name,
    args.set(XmNx,      (LONG_PTR)CW_USEDEFAULT)
        .set(XmNy,      (LONG_PTR)CW_USEDEFAULT)
        .set(XmNwidth,  (LONG_PTR)CW_USEDEFAULT)
        .set(XmNheight, (LONG_PTR)CW_USEDEFAULT)
        .set(XmNstyle,  (LONG_PTR)WS_OVERLAPPEDWINDOW)
      //  .set(XmNpredefined,  False)
        .set(XmNclassName, _T("ApplicationView") )), //2017/01/29
    application(applet),
    menuBar(NULL),
    accel(NULL),
    toolBar(NULL),
    statusBar(NULL),
    defaultLayout(NULL)
  {
    defaultLayout = new DefaultLayout();
    setLayout(defaultLayout);
    applet.setToplevel(this);

    LONG_PTR val;
    const TCHAR* menuName = name;
    if (args.get(XmNmenuName, &val)) {
      menuName = (const TCHAR*)val;
    }
    menuBar = new MenuBar(this, menuName);

    const TCHAR* accelName = name;
    if (args.get(XmNacceleratorName, &val)) {
      accelName = (const TCHAR*)val;
    }
    accel   = new Accelerator(accelName);

    Args ar;
    if (args.get(XmNdefaultToolBar)) {
      LONG_PTR id = args.get(XmNtoolBarBitmapID);
      ar.set(XmNtoolBarBitmapID,  id);
      toolBar = new ToolBar(this, _T(""), ar);
    }
    if(args.get(XmNdefaultStatusBar)) {
      ar.reset();
      statusBar = new StatusBar(this, _T(""), ar);  
    }

    //<added date="2009/09/08">
    const TCHAR* iconName = name;
    if (args.get(XmNiconName, &val)) {
      iconName = (const TCHAR*)val;
    }
    int iconId = 0;
    if (args.get(XmNiconId, &val)) {
      iconId = (int)val;
    }
    
    if (setIcon(iconName) == false) {
      setIcon(iconId);
    }
    //addEventHandler(WM_ERASEBKGND, this, (Handler)&ApplicationView::erase, NULL);

  }

public:
  ~ApplicationView() 
  { 
    // Don't delete the application
    delete defaultLayout;
    delete accel;  
    delete menuBar; 
    delete toolBar;
    delete statusBar;
  }
  
public:
  // For compatibility Oz++ class library on Motif.
  void  realize()
  {
    int cmdShow = SW_SHOWNORMAL;
  
    cmdShow = application.getShowCommand();
    show(cmdShow);
    //2017/03/22
    raise();
    setFocus();
  }

 void  realize(int cmdShow)
  {
    //int cmdShow = SW_SHOWNORMAL;
  
    //cmdShow = application.getShowCommand();
    show(cmdShow);
  }
  
public:
  Boolean  translate(MSG* msg)
  {
    HACCEL haccel = NULL;
    if(accel) haccel = accel->get();
    if(haccel && ::TranslateAccelerator(getWindow(), haccel, msg)) {
      return TRUE;
    } else {
      return FALSE;
    }
  }

public:
  virtual long erase(Event& ev)
  {
    return TRUE;
  }

public:
  void getClientRect(RECT* r)
  {
    View::getClientRect(r);
    if(toolBar) {
      RECT rt;
      toolBar -> getClientRect(&rt);
      r->top = (rt.bottom - rt.top);      
    }
    if(statusBar) {
      RECT rs;
      statusBar -> getClientRect(&rs);
      r->bottom -= (rs.bottom - rs.top);      
    }
  }

public:
  int  showMessageDialog(const TCHAR* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }

    TCHAR path[_MAX_PATH];
    ::GetModuleFileName(NULL, path, _MAX_PATH);
    Folder folder(path);
    String progname = _T("");
    folder.getName(progname);
    int rc = ::MessageBox(getWindow(), message, (const TCHAR*)progname, flag);
    return rc;
  }
// 2009/10/19
public:
  int showMessageDialog(const wchar_t* title, const wchar_t* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxW(getWindow(), message, title,  flag);
  }


public:
  int showErrorDialog(const wchar_t* title, const wchar_t* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxW(getWindow(), message, title, MB_ICONERROR|flag);
  }

public:
  int showInformationDialog(const wchar_t* title, const wchar_t* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxW(getWindow(), message, title, MB_ICONINFORMATION|flag);
  }

public:
  int showQuestionDialog(const wchar_t* title, const wchar_t* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxW(getWindow(), message, title, MB_ICONQUESTION|flag);  
  }

// 2009/10/19
public:
  int showMessageDialog(const char* title, const char* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxA(getWindow(), message, title,  flag);
  }


public:
  int showErrorDialog(const char* title, const char* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxA(getWindow(), message, title, MB_ICONERROR|flag);
  }

public:
  int showInformationDialog(const char* title, const char* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxA(getWindow(), message, title, MB_ICONINFORMATION|flag);
  }

public:
  int showQuestionDialog(const char* title, const char* message, int flag = MB_OK)
  {
    if(isIconic()) {
      show(SW_NORMAL);
    }
    return ::MessageBoxA(getWindow(), message, title, MB_ICONQUESTION|flag);  
  }


  //
public:
  // 1996.12.01 to-arai
  void wait(LONG interval) 
  {
    DWORD startedTime = ::GetTickCount();
    while(::GetTickCount() - startedTime < (DWORD)interval){
      MSG msg;
      if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }
    }
  }


public:
  void restorePlacement()
  {
    //Profile profile(name);
    WINDOWPLACEMENT pl;
    memset(&pl, 0, sizeof(pl));
    pl.length = sizeof(pl); 

    int x, y, w, h;
    profile.getGeometry(&x, &y, &w, &h);

    RECT r;
    r.left     = x;
    r.right    = x+ w;
    r.top      = y;
    r.bottom   = y+h;
    pl.showCmd = SW_SHOWNORMAL; 
    pl.rcNormalPosition = r;

    if(x > 0 && y > 0) {
      setPlacement(&pl);
    }
  }

public:
  void savePlacement()
  {
    //Profile profile(name);
    WINDOWPLACEMENT pl;

    //  memset(&pl, 0, sizeof(pl));
    pl.length = sizeof(pl); 

    getPlacement(&pl);
    RECT r = pl.rcNormalPosition;
    profile.setGeometry(&r);
  }

public:
  bool restoreFileFolder(TCHAR* folder, size_t size)
  {
    bool rc = false;
    if (folder != NULL && size >0) {
      rc = profile.getFileFolder(folder, (UINT)size);
    }
    return rc;
  }

public:
  bool saveFileFolder(const TCHAR* filePath)
  {
    bool rc = false;
    if (filePath != NULL && strlen(filePath)>0) {
    
      Folder folder(filePath);
      String dirOnly = _T("");
    
      folder.getDirectory(dirOnly);
      const TCHAR* dir = (const TCHAR*)dirOnly;
      if (dir) {
        rc = profile.setFileFolder(dir);
      }
    }
    return rc;
  }


  void    exit(Action& action) {
    //2009/10/14
    savePlacement();
      post(WM_CLOSE, 0, 0L);
  }


  StatusBar* getStatusBar() { return statusBar; }

  StatusBar& getStatusBarRef() { return *statusBar; }

  ToolBar*   getToolBar() { return toolBar; }
  ToolBar&   getToolBarRef() { return *toolBar; }

  MenuBar*  getMenuBar()  { return menuBar; }

  BOOL  isIconic() { return ::IsIconic(getWindow()); }

  BOOL  isZoomed() { return ::IsZoomed(getWindow()); }

//  void  realize();

  void  setToolBar(ToolBar* bar)   { toolBar = bar; }
  void  setStatusBar(StatusBar* bar) { statusBar = bar; }


  Profile& getProfile() { return profile; }

public:
  //2009/11/16
  void  waitForThread(HANDLE hThread){
    HANDLE handle[1];
    handle[0] = hThread;

    bool looping = true;    
    while (looping)  { 
    
      if (MsgWaitForMultipleObjects(1, handle, FALSE,   
        INFINITE, QS_ALLINPUT|QS_ALLEVENTS) == WAIT_OBJECT_0+1 ) {
        MSG msg;

        while(PeekMessage (&msg,NULL,0,0,PM_REMOVE)) {
          SleepEx(0, TRUE);
          if (msg.message == WM_QUIT) {
            //Repost WM_QUIT message to your application message queue.
            PostMessage(NULL, WM_QUIT, 0, 0);
            looping = false;
            break;
          }  
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }

      }else {
        break;   
      }
    }
  }

public:
  //2012/04/07
  String getModuleDirectory()
  {
    const int size = 1024;
    wchar_t base[size];
    memset(base, (wchar_t)0, size);
    GetModuleFileNameW(NULL, base, size);
    wchar_t* sl = strrchr(base, L'\\');
    if (sl) {
      *sl = NULL;
    }

    return String(base);
  }
  
};

}


