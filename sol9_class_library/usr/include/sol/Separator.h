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
 *  Separator.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>
#include <sol\PaintDC.h>
#include <sol\Pen.h>
#include <sol\Brush.h>
#include <sol\StockObject.h>

namespace SOL {

class Separator :public Primitive {

protected:
  long paint(Event& event)
  {
    PaintDC pdc(this);
    int x, y, w, h;
    getGeometry(x, y, w, h);

    int val = pdc.save();

    StockObject NULLPen(NULL_PEN);
    pdc.select(&NULLPen);

    Brush btnFace(::GetSysColor(COLOR_BTNFACE));
    pdc.select(&btnFace);

    pdc.rectangle(0, 0, w+1, h+1);

    Pen shadowPen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
    pdc.select(&shadowPen);

    pdc.moveTo(0,   h/2, NULL);
    pdc.lineTo(w+1, h/2);

    Pen colorPen(PS_SOLID, 1, ::GetSysColor(COLOR_WINDOW));
    pdc.select(&colorPen);

    pdc.moveTo(0,   1+h/2, NULL);
    pdc.lineTo(w+1, 1+h/2);

    pdc.restore(val);

    return NULL;
  }

 
public:
  Separator(): Primitive()  { }

public:
  Separator(View* parent, const TCHAR* label, Args& args)
  :Primitive()
  {
    create(parent, label, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = Primitive::create(parent, label, args);

    addEventHandler(WM_PAINT, this,
      (Handler)&Separator::paint, NULL);
    setValues(args);
    return rc;
  }

  BOOL  hasCallback() { return FALSE; }
};

}


