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
 *  Region.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\GdiObject.h>

#include <sol\Brush.h>

namespace SOL {

class Region :public GdiObject {
  public:
  Region(HRGN hrgn)
    :GdiObject((HANDLE)hrgn) { };
  ~Region() {
      HRGN hrgn = (HRGN)get();
      if(hrgn) DeleteObject(hrgn);
  }
  BOOL  equal(Region* region) {
      return ::EqualRgn((HRGN)get(), (HRGN)region->get());
  }
  BOOL  fill(HDC hdc, Brush* brush) {
      return ::FillRgn(hdc, (HRGN)get(), (HBRUSH)brush->get());
  }
  BOOL  frame(HDC hdc, Brush* brush, int width, int height) {
      return ::FrameRgn(hdc, (HRGN)get(), (HBRUSH)brush->get(), 
        width, height);
  }
  int    getBox(RECT* rect) {
      return ::GetRgnBox((HRGN)get(), rect);
  }
  BOOL  invert(HDC hdc) {
      return ::InvertRgn(hdc, (HRGN)get());
  }
  int    offset(int x, int y) {
      return ::OffsetRgn((HRGN)get(), x, y);
  }
  BOOL   paint(HDC hdc) {
      return ::PaintRgn(hdc, (HRGN)get());
  }
  BOOL   ptIn(int x, int y) {
      return ::PtInRegion((HRGN)get(), x, y);
  }
  BOOL   rectIn(RECT* rect) {
      return ::RectInRegion((HRGN)get(), rect);
  }

  //2009/11/01
public:
  operator HRGN(){
    return (HRGN)get();
  }

};

}

