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
 *  CommonDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

#include <sol\View.h>
#include <commdlg.h>


typedef UINT (CALLBACK* HOOKFUN)(HWND, UINT, WPARAM, LPARAM);


namespace SOL {

class CommonDialog :public View {
private:
  void*  calldata;

protected:
  CommonDialog():View() {
      calldata = NULL;
  }


public:
  CommonDialog(View* parent, void* data)
  :View(parent) 
  {
    calldata = data;
  }


public:
  virtual Boolean create(View* parent, void* data)
  { 
    Boolean rc = True;
    View::setParent(parent);


    calldata = data;
    return rc;
  }


public:
  LRESULT defaultProc(Event& event)
  {
    return FALSE;
  }


public:
  LRESULT command(Event& event)
  {
    MessageBox(NULL, _T("Command"), _T("Debug"), MB_OK);
    
    return FALSE;
  }

public:   
  virtual void popup(Action& action)
  {
    // Realize a modal/modeless common dialog.
  }


public:
  ~CommonDialog() { 
    setWindow(NULL); 
  }


  void*  getCallData() { 
    return calldata; 
  }



public:
  static long CALLBACK hookProc(HWND hwnd, UINT message, 
      WPARAM wParam, LPARAM lParam)
  {
    CommonDialog* dlg = NULL;

    if (message == WM_INITDIALOG) {
      dlg = (CommonDialog*)lParam;
      Application::add(hwnd, dlg);
    } else {
      dlg = (CommonDialog*)Application::lookup(hwnd);
    }

    if(message == WM_DESTROY) {
      Application::remove(hwnd);
      return 0L;
    }

    Event event(message, wParam, lParam);

    if(dlg) {
      //if (message ==WM_COMMAND) {
      //  dlg->command(event);
      //}
      return (UINT)dlg -> dispatch(event);
    } else{
      return 0L;
    }
  }

};

}

