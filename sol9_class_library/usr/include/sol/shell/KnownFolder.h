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
 *  KnownFolder.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>
#include <sol/HTMLEncoder.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>
#include <sol/FileFlagsAndAttributes.h>
#include <sol/Writer.h>
#include <sol/Guid.h>


namespace SOL {

class KnownFolder: public ComIUnknown {

public:
  KnownFolder(IKnownFolder* pFolder=NULL)
  :ComIUnknown(pFolder)
  {

  }

public:
  IKnownFolder* getFolder()
  {
    return (IKnownFolder*)getIUnknown();
  }

public:
  HRESULT getId(/* [out] */ KNOWNFOLDERID *pkfid)
  {
    //IKnownFolder* pFolder = getFolder();
    HRESULT hr = getFolder() -> GetId(pkfid);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  KNOWNFOLDERID getId() 
  {
    KNOWNFOLDERID kfid;
    IKnownFolder* pFolder = getFolder();

    HRESULT hr = pFolder -> GetId(&kfid); 

    if (FAILED(hr)) {
      throw hr;
    }
    return kfid;  
  }

public:
  HRESULT getCategory( 
            /* [out] */ KF_CATEGORY *pCategory) 
  {
    IKnownFolder* pFolder = getFolder();

    HRESULT hr = pFolder -> GetCategory(pCategory);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  KF_CATEGORY getCategory() 
  {
    KF_CATEGORY category;
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetCategory(&category);

    if (FAILED(hr)) {
      throw hr;
    }
    return category;  
  }
         
public:
  HRESULT getShellItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetShellItem( 
        dwFlags,
        riid,
        ppv);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }

/* 
typedef enum  { 
  KF_FLAG_SIMPLE_IDLIST                = 0x00000100,
  KF_FLAG_NOT_PARENT_RELATIVE          = 0x00000200,
  KF_FLAG_DEFAULT_PATH                 = 0x00000400,
  KF_FLAG_INIT                         = 0x00000800,
  KF_FLAG_NO_ALIAS                     = 0x00001000,
  KF_FLAG_DONT_UNEXPAND                = 0x00002000,
  KF_FLAG_DONT_VERIFY                  = 0x00004000,
  KF_FLAG_CREATE                       = 0x00008000,
  KF_FLAG_NO_APPCONTAINER_REDIRECTION  = 0x00010000,
  KF_FLAG_ALIAS_ONLY                   = 0x80000000
} KNOWN_FOLDER_FLAG
*/
  //dwFlags can take one of KNOWN_FOLDER_FLAG enum.
public:
  IShellItem* getShellItem( 
            /* [in] */ DWORD dwFlags = KF_FLAG_DEFAULT_PATH)
   {
     REFIID riid = IID_IShellItem;

    IShellItem* psi = NULL;

    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetShellItem( 
        dwFlags,
        riid,
        (void**)&psi); 

    if (FAILED(hr)) {
      throw hr;
    }
    return psi;  
  }
    
public:
  // You have to free the returned path string by calling CoTaskMemFree().
  HRESULT getPath( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ wchar_t** ppszPath) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetPath( 
        dwFlags,
        ppszPath); 

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  

  }

public:
  _bstr_t getPath( 
            /* [in] */ DWORD dwFlags=0) 
  {
    wchar_t* path = NULL;

    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetPath( 
        dwFlags,
        &path); 

    if (FAILED(hr)) {
      throw hr;
    }

    wchar_t* wpath = new_strdup(path); //Make a copy of path
    CoTaskMemFree(path);    //Free the original path string
    return _bstr_t(wpath);  //Return _bstr_t of wpath 
  }

        
public:
  HRESULT setPath( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ const wchar_t* pszPath) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> SetPath( 
        dwFlags,
        pszPath); 

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }

        
public:
  HRESULT getIDList( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetIDList( 
        dwFlags,
        ppidl);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }

public:
  PIDLIST_ABSOLUTE getIDList( 
            /* [in] */ DWORD dwFlags) 
  {
    PIDLIST_ABSOLUTE pidl;
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetIDList( 
        dwFlags,
        &pidl);

    if (FAILED(hr)) {
      throw hr;
    }
    return pidl;  
  }
    
public:
  HRESULT getFolderType( 
            /* [out] */ FOLDERTYPEID *pftid) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetFolderType( 
      pftid);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }

public:
  FOLDERTYPEID getFolderType() 
  {
    FOLDERTYPEID ftid;

    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetFolderType( 
      &ftid);

    if (FAILED(hr)) {
      throw hr;
    }
    return ftid;  
  }

        
public:
  HRESULT getRedirectionCapabilities( 
    /* [out] */ KF_REDIRECTION_CAPABILITIES *pCapabilities) 
  {
    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetRedirectionCapabilities(pCapabilities);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }

public:
  KF_REDIRECTION_CAPABILITIES getRedirectionCapabilities() 
  {
    KF_REDIRECTION_CAPABILITIES capabilities;

    IKnownFolder* pFolder = getFolder();
    HRESULT hr = pFolder -> GetRedirectionCapabilities(&capabilities);
    if (FAILED(hr)) {
      throw hr;
    }
    return capabilities;
  }

