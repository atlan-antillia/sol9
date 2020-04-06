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
 *  Menu.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.06.15 Added some new methods.
// 2000/11/18 to-arai:Added return to some methods.

#pragma once

#include <sol\View.h>

namespace SOL {

class Menu :public Object {
private:
  View*    owner;
  HMENU     hmenu;

  void  redraw() {
    ::DrawMenuBar(owner -> getWindow());
  }

  //2012/06/23
public:
  Menu()
  {
    owner = NULL;
    hmenu = NULL;
  }

public:
  void setOwner(View* view)
  {
    owner = view;
  }

public:
  Menu(View* view) {
    owner = view;
    hmenu = NULL;
  }

public:  
  void  checkByCommand(int id) {
    ::CheckMenuItem(hmenu, id, MF_BYCOMMAND|MF_CHECKED);
  }
  void  checkByPosition(int pos) {
    ::CheckMenuItem(hmenu, pos, MF_BYPOSITION|MF_CHECKED);
  }
  int   getItemCount() {
    return ::GetMenuItemCount(hmenu);
  }
  void  deleteByCommand(int id) {
    ::DeleteMenu(hmenu, id, MF_BYCOMMAND);
    redraw();
  }
  void  deleteByPosition(int pos) {
    ::DeleteMenu(hmenu, pos, MF_BYPOSITION);
    redraw();
  }
  void  enableByPosition(int pos) {
    ::EnableMenuItem(hmenu, pos, MF_ENABLED|MF_BYPOSITION);
    redraw();
  }
  void  enableByCommand(int id) {
    ::EnableMenuItem(hmenu, id, MF_ENABLED|MF_BYCOMMAND);
    redraw();
  }
  void  disableByPosition(int pos) {
    ::EnableMenuItem(hmenu, pos, MF_GRAYED|MF_BYPOSITION);
    redraw();
  }
  void  disableByCommand(int id) {
    ::EnableMenuItem(hmenu, id, MF_GRAYED|MF_BYCOMMAND);
    redraw();
  }
  void  getStringByCommand(int id, TCHAR* string, int len) {
    ::GetMenuString(hmenu, id,  string, len, MF_BYCOMMAND);
  }
  void  getStringByPosition(int pos, TCHAR* string, int len) {
    ::GetMenuString(hmenu, pos, string, len, MF_BYPOSITION);
  }
  HMENU get() { return hmenu; }
  View* getOwner() { return owner; }
  void  set(HMENU hmenu1) { hmenu = hmenu1; }
  void  uncheckByCommand(int id) {
    ::CheckMenuItem(hmenu, id, MF_BYCOMMAND|MF_UNCHECKED);
  }
  void  uncheckByPosition(int pos) {
    ::CheckMenuItem(hmenu, pos, MF_BYPOSITION|MF_UNCHECKED);
  }

  //<added date="2000.06.15">
  BOOL  isCheckedByCommand(int id) {
    BOOL rc = FALSE;
    UINT state =::GetMenuState(hmenu, id, MF_BYCOMMAND);
    if (state & MF_CHECKED) {
      rc = TRUE;
    }
    return rc;
  }

  BOOL  isCheckedByPosition(int pos) {
    BOOL rc = FALSE;
    UINT state =::GetMenuState(hmenu, pos, MF_BYPOSITION);
    if (state & MF_CHECKED) {
      rc = TRUE;
    }
    return rc;
  }


  void  toggleCheckByCommand(int id) {
    if (isCheckedByCommand(id)) {
      uncheckByCommand(id);
    } else {
      checkByCommand(id);
    }
  }

  void  toggleCheckByPosition(int pos) {
    if (isCheckedByPosition(pos)) {
      uncheckByPosition(pos);
    } else {
      checkByPosition(pos);
    }
  }

  UINT  getStateByCommand(int id) {
    return ::GetMenuState(hmenu, id, MF_BYCOMMAND);
  }

  UINT  getStateByPosition(int pos) {
    return ::GetMenuState(hmenu, pos, MF_BYPOSITION);
  }

  BOOL  getMenuItemInfoByCommand(MENUITEMINFO& menuItemInfo, int id) {
    memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));
    menuItemInfo.cbSize = sizeof(MENUITEMINFO);
    // 2000/11/18
    return ::GetMenuItemInfo(hmenu, id, FALSE, &menuItemInfo);
  }

  BOOL  getMenuItemInfoByPosition(MENUITEMINFO& menuItemInfo, int pos) {
    memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));
    menuItemInfo.cbSize = sizeof(MENUITEMINFO);
    // 2000/11/18
    return ::GetMenuItemInfo(hmenu, pos,  TRUE, &menuItemInfo);
  }

};

}

