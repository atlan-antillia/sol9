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
 *  ScrollBar.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#define Min(a,b)    (((a) < (b)) ? (a) : (b))


class ScrollBar  :public Primitive {
private:
  int    pageIncrement;
  int    lineIncrement;

public:
  static const int ScrollBar::HORIZONTAL = (int)SB_HORZ;
  static const int ScrollBar::VERTICAL   = (int)SB_VERT;

protected:
  LRESULT ScrollBar::defaultProc(Event& event)
  {
    return discardInput(event);
  }

public:
  ScrollBar():Primitive() { }
    

public:
  //2012/06/25
  ScrollBar(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
          .set(XmNclassName, _T("ScrollBar")));

    pageIncrement = 4;
    lineIncrement = 1;
    setValues(args);

    return rc;
  }


public:
  int moveThumb(Event& event)
  {
    int pos  = getPos();
    int prev = pos;

    SCROLLINFO scInfo;
    int min, max;
    getScrollRange(&min, &max);
    int range = max - min;

    int request = LOWORD(event.getWParam());
    switch(request) {

    case SB_PAGEDOWN: pos += pageIncrement;
    case SB_LINEDOWN: pos = Min(range, pos + lineIncrement);
      break;

    case SB_PAGEUP:  pos -= pageIncrement;
    case SB_LINEUP:  pos = Max(0, pos - lineIncrement);
      break;

    case SB_TOP: pos = 0;
      break;

    case SB_BOTTOM:  pos = range;
      break;

    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      scInfo.fMask = SIF_ALL;
      getScrollInfo(&scInfo);
      pos = scInfo.nTrackPos;
      break;

    default:
      break;
    }
    setPos(pos);
    return  prev - pos;
  }

public:
  void getValues(Args& args)
  {
    Primitive::getValues(args);

    int num   = args.getCount();
    Arg* arg  = args.getArgList();
    int max, min;

    for (int i = 0; i<num; i++) {
      const TCHAR*  name = arg[i].name;
      LONG_PTR* val  = (LONG_PTR*)arg[i].value;
      if (name == XmNpageIncrement) {
        *val =  pageIncrement;  // 08/02 '94
        continue;
      }
      if (name == XmNlineIncrement) {
        *val =  lineIncrement;
        continue;
      }
      if (name == XmNmaximum) {
        getScrollRange(&min, &max);
        *val = max;
        continue;
      }
      if (name == XmNminimum) {
        getScrollRange(&min, &max);
        *val = min;
        continue;
      }
      if (name == XmNthumbPosition) {
        *val = (LONG_PTR)getPos();
        continue;
      }
    }
  }

public:
  void setValues(Args& args)
  {
    Primitive::setValues(args);

    LONG_PTR val;
    if (args.get(XmNpageIncrement, &val))
      pageIncrement = (int)val;
    if (args.get(XmNlineIncrement, &val))
      lineIncrement = (int)val;

    int max, min;
    getScrollRange(&min, &max);
    if (args.get(XmNmaximum, &val))
      setScrollRange(min, (int)val);

    getScrollRange(&min, &max);
    if (args.get(XmNminimum, &val))
      setScrollRange((int)val, max);

    if (args.get(XmNthumbPosition, &val))
      setPos((int)val);
  }


public:
  void disable()
  {
    if(isEditable()) {
      if(!getNewProc()) 
        replaceWindowProc();
    }
    else {
         View::disable();
    }
  }

public:
  void enable()
  {
    if(isEditable()) {
      restoreWindowProc();
    }
    else {
      View::enable();
    }
  }

public:
  BOOL getScrollInfo(SCROLLINFO* scInfo) 
  {
    BOOL rc = FALSE;
    if(scInfo) {
      scInfo->cbSize = sizeof(SCROLLINFO);
      rc  = ::GetScrollInfo(getWindow(), SB_CTL, scInfo);
    }
    return rc;
  }
  
public:
  int  setScrollInfo(SCROLLINFO* scInfo) 
  {
    int pos = 0;
    if(scInfo) {
      scInfo->cbSize = sizeof(SCROLLINFO);
      pos = ::SetScrollInfo(getWindow(), SB_CTL, scInfo, TRUE);
    }
    return pos;
  }

  int    getPos() {
      return ::GetScrollPos(getWindow(), SB_CTL);
  }

  void  getScrollRange(int* min, int* max) {
       ::GetScrollRange(getWindow(), SB_CTL, min, max);
  }

  void   setPos(int pos) {
      ::SetScrollPos(getWindow(), SB_CTL, pos, TRUE);
  }

  int    getPageIncrement() { return pageIncrement; }

  int    getLineIncrement() { return lineIncrement; }

  void  setScrollRange(int min, int max) {
       ::SetScrollRange(getWindow(), SB_CTL, min, max, TRUE);
  }

  void  setPageIncrement(int val) { pageIncrement = val; }

  void  setLineIncrement(int val) { lineIncrement = val; }


  void    enableArrows(int arrows) {
      send(SBM_ENABLE_ARROWS, (WPARAM)arrows, 0L);
  }

  void  getRange(int* min, int* max) {
       send(SBM_GETRANGE, (WPARAM)min, (LPARAM)max);
  }

  void  setRange(int min, int max) {
       send(SBM_SETRANGE, (WPARAM)min, (LPARAM)max);
  }

  void  setRangeRedraw(int min, int max) {
       send(SBM_SETRANGEREDRAW, (WPARAM)min, (LPARAM)max);
  }
};

}

