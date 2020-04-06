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
 *  DynamicDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\PopupView.h>

namespace SOL {

class DynamicDialog :public PopupView {
protected:
  LRESULT  defaultProc(Event& event) {
    return FALSE;
  }
public:
  DynamicDialog():PopupView() { }

public:
  //2012/06/22
  DynamicDialog(View* parent, const TCHAR* label, Args& args)
  :PopupView()
  {
    create(parent, label, args);
  }

public:
  //2012/06/22
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    return PopupView::create(parent, label,
      args.set(XmNpredefined, True)
          .set(XmNclassName, (LONG_PTR)WC_DIALOG));

  }

  void  popup(Action& action) {
      show(SW_NORMAL);
  }
};

}


