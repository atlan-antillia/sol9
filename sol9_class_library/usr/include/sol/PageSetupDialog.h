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
 *  PageSetupDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\CommonDialog.h>

namespace SOL {

class PageSetupDialog :public CommonDialog {
public:
  PageSetupDialog(): CommonDialog() { }

public:
  //2012/06/23
  PageSetupDialog(View* parent, const TCHAR* name, Args& args)
  :CommonDialog()
  {
    create(parent, name, args);
  }

public:
  ~PageSetupDialog() 
  {
    PAGESETUPDLG* pd = get();
    delete pd;
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = True;
    CommonDialog::create(parent, new PAGESETUPDLG);

    PAGESETUPDLG* pd = get();
    memset(pd, 0, sizeof(PAGESETUPDLG));
    pd -> lStructSize = sizeof(PAGESETUPDLG);
    pd -> hInstance  = GetModuleHandle(NULL);//Application::getInstance();

    if(parent) {
      pd -> hwndOwner = parent -> getWindow();
    }
    pd -> Flags   = PSD_DEFAULTMINMARGINS|PSD_INHUNDREDTHSOFMILLIMETERS;
    setValues(args);

    return rc;
  }

public:
  void getValues(Args& args)
  {
    PAGESETUPDLG* pd = get();
    LONG_PTR* val = NULL;
    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    for (int i = 0; i<num; i++) {
      const TCHAR* name = arg[i].name;
      *val = (LONG_PTR)arg[i].value;
      if (name == XmNflags) {
        *val = (LONG_PTR)pd->Flags;
        continue;
      }
    }
  }

public:
  void setValues(Args& args)
  {
    PAGESETUPDLG* pd = get();
    LONG_PTR val;
    if (args.get(XmNhook, &val)) {
      pd -> Flags |= PSD_ENABLEPAGESETUPHOOK;
      pd->lpfnPageSetupHook = (LPPAGESETUPHOOK)val; // (HOOKFUN)val;
    }
    if (args.get(XmNtemplateName, &val)) {
      pd -> Flags |= PSD_ENABLEPAGESETUPTEMPLATE;
      pd -> lpPageSetupTemplateName  = (TCHAR*)val;
    }
    if (args.get(XmNflags, &val)) {
      pd ->Flags |= (DWORD)val;
    }
  }

public:
  void popup(Action& action)
  {
    int result = pageSetup();
    action.setResult(result);
  }

  PAGESETUPDLG* get() {
    return (PAGESETUPDLG*)getCallData();
  }

  int  pageSetup() {
    return PageSetupDlg(get());
  }
/*
  void  getValues(Args& args);
  void  setValues(Args& args);

  void  popup(Action& action);
*/
};

}


