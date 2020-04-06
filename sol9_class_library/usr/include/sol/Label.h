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
 *  Label.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

#include <sol\Resource.h>
#include <sol\BitmapFile.h>
#include <sol\Label.h>
#include <sol\Bitmap.h>
#include <sol\Icon.h>
#include <sol\PaintDC.h>
#include <sol\ClientDC.h>
#include <shellapi.h>


namespace SOL {

class Label :public Primitive {
private:
  Resource* resource;
  int    labelType;
  int    width;
  int    height;
  BOOL  recomputeSize;

protected:
  long size(Event& event)
  {
    int x, y, w, h;

    getGeometry(x, y, w, h);
    if(recomputeSize == TRUE) 
      reshape(x, y, width, height);
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

    if(labelType == LABEL_STRING) {
      TCHAR  text[1024];
      getText(text, 1024);
      pdc.setBkMode(TRANSPARENT);
      Size size;

      //2008/06/26
      HFONT hfont = NULL;
      View* parent = getParent();
      Font* font = parent->getFont();

      if (font) {
        hfont = (HFONT)pdc.select(font);
      }
      DWORD ext = pdc.getTextExtent(text, strlen(text), &size);
      int hh = size.cy;  
      int ww = size.cx;  
      pdc.textOut(2, (h-hh)/2, text, strlen(text));

      pdc.select(hfont);

    }
    if(resource != NULL &&
      (labelType == LABEL_BITMAP || 
      labelType == LABEL_ICON) ) {
      resource -> draw(hdc, 0, 0);
    }
    return NULL;
  }

public: 
  enum {LABEL_STRING, LABEL_BITMAP, LABEL_ICON} LabelType;

public:
  Label()
  :Primitive(),
  resource(NULL) { //2012/07/10
  }


public:
  ~Label() {
    if(resource) delete resource;
  }

public:
  //2012/06/25
  Label(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
      args.set(XmNstyle, (LONG_PTR)WS_GROUP)
        .set(XmNbackground, (COLOR_BTNFACE+1))
        .set(XmNclassName, _T("Label"))         //2012/06/25
      .set(XmNuseDefaultFont, _T("true"))     //2012/06/25
      .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));

    addEventHandler(WM_PAINT, this,
      (Handler)&Label::paint, NULL);
    addEventHandler(WM_SIZE, this,
      (Handler)&Label::size, NULL);
    resource      = NULL;
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
      if(name == XmNlabelType) {
        *val = labelType;
        continue;
      }
    }
  }

public:
  void setValues(Args& args)
  {
    Primitive::setValues(args);

    TCHAR  label[1024];
    getText(label, 1024);
    labelType = (int) args.get(XmNlabelType);
    HICON   hicon   = (HICON)  args.get(XmNicon);
    HBITMAP hbitmap = (HBITMAP)args.get(XmNbitmap);

    if (labelType == LABEL_STRING) {
      ClientDC cdc(this);
      HFONT hfont = NULL;
      View* parent = getParent();
      if (parent) {
        Font* dfont = parent->getFont();
        if (dfont) {
          hfont = (HFONT)cdc.select(dfont);
        }
      }
      Size size;
      cdc.getTextExtent(label, strlen(label), &size);
      if (hfont) {
        cdc.select(hfont);
      }
      height = size.cy + 4;
      width  = size.cx + 4;
    }
    if (hicon) {
      labelType = LABEL_ICON;
      if(resource) delete resource;
      resource  = new Icon(_T(""), hicon);
      resource -> getSize(&width, &height);
    }
    if (hbitmap) {
      labelType = LABEL_BITMAP;
      if(resource) delete resource;
      resource  = new Bitmap(label, hbitmap);
      resource -> getSize(&width, &height);
    }
    if (hicon == NULL && hbitmap == NULL) {
      setLabel(label);
    }
    width++;
    height++;

    LONG_PTR val;
    if (args.get(XmNrecomputeSize, &val))
      recomputeSize = (BOOL)val;
    if (recomputeSize == TRUE) 
      send(WM_SIZE, 0, 0L);

    update(NULL);
  }


public:
  void setLabel(const TCHAR* label)
  {
    ClientDC cdc(this);

    labelType = LABEL_STRING;

    LONG_PTR val;
    get(XmNinstance, &val);

    TCHAR* dot = strrchr((TCHAR*)label, '.');
    TCHAR ext[80];
    ext[0] = NULL;
    if(dot) {
      strcpy_s(ext, CountOf(ext), dot); //2012/06/21
    }
    TCHAR* name = (TCHAR*)strrchr((TCHAR*)label, (TCHAR)'\\');
    if(name) 
      name++;
    else
      name = (TCHAR*)label;

    if(strcmp(ext,_T(".ico")) == 0) {
      HICON hicon = ::ExtractIcon((HINSTANCE)val, label, 0);
      if(hicon) {
        if(resource) delete resource;
        resource = new Icon(_T(""), hicon);
        labelType = LABEL_ICON;
        resource -> getSize(&width, &height);
      }
    }
    if(strcmp(ext, _T(".bmp")) == 0) {
      BitmapFile bmpFile;
      if(bmpFile.openReadOnly(label) >= 0) {
        HBITMAP hbmp = bmpFile.extract(cdc.get());
        if(hbmp) {
          if(resource) delete resource;
          resource = new Bitmap(name, hbmp);
          labelType = LABEL_BITMAP;
          resource -> getSize(&width, &height);
        }
        bmpFile.close();
      }
    }
    if(labelType == LABEL_STRING) {
      Size size;
      cdc.getTextExtent(label, strlen(label), &size);
      height = size.cy + 4;
      width  = size.cx + 4;
    }
  }


  void  getSize(int& width1, int& height1) {
      width1  = width;
      height1 = height;
  }
  
  void  getSize(int* width1, int* height1) {
      *width1  = width;
      *height1 = height;
  }
};

}


