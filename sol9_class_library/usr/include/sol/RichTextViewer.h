/******************************************************************************
 *
 * Copyright (c) 1999-2012  TOSHIYUKI ARAI. ALL RIGHTS RESERVED. 
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
 *  RichTextViewer.h
 *
 *****************************************************************************/

// 2012/06/25

#include <sol\PopupView.h>
#include <sol\FileDialog.h>
#include <sol\ScrolledRichText.h>
#include <sol\Font.h>
#include <sol\FontDialog.h>
#include <sol\ClientDC.h>
#include <sol\FileStream.h>
#include <sol/MessageFont.h>
#include "resource.h"

namespace SOL {

class RichTextViewer :public PopupView {

private:
  ScrolledRichText  text;
  MessageFont    font;


public:
  RichTextViewer()
  :PopupView()
  {

  }  


public:
  //2012/06/25
  RichTextViewer(View* parent, const TCHAR* name, Args& args)
  :PopupView()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = PopupView::create(parent, name, args.set(XmNstyle, WS_THICKFRAME));

    Args  ar;
    ar.set(XmNexStyle, (LONG_PTR)WS_EX_ACCEPTFILES);
    text.create(this, NULL, ar);
    //add(text);

    text.setEventMask(ENM_DROPFILES);
    text.addCallback(XmNdropFilesCallback, this,
      (Callback)&RichTextViewer::dropped, NULL);

    addEventHandler(WM_SIZE, this,
      (Handler)&RichTextViewer::size, NULL);

    font.create(9);
    text.setFont(font);

    resize();

    return rc;
  }

private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);
    text.reshape(0, 0, w, h);

    return 0;
  }

public:
  void setCaption(TCHAR* filename)
  {
    if(filename) {
      TCHAR text[MAX_PATH];
      _stprintf_s(text, CountOf(text), _T("%s - RichTextEditor"), filename);
      setText(text);
    }
  }

public:

  void openRTF(TCHAR* filename)
  {
    if (filename) {
      text.streamIn(filename, SF_RTF);
      setCaption(filename);
    }
  }

public:

  void openText(TCHAR* filename)
  {
    if (filename) {
      text.streamIn(filename, SF_TEXT);
      setCaption(filename);
    }
  }

public:
  void dropped(Action& action)
  {
    Event& event = action.getEvent();
    ENDROPFILES* endrop = (ENDROPFILES*)event.getLParam();
    HDROP hdrop = (HDROP)endrop->hDrop;
    TCHAR filename[_MAX_PATH];
    ::DragQueryFile(hdrop, 0, filename, CountOf(filename)); //2012/06/21

    text.streamIn(filename, SF_TEXT|SFF_SELECTION);

  }


public:
  void  clear(Action& action) 
  { 
    text.clear();
  }

};

}

