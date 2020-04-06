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
 *  LabeledTrackBar.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Composite.h>

#include <sol/Static.h>
#include <sol/TrackBar.h>

namespace SOL {

class LabeledTrackBar :public Composite {
private:
  Static    label;
  Static    value;
  int       displayDigit;
  int       minimum;
  int       maximum;
  TrackBar  trackBar;
  bool      displayOddValue;
  bool      displayFloatValue;
  static const int DEFAULT_WIDTH = 170;
  static const int DEFAULT_HEIGHT = 60;
private: 
  virtual long horizScroll(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();

    int  diff = 0;

    if(hwnd) { // scrollbar control.
      ScrollBar* scb = (ScrollBar*)Application::lookup(hwnd);
      if(scb)  diff = scb -> moveThumb(event);
    }
    else {     // standard scrollbar
      hwnd = getWindow();
      diff = moveThumb(event, SB_HORZ);
    }
    // TCHAR  buffer[10];
    //setValue(pos);
    int pos = trackBar.getPos();
    setValue(pos);
    /*
    if (displayOddValue) {
      pos = (pos/2)*2 + 1;
    }
    _stprintf_s(buffer, CountOf(buffer),_T("%d"),  pos);
    value.setText(buffer);
   */
    callCallback(XmNtrackBarScrollCallback, (Key)hwnd, (void*)diff, event);
    return 1;
  }

private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);

    ClientDC cdc(this);
    Size size;
    cdc.getTextExtent(_T("A"), 1, &size);
    int h1 = size.cy;
    int w1 = size.cx;
    int margin = 0;
    label.reshape(margin, margin, w-margin*2, h1);
    int top = h1;
    trackBar.reshape(margin,       top, w- w1*displayDigit, h- margin*2 - h1);
    value   .reshape(margin*2+ w- w1*displayDigit + margin, top, 
      w1*(displayDigit+1), h1);

    return 0L;
  }

  
public:
  LabeledTrackBar()
    :Composite(),
  displayDigit(4),
  displayOddValue(true)
  {
  }

public:
  /**
   * Constructor
   */
  LabeledTrackBar(View* parent, const TCHAR* caption, Args& args)
  :Composite(),
  displayDigit(4),
  displayOddValue(true),
  displayFloatValue(false)
  {
    create(parent, caption, args);
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = Composite::create(parent, caption, 
          args.set(XmNstyle, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_CHILD|WS_VISIBLE)
              .set(XmNclassName, _T("_LabeledTrackBar_"))
            //  .set(XmNexStyle, (LONG_PTR)(WS_EX_TRANSPARENT|WS_EX_CONTROLPARENT))
              .set(XmNbackground, (COLOR_BTNFACE+1)));

    const TCHAR* title = caption;
    const TCHAR* string = (const TCHAR*)args.get(XmNlabelString); 
    if (string) {
      title = string;
    }
    minimum = (int)args.get(XmNminimum);
    maximum = (int)args.get(XmNmaximum);
    if (maximum == 0) {
      maximum = 128;
    }
    
    if (args.has(XmNdisplayDigit)) {
      displayDigit = (int)args.get(XmNdisplayDigit);
    }
    
    displayFloatValue = false;
    if (args.has(XmNdisplayFloatValue)) {
      displayFloatValue = (bool)args.get(XmNdisplayFloatValue);
    }
    
    TCHAR name[256];
    if (displayFloatValue) {
    _stprintf_s(name, CountOf(name), _T("%s [%1.2f, %1.2f]"), title, (float)minimum, (float)maximum/100.0f);

    } else {
    
    _stprintf_s(name, CountOf(name), _T("%s [%d, %d]"), title, minimum, maximum);
    }
    Args ar;
    ar.set(XmNstyle, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_CHILD);
    label.create(this, name, ar);
    
    int position = (int)args.get(XmNposition);
    if (position < minimum) {
      position = minimum;
    }
    if (position > maximum) {
      position = maximum;
    }

    if (args.has(XmNdisplayOddValue)) {
      displayOddValue = (bool)args.get(XmNdisplayOddValue);
    }

    ar.reset();
    ar.set(XmNstyle, (LONG_PTR)SS_LEFT|WS_CLIPCHILDREN|WS_CLIPSIBLINGS| WS_CHILD);
    value.create(this, _T(""), ar);
    
    setValue(position);
    
    ar.reset();
    ar.set(XmNstyle, TBS_AUTOTICKS |TBS_ENABLESELRANGE|
              WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_CHILD); 
    trackBar.create(this, _T(""), ar);
  
    trackBar.setRange(minimum, maximum);
    trackBar.setPos(position);
      
    return rc;
  }
  
public:
  ~LabeledTrackBar()
  {
  }
  
  void addCallback(const TCHAR* name, Object* object, 
          Callback callback, void* data)
  {
    if (name == XmNtrackBarScrollCallback) {
      trackBar.addCallback(XmNtrackBarScrollCallback, object,
        callback, data);
    }
  }
  
  
  void getPreferredSize(Dimension& dim)
  {
    dim.set(DEFAULT_WIDTH,  DEFAULT_HEIGHT);
  }
  
  
  int getDefaultHeight()
  {
    return DEFAULT_HEIGHT;
  }
  
  int getPosition()
  {
    return trackBar.getPos();
  }

  void setPosition(int position)
  {
    trackBar.setPos(position);
    int pos = trackBar.getPos();
    
    setValue(pos);
  }
  
  void setValue(int pos)
  {
    const TCHAR* format = _T("%d");  
    TCHAR buffer[20];

    if (displayOddValue) {
      pos = (pos/2)*2 + 1;
    }
    if (displayFloatValue) {
      _stprintf_s(buffer, CountOf(buffer), _T("%1.2f"),  (float)pos/100.0f);      
    } else {
      _stprintf_s(buffer, CountOf(buffer), _T("%d"),  pos);  
    }
    value.setText(buffer);
  }
  
  HWND getTrackBarWindow()
  {
    return trackBar.getWindow();
  }  
};

}
