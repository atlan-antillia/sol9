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
 *  FindDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\CommonDialog.h>


namespace SOL {

class FindDialog :public CommonDialog {
private:
  TCHAR* findString;
  
private:
  FINDREPLACE  fr;
public:
  FindDialog():CommonDialog() { }

public:
  //2012/06/22
  FindDialog(View* parent, const TCHAR* name, Args& args)
  :CommonDialog()
  {
    create(parent, name, args);
  }

public:
  ~FindDialog() 
  {
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = CommonDialog::create(parent, &fr);

    findString    = new TCHAR[MAX_LEN];
    findString[0] = NULL;

    memset(&fr, 0, sizeof(FINDREPLACE));
    fr . lStructSize = sizeof(FINDREPLACE);

    if(parent) {
      fr . hwndOwner = parent -> getWindow();
    }
  
    fr . hInstance = GetModuleHandle(NULL);//Application::getInstance();

    fr . lpstrFindWhat = findString;
    fr . wFindWhatLen  = MAX_LEN;

    setValues(args);

    return rc;
  }

public:
  void find()
  {
    setWindow(::FindText(&fr));
  }

public:
  void find(TCHAR* string)
  {
    if(strlen(string) >= MAX_LEN) {
      *(string+ MAX_LEN-1) = NULL;
    }
    strcpy_s(findString, MAX_LEN, string);
    setWindow(::FindText(&fr));
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
      // </modifed>

      if (name == XmNflags) {
        *val = (LONG_PTR)fr.Flags;
        continue;
      }
      if (name == XmNfindString) {
        *val = (LONG_PTR)findString;
        continue;
      }
    }
  }

public:
  void setValues(Args& args)
  {
    LONG_PTR val;
    if (args.get(XmNflags, &val)) {
      fr . Flags |= (DWORD)val;
    }
    if (args.get(XmNhook, &val)) {
      fr . Flags |= FR_ENABLEHOOK;
      fr.lpfnHook = (LPFRHOOKPROC)hookProc; // 2017/9/10 (HOOKFUN)hookProc;
    }
    if (args.get(XmNfindString, &val)) {
      TCHAR* string = (TCHAR*)val;
      if(strlen(string) >= MAX_LEN) {
        *(string+MAX_LEN-1) = NULL;
      }
      strcpy_s(findString, MAX_LEN, string);
    }
  }


  DWORD   getFlag() { 
    return fr. Flags; 
  }

  TCHAR*  getFindString() {
    return findString;
  }
};

}

