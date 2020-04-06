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
 *  Column.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once
#include <sol\Composite.h>
#include <sol\ClientDC.h>

namespace SOL {

class Column :public Composite {
private:
  int    margin;
  int    spacing;
  int    column;
  int    labelWidth;

protected:
  long  size(Event& event)
  {
    LPARAM lParam = event.getLParam();
    int  w = LOWORD(lParam);
  //int  h = HIWORD(lParam);

    ClientDC cdc(this);
    TCHAR*  label = _T("A");

    SIZE size;
    cdc.getTextExtent(label, strlen(label), &size);
    int  ch = size.cy * 3/2; 

    int  num = 0;
    int  x = margin;
    int  y = margin;

    HWND self = getWindow();
    HWND child = ::GetWindow(self, GW_CHILD);
    TCHAR  text[1024];
    if (labelWidth == 0) {
      while(child) {
        if((num % 2) == 0) {
          ::GetWindowText(child, text, CountOf(text)); //2012/06/21
          SIZE size; 
          cdc.getTextExtent(text, strlen(text), &size);
          if(size.cx >= (WORD)labelWidth) 
            labelWidth = size.cx;
        }
        child = ::GetWindow(child, GW_HWNDNEXT);
        num++;
      }
      labelWidth = labelWidth+2*margin;
    }

    child = ::GetWindow(self, GW_CHILD);
    num = 0;
    int res;
    int ss;
    x = margin;
    while(child) {
      res = num % column;
      if(num >0 && res == 0) {
        y = y + ch + spacing;
      }
      if(res == 0) {
        x = margin;
        ss = labelWidth-margin;
      }
      if(res == 1) {
        x = labelWidth+margin;
        ss = w - x - margin;
      }
//    x = margin + cw * (num % column);
      ::MoveWindow(child, x, y, ss, ch, FALSE);
      child = ::GetWindow(child, GW_HWNDNEXT);
      num++;
    }

    update(NULL);
    return NULL;
}

public:
  Column():Composite() { }

public:
  //2012/06/22
  Column(View* parent, const TCHAR* name, Args& args)
  :Composite()
  {
    create(parent, name, args)
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name, 
      args.set(XmNclassStyle, NULL)
        .set(XmNclassName, _T("Column")));

    margin  = 4;
    spacing = 4;
    column  = 2;
    addEventHandler(WM_SIZE, this,
      (Handler)&Column::size, NULL);
    labelWidth = 0;
    setValues(args);

    return rc;
  }

public:
  void  setValues(Args& args)
  {
    LONG_PTR  val;
    if (args.get(XmNmargin, &val))
      margin = (int)val;
    if (args.get(XmNspacing, &val))
      spacing = (int)val;
    if (args.get(XmNcolumn, &val))
      column = (int)val;
  }

};

}


