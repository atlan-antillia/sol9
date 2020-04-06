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
 *  DrawnButton.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\Label.h>


namespace SOL {

class DrawnButton :public Label {
private:
  int        capturing;

protected:
  long leftButtonDown(Event& event)
  {
    capture();  

    capturing = TRUE;
    if(capturing == TRUE) {
      callCallback(XmNarmCallback, (Key)getWindow(), this, event);
    }
    return NULL;
  }


  long mouseMove(Event& event)
  {
    POINT p;

    RECT r;

    ::GetCursorPos(&p);
    ::GetWindowRect(getWindow(), &r);

    if(capturing == TRUE && ((p.x < r.left) || 
      (p.y < r.top) || (p.x > r.right) || (p.y > r.bottom))) {
      releaseCapture();
      capturing = FALSE;
    }
    return NULL;
  }

  long leftButtonUp(Event& event)
  {
    if(capturing == TRUE) {
      callCallback(XmNactivateCallback, 
        (Key)getWindow(), this, event);
      releaseCapture();
    }
    capturing = FALSE;
    return NULL;
  }


public:

  DrawnButton():Label() { }

public:
  //2012/06/22
  DrawnButton(View* parent, const TCHAR* label, Args& args)
  :Label()
  {
    create(parent, label, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {  
    Boolean rc = False;
    rc = Label::create(parent, label, args);

    addEventHandler(WM_LBUTTONDOWN, this,
      (Handler)&DrawnButton::leftButtonDown, NULL);
    addEventHandler(WM_MOUSEMOVE, this,
      (Handler)&DrawnButton::mouseMove, NULL);
    addEventHandler(WM_LBUTTONUP, this,
      (Handler)&DrawnButton::leftButtonUp, NULL);
    return rc;
  }


public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }

};

}


