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
 *  PopupMenu.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Menu.h>
#include <sol/PopupMenuItem.h>

namespace SOL {

class PopupMenu :public Menu {

public:
  //2012/06/23
  PopupMenu()
    :Menu()
  {
  }

public:
  //2012/06/23
  PopupMenu(View* view)
    :Menu(view) 
  {
   // setOwner(view);
    set(::CreatePopupMenu());
  }

public:
  ~PopupMenu() 
  {
    ::DestroyMenu(get());
  }

public:
  void  append(int id, TCHAR* item) 
  {
    ::AppendMenu(get(), MF_STRING, id, item);
  }
  
  void  append(int id, const TCHAR* item) 
  {
    ::AppendMenu(get(), MF_STRING, id, item);
  }
  
public:
  void track()
  {
    POINT p;
    ::GetCursorPos(&p);
    View* owner = getOwner();
    int  h = ::GetSystemMetrics(SM_CYMENU);
    // Modified to select an item with the right button.
    ::TrackPopupMenu(get(), TPM_CENTERALIGN|TPM_RIGHTBUTTON,
      p.x-h, p.y-h/2, 0, 
      owner->getWindow(), NULL);
  }


};

}


