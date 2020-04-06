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
 *  RowColumn.h
 *
 *****************************************************************************/

//2017/10/03 Updated.

#pragma once

#include <sol\Composite.h>
#include <sol\ClientDC.h>

namespace SOL {

class RowColumn :public Composite {
private:
  static const long STYLE = WS_CHILD|WS_VISIBLE;

private:
  int    margin;
  int    spacing;
  int    column;

public:
  static const int HORIZ_ORIENTATION = 0;
  static const int VERT_ORIENTATION  = 1;
  
protected:
  long size(Event& event)
  {
    LPARAM lParam = event.getLParam();
    int  w = LOWORD(lParam);
    int  h = HIWORD(lParam);
    //Modified to call a virtual resize method.
    resize(w, h);
    return 0;
  }
  
  //Please define your own resize method in a subclass derived from this class.
  virtual void resize(int w, int h)
  {
    ClientDC cdc(this);
    char*  label = "A";
    Size size;
    cdc.getTextExtent(label, strlen(label), &size);
    int  ch = size.cy*3/2;

    int  cw = (w-margin)/column;

    int  num = 0;
    int  x = margin;
    int  y = margin;

    HWND self = getWindow();
    HWND child = ::GetWindow(self, GW_CHILD);
    while(child) {
      if(num >0 && (num%column)== 0) {
        y = y + ch + spacing;
      }
      x = margin + cw * (num % column);
      ::MoveWindow(child, x, y, cw-margin, ch, FALSE);
      child = ::GetWindow(child, GW_HWNDNEXT);
      num++;
    }
    update();
  }

  int    getMargin() { return margin;  }

  int    getSpacing(){ return spacing; }

  int    getColumn() { return column;  }

public:
    RowColumn():Composite() { }

public:
  RowColumn(View* parent)
    :Composite(parent) { }
  

public:
  //2012/06/25
  RowColumn(View* parent, const TCHAR* name, Args& args)
  :Composite()
  {
    create(parent, name, args);
  }

public:
  ~RowColumn() { }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name, 
      args.set(XmNclassStyle, NULL)
        .set(XmNstyle, (LONG_PTR)STYLE)
        .set(XmNclassName, _T("RowColumn") ));

    margin  = 4;
    spacing = 4;
    column  = 2;
    addEventHandler(WM_SIZE, this,
      (Handler)&RowColumn::size, NULL);
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

