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
 *  ShellBrowser.h
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

class ShellBrowser: public IShellBrowser {
private:
  LONG refCount;

private:
  HWND hwndView;
  IShellView* pShellView;
  HWND hwndParent;

public:
  ShellBrowser()
    :refCount(1),
    hwndView(NULL),
    hwndParent(NULL),
    pShellView(NULL)
  {
  }

public:
  ~ShellBrowser()
  {
    clean();
  }

public:
  void clean()
  {
    if (pShellView) {
      pShellView -> Release();
      pShellView = NULL;
    }
    if (hwndView) {
      hwndView = NULL;
    }
  }


public:
  IShellBrowser* getShellBrowser()
  {
    return static_cast<IShellBrowser *>(this);
  }

  
/*
typedef struct FOLDERSETTINGS {
  UINT ViewMode;
  UINT fFlags;
} FOLDERSETTINGS;

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

typedef enum FOLDERFLAGS { 
  FWF_NONE                 = 0x00000000,
  FWF_AUTOARRANGE          = 0x00000001,
  FWF_ABBREVIATEDNAMES     = 0x00000002,
  FWF_SNAPTOGRID           = 0x00000004,
  FWF_OWNERDATA            = 0x00000008,
  FWF_BESTFITWINDOW        = 0x00000010,
  FWF_DESKTOP              = 0x00000020,
  FWF_SINGLESEL            = 0x00000040,
  FWF_NOSUBFOLDERS         = 0x00000080,
  FWF_TRANSPARENT          = 0x00000100,
  FWF_NOCLIENTEDGE         = 0x00000200,
  FWF_NOSCROLL             = 0x00000400,
  FWF_ALIGNLEFT            = 0x00000800,
  FWF_NOICONS              = 0x00001000,
  FWF_SHOWSELALWAYS        = 0x00002000,
  FWF_NOVISIBLE            = 0x00004000,
  FWF_SINGLECLICKACTIVATE  = 0x00008000,
  FWF_NOWEBVIEW            = 0x00010000,
  FWF_HIDEFILENAMES        = 0x00020000,
  FWF_CHECKSELECT          = 0x00040000,
  FWF_NOENUMREFRESH        = 0x00080000,
  FWF_NOGROUPING           = 0x00100000,
  FWF_FULLROWSELECT        = 0x00200000,
  FWF_NOFILTERS            = 0x00400000,
  FWF_NOCOLUMNHEADER       = 0x00800000,
  FWF_NOHEADERINALLVIEWS   = 0x01000000,
  FWF_EXTENDEDTILES        = 0x02000000,
  FWF_TRICHECKSELECT       = 0x04000000,
  FWF_AUTOCHECKSELECT      = 0x08000000,
  FWF_NOBROWSERVIEWSTATE   = 0x10000000,
  FWF_SUBSETGROUPS         = 0x20000000,
  FWF_USESEARCHFOLDER      = 0x40000000,
  FWF_ALLOWRTLREADING      = 0x80000000
} FOLDERFLAGS;
*/

public:
  // rfid takes a folder Id of type REFKNOWNFOLDERID. For example, FOLDERID_Desktop, 
  BOOL create(HWND hParent, REFKNOWNFOLDERID rfid, FOLDERSETTINGS fs, RECT rc)
  {
    BOOL r = FALSE; 
    if (IsEqualGUID((const GUID)rfid, (const GUID)FOLDERID_Desktop)) {
      r = create(hParent, fs, rc);
    } else {
      PIDLIST_ABSOLUTE pidl;
      HRESULT hr = SHGetKnownFolderIDList(rfid, 0, (HANDLE)-1, &pidl);
      CoSmartPtr<PIDLIST_ABSOLUTE> idl(pidl);

      if (FAILED(hr)) {
        MessageBox(NULL, _T("Failed to SHGetKnownFolderIDList"), _T("Error"), MB_OK);

        throw hr;
      }
      r = create(hParent, pidl,
        fs, rc);
    }
    return r;
  }

public:
  // csidl takes one of values CLSID, For example, CSIDL_COMMON_STARTMENU
  BOOL create(HWND hParent, int csidl, FOLDERSETTINGS fs, RECT rc)
  {    
    BOOL r = FALSE;
    if (csidl == CSIDL_DESKTOP) {
      r = create(hParent, fs, rc);
    } else { 
      TCHAR path[1024] = {0};

      PIDLIST_ABSOLUTE pidl;
      HRESULT hr = SHGetSpecialFolderLocation(NULL, csidl, &pidl);
      CoSmartPtr<PIDLIST_ABSOLUTE> idl(pidl);

      if (FAILED(hr)) {
        MessageBox(NULL, _T("Failed to SHGetSpecialFolderLocation"), _T("Error"), MB_OK);
        throw hr;
      }      
      r = create(hParent, pidl, fs, rc);
    }
    return r;
  }

public:
  BOOL create(HWND hParent, FOLDERSETTINGS fs, RECT rc)
  {    
    hwndParent = hParent;

    PIDLIST_ABSOLUTE pidl = NULL;

    IShellFolder* pDesktopFolder = NULL;
    SHGetDesktopFolder(&pDesktopFolder);
    
    HRESULT hr = pDesktopFolder->CreateViewObject(hwndParent, IID_PPV_ARGS(&pShellView));
    pDesktopFolder->Release();

    if (FAILED(hr)) {
      throw hr;;
    }

    hr = pShellView -> CreateViewWindow(NULL, &fs, 
        static_cast<IShellBrowser *>(this),
        &rc, &hwndView);
    if (FAILED(hr)) {
      throw hr;
    }

    pShellView -> UIActivate(SVUIA_ACTIVATE_NOFOCUS);
    
    return TRUE;
  }


public:  
  BOOL create(HWND hParent, const TCHAR* path, FOLDERSETTINGS fs, RECT rc)
  {
    IShellFolder* pDesktopFolder = NULL;
    SHGetDesktopFolder(&pDesktopFolder);

    ULONG chEaten = 0;
    ULONG dwAttributes = 0;
    PIDLIST_RELATIVE pidl = NULL;

    HRESULT hr = pDesktopFolder -> ParseDisplayName(NULL, NULL, 
        (wchar_t*)_bstr_t(path), &chEaten, &pidl, &dwAttributes);
    pDesktopFolder ->Release();

    CoSmartPtr<PIDLIST_RELATIVE> id(pidl);

    if (FAILED(hr)) {
      MessageBox(NULL, _T("Failed to ParseDisplayName"), _T("Error"), MB_OK);
      throw hr;
    }

    BOOL r = create(hParent, pidl, fs, rc);

    return r;
  }

public:
  BOOL create(HWND hParent, PCUIDLIST_RELATIVE pidl, FOLDERSETTINGS fs, RECT rc)
  {
    hwndParent = hParent;
    
    IShellFolder* pDesktopFolder = NULL;
    SHGetDesktopFolder(&pDesktopFolder);    
    
    IShellFolder* pCurFolder = NULL;
    HRESULT hr = pDesktopFolder -> BindToObject(pidl, NULL, IID_IShellFolder, (LPVOID *)&pCurFolder);

    if (FAILED(hr)) {
      MessageBox(NULL, _T("BindToObject"), _T("Error"), MB_OK);
      pDesktopFolder -> Release();
      throw hr;
    }
    
    hr = pCurFolder->CreateViewObject(hwndParent, IID_IShellView, (void**)&pShellView);
    if (FAILED(hr)) {
      MessageBox(NULL, _T("CreateViewObject"), _T(""), MB_OK);
      throw hr;;
    }

    hr = pShellView -> CreateViewWindow(NULL, &fs, 
        static_cast<IShellBrowser *>(this),
        &rc, &hwndView);
    if (FAILED(hr)) {
      MessageBox(NULL, _T("CreateViewWindow"), _T(""), MB_OK);
      throw hr;
    }

    pShellView -> UIActivate(SVUIA_ACTIVATE_NOFOCUS);
    pCurFolder->Release();

    return TRUE;
  }

public:
  IShellFolder* getShellFolderFromPath(const TCHAR* path)
  {
    IShellFolder* pDesktopFolder = NULL;
    SHGetDesktopFolder(&pDesktopFolder);

    ULONG chEaten = 0;
    ULONG dwAttributes = 0;
    PIDLIST_RELATIVE pidl = NULL;
    
    HRESULT hr = pDesktopFolder -> ParseDisplayName(NULL, NULL, 
        (wchar_t*)_bstr_t(path), &chEaten, &pidl, &dwAttributes);
      
    if (FAILED(hr)) {
      pDesktopFolder -> Release();
      throw hr;
    }

    IShellFolder* pCurFolder = NULL;
    hr = pDesktopFolder->BindToObject(pidl, NULL, IID_IShellFolder, (LPVOID *)&pCurFolder);
    pDesktopFolder -> Release();

    if (FAILED(hr)) {
      throw hr;    
    }
    return pCurFolder;    
  }

public:
  PIDLIST_RELATIVE getItemIDList(const TCHAR* path)
  {
    PIDLIST_RELATIVE pIDL = NULL;
  
    IShellFolder* pDesktopFolder;

    HRESULT hr = SHGetDesktopFolder(&pDesktopFolder);
    if (FAILED(hr)) {
      throw hr;
    }

    ULONG  chEaten = 0;
    ULONG  dwAttributes = 0;

    _bstr_t bpath = path;

    hr = pDesktopFolder->ParseDisplayName(NULL, NULL, 
        (wchar_t*)bpath, &chEaten, &pIDL, &dwAttributes);
    
    pDesktopFolder->Release();

    if (FAILED(hr)) {
      throw hr;
    }

    return pIDL;
  }

public:
  void reshape(int x, int y, int width, int height, BOOL flag=TRUE)
  {
    MoveWindow(hwndView, x, y, width, height, flag);
  }

public:
  IShellView* getShellView()
  {
    IShellView* pView = NULL;
    HRESULT hr = QueryInterface(IID_IShellView, (void**)&pView);
    if (FAILED(hr)) {
      throw hr;
    }
    return pView;
  }

public:
  HRESULT insertMenus( 
            /* [in] */ HMENU hmenuShared,
            /* [out][in] */ LPOLEMENUGROUPWIDTHS lpMenuWidths)
  {
    HRESULT hr = InsertMenusSB( 
        hmenuShared,
        lpMenuWidths);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setMenu( 
            /* [in] */ HMENU hmenuShared,
            /* [in] */ HOLEMENU holemenuRes,
            /* [in] */ HWND hwndActiveObject)
  {
    HRESULT hr = SetMenuSB( 
        hmenuShared,
        holemenuRes,
        hwndActiveObject);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  HRESULT removeMenus( 
            /* [in] */ HMENU hmenuShared)
  {
    HRESULT hr = RemoveMenusSB(hmenuShared);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setStatusText( 
            /* [in] */ LPCWSTR pszStatusText)
  {
    HRESULT hr = SetStatusTextSB(pszStatusText);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT enableModeless(/* [in] */ BOOL fEnable)
  {
    HRESULT hr = EnableModelessSB(fEnable);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT translateAccelerator( 
            /* [in] */ MSG *pmsg,
            /* [in] */ WORD wID)
  {
    HRESULT hr = TranslateAcceleratorSB( 
        pmsg,
        wID);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT browseObject( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ UINT wFlags)
  {
    HRESULT hr = BrowseObject( 
        pidl,
        wFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT getViewStateStream( 
            /* [in] */ DWORD grfMode,
            /* [out] */ IStream **ppStrm)
  {
    HRESULT hr = GetViewStateStream( 
      grfMode,
      ppStrm);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IStream* getViewStateStream( 
            /* [in] */ DWORD grfMode)
  {
    IStream* pStream = NULL;
    HRESULT hr = GetViewStateStream( 
      grfMode,
      &pStream);
    if (FAILED(hr)) {
      throw hr;
    }
    return pStream;
  }

public:
  HRESULT getControlWindow( 
            /* [in] */ UINT id,
            /* [out] */ HWND *phwnd)
  {
    HRESULT hr = GetControlWindow( 
        id,
        phwnd);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HWND getControlWindow( 
            /* [in] */ UINT id)
  {
    HWND hwnd = NULL;
    HRESULT hr = GetControlWindow( 
        id,
        &hwnd);

    if (FAILED(hr)) {
      throw hr;
    }
    return hwnd;
  }


public:
  HRESULT sendControlMsg( 
            /* [in] */ UINT id,
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam,
            /* [out] */ LRESULT *pret)
  {
    HRESULT hr = SendControlMsg( 
        id,
        uMsg,
        wParam,
        lParam,
        pret);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT queryActiveShellView( 
            /* [out] */ IShellView **ppshv)
  {
    HRESULT hr = QueryActiveShellView( 
      ppshv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellView* queryActiveShellView()
  {
    IShellView *pshv = NULL;
    HRESULT hr = QueryActiveShellView( 
      &pshv);

    if (FAILED(hr)) {
      throw hr;
    }
    return pshv;
  }
        
public:
  HRESULT onViewWindowActive( 
            /* [in] */ IShellView *pshv)
  {
    HRESULT hr = OnViewWindowActive( 
        pshv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT setToolbarItems( 
            /* [in] */ LPTBBUTTONSB lpButtons,
            /* [in] */ UINT nButtons,
            /* [in] */ UINT uFlags)
  {
    HRESULT hr = SetToolbarItems( 
        lpButtons,
        nButtons,
        uFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  // <IShellBrowser_Interfaces>
public:
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv)
  {
    *ppv = NULL;

    if (IsEqualIID(riid, IID_IUnknown) || 
      IsEqualIID(riid, IID_IOleWindow) ||
      IsEqualIID(riid, IID_IShellBrowser)) {
      *ppv = static_cast<IShellBrowser *>(this);
    }
    else {
      return E_NOINTERFACE;
    }

    AddRef();
    return S_OK;
  }

  virtual ULONG STDMETHODCALLTYPE AddRef()
  {
    return InterlockedIncrement(&refCount);
    //return 1;
  }

  virtual ULONG STDMETHODCALLTYPE Release()
  {
    //return 1;
    if (InterlockedDecrement(&refCount) == 0) {
      delete this;
      return 0;
    }
    return refCount;
  }

  virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND *phwnd)
  {
    HRESULT hr = S_OK;
    if (hwndParent) {
      *phwnd = hwndParent; // Return a hosting window of a shellview object.
    } else {
      *phwnd = NULL;
      hr = E_FAIL;
    }
    return hr;
  }

  virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE InsertMenusSB(HMENU hmenuShared, 
        LPOLEMENUGROUPWIDTHS lpMenuWidths)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE SetMenuSB(HMENU hmenuShared, 
        HOLEMENU holemenuRes, 
        HWND hwndActiveObject)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE RemoveMenusSB(HMENU hmenuShared)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE SetStatusTextSB(LPCWSTR lpszStatusText)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE EnableModelessSB(BOOL fEnable)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE TranslateAcceleratorSB(LPMSG lpmsg, WORD wID)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE BrowseObject(PCUIDLIST_RELATIVE pidl, UINT wFlags)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetViewStateStream(DWORD grfMode, IStream **ppStrm)
  {
    return E_NOTIMPL;
  }


  virtual HRESULT STDMETHODCALLTYPE GetControlWindow(UINT id, HWND *lphwnd)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE SendControlMsg(UINT id, 
        UINT uMsg, 
        WPARAM wParam, 
        LPARAM lParam, LRESULT *pret)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE QueryActiveShellView(IShellView **ppshv)
  {
    HRESULT hr = S_OK;
    if (pShellView) {
      *ppshv = pShellView;
    } else {
      hr = E_FAIL;
    }
    return hr;
  }

  virtual HRESULT STDMETHODCALLTYPE OnViewWindowActive(IShellView *ppshv)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE SetToolbarItems(
      LPTBBUTTONSB lpButtons, 
      UINT nButtons, 
      UINT uFlags)
  {
    return E_NOTIMPL;
  }
  // </IShellBrowser_Interfaces>

};

}
