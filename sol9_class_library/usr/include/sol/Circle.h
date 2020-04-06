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
 *  Circle.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Shape.h>

namespace SOL {

class Circle :public Shape {
private:
    int      x,  y;
    unsigned int radius;
   
public:
  Circle(int x1, int y1, unsigned int r) {
    x = x1; y = y1;
    radius = r;
  }

public:
  void   draw(DC* dc) {
    Circle::draw(dc, 0, 0);
  }
public:

  void draw(DC* dc, int px, int py)
  {
    if(getFillMode()) {
         Brush brush(getBackColor());
      Pen pen(PS_SOLID, getBorderWidth(), getBorderColor());
         HGDIOBJ oldbrush = dc->select(&brush);
      HGDIOBJ oldpen   = dc->select(&pen);
         dc -> ellipse(px+x-radius, py+y-radius, 
        px+x+radius, py+y+radius);
         dc->select(oldbrush);
      dc->select(oldpen);
    }
    else {
      StockObject brush(NULL_BRUSH);
      Pen pen(PS_SOLID, getBorderWidth(), getBorderColor());
      dc ->select(&brush);
      HGDIOBJ oldpen =dc ->select(&pen);
         dc -> ellipse(px+x-radius, py+y-radius, 
        px+x+radius, py+y+radius);
      dc -> select(oldpen);
    }
  }

  void  get(int* x1, int* y1, unsigned int *r) {
      *x1 = 1; *y1 = y;
      *r  = radius;
  }

  void  move(int x1, int y1) {
    x += x1; y += y1;
  }

  void  set(int x1, int y1, unsigned int r) {
    x = x1; y = y1;
    radius = r;
  }
};

}

