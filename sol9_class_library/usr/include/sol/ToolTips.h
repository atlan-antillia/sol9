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
 *  ToolTips.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25 Updated

#pragma once

#include <sol\PopupView.h>

namespace SOL {

class ToolTips :public PopupView {
public:  
  ToolTips(): PopupView() { }

public:
  //2012/06/25
  ToolTips(View* parent, const TCHAR* label, Args& args)
  :PopupView()
  {
    create(parent, label, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    return PopupView::create(parent, label,
      args.set(XmNpredefined, TRUE)
          .set(XmNclassName, (LONG_PTR)TOOLTIPS_CLASS));
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNneedTextCallback,   TTN_NEEDTEXT},
    {XmNpopupCallback,    TTN_POP},
    {XmNshowCallback,    TTN_SHOW},
     };

    *num = XtNumber(table);
    return table;
  }

public:  
  //2012/06/21 Updated
  //  void   addTool(View* parent, View* target, TCHAR* text, UINT flags);
  void addTool(View* target, TCHAR* text, UINT flags) 
  {
    if(target) {
      TOOLINFO ps;
      memset(&ps, 0, sizeof(ps));
      ps.cbSize = sizeof(ps);
      ps.hwnd   = target->getWindow(); //parent -> getWindow();  
      ps.uFlags =  flags;  
      ps.hinst  = target->getInstanceHandle();
      ps.lpszText = text;
      ps.uId      = (UINT)target->getWindow();

      //2012/06/20
      target->getClientRect(&(ps.rect));

      send(TTM_ADDTOOL, 0, (LPARAM)&ps);
    }
  }

  void  addTool(TOOLINFO* info) {
      send(TTM_ADDTOOL, 0, (LPARAM)info);
  }
};

}


