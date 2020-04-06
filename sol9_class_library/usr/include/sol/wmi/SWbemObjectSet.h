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
 *  SWbemObjectSet.h
 *
 *****************************************************************************/

// 2009/12/22 Modified base class to be SWbemBaseObjectSet, not SWbemBaseObject
// 2012/03/08 Updated.

#pragma once

#include <sol\Object.h>
#include <sol/wmi/SWbemBaseObjectSet.h>
#include <sol/wmi/SWbemObject.h>

namespace SOL {

class SWbemObjectSet : public SWbemBaseObjectSet {

   
public:
  SWbemObjectSet(IDispatch* pDisp=NULL)
    :SWbemBaseObjectSet(pDisp)
  {
  }
    
public:
  ISWbemObjectSet* get()
  {
    return (ISWbemObjectSet*)getIDispatch();
  }

public:
  SWbemObjectSet& operator=(ISWbemObjectSet* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  IUnknown* get__NewEnum() 
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = E_FAIL;
    ISWbemObjectSet* objectSet = get();

    if (FAILED(hr = objectSet->get__NewEnum(&pUnk))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pUnk;
  }

  
public:
  ISWbemObject* item( 
            __in _bstr_t strObjectPath,
           __in long iFlags)
  {
    ISWbemObject* pObjWbemObject = NULL;

    HRESULT hr = E_FAIL;
    ISWbemObjectSet* objectSet = get();

    if (FAILED(hr = objectSet->Item( 
            (BSTR)strObjectPath,
            iFlags,
      &pObjWbemObject))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pObjWbemObject;
  }


public:
  long getCount()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectSet* objectSet = get();
    long iCount = 0;

    if (FAILED(hr = objectSet-> get_Count(&iCount))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iCount;
  }

public: 
  ISWbemSecurity* getSecurity()
  {
    HRESULT hr = E_FAIL;
    ISWbemObjectSet* objectSet = get();
    ISWbemSecurity *objWbemSecurity = NULL;
    if (FAILED(hr = objectSet->get_Security_( 
      &objWbemSecurity))) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemSecurity;
  }


public:
  ISWbemObject* itemIndex(
            __in long lIndex)
  {  
    HRESULT hr = E_FAIL;
    ISWbemObjectSet* objectSet = get();
    ISWbemObject *wbemObject = NULL;

    if (FAILED(hr = objectSet->ItemIndex( 
        lIndex,
        &wbemObject))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return wbemObject;
  }

    
public:
  void write(Writer& writer)
  {
    //long c = getCount();

    writer.writeln(L"<ObjectSet>");
    
    try {
      EnumVariant enumVar = ComObjectSet::getNewEnum();
      IDispatch* pDisp = NULL;
      while (enumVar.next(1, &pDisp) == 1) {
    
        try {
          SWbemObject object = pDisp;
          object.write(writer);
        } catch (...) {
          break;
        }
      }
      //reportWriter.write(L"\n");

    } catch (...) {
      
    }
    writer.writeln(L"</ObjectSet>");

  }
};

}
