/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ColorChooser.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2012/06/11

#pragma once

#include <sol\Composite.h>
#include <sol\PaintDC.h>
#include <sol\Static.h>

#include <sol\ClientDC.h>
#include <sol\DIBSection.h>

namespace SOL {

#define WM_COLORCHOOSER_PICKED (WM_USER+1899)

class ColorChooser :public Composite {

private:
  static const int WM_CREATE_COLORS =  (WM_USER+200);
  static const int CHOOSER_SIZE = 284;
  static const int POSITION     = 10;
  Static     value;
  Static     color;

  DIBSection colorSpace;
  int       num;
  COLORREF   rgb;

private:
  long  createColors(Event& event) {
    ClientDC cdc(this);
    
    num = 128;//256/2;
    colorSpace.create(cdc, num*2, num*2);
    colorSpace.clear();

    for (int r = 0; r<num; r++) {
      for(int g = 0; g<num; g++) {
        for(int b = 0; b<num; b++) {
          colorSpace.setPixel(b + r,g + r, RGB(2*r, 2*g, 2*b));
        }
      }
    }
    return 0;
  }

public:
  void  move(int x, int y, int width, int height, Boolean flag = TRUE) 
  {
    reshape(x, y, width, height, flag);
  }

public:
  void reshape(int x, int y, int width, int height, Boolean flag=True)
  {
    if (width< CHOOSER_SIZE) {
      width = CHOOSER_SIZE;
    }

    if (height< CHOOSER_SIZE) {
      height = CHOOSER_SIZE;
    }

    Composite::reshape(x, y, width, height, flag);
  }

private:
  long paint(Event& event)
  {
    PaintDC pdc(this);
    colorSpace.draw(pdc, POSITION, POSITION);
    return 0;
  }

private:
  void setRGBValue(COLORREF rgb)
  {
    int r = GetRValue(rgb);
    int g = GetGValue(rgb);
    int b = GetBValue(rgb);
    TCHAR name[128];
    _stprintf_s(name, CountOf(name), _T("RGB(%02X,%02X,%02X)"), r, g, b);
    value.setText(name);
  }

 private:
  long leftButtonDown(Event& event)
  {
    POINT p;
    event.getMousePosition(&p);

    if (p.x >= POSITION && p.y >= POSITION && p.x <= POSITION+num*2 && p.y <= POSITION+num*2) {
      this->rgb = colorSpace.getPixel(p.x - POSITION, p.y - POSITION);
      setRGBValue(this->rgb);

      color.update(NULL);
      View* parent = getParent();
      if (parent) {
        parent->post(WM_COLORCHOOSER_PICKED, (WPARAM)getWindow(), (LPARAM)rgb);
      }
    }
    return 0;
  }

public:
  ColorChooser()
    :Composite()
  {
  }

public:
  /**
   * Constructor
   */
  ColorChooser(View* parent, const TCHAR* label, Args& args)
    :Composite()
  {
    create(parent, label, args);
  }

public:
  Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = Composite::create(parent, label, 
      args.set(XmNstyle, WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS) //2016/12/10
        .set(XmNwidth, CHOOSER_SIZE)
        .set(XmNheight, CHOOSER_SIZE)
        .set(XmNbackground, (COLOR_BTNFACE +1))
        .set(XmNclassName, _T("_ColorChooser_")));

    ClientDC dc(this);
    int h = dc.getTextHeight();
    Args ar;

    ar.set(XmNx, 4);
    ar.set(XmNy, 2+128*2+4);
    ar.set(XmNwidth,  120);
    ar.set(XmNheight,  h);
    //ar.set(XmNstyle, (LONG_PTR)SS_OWNERDRAW);
    value.create(this, NULL, ar);
    
    ar.reset();
    ar.set(XmNx, 2+128);
    ar.set(XmNy, 2+128*2+6);
    ar.set(XmNwidth,  128);
    ar.set(XmNheight,  h);
    ar.set(XmNstyle, (LONG_PTR)SS_OWNERDRAW);
    color.create(this, NULL, ar);

    this->rgb = RGB(255, 255, 255);
    setRGBValue(this->rgb);

    addEventHandler(WM_PAINT, this, 
      (Handler)&ColorChooser::paint, NULL);
    addEventHandler(WM_CREATE_COLORS, this, 
      (Handler)&ColorChooser::createColors, NULL);

    addEventHandler(WM_LBUTTONDOWN, this, 
      (Handler)&ColorChooser::leftButtonDown, NULL);

    addEventHandler(WM_DRAWITEM, this, 
      (Handler)&ColorChooser::drawItem, NULL);

    post(WM_CREATE_COLORS, 0, 0);
    return rc;
  }

public:
  COLORREF getCurrentColor()
  {
    return this->rgb;
  }

private:

  long drawItem(Event& event)
  {
    LPARAM lParam = event.getLParam();
    DRAWITEMSTRUCT* ptr = (DRAWITEMSTRUCT*)lParam;

    HDC hdc = ptr->hDC;
    RECT r = ptr->rcItem;

    HBRUSH hb = CreateSolidBrush(rgb);
    HBRUSH oldb = (HBRUSH)SelectObject(hdc, hb);
    Rectangle(hdc, r.left, r.top, r.right-r.left, r.bottom-r.top);

    SelectObject(hdc, oldb);
    DeleteObject(hb);

    return 0L;
  }
};

}

