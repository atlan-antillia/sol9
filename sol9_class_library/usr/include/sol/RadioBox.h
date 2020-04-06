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
 *  RadioBox.h
 *
 *****************************************************************************/

// SOL9
// 2017/09/25 Updated

#pragma once

#include <sol/RowColumn.h>
#include <sol/GroupBox.h>
#include <sol/RadioButton.h>
#include <sol/ClientDC.h>
#include <sol/ApplicationView.h>


namespace SOL {

class RadioBox :public RowColumn {
private:
  int            num;
  GroupBox*      frame;
  RadioButton**  radiob;
  
private:
  void checked(Action& action)
  {
    RadioButton* rb = (RadioButton*)action.getData();
    for (int i = 0; i<num; i++) {
      if (radiob[i]->isChecked()) {
        radiob[i]->uncheck();
      }
    }
    
    if (rb) {
      rb->check();
      Event event(WM_COMMAND, BST_CHECKED, (LPARAM)rb);
      callCallback(XmNcheckedCallback, (Key)getWindow(), NULL, event);
    }
  }
  
public:
  //2017/09/25
  RadioBox(View* parent, const TCHAR* name, Args& args)
  :RowColumn(parent, name,
                args.set(XmNstyle, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_CHILD|WS_VISIBLE)
                .set(XmNclassName, _T("_RadioBox_"))
                //.set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
                .set(XmNbackground, (COLOR_BTNFACE+1)))
  {
    num = (int) args.get(XmNitemCount);
    int orientation = (int)args.get(XmNorientation);
    
    TCHAR** items = (TCHAR**)args.get(XmNitems);
    radiob = new RadioButton*[num];
    int sx = 6;
    int sy = 4;
    if (name != NULL) {
      sy += 20;
    }
    int x = sx;
    int y = sy;
    Args ar;
    int bw = 0;
    int bh = 0;
    int w  = 0;
    int h  = 0;
    if (orientation == RowColumn::HORIZ_ORIENTATION) {
      
      for(int i = 0; i<num; i++) {
        ar.reset();
        ar.set(XmNx, x);
        ar.set(XmNy, y);
        radiob[i] = new RadioButton(this, items[i], ar);
        radiob[i] -> addCallback(XmNactivateCallback, this,
            (Callback)&RadioBox::checked, radiob[i]);
        Dimension d;
        radiob[i]->getPreferredSize(d);
        
        d.get(w, h);
        x += (w + 0);
        bw += w;
        bh  = h;
      }
      if (name) {
        ar.reset();
        ar.set(XmNx, 2);
        ar.set(XmNy, sy- bh/2-4);
        ar.set(XmNwidth, bw + 30);
        ar.set(XmNheight,bh * 2); 
        ar.set(XmNbackground, (COLOR_BTNFACE+1));
        frame = new GroupBox(this, name, ar);
      }
    } else 
    if (orientation == RowColumn::VERT_ORIENTATION) {
      x = sx;
      y = sy;
      bw = 0;
      bh = 0;
      w  = 0;
      h  = 0;
      for(int i = 0; i<num; i++) {
        ar.reset();
        ar.set(XmNx, x);
        ar.set(XmNy, y);
        radiob[i] = new RadioButton(this, items[i], ar);
        radiob[i] -> addCallback(XmNactivateCallback, this,
          (Callback)&RadioBox::checked,  radiob[i]);
        
        Dimension d;
        radiob[i]->getPreferredSize(d);  
        d.get(w, h);
        y += (h + 0);
        if (w >bw) { 
           bw = w;
        }
        bh += h;
      }
      if (name) {
        ar.reset();
        ar.set(XmNx, 2);
        ar.set(XmNy, sy-20);
        ar.set(XmNwidth, bw + h/2);
        ar.set(XmNheight,bh + h); 
        ar.set(XmNbackground, (COLOR_BTNFACE+1));
        frame = new GroupBox(this, name, ar);
      }
    }
  }

public:
  ~RadioBox()
  {
    delete frame;
    for(int i = 0; i<num; i++) {
      delete radiob[i];
    }
    delete [] radiob;
  }
  
public:
  int  getCheck(int pos)
  {
    int rc = FALSE;
    if(pos >= 0 && pos < num) {
      rc = radiob[pos] ->getCheck();
    }
    return rc;
  }

public:
  void setCheck(int pos)
  {
    if(pos >= 0 && pos < num) {
      radiob[pos] -> setCheck(TRUE);
    }
  }
 
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    if (name  == XmNcheckedCallback) {
      RowColumn::addCallback(name, (Key)getWindow(), object, callback, data);
    }
  }
};

}


