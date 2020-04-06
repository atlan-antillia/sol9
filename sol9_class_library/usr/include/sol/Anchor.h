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
 *  Anchor.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// SOL++2000
// 2000.02.18
// 2012/07/10 Modified to be able to use XmNfontSize property to create
//           an instance of this Anchor class.

#pragma once

#include <sol\Primitive.h>

#include <sol\Resource.h>
#include <sol\BitmapFile.h>
#include <sol\Anchor.h>
#include <sol\Bitmap.h>
#include <sol\Icon.h>
#include <sol\PaintDC.h>
#include <sol\ClientDC.h>
#include <shellapi.h>
#include <sol/UnderlineFont.h>
#include <sol/String.h>

namespace SOL {

class Anchor :public Primitive {
private:
  static const int FONT_SIZE = 9;

private:
//  int    labelType;
  int    width;
  int    height;
  BOOL  recomputeSize;
  UnderlineFont ufont;
  int     fontSize;
  String   url;

protected:
  long leftButtonUp(Event& event)
  {
    //MessageBox(NULL, (const TCHAR*)url, _T("DEBUG"), MB_OK);
    if ((const TCHAR*)url) {
      SHELLEXECUTEINFO sei;
      ::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
      sei.cbSize = sizeof(SHELLEXECUTEINFO);
      sei.lpFile = (const TCHAR*)url;
      sei.nShow  = SW_SHOWNORMAL;
      ::ShellExecuteEx(&sei);
    }
    return 0L;
  }

protected:
  long size(Event& event)
  {
    int x, y, w, h;

    getGeometry(x, y, w, h);
    if(recomputeSize == TRUE) {
      reshape(x, y, width, height);
    }
    return NULL;
  }

protected:
  long paint(Event& event)
  {
    int x, y;
    int  w, h;

    PaintDC pdc(this);
    getGeometry(x, y, w, h);
    RECT rect;
    getWindowRect(&rect);
    HDC hdc = pdc.get();

    TCHAR  text[256];
    getText(text, 256);
    pdc.setBkMode(TRANSPARENT);
    Size size;

    HFONT hfont = ufont.getFont();

    hfont = (HFONT)pdc.select(hfont);
    pdc.setTextColor(RGB(128, 128, 255));      
    DWORD ext = pdc.getTextExtent(text, (int)strlen(text), &size);
    int hh = size.cy;  
    int ww = size.cx;  
    pdc.textOut(2, (h-hh)/2, text, (int)strlen(text));

    pdc.select(hfont);

    return 0L;
  }


public:
  Anchor():Primitive() 
  { 
    url = _T("");
  }


public:
  /**
   * Constructor
   */
  //2012/07/10
  Anchor(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  ~Anchor() 
  {
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
      args.set(XmNstyle, (LONG_PTR)WS_GROUP)
        .set(XmNbackground, (LONG_PTR)GetStockObject(NULL_BRUSH))
        .set(XmNclassName, _T("_Anchor_")) //2012/07/10
       .set(XmNuseDefaultFont, "false")
      .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW)
      .set(XmNcursor, (LONG_PTR)LoadCursor(NULL, IDC_HAND)) );

    addEventHandler(WM_PAINT, this,
      (Handler)&Anchor::paint, NULL);
    addEventHandler(WM_SIZE, this,
      (Handler)&Anchor::size, NULL);
    addEventHandler(WM_LBUTTONUP, this,
      (Handler)&Anchor::leftButtonUp, NULL);

    //2012/07/10
    fontSize = FONT_SIZE;
    LONG_PTR val = 0;
    if (args.get(XmNfontSize, &val)) {
      if (val > 0) {
        fontSize = (int)val; 
      }
    }
    ufont.create(fontSize);

    recomputeSize = TRUE;
    setValues(args);

    return rc;
  }

public:
  void getValues(Args& args)
  {
    Primitive::getValues(args);

    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    for (int j = 0; j<num; j++) {
      const TCHAR*   name  = arg[j].name;
      LONG_PTR* val  = (LONG_PTR*)arg[j].value;
      if(name == XmNrecomputeSize) {
        *val = recomputeSize;
        continue;
      }
      /*
      if(name == XmNlabelType) {
        *val = labelType;
        continue;
      }
      */
    }
  }

public:
  void setValues(Args& args)
  {
    Primitive::setValues(args);

    TCHAR  label[256];
    getText(label, 256);
    url = _T("");
    const TCHAR* turl = (const TCHAR*)args.get(XmNurl);
    if (turl) {
      url = turl;
    }

    ClientDC cdc(this);
    HFONT hfont = ufont.getFont();
      
    hfont = (HFONT)cdc.select(hfont);
      Size size;
    cdc.getTextExtent(label, (int)strlen(label), &size);
    if (hfont) {
      cdc.select(hfont);
    }
    height = size.cy + 4;
    width  = size.cx + 4;

    width++;
    height++;
    
    LONG_PTR val;
    if (args.get(XmNrecomputeSize, &val)) {
      recomputeSize = (BOOL)val;
    }
    if (recomputeSize == TRUE) {
      send(WM_SIZE, 0, 0);
    }

    update(NULL);
  }


public:
  void setAnchor(const TCHAR* label, const TCHAR* turl)
  {
    ClientDC cdc(this);

    LONG_PTR val;
    get(XmNinstance, &val);

    Size size;
    cdc.getTextExtent(label, (int)strlen(label), &size);
    height = size.cy + 4;
    width  = size.cx + 4;
    
    if (turl) {
      url = turl;
    }
  }

public:
  const TCHAR* geUrl()
  {
    return (const TCHAR*)url;
  }

public:
  void  getSize(int* width1, int* height1) 
  {
      *width1  = width;
      *height1 = height;
  }
};

}


