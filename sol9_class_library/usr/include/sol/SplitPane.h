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
 *  SplitPane.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Composite.h>
#include <sol\Sash.h>
#include <sol\ClientDC.h>

namespace SOL {

class SplitPane :public Composite {
private:
  int    direction;

  Sash  sash;
  View*  first;
  View*  second;
  int    position;

private:
  void arrange(Action& action)
  {
    RECT rec;
    getClientRect(&rec);
    int w = rec.right;
    int h = rec.bottom;

    RECT r;
    sash.getWindowRect(&r);
    POINT p;
    p.x = r.left;
    p.y = r.top;
    ::ScreenToClient(getWindow(), &p);

    int thickness = sash.getThickness();

    if (direction == VERTICAL) {
      position = p.y;

      if(first) {
        first -> reshape(0, 0, w, position);
      }

      sash.reshape(0, position, w, thickness);
      if(second) {
        //<added date="2000.07.03">
        second -> update();
        //</added>
        second -> reshape(0, position+thickness, 
          w, h-position-thickness);
      }
    }

    if (direction == HORIZONTAL) {
      position = p.x;
      if(first) {
        first -> reshape(0, 0, position, h);
      }

      sash.reshape(position, 0, thickness, h);
      if(second) {
        //<added date="2000.07.03">
        second -> update(NULL);
        //</added>
        second -> reshape(position+thickness, 0, 
          w-position-thickness, h);
      }
    }
  }

private:
  long  size(Event& event)
  {
    RECT   rec;
    getClientRect(&rec);
    int w = rec.right;
    int h = rec.bottom;

    int thickness = sash.getThickness();

    RECT cr;
    sash.getClientRect(&cr);
    int pos = 0;

    if (direction == VERTICAL) {
      if (position - 10> h) {
        pos = h - thickness;
        if(first) {
          first -> reshape(0, 0, w, pos);
        }
        sash.reshape(0, pos, w, thickness);
        if(second) {
          second->reshape(0, pos+thickness, w, 2);
        }
      }
      else {
        if(first) {
          //first -> reshape(0, 0, w, position);
          first -> reshape(0, 0, position, w);

        }
        sash.reshape(0, position, w, thickness);
        if(second) {
          second -> reshape(0, position+thickness, 
            w, h-position-thickness);
        }
      }
    }

    if (direction == HORIZONTAL) {
      if (position - 10> w) {
        pos = w - thickness;
        if(first) {
          first -> reshape(0, 0, pos, h);
        }
        sash.reshape(pos, 0, thickness, h);
        if(second) {
          second->reshape(pos+thickness, 0, 2, h);
        }
      }
      else {
        if(first) {
          first -> reshape(0, 0, position, h);
        }
        sash.reshape(position, 0, thickness, h);
        if(second) {
          second -> reshape(position+thickness, 0, 
            w-position-thickness, h);
        }
      }
    }
    //2009/11/16
    if (first) {
      first->update();
    }
    if (second) {
      second->update();
    }
    return NULL;
  }
  
public:
  static const int VERTICAL   = 0;
  static const int HORIZONTAL = 1;
  
public:
  SplitPane():Composite() { }

public:
  //2012/06/25
  SplitPane(View* parent, const TCHAR* label, Args& args)
  :Composite()
  {
    create(parent, label, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = Composite::create(parent, label, 
      args.set(XmNstyle, (LONG_PTR)(WS_VISIBLE|WS_CHILD) )
          .set(XmNclassName, _T("SplitPane"))
        .set(XmNclassStyle, 0));

    first  = NULL;
    second = NULL;
    //RECT r;
    //getClientRect(&r);
    position = 80;

    direction   = VERTICAL;
    LONG_PTR val = 0;
    if (args.get(XmNdirection, &val)) {
      direction = (int)val;
    }

    int dir = Sash::VERTICAL;
    HCURSOR cursor = LoadCursor(NULL, IDC_SIZENS);
    if (direction == HORIZONTAL) {
      dir = Sash::HORIZONTAL;
      cursor = LoadCursor(NULL, IDC_SIZEWE);
    }

    Args ar;
    ar.set(XmNdirection, dir);
    ar.set(XmNcursor, (LONG_PTR)cursor);
    sash.create(this, _T(""), ar);
    sash.addCallback(XmNdragFinishedCallback, this,
      (Callback)&SplitPane::arrange, NULL);

    addEventHandler(WM_SIZE, this, 
      (Handler)&SplitPane::size, NULL);

    setValues(args);
    return rc;
  }

public:
  void add(View* view1)
  {
    if(first == NULL) {
      first = view1;
    }
    else {
      second = view1;
    }
    RECT  rc;
    getClientRect(&rc);
    send(WM_SIZE, 0, MAKELONG(rc.right, rc.bottom));
  }

public:
  void setSashPosition(int pos)
  {
    RECT  rc;
    getClientRect(&rc);

    //<added date="2000.06.30">
    position = pos;
    //</added>

    if (direction == VERTICAL) {
      if(pos > 0 && pos <rc.bottom) {
        position = pos;
        RECT  rc;
        getClientRect(&rc);
        send(WM_SIZE, 0, MAKELONG(rc.right, rc.bottom));
      }
    }

    if (direction == HORIZONTAL) {
      if(pos > 0 && pos <rc.right) {
        position = pos;
        RECT  rc;
        getClientRect(&rc);
        send(WM_SIZE, 0, MAKELONG(rc.right, rc.bottom));
      }
    }
  }


  int    getSashPosition() { 
    return position; 
  }
};

}


