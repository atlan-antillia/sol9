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
 *  WcharProperty.h
 *
 *****************************************************************************/

// SOL9
#pragma once

// 2015/12/20
#include <sol/Exception.h>
#include <sol/StringTokenizerT.h>
#include <sol/StringT.h>
#include <sol/SmartPtrs.h>

namespace SOL {

class WcharProperty :public Object {

private:
  StringT<wchar_t> name;
  StringT<wchar_t> value;

public:
  WcharProperty(StringT<wchar_t>& wstring, const wchar_t tailTrimmer=(wchar_t)';')
  :name(L""),
  value(L"")
  {
    static const wchar_t equal = (wchar_t)'=';
    
    const wchar_t* string = (const wchar_t*)wstring;
    
    if (strchr(string, equal)) {
      StringTokenizerT<wchar_t> wtokenizer(string);
      wtokenizer.clearSeparator();
      wtokenizer.addSeparator(equal);
      wchar_t wname [1024] = { 0 };
      wchar_t wvalue[1024] = { 0 };
      wtokenizer.getToken(wname, CountOf(wname));
      SmartPtrs<wchar_t> n  = StringT<wchar_t>::trim(wname);
      name  = (wchar_t*)n; 
      wtokenizer.getToken(wvalue, CountOf(wvalue));
      
      SmartPtrs<wchar_t> v  = StringT<wchar_t>::trim(wvalue);
      wchar_t* temp = (wchar_t*)v;
      int pos = wcslen(temp)-1;
      
      if (tailTrimmer != 0 && temp[pos] == tailTrimmer) {
        temp[pos] = (wchar_t)'\0';
      }
      
      value = (wchar_t*)v;
      
    } else {
      //Ignore
    }
  }

public:
  WcharProperty(const wchar_t* cname= L"", const wchar_t* cvalue= L"")
  :name(cname),
  value(cvalue)
  {
  }

public:
  void set(const wchar_t* cname, const wchar_t* cvalue)
  {
    if (cname) {
      name = cname;
    }
    if (cvalue) {
      value = cvalue;
    }
  }

public:
  void setName(const wchar_t* cname)
  {
    if (cname) {
      name = cname;
    }
  }

public:
  void setValue(const wchar_t* cvalue)
  {
    if (cvalue) {
      value = cvalue;
    }
  }

public:
  const wchar_t* getName()
  {
    return (const wchar_t*)name;
  }

public:
  const wchar_t* getValue()
  {
    return (const wchar_t*)value;
  }

public:
  void dump()
  {
    printf("%S=[%S]\n", getName(), getValue());
  }
      
};

}

