/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WindowAttributes.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/13

#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <sol/Arg.h>
#include <sol/StringBuffer.h>

namespace SOL {

class WindowAttributes :public Object {

private:
  HWND   hwnd;

  char   className[MAX_PATH];

  HINSTANCE hInstance;

  HWND  hParent;

  DWORD  windowID;  

  WINDOWPLACEMENT placement;

  WINDOWINFO windowInfo;
  
  char  windowText[MAX_PATH];

  DWORD  processID;

  DWORD  threadID;

  BOOL isWindowUnicode;

  BOOL isIconic;

  BOOL isZoomed;

  BOOL isVisible;

public:
  /**
   * Constructor
   */
  WindowAttributes()
  {
    initialize();
  }

public:
  /**
   * Constructor
   */
  WindowAttributes(HWND hwnd)
  {
    getAttributes(hwnd);
  }

private:
  void initialize()
  {
    hwnd = NULL;
    hParent = NULL;
    hInstance = NULL,
    windowID = 0,

    memset(className, 0, sizeof(className));
    memset(windowText,  0, sizeof(windowText));

    memset(&placement, 0, sizeof(placement));

    memset(&windowInfo, 0, sizeof(windowInfo));

    processID = 0;

    threadID = 0;

    isWindowUnicode = FALSE;

    isIconic = FALSE;

    isZoomed = FALSE;

    isVisible = FALSE;
  }


public:
  bool getAttributes(HWND hWnd)
  {
    bool rc = false;

    initialize();

    if (hWnd == NULL) {
      return rc;
    }

    if (!IsWindow(hWnd)) {
      return rc;
    }

    this->hwnd = hWnd;    

    try {
      GetClassName(hwnd, className, sizeof(className)-1);
    
      hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
      hParent   = (HWND)GetWindowLong(hwnd, GWL_HWNDPARENT);
      windowID   = GetWindowLong(hwnd, GWL_ID);

      GetWindowText(hwnd, windowText,sizeof(windowText)-1);

      placement.length = sizeof(placement);
      GetWindowPlacement(hwnd, &placement);

      threadID = GetWindowThreadProcessId(hwnd, &processID);

      windowInfo.cbSize = sizeof(windowInfo);

      GetWindowInfo(hwnd, &windowInfo);
  
      isWindowUnicode = IsWindowUnicode(hwnd);
    
      isIconic = IsIconic(hwnd);

      isZoomed = IsZoomed(hwnd);

      isVisible = IsWindowVisible(hwnd);
    
      rc = true;
    } catch (...) {

    }
    return rc;
  }

public:
  HWND getWindow() 
  {
    return hwnd;
  }

public:
  const char* getClassName() 
  {
    return className;
  }

public:
  HINSTANCE getInstance()
  {
    return hInstance;
  }

public:
  HWND  getParent() 
  {
    return hParent;
  }

public:
  DWORD  getWindowID() 
  {
    return windowID;  
  }

public:
  WINDOWPLACEMENT& getPlacement()
  {
    return placement;
  }

public:
  WINDOWINFO& getWindowInfo()
  {
    return windowInfo;
  }
  
public:
  const char* getWindowText()
  {
    return windowText;
  }

public:
  DWORD  getProcessID()
  {
    return processID;
  }
  
public:
  DWORD  getThreadID()
  {
    return threadID;
  }

public:
  BOOL getIsWindowUnicode() 
  {
    return isWindowUnicode;
  }

public:
  BOOL getIsIconic() 
  {
    return isIconic;
  }

public:
  BOOL getIsZoomed() 
  {
    return isZoomed;
  }

public:
  BOOL getIsVisible() 
  {
    return isVisible;
  }

public:
  virtual void display(HWND hwndToDisplay)
  {
    //Please implement this method in a subclass of this class.
  }

public:
  void dump()
  {
    printf("ClassName=%s\n", className);

    printf("hParent = 0x%08x\n", hParent);

    printf("hWnd   = 0x%08x\n", hwnd);

    printf("WindowID = 0x%08x\n", windowID);

    StringBuffer style;
    getStyle(windowInfo.dwStyle, style);
  
    printf("Style = %s\n", (const char*)style);
  
    StringBuffer exBuffer;
    getExStyle(windowInfo.dwExStyle, exBuffer);

    printf("ExStyle = %s\n", (const char*)exBuffer);

    printf("WindowText = %s\n", windowText);

    printf("hInstance = 0x%08x\n", hInstance);

    printf("ProcessID = 0x%08x\n", processID);

    printf("ThreadID = 0x%x\n", threadID);

    printf("IsWindowUnicode = %s\n", toString(isWindowUnicode));

    
    printf("IsIconic = %s\n", toString(isIconic));

    printf("IsZoomed = %s\n", toString(isZoomed));

    printf("IsVisible = %s \n", toString(isVisible));

    RECT r = windowInfo.rcWindow; 
    printf("WindowRect x=%d y= %d width=%d height=%d\n", 
      r.left, r.top, r.right-r.left, r.bottom - r.top);

    r = windowInfo.rcClient; 
    printf("ClientRect x=%d y= %d width=%d height=%d\n", 
      r.left, r.top, r.right-r.left, r.bottom - r.top);


    if (windowInfo.dwWindowStatus == 1) {
      printf("Status Active\n"); 
    } else {
      printf("Status NonActive\n"); 
    }
    printf("BorderWidth =%d\n", windowInfo.cxWindowBorders);

    printf("BorderHeight =%d\n", windowInfo.cyWindowBorders);
    
    //ATOM  atomWindowType;
    printf("CreatorVersion = %d\n", windowInfo.wCreatorVersion);

     printf("Placement Flags = %d\n", placement.flags);
    if (placement.flags == WPF_SETMINPOSITION) {
      printf("WPF_SETMINPOSITION\n");
    }

    if (placement.flags == WPF_RESTORETOMAXIMIZED) {
      printf("WPF_RESTORETOMAXIMIZED\n");
    }   

    printf("Placemnent ShowCmd = %s\n", getShowCmd(placement.showCmd));

    POINT ptMin = placement.ptMinPosition;
    printf("Placement MinPosition x=%d y=%d\n", ptMin.x, ptMin.y);

       POINT ptMax = placement.ptMaxPosition;
    printf("Placement MaxPosition x=%d y=%d\n", ptMax.x, ptMax.y);

       r = placement.rcNormalPosition;

    printf("Placement NormalPosition x=%d y= %d width=%d height=%d\n", 
      r.left, r.top, r.right-r.left, r.bottom - r.top);
  }

protected:
  const char* toString(BOOL flag)
  {
    static const Arg bools[] = {
      {"TRUE", TRUE},
      {"FALSE", FALSE},};

    int count = sizeof(bools)/sizeof(bools[0]);

    const char* string = "";
    for (int i = 0; i<count; i++) {
      if (bools[i].value == flag) {
        string = bools[i].name;
        break;
      }
    }
    return string;
  }

protected:
  virtual int getStyle(DWORD style, StringBuffer& buffer)
  {  
    static const Arg styles[] = {
    {"WS_OVERLAPPED",  WS_OVERLAPPED},//
    {"WS_POPUP",    WS_POPUP},
    {"WS_CHILD",    WS_CHILD},
    {"WS_MINIMIZE",    WS_MINIMIZE}, 
    {"WS_VISIBLE",    WS_VISIBLE},
    {"WS_DISABLED",    WS_DISABLED},
    {"WS_CLIPSIBLINGS",  WS_CLIPSIBLINGS},
    {"WS_CLIPCHILDREN",  WS_CLIPCHILDREN},
    {"WS_CAPTION",    WS_CAPTION},
    {"WS_BORDER",    WS_BORDER},
    {"WS_DLGFRAME",    WS_DLGFRAME},
    {"WS_VSCROLL",    WS_VSCROLL},
    {"WS_HSCROLL",    WS_HSCROLL},
    {"WS_SYSMENU",    WS_SYSMENU},
    {"WS_SIZEBOX",    WS_SIZEBOX},
    {"WS_GROUP",    WS_GROUP},
    {"WS_TABSTOP",    WS_TABSTOP},
    {"WS_MINIMIZEBOX",  WS_MINIMIZEBOX},
    {"WS_MAXIMIZEBOX",  WS_MAXIMIZEBOX},
    };

    int count = sizeof(styles)/sizeof(styles[0]);
    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (styles[i].value & style) {
        if (matched>0) {
          buffer.append(" ");
        }
        buffer.append(styles[i].name);
        matched++;
      }
    }
    return matched;
  }

protected:
  virtual int getExStyle(DWORD style, StringBuffer& buffer)
  {
    static const Arg styles[] = {
    {"WS_EX_ACCEPTFILES",    WS_EX_ACCEPTFILES}, 
    {"WS_EX_APPWINDOW",      WS_EX_APPWINDOW},
    {"WS_EX_CLIENTEDGE",    WS_EX_CLIENTEDGE},
    {"WS_EX_CONTEXTHELP",    WS_EX_CONTEXTHELP}, 
    {"WS_EX_CONTROLPARENT",    WS_EX_CONTROLPARENT},
    {"WS_EX_DLGMODALFRAME",    WS_EX_DLGMODALFRAME},
    {"WS_EX_LAYERED",      WS_EX_LAYERED},
    {"WS_EX_LAYOUTRTL",      WS_EX_LAYOUTRTL},
    {"WS_EX_LEFT",        WS_EX_LEFT},
    {"WS_EX_LEFTSCROLLBAR",    WS_EX_LEFTSCROLLBAR},
    {"WS_EX_LTRREADING",    WS_EX_LTRREADING},
    {"WS_EX_MDICHILD",      WS_EX_MDICHILD},
    {"WS_EX_NOACTIVATE",    WS_EX_NOACTIVATE}, 
    {"WS_EX_NOINHERITLAYOUT",  WS_EX_NOINHERITLAYOUT},
    {"WS_EX_NOPARENTNOTIFY",  WS_EX_NOPARENTNOTIFY},
    {"WS_EX_RIGHT",        WS_EX_RIGHT},
    {"WS_EX_RIGHTSCROLLBAR",  WS_EX_RIGHTSCROLLBAR},
    {"WS_EX_RTLREADING",    WS_EX_RTLREADING},
    {"WS_EX_STATICEDGE",    WS_EX_STATICEDGE}, 
    {"WS_EX_TOOLWINDOW",    WS_EX_TOOLWINDOW},
    {"WS_EX_TOPMOST",      WS_EX_TOPMOST},
    {"WS_EX_TRANSPARENT",    WS_EX_TRANSPARENT},
    {"WS_EX_WINDOWEDGE",    WS_EX_WINDOWEDGE},
    };

    int count = sizeof(styles)/sizeof(styles[0]);

    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (styles[i].value & style) {
        if (matched>0) {
          buffer.append(" ");
        }
        buffer.append(styles[i].name);
        matched++;
      }
    }
    return matched;
  }

protected:
  const char* getShowCmd(DWORD cmd)
  {
    static const Arg showCmd[] = {
    {"Hide",      SW_HIDE},
    {"Minimize",    SW_MINIMIZE},
    {"Restore",      SW_RESTORE},
    {"Show",      SW_SHOW},   
    {"ShowMaximized",   SW_SHOWMAXIMIZED},
    {"ShowMinimized",   SW_SHOWMINIMIZED},   
    {"ShowMinNoActive",   SW_SHOWMINNOACTIVE},
    {"ShowNA",      SW_SHOWNA},   
    {"ShowNoActive",  SW_SHOWNOACTIVATE},
    {"ShowNormal",    SW_SHOWNORMAL}
    };

    char* name = "";
       int count = sizeof(showCmd)/sizeof(showCmd[0]);
  
    for (int i = 0; i<count; i++) {
      if (showCmd[i].value == cmd) {
        name = (char*)showCmd[i].name;
        break;
      }
    }
    return name;
  }
};

}
