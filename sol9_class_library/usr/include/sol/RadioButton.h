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
 *  RadioButton.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Button.h>

namespace SOL {

class RadioButton :public Button {
public:
    RadioButton():Button() { }

public:
    RadioButton(View* parent, HWND hwnd)
    :Button(parent, hwnd) { }

public:
  //2012/06/25
  RadioButton(View* parent, const TCHAR* label, Args& args)
  :Button()
  {
    create(parent, label, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    return   Button::create(parent, label, 
      args.set(XmNstyle, (LONG_PTR)(WS_TABSTOP|BS_AUTORADIOBUTTON) ));

  }

public:
  void getPreferredSize(Dimension& d)
  {
    TCHAR label[1024];
    label[0] = ZERO;
    getText(label, CountOf(label)); //2012/06/21

    resize(label);
    int w, h;
    getSize(w, h);
    // 2001/03/18
    d.set(w, h);
  }
};

}


