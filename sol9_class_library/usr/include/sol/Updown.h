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
 *  Updown.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class Updown :public Primitive {

  public:
  Updown(): Primitive() { }

public:
  //2012/06/25
  Updown(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
          .set(XmNclassName, (LONG_PTR)UPDOWN_CLASS));
    setValues(args);

    return rc;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNdeltaPosCallback,  UDN_DELTAPOS},
    };
    *num = XtNumber(table);
    return table;
  }


  void   setRange(int min, int max) {
      send(UDM_SETRANGE, min, max);
  }
  BOOL  getRange(int* min, int* max) {
      return send(UDM_GETRANGE, (WPARAM)min, (LPARAM)max);
  }
  void   setPos(int pos) {
      send(UDM_SETPOS, pos, 0L);
  }
  int    getPos() {
      return send(UDM_GETPOS, 0, 0L);
  }
  void   setBuddy(int buddy) {
      send(UDM_SETBUDDY, 0, 0L);
  }    
  int    getBuddy() {
      return send(UDM_GETBUDDY, 0, 0L);
  }
  int    setAccel(int accel) {
      return send(UDM_SETACCEL, accel, 0L);
  }
 
   int    getAccel() {
      return send(UDM_GETACCEL, 0, 0L); 
   }
  void  setBase(int base) {
      send(UDM_SETBASE, 0, 0L);
  }

  int    getBase() {
      return send(UDM_GETBASE, 0, 0L);        
  }
};

}

