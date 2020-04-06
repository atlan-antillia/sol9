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
 *  ComboBoxColorChooser.cpp
 *
 *****************************************************************************/


// SOL9 2.0 
// 2012/05/28 Sample program to use SOL::ColorComboBox class
// 2012/06/16 Added reshape method.

#include <sol\Composite.h>
#include <sol\Static.h>
#include <sol\ClientDC.h>
#include <sol\ColorComboBox.h>

namespace SOL {

#define WM_COMBOBOX_COLORCHOOSER_SELCHANGED (WM_USER+1991)

class ComboBoxColorChooser :public Composite {

private:
  Static         label;
  ColorComboBox  comboBox;
  int            selectedItemID;

  
public:
  ComboBoxColorChooser()
    :Composite()
  {
  }

public:
  ComboBoxColorChooser(View* parent, const TCHAR* caption, Args& args)
        :Composite() 
  {
    create(parent, caption, args);
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, 
            args.set(XmNstyle, WS_CHILD|WS_CLIPCHILDREN)
            .set(XmNbackground, (COLOR_BTNFACE +1))
            //.set(XmNexStyle, WS_EX_TRANSPARENT)  //2012/06/16
            .set(XmNclassName, _T("_ComboBoxColorChooser_") ));

    const TCHAR* chooserTitle = (const TCHAR*)args.get(XmNcolorChooserTitle);
      

    Args ar;
    ar.reset();
    label.create(this, chooserTitle, ar);
  
    int height = (int)args.get(XmNitemHeight);
    if (height <=0) {
      height = 32;
    }

    int step = (int)args.get(XmNrgbStep);
    if (step <=0) {
      step = 0x20;
    }

    ar.reset();
    ar.set(XmNitemHeight, height);
    //ar.set(XmNrgbStep, 0x33);
    ar.set(XmNrgbStep, step);

    comboBox.create(this, NULL, ar);

    addEventHandler(WM_DRAWITEM, &comboBox, 
      (Handler)&ColorComboBox::drawItem, NULL);

    addEventHandler(WM_MEASUREITEM, &comboBox, 
      (Handler)&ColorComboBox::measureItem, NULL);

    comboBox.addCallback(XmNselChangeCallback, this, 
        (Callback)&ComboBoxColorChooser::selected, NULL);

    int count = comboBox.getCount();
    selectedItemID = count-1;

    comboBox.setCurSel(count-1);
    
    return rc;
  }
  
public:
  void initSelection()
  {
    int count = comboBox.getCount();
    selectedItemID = count-1;

    comboBox.setCurSel(count-1);
  }


public:
  void disable()
  {
    label.disable();
    comboBox.disable();
  }

public:
  void enable()
  {
    label.enable();
    comboBox.enable();

  }

public:
  COLORREF getCurrentColor()
  {
    COLORREF color =RGB(0xff, 0xff, 0xff);

    int n = comboBox.getCurSel();
    if (n >= 0) {
      color = comboBox.getItemData(n);
    }
    return color;
  }

public:
  void setCurrentSelection(int index)
  {
    int count = comboBox.getCount();
    if (index <count) {
      selectedItemID = index;
      comboBox.setCurSel(index);
    }
  }

  void setCurrentSelection(TCHAR* colorName) //char* colorName)  //
  {
    int count = comboBox.getCount();
    int index = comboBox.findString(0, colorName);
    if (index >=0 && index <count) {
      comboBox.setCurSel(index);
    }
  }

public:
  //2012/06/16
  virtual void  reshape(int x, int y, int width, int height, Boolean flag = TRUE) 
  {
    int ch = comboBox.getControlHeight()+8;

    ::MoveWindow(getWindow(), x, y, width, ch, flag);
    send(WM_SIZE, 0, MAKELONG(width, height));

  }

private:
  void selected(Action& action)
  {
    int n = comboBox.getCurSel();
    if (n >= 0) {

      COLORREF color = comboBox.getItemData(n);
      View* parent = getParent();
      if (parent) {
        parent->post(WM_COMBOBOX_COLORCHOOSER_SELCHANGED, (WPARAM)getWindow(), (LPARAM)color);
      }
    }
  }


private:
  long size(Event& event)
  {
    int width, height;
    event.getSize(width, height);

    ClientDC dc(this);
    int h = dc.getTextHeight();

    const TCHAR* text = label.getText();
    SIZE extent;
    
    dc.getTextExtent(text, _tcslen(text), &extent);

    label.reshape(2,  4, extent.cx, h);
    int ch = comboBox.getControlHeight();
    comboBox.reshape(2+ extent.cx, 2, width - 6-extent.cx, height);

    return 0L;
  }
};

}

