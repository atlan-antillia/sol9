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
 *  LabeledComboBox.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Composite.h>

#include <sol/Static.h>
#include <sol/ComboBox.h>

namespace SOL {

class LabeledComboBox :public Composite {
private:
  Static    label;
  ComboBox  comboBox;

  static const int DEFAULT_WIDTH  = 190;
  static const int DEFAULT_HEIGHT = 140; //Combobox height, not Composite size
  static const int DEFAULT_CONTAINER_HEIGHT = 50;
private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);

    ClientDC cdc(this);
    SOL::Size size;
    cdc.getTextExtent(_T("A"), 1, &size);
    int h1 = size.cy;
    int w1 = size.cx;
    int margin = 0;
    label.reshape(margin, margin, w-margin*2, h1);
    int top = h1;
    comboBox.reshape(margin,       top, w, DEFAULT_HEIGHT);
    comboBox.setDroppedWidth(w-margin*2);
    return 0L;
  }

  
public:
  LabeledComboBox()
  :Composite()
  {
  }

public:
  /**
   * Constructor
   */
  LabeledComboBox(View* parent, const TCHAR* caption, Args& args)
  :Composite()
  {
    create(parent, caption, args);
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, args.set(XmNstyle, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_CHILD|WS_VISIBLE)
      .set(XmNclassName, _T("_LabeledComboBox_"))
      .set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
      .set(XmNbackground, (COLOR_BTNFACE+1)));

    const TCHAR* title = caption;
    const TCHAR* string = (const TCHAR*)args.get(XmNlabelString); 
    if (string) {
      title = string;
    }
    
    Args ar;
    ar.set(XmNstyle, WS_CHILD);
    label.create(this, title, ar);

    ar.reset();
    ar.set(XmNstyle, CBS_DROPDOWNLIST|  WS_CHILD); 
    comboBox.create(this, _T(""), ar);
    comboBox.setExtendedUI(TRUE);
    
    addEventHandler(WM_SIZE, this,
      (Handler)&LabeledComboBox::size, NULL);
    return rc;
  }
  
public:
  ~LabeledComboBox()
  {
  }

  
  void addCallback(const TCHAR* name, Object* object,
    Callback callback, void* data)
  {
    comboBox.addCallback(name, object,
        callback, data);
  }
  
  void getPreferredSize(Dimension& dim)
  {
    dim.set( DEFAULT_WIDTH, DEFAULT_CONTAINER_HEIGHT);
  }
  
  String getCurrentSelection()
  {
    return comboBox.getCurrentSelection();
  }

  int getCurSel()
  {
    return comboBox.getCurSel();
  }

  void addString(const TCHAR* string)
  {
    comboBox.addString(string);
  }

  void addString(const WString* string)
  {
    comboBox.addString(string);
  }
  
  void getString(int index, String& string)
  {
    comboBox.getString(index, string);
  }
  
  void getString(int index, WString& string)
  {
    comboBox.getString(index, string);
  }
  
  int getDefaultWidth()
  {
    return DEFAULT_WIDTH; 
  }
  
  int getDefaultHeight()
  {
    return DEFAULT_HEIGHT; 
  }

  void setCurrentSelection(int index)
  {
    comboBox.setCurSel(index);
  }

  void setCurSel(int index)
  {
    comboBox.setCurSel(index);
  }
  
  void clear()
  {
    comboBox.clear();
  }
  
  HWND getComboBoxWindow()
  {
    return comboBox.getWindow();
  }  
};

}
