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
 *  ColorListView.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2012/05/25

#pragma once

#include <sol\ListView.h>
#include <sol/DC.h>
#include <sol/Brush.h>

namespace SOL {

class ColorListView :public ListView {
private:
  static const int DEFAULT_HEIGHT = 32;
  static const int DEFAULT_RGBSTEP= 0x33;

private:
  static const long STYLE = (LVS_REPORT|LVS_OWNERDRAWFIXED);

private:
  int itemHeight;
  int rgbStep;

public:
  ColorListView(): ListView() { }


public:
  ColorListView(View* parent, const TCHAR* name, Args& args)
    :ListView()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = ListView::create(parent, name, 
      args.set(XmNstyle, (LONG_PTR)STYLE));

    return rc;
  }

private:
  void setValues(Args& args)
  {
    ListView::setValues(args);

    this->itemHeight = DEFAULT_HEIGHT;
    this->rgbStep    = DEFAULT_RGBSTEP;

    int h = (int)args.get(XmNitemHeight);
    if (h > 0) {
      itemHeight = h;
    }
    int s = (int)args.get(XmNrgbStep);
    if (s > 0 && s < 0xff) {
      this->rgbStep = s;
    }

    DWORD dwStyle = getExtendedViewStyle() | LVS_EX_FULLROWSELECT;//|LVS_EX_GRIDLINES;
    setExtendedViewStyle(dwStyle);

    ListViewColumn items[] = {
      {_T("Color"),  LVCFMT_LEFT, 100},
      {_T("RGB"),    LVCFMT_LEFT, 100},
    };
    setColumn(items, CountOf(items));
    
    int size = 0xff/rgbStep;
    float step = (float)0xff/(float)size;

    if (0xff%rgbStep) {
      size++;
    }

    int n = 0;
    for (int i = 0; i<=size; i++) {
      for(int j = 0; j<=size; j++) {
        for (int k = 0; k<=size; k++) {    
      
          int r = (int)(step*(float)i);
          int g = (int)(step*(float)j);
          int b = (int)(step*(float)k);

          if (r>0xff) r = 0xff;
          if (g>0xff) g = 0xff;
          if (b>0xff) b = 0xff;

          if (RGB(r, g, b) <= RGB(0xff, 0xff, 0xff)) {
          
            int m = insertItemParam(n++, 0, RGB(r, g, b));
            TCHAR name[128];
            _stprintf_s(name, CountOf(name), _T("#%02X%02X%02X"), r, g, b);  
            setItemText(m, 1, name);
          } else {
            //Ignore this case.
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
  
    DC dc(lpDraw->hDC);
    int itemID = lpDraw->itemID;
    
    RECT   rcItem, rcSubItem, rcAll;
    TCHAR  subItemName[256];
  
    dc.saveDC();
  
    getItemRect(itemID, &rcAll, LVIR_BOUNDS);  
    getItemRect(itemID, &rcItem, LVIR_LABEL);
    getSubItemRect(itemID, 1, LVIR_LABEL, &rcSubItem);

    getItemText(itemID, 1, subItemName, CountOf(subItemName));
    
    COLORREF color = (COLORREF)getItemParam(itemID);

    Brush br(color);

    COLORREF fcolor = COLOR_WINDOWTEXT;
    COLORREF bcolor = COLOR_WINDOW;
    if (lpDraw->itemState & ODS_SELECTED) {
      fcolor = COLOR_HIGHLIGHTTEXT;
      bcolor = COLOR_HIGHLIGHT;
    }
    dc.setTextColor(GetSysColor(fcolor));
    dc.setBkColor(GetSysColor(bcolor));  

    Brush br1(GetSysColor(bcolor));

    rcAll.left  += 1;
    dc.fillRect(&rcAll, (HBRUSH)br1);

    dc.fillRect(&rcItem, (HBRUSH)br);
  
    dc.setBkMode(TRANSPARENT);
    dc.fillRect(&rcSubItem, (HBRUSH)br1);

    rcSubItem.left +=2;
    dc.drawText(subItemName, -1, &rcSubItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    if (lpDraw->itemState & ODS_FOCUS) {
      rcAll.bottom -= 1;      
      dc.drawFocusRect(&rcAll);
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

