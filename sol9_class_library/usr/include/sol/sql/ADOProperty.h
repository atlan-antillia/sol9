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
 *  ADOProperty.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {


class ADOProperty :public ADOObject {
  

public:
  ADOProperty()
  {
  }

public:
  ~ADOProperty()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Property));
  }

public:
  void set(__in ADODB::PropertyPtr pP) 
  {
    setObject((IDispatchPtr)pP);
  }


public:
  ADODB::PropertyPtr getPropertyPtr() 
  {
    return (ADODB::PropertyPtr)getObject();
  }

public:
  _variant_t getValue()
  {
    return getPropertyPtr()->GetValue();
  }


public:
  void putValue(__in const _variant_t& pval)
  {
    getPropertyPtr()->PutValue(pval);
  }

public:
  _bstr_t getName()
  {
    return getPropertyPtr()->GetName();
  }

public:  
  ADODB::DataTypeEnum getType()
  {
    return getPropertyPtr()->GetType();
  }
    
  
public:
  long getAttributes()
  {
    return getPropertyPtr()->GetAttributes();
  }
    

public:
  void putAttributes(long plAttributes)
  {
    getPropertyPtr()->PutAttributes(plAttributes);
  }

public:
  void dump()
  {
    _bstr_t name = getName();
    ADOEnumNames names;
    const char* type = names.getName(getType());
    printf("Property: Name=%S, Type=%s\n", 
      (const wchar_t*)name,
      type);
  }
};


}
