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
 *  ColorMixer.h
 *
 *****************************************************************************/


// SOL++2000 
// 1999.09.23 Modified
// 2000.02.18

// 2009/10/11 Updated.

#pragma once

#include <sol\Composite.h>
#include <sol\Brush.h>

#include <sol\Static.h>
#include <sol\ScrollBar.h>
#include <sol\ColorBox.h>
#include <sol\ClientDC.h>

namespace SOL {

#define WM_COLORCHANGED (WM_USER+2012)

class ColorMixer :public Composite {
private:

  Static    value[3];
  ScrollBar scrollbar[3];
  ColorBox  colorbox;

  HBRUSH hRed;
  HBRUSH hGreen;
  HBRUSH hBlue;

private:
  void scrolled(Action& action)
  {
    ScrollBar* scroll = (ScrollBar*)action.getData();
    TCHAR  label[128];
    scroll ->getText(label, CountOf(label));
    TCHAR  buffer[10];
    _stprintf_s(buffer, CountOf(buffer), _T("%s%02x"), label, scroll->getPos());

    for(int i = 0; i<3; i++) {
      if(scroll == &scrollbar[i]) {
        value[i].setText(buffer);
        break;
      }
    }
    int r = scrollbar[0].getPos();
    int g = scrollbar[1].getPos();
    int b = scrollbar[2].getPos();
    colorbox.setColor(RGB(r, g, b));
    View* parent = getParent();
    if (parent) {
      parent->post(WM_COLORCHANGED, 0, RGB(r,g,b));
    }
  }

private:
  long colorScrollBar(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();
    HDC hdc = (HDC)event.getWParam();
    //SetBkMode(hdc, TRANSPARENT ); 

    if (hwnd == scrollbar[0].getWindow()) {
      return (long)hRed;
    }

    if (hwnd == scrollbar[1].getWindow()) {
      return (long)hGreen;
    }

    if (hwnd == scrollbar[2].getWindow()) {
      return (long)hBlue;
    }

    return NULL;
  }

private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);

    ClientDC cdc(this);
    Size size;
    cdc.getTextExtent(_T("A"), 1, &size);
    int h1 = size.cy;

    for(int i = 0; i<3; i++) {
      scrollbar[i].reshape(30, 10+(h1+10)*i, w*4/5-10, h1);
      value[i]    .reshape(22+w*4/5, 10+(h1+10)*i, w*1/5-10, h1);
    }
    colorbox.reshape(30, 10+(h1+10)*3, w*4/5-10, h - h1*3-50);

    return 0L;
  }

public:
  ColorMixer()
    :Composite()
  {
    hRed   = NULL;
    hGreen = NULL;
    hBlue  = NULL;
  }

public:
  /**
   * Constructor
   */
  ColorMixer(View* parent, const TCHAR* caption, Args& args)
  :Composite()
  {
    create(parent, caption, args);
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, args.set(XmNstyle, WS_BORDER|WS_CHILD|WS_VISIBLE)
      .set(XmNclassName, _T("_ColorMixer_"))
      .set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
      .set(XmNbackground, (COLOR_BTNFACE+1)));

    TCHAR name[20];
    static TCHAR* names[] = {_T("R="),_T( "G="), _T("B=")};

    Args ar;
    for(int i = 0; i<3; i++) {
      _stprintf_s(name, CountOf(name), names[i], 0);
      ar.reset();
      ar.set(XmNstyle, (LONG_PTR)SS_LEFT);
      value[i].create(this, name, ar);
      ar.reset();
      ar.set(XmNminimum,   0);
      ar.set(XmNmaximum, 255);
      ar.set(XmNstyle,   (LONG_PTR)SBS_HORZ|WS_EX_CONTROLPARENT);
      scrollbar[i].create(this, names[i], ar);
      TCHAR val[128];
      _stprintf_s(val, CountOf(val),_T("%s%02x"),  names[i], 0);
      value[i].setText(val);

      scrollbar[i].addCallback(XmNhorizScrollCallback, this,
        (Callback)&ColorMixer::scrolled, &scrollbar[i]);
    }
    ar.reset();
    colorbox.create(this, _T(""), ar);
    addEventHandler(WM_CTLCOLORSCROLLBAR, this, (Handler)&ColorMixer::colorScrollBar, NULL);

    hRed   = CreateSolidBrush(RGB(0xff,00,00));  
    hGreen = CreateSolidBrush(RGB(00,0xff,00));
    hBlue  = CreateSolidBrush(RGB(00,00,0xff));
    
    return rc;
  }
public:
  ~ColorMixer()
  {
    if (hRed) DeleteObject(hRed);
    if (hGreen) DeleteObject(hGreen);
    if (hBlue) DeleteObject(hBlue);

  }

};

}
