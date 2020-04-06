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
 *  ShellView.h
 *
 *****************************************************************************/


// 2012/10/30
// This is a simple wrapper class for IShellView, IShellView2, amd IShellView3 interfaces.
#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/ole/OleWindow.h>
#include <shobjidl.h>

#pragma comment (lib, "shlwapi.lib")

namespace SOL {

class ShellView: public OleWindow {

public:
  ShellView(IShellView* pView)
  :OleWindow(pView)
  {
  }    

public:
  IShellView* getView()
  {
    return (IShellView*)getOleWindow();
  }

public:
  HRESULT translateAccelerator( 
            /* [in] */ MSG *pmsg)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> TranslateAccelerator( 
        pmsg);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT enableModeless( 
            /* [in] */ BOOL fEnable)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> EnableModeless(fEnable);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT uiActivate( 
            /* [in] */ UINT uState) 
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> UIActivate(uState) ;

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT refresh()
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> Refresh();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  void reshape(int x, int y, int w, int h, BOOL flag=TRUE)
  {
    HWND hwnd = getWindow();
    MoveWindow(hwnd, x, y, w, h, flag);
  }

public:
  HRESULT createViewWindow( 
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView,
            /* [out] */ HWND *phWnd)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> CreateViewWindow( 
        psvPrevious,
        pfs,
        psb,
        prcView,
        phWnd);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HWND createViewWindow( 
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView)
  {
    HWND hwnd = NULL;
    IShellView* pView = getView();
    HRESULT hr = pView -> CreateViewWindow( 
        psvPrevious,
        pfs,
        psb,
        prcView,
        &hwnd);

    if (FAILED(hr)) {
      throw hr;
    }
    return hwnd;
  }

        
public:
  HRESULT destroyViewWindow()
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> DestroyViewWindow();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:  
  HRESULT getCurrentInfo( 
            /* [out] */ LPFOLDERSETTINGS pfs)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> GetCurrentInfo( 
        pfs);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  FOLDERSETTINGS getCurrentInfo()
  {
    FOLDERSETTINGS fs;
    IShellView* pView = getView();
    HRESULT hr = pView -> GetCurrentInfo( 
        &fs);

    if (FAILED(hr)) {
      throw hr;
    }
    return fs;
  }
        

public:
  HRESULT addPropertySheetPages( 
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> AddPropertySheetPages( 
        dwReserved,
        pfn,
        lparam);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT saveViewState()
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> SaveViewState();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT selectItem( 
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ SVSIF uFlags)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> SelectItem( 
        pidlItem,
        uFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getItemObject( 
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellView* pView = getView();
    HRESULT hr = pView -> GetItemObject( 
        uItem,
        riid,
        ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  void* getItemObject( 
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid)
  {
    void *pv = NULL;
    IShellView* pView = getView();
    HRESULT hr = pView -> GetItemObject( 
        uItem,
        riid,
        &pv);

    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }

public:
  IFolderView* getFolderView()
  {
    IShellView* pView = getView();
        return (IFolderView*) queryInterface(IID_IFolderView);
  }


//<IShellView2>    
public:
  IShellView2* getView2()
  {
    //IShellView* pView = getView();
    return (IShellView2*)queryInterface(IID_IShellView2);
  }

public:
  HRESULT getView( 
            /* [out][in] */ SHELLVIEWID *pvid,
            /* [in] */ ULONG uView)
  {
    IShellView2* pView2 = getView2();
    HRESULT hr = pView2 -> GetView( 
          pvid,
          uView);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT createViewWindow2( 
            /* [in] */ LPSV2CVW2_PARAMS lpParams)
  {
    IShellView2* pView2 = getView2();
    HRESULT hr = pView2 -> CreateViewWindow2( 
          lpParams);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT handleRename( 
            /* [in] */ PCUITEMID_CHILD pidlNew)
  {
    IShellView2* pView2 = getView2();
    HRESULT hr = pView2 -> HandleRename( 
          pidlNew);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT selectAndPositionItem( 
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ UINT uFlags,
            /* [in] */ POINT *ppt)
  {
    IShellView2* pView2 = getView2();
    HRESULT hr = pView2 -> SelectAndPositionItem( 
          pidlItem,
          uFlags,
          ppt);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
//</IShellView2>
    

//<IShellView3>
public:
  IShellView3* getView3()

  {
    IShellView* pView = getView();
    return (IShellView3*)queryInterface(IID_IShellView3);
  }

public:
  HRESULT createViewWindow3(
            /* [in] */ IShellBrowser *psbOwner,
            /* [in] */ IShellView *psvPrev,
            /* [in] */ SV3CVW3_FLAGS dwViewFlags,
            /* [in] */ FOLDERFLAGS dwMask,
            /* [in] */ FOLDERFLAGS dwFlags,
            /* [in] */ FOLDERVIEWMODE fvMode,
            /* [in] */ const SHELLVIEWID *pvid,
            /* [in] */ const RECT *prcView,
            /* [out] */ HWND *phwndView)
  {
    IShellView3* pView3 = getView3();
    HRESULT hr = pView3 -> CreateViewWindow3( 
            psbOwner,
            psvPrev,
            dwViewFlags,
            dwMask,
            dwFlags,
            fvMode,
            pvid,
            prcView,
            phwndView);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HWND createViewWindow3(
            /* [in] */ IShellBrowser *psbOwner,
            /* [in] */ IShellView *psvPrev,
            /* [in] */ SV3CVW3_FLAGS dwViewFlags,
            /* [in] */ FOLDERFLAGS dwMask,
            /* [in] */ FOLDERFLAGS dwFlags,
            /* [in] */ FOLDERVIEWMODE fvMode,
            /* [in] */ const SHELLVIEWID *pvid,
            /* [in] */ const RECT *prcView)
  {
    HWND hwndView = NULL;

    IShellView3* pView3 = getView3();
    HRESULT hr = pView3 -> CreateViewWindow3( 
            psbOwner,
            psvPrev,
            dwViewFlags,
            dwMask,
            dwFlags,
            fvMode,
            pvid,
            prcView,
            &hwndView);
    if (FAILED(hr)) {
      throw hr;
    }
    return hwndView;
  }
//</IShellView3>

};
    
}
