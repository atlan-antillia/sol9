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
 *  ColorTable.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/04/22 Updated.

#pragma once

#include <sol\HashTable.h>

#include <sol\ColorItem.h>
#include <sol\String.h>
#include <sol\StringBuffer.h>

namespace SOL {

class ColorTable :public HashTable {

public:
  static const long Black    =RGB(   0,    0,    0);
  static const long Blue    =RGB(   0,    0, 0xff);
  static const long Brown    =RGB(0x80, 0x80,    0);
  static const long Cyan    =RGB(   0, 0xff, 0xff);
  static const long DarkBlue  =RGB(   0,    0, 0x80);
  static const long DarkCyan  =RGB(   0, 0x80, 0x80);
  static const long DarkGray  =RGB(0x80, 0x80, 0x80);
  static const long DarkGreen =RGB(   0, 0x80,    0);
  static const long DarkMagenta=RGB(0x80,    0, 0x80);
  static const long DarkRed   =RGB(0x80,    0,    0);
  static const long Gray    =RGB(0xc0, 0xc0, 0xc0);
  static const long Green    =RGB(   0, 0xff,    0);
  static const long LightBlue  =RGB(   0,    0, 0xff);
  static const long LightCyan  =RGB(   0, 0xff, 0xff);
  static const long LightGray  =RGB(0xc0, 0xc0, 0xc0);
  static const long LightGreen=RGB(   0, 0xff,    0);
  static const long LightMagenta=RGB(0xff,    0, 0xff);
  static const long LightRed  =RGB(0xff,    0,    0);
  static const long Magenta  =RGB(0xff,    0, 0xff);
  static const long Red    =RGB(0xff,    0,    0);
  static const long White    =RGB(0xff, 0xff, 0xff);
  static const long Yellow  =RGB(0xff, 0xff,    0);

public:
  ColorTable()
  :HashTable(113)
  {
    initialize();
  }


private:
  ColorItem* getColorItems(int& count)
  {
    static ColorItem rgbTable[] = { 
    {_T("Black"),  Black},
    {_T("Blue"),  Blue},
    {_T("Brown"),  Brown},
    {_T("Cyan"),  Cyan},
    {_T("DarkBlue"),  DarkBlue},
    {_T("DarkCyan"),     DarkCyan},
    {_T("DarkGray"),    DarkGray},
    {_T("DarkGreen"),   DarkGreen},
    {_T("DarkMagenta"),  DarkMagenta},
    {_T("DarkRed"),  DarkRed},
    {_T("Gray"),  Gray},
    {_T("Green"),  Green},
    {_T("LightBlue"),  LightBlue},
    {_T("LightCyan"),  LightCyan},
    {_T("LightGray"),  LightGray},
    {_T("LightGreen"),  LightGreen},
    {_T("LightMagenta"), LightMagenta},
    {_T("LightRed"),  LightRed},
    {_T("Magenta"),  Magenta},
    {_T("Red"),    Red},
    {_T("White"),  White},
    {_T("Yellow"),  Yellow},
    };

    count = CountOf(rgbTable);
    return rgbTable;
  }

private:
  void initialize()
  {
    int count = 0;
    ColorItem* rgbTable = getColorItems(count);

    for(int i = 0; i<count; i++) {
      add(rgbTable[i].name, (Object*)&rgbTable[i]);
    }
  }

public:
  BOOL get(const TCHAR* colorName, long* value)
  {
    ColorItem* colorItem  = (ColorItem*) lookup(colorName);
    if(colorItem) {
      *value = colorItem->value;
      return TRUE;
    }
    else return FALSE;
  }

public:
  String getColorNames()
  {
    StringBuffer buffer;
    int count = 0;
    ColorItem* rgbTable = getColorItems(count);
    for(int i = 0; i<count; i++) {
      buffer.append(rgbTable[i].name);
      buffer.append(_T(" "));
      if (i>0 && i%8==0) {
        buffer.append(_T("\n"));
      }
    }
    return String((const TCHAR*)buffer);
  }
};

}


