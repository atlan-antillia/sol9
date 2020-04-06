/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary ApplicationViews, with or without
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
 *  ListViewColorChooser.h
 *
 *****************************************************************************/


// SOL9 2.0 
// 2012/05/28 Sample program to use SOL::ColorListView class


#include <sol\Composite.h>
#include <sol\Static.h>

#include <sol\ClientDC.h>
#include <sol\ColorListView.h>
//#include <sol\ColorBox.h>

#include "resource.h"

namespace SOL {

#define WM_COLORLISTVIEW_SELCHANGED (WM_USER+1988)

class ListViewColorChooser :public Composite {

private:
  Static         label;

  ColorListView  listView;
  int            selectedItemID;

public:
  ListViewColorChooser()
    :Composite()
  {
  }

public:
  ListViewColorChooser(View* parent, const TCHAR* caption, Args& args)
    :Composite()
  {
    create(parent, caption, args); 
  }


public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, 
          args.set(XmNstyle, WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS)
            .set(XmNbackground, (COLOR_BTNFACE +1))
            .set(XmNclassName, _T("_ListViewColorChooser_") ));
  
    const TCHAR* chooserTitle = (const TCHAR*)args.get(XmNcolorChooserTitle);

    Args ar;
    ar.reset();
    ar.set(XmNstyle, WS_VISIBLE);
    label.create(this, chooserTitle, ar);

    int height = (int)args.get(XmNitemHeight);
    if (height <=0) {
      height = 30;
    }

    int step = (int)args.get(XmNrgbStep);
    if (step <=0) {
      step = 0x20;
    }

    ar.reset();
    ar.set(XmNstyle, WS_VISIBLE);

    ar.set(XmNitemHeight, height);
    //ar.set(XmNrgbStep, 0x33);
    ar.set(XmNrgbStep, step);

    listView.create(this, NULL, ar);

    addEventHandler(WM_DRAWITEM, &listView, 
      (Handler)&ColorListView::drawItem, NULL);

    addEventHandler(WM_MEASUREITEM, &listView, 
      (Handler)&ColorListView::measureItem, NULL);

    listView.addCallback(XmNclickCallback, this,
        (Callback)&ListViewColorChooser::clicked, NULL);

    listView.addCallback(XmNdoubleClickCallback, this,
        (Callback)&ListViewColorChooser::clicked, NULL);

    listView.addCallback(XmNitemChangedCallback, this,
        (Callback)&ListViewColorChooser::itemChanged, NULL);

    listView.addCallback(XmNreturnCallback, this,
        (Callback)&ListViewColorChooser::clicked, NULL);

    selectedItemID = -1;

    return rc;
  }

private:
  long size(Event& event)
  {
    int width, height;
    event.getSize(width, height);

    ClientDC dc(this);
    int h = dc.getTextHeight();

    label.reshape(2,  4, width-4, h);

    int sx = GetSystemMetrics(SM_CXVSCROLL);
    listView.setColumnWidth(0, (width-sx)/2);
    listView.setColumnWidth(1, (width-sx)/2);
    
    listView.reshape(0,  h+6, width, height-h-6-2);

    return 0L;
  }

private:
  void clicked(Action& event)
  {
    TCHAR text[1024];
    if (selectedItemID>=0) {

      COLORREF color = (COLORREF)listView.getItemParam(selectedItemID);

      int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

      _stprintf_s(text, CountOf(text), _T("#%02X%02X%02X"), r, g, b);
      //label.setText(text);
  
      //colorBox.setColor(color);
      View* parent = getParent();
      if (parent) {
        parent->post(WM_COLORLISTVIEW_SELCHANGED, (WPARAM)getWindow(), (LPARAM)color);
      }
    }
  }

private:
  void itemChanged(Action& action) 
  {
    Event& event = action.getEvent();

    NM_LISTVIEW* nmlistv = (NM_LISTVIEW*)event.getLParam();
    selectedItemID = nmlistv->iItem;
    clicked(action);
  }
};

}

