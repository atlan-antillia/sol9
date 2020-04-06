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
 *  PromptDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\PopupView.h>
#include <sol\TextField.h>

#include <sol\PushButton.h>
#include <sol/MessageFont.h>


namespace SOL {

class PromptDialog :public PopupView {
private:
  //TextField   textf;
  Text  textf;

  PushButton  ok;
  PushButton  cancel;

private:
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);

    ClientDC cdc(this);
    int h1 = cdc.getTextHeight() * 7/4;
    int w1 = (w - 40)/3;

    textf .reshape(10, 10, w-20, h1);
    ok    .reshape(20, h-h1-10, w1, h1);
    cancel.reshape(20+w1*2, h-h1-10, w1, h1);

    update(NULL);

    return NULL;
  }

 
public:
  PromptDialog(): PopupView() { }

public:
  /**
   * Constructor
   */
  //2012/06/25
  PromptDialog(View* parent, const TCHAR* label, Args& args)
  :PopupView()
  {
    create(parent, label, args);
  }

public:
  ~PromptDialog()
  {
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = PopupView::create(parent, label, 
        args.set(XmNstyle, (LONG_PTR)WS_THICKFRAME));

    Args ar;
    textf.create(this, _T(""), ar);

    ar.reset();
    ar.set(XmNid, IDOK);
    ok.create(this, _T("Ok"), ar);

    ar.reset();
    ar.set(XmNid, IDCANCEL);
    cancel.create(this, _T("Cancel"), ar);
    cancel.addCallback(XmNactivateCallback, this, 
        (Callback)&PromptDialog::popdown, NULL);

    addEventHandler(WM_SIZE, this,
      (Handler)&PromptDialog::size, NULL);

    resize();

    return rc;
  }


/*public:
  TextField&   getTextField() { 
    return textf; 
  }
*/
public:
  PushButton&  getOkButton() { 
    return ok; 
  }

public:  
  void  popup(Action& action)
  {
    textf.setSel(0, 256);
    textf.setFocus();
    PopupView::popup(action);
  }
public:
  void addOkCallback(View* object, Callback callback, void* userData)
  {
    ok.addCallback(XmNactivateCallback, this, 
        callback, NULL);
  }

public:
  int getPrompt(StringT<wchar_t>& text)
  {
    wchar_t buff[256];
    HWND hwn = textf.getWindow();
    if (hwn) {
      MessageBox(NULL, _T("this is a window"), _T("Prompter"), MB_OK);
    } else {
      MessageBox(NULL, _T("this is not a window"), _T("Prompter"), MB_OK);
      
    }
    GetWindowText(hwn, buff, 256);
    text = buff;
    return 0;
    //return textf.getText(text);      
  }
};

}



