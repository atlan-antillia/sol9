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
 *  SysLink.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/13
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class SysLink :public Primitive {

public:
  SysLink() :Primitive() { }

public:
  SysLink(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  SysLink(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, True)
        .set(XmNstyle, WS_CHILD|WS_TABSTOP)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName, _T("SysLink")));
    //WC_LINK;

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



public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
      {XmNactivateCallback, NM_CLICK},
      {XmNactivateCallback,   NM_RETURN},
     };
    *num = XtNumber(table);
    return table;
  }


  const TCHAR*  defaultCallbackName() { 
    return XmNactivateCallback; 
  }

  

};

}


