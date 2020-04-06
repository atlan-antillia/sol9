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
 *  FolderView.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

//#include <sol/ole/OleWindow.h>
#include <sol/com/ComIUnknown.h>
#include <sol/Guid.h>
#include <sol/CoSmartPtr.h>
#include <shobjidl.h>

namespace SOL {

class FolderView: public ComIUnknown {

public:
  FolderView(IFolderView* pView)
  :ComIUnknown(pView)
  {
  }    
public:
  IFolderView* getView()
  {
    return (IFolderView*)getIUnknown();
  }

public:
  HRESULT getCurrentViewMode( 
            /* [out] */ UINT *pViewMode)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetCurrentViewMode( 
      pViewMode);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  UINT getCurrentViewMode()
  {
    UINT viewMode;

    IFolderView* pView = getView();
    HRESULT hr = pView -> GetCurrentViewMode( 
      &viewMode);
    if (FAILED(hr)) {
      throw hr;
    }
    return viewMode;
  }

/*
typedef enum FOLDERVIEWMODE { 
  FVM_AUTO        = -1,
  FVM_FIRST       = 1,
  FVM_ICON        = 1,
  FVM_SMALLICON   = 2,
  FVM_LIST        = 3,
  FVM_DETAILS     = 4,
  FVM_THUMBNAIL   = 5,
  FVM_TILE        = 6,
  FVM_THUMBSTRIP  = 7,
  FVM_CONTENT     = 8,
  FVM_LAST        = 8
} FOLDERVIEWMODE;
 */
public:
  HRESULT setCurrentViewMode( 
            /* [in] */ UINT viewMode)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> SetCurrentViewMode( 
       viewMode);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getFolder( 
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetFolder( 
      riid,
      ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  void* getFolder( 
            /* [in] */ REFIID riid)
  {
    void* pv = NULL;
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetFolder( 
        riid,
        &pv);
    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }


public:
  HRESULT item( 
            /* [in] */ int iItemIndex,
            /* [out] */ PITEMID_CHILD *ppidl)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> Item( 
      iItemIndex,
      ppidl);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  PITEMID_CHILD item( 
            /* [in] */ int iItemIndex)
  {
    PITEMID_CHILD pidl;
    IFolderView* pView = getView();
    HRESULT hr = pView -> Item( 
      iItemIndex,
      &pidl);
    if (FAILED(hr)) {
      throw hr;
    }
    return pidl;
  }
        
public:
  HRESULT itemCount( 
            /* [in] */ UINT uFlags,
            /* [out] */ int *pcItems)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> ItemCount( 
        uFlags,
        pcItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int itemCount( 
            /* [in] */ UINT uFlags)
  {
    int cItems = 0;
    IFolderView* pView = getView();
    HRESULT hr = pView -> ItemCount( 
        uFlags,
        &cItems);
    if (FAILED(hr)) {
      throw hr;
    }
    return cItems;
  }
        
public:
  HRESULT items( 
            /* [in] */ UINT uFlags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> Items( 
          uFlags,
          riid,
          ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  void* items( 
            /* [in] */ UINT uFlags,
            /* [in] */ REFIID riid)
  {
    void* pv = NULL;
    IFolderView* pView = getView();
    HRESULT hr = pView -> Items( 
          uFlags,
          riid,
          &pv);
    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }
        
public:
  HRESULT getSelectionMarkedItem( 
            /* [out] */ int *piItem)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetSelectionMarkedItem( 
            piItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int getSelectionMarkedItem()
  {
    int iItem = 0;
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetSelectionMarkedItem( 
            &iItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return iItem;
  }
  

public:
  HRESULT getFocusedItem( 
            /* [out] */ int *piItem)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetFocusedItem( 
          piItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int getFocusedItem()
  {
    int iItem = 0;
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetFocusedItem( 
          &iItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return iItem;
  }        

public:
  HRESULT getItemPosition( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ POINT *ppt)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetItemPosition( 
          pidl,
          ppt);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  POINT getItemPosition( 
            /* [in] */ PCUITEMID_CHILD pidl)
  {
    POINT pt;
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetItemPosition( 
          pidl,
          &pt);
    if (FAILED(hr)) {
      throw hr;
    }
    return pt;
  }
        
public:
  HRESULT getSpacing( 
            /* [out][in] */ POINT *ppt)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetSpacing( 
          ppt);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getDefaultSpacing( 
            /* [out] */ POINT *ppt)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetDefaultSpacing( 
          ppt);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  POINT getDefaultSpacing()
  {
    POINT pt;
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetDefaultSpacing( 
          &pt);
    if (FAILED(hr)) {
      throw hr;
    }
    return pt;
  }
        
public:
  HRESULT getAutoArrange()
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> GetAutoArrange();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT selectItem( 
            /* [in] */ int iItem,
            /* [in] */ DWORD dwFlags)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> SelectItem( 
          iItem,
          dwFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT SelectAndPositionItems( 
            /* [in] */ UINT cidl,
            /* [in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in]*/  POINT *apt,
            /* [in] */ DWORD dwFlags)
  {
    IFolderView* pView = getView();
    HRESULT hr = pView -> SelectAndPositionItems( 
          cidl,
          apidl,
          apt,
          dwFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
};


}
