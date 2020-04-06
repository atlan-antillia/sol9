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
// 2012/11/20 Added ShellItem(wchar_t* filePath) constructor

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>
#include <sol/ArgT.h>
#include <sol/StringBufferT.h>
#include <sol/FileWriter.h>
#include <sol/HTMLEncoder.h>
#include <propkey.h>


namespace SOL {

class ShellItem: public ComIUnknown {

public:
  ShellItem(IShellItem* pItem=NULL)
  :ComIUnknown(pItem)
  {
  }

public:
  ShellItem(PCIDLIST_ABSOLUTE pidl, REFIID riid = IID_IShellItem)
  {
    IShellItem* pItem = NULL;
    HRESULT hr = SHCreateItemFromIDList(
          pidl,
          riid,
          (void**)&pItem);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pItem);
    }
  }

public:
  ShellItem(REFKNOWNFOLDERID kfid, REFIID riid = IID_IShellItem)
  {
    IShellItem* pItem = NULL;

    HRESULT hr = SHCreateItemInKnownFolder(kfid, 0, NULL,
        riid, (void**)&pItem);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pItem);
    }
  }

public:
  //2012/11/20
  ShellItem(const wchar_t* filePath)
  {
    IShellItem* pItem = NULL;

    HRESULT hr = SHCreateItemFromParsingName(
        filePath, NULL, IID_IShellItem, (void**)&pItem);

    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pItem);
    }
  }

public:
  IShellItem* getItem()
  {
    return (IShellItem*)getIUnknown();
  }
    
public:
  operator IShellItem*()
  {
    return (IShellItem*)getIUnknown();
  }


