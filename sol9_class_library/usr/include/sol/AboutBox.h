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
 *  AboutBox.h
 *
 *****************************************************************************/

// SOL9 
// 2009/11/15
// This is simple AboutBox class which DOES NOT depend on SOL::View class
// and SOL::Application class.
// This is a resource based Modal DialogBox to show simple about information.

/* 
 {
  AboutBox aboutBox(hparent, _T("MyAboutBox"));
  aboutBox.show();  
 }
 */

#pragma once

#include <windows.h>

namespace SOL  {

class AboutBox {
private:
  HWND  parent;
  HWND  hwnd;
  HINSTANCE hInstance;

  const TCHAR*  dialogTemplate;

/**
// resource.h
#define IDD_ABOUTBOX 1000

// applet.rc
IDD_ABOUTBOX DIALOGEX 0, 0, 218, 62
STYLE DS_SETFONT | DS_MODALFRAME | DS_3DLOOK | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Version Information - SolNetUser"
FONT 9, "Arial", 400, 0, 0x0
BEGIN
    ICON            IDI_SOLNETUSER, IDC_STATIC,14,14,20,20
    LTEXT           "SolNetUser, Version 1,0,0,1",IDC_STATIC,41,14,169,8,SS_NOPREFIX
    LTEXT           "Copyright (C) 2009 Antillia.com",IDC_STATIC,42,26,140,8
    DEFPUSHBUTTON   "OK",IDOK,163,41,47,14,WS_GROUP
END
 */



public:
  /**
   * Constructor
   * @param parent  Parent Window handle
   * @param dialogId  DialogId is an dialog template Id(integer) in a application somthing resourc file(*.rc).
   *   See the above sample
   */
  AboutBox(HWND parent, int dialogId)
  {
    this->parent = parent;

    this->hInstance = GetModuleHandle(NULL);
    //Shallow pointer copy
    this->dialogTemplate = MAKEINTRESOURCE(dialogId);
  }


/*
// applet.rc
SolAboutDialog DIALOGEX 0, 0, 218, 62
STYLE DS_SETFONT | DS_MODALFRAME | DS_3DLOOK | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Version Information - SolNetUser"
FONT 9, "Arial", 400, 0, 0x0
BEGIN
    ICON            IDI_SOLNETUSER, IDC_STATIC,14,14,20,20
    LTEXT           "SolNetUser, Version 1,0,0,1",IDC_STATIC,41,14,169,8,SS_NOPREFIX
    LTEXT           "Copyright (C) 2009 Antillia.com",IDC_STATIC,42,26,140,8
    DEFPUSHBUTTON   "OK",IDOK,163,41,47,14,WS_GROUP
END
 */

public:
  /**
   * Constructor
   * @param parent  Parent Window handle
   * @param dialogName  DialoName is a dialog template name(string) in a application somthing resourc file(*.rc).
   *   See the above sample
   */
  AboutBox(HWND parent, const TCHAR* dialogName)
  {
    this->parent = parent;

    this->hInstance = GetModuleHandle(NULL);
    //Shallow pointer copy

    this->dialogTemplate = dialogName;//
  }

public:
  /**
   * 1 Create a dialog by calling ::DialogBox of AboutBox::dialogProc CALLBACK.
   * 2 ::DialogBox enters a own event loop
   */
  int  show() {
    int rc = ::DialogBox(this->hInstance, 
        this->dialogTemplate, this->parent,
         (DLGPROC)dialogProc);
    return rc;
  }


public:
  //DialogProcedure 
  static LRESULT CALLBACK dialogProc(
    HWND hwnd , UINT uMsg ,
    WPARAM wParam , LPARAM lParam)
  {
    switch (uMsg) {
    case WM_INITDIALOG:
      {
        center(hwnd, GetParent(hwnd));
        return TRUE; 
      }
      break;

    case WM_COMMAND:
      //If something command button (OK button) has beenn clicked
      //Simply end this modal event loop.
      EndDialog(hwnd, IDOK);
      break;

    case WM_CLOSE:
      EndDialog(hwnd, IDCANCEL);

    default:
      break;
    }
    return FALSE;
  }


public:
  static void center(HWND hwnd, HWND parent)
  {
    RECT rect;
    ::GetWindowRect(hwnd, &rect);

    int x      = 0;
    int y      = 0;
    int width  = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int scWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    int scHeight = ::GetSystemMetrics(SM_CYSCREEN);
    
    if(parent) {
      RECT pr;
      GetWindowRect(parent, &pr);
      x = pr.left + (pr.right - pr.left - width)/2;
      y = pr.top  + (pr.bottom - pr.top - height)/2;
    }
    if((x+width) >scWidth) {
      x = scWidth - width;
    }
    if(x <0 ) { 
      x = 0;
    }
    if((y+height) >scHeight){
      y = scHeight - height;
    }
    if(y < 0) { 
      y = 0;
    }
    
    MoveWindow(hwnd, x, y, width, height, FALSE);
    ShowWindow(hwnd, SW_SHOW);
  }  

};

}
