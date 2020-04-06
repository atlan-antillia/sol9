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
 *  Positioner.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Composite.h>

#include <sol/Static.h>
#include <sol/ScrollBar.h>

namespace SOL {

//Default positionChangedMessage

#define WM_POSITIONCHANGED (WM_USER+2016)

class Positioner :public Composite {
private:
  Static    label;
  Static    value[3];
  ScrollBar scrollbar[3];

  UINT positionChangedMessage;

  static const int DEFAULT_WIDTH  = 290;
  static const int DEFAULT_HEIGHT = 120;
  
private:
  void scrolled(Action& action)
  {
    ScrollBar* scroll = (ScrollBar*)action.getData();
    TCHAR  label[128];
    scroll ->getText(label, CountOf(label));
    TCHAR  buffer[10];
    _stprintf_s(buffer, CountOf(buffer),_T("%s%d"), label, scroll->getPos());

    for(int i = 0; i<3; i++) {
      if(scroll == &scrollbar[i]) {
        value[i].setText(buffer);
        break;
      }
    }
    View* parent = getParent();
    if (parent) {
      parent->post(positionChangedMessage, getId(), (LPARAM)this); //2017/10/10
    }
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
    label.reshape(2, 2, w-4, 30);
    int top = 32;

    for(int i = 0; i<3; i++) {
      scrollbar[i].reshape(10,       top+(h1+10)*i, w*4/5-10, h1);
      value[i]    .reshape(10+w*4/5, top+(h1+10)*i, w*1/5-10, h1);
    }

    return 0L;
  }

  
public:
  Positioner()
    :Composite(),
  positionChangedMessage(WM_POSITIONCHANGED)
  {
  }

public:
  /**
   * Constructor
   */
  Positioner(View* parent, const TCHAR* caption, Args& args)
  :Composite(),
  positionChangedMessage(WM_POSITIONCHANGED)
  {
    create(parent, caption, args);
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, args.set(XmNstyle, WS_BORDER|WS_CHILD|WS_VISIBLE)
      .set(XmNclassName, _T("_Positioner_"))
    //  .set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
      .set(XmNbackground, (COLOR_BTNFACE+1)));

    TCHAR name[20];
    static TCHAR* names[] = {_T("X="),_T( "Y="), _T("Z=")};


    Args ar;
    TCHAR* title = _T("Positioner");
    TCHAR* string = (TCHAR*)args.get(XmNlabelString); 
    if (string) {
      title = string;
    }

    label.create(this, title, ar);

    int min = args.get(XmNminimum);
    int max = args.get(XmNmaximum);
    if (max == 0) {
      max = 128;
    }
    for(int i = 0; i<3; i++) {
      _stprintf_s(name, CountOf(name), names[i], 0);
      ar.reset();
      ar.set(XmNstyle, (LONG_PTR)SS_LEFT);
      value[i].create(this, name, ar);
      ar.reset();
      ar.set(XmNminimum, min);
      ar.set(XmNmaximum, max);
      ar.set(XmNstyle,   (LONG_PTR)SBS_HORZ|WS_EX_CONTROLPARENT);
      scrollbar[i].create(this, names[i], ar);
      TCHAR val[128];
      _stprintf_s(val, CountOf(val), _T("%s%d"),  names[i], 0);
      value[i].setText(val);

      scrollbar[i].addCallback(XmNhorizScrollCallback, this,
        (Callback)&Positioner::scrolled, &scrollbar[i]);
    }
    ar.reset();
    return rc;
  }
  
public:
  ~Positioner()
  {
  }

  UINT getPositionChangedMessage()
  {
    return positionChangedMessage;
  }

  void setPositionChangedMessage(UINT message)
  {
    positionChangedMessage = message;
  }

  void getThumPosition(int& x, int& y, int& z)
  {
    x = getX();
    y = getY();
    z = getZ();
  }
  
  int getX()
  {
    return scrollbar[0].getPos();
  }

  int getY()
  {
    return scrollbar[1].getPos();
  }

  int getZ()
  {
    return scrollbar[2].getPos();
  }
  
  static int getDefaultWidth()
  {
    return DEFAULT_WIDTH; 
  }
  
  static int getDefaultHeight()
  {
    return DEFAULT_HEIGHT; 
  }

  void setXPos(int pos)
  {
    scrollbar[0].setPos(pos);
  }
  
  void setYPos(int pos)
  {
    scrollbar[1].setPos(pos);
  }

  void setZPos(int pos)
  {
    scrollbar[2].setPos(pos);    
  }
  
  void setThumbPosition(int x, int y, int z)
  {
    setXPos(x);
    setYPos(y);
    setZPos(z);
    TCHAR  label[128];
    const int val[] = {x, y, z};
    
   for (int i = 0; i<3; i++) {
    scrollbar[i].getText(label, CountOf(label));
    TCHAR  buffer[10];
    _stprintf_s(buffer, CountOf(buffer), _T("%s%d"), label, val[i]);
    
    value[i].setText(buffer);
   } 
  }

  void setXValues(Args& args)
  {
    scrollbar[0].setValues(args);
  }

  void setYValues(Args& args)
  {
    scrollbar[1].setValues(args);
  }

  void setZValues(Args& args)
  {
    scrollbar[2].setValues(args);
  }

  HWND getScrollBarWindow(int index)
  {
    if (index >= 0 && index<3) {
      return scrollbar[index].getWindow();
    } else {
      throw IException("Invalid index");
    }
  }
 
  void setScrollBarText(int index, const TCHAR* text)
  {
    if (index >= 0 && index<3) {
      scrollbar[index].setText(text);
    } else {
      throw IException("Invalid index");
    }    
  }
  
};

}
