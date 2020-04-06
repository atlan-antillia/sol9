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
 *  ADOXView.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOObject.h>

namespace SOL {

class ADOXView :public ADOObject {

public:
  ADOXView()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::View));
  }

public:
  void set(__in ADOX::ViewPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::ViewPtr getViewPtr() 
  {
    return (ADOX::ViewPtr)getObject();  
  }


public:
  _variant_t getCommand()
  {
    return getViewPtr()->GetCommand();
  }

public:
  void putCommand (
    __in const _variant_t& pVal)
  {
    getViewPtr()->PutCommand (pVal);
  }

public:
  void putRefCommand(__in IDispatch * pVal)
  {
    getViewPtr()->PutRefCommand (pVal);
  }

public:
  _bstr_t getName()
  {
    return getViewPtr()->GetName();
  }

public:
  _variant_t getDateCreated()
  {
    return getViewPtr()->GetDateCreated();
  }

public:
  _variant_t getDateModified()
  {
    return getViewPtr()->GetDateModified();
  }

public:
  void dump()
  {
    _bstr_t name = getName();

    COMTypeConverter converter;
    _variant_t val = getDateCreated();
    _bstr_t created="";
    converter.toString(val, created);

    printf("<View Name=\"%s\" Created=\"%s\" />\n", 
      (const char*)name,
      (const char*)created);
    /*
    _variant_t mval = getDateModified();
    _bstr_t modified="";
    converter.toString(mval, modified);
    printf("Modified=%S\n", (const wchar_t*)modified);
    */
  }
};

}
