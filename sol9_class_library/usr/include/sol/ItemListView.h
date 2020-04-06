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
 *  ItemListView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\DC.h>

#include <sol\Item.h>
#include <sol\OwnerDrawListBox.h>
#include <sol\Composite.h>
#include <sol\ClientDC.h>

namespace SOL {

class ItemListView :public Composite {
private:
  int   labelWidth;
  int   itemHeight;
  int   labelMaxWidth;
  COLORREF faceColor;
  COLORREF normalColor;
  COLORREF selectedColor;
  COLORREF normalTextColor;
  COLORREF selectedTextColor;

  OwnerDrawListBox* listbox;

private:

  void selected(DC* dc, LPDRAWITEMSTRUCT dis, RECT* rc)
  {
    RECT  r;
    ::CopyRect(&r, rc);
    r.left += (labelWidth+1);

    COLORREF color = normalColor;
    if (dis->itemState & ODS_SELECTED) {
      color = selectedColor;
    }
    HBRUSH hbr = ::CreateSolidBrush(color);
    dc->fillRect(&r, hbr);
    ::DeleteObject(hbr);
  }


  void focusIn(DC* dc, LPDRAWITEMSTRUCT  dis, RECT* rc)
  {
    RECT  r;
    CopyRect(&r, rc);
    r.bottom -= 1;
    r.left   += (labelWidth+1);

    COLORREF color = normalColor;
    if (dis->itemState & ODS_FOCUS) {
      color = selectedColor;
    }
    HBRUSH hbr = ::CreateSolidBrush(color);
    dc->frameRect(&r, hbr);
    ::DeleteObject (hbr);
  }


  long drawItem(Event& event)
  {
    LPARAM lParam = event.getLParam();
    LPDRAWITEMSTRUCT ptr = (LPDRAWITEMSTRUCT)lParam;

    DC  dc(ptr->hDC);
    RECT rc = ptr->rcItem;
    if (ptr->itemID == -1) {
      focusIn(&dc, ptr, &rc);
      return TRUE;
    }
    if(ptr->itemAction == ODA_DRAWENTIRE) {
      selected(&dc, ptr, &rc);
      focusIn(&dc,ptr, &rc);
    }
    if(ptr -> itemAction == ODA_SELECT) {
      selected(&dc, ptr, &rc);
    }
    if(ptr -> itemAction == ODA_FOCUS) {
      focusIn(&dc, ptr, &rc);
    }

    if(ptr -> itemAction == ODA_DRAWENTIRE ||
      ptr -> itemAction == ODA_SELECT) {
      Item* item = (Item*) ptr->itemData;

      COLORREF color = normalTextColor;
      if(item) {
        char* str = item->getName();
        dc.setBkMode(TRANSPARENT);
        RECT r;
        ::CopyRect(&r, &rc);
        r.left += 1;
        r.top  += 1;
        r.right = r.left+labelWidth-1;
        HBRUSH hbr = ::CreateSolidBrush(faceColor);
        dc.fillRect(&r, hbr);
        ::DeleteObject(hbr);
        r.left += 1;
        r.top  += 1;
        dc.setTextColor(color);
        dc.drawText(str, strlen(str),  &r, DT_LEFT);

        str = item->getText();
        ::CopyRect(&r, &rc);
        r.top  += 2;
        r.left += labelWidth+4;
        r.right -= 2;
            if(ptr->itemState & ODS_SELECTED) {
          color = selectedTextColor;
        }
        dc.setTextColor(color);
        dc.drawText(str, strlen(str),  &r, DT_LEFT);
      }
    }

    HPEN pen  = ::CreatePen(PS_SOLID,1, RGB(0x80, 0x80, 0x80));
    HPEN prev = (HPEN)dc.select(pen);
    dc.moveTo(rc.left,  rc.bottom-1);  
    dc.lineTo(rc.right, rc.bottom-1);
    dc.moveTo(rc.left+labelWidth, rc.top);
    dc.lineTo(rc.left+labelWidth, rc.bottom);
    dc.select(prev);
    ::DeleteObject(pen);

    return TRUE;
  }


  long measureItem(Event& event)
  {
    LPARAM lParam = event.getLParam();
    LPMEASUREITEMSTRUCT ptr = (LPMEASUREITEMSTRUCT)lParam;
    ptr -> itemHeight = itemHeight; 
    return TRUE;
  }

  long compareItem(Event& event)
  {
    LPARAM lParam = event.getLParam();
    LPCOMPAREITEMSTRUCT ptr = (LPCOMPAREITEMSTRUCT)lParam;

    Item* item1 = (Item*) ptr -> itemData1;
    Item* item2 = (Item*) ptr -> itemData2;

    return strcmp(item1->getName(), item2->getName());
  }

  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);
    listbox -> reshape(0, 0, w, h);
    return NULL;
  }

public:
  ItemListView(): Composite() { }

public:
  //2012/06/25
  ItemListView(View* parent, const TCHAR* label, Args& args)
  :Composite()
  {
    create(parent, label, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {  
    Boolean rc = Composite::create(parent, label,    
        args.set(XmNstyle,(LONG_PTR)(WS_CHILD|WS_VISIBLE) ));

    labelWidth  = 10;

    ClientDC dc(this);
    SIZE size;
    dc.getTextExtent("A", 1, &size);
    itemHeight = size.cy*5/4;
    normalColor       = ::GetSysColor(COLOR_WINDOW);
    selectedColor     = ::GetSysColor(COLOR_HIGHLIGHT);  
    normalTextColor   = ::GetSysColor(COLOR_WINDOWTEXT);
    selectedTextColor = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    faceColor         = ::GetSysColor(COLOR_BTNFACE);

    Args ar;
    LONG_PTR val;
    if (args.get(XmNsortItems, &val)) {
      ar.set(XmNstyle, (LONG_PTR)LBS_SORT);
    }
    listbox = new OwnerDrawListBox(this, "", ar);
    listbox -> setItemHeight(0, MAKELPARAM(itemHeight,0));

    addEventHandler(WM_DRAWITEM, this,
      (Handler)&ItemListView::drawItem, NULL);
    addEventHandler(WM_MEASUREITEM, this,
      (Handler)&ItemListView::measureItem, NULL);
    addEventHandler(WM_COMPAREITEM, this,
      (Handler)&ItemListView::compareItem, NULL);

    addEventHandler(WM_SIZE, this,
      (Handler)&ItemListView::size, NULL);

    return rc;
  }

public:
  ~ItemListView()
  {
    delete listbox;
  }

public:
  void add(Item* item) 
  {
    listbox -> add(item);
    char* name = item->getName();
    ClientDC dc(this);
    SIZE size;
    if(name) {
      dc.getTextExtent(name, strlen(name), &size);
      if(size.cx+10 > labelWidth) {
        labelWidth = size.cx+10;
        RECT* rect = NULL;
        listbox -> invalidate(rect);
        listbox -> update();
      }
    }  
  }

public:
  void clear()
  {
    listbox -> resetContent();
    labelMaxWidth = 0;
  }


public:
  void setItemHeight(int height)
  {
    itemHeight = height;
    listbox -> setItemHeight(0, height);
  }

public:
  void setLabelWidth(int width)
  {
    labelWidth = width;
    RECT* rect = NULL;         //1997.08.23
    listbox -> invalidate(rect);
    listbox -> update();
  }

public:
  void remove(int indx)
  {
    listbox -> deleteString(indx);
  }


};

}

