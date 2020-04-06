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
 *  MdiChild.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\Primitive.h>


namespace SOL {

class MdiClient :public Primitive {
public:
  MdiClient(): Primitive() { }

public:
  //2012/06/23
  MdiClient(View* parent, const TCHAR* name, Args& args)
    :Primitive()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
      args.set(XmNstyle, (LONG_PTR)(WS_VISIBLE|WS_CLIPCHILDREN))
          .set(XmNpredefined, TRUE)
          .set(XmNclassName, _T("MDIClient")));

    setValues(args);

    return rc;
  }


  void  activate(View* mdiChild) {
      send(WM_MDIACTIVATE, (WPARAM)mdiChild->getWindow(), 0L);
  }
  void  cascade() {
      send(WM_MDICASCADE, 0, 0L);
  }
  void  iconArrange() {
      send(WM_MDIICONARRANGE, 0, 0L);
  }
  HWND  getActiveWindow() {
      return (HWND)send(WM_MDIGETACTIVE, 0, 0L);
  }
  void  setMenu(HMENU hmenu, HMENU hsubmenu) {
      send(WM_MDISETMENU, (WPARAM)hmenu, (LPARAM)hsubmenu);
  }
  void  tile() {
      send(WM_MDITILE, 0, 0L);
  }
  long  destroy(Event& event) {
    return send(WM_MDIDESTROY, event.getWParam(),
            event.getLParam());
  }
};

}

