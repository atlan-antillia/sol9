/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SystemColor.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\HashTable.h>
#include <sol\ColorItem.h>

namespace SOL {

class SystemColor :public HashTable {

private:
  void initialize()
  {
  static ColorItem colors[] = {
    {_T("COLOR_ACTIVEBORDER"),     COLOR_ACTIVEBORDER},
    {_T("COLOR_ACTIVECAPTION"),    COLOR_ACTIVECAPTION},
    {_T("COLOR_APPWORKSPACE"),    COLOR_APPWORKSPACE},

    {_T("COLOR_BACKGROUND"),    COLOR_BACKGROUND},
    {_T("COLOR_BTNFACE"),      COLOR_BTNFACE},
    {_T("COLOR_BTNSHADOW"),      COLOR_BTNSHADOW},
    {_T("COLOR_BTNTEXT"),      COLOR_BTNTEXT},
    {_T("COLOR_CAPTIONTEXT"),    COLOR_CAPTIONTEXT},
    {_T("COLOR_GRAYTEXT"),      COLOR_GRAYTEXT},

    {_T("COLOR_HIGHLIGHT"),      COLOR_HIGHLIGHT},
    {_T("COLOR_HIGHLIGHTTEXT"),    COLOR_HIGHLIGHTTEXT},
    {_T("COLOR_INACTIVEBORDER"),  COLOR_INACTIVEBORDER},
    {_T("COLOR_INACTIVECAPTION"),  COLOR_INACTIVECAPTION},
    {_T("COLOR_MENU"),        COLOR_MENU},
    {_T("COLOR_MENUTEXT"),      COLOR_MENUTEXT},
    {_T("COLOR_SCROLLBAR"),      COLOR_SCROLLBAR},
    {_T("COLOR_WINDOW"),      COLOR_WINDOW},
    {_T("COLOR_WINDOWFRAME"),    COLOR_WINDOWFRAME},
    {_T("COLOR_WINDOWTEXT"),    COLOR_WINDOWTEXT},
    };

    for(int i = 0; i<XtNumber(colors); i++) {
      add(colors[i].name, (Object*)&colors[i]);
    }
  }

public:
  SystemColor()
  :HashTable(113)
  {
    initialize();
  }

public:
  BOOL get(const TCHAR* name, long* value)
  {
    ColorItem* colorItem  = (ColorItem*) lookup(name);
    if(colorItem) {
      int indx = (int)colorItem ->value;
      *value   = ::GetSysColor(indx);
      return TRUE;
    }
    else return FALSE;
  }


};

}


