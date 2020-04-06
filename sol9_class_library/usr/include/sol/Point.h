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
 *  Point.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Shape.h>

namespace SOL {

class Point :public Shape {
  int x1, y1;
  COLORREF color;
  public:
  Point(int p1, int q1) {
    x1 = p1; y1 = q1;
    color = RGB(0, 0, 0); // Black;
  }
  void  draw(DC* dc) {
      dc -> setPixel(x1, y1, color);
  }
  void  draw(DC* dc, int x, int y) {
      dc -> setPixel(x+x1, y+y1, color);
  }
  void  get(int* p1, int* q1) {
      *p1 = x1; *q1 = y1;
  }
  void  get(COLORREF* color1) {
      *color1 = color;
  }
  void  move(int x, int y) {
      x1 += x; y1 += y;
  }
  void  set(int p1, int q1) {
      x1 = p1; y1 = q1;
  }
  void  set(COLORREF color1) {
      color = color1;
  }
};

}


