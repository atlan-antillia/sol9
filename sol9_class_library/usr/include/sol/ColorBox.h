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
 *  ColorBox.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/05/22

#pragma once

#include <sol\Primitive.h>
#include <sol\PaintDC.h>
#include <sol\Pen.h>


namespace SOL {

class ColorBox :public Primitive {

private:
  int   width;
  COLORREF color;

  long paint(Event& event) 
  {
    RECT r;
    getClientRect(&r);
    PaintDC pdc(this);
    Pen pen(PS_INSIDEFRAME, width, color);

    pdc.select(&pen);
    pdc.rectangle(0, 0, r.right - r.left, r.bottom - r.top);

    return NULL;
  }

public:
  ColorBox():Primitive() { }

public:
  //2012/06/22
  ColorBox(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNclassName, _T("ColorBox")));

    color = 0;
    width = 1000;
    addEventHandler(WM_PAINT, this,
      (Handler)&ColorBox::paint, NULL);

    return rc;
  }

public:
  void setColor(COLORREF color1) 
  {
    color = color1;
    invalidateAll();
    update();
  }

  void set(const TCHAR* name, COLORREF rgb)
  {
    if (name == XmNrgbColor) {
      setColor(rgb);
    }
  }
  
  void  setWidth(int width1) { width = width1; }
};

}


