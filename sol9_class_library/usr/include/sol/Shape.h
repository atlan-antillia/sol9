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
 *  Shape.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\Object.h>
#include <sol\DC.h>
#include <sol\Pen.h>
#include <sol\Brush.h>
#include <sol\StockObject.h>

namespace SOL {

class Shape :public Object {
private:
  int   borderWidth;
  COLORREF border;
  COLORREF back;
  BOOL   filled;
 
public:
  Shape() {
    borderWidth = 1;
    filled = TRUE;
    back   = RGB(255, 255, 255);
    border = RGB(0,  0, 0);
  }

  virtual void draw(DC* dc) { filled = TRUE; };

  virtual void draw(DC* dc, int x, int y) { }

  virtual void move(int x, int y) { }

  int       getBorderWidth() { return borderWidth; }

  COLORREF     getBorderColor() { return border; }

  COLORREF     getBackColor() { return back; }

  BOOL       getFillMode() { return filled; }

  void       setFillMode(BOOL flag) { filled = flag; }

  void       setBorderColor(COLORREF bd) { border = bd; }

  void       setBorderWidth(int w) { borderWidth = w; }

  void       setBackColor(COLORREF bc) { back = bc; }
};

}


