/******************************************************************************
 *
 * Copyright (c) 2009-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  AppEntry.h
 *
 *****************************************************************************/

//SOL9
// 2009/11/04 Modified to define AppEntry c++ class and use it in _tWinMain. 
// 2012/04/10 Updated.
#pragma once

#include <sol\Application.h>
#include <sol\CommandLine.h>
//2012/04/10
#include <sol\gdiplus\GdiplusInitializer.h>

#define _MAX_ARG  100

#include <tchar.h>
//2009/11/04
#include <vfw.h>
#pragma comment(lib, "vfw32.lib")

namespace SOL {

class AppEntry {

private:
  HINSTANCE  richEdit;

public:
  AppEntry(HINSTANCE progIns)
  :richEdit(NULL)
  {
    //1 Load RichEdit dll
    richEdit = ::LoadLibrary(_T("RICHED32.DLL"));

    //2 Initialize CommonControl
    InitCommonControls();  
    
    INITCOMMONCONTROLSEX ic;
    memset(&ic, 0, sizeof(ic));
    ic.dwSize = sizeof(ic);
    ic.dwICC  =
    ICC_LISTVIEW_CLASSES| // listview, header
    ICC_TREEVIEW_CLASSES| // treeview, tooltips
    ICC_BAR_CLASSES     | // toolbar, statusbar, trackbar, tooltips
    ICC_TAB_CLASSES     | // tab, tooltips
    ICC_UPDOWN_CLASS    | // updown
    ICC_PROGRESS_CLASS  | // progress
    ICC_HOTKEY_CLASS    | // hotkey
    ICC_ANIMATE_CLASS   | // animate
    ICC_WIN95_CLASSES   | 
    ICC_DATE_CLASSES    | // month picker, date picker, time picker, updown
    ICC_USEREX_CLASSES  | // comboex
    ICC_INTERNET_CLASSES| // IP address field  1999.08.14
    ICC_COOL_CLASSES  |     // rebar (coolbar) control
    ICC_PAGESCROLLER_CLASS|   // PageScroller 
    ICC_NATIVEFNTCTL_CLASS|   //   NativeFon
    ICC_STANDARD_CLASSES|     //   Standard  
    ICC_LINK_CLASS;      //Link

    //3 Initialize Extended CommonControl

    InitCommonControlsEx(&ic);  

    // For socket library
    WSADATA wsaData;
    //4 Initialize Socket module
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
      MessageBox(NULL, _T("Could not load Windows Sockets DLL."), 
          _T("SOL9"), MB_OK|MB_ICONSTOP);
    }      
    //4 Initialize(register) MCI(Media Control Interface) window class
    MCIWndRegisterClass(); //
  }
public:
  ~AppEntry()
  {
    FreeLibrary(richEdit);
    WSACleanup();
  }
};

}

//////////////////////////////////////////////////////////
//
// WinMain
#ifdef _CONSOLE_

#else 
int WINAPI _tWinMain(HINSTANCE progIns, HINSTANCE prevIns, 
      LPTSTR cmdLine, int cmdShow)
{
  AppEntry appEntry(progIns);
  {
    int argc = 0;
    TCHAR* argv[_MAX_ARG];
    TCHAR module[_MAX_PATH];
    CommandLine commandLine(cmdLine);

    GetModuleFileName(progIns, module, CountOf(module));
    argv[argc++] = module;
    argc +=  commandLine.getArgv(&argv[argc], _MAX_ARG);

    //2012/04/10    
    GdiplusInitializer initializer;
    {
      //Call Main function of SOL9 Windows Application
      Main(argc, argv);
    }
  }

  return TRUE;
}

#endif

//void  Main(int argc, TCHAR** argv);
