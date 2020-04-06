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
 *  ImageButton.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/08
#pragma once

#include <sol/ImageBox.h>
//#include <sol/gdiplus/ImageBlender.h>

//using namespace Gdiplus;

namespace SOL {

class ImageButton :public ImageBox {
private:
  bool enabled;

private:
  COLORREF bkColor;

private:
  
  float  transparency;

  int    delta;

  HICON  hIcon;

protected:
  long  leftButtonDown(Event& event)
  {
    if (enabled) {
      delta = 2;
      this->capture();

      invalidateAll();
      update();
      callCallback(XmNarmCallback,
        (Key)getWindow(), this, event);
    }
    return 0;
  }

  long  leftButtonUp(Event& event)
  {
    if (enabled) {
      delta = 0;
      invalidateAll();
      update();
      releaseCapture();

      callCallback(XmNactivateCallback,
        (Key)getWindow(), this, event);
    }
    return 0;
  }

public:
  ImageButton(): ImageBox() { }

public:
  ImageButton(View* parent, 
      const TCHAR* name, Args& args)
  :ImageBox()
  {
    create(parent, name, args);
  }

public:
  void enable()
  {
    enabled = true;
    Primitive::enable();
    invalidateAll();
    update();
  }

public:
  void disable()
  {
    enabled = false;
    Primitive::disable();

    invalidateAll();
    update();
  }

public:
  virtual Boolean create(View* parent, 
      const TCHAR* name, Args& args)
  {
    Boolean rc = ImageBox::create(parent, name,
        args.set(XmNclassName, _T("_ImageButton_"))
        .set(XmNcursor, (LONG_PTR)LoadCursor(NULL, IDC_HAND))
            .set(XmNbackground, (LONG_PTR)GetStockObject(NULL_BRUSH)) );


    //addEventHandler(WM_PAINT, this,
    //  (Handler)&ImageButton::paint, NULL);

    addEventHandler(WM_LBUTTONDOWN, this,
      (Handler)&ImageButton::leftButtonDown, NULL);
    addEventHandler(WM_LBUTTONUP, this,
      (Handler)&ImageButton::leftButtonUp, NULL);

    enabled = true;
    bkColor =GetSysColor(COLOR_BTNFACE); // RGB(0xff, 0xff, 0xff);
    transparency = 0.5;
    delta = 0;

    return rc;
  }

public:
  ~ImageButton()
  {
  }

public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }

  //2012/05/28 Modified to be a public virtual method
  
public:
  virtual long paint(Event& event)
  {
    Gdiplus::Bitmap* image = getImage();
      
    int scaling = getScaling();

    PaintDC pdc(this);

    Gdiplus::Graphics graphics(pdc.get());


    RECT r;
    //Get the size of this window.
    getClientRect(&r);
    //2012/06/05
    Brush white(bkColor);
    pdc.fillRect(&r, (HBRUSH)white);
  

    if (enabled) {
      if (image) {
        if (scaling == StretchImage) {

          Gdiplus::Rect rect(r.left+delta, r.top+delta, r.right-r.left+delta, r.bottom-r.top+delta);
        //Draw resized image in the rectangle of 'rect'. 
          graphics.DrawImage(image, rect);
        }
        if (scaling == StretchWindow) {
          UINT width = image->GetWidth();
          UINT height = image->GetHeight();
        //Resize this window to display the whole area of the image with real size.
          resize(width, height);
        //Draw real image in the resized window.
          graphics.DrawImage(image, delta, delta, width+delta, height+delta);
        }
      } else {
        //2012/06/05
        Brush white(RGB(0xff,0xff,0xff));
        pdc.fillRect(&r, (HBRUSH)white);
      }
      return 0;
    } else {

    //enabled == false;
      if (image) {
        UINT width = image->GetWidth();
        UINT height = image->GetHeight();

        Gdiplus::Color color;
        color.SetFromCOLORREF(bkColor);
         Gdiplus::SolidBrush colorBrush(color);

        Gdiplus::ColorMatrix matrix  = 
        {1, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 
         0, 0, 1, 0, 0,
         0, 0, 0, transparency, 0,
         0, 0, 0, 0, 1};

        Gdiplus::ImageAttributes imageAttributes;
        imageAttributes.SetColorMatrix(&matrix,
            Gdiplus::ColorMatrixFlagsDefault, 
                        Gdiplus::ColorAdjustTypeBitmap);
      

        if (scaling == StretchImage) {
          Gdiplus::Rect rect(r.left, r.top, r.right-r.left, r.bottom-r.top);

          //1 Draw a rectangle with a colorBrush specified by backColor
          graphics.FillRectangle(&colorBrush, r.left, r.top, r.right-r.left, r.bottom-r.top);

          //Draw resized image in the rectangle of 'rect'. 
          graphics.DrawImage(image, rect,
            0, 0, width, height, Gdiplus::UnitPixel,&imageAttributes);
        }
        if (scaling == StretchWindow) {
          //Resize this window to display the whole area of the image with real size.
          resize(width, height);
          //Draw real image in the resized window.
          Gdiplus::Rect rect(0, 0, width, height);
          //1 Draw a rectangle with a colorBrush specified by backColor
          graphics.FillRectangle(&colorBrush, 0, 0, width, height);

          //graphics.DrawImage(image, 0, 0, width, height);
          graphics.DrawImage(image, rect,
            0, 0, width, height, Gdiplus::UnitPixel,&imageAttributes);

        }
      } else {
      //2012/06/05
      //imge is NULL
        Brush white(RGB(0xff,0xff,0xff));
        pdc.fillRect(&r, (HBRUSH)white);
      }
      
      return 0;
    }  
    //return 0;
  }
  
};

}

