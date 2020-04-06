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
 *  MenuBar.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Menu.h>

#include <sol\LinkedList.h>
#include <sol\Item.h>
#include <sol\StringT.h>

namespace SOL {

//2008/08/04
typedef struct {
  const TCHAR* name;  //Display string
  int id;        //Id
  int flags;      //Flags  (Ex. MF_GLAYED|MF_STRING)
} MenuItem;

class MenuBar :public Menu {

public:
  MenuBar()
    :Menu()
  {
  }

public:
  //2012/06/23
  MenuBar(View* view, const TCHAR* name)
  {
    create(view, name);
  }


public:
  //2012/06/23
  Boolean create(View* view, const TCHAR* name)
  {
    Boolean rc = True;
    Menu::setOwner(view);

    HWND   hwnd    = view -> getWindow();
    HINSTANCE progIns = (HINSTANCE)::GetWindowLong(hwnd, GWLP_HINSTANCE);
    HMENU  hmenu   = ::LoadMenu(progIns, name);
    if(hmenu == NULL) {
      //2017/07/20
      TCHAR menuName[MAX_PATH];
      if (!StringT<TCHAR>::endsWithIgnoreCase(name, _T(".exe"))) { 
        _stprintf_s(menuName, CountOf(menuName), _T("%s.exe"), name);
        hmenu   = ::LoadMenu(progIns, menuName);
      } else {
        strcpy_s(menuName, CountOf(menuName), name);
        TCHAR* dot = (TCHAR*)strstr(menuName, _T(".exe"));
        if (dot) {
          *dot = NULL;
        }
        hmenu   = ::LoadMenu(progIns, menuName);        
      }
      if (hmenu == NULL) {
        hmenu = ::CreateMenu();
      }
    }
    set(hmenu);
    ::SetMenu(hwnd, hmenu);
    ::DrawMenuBar(hwnd);
    return rc;
  }

public:
  void tearOff(int n)
  {
    HMENU hpopup = ::GetSubMenu(get(), n);
    if(hpopup) {
      POINT p;
      ::GetCursorPos(&p);
      View* owner = getOwner();
      int  h = ::GetSystemMetrics(SM_CYMENU);
      ::TrackPopupMenu(hpopup, 0, p.x-h, p.y-h/2, 0,
             owner->getWindow(), NULL);
    }
  }


public:
  void append(const TCHAR* head, LinkedList* list)
  {
    View* owner  = getOwner();
    HMENU hmenu  = get();
    HMENU hpopup= ::CreateMenu();
    //2016/10/05 (WORD)hpopup ->(UINT_PTR)hpopup
    ::AppendMenu(hmenu, MF_STRING | MF_POPUP, (UINT_PTR)hpopup, head);

    if(list) {
      ListEntry* p = list -> getEntry();
      while(p) {
        Item* item = (Item *)(p->getObject());
        if(strcmp(item->getText(), _T("SEPARATOR")) == 0) {
          ::AppendMenu(hpopup, MF_SEPARATOR, 0, 0L);
        }
        else {
          ::AppendMenu(hpopup, MF_STRING, 
             item->getId(), item->getText());
        }
        p = p->getNext();
      }
    }
    ::DrawMenuBar(owner ->getWindow());
  }

public:
  void addPopupMenu(HMENU hpopup, LinkedList* list)
  {
    if(list) {
      ListEntry* p = list -> getEntry();
      while(p) {
        Item* item = (Item *)(p->getObject());
        if(strcmp(item->getText(), _T("SEPARATOR")) == 0) {
          ::AppendMenu(hpopup, MF_SEPARATOR, 0, 0L);
        }
        else {
          ::AppendMenu(hpopup, MF_STRING, 
             item->getId(), item->getText());
        }
        p = p->getNext();
      }
    }
  }

public:
  void changePopupMenu(int n, TCHAR* menuItems[])
  {
    HMENU hmenu  = get();
    HMENU hpopup = ::GetSubMenu(hmenu, n);

    int count = ::GetMenuItemCount(hpopup);
    // For BC by Yamada of SOFT BANK.
    int i = 0;
    for(i = 0; i<count; i++) {
      ::DeleteMenu(hpopup, 0, MF_BYPOSITION);
    }
    for(i = 0; menuItems[i] != NULL; i++) {
      if(strcmp(menuItems[i], _T("SEPARATOR")) == 0) {
        ::AppendMenu(hpopup, MF_SEPARATOR,0, 0L);
      }
      else {
        ::AppendMenu(hpopup, MF_STRING,i, menuItems[i]);
      }
    }
  }

public:
  HMENU getPopupHandle(int n)
  {
    return ::GetSubMenu((HMENU)get(), n);
  }

public:
  void update(int n, const TCHAR* head, LinkedList* items, HMENU hpopup) 
  {
    HMENU hmenu = get();
    View* owner = getOwner();

    ::ChangeMenu(hmenu,n, head, (UINT)hpopup,
      MF_POPUP|MF_CHANGE|MF_BYPOSITION);
    int count = ::GetMenuItemCount(hpopup);
    for(int i = 0; i<count; i++) {
      ::DeleteMenu(hpopup, 0, MF_BYPOSITION);
    }
    ListEntry* p = items -> getEntry();
    while(p) {
      Item* item = (Item *)(p->getObject());
      if(strcmp(item->getText(), _T("SEPARATOR")) == 0) {
        ::AppendMenu(hpopup, MF_SEPARATOR, 0, 0L);
      }
      else {
        ::AppendMenu(hpopup, MF_STRING, item->getId(), 
             (TCHAR*)item->getText());
      }
      p = p -> getNext();
    }
    ::DrawMenuBar(owner->getWindow());
  }

//2008/08/04
public:
  void append(const TCHAR* name, const MenuItem* items, int count)
  {
    View* owner = getOwner();
    HMENU hPopup = CreatePopupMenu();

    HMENU hMenu  = get();

    AppendMenu(hMenu, MF_ENABLED | MF_POPUP , (UINT_PTR)hPopup, name);
    for (int i = 0; i<count; i++) {
      AppendMenu(hPopup, 
        items[i].flags,  //MF_ENABLED | MF_STRING ,
        items[i].id, items[i].name);
    }
    ::DrawMenuBar(owner ->getWindow());
  }

};

}


