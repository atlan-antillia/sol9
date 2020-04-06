/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Hyperlink.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/16

#pragma once

#include <sol\Gadget.h>
#include <sol\UnderlineFont.h>
#include <sol\PaintDC.h>
#include <sol\ClientDC.h>

namespace SOL {

class Hyperlink :public Gadget {

private:
  /** Display-string in this link such as "Antillia.com"*/
  String title;

  /** Link-string such "http://www.antillia.com" */
  String link;

private:
  UnderlineFont font;

private:
  HCURSOR  hHand;
  HCURSOR hprev;

private:
  bool  visited;

private:
  //Purple
  static const COLORREF VISITED_COLOR = RGB(128, 0, 128);
  //Blue
  static const COLORREF DEFAULT_COLOR = RGB(0, 0, 255);

public:
  /**
   * Constructor
   */
  Hyperlink()
  :title(_T("")),
   link(_T("")),
   visited(false)
  {
    font.create();
    hHand = LoadCursor(NULL, IDC_HAND);
    hprev = NULL;
  }

  
public:
  /**
   * Destructor
   */
  ~Hyperlink() {
  }


public:
  /**
   * Create no window, because this is a Gadget class.
   */
  Boolean create(View* parent, const TCHAR* title, Args& args)
  { 
    Boolean rc = Gadget::create(parent, title, args);
    if (rc == False) {
      return rc;
    }

    this->title = title;
    LONG_PTR val = 0;
    if (args.get(XmNlink, &val)) {
      link = (TCHAR*)val;
      rc = True;  
    }

    RECT r;
    r.left = args.get(XmNx);
    r.top = args.get(XmNy);
    const TCHAR* label= (const TCHAR*)title;
    ClientDC dc(parent);

    HFONT old = (HFONT)dc.select(font.getFont());

    SIZE size;
    dc.getTextExtentPoint32(label, strlen(label),&size);
    r.right = r.left + size.cx;
    r.bottom = r.top + size.cy;
    //Set a rectangle for this label
    setRect(&r);
    dc.select(old);

    parent->invalidate(&r, TRUE);
      
    return rc;
  }


public:
  const TCHAR* getTitle() {
    return (const TCHAR*)title;
  }

public:
  const TCHAR* getLink() {
    return (const TCHAR*)link;
  }

public:

  /**
   * Call ShellExecuteEx for the link (such as "http://www.foo.com/")
   */
  virtual int execute() {
    int rc = 0;
    //printf("ShellExecuteEx for a filePath =[%s]\r\n", (const TCHAR*)link);
    visited = true;
    RECT r;
    getRect(&r);
    View* parent = getParent();
    parent->invalidate(&r, TRUE);
    
    SHELLEXECUTEINFO sei;
    ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.lpFile = (const TCHAR*)link;
    sei.nShow  = SW_SHOWNORMAL;
    rc = ShellExecuteEx(&sei);
    return rc;    
  }

public:
  virtual bool isMouseOver(int x, int y) {
    bool rc = false;
    RECT r;
    getRect(&r);
    
    if (x> r.left && x < r.right && y> r.top && y < r.bottom) {
      hprev = SetCursor(hHand);
      rc = true;
    } else {
      if (hprev) {
        SetCursor(hprev);
      }
    }
    return rc;
  }


public:
  virtual void draw(DC* dc, int x=0, int y=0) { 

    RECT r;
    const TCHAR* label= (const TCHAR*)title;
    getRect(&r);
    HFONT old = (HFONT)dc->select(font.getFont());

    SIZE size;
    
    dc->getTextExtentPoint32(label, strlen(label), &size);
    r.right = r.left + size.cx;
    r.bottom = r.top + size.cy;

    setRect(&r);

    dc->setBkMode(TRANSPARENT);
    if (visited) {
      //Visited color:Purple
      dc->setTextColor(VISITED_COLOR);
    } else {
      //Default color:Blue
      dc->setTextColor(DEFAULT_COLOR);
    }
        dc->textOut(r.left+x , r.top+y, label, strlen(label));
    dc->select(old);
  }
};

}