/*
typedef struct KNOWNFOLDER_DEFINITION {
  KF_CATEGORY         category;
  LPWSTR              pszName;
  LPWSTR              pszDescription;
  KNOWNFOLDERID       fidParent;
  LPWSTR              pszRelativePath;
  LPWSTR              pszParsingName;
  LPWSTR              pszTooltip;
  LPWSTR              pszLocalizedName;
  LPWSTR              pszIcon;
  LPWSTR              pszSecurity;
  DWORD               dwAttributes;
  KF_DEFINITION_FLAGS kfdFlags;
  FOLDERTYPEID        ftidType;
} KNOWNFOLDER_DEFINITION;
*/
public:
  //The returned pointer pKDF has to be freed by calling 
  //FreeKnownFolderDefinitionFields();
  HRESULT getFolderDefinition( 
    /* [out] */ KNOWNFOLDER_DEFINITION *pKFD)  
  {
    IKnownFolder* pFolder = getFolder();

    HRESULT hr = pFolder -> GetFolderDefinition(pKFD);
    //FOLDERTYPEID        ftidType;
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;  
  }
        
public:
  KNOWNFOLDER_DEFINITION getFolderDefinition()  
  {
    KNOWNFOLDER_DEFINITION kfd;
    IKnownFolder* pFolder = getFolder();

    HRESULT hr = pFolder -> GetFolderDefinition(&kfd);

    if (FAILED(hr)) {
      throw hr;
    }
    return kfd;  
  }

public:
  virtual void write(Writer& writer)
  {
    Guid guid;

    writer.write(L"<KnownFolder>\n");
    
    KNOWNFOLDER_DEFINITION def;
    getFolderDefinition(&def); 
    
    HTMLEncoder encoder;
    writer.write(L"<Category>%s</Category>\n", (const wchar_t*)_bstr_t(toString(def.category) ) );
    
    _bstr_t name;
    encoder.encode(def.pszName, name);
    writer.write(L"<Name>%s</Name>\n",    (const wchar_t*)name);
  
    _bstr_t desc;
    encoder.encode(def.pszDescription, desc);
    writer.write(L"<Description>%s</Description>\n", (const wchar_t*)desc);

    writer.write(L"<ParentFolderId>%d</ParentFolderId>\n",    def.fidParent);
    
    _bstr_t rpath;
    encoder.encode(def.pszRelativePath, rpath);
    writer.write(L"<RelativePath>%s</RelativePath>\n", (const wchar_t*)rpath);

    _bstr_t pname;
    encoder.encode(def.pszParsingName, pname);
    writer.write(L"<ParsingName>%s</ParsingName>\n",   (const wchar_t*)pname);
    
    _bstr_t tip;
    encoder.encode(def.pszTooltip, tip);
    writer.write(L"<Tooltip>%s</Tooltip>\n",  (const wchar_t*)tip);
    
    _bstr_t lname;
    encoder.encode(def.pszLocalizedName, lname);
    writer.write(L"<LocalizedName>%s</LocalizedName>\n", (const wchar_t*)lname);

    _bstr_t icon;
    encoder.encode(def.pszIcon, icon);
    writer.write(L"<Icon>%s</Icon>\n", (const wchar_t*)icon);

    _bstr_t security;
    encoder.encode(def.pszSecurity, security);
    writer.write(L"<Security>%s</Security>\n", (const wchar_t*)security);
    
    FileFlagsAndAttributes flagsAndAttributes;
    _bstr_t attrs = flagsAndAttributes.toString(def.dwAttributes);
    writer.write(L"<Attributes>%s</Attributes>\n", (const wchar_t*)attrs);

    _bstr_t dflags = toString(def.kfdFlags);
    writer.write(L"<Flags>%s</Flags>\n",  (const wchar_t*)dflags);
    
    writer.write(L"<FileTypeId>%d</FileTypeId>\n",  (const wchar_t*)guid.toString(def.ftidType));

    writer.write(L"</KnownFolder>\n");

    FreeKnownFolderDefinitionFields(&def);
  }

public:
  const TCHAR* toString(KF_CATEGORY kf)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("VIRTUAL"), KF_CATEGORY_VIRTUAL},
      {_T("FIXED"), KF_CATEGORY_FIXED},
      {_T("COMMON"), KF_CATEGORY_COMMON},
      {_T("PERUSER"), KF_CATEGORY_PERUSER}
    };

    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(kf);
  }

public:
  const TCHAR* toString(KF_DEFINITION_FLAGS kf)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("LOCAL_REDIRECT_ONLY"), KFDF_LOCAL_REDIRECT_ONLY},
      {_T("ROAMABLE"), KFDF_ROAMABLE},
      {_T("PRECREATE"), KFDF_PRECREATE},
      {_T("STREAM"), KFDF_STREAM},
      {_T("PUBLISHEXPANDEDPATH"), KFDF_PUBLISHEXPANDEDPATH},
    };

    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(kf);
  }
};

}
