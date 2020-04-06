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


#include <sol\Composite.h>
#include <sol\Static.h>
#include <sol\TrackBar.h>
#include <sol\ClientDC.h>

#include "resource.h"


namespace SOL {

#define WM_VALUESLIDER_CHANGED (WM_USER+2009)

class ValueSlider: public Composite {
private:
  Static    title;
  TrackBar  trackBar;
  Static    value;
  int       position;

public:
  ValueSlider()
  :Composite()
  {
  }

public:
  ValueSlider(View* parent, const TCHAR* name, Args& args)
  :Composite()
  {
    create(parent, name, args);
  }

public:

  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name, 
        args.set(XmNstyle, WS_CHILD|WS_CLIPCHILDREN)
            .set(XmNbackground, (COLOR_BTNFACE +1))
            .set(XmNclassName, _T("_ValueSlider_") ));
      
    const TCHAR* sliderTitle = (const TCHAR*)args.get(XmNsliderTitle);
      
    int sliderRange = (int)args.get(XmNsliderRange);
    if (sliderRange<=0) {
      sliderRange = 100; //_Default range
    }

    int sliderPosition = (int)args.get(XmNsliderPosition);
    if (sliderPosition<=0) {
      sliderPosition = sliderRange; //_Default range
    }

    Args ar;

    ar.reset();
    ar.set(XmNstyle, WS_VISIBLE);
    title.create(this, sliderTitle, ar);

    ar.reset();
    ar.set(XmNstyle, WS_VISIBLE);

    value.create(this, _T(""), ar);
  
    ar.reset();
    ar.set(XmNstyle, WS_VISIBLE);
    trackBar.create(this, NULL, ar);
    trackBar.setRange(0, sliderRange);
    trackBar.setPos(sliderPosition);

    position = sliderPosition;
  
    value.setText(position);

    addEventHandler(WM_SIZE, this, (Handler)&ValueSlider::size, NULL);
    return 0;
  }

  
public:
  void setPosition(int pos)
  {
    trackBar.setPos(pos);
    value.setText(pos);
  }

private:
  long size(Event& event)
  {
    int width, height;
    event.getSize(width, height);

    ClientDC dc(this);
    int h = dc.getTextHeight();
    const TCHAR* text = title.getText();
    SIZE extent;
    
    dc.getTextExtent(text, _tcslen(text), &extent);
    
    title.reshape(2, 4, extent.cx, h);

    trackBar.reshape(2+extent.cx, 2, 110, 30);
    
    value.reshape(2+extent.cx+110+2, 4, 60, h);

    return 0L;
  }

private:
  long horizScroll(Event& event)
  {
    int pos = (int)trackBar.getPos();
    position = pos;
    value.setText(position);

    View* parent = getParent();
    if (parent) {
      parent->post(WM_VALUESLIDER_CHANGED, (WPARAM)getWindow(), (LPARAM)pos);
    }

    return 0L;
  }
};


}

