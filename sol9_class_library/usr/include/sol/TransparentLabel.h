/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  TransparentLabel.h
 *
 *****************************************************************************/

//2016/11/12 

#pragma once

#include <sol\Primitive.h>
#include <sol\PaintDC.h>
#include <sol\MessageFont.h>
#include <sol\Brush.h>

namespace SOL {

class TransparentLabel :public Primitive {
private:
  MessageFont mfont;
  int         margin;
  COLORREF    color; 
  UINT        alignment;
  //2012/07/05
  bool        enabled;
  int         delta;

protected:
  long  paint(Event& event)
  {
    PaintDC pdc(this);

    const TCHAR* text = getText();
    if (text) {

      RECT r;
      getClientRect(&r);

      HFONT hfont = (HFONT)pdc.select((HFONT)mfont);

      pdc.setBkMode(TRANSPARENT);
      if (enabled) {
        pdc.setTextColor(color);
      } else {
        pdc.setTextColor(RGB(128, 128, 128));
      }

      RECT rr;
      pdc.drawText(text, strlen(text), &rr, DT_CALCRECT);
    
      int width = rr.right - rr.left;
      int height = rr.bottom - rr.top;
      int th = pdc.getTextHeight();
      
      r.left += margin;
      r.top  += margin;
      r.right -= margin*2;
      r.bottom -= margin*2;
      
      r.top = r.top + (r.bottom - r.top - height)/2;

      r.top  += delta;
      r.left += delta;

      pdc.drawText(text, strlen(text), &r, alignment);

      pdc.select(hfont);
    }
    return 0;
  }

public:
  TransparentLabel(): Primitive() { }

public:
  TransparentLabel(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, 
      const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
        args.set(XmNclassName, _T("_TransparentLabel_"))
            .set(XmNexStyle,   (LONG_PTR)WS_EX_TRANSPARENT) 
            .set(XmNbackground, (LONG_PTR)GetStockObject(NULL_BRUSH)) );
    
    mfont.create();
    margin = 4;
    //Default color is gray.
    color = RGB(0xff/2, 0xff/2, 0xff/2);
    LONG_PTR val;
    if (args.get(XmNtextColor, &val)) {
      color = val;
    }

    alignment = DT_CENTER;
    if (args.get(XmNtextAlignment, &val)) {
      alignment = val;
    }

    addEventHandler(WM_PAINT, this,
      (Handler)&TransparentLabel::paint, NULL);

    setValues(args);

    enabled = true;
    delta = 0;

    return rc;
  }

  void setTextColor(COLORREF c)
  {
    color = c;
    invalidateAll();
    update();
  }

};

}

