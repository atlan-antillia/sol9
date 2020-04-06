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
 *  SWbemMethodSet.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObjectSet.h>
#include <sol/wmi/SWbemMethod.h>

namespace SOL {

class SWbemMethodSet :public SWbemBaseObjectSet {

public:
  SWbemMethodSet(IDispatch* pDisp=NULL)
  :SWbemBaseObjectSet(pDisp)
  {

  }

public:
  ISWbemMethodSet*  get()
  {
    return (ISWbemMethodSet*)getIDispatch();
  }

public:
  SWbemMethodSet& operator=(ISWbemMethodSet* pDisp)
  { 
    set(pDisp);
    return *this;
  }
    
public:
  IUnknown* get__NewEnum()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = E_FAIL;
    ISWbemMethodSet* set = get();

    if (FAILED(hr = set->get__NewEnum( 
      &pUnk))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pUnk;
  }        

public:
  ISWbemMethod* item( 
            __in _bstr_t strName,
           __in long iFlags)
  {
    ISWbemMethod* pObjWbemMethod = NULL;
    HRESULT hr = E_FAIL;
    ISWbemMethodSet* set = get();

    if (FAILED(hr = set ->Item( 
        (BSTR)strName,
        iFlags,
        &pObjWbemMethod))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemMethod;
  }        

public:
  long getCount()
  {
    HRESULT hr = E_FAIL;
    ISWbemMethodSet* set = get();
    long iCount = 0;

    if (FAILED(hr = set ->get_Count(&iCount))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iCount;
  }        
  


/*public:
  void display()
  {

  }
*/

public:
  void write(Writer& writer)
  {
    long c = getCount();

    writer.writeln(L"<MethodSet>");
    
    writer.writeln(L"<Count>%d</Count>", c);

    try {
      EnumVariant enumVar = ComObjectSet::getNewEnum();
      IDispatch* pDisp = NULL;
      while (enumVar.next(1, &pDisp) ==1) {
          
        try {        
          SWbemMethod method = (ISWbemMethod*)pDisp;
          method.write(writer);
        } catch (...) {
          break;
        }
      }

    } catch (...) {
      
    }
    writer.writeln(L"</MethodSet>");

  }
};


}
