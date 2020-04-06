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
 *  WbemObjectSink.h
 *
 *****************************************************************************/

// 2009/01/18 Please define a subclass of this class and customize ShowObject method
// to match your need.

// 2010/04/01 Modified ShowObject method to show an objectText

#pragma once

#define _WIN32_DCOM

#include <sol\Object.h>
#include <wbemidl.h>
#include <comutil.h>


namespace SOL {

_COM_SMARTPTR_TYPEDEF(IWbemClassObject, __uuidof(IWbemClassObject));


class WbemObjectSink : public IWbemObjectSink
{
private:
    LONG ref;

public:
  /**
   * Constructor
   */
  WbemObjectSink()
  :ref(0) { 
    AddRef();
  }

public:
  /**
   * virtual Destructor
   */
  virtual ~WbemObjectSink() {
     Release();
   }

public:
    virtual ULONG STDMETHODCALLTYPE AddRef() {
    return InterlockedIncrement(&ref);
  }


public:
    virtual ULONG STDMETHODCALLTYPE Release() {
    LONG lRef = InterlockedDecrement(&ref);
    if(lRef == 0) {
      delete this;
    }
    return lRef;
  }

public:  
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
      REFIID riid, void** ppv) {
    HRESULT hr = S_OK;
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink) {
      *ppv = (IWbemObjectSink*)this;
      AddRef();
      hr =WBEM_S_NO_ERROR;
    }
    else {
      hr =E_NOINTERFACE;
    }
    return hr;
  }

public:
  /**
   * Show properties of IWbemClassObject specified by vTargInst here;
   *
   * This is really a virtual method.
   * You can define a subclass of this to customize this method to match your need.
   */
  virtual HRESULT ShowObject(VARIANT& vTargetInst) {
    HRESULT hr = WBEM_S_NO_ERROR;
    _variant_t vInst(vTargetInst);  
    IWbemClassObjectPtr pObject(vInst);

    BSTR bstr = NULL;
    if (SUCCEEDED(hr = pObject->GetObjectText(0, &bstr) )) {
      printf("ObjectText=[%S]\n", bstr);
      SysFreeString(bstr);
    }

  
    return hr;
  }


public:
  /**
   * This is called when an event occurs.
   */
    virtual HRESULT STDMETHODCALLTYPE Indicate(
      LONG lObjectCount,
      IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray) {

    for (int i = 0; i < lObjectCount; i++) {
      //printf("WbemObjectSink#Indicate,1,Event occurred\n");

      HRESULT hr;
      VARIANT vTargetInst;
      try {
        
        if (SUCCEEDED(hr = apObjArray[i]->Get(L"TargetInstance", 0, &vTargetInst, 0, 0))) {
          //Call a virtual function to show properties of the IWbemClassObject of vTargetInst.
          ShowObject(vTargetInst);
        }
      } catch(...) {
        printf("WbemObjectSink#Indicate,1,Exception\n");
      }
    }
    return WBEM_S_NO_ERROR;
  }
        

public:
  virtual HRESULT STDMETHODCALLTYPE SetStatus( 
      LONG lFlags,
            HRESULT ,
            BSTR  ,
            IWbemClassObject __RPC_FAR* ) {
    if(lFlags == WBEM_STATUS_COMPLETE) {
      //printf("Call complete. hResult = 0x%X\n", hResult);
    } else if(lFlags == WBEM_STATUS_PROGRESS) {
      //printf("Call in progress.\n");
    }

    return WBEM_S_NO_ERROR;
  }
};

}
