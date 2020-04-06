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
 *  Args.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>
#include <sol\StrDef.h>
#include <sol\Arg.h>

// Note: The macro XtSetArg is really from Xt of X11.
#define  XtSetArg(a,b,c) a.name=(TCHAR*)b;a.value =(LONG_PTR)c

/**
 * Args class.
 */

namespace SOL {

class Args :public Object {
  int    max;
  int     num;
  Arg*    arg;


public:
  /**
   * Constructor
   */
  Args()
  {
    max = 50;
    num = 0;
    arg = new Arg[max];
  }

public:
  ~Args()
  {
    if (arg) {
      delete [] arg;
      arg = NULL;
    }
  }

public:
  Args& reset()
  {
    num = 0;
    return *this;
  }


public:
  Arg* getArgList() { return arg; }
  int   getCount() { return num; }

public:
  Args& put(const TCHAR* name, LONG_PTR value)
  {
    for(int i = 0; i<num; i++) {
      if(arg[i].name == name) {
        XtSetArg(arg[i], name, value);
        return *this;
      }
    }
    XtSetArg(arg[num], name, value);
    if(num < max) num++;
    return *this;
  }

public:
  Args& set(const TCHAR* name, LONG_PTR value)
  {
    LONG_PTR val = value;

    for(int i = 0; i<num; i++) {
      if(arg[i].name == XmNstyle && 
       name == XmNstyle) {
        arg[i].value |= val;
        return *this;
      }
      if(arg[i].name == XmNexStyle && 
      name == XmNexStyle) {
        arg[i].value |= val;
        return *this;
      }
    }
    XtSetArg(arg[num], name, val);

    if(num < max){
      num++;
    }
    return *this;
  }
public:
  Args& set(const TCHAR* name, int value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

public:
  Args& set(const TCHAR* name, void* value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

public:
  Args& set(const TCHAR* name, uint value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

public:
  Args& set(const TCHAR* name, unsigned long value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

  Args& set(const TCHAR* name, const char* value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

  Args& set(const TCHAR* name, const wchar_t* value)
  {
    return Args::set(name, (LONG_PTR)value);
  }

public:
  Args& set(Arg* ar, int num)
  {
    LONG_PTR val;
    for(int i = 0; i<num; i++) {
      if(get(ar[i].name, &val)) {
        if (val) {
          set(XmNstyle, (LONG_PTR)ar[i].value);
        }
      }
    }
    return *this;
  }

public:
  LONG_PTR get(const TCHAR* name)
  {
    for(int i = 0; i<num; i++) {
      if(arg[i].name == name) 
        return arg[i].value;
    }
    return 0L;
  }


public:
  Boolean get(const TCHAR* name, LONG_PTR* val)
  {
    *val = NULL;
    for(int i = 0; i<num; i++) {
      if(arg[i].name == name) {
        *val = arg[i].value;
        return TRUE;
      }
    }
    return FALSE;
  }

public:
  Args& toPixelUnit()
  {
    long unit = GetDialogBaseUnits();
    put(XmNx,     get(XmNx)     *LOWORD(unit)/4);
    put(XmNy,     get(XmNy)     *HIWORD(unit)/8);
    put(XmNwidth, get(XmNwidth) *LOWORD(unit)/4);
    put(XmNheight,get(XmNheight)*HIWORD(unit)/8);
    return *this;
  }

  //2015/01/26 Added 
  Boolean has(const TCHAR* name)
  {
  	Boolean rc = False;
    for(int i = 0; i<num; i++) {
    	if(arg[i].name == name) {
          //value = args[i].value;
    	  rc = True;
    	  break;
    	}
    }
    return rc;
  }
  
  //2017/12/28
  Args&  setIfNotSet(const TCHAR* name, int value)
  {
    if (!has(name)) {
      set(name, (LONG_PTR)value); 
    }
    return *this; 
  }
  Args&  setIfNotSet(const TCHAR* name, LONG_PTR value)
  {
    if (!has(name)) {
      set(name, value);
    }
    return *this;
  }

};

}



