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
 *  LabelGadget.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Gadget.h>
#include <sol\Font.h>

#include <sol\String.h>
#include <sol\Brush.h>
#include <sol\ClientDC.h>

namespace SOL {

class LabelGadget :public Gadget {
private:
  BOOL   status;

  String   text;

  Font*   font;
  COLORREF backColor;
  COLORREF textColor;
  COLORREF selBackColor;
  COLORREF selTextColor;
  DWORD   style;

public:
  enum {L_LEFT, L_CENTER, L_RIGHT} LabelType;

public:
  LabelGadget() : Gadget() { }

public:
  //2012/06/25
  LabelGadget(View* parent, const TCHAR* label, Args& args)
  :Gadget() //parent, label, args) 
  {
    create(parent, label, args);
  }


public:
  ~LabelGadget()
  {
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    font   = NULL;
  
    int margin = args.get(XmNmargin);
    if (margin==0) {
      margin = 2;
    }

    setMargin(margin);
  
    Boolean rc = Gadget::create(parent, label, args); 

    status      = FALSE;
    backColor    = ::GetSysColor(COLOR_BTNFACE);
    textColor    = ::GetSysColor(COLOR_BTNTEXT);
    selTextColor = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    selBackColor = ::GetSysColor(COLOR_HIGHLIGHT);

    const TCHAR* ptr = (const TCHAR*)args.get(XmNlabelString);
    if(ptr == NULL) {
      ptr = label;           
    }
    if(ptr == NULL) {
      ptr = _T("");
    }

    this->text = ptr;

    this->style = L_LEFT;

    LONG_PTR val;
    if (args.get(XmNstyle, &val)) {
      this->style = val;
    }
  
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
    
      SIZE size;
      const TCHAR* ctext = (const TCHAR*)text;
      dc.getTextExtent(ctext, strlen(ctext), &size);

      setSize(size.cx+margin*2, size.cy+margin*2);
    }

    return rc;
  }

public:
  void setText(const TCHAR* string)
  {
    this->text = string;
  }
  
public:
  virtual void draw(DC* dc)
  {
    LabelGadget::draw(dc, 0, 0);
  }

public:
  virtual void draw(DC* cdc, int x, int y)
  {

    cdc->setBkMode(TRANSPARENT);

    COLORREF color = backColor;
    if(status) {
      color = selBackColor;
    }
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

    COLORREF tcolor = textColor;
    if(status) {
      tcolor = selTextColor;
    }
    cdc -> setTextColor(tcolor);
    cdc -> setBkColor(color);

    int margin = getMargin();
    //
    const TCHAR* ctext = (const TCHAR*)text;

    SIZE size;
    cdc -> getTextExtent(ctext, strlen(ctext), &size);
    setSize(size.cx+margin*2, size.cy+ margin*2);

    RECT r;
     getRect(&r);
    r.left   += x;
    r.top    += y;
    r.right  += x;
    r.bottom += y;

    // LABEL_LEFT   
    int px = r.left + margin;

    int  py = r.top+ margin;

    if(style == L_CENTER) {
      px = r.left + ((r.right - r.left) - size.cx)/2;
    }
    if(style == L_RIGHT) {
      px = r.right - size.cx - margin;
    }

    cdc -> extTextOut(px, py, ETO_CLIPPED|ETO_OPAQUE, &r, 
        (TCHAR*)ctext, strlen(ctext), NULL); 

    if(hfont) {
      //back to original hfont
      cdc->select(hfont);
    }
  }

public:
  void  setStyle(DWORD style1) {
    style = style1; }

public:
  void  setFont(Font* f) { 
    font = f; 
  }

  void  setFont(Font& f) { 
    font = &f; 
  }

  void  setTextColor(COLORREF color) { 
    textColor = color; 
  }
  void  setBackColor(COLORREF color) { 
    backColor = color; 
  }

  void  setSelTextColor(COLORREF color) { 
    selTextColor = color; 
  }

  void  setSelBackColor(COLORREF color) { 
    selBackColor = color; 
  }

  void  setStatus(BOOL flag) { 
    status = flag; 
  }
};

}

