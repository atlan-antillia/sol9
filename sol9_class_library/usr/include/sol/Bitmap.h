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
 *  Bitmap.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\GdiObject.h>

namespace SOL {

class DC;

class Bitmap :public GdiObject {
private:
  int    dx, dy;
  int    sx, sy;
  int    ratio;
  int    width;
  int    height;
  DWORD  operation;
  Boolean  destructable;
  
public:
  Bitmap(const TCHAR* name, HBITMAP hbitmap)
  :GdiObject(name, hbitmap)
  {
    dx = dy = 0;
    sx = sy = 0;
    BITMAP bm;
    ::GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
    width     = bm.bmWidth;
    height    = bm.bmHeight;
    ratio     = 100;    // V1.20 specify a percentage 
    operation = SRCCOPY;
    destructable  = TRUE;
  }

public:
  ~Bitmap() { 
    if(destructable) {
      ::DeleteObject(get());
    }
  }

public:
  void draw(HDC hdc, int x, int y)
  {
    HBITMAP hbitmap = (HBITMAP)get();

    if(hbitmap) {
      HDC hdcMem = ::CreateCompatibleDC(hdc);
      ::SelectObject(hdcMem, hbitmap);
      ::SetMapMode(hdcMem, GetMapMode(hdc));
      ::StretchBlt(hdc,     x, y, width*ratio/100, height*ratio/100,
            hdcMem, sx, sy, width, height, operation);
      ::DeleteDC(hdcMem);
    }
  }

public:
  void draw(DC& dc, int x, int y)
  {
    Bitmap::draw(dc.get(), x, y);
  }


  void  getDestination(int& x, int& y) { x = dx; y = dy; }

  void  getSize(int& w, int& h) { w = width; h = height; }

  void  getSource(int& x, int& y) { x = sx; y = sy; }

  void  setDestination(int x, int y) { dx = x; dy = y; }

  void  setFlag(Boolean flag) { destructable = flag; }

  void  setOperation(DWORD op) { operation = op; }

  void  setSource(int x, int y) { sx = x; sy = y; }

  void   setStretchingRatio(int r) { ratio = r; }
};

}


