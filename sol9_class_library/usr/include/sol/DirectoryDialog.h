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
 *  DirectoryDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

#include <sol\FileDialog.h>
#include <dlgs.h>
#include <sol\stdio.h>
#include <io.h>
#include <direct.h>

#define WM_DIRCHANGED   (WM_USER+100)
#define WM_DRIVECHANGED (WM_USER+101)

#define  DIR_FIELD  256

namespace SOL {


class DirectoryDialog :public FileDialog {
private:
  TCHAR*  dir;

private:
  long dirChanged(Event& event)
  {
    HWND hwnd = getWindow();
    HWND child = ::GetDlgItem(hwnd, lst2);
    int id = ::SendMessage(child, LB_GETCURSEL, 0, 0);

    TCHAR buff[_MAX_PATH];
    //ZeroMemory(buff, _MAX_PATH);
    memset(buff, (TCHAR)0, CountOf(buff));

    TCHAR item[_MAX_PATH];
    //ZeroMemory(item, _MAX_PATH);
    memset(item, (TCHAR)0, CountOf(item));

    buff[0] = (TCHAR)0;

    for(int i = 0; i<= id; i++) {
      ::SendMessage(child, LB_GETTEXT, i, (LPARAM)item);
      strcat_s(buff, sizeof(buff), item);

      if(i != id && strrchr(item, (TCHAR)'\\') == NULL) {
        strcat_s(buff, CountOf(buff)-strlen(buff), _T("\\"));
      }
    }
    child = ::GetDlgItem(hwnd, DIR_FIELD);
    ::SetWindowText(child, buff);
    setDir(buff);
    return NULL;
  }

private:
  long driveChanged(Event& event)
  {
    HWND hwnd    = getWindow();
    HWND control = ::GetDlgItem(hwnd, cmb2);

    int  id = ::SendMessage(control, CB_GETCURSEL, 0, 0);
    if(id > -1) {
      TCHAR drive[10];     
      ::SendMessage(control, CB_GETLBTEXT, id, (LPARAM)drive);
    //  Printf("Drive %s \r\n", drive);
      TCHAR cdir[_MAX_PATH];
      ::GetCurrentDirectory(CountOf(cdir), cdir); //2012/06/21
      HWND child = ::GetDlgItem(hwnd, DIR_FIELD);
      ::SetWindowText(child, cdir);
    }
    return NULL;
  }

private:
  long initDialog(Event& event)
  {
    RECT p;
    HWND hwnd = getWindow();
    getClientRect(&p);
    int width = p.right - p.left;
    int height = p.bottom - p.top;

    // Hide some controls.
    ::ShowWindow(::GetDlgItem(hwnd,stc1), SW_HIDE);
    ::ShowWindow(::GetDlgItem(hwnd, lst1), SW_HIDE);        
    ::ShowWindow(::GetDlgItem(hwnd,stc2), SW_HIDE);
    ::ShowWindow(::GetDlgItem(hwnd,stc3), SW_HIDE);
    ::ShowWindow(::GetDlgItem(hwnd,cmb1), SW_HIDE);

    RECT r;
    HWND child = ::GetDlgItem(hwnd,IDOK);
    ::GetWindowRect(child, &r);
    int w = r.right - r.left;
    int h = r.bottom - r.top;
    // Move thd FolderLabel.   
    child = ::GetDlgItem(hwnd, 0xffff);
    ::MoveWindow(child, 10, 4, width - w -40, h/2, TRUE);

    // Hide the Inputfield
    child = ::GetDlgItem(hwnd, edt1);
    ::ShowWindow(child, SW_HIDE);
    RECT e;
    ::GetWindowRect(child, &e);
    HFONT hfont = (HFONT)::SendMessage(child, WM_GETFONT, 0, 0);

    // Create a new edit control to display a directory.
    HINSTANCE hInst = (HINSTANCE)::GetWindowLong(hwnd, GWLP_HINSTANCE);
    DWORD exStyle = ::GetWindowLong(child, GWL_EXSTYLE);
    OPENFILENAME* ofn = get();
    child = ::CreateWindowEx(exStyle, _T("Edit"), ofn->lpstrInitialDir, 
      WS_CHILD|WS_TABSTOP|WS_VISIBLE|ES_AUTOHSCROLL,
      10, 8+h/2, width - w -40, e.bottom - e.top, hwnd,
      (HMENU)DIR_FIELD, hInst, NULL);
    if(hfont) {
      ::SendMessage(child, WM_SETFONT, (WPARAM)hfont, TRUE);
    }
    // Move the DirListbox.
    child = ::GetDlgItem(hwnd, lst2);
    ::MoveWindow(child, 10, 8+h/2+h+4, width - w -40,height-4*h, TRUE);

    // Move the DriveLabel.
    child = ::GetDlgItem(hwnd,stc4);
    ::GetWindowRect(child, &r);
    ::MoveWindow(child, 10, height-h-8-h/2, (width-w-40), h/2, TRUE);

    // Move the DriveCombobox.
    child = ::GetDlgItem(hwnd,cmb2);
    ::MoveWindow(child, 10, height-h-4, (width-w-40), h*5, TRUE);
 
    return FALSE;
  }


private:
  long command(Event& event)
  {
    HWND hwnd    = getWindow();
    WORD notify  = (WORD)event.getNotification(); //2000/11/18
   HWND control = (HWND)event.getLParam();

    WORD controlId = LOWORD(event.getWParam());
    if(controlId == lst2 && notify == LBN_DBLCLK) {
      ::PostMessage(hwnd, WM_DIRCHANGED, 0, 0);            
    }
    if(controlId == cmb2 && notify == CBN_SELCHANGE) {
      ::PostMessage(hwnd, WM_DRIVECHANGED, 0, 0);
    }

    if(controlId == IDOK) {
      TCHAR text[_MAX_PATH];    
      HWND child = ::GetDlgItem(hwnd, DIR_FIELD);
      ::GetWindowText(child, text, CountOf(text)); //2012/06/21
      setDir(text);
      ::EndDialog(hwnd, IDOK);
    }
    return FALSE;
  }


private:
  void setDir(TCHAR* string)
  {
    if(string) {
      delete [] dir;
      int slen = strlen(string)+1;
      dir = new TCHAR[slen];
      strcpy_s(dir, slen, string);
    }
  }


public:
    DirectoryDialog():FileDialog() { }


public:
  DirectoryDialog(View* parent, const TCHAR* name, Args& args)
  :FileDialog(parent, name, 
    args.set(XmNflags, OFN_HIDEREADONLY|OFN_LONGNAMES)
        .set(XmNhook, (LONG_PTR)&CommonDialog::hook))
  {
    dir = NULL;
    addEventHandler(WM_COMMAND, this,
      (Handler)&DirectoryDialog::command, NULL);

    addEventHandler(WM_DIRCHANGED, this,
      (Handler)&DirectoryDialog::dirChanged, NULL);
    addEventHandler(WM_DRIVECHANGED, this,
      (Handler)&DirectoryDialog::driveChanged, NULL);

    addEventHandler(WM_INITDIALOG, this,
      (Handler)&DirectoryDialog::initDialog, NULL);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = FileDialog::create(parent, name, 
      args.set(XmNflags, OFN_HIDEREADONLY|OFN_LONGNAMES)
        .set(XmNhook, (LONG_PTR)&CommonDialog::hook));

    dir = NULL;
    addEventHandler(WM_COMMAND, this,
      (Handler)&DirectoryDialog::command, NULL);

    addEventHandler(WM_DIRCHANGED, this,
      (Handler)&DirectoryDialog::dirChanged, NULL);
    addEventHandler(WM_DRIVECHANGED, this,
      (Handler)&DirectoryDialog::driveChanged, NULL);

    addEventHandler(WM_INITDIALOG, this,
      (Handler)&DirectoryDialog::initDialog, NULL);
    return rc;
  }

public:
  ~DirectoryDialog()
  {
    delete [] dir;
  }


public:
  TCHAR*  getDir() { return dir; }
};

}