public:
  HRESULT bindToHandler( 
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID bhid,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> BindToHandler( 
        pbc,
        bhid,
        riid,
        ppv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getParent( 
            /* [out] */ IShellItem **ppsi)
  {
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetParent(ppsi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  IShellItem* getParent()
  {
    IShellItem* psi = NULL;
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetParent(&psi);
    if (FAILED(hr)) {
      throw hr;
    }
    return psi;
  }


public:
  HRESULT getDisplayName( 
            /* [in] */ SIGDN sigdnName,
            /* [out] */ LPWSTR *ppszName)
  {
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetDisplayName( 
        sigdnName,
        ppszName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
/*
typedef enum _SIGDN { 
  SIGDN_NORMALDISPLAY                = 0x00000000,
  SIGDN_PARENTRELATIVEPARSING        = (int)0x80018001,
  SIGDN_DESKTOPABSOLUTEPARSING       = (int)0x80028000,
  SIGDN_PARENTRELATIVEEDITING        = (int)0x80031001,
  SIGDN_DESKTOPABSOLUTEEDITING       = (int)0x8004c000,
  SIGDN_FILESYSPATH                  = (int)0x80058000,
  SIGDN_URL                          = (int)0x80068000,
  SIGDN_PARENTRELATIVEFORADDRESSBAR  = (int)0x8007c001,
  SIGDN_PARENTRELATIVE               = (int)0x80080001,
  SIGDN_PARENTRELATIVEFORUI          = (int)0x80094001
} SIGDN;
*/
public:
  _bstr_t getDisplayName( 
            /* [in] */ SIGDN sigdnName = SIGDN_NORMALDISPLAY)
  {
    wchar_t* name = NULL;
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetDisplayName( 
        sigdnName,
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    wchar_t* tname = new_strdup(name);
    CoTaskMemFree(name);
    return _bstr_t(tname);
  }

public:
  HRESULT getAttributes( 
    /* [in] */ SFGAOF sfgaoMask,
    /* [out] */ SFGAOF *psfgaoAttribs)
  {
    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetAttributes( 
        sfgaoMask,
      psfgaoAttribs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  SFGAOF getAttributes( 
    /* [in] */ SFGAOF sfgaoMask)
  {
    SFGAOF sfgaoAttribs;

    IShellItem* pItem = getItem();
    HRESULT hr = pItem -> GetAttributes( 
        sfgaoMask,
        &sfgaoAttribs);
    if (FAILED(hr)) {
      throw hr;
    }
    return sfgaoAttribs;
  }

public:
  static _bstr_t toString(SFGAOF value)
  {
    ArgT<TCHAR> names[] = {
      
    {_T("CANCOPY"), SFGAO_CANCOPY},
    {_T("CANMOVE"), SFGAO_CANMOVE},
    {_T("CANLINK"), SFGAO_CANLINK},
    {_T("STORAGE"), SFGAO_STORAGE},
    {_T("CANRENAME"), SFGAO_CANRENAME},
    {_T("CANDELETE"), SFGAO_CANDELETE},
    {_T("HASPROPSHEET"), SFGAO_HASPROPSHEET},
    {_T("DROPTARGET"), SFGAO_DROPTARGET},
    {_T("CAPABILITYMASK"), SFGAO_CAPABILITYMASK},
    {_T("ENCRYPTED"), SFGAO_ENCRYPTED},
    {_T("ISSLOW"), SFGAO_ISSLOW},
    {_T("GHOSTED"), SFGAO_GHOSTED},
    {_T("LINK"), SFGAO_LINK},
    {_T("SHARE"), SFGAO_SHARE},
    {_T("READONLY"), SFGAO_READONLY},
    {_T("HIDDEN"), SFGAO_HIDDEN},
    {_T("DISPLAYATTRMASK"), SFGAO_DISPLAYATTRMASK},
    {_T("FILESYSANCESTOR"), SFGAO_FILESYSANCESTOR}, 
    {_T("FOLDER"), SFGAO_FOLDER},
    {_T("FILESYSTEM"), SFGAO_FILESYSTEM},
    {_T("HASSUBFOLDER"), SFGAO_HASSUBFOLDER},
    //{_T("VALIDATESFGAO_REMOVABLE"), SFGAO_VALIDATESFGAO_REMOVABLE},
    {_T("COMPRESSED"), SFGAO_COMPRESSED},
    {_T("BROWSABLE"), SFGAO_BROWSABLE},
    {_T("NONENUMERATED"), SFGAO_NONENUMERATED},
    {_T("NEWCONTENT"), SFGAO_NEWCONTENT},
    {_T("CANMONIKER"), SFGAO_CANMONIKER},
    {_T("HASSTORAGE"), SFGAO_HASSTORAGE},
    {_T("STREAM"), SFGAO_STREAM},
    {_T("STORAGEANCESTOR"), SFGAO_STORAGEANCESTOR},
    {_T("STORAGECAPMASK"), SFGAO_STORAGECAPMASK}, 
    };

    StringBufferT<TCHAR> buffer;
    int n = 0;
    for (int i = 0; i<CountOf(names); i++) {
      if (value & names[i].value) {
        if (n > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        n++;
      }
    }
    return _bstr_t((const TCHAR*)buffer);
  }

public:
  HRESULT  compare( 
            /* [in] */ IShellItem *psi,
            /* [in] */ SICHINTF hint,
            /* [out] */ int *piOrder)
  {
    IShellItem* pItem = getItem();
    HRESULT hr = pItem ->  Compare( 
        psi,
        hint,
        piOrder);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int compare( 
            /* [in] */ IShellItem *psi,
            /* [in] */ SICHINTF hint)
  {
    int iOrder = 0;
    IShellItem* pItem = getItem();
    HRESULT hr = pItem ->  Compare( 
        psi,
        hint,
        &iOrder);
    if (FAILED(hr)) {
      throw hr;
    }
    return iOrder;
  }
       
public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<ShellItem>\n");
    
    HTMLEncoder encoder;
    try {
      _bstr_t displayName = getDisplayName();
      _bstr_t encName;
      encoder.encode((const wchar_t*)displayName, encName);
      writer.write(L"<DisplayName>%s</DisplayName>\n", (const wchar_t*)encName);
    } catch (...) {
    }

    try {
      _bstr_t computerName = getString(PKEY_ComputerName);
      writer.write(L"<ComputerName>%s</ComputerName>\n", (const wchar_t*)computerName);
    } catch (...) {
    }

    try {
      _bstr_t fileAttr = getString(PKEY_FileAttributes);
      writer.write(L"<FileAttributes>%s</FileAttributes>\n", (const wchar_t*)fileAttr);
    } catch (...) {
    }

    try {
      _bstr_t fileName = getString(PKEY_FileName);
      writer.write(L"<FileName>%s</FileName>\n", (const wchar_t*)fileName);
    } catch (...) {
    }

    try {
      _bstr_t date = getString(PKEY_DateModified);
      writer.write(L"<DateModified>%s</DateModified>\n", (const wchar_t*)date);
    } catch (...) {
    }

    try {
      _bstr_t percentFull = getString(PKEY_PercentFull);
      writer.write(L"<PercentFull>%s</PercentFull>\n", (const wchar_t*)percentFull);
    } catch (...) {
    }

    try {
      _bstr_t  freeSpace   = getString(PKEY_FreeSpace);
      writer.write(L"<FreeSpace>%s</FreeSpace>\n", (const wchar_t*)freeSpace);
    } catch (...) {
    }

    try {
      _bstr_t capacity    = getString(PKEY_Capacity);
      writer.write(L"<Capacity>%s</Capacity>\n", (const wchar_t*)capacity);
    } catch (...) {
    }

    try {
      _bstr_t fileSystem = getString(PKEY_Volume_FileSystem);

      writer.write(L"<Capacity>%s</Capacity>\n", (const wchar_t*)fileSystem);
    } catch (...) {
    }
    
  
/*
      PKEY_DateCreated,
      PKEY_DateAccessed,
      PKEY_DateModified
      PKEY_Link_TargetParsingPath
      PKEY_ComputerName,

      PKEY_FileAttributes,
      PKEY_FileName,
      PKEY_FileOwner,
      ...  
      PKEY_ItemDate,
      PKEY_ItemFolderNameDisplay,
      PKEY_ItemFolderPathDisplay,
      PKEY_ItemFolderPathDisplayNarrow,
      PKEY_ItemPathDisplay,
      ...
      PKEY_Kind,      
      PKEY_Rating,    
      ...
*/

    writer.write(L"</ShellItem>\n");
  }

  //<IShellItem2>
public:
  IShellItem2* getItem2()
  {
    return (IShellItem2*)queryInterface(IID_IShellItem2);
  }

    
public:
  HRESULT getPropertyStore( 
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetPropertyStore( 
          flags,
          riid,
        ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  HRESULT getPropertyStoreWithCreateObject( 
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ IUnknown *punkCreateObject,
            /* [in] */REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetPropertyStoreWithCreateObject( 
            flags,
            punkCreateObject,
            riid,
            ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

        
public:
  HRESULT getPropertyDescriptionList( 
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetPropertyDescriptionList( 
            keyType,
            riid,
            ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        
        
public:
  IPropertyDescriptionList* getPropertyDescriptionList( 
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid)
  {
    IPropertyDescriptionList* pv = NULL;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetPropertyDescriptionList( 
            keyType,
            riid,
            (void**)&pv);

    if (FAILED(hr)) {
      throw hr;
    }
    return pv;
  }

public:
  HRESULT update( 
            /* [in] */ IBindCtx *pbc)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> Update(pbc);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT getProperty( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ PROPVARIANT *ppropvar)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetProperty( 
            key,
            ppropvar);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        
        
public:
  HRESULT getCLSID( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ CLSID *pclsid)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetCLSID( 
            key,
            pclsid);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  CLSID getCLSID( 
            /* [in] */ REFPROPERTYKEY key)
  {
    CLSID clsid;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetCLSID( 
            key,
            &clsid);

    if (FAILED(hr)) {
      throw hr;
    }
    return clsid;
  }
 

public:
  HRESULT getFileTime( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ FILETIME *pft)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetFileTime( 
            key,
            pft);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  FILETIME getFileTime( 
            /* [in] */ REFPROPERTYKEY key=PKEY_DateModified)
  {
    FILETIME ft;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetFileTime( 
            key,
            &ft);

    if (FAILED(hr)) {
      throw hr;
    }
    return ft;
  }
        
        
public:
  HRESULT getInt32( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ int *pi)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetInt32( 
          key,
          pi);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  int getInt32( 
            /* [in] */ REFPROPERTYKEY key)
  {
    int i = 0;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetInt32( 
          key,
          &i);
    if (FAILED(hr)) {
      throw hr;
    }
    return i;
  }
        
public:
  HRESULT getString( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ LPWSTR *ppsz)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetString( 
          key,
          ppsz);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getString( 
            /* [in] */ REFPROPERTYKEY key)
  {
    wchar_t* psz = NULL;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetString( 
          key,
          &psz);

    if (FAILED(hr)) {
      throw hr;
    }

    wchar_t* string = new_strdup(psz); 
    CoTaskMemFree(psz);
    return _bstr_t(string);
  }
        
public:
  HRESULT getUInt32( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ ULONG *pui)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetUInt32( 
          key,
          pui);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }     

public:
  ULONG getUInt32( 
            /* [in] */ REFPROPERTYKEY key)
  {
    ULONG ui = 0;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetUInt32( 
          key,
          &ui);
    if (FAILED(hr)) {
      throw hr;
    }
    return ui;
  }
        
public:
  HRESULT getUInt64( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ ULONGLONG *pull)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetUInt64( 
            key,
            pull);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  ULONGLONG getUInt64( 
            /* [in] */ REFPROPERTYKEY key)
  {
    ULONGLONG ull;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetUInt64( 
            key,
            &ull);
    if (FAILED(hr)) {
      throw hr;
    }
    return ull;
  }
        
public:
  HRESULT getBool( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ BOOL *pf)
  {
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetBool( 
            key,
            pf);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        
   
public:
  BOOL getBool( 
            /* [in] */ REFPROPERTYKEY key)
  {
    BOOL f;
    IShellItem2* pItem2 = getItem2();
    HRESULT hr = pItem2 -> GetBool( 
            key,
            &f);
    if (FAILED(hr)) {
      throw hr;
    }
    return f;
  }

//</IShellItem2>
};

}

    
