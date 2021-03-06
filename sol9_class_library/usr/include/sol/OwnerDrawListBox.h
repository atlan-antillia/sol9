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
 *  OwnerDrawListBox.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\ListBox.h>

namespace SOL {

class OwnerDrawListBox :public ListBox {
public:
  OwnerDrawListBox(): ListBox() { }

public:
  //2012/06/23
  OwnerDrawListBox(View* parent, const TCHAR* label, Args& args)
  :ListBox()
  {
    create(parent, label, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = ListBox::create(parent, label,
      args.set(XmNstyle, 
        (LONG_PTR)(LBS_OWNERDRAWFIXED|LBS_NOINTEGRALHEIGHT)) ); 

    setValues(args);
    return rc;
  }

  void  add(Object* object) {
      send(LB_ADDSTRING,    0,  (LPARAM)object);
  }
  void  addLast(Object* object) {
      send(LB_INSERTSTRING, (WPARAM)(-1), (LPARAM)object);
  }

};

}


