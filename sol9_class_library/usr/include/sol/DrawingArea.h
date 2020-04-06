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
 *  DrawingArea.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\Composite.h>
#include <sol\PaintDC.h>


namespace SOL {

class DrawingArea :public Composite {
private:

  long paint(Event& event)
  {
    PaintDC pdc(this);
    callCallback(XmNexposeCallback,
      (Key)getWindow(), &pdc, event);
    return 0L;
  }


  long size(Event& event)
  {
    return 0L;
  }

public:
  DrawingArea():Composite() { }

public:
  //2012/06/22
  DrawingArea(View* parent, const TCHAR* caption, Args& args)
  :Composite()
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = False;

    rc = Composite::create(parent, caption,  
      args.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE)
          .set(XmNclassName, _T("DrawingArea"))
        .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));

    addEventHandler(WM_PAINT, this,
      (Handler)&DrawingArea::paint, NULL);
    return rc;
  }

public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    // The name should be XmNexposeCallback.
    if(name == XmNexposeCallback) {
      View::addCallback(name, (Key)getWindow(), object, 
        callback, data);
    }
  }


};

}


