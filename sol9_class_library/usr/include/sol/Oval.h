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
 *  Oval.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Shape.h>


namespace SOL {

class Oval :public Shape {
private:
    int x1, y1;
    int x2, y2;
   
public:
  Oval(int p1, int q1, int p2, int q2) {
    x1 = p1; y1 = q1;
    x2 = p2; y2 = q2;
  }

  void   draw(DC* dc) {
      Oval::draw(dc, 0, 0);
  }

  void  draw(DC* dc, int x, int y)
  {
    if(getFillMode()) {
         Brush brush(getBackColor());
      Pen pen(PS_SOLID, getBorderWidth(), getBorderColor());
         HGDIOBJ oldbrush = dc->select(&brush);
      HGDIOBJ oldpen   = dc->select(&pen);
      dc -> ellipse(x+x1, y+y1, x+x2, y+y2);
         dc -> select(oldbrush);
      dc -> select(oldpen);
    }
    else {
      StockObject brush(NULL_BRUSH);
      Pen pen(PS_SOLID, getBorderWidth(), getBorderColor());
      dc -> select(&brush);
      HGDIOBJ oldpen =dc ->select(&pen);
      dc -> ellipse(x+x1, y+y1, x+x2, y+y2);
      dc -> select(oldpen);
    }
  }


  void  get(int* p1, int* q1, int* p2, int* q2) {
        *p1 = x1; *q1 = y1;
        *p2 = x2; *q2 = y2;
  }

  void  move(int x, int y) {
        x1 += x; y1 += y;
        x2 += x; y2 += y;
  }

  void  set(int p1, int q1, int p2, int q2) {
        x1 = p1; y1 = q1;
        x2 = p2; y2 = q2;
  }
};

}

