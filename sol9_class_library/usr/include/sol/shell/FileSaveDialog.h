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
 *  FileSaveDialog.h
 *
 *****************************************************************************/


// 2012/11/17

#pragma once

#include <sol/shell/FileDialog.h>

namespace SOL {

class FileSaveDialog: public FileDialog {
    
public:
  FileSaveDialog()
  :FileDialog()
  {
      IFileDialog *pDialog = NULL;
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, 
      CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&pDialog);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pDialog);
    }
  }

public:
  IFileSaveDialog* getSaveDialog()
  {
    return (IFileSaveDialog*)getIUnknown();
  }

public:
  HRESULT setSaveAsItem( 
            /* [in] */ IShellItem *psi)
  {
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog -> SetSaveAsItem( 
        psi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT  setProperties( 
            /* [in] */ IPropertyStore *pStore)
  {
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog ->  SetProperties( 
        pStore);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT setCollectedProperties( 
            /* [in] */ IPropertyDescriptionList *pList,
            /* [in] */ BOOL fAppendDefault)
  {
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog -> SetCollectedProperties( 
        pList,
        fAppendDefault);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getProperties( 
            /* [out] */ IPropertyStore **ppStore)
  {
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog -> GetProperties( 
      ppStore);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IPropertyStore* getProperties()
  {
    IPropertyStore* pStore = NULL;
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog -> GetProperties( 
      &pStore);
    if (FAILED(hr)) {
      throw hr;
    }
    return pStore;
  }
        

public:
  HRESULT applyProperties( 
            /* [in] */ IShellItem *psi,
            /* [in] */ IPropertyStore *pStore,
            /* [in] */ HWND hwnd,
            /* [in] */ IFileOperationProgressSink *pSink)
  {
    IFileSaveDialog* pDialog = getSaveDialog();
    HRESULT hr = pDialog -> ApplyProperties( 
          psi,
          pStore,
          hwnd,
          pSink);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }    
};

}

