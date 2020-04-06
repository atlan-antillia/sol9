/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  NetSharingEveryConnectionCollection.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netcon.h>
#include <sol/com/EnumVariant.h>

namespace SOL {

class NetSharingEveryConnectionCollection: public ComIDispatch {
public:
  NetSharingEveryConnectionCollection(INetSharingEveryConnectionCollection* pCollection=NULL)
    :ComIDispatch(pCollection)
  {
  }

public:
  INetSharingEveryConnectionCollection* getCollection()
  {
    return (INetSharingEveryConnectionCollection*) getIDispatch();
  }
    
public:
  IUnknown* getNewEnum()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = getCollection() -> get__NewEnum( 
        &pUnk);

    if (FAILED(hr)) {
      throw hr;
    }
    return pUnk;
  }

public:
  IEnumVARIANT* getEnumVariant()
  {
    IUnknown* pUnk = NULL;
    HRESULT hr = getCollection() -> get__NewEnum(&pUnk);
    if (FAILED(hr)) {
      throw hr;
    }

    IEnumVARIANT* pEnum = NULL;
    hr = pUnk->QueryInterface(__uuidof(IEnumVARIANT),
                                       (void**)&pEnum);
    pUnk->Release();
    if (FAILED(hr)) {
      throw hr;
    }
        
    return pEnum;
  }
public:
  long getCount()
  {
    long count = 0;
    HRESULT hr = getCollection() -> get_Count(&count);

    if (FAILED(hr)) {
      throw hr;
    }
    return count;
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    EnumVariant enumVar = getEnumVariant();
    //int i = 0;
    bool looping = true;
    while (looping) {
  
      try {
        ComIUnknown pUnk = enumVar.nextIUnknown();
      } catch (HRESULT ) {

      }
    }
  }
};

}
