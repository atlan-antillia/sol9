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
 *  ExplorerBrowser.h
 *
 *****************************************************************************/

// 2012/10/30
// 2012/11/15 Updated.

#pragma once

//#include <sol/ole/OleWindow.h>
#include <sol/com/ComIUnknown.h>
#include <sol/Guid.h>
#include <sol/CoSmartPtr.h>
#include <shobjidl.h>

namespace SOL {
   
class ExplorerBrowser: public ComIUnknown {
private:
  DWORD dwCookie;

public:
  ExplorerBrowser()
  :ComIUnknown(),
  dwCookie(0)
  {
    IExplorerBrowser* pBrowser = NULL;

    HRESULT hr = CoCreateInstance(CLSID_ExplorerBrowser, NULL, CLSCTX_INPROC_SERVER, 
      IID_IExplorerBrowser, (void**)&pBrowser);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pBrowser);
    }
  }

public:
  IExplorerBrowser* getBrowser()
  {
    return (IExplorerBrowser*)getIUnknown();
  }

public:
  HRESULT initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ const RECT& rec,
            /* [in] */ const FOLDERSETTINGS& fs)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> Initialize( 
      hwndParent,
      &rec,
      &fs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
  

public:
  HRESULT initialize( 
            /* [in] */ HWND hwndParent,
      /* [in] */ FOLDERVIEWMODE viewMode = FVM_DETAILS,
      /* [in] */ FOLDERFLAGS folderFlags = FWF_NONE,  
      /* [in] */ EXPLORER_BROWSER_OPTIONS option = EBO_SHOWFRAMES)
  {
    RECT rec = {0, 0, 0, 0};
    FOLDERSETTINGS fs;
    fs.ViewMode = viewMode;
    fs.fFlags   = folderFlags;

    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> Initialize( 
      hwndParent,
      &rec,
      &fs);
    if (FAILED(hr)) {
      throw hr;
    }

    setOptions(option);
    
    return hr;
  }

public:
  HRESULT destroy() 
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> Destroy();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT setRect( 
            /* [out][in] */ HDWP *phdwp,
            /* [in] */ RECT rcBrowser)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> SetRect( 
        phdwp,
        rcBrowser);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

   
public:
  HRESULT setPropertyBag( 
            /* [in] */ LPCWSTR pszPropertyBag)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> SetPropertyBag( 
      pszPropertyBag);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT setEmptyText( 
            /* [in] */ LPCWSTR pszEmptyText)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> SetEmptyText( 
      pszEmptyText);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
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
  HRESULT setFolderSettings( 
            /* [in] */ const FOLDERSETTINGS *pfs)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> SetFolderSettings( 
        pfs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  DWORD advise( 
            /* [in] */ IExplorerBrowserEvents *psbe) 
  {
    this -> dwCookie = 0;
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> Advise( 
        psbe,
        &(this->dwCookie)) ;
    if (FAILED(hr)) {
      throw hr;
    }
    return dwCookie;
  }
        

public:
  HRESULT unadvise()
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> Unadvise( 
        this->dwCookie);
    if (FAILED(hr)) {
      throw hr;
    }
    dwCookie = 0;
    return hr;
  }

/*        
typedef enum EXPLORER_BROWSER_OPTIONS { 
  EBO_NONE                = 0x00000000,
  EBO_NAVIGATEONCE        = 0x00000001,
  EBO_SHOWFRAMES          = 0x00000002,
  EBO_ALWAYSNAVIGATE      = 0x00000004,
  EBO_NOTRAVELLOG         = 0x00000008,
  EBO_NOWRAPPERWINDOW     = 0x00000010,
  EBO_HTMLSHAREPOINTVIEW  = 0x00000020,
  EBO_NOBORDER            = 0x00000040,
  EBO_NOPERSISTVIEWSTATE  = 0x00000080
} EXPLORER_BROWSER_OPTIONS;
*/

public:
  HRESULT setOptions( 
            /* [in] */ EXPLORER_BROWSER_OPTIONS dwFlag)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> SetOptions( 
        dwFlag);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getOptions( 
            /* [out] */ EXPLORER_BROWSER_OPTIONS *pdwFlag)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> GetOptions( 
        pdwFlag);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  EXPLORER_BROWSER_OPTIONS getOptions()
  {
    EXPLORER_BROWSER_OPTIONS dwFlag;
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> GetOptions( 
        &dwFlag);
    if (FAILED(hr)) {
      throw hr;
    }
    return dwFlag;
  }
        

public:
  HRESULT browseToIDList( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ UINT uFlags)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> BrowseToIDList( 
        pidl,
        uFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT browseToFolder(REFKNOWNFOLDERID rfid = FOLDERID_Desktop)
  {
    PIDLIST_ABSOLUTE pidl;
    SHGetKnownFolderIDList(rfid, 0, NULL, &pidl); //(HANDLE)-1 default user
    CoSmartPtr<PIDLIST_ABSOLUTE> ptr(pidl);

    return browseToIDList(pidl, SBSP_ABSOLUTE);
  }

public:
  HRESULT browseToPath(const TCHAR* path)
  {
    PIDLIST_ABSOLUTE pidl;
    if (path == NULL || strlen(path) == 0) {
      SHGetKnownFolderIDList(FOLDERID_Desktop, 0, NULL, &pidl); //(HANDLE)-1 default user
    } else {
      pidl = ILCreateFromPath(path);
    }
    CoSmartPtr<PIDLIST_ABSOLUTE> ptr(pidl);
    return browseToIDList(pidl, SBSP_ABSOLUTE);
  }

public:
  HRESULT browseToObject( 
            /* [in] */ IUnknown *punk,
            /* [in] */ UINT uFlags)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> BrowseToObject( 
        punk,
        uFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT fillFromObject( 
            /* [in] */ IUnknown *punk,
            /* [in] */ EXPLORER_BROWSER_FILL_FLAGS dwFlags)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> FillFromObject( 
        punk,
        dwFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT removeAll()
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> RemoveAll();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getCurrentView( 
            /* [in] */REFIID riid,
            /* [out] */ void **ppv)
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> GetCurrentView( 
        riid,
        ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  void* getCurrentView( 
            /* [in] */REFIID riid)
  {
    void* pv = NULL;
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> GetCurrentView( 
        riid,
        &pv);
    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }
    
public:
  void reshape(int x, int y, int width, int height)
  {
    RECT rec = {x, y, x+width, y+height};
    setRect(NULL, rec);
  }

public:
  HRESULT navigateBack()
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> BrowseToIDList(NULL, SBSP_NAVIGATEBACK);
    if (FAILED(hr)) {
      throw hr;
    }
      return hr;
  }

public:
  HRESULT navigateForward()
  {
    IExplorerBrowser* pBrowser = getBrowser();
    HRESULT hr = pBrowser -> BrowseToIDList(NULL, SBSP_NAVIGATEFORWARD);
    if (FAILED(hr)) {
      throw hr;
    }
      return hr;
  }

  //2012/11/15
public:
  IFolderFilterSite* getFolderFilterSite()
  {
    return (IFolderFilterSite*)queryInterface(IID_IFolderFilterSite);
  }

  //2012/11/15
public:
  HRESULT setFolderFilter(IFolderFilter* pFilter)
  {
    IFolderFilterSite* pSite = getFolderFilterSite();

    HRESULT hr = pSite -> SetFilter(pFilter);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
};

}
