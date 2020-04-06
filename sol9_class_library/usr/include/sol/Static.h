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
 *  Static.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.08.13 getPreferredSize.
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>


namespace SOL {

class Static :public Primitive {
public:
  Static():Primitive() { }

public:
  Static(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  Static(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
        .set(XmNuseDefaultFont, _T("true"))
      .set(XmNclassName, _T("Static")));

    LONG_PTR val;
    if (args.get(XmNwidth, &val)  == FALSE ||
      args.get(XmNheight, &val) == FALSE) {
      const TCHAR*   label = name;
      if (args.get(XmNlabelString, &val)) {
        label = (TCHAR*)val;
      }
      resize(label);
    }
    return rc;
  }

public:
// 1999.08.13
  void getPreferredSize(Dimension& d)
  {
    TCHAR label[1024];
    label[0] = ZERO;
    getText(label, CountOf(label)); //2012/06/21
    resize(label);
    int w, h;
    getSize(w, h);
    d.set(w, h);
  }

  void  disable() { }

  HICON  getIcon() {
      return (HICON)send(STM_GETICON, 0, 0L);
  }

  BOOL  hasCallback() { return FALSE; }

  HICON  setIcon(HICON hicon) {
      return (HICON)send(STM_SETICON, (WPARAM)hicon, 0L);
  }

};

}



