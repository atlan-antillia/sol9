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
 *  GradientBar.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>
#include <sol\PaintDC.h>
#include <sol\Pen.h>
#include <sol\MessageFont.h>

namespace SOL {

class GradientToolBar :public Primitive {
private:
  int  background;
  int contrast;
public:
  enum BACKGROUND {
    LIGHT_GRAY,
    LIGHT_BLUE, 
    LIGHT_PINK,
    LIGHT_YELLOW,
    LIGHT_GREEN,
  };

protected:
  long  paint(Event& event)
  {
    PaintDC pdc(this);
    RECT r;
    getClientRect(&r);
    int width = r.right - r.left;
    int height = r.bottom - r.top;

    float p = (float)height/255.0;
  
    for(int i = 0; i <0xff; i++) {
      COLORREF color;

      if (background == LIGHT_GRAY) {
          color = RGB(0xff-i/contrast, 0xff-i/contrast, 0xff-i/contrast);
      }
      
      if (background == LIGHT_GREEN) {
          color = RGB(0, 0xff-i/contrast, 0);
      }
      
      if (background == LIGHT_YELLOW) {
        color = RGB(0xff, 0xff, 0xff-i/contrast);
      }

      if (background == LIGHT_BLUE) {
        color = RGB(0xff-i/contrast, 0xff-i/contrast,  0xff);
      }
      if (background == LIGHT_PINK) {
          color = RGB(0xff, 0xff-i/contrast, 0xff-i/contrast);
      }
      Pen pen(PS_SOLID, (int)p+4, color ); 

      HGDIOBJ prev = pdc.select(&pen);

      pdc.moveTo(0, (int)((float)i*p), NULL);
      pdc.lineTo(width, (int)((float)i*p));

      pdc.select(prev);    
    }

    return 0;
  }

public:
  GradientToolBar(): Primitive() { }

public:
  //2012/06/25
  GradientToolBar(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, 
      const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
        args.set(XmNclassName, _T("_GradientToolBar__"))
            .set(XmNbackground, (LONG_PTR)GetStockObject(NULL_BRUSH)) );
    
    background = LIGHT_BLUE;

    LONG_PTR val;
    if (args.get(XmNgradientColor, &val)) {
      background = val;
    }
  
    contrast = 6;

    if (args.get(XmNgradientContrast, &val)) {
      if (val>2) {
        contrast = val;
      }
    }
    addEventHandler(WM_PAINT, this,
      (Handler)&GradientToolBar::paint, NULL);
  
    setValues(args);

    return rc;
  }

public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }


};

}

