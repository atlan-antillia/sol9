/******************************************************************************
 *
 * Copyright (c) 1999-2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OperationNotifier.h
 *
 *****************************************************************************/

#pragma once

#include <sol\PopupView.h>
#include <sol\Static.h>
#include <sol\TextField.h>
#include <sol\IntegerField.h>
#include <sol\PushButton.h>
#include <sol\MessageFont.h>
#include <sol/ClientDC.h>

//2009/10/18
#include <sol/StringT.h>

namespace SOL {

class OperationNotifier :public PopupView {
private:
  Static    label;
  MessageFont    font;

public:
  /**
   */
  OperationNotifier()
    :PopupView()
  {

  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = PopupView::create(parent, name, args);//.set(XmStyle, WS_POPUP));

    Args ar;
    font.create(9);
  
    ar.reset();
    label.create(this, name, ar);
    label.setFont(&font);


    addEventHandler(WM_GETMINMAXINFO, this,
      (Handler)&OperationNotifier::minMaxInfo, NULL);
  
    resize();

    return rc;
  }

private:
  long minMaxInfo(Event& event)
  {
      LPMINMAXINFO lpmm = (LPMINMAXINFO)event.getLParam();
       lpmm->ptMinTrackSize.x = 320;
       lpmm->ptMinTrackSize.y = 60;
       lpmm->ptMaxTrackSize.x = 600;
       lpmm->ptMaxTrackSize.y = 60;

    return 0;
  }

public:
  ~OperationNotifier()
  {
  }

  void  setLabel(const char* string) 
  { 
    label.setText(string); 
  }

  void  setLabel(const wchar_t* string) 
  { 
    label.setText(string); 
  }

private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);
    
    ClientDC cdc(this);
    HGDIOBJ prev = cdc.select(font);
    int h1 = cdc.getTextHeight() * 7/5;
    int fh = cdc.getTextHeight() + 8;
    cdc.select(prev);
    
    int w1 = 80;//button width;

    label.reshape(4, 4, w-8, fh);

    update(NULL);

    return 0L;
  }
};

}

