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
 *  ShellItem.h
 *
 *****************************************************************************/


// 2012/10/30
// This class is for IShellItem and IShellItem2 interfaces.

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/shell/ShellItem.h>
#include <sol/ole/OleWindow.h>
#include <shobjidl.h>

#pragma comment (lib, "shlwapi.lib")

namespace SOL {

class NameSpaceTreeControl: public ComIUnknown {
private:
  DWORD dwCookie;

public:
  NameSpaceTreeControl()
  :ComIUnknown(),
  dwCookie(0)
  {
    INameSpaceTreeControl* pControl = NULL;
    HRESULT hr = CoCreateInstance(CLSID_NamespaceTreeControl, NULL, 
      CLSCTX_INPROC_SERVER,
      IID_INameSpaceTreeControl, (void**)&pControl);
    if (FAILED(hr)) {
      MessageBox(NULL, _T("Error"), _T("NameSpaceTreeControl"), MB_OK);
      throw hr;
    } else {
      set(pControl);
    }
  }

public:
  INameSpaceTreeControl* getControl()
  {
     return (INameSpaceTreeControl*)getIUnknown();
  }

public:
  operator INameSpaceTreeControl*()
  {
     return (INameSpaceTreeControl*)getIUnknown();
  }

public:
  HRESULT initialize( 
    /* [in] */ HWND hParent,
    /* [in] */ RECT *prc,
    /* [in] */ NSTCSTYLE nsctsFlags)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> Initialize( 
        hParent,
        prc,
        nsctsFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

    
public:
  void move(int x, int y, int width, int height, BOOL flag = TRUE) 
  {
    HWND hwndControl = getWindow();
    MoveWindow(hwndControl, x, y, width, height, flag);
  }

public:
  void reshape(int x, int y, int width, int height, BOOL flag = TRUE) 
  {
    HWND hwndControl = getWindow();
    MoveWindow(hwndControl, x, y, width, height, flag);
  }


public:
  HRESULT treeAdvise( 
            /* [in] */ IUnknown *punk)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> TreeAdvise( 
        punk,  
        &dwCookie);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT treeUnadvise()
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> TreeUnadvise( 
        dwCookie);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT appendRoot( 
            /* [in] */ IShellItem *psiRoot,
            /* [in] */ SHCONTF grfEnumFlags,
            /* [in] */ NSTCROOTSTYLE grfRootStyle,
            /* [in] */ IShellItemFilter *pif)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> AppendRoot( 
        psiRoot,
        grfEnumFlags,
        grfRootStyle,
        pif);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT insertRoot( 
            /* [in] */ int iIndex,
            /* [in] */ IShellItem *psiRoot,
            /* [in] */ SHCONTF grfEnumFlags,
            /* [in] */ NSTCROOTSTYLE grfRootStyle,
            /* [in] */ IShellItemFilter *pif)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> InsertRoot( 
        iIndex,
        psiRoot,
        grfEnumFlags,
        grfRootStyle,
        pif);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT removeRoot( 
            /* [in] */ IShellItem *psiRoot)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> RemoveRoot( 
        psiRoot);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT removeAllRoots()
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> RemoveAllRoots();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT getRootItems( 
            /* [out] */ IShellItemArray **ppsiaRootItems) 
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetRootItems( 
        ppsiaRootItems) ;

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItemArray* getRootItems() 
  {
    IShellItemArray* psiaRootItems = NULL; 

    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetRootItems( 
        &psiaRootItems) ;

    if (FAILED(hr)) {
      throw hr;
    }
    return psiaRootItems;
  }

        
public:
  HRESULT setItemState( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCITEMSTATE nstcisMask,
            /* [in] */ NSTCITEMSTATE nstcisFlags)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> SetItemState( 
      psi,
      nstcisMask,
      nstcisFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT getItemState( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCITEMSTATE nstcisMask,
            /* [out] */ NSTCITEMSTATE *pnstcisFlags)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemState( 
        psi,
        nstcisMask,
        pnstcisFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  NSTCITEMSTATE getItemState( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCITEMSTATE nstcisMask)
  {
    NSTCITEMSTATE nstcisFlags;

    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemState( 
        psi,
        nstcisMask,
        &nstcisFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return nstcisFlags;
  }


public:
  HRESULT getSelectedItems( 
            /* [out] */ IShellItemArray **psiaItems)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetSelectedItems( 
      psiaItems);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  IShellItemArray* getSelectedItems( 
            /* [out] */ )
  {
    IShellItemArray* psiaItems = NULL;
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetSelectedItems( 
      &psiaItems);

    if (FAILED(hr)) {
      throw hr;
    }
    return psiaItems;
  }

        
public:
  HRESULT getItemCustomState( 
            /* [in] */ IShellItem *psi,
            /* [out] */ int *piStateNumber)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemCustomState( 
        psi,
        piStateNumber);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int getItemCustomState( 
            /* [in] */ IShellItem *psi)
  {
    int iStateNumber;

    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemCustomState( 
        psi,
        &iStateNumber);

    if (FAILED(hr)) {
      throw hr;
    }
    return iStateNumber;
  }

        
public:
  HRESULT setItemCustomState( 
            /* [in] */ IShellItem *psi,
            /* [in] */ int iStateNumber)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> SetItemCustomState( 
        psi,
        iStateNumber);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT ensureItemVisible( 
            /* [in] */ IShellItem *psi)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> EnsureItemVisible( 
        psi);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT setSelection(
    /* [in]*/ const char* displayName)
  {
    return setSelection((const wchar_t*)_bstr_t(displayName));
  }

public:
  HRESULT setSelection(
    /* [in]*/ const wchar_t* displayName)
  {
    SFGAOF sfgaof;
    PIDLIST_ABSOLUTE pidl;
    HRESULT hr = SHParseDisplayName(displayName, NULL, &pidl, SFGAO_FOLDER, &sfgaof);
    if (FAILED(hr)) {
      throw hr;
    }
  
    ShellItem shellItem(pidl);
    hr = setItemState(shellItem, NSTCIS_SELECTED, NSTCIS_SELECTED);
    if (FAILED(hr)) {
      throw hr;
    }

    hr = ensureItemVisible(shellItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT setSelection(
    /* [in]*/ PCIDLIST_ABSOLUTE pidl)
  {  
    ShellItem shellItem(pidl);
    HRESULT hr = S_OK;

    hr = setItemState(shellItem, NSTCIS_SELECTED, NSTCIS_SELECTED);
    if (FAILED(hr)) {
      throw hr;
    }

    hr = ensureItemVisible(shellItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setSelection(
    /* [in]*/ IShellItem* pShellItem)
  {  
    HRESULT hr = S_OK;
    hr = setItemState(pShellItem, NSTCIS_SELECTED, NSTCIS_SELECTED);
    if (FAILED(hr)) {
      throw hr;
    }

    hr = ensureItemVisible(pShellItem);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setTheme( 
            /* [in] */ LPCWSTR pszTheme)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> SetTheme( 
        pszTheme);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT getNextItem( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCGNI nstcgi,
            /* [out] */ IShellItem **ppsiNext)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetNextItem( 
        psi,
        nstcgi,
        ppsiNext);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItem* getNextItem( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCGNI nstcgi)
  {
    IShellItem *psiNext = NULL;
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetNextItem( 
        psi,
        nstcgi,
        &psiNext);

    if (FAILED(hr)) {
      throw hr;
    }
    return psiNext;
  }

        
public:
  HRESULT hitTest( 
            /* [in] */ POINT *ppt,
            /* [out] */ IShellItem **ppsiOut)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> HitTest( 
      ppt,
      ppsiOut);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItem* hitTest( 
            /* [in] */ POINT *ppt)
  {
    IShellItem *psiOut = NULL;
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> HitTest( 
      ppt,
      &psiOut);

    if (FAILED(hr)) {
      throw hr;
    }
    return psiOut;
  }

        
public:
  HRESULT getItemRect( 
            /* [in] */ IShellItem *psi,
            /* [out] */ RECT *prect)
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemRect( 
        psi,
        prect);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  RECT getItemRect( 
            /* [in] */ IShellItem *psi)
  {
    RECT rect;
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> GetItemRect( 
        psi,
        &rect);

    if (FAILED(hr)) {
      throw hr;
    }
    return rect;
  }

        
public:
  HRESULT collapseAll()
  {
    INameSpaceTreeControl* pControl = getControl();
    HRESULT hr = pControl -> CollapseAll();

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HWND getWindow() //This returns a window handle for the window class "NameSpaceTreeControl"
  {
    HWND hwnd = NULL;
    try {
      OleWindow oleWindow = (IOleWindow*)queryInterface(IID_IOleWindow);
      hwnd = oleWindow.getWindow();
    } catch (...) {

    }
    return hwnd;
  }

public:
  //2012/11/26
  //Get a window handle of the CommonControl SysTreeView32 embedded in NameSpaceTreeControl windnow.
  HWND getTreeView() 
  {
    HWND hTreeView = NULL;

    try {
      const int TREEVIEW_ID = 0x64;

      OleWindow oleWindow = (IOleWindow*)queryInterface(IID_IOleWindow);
      HWND hwndControl = oleWindow.getWindow();
      hTreeView = GetDlgItem(hwndControl, TREEVIEW_ID);
      /*
      HWND hChild = GetWindow(hwndControl, GW_CHILD);
      TCHAR className[1024];
      while (hChild) {
        GetClassName(hChild, className, CountOf(className));
        if (stricmp((const TCHAR*)className, (const TCHAR*)WC_TREEVIEW) == 0) { //WC_TREEVIEWA = "SysTreeView32"
          hTreeView = hChild;
          break;
        }
        hChild = GetWindow(hChild, GW_HWNDNEXT);
      }
      */
    } catch (...) {
    }
    return hTreeView;
  }


public:
  void expand(const wchar_t* path)
  {
    try {
      setSelection(path);
      HWND hTreeView = getTreeView();
      SetFocus(hTreeView);
      PostMessage(hTreeView, WM_KEYDOWN, VK_RIGHT, 0);
    } catch (...) {
    }
  }

};

}
