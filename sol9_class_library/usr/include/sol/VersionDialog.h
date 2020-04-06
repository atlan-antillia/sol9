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
 *  VersionDialog.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/18
//

#pragma once

#include <sol/Object.h>

/**
 * DialogBox based on Windows resource file (*.rc)
 */
namespace SOL {

class VersionDialog :public Object{
private:
  HWND  hparent;
  HWND  hwnd;
  HINSTANCE hInstance;

  const char*  dialogTemplate;

public:
  /**
   * @param parent   A parent Window hande
   * @param dialogID A dialogID in each application's resource file (*.rc)
   */
  VersionDialog(HWND parent, int dialogID)
    :hparent(parent)
  {
    this->hparent = parent;

    this->hInstance = GetModuleHandle(NULL);

    //this->dialogTemplate = (const char*)IDD_ABOUTBOX;
    this->dialogTemplate = MAKEINTRESOURCE(dialogID);
  }

public:

  int    show() {
    int rc = ::DialogBox(this->hInstance, 
          this->dialogTemplate, 
          this->hparent,
          (DLGPROC) dialogProc);
    return rc;
  }


private:
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

public:
  static LRESULT CALLBACK dialogProc(HWND hwnd, UINT msg,
      WPARAM wParam, LPARAM lParam)
  {
    switch (msg) {
    case WM_INITDIALOG:
      {
        center(hwnd, GetParent(hwnd));
        return TRUE; 
      }
      break;

    case WM_COMMAND:
      EndDialog(hwnd, IDOK);
      break;

    case WM_CLOSE:
      EndDialog(hwnd, IDCANCEL);

    default:
      break;
    }
    return FALSE;
  }

};

}
