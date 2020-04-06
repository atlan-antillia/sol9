/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectXView.h
 *
 *****************************************************************************/

//2015/10/01

#pragma once

#include <sol/ClientDC.h>

#include <sol/Primitive.h>
#include <sol/PaintDC.h>
#include <sol/wic/WICImagingFactory.h>
#include <sol/directx/Direct2D1Factory.h>
#include <sol/directx/DirectWriteFactory.h>
#include <sol/directx/DirectXMainView.h>
#include <sol/directx/Direct2D1HwndRenderTarget.h>

#include <sol/Stdio.h>

namespace SOL {

class DirectXView :public Primitive {

private:
  //Shallow copies from the parent (DirectXMainView)
  WICImagingFactory*  imagingFactory;
  Direct2D1Factory*   d2d1Factory;
  DirectWriteFactory* writeFactory;


private:
  
  long eraseBackground(Event& event)
  {
    return 1L;
  }

  long paint(Event& event)
  {
    PaintDC dc(this);
    {
    //Call a virtual display method.
      display();
    }
    return 1L;
  }

  long size(Event& event)
  {
    int w = 0;
    int h = 0;
    event.getSize(w, h);
	//Call a virtual resize method.
    resize(w, h);
    
    return 1L;
  }

  long lButtonDown(Event& event)
  {
    leftButtonDown(event);
    return 0L;
  }


  long lButtonUp(Event& event)
  {
    leftButtonUp(event);
    return 0L;
  }

  long kDown(Event& event)
  {
    keyDown(event);
    return 0L;
  }

  long kUp(Event& event)
  {
    keyUp(event);
    return 0L;
  }
   //Please define your own display method in subclass derived form this class.
public:
  virtual void display()
  {
  }

   //Please define your own resize method in subclass derived form this class.
  virtual void resize(int w, int h)
  {
  }
  
  //Please define your own method in subclass derived form this class.
  virtual void leftButtonUp(Event& event)
  {
  }
  
  virtual void leftButtonDown(Event& event)
  {
  }

  //Please define your own method in subclass derived form this class.
  virtual void keyDown(Event& event)
  {
  }
  
  virtual void keyUp(Event& event)
  {
  }


public:
  WICImagingFactory*  getImagingFactory()
  {
  return imagingFactory;
  }

  Direct2D1Factory*   get2D1Factory()
  {
   return d2d1Factory;
  }

  DirectWriteFactory* getWriteFactory()
  {
  return writeFactory;
  }

public:
  //Constructor
  DirectXView()
  :Primitive(),
  imagingFactory(NULL),
  d2d1Factory(NULL),
  writeFactory(NULL)
  { 
  }

public:
  //Constructor
  DirectXView(DirectXMainView* parent, const TCHAR* caption, Args& args)
  :Primitive(),
  imagingFactory(NULL),
  d2d1Factory(NULL),
  writeFactory(NULL)
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(DirectXMainView* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = False;
    try {
      imagingFactory  = parent -> getImagingFactory();
      d2d1Factory     = parent -> getD2D1Factory();
      writeFactory    = parent -> getWriteFactory();
    
      rc = Primitive::create(parent, caption,  
                args.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE)
                    .set(XmNclassName, _T("DirectXView")) 
                     .set(XmNclassStyle, (LONG_PTR)CS_VREDRAW|CS_HREDRAW));
    
      addEventHandler(WM_PAINT, this,
                    (Handler)&DirectXView::paint, NULL);
    
      addEventHandler(WM_SIZE, this,
                    (Handler)&DirectXView::size, NULL);
    
      addEventHandler(WM_LBUTTONDOWN, this,
                    (Handler)&DirectXView::lButtonDown, NULL);
      addEventHandler(WM_LBUTTONUP, this,
                    (Handler)&DirectXView::lButtonUp, NULL);
    
      addEventHandler(WM_KEYDOWN, this,
                    (Handler)&DirectXView::kDown, NULL);
      addEventHandler(WM_KEYUP, this,
                    (Handler)&DirectXView::kUp, NULL);

    } catch (Exception& ex) {
      ex.display();
    }  
    return rc;
  }

  ~DirectXView()
  {
  }
};

}
