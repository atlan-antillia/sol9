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
 *  GradientLabelGadget.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/01
// 2012/06/30

#pragma once

#include <sol\PaintDC.h>
#include <sol\Brush.h>
#include <sol\StockObject.h>
#include <sol\Pen.h>
#include <sol\ClientDC.h>
#include <sol\Font.h>

#include <sol\Gadget.h>
#include <sol\String.h>


namespace SOL {

class GradientLabelGadget :public Gadget {
private:
  //char*   text;
  String   text;
  Font*   font;

  COLORREF textColor;
  int     margin;
  
  UINT   alignment; // for API DrawText 

private:
  int    baseColor;
  int    width;
  int    height;

public:
  enum {GRADIENT_BASECOLOR_RED, 
    GRADIENT_BASECOLOR_GREEN, 
    GRADIENT_BASECOLOR_BLUE} GradientBaseColorType;

public:
  GradientLabelGadget(): Gadget() {
    //text = NULL;
    font = NULL;

    textColor=0;
    margin =0;

    baseColor =0;
    width = 0;
    height =0;
  
  }

public:
  //2012/06/22
  GradientLabelGadget(View* parent, const TCHAR* label, Args& args)
    :Gadget()
  {
    create(parent, label, args);
  }

public:
  /**
   */
  ~GradientLabelGadget() {
  }


public:
  Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    int margin = 4;
    setMargin(margin);

    int width = 0;
    int height = 0;

    font   = NULL;

    Boolean rc = Gadget::create(parent, label, args); 

    textColor = ::GetSysColor(COLOR_BTNTEXT);


    alignment = 0;

    const TCHAR* ptr = (const TCHAR*)args.get(XmNlabelString);
    if(ptr == NULL) {
      ptr = label;           
    }
    if(ptr == NULL) {
      ptr = _T("");
    }
    this->text = ptr;
  
    ClientDC dc(parent);

    if (args.get(XmNwidth) == 0 || args.get(XmNheight) == 0) {
      HGDIOBJ hfont = NULL;
      if(font) {
        hfont = dc.select(font);
      } else {
        View* parent = getParent();
        if (parent) {
          Font* dfont = parent->getFont();

          if (dfont) {
            hfont = dc.select(dfont);
          }
        }
      }
      const TCHAR* ctext = (const TCHAR*)text;
      RECT r;
      dc.drawText(ctext, strlen(ctext), &r, DT_CALCRECT);
      
      width = r.right - r.left;
      height = r.bottom - r.top;

      if (hfont) {
        dc.select(hfont);
      }
    }
    this->baseColor = GRADIENT_BASECOLOR_BLUE;

    LONG_PTR color = 0;
    if (args.get(XmNgradientBaseColor, &color)) {
      this->baseColor = (int)color;
    }
    if (!(this->baseColor ==GRADIENT_BASECOLOR_RED ||
      this->baseColor ==GRADIENT_BASECOLOR_GREEN ||
      this->baseColor ==GRADIENT_BASECOLOR_BLUE)) {

      this->baseColor = GRADIENT_BASECOLOR_BLUE;
    }


    if (width<255) {
      width = 255;
    }
    
    //2012/06/30
    LONG_PTR ww = 0;
    if (args.get(XmNwidth, &ww)) {
      width = (int)ww;
    }

    //2012/06/30
    LONG_PTR hh = 0;
    if (args.get(XmNheight, &hh)) {
      height = (int)hh;
    }

    //2012/06/30
    LONG_PTR al = 0;
    if (args.get(XmNtextAlignment, &al)) {
      alignment = (int)al;
    }

    setSize(width+margin*2, height+margin*2);

    return rc;
  }


public:
  void draw(DC* dc)
  {
    draw(dc, 0, 0);
  }


public:
  void draw(DC* cdc, int x, int y)
  {
    cdc->setBkMode(TRANSPARENT);
    StockObject pen(NULL_PEN);
    cdc->select(&pen);

    //hfont = a previous original font-handle
    HGDIOBJ hfont = NULL;
    if(font) {
      hfont = cdc->select(font);
    } else {
      View* parent = getParent();
      if (parent) {
        Font* dfont = parent->getFont();

        if (dfont) {
          hfont = cdc->select(dfont);
        }
      }
    }

    int width, height;
    getSize(width, height);

    cdc -> setTextColor(textColor);

    const TCHAR* ctext = (const TCHAR*)text;
    RECT r;
    cdc->drawText(ctext, strlen(ctext), &r, DT_CALCRECT);
    int w  = r.right - r.left;
    int h  = r.bottom - r.top;

    if (w >width) {
      width = w;
    }

    //2012/06/30
    if (h >height) {
      height = h;
    }

    float p = (float)width/255.0;//+1; 2012/06/30
  
    for(int i = 0; i < 255; i++) {
      Brush* brush = NULL;
      if (baseColor==GRADIENT_BASECOLOR_RED) {
        brush = new Brush(RGB(255, 128+i/2,128+i/2) );
      }

      if (baseColor==GRADIENT_BASECOLOR_GREEN) {
        brush = new Brush(RGB(128+i/2, 255, 128+i/2) );
      }

      if (baseColor==GRADIENT_BASECOLOR_BLUE) {
        brush = new Brush(RGB(128+i/2, 128+i/2, 255) );
      }

      HGDIOBJ prev = cdc->select(brush);
      //cdc->rectangle(x+(int)((float)i*p), y, x+20+(int)((float)i*p), y+ h+ margin*2);
      cdc->rectangle(x+(int)((float)i*p), y, x+20+(int)((float)i*p), y+ height+ margin*2);

      cdc->select(prev);
      delete brush;
    }


    r.left  = x + margin;
    r.right = r.left + width+margin*2;
    r.top   = y + margin;
    //r.bottom = r.top  + h +margin*2;
    //r.bottom = r.top  + height +margin*2;
    r.bottom = r.top  + height +margin;
    cdc->drawText(ctext, strlen(ctext), &r, alignment);

    if(hfont) {
      //back to original hfont
      cdc->select(hfont);
    }
  }


  void  setHighLightTextColor() { 
    textColor = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
  }

  void  setMargin(int val) { 
    margin = val; 
  }

  void  setFont(Font* f) { 
    font = f; 
  }

  void  setFont(Font& f) { 
    font = &f; 
  }

};

}

