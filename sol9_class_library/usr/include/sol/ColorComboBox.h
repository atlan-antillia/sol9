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
 *  ColorComboBox.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2012/05/25

#pragma once

#include <sol\ComboBox.h>
#include <sol/DC.h>
#include <sol/Brush.h>

namespace SOL {

class ColorComboBox :public ComboBox {
private:
  static const int DEFAULT_HEIGHT = 32;
  static const int DEFAULT_RGBSTEP = 0x33;

private:
  static const long STYLE = (CBS_DROPDOWNLIST|CBS_OWNERDRAWFIXED|CBS_HASSTRINGS|WS_VSCROLL|CBS_SORT);

private:
  int itemHeight;
  int rgbStep;

public:
  ColorComboBox(): ComboBox() { }


public:
  ColorComboBox(View* parent, const TCHAR* name, Args& args)
    :ComboBox()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = ComboBox::create(parent, name, 
    args.set(XmNstyle, (LONG_PTR)STYLE));

    return rc;
  }

private:
  void setValues(Args& args)
  {
    ComboBox::setValues(args);

    this->itemHeight = DEFAULT_HEIGHT;
    this->rgbStep    = DEFAULT_RGBSTEP;

    int h = args.get(XmNitemHeight);
    if (h > 0) {
      itemHeight = h;
    }
    int s = args.get(XmNrgbStep);
    if (s > 0 && s < 0xff) {
      this->rgbStep = s;
    }
    
    int size = 0xff/rgbStep;

    float step = (float)0xff/(float)size;

    if (0xff%rgbStep) {
      size++;
    }

    for (int i = 0; i<= size; i++) {
      for(int j = 0; j<= size; j++) {
        for (int k = 0; k<= size; k++) {
          int r = (int)(step*(float)i);
          int g = (int)(step*(float)j);
          int b = (int)(step*(float)k);

          if (r>0xff) r = 0xff;
          if (g>0xff) g = 0xff;
          if (b>0xff) b = 0xff;

          if (RGB(r, g, b) <= RGB(0xff, 0xff, 0xff)) {
            TCHAR name[128];
            _stprintf_s(name, 128, _T("#%02X%02X%02X"), r, g, b);    
    
               DWORD dwIndex = addString(name);
              setItemData(dwIndex,  RGB(r, g, b));

          } else {
            //We simply ignore this case;
          }
        }
      }
    }

  }

/*
typedef struct tagDRAWITEMSTRUCT {
   UINT CtlType;
   UINT CtlID;
   UINT itemID;
   UINT itemAction;
   UINT itemState;
   HWND hwndItem;
   HDC hDC;
   RECT rcItem;
   DWORD itemData;
} DRAWITEMSTRUCT;
*/
public:
  long drawItem(Event& event)
  {
    LPDRAWITEMSTRUCT lpDraw = (LPDRAWITEMSTRUCT)event.getLParam();
 
    if (lpDraw->itemID == -1) {
      return 0;
    }

    DC dc(lpDraw->hDC);

    dc.saveDC();
    dc.setBkMode(TRANSPARENT);    
  
    COLORREF color = (COLORREF) lpDraw->itemData;

    COLORREF fcolor = COLOR_WINDOWTEXT;
    COLORREF bcolor = COLOR_WINDOW;
    if (lpDraw->itemState & ODS_SELECTED) {
      fcolor = COLOR_HIGHLIGHTTEXT;
      bcolor = COLOR_HIGHLIGHT;
    }
    dc.setTextColor(GetSysColor(fcolor));
    dc.setBkColor(GetSysColor(bcolor));
    
    Brush br(color);

    RECT rcItem = lpDraw->rcItem;
    int  width = (rcItem.right - rcItem.left)/2;//-2;
    rcItem.right -= width;  
    dc.fillRect(&rcItem, (HBRUSH)br);

    TEXTMETRIC tm;
      dc.getTextMetrics(&tm);
    int x = 2;
    int y = (lpDraw->rcItem.bottom + lpDraw->rcItem.top - tm.tmHeight) / 2;

      TCHAR name[256];
      SendMessage(lpDraw->hwndItem, CB_GETLBTEXT,
          lpDraw->itemID, (LPARAM)name);
    int cch = _tcslen(name);
    rcItem =lpDraw->rcItem;
    rcItem.left +=width;
    
    dc.extTextOut(width + 2 * x, y,
      ETO_CLIPPED | ETO_OPAQUE, &rcItem,
      name, (UINT)cch, NULL);

    if (lpDraw->itemState & ODS_FOCUS) {
      dc.drawFocusRect(&lpDraw->rcItem);
    }
    dc.restoreDC(-1);

    return 1;
  }


/*
typedef struct tagMEASUREITEMSTRUCT {
    UINT   CtlType;
    UINT   CtlID;
    UINT   itemID;
    UINT   itemWidth;
    UINT   itemHeight;
    DWORD  itemData
} MEASUREITEMSTRUCT, *PMEASUREITEMSTRUCT, *LPMEASUREITEMSTRUCT; 
*/
public:
  long measureItem(Event& event)
  {
    LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)event.getLParam();
    
    lpmis->itemHeight = this->itemHeight;

    return 0;
  }

};

}

