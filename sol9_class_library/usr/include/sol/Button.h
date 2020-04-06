/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Button.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

#include <sol\Primitive.h>

namespace SOL {

class Button :public Primitive {
protected:
//  LRESULT  defaultProc(Event& event);

public:
  Button() :Primitive() { }

public:
  Button(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  Button(View* parent, const TCHAR* name, Args& args)
  :Primitive(parent, name, 
      args.set(XmNpredefined, True)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName, _T("Button")))
  {
    LONG_PTR val;
    if (args.get(XmNwidth, &val)  == False ||
      args.get(XmNheight, &val) == False) {
      const TCHAR*   label = name;
      if (args.get(XmNlabelString, &val))
        label = (TCHAR*)val;
      resize(label);
    }
  }

public:
  //<added date="2000.02.13">
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, True)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName, (LONG_PTR)_T("Button")));

    LONG_PTR val;
    if (args.get(XmNwidth, &val)  == False ||
      args.get(XmNheight, &val) == False) {
      const TCHAR*   label = name;
      if (args.get(XmNlabelString, &val))
        label = (TCHAR*)val;
      resize(label);
    }
    return rc;
  }

//</added>
public:
  LRESULT defaultProc(Event& event)
  {
    return discardInput(event);
  }

public:
  void disable()
  {
    if(isEditable()) {
      if(!getNewProc()) 
        replaceWindowProc();
    } else {
         View::disable();
    }
  }

public:
  void enable()
  {
    if(isEditable()) {
      restoreWindowProc();
    } else {
       View::enable();
    }
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
      {XmNactivateCallback,    BN_CLICKED},
     };
    *num = XtNumber(table);
    return table;
  }


  const TCHAR*  defaultCallbackName() 
  { 
    return XmNactivateCallback; 
  }

  
  int    getCheck() 
  {
      return (int)send(BM_GETCHECK, 0, 0L);
  }

  int    getState() 
  {
      return (int)send(BM_GETSTATE, 0, 0L);
  }

  void  setCheck(int check) 
  {
      send(BM_SETCHECK, check, 0L);
  }

  void  setState(int state) {
      send(BM_SETSTATE, state, 0L);
  }
  
  void check()
  {
    send(BM_SETCHECK, BST_CHECKED, 0);
  }

  void uncheck()
  {
    send(BM_SETCHECK, BST_UNCHECKED, 0); 
  }
  
  bool isChecked()
  {
    bool rc = false;
    int checked = getCheck();
    if (checked == BST_CHECKED) {
      rc = true;
    }
    return rc;
  }
};

}


