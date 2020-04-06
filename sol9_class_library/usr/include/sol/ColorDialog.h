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
 *  ColorDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\CommonDialog.h>

namespace SOL {

class ColorDialog :public CommonDialog {
private:
  COLORREF   custColors[16];

private:
  CHOOSECOLOR    cc;

public:
   ColorDialog():CommonDialog() { }

public:
  //2012/06/22
  ColorDialog(View* parent, const TCHAR* name, Args& args)
  :CommonDialog()
  {
    create(parent, name, args);
  }

public:
  ~ColorDialog() 
  {
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = True;
    CommonDialog::create(parent, &cc);

    for(int i = 0; i<16; i++) {
      custColors[i] = RGB(255, 255, 255);
    }
    memset(&cc, 0, sizeof(CHOOSECOLOR));

    cc . lStructSize = sizeof(CHOOSECOLOR);
    cc . Flags      = CC_FULLOPEN;
    cc . rgbResult   = RGB(255, 255, 255);
    cc . lpCustColors = custColors;

    if(parent) {
      cc . hwndOwner = parent -> getWindow();
    }  

    cc . hInstance = (HWND)GetModuleHandle(NULL);//(HWND)Application::getInstance();

    setValues(args);

    return rc;
  }

public:
  void getValues(Args& args)
  {
    LONG_PTR* val = NULL;
    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    for(int i = 0; i<num; i++) {
      const TCHAR* name = arg[i].name;
      // <modified date="2000.01.09">
      val = (LONG_PTR*)arg[i].value;
      // </modified>

      if(name == XmNflags) {
        *val = (LONG_PTR)cc.Flags;
        continue;
      }
      if(name == XmNrgbResult) {
        *val = (LONG_PTR)cc.rgbResult;
        continue;
      }
    }
  }


public:
  void setValues(Args& args)
  {
    LONG_PTR val;
    if (args.get(XmNhook, &val)) {
      cc . Flags |= CC_ENABLEHOOK;
      cc . lpfnHook = (LPCCHOOKPROC)hookProc;
    }
    if (args.get(XmNflags, &val)) {
      cc . Flags |= (DWORD)val;
    }
    if (args.get(XmNtemplateName, &val)) {
      cc . Flags |= CC_ENABLETEMPLATE;
      cc . lpTemplateName  = (TCHAR*)val;
    }
  }

public:
  int  choose()
  {
    return ::ChooseColor(&cc);
  }

public:
  void popup(Action& action)
  {
    int result = choose();
    action.setResult(result);
  }


  COLORREF getRGBResult() {
      return cc.rgbResult;
  }

  COLORREF* getCustomColors() {
      return custColors;
  }

};

}


