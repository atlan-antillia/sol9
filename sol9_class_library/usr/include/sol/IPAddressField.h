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
 *  IPAddressField.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.08.14 Modified
// 2012/06/25

#pragma once

#include <sol\Primitive.h>


namespace SOL {

class IPAddressField :public Primitive {
public:
  IPAddressField():Primitive() { }

public:
  IPAddressField(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  IPAddressField(View* parent, const TCHAR* label, Args& args)
  :Primitive()
  {
    create(parent, label, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = Primitive::create(parent, label, 
      args.set(XmNpredefined, TRUE)
        .set(XmNuseDefaultFont, _T("true"))
        .set(XmNclassName, (LONG_PTR)WC_IPADDRESS) );

    setValues(args);

    return rc;
  }

  void  clearAddress() {
    send(IPM_CLEARADDRESS, 0, 0);
  }

  void  setAddress(int a, int b, int c, int d) {
    send(IPM_SETADDRESS, 0, MAKEIPADDRESS(a,b,c,d));  
  }

  void  setAddress(LPARAM address) {
    send(IPM_SETADDRESS, 0, address);
  }

  LRESULT  getAddress(LPARAM* address) {
    return (LRESULT)send(IPM_GETADDRESS, 0, (LPARAM)address);
  }

  void  setRange(int field, LPARAM range) {
    send(IPM_SETRANGE, field, range);
  }

  void  setFocus(int field) {
    send(IPM_SETFOCUS, field, 0);
  }


  BOOL  isBlank() {
    return (BOOL)send(IPM_ISBLANK, 0, 0);
  }
};

}
