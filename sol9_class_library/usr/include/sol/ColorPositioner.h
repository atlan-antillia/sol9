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
 *  ColorPositioner.h
 *
 *****************************************************************************/

 //2016/11/10 Modifed to use WM_COLOR_POSITION_CHANGED

#pragma once

#include <sol/Positioner.h>
#include <sol/Brush.h>
#include <sol/Vector3f.h>

namespace SOL {

#define WM_COLOR_POSITION_CHANGED (WM_USER+2014)

class ColorPositioner :public Positioner {
private:
  HBRUSH hRed;
  HBRUSH hGreen;
  HBRUSH hBlue;

private:
  long colorScrollBar(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();
    HDC hdc = (HDC)event.getWParam();
    //SetBkMode(hdc, TRANSPARENT ); 

    if (hwnd == getScrollBarWindow(0)) {
      return (long)hRed;
    }

    if (hwnd == getScrollBarWindow(1)) {
      return (long)hGreen;
    }

    if (hwnd == getScrollBarWindow(2)) {
      return (long)hBlue;
    }
    return NULL;
  }

public:
  /**
   * Constructor
   */
  ColorPositioner()
  :Positioner(),
  hRed  ( CreateSolidBrush(RGB(0xff,00,00)) ),  
  hGreen( CreateSolidBrush(RGB(00,0xff,00)) ),
  hBlue ( CreateSolidBrush(RGB(00,00,0xff)) )
  {
  }

  ColorPositioner(View* parent, const TCHAR* caption, Args& args)
  :Positioner(parent, caption, args.set(XmNlabelString, _T("ColorPositioner"))
                                .set(XmNminimum, 0)
                                .set(XmNmaximum, 255)),
  hRed  ( CreateSolidBrush(RGB(0xff,00,00)) ),  
  hGreen( CreateSolidBrush(RGB(00,0xff,00)) ),
  hBlue ( CreateSolidBrush(RGB(00,00,0xff)) )
  {
  	ColorPositioner::create(parent, caption, args);
  }
  
  Boolean create(View* parent, const TCHAR* caption, Args& args)
	{
       Positioner::create(parent, caption, args.set(XmNlabelString, _T("ColorPositioner"))
                                .set(XmNminimum, 0)
                                .set(XmNmaximum, 255));
    setPositionChangedMessage(WM_COLOR_POSITION_CHANGED);  
    addEventHandler(WM_CTLCOLORSCROLLBAR, this, (Handler)&ColorPositioner::colorScrollBar, NULL);
    //2016/11/10
    const TCHAR* labels[] = {_T("R="), _T("G="), _T("B=") };
    for (int i = 0; i<3; i++) {
      setScrollBarText(i, labels[i]);
    }   
	return True;
  }

public:
  ~ColorPositioner()
  {
    if (hRed) DeleteObject(hRed);
    if (hGreen) DeleteObject(hGreen);
    if (hBlue) DeleteObject(hBlue);
  }

 
  void getRGBColor(int& r, int& g, int& b)
  {
    r = getX();
    g = getY();
    b = getZ();
  }
  
  void getBGRColor(Vector3f& vector)
  {
    int bgr[3];
    bgr[0] = getZ(); //blue  0-255
    bgr[1] = getY(); //green 0-255
    bgr[2] = getX(); //red   0-255
    float fv[3];
    for (int i = 0; i<3; i++) {
      fv[i] = (float)bgr[i]/255.0f;
    }
    vector.set(fv, 3);
      
  } 
};

}
