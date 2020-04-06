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
 *  FileDialog.h
 *
 *****************************************************************************/


// 2012/11/17

#pragma once

#include <sol/shell/ModalWindow.h>
#include <sol/CoSmartPtr.h>

namespace SOL {

class FileDialog: public ModalWindow {

public:
  FileDialog(IFileDialog* pDialog=NULL)
  :ModalWindow(pDialog)
  {
  }
public:
  IFileDialog* getFileDialog()
  {
    return (IFileDialog*)getIUnknown();
  }
    
public:
  HRESULT setFileTypes( 
            /* [in] */ UINT cFileTypes,
            /* [in] */ const COMDLG_FILTERSPEC *rgFilterSpec)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFileTypes( 
          cFileTypes,
        rgFilterSpec);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setFileTypeIndex( 
            /* [in] */ UINT iFileType)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFileTypeIndex( 
        iFileType);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        


public:
  HRESULT getFileTypeIndex( 
            /* [out] */ UINT *piFileType)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetFileTypeIndex(piFileType);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT advise( 
            /* [in] */ IFileDialogEvents *pfde,
            /* [out] */ DWORD *pdwCookie)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> Advise( 
        pfde,
        pdwCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT unadvise( 
            /* [in] */ DWORD dwCookie)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> Unadvise( 
        dwCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT setOptions( 
            /* [in] */ FILEOPENDIALOGOPTIONS fos)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetOptions( 
        fos);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  HRESULT getOptions( 
            /* [out] */ FILEOPENDIALOGOPTIONS *pfos)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetOptions( 
      pfos);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  FILEOPENDIALOGOPTIONS getOptions()
  {
    FILEOPENDIALOGOPTIONS fos;
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetOptions( 
      &fos);
    if (FAILED(hr)) {
      throw hr;
    }
    return fos;
  }

 
public:
  HRESULT setDefaultFolder( 
            /* [in] */ IShellItem *psi)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetDefaultFolder( 
        psi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT setFolder( 
            /* [in] */ IShellItem *psi)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFolder(psi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getFolder( 
            /* [out] */ IShellItem **ppsi)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetFolder( 
        ppsi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItem* getFolder()
  {
    IShellItem* pItem = NULL; 
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetFolder( 
        &pItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return pItem;
  }
        

public:
  HRESULT getCurrentSelection( 
            /* [out] */ IShellItem **ppsi)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetCurrentSelection( 
        ppsi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  IShellItem* getCurrentSelection()
  {
    IShellItem* pItem = NULL;
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetCurrentSelection( 
        &pItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return pItem;
  }
        

public:
  HRESULT setFileName( 
            /* [in] */ LPCWSTR pszName)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFileName( 
        pszName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  /*
  MSDN says: The text in the File name edit box does not necessarily reflect the item the user chose.
   To get the item the user chose, use IFileDialog::GetResult
  */
  HRESULT getFileName( 
            /* [out] */ LPWSTR *pszName) 
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetFileName( 
        pszName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getFileName()
  {
    wchar_t* wname;
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> GetFileName( 
        &wname);
    if (FAILED(hr)) {
      throw hr;
    }
    wchar_t* name = new_strdup(wname);
    CoSmartPtr<wchar_t*> sp = wname;
    return _bstr_t(name);
  }

public:
  HRESULT setTitle( 
            /* [in] */ LPCWSTR pszTitle)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetTitle( 
        pszTitle);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        

public:
  HRESULT setOkButtonLabel( 
            /* [in] */ LPCWSTR pszText)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetOkButtonLabel( 
        pszText);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT setFileNameLabel( 
            /* [in] */ LPCWSTR pszLabel)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFileNameLabel( 
      pszLabel);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT  getResult( 
            /* [out] */ IShellItem **ppsi)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog ->  GetResult( 
        ppsi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  IShellItem*  getResult()
  {
    IShellItem* pItem = NULL;
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog ->  GetResult( 
        &pItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return pItem;
  }        

public:
  HRESULT addPlace( 
            /* [in] */ IShellItem *psi,
            /* [in] */ FDAP fdap)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> AddPlace( 
        psi,
        fdap);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT setDefaultExtension( 
            /* [in] */ LPCWSTR pszDefaultExtension)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetDefaultExtension( 
      pszDefaultExtension);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  HRESULT close( 
            /* [in] */ HRESULT hrs)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> Close( 
        hrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT setClientGuid( 
            /* [in] */ REFGUID guid)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetClientGuid( 
        guid);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  HRESULT clearClientData()
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> ClearClientData();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }       


public:
  HRESULT setFilter( 
            /* [in] */ IShellItemFilter *pFilter)
  {
    IFileDialog* pDialog = getFileDialog();
    HRESULT hr = pDialog -> SetFilter( 
        pFilter);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
    
//<IFileDialog2>
public:
  IFileDialog2* getDialog2()
  {
    return (IFileDialog2*)queryInterface(IID_IFileDialog2);
  }

public:
  HRESULT setCancelButtonLabel( 
            /* [in] */ LPCWSTR pszLabel)
  {
    IFileDialog2* pDialog = getDialog2();
    HRESULT hr = pDialog -> SetCancelButtonLabel( 
        pszLabel);
    if (FAILED(hr)) { 
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT setNavigationRoot( 
            /* [in] */ IShellItem *psi) 
  {
    IFileDialog2* pDialog = getDialog2();
    HRESULT hr = pDialog -> SetNavigationRoot( 
          psi);
    if (FAILED(hr)) { 
      throw hr;
    }
    return hr; 
    }
  //</IFileDialog2>

};
    
}
