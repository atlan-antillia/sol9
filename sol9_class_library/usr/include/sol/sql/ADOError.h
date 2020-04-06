/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ADOError.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/05/12 Added dump method.
// 2009/05/15

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {

class ADOError :public ADOObject {

public:
  ADOError()
  {
  }

public:
  ~ADOError()
  {
  }

public:
  /*
  HRESULT create()
  {
    return ADOObject::create(__uuidof(ADODB::Error));
  }
  */

public:
  void set(__in ADODB::ErrorPtr pE)
  {
    setObject((IDispatchPtr)pE);
  }

public:
  ADODB::ErrorPtr getErrorPtr()
  {
    return (ADODB::ErrorPtr)getObject();
  }

public:
  long getNumber()
  {
    return getErrorPtr()->GetNumber();
  }

public:
  _bstr_t getSource()
  {
    return getErrorPtr()->GetSource();
  }

public:
  _bstr_t getDescription()
  {
    return getErrorPtr()->GetDescription();
  }

public:
  _bstr_t getHelpFile()
  {
    return getErrorPtr()->GetHelpFile();
  }

public:
  long getHelpContext()
  {
    return getErrorPtr()->GetHelpContext();
  }
public:
  _bstr_t getSQLState()
  {
    return getErrorPtr()->GetSQLState();
  }

public:
  long getNativeError()
  {
    return getErrorPtr()->GetNativeError();
  }

public:
  // 2008/05/12
  void dump()
  {
    printf("Number:0x%x\n",  getNumber());

    printf("Source:%s\n", (const char*)getSource());
    printf("Description:%s\n", (const char*)getDescription());
    printf("HelpFile:%s\n", (const char*)getHelpFile());
    printf("HelpContext:0x%x\n",  getHelpContext());

    printf("SQLState:%s\n", (const char*)getSQLState());
    printf("NativeError:0x%x\n",  getNativeError());
  }
};

}

