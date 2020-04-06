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
 *  FileOpenDialog.h
 *
 *****************************************************************************/


// 2012/11/17

#pragma once

#include <sol/shell/FileDialog.h>

namespace SOL {

class FileOpenDialog: public FileDialog {

public:
  FileOpenDialog()
  :FileDialog()
  {
    IFileDialog *pDialog = NULL;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, 
      CLSCTX_INPROC_SERVER, IID_IFileDialog, (void**)&pDialog);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pDialog);
    }
  }


public:
  IFileOpenDialog* getOpenDialog()
  {
    return (IFileOpenDialog*)getIUnknown();
  }

    
public:
  HRESULT getResults( 
            /* [out] */ IShellItemArray **ppenum)
  {
    IFileOpenDialog* pDialog = getOpenDialog();
    HRESULT hr = pDialog -> GetResults( 
        ppenum);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItemArray* getResults()
  {
    IShellItemArray* pArray = NULL;
    IFileOpenDialog* pDialog = getOpenDialog();
    HRESULT hr = pDialog -> GetResults( 
        &pArray);
    if (FAILED(hr)) {
      throw hr;
    }
    return pArray;
  }
        
public:
  HRESULT getSelectedItems( 
            /* [out] */ IShellItemArray **ppsai)
  {
    IFileOpenDialog* pDialog = getOpenDialog();
    HRESULT hr = pDialog -> GetSelectedItems( 
        ppsai);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItemArray* getSelectedItems()
  {
    IShellItemArray* pArray = NULL;
    IFileOpenDialog* pDialog = getOpenDialog();
    HRESULT hr = pDialog -> GetSelectedItems( 
        &pArray);
    if (FAILED(hr)) {
      throw hr;
    }
    return pArray;
  }    
};
    
}

