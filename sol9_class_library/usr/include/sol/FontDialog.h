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
 *  FontDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\CommonDialog.h>
#include <sol\Font.h>


namespace SOL {

class FontDialog :public CommonDialog {
private:
  LOGFONT      lf;
  
private:
  CHOOSEFONT cf;


public:
  FontDialog():CommonDialog() { }

public:
  //2012/06/22
  FontDialog(View* parent, const TCHAR* name, Args& args)
  :CommonDialog()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = CommonDialog::create(parent, &cf);

    memset(&cf, 0, sizeof(CHOOSEFONT));
    cf . lStructSize = sizeof(CHOOSEFONT);
    cf . lpLogFont = &lf;
    cf . Flags     = CF_SCREENFONTS|CF_EFFECTS;
    cf . nFontType = SCREEN_FONTTYPE;

    if(parent) {
      cf . hwndOwner = parent -> getWindow();
    }

    cf . hInstance = GetModuleHandle(NULL);//Application::getInstance();

    setValues(args);

    return rc;
  }


public:
  ~FontDialog() 
  {
  }

public:
  void getValues(Args& args)
  {
    LONG_PTR* val = NULL;
    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    for (int i = 0; i<num; i++) {
      const TCHAR* name = arg[i].name;
      // <modified date="2000.01.09">
      val = (LONG_PTR*)arg[i].value;
      //</modified>

      if (name == XmNflags) {
        *val = (LONG_PTR)cf.Flags;
        continue;
      }
      if (name == XmNtype) {
        *val = (LONG_PTR)cf . nFontType;
        continue;
      }
      if (name == XmNminimum) {
        *val = (LONG_PTR)cf . nSizeMin;
        continue;
      }
      if (name == XmNmaximum) {
        *val = (LONG_PTR)cf . nSizeMax;
        continue;
      }
      if (name == XmNlogicalFont) {
        *val = (LONG_PTR)cf . lpLogFont;
        continue;
      }
    }
  }


public:
  void setValues(Args& args)
  {
    LONG_PTR val;
    if (args.get(XmNdc, &val)) {
      cf . Flags |= CF_PRINTERFONTS;
      cf . nFontType |= PRINTER_FONTTYPE;
      cf . hDC = (HDC)val;
    }
    if (args.get(XmNhook, &val)) {
      cf . Flags |= CF_ENABLEHOOK;
      cf . lpfnHook = (LPCCHOOKPROC)hookProc;
    }
    if (args.get(XmNflags, &val)) {
      cf .Flags |= (DWORD)val;
    }
    if (args.get(XmNtype, &val)) {
      cf . nFontType = (UINT)val;
    }
    if (args.get(XmNtemplateName, &val)) {
      cf . Flags |= CF_ENABLETEMPLATE;
      cf . lpTemplateName  = (TCHAR*)val;
    }
    if (args.get(XmNminimum, &val)) {
      cf . nSizeMin = (int)val;
    }
    if (args.get(XmNmaximum, &val)) {
      cf . nSizeMax = (int)val;
    }
  }

public:
  int choose()
  {
    return ::ChooseFont(&cf);
  }

public:
// Modal popup
  void popup(Action& action)
  {
    int result = choose();
  
    action.setResult(result);
  }

public:
  LOGFONT getLogicalFont() {
      return lf;
  }

public:
  Font*  getFont() {
      return new Font(&lf);
  }

//  void  getValues(Args& args);
//  void  setValues(Args& args);

//  void  popup(Action& action);
};

}


