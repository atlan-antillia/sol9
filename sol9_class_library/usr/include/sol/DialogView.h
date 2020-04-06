/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DialogView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/21

#pragma once

#include <sol\PopupView.h>


namespace SOL {

class DialogView :public PopupView {
private:
//  void changeSystemMenu();
  void changeSystemMenu()
  {
    HMENU sysMenu = ::GetSystemMenu(getWindow(), 0);
    int   count   = ::GetMenuItemCount(sysMenu);
    TCHAR item1[MAX_PATH];
    TCHAR item2[MAX_PATH];
    ::GetMenuString(sysMenu, SC_MOVE,  item1, CountOf(item1), MF_BYCOMMAND); //2012/06/21
    ::GetMenuString(sysMenu, SC_CLOSE, item2, CountOf(item2), MF_BYCOMMAND); //2012/06/21
    for(int i = 0; i<count; i++) {
      ::DeleteMenu(sysMenu, 0, MF_BYPOSITION);
    }
    ::AppendMenu(sysMenu, MF_STRING, SC_MOVE,  item1);
    ::AppendMenu(sysMenu, MF_STRING, SC_CLOSE, item2);
  }

public:
  DialogView():PopupView() { }

public:
  DialogView(View* parent, const TCHAR* name, Args& args)
  :PopupView()
  {
    create(parent,name, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = PopupView::create(parent, name, 
       args.set(XmNexStyle, (LONG_PTR)WS_EX_DLGMODALFRAME));

    changeSystemMenu();

    return rc;
  }

};

}

