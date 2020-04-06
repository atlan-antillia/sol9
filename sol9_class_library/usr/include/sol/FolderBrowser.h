/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FolderBrowser.h
 *
 *****************************************************************************/

#pragma once


#include <sol\Object.h>
#include <sol\String.h>
#include <sol/View.h>
#include <sol/Profile.h>
#include <shlobj.h>
#include <shellapi.h>


namespace SOL {

class FolderBrowser :public Object {
private:
  HWND hwnd;
  String title;
  String selectedFolder;
  String startingDirectory;
  Profile profile;
  
public:
  /**
   * Constructor
   */
  FolderBrowser(View* view, const TCHAR* name, Args& args) 
  {
    HWND hwnd = NULL;
    if (view) {
      hwnd = view->getWindow();
    }
    
    title = _T("Please select a folder");
    if (args.has(XmNtitle)) {
      title = (const TCHAR*)args.get(XmNtitle);
    }
    
    this->hwnd = hwnd;
    this->title = title;
    this->selectedFolder = _T("");
  
    startingDirectory = _T("C:\\ProgramData");
    if (args.has(XmNstartingDirectory)) {
      startingDirectory = (const TCHAR*)args.get(XmNstartingDirectory);
    }
    OleInitialize(NULL);
  }

  FolderBrowser(HWND hwnd=NULL) {
    this->hwnd = hwnd;
    this->title = _T("Please select a folder");

    OleInitialize(NULL);
  }

public:
  /**
   * Destructor
   */
  ~FolderBrowser() {
    OleUninitialize();
  }


public:
  void setTitle(const TCHAR* string) {
    this->title = string;
  }

public:
  /**
   * @param startingDir    [IN] Starting folder's directory    
   * @param selectedFolder  [OUT] Selected folder's full path  
   * @return BOOL  
   */
  BOOL show(const TCHAR* startingDir, String& selectedFullPath)
  {
    BOOL    rc = FALSE;

    selectedFullPath = "";  //Initialize to empty string.

    LPMALLOC  lpMalloc = NULL;

    if (FAILED(SHGetMalloc(&lpMalloc))) {
      return rc;
    }

    TCHAR fileName[_MAX_PATH];

    BROWSEINFO bi;
    memset(&bi, 0, sizeof(bi));

    bi.hwndOwner  = this->hwnd;
    bi.pidlRoot    = NULL;
    bi.pszDisplayName = fileName;
    bi.lpszTitle  =  (TCHAR*)(this->title);  //
    bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_SHAREABLE|\
      BIF_USENEWUI|BIF_BROWSEFORCOMPUTER|BIF_VALIDATE;

    bi.lpfn   = BrowseForFolderCallback;       
    bi.lParam = (LPARAM)startingDir;  
    
    // Display Folder Selection Dialog and wait a user's selection.
    LPITEMIDLIST  itemIdList = SHBrowseForFolder(&bi);
    if (itemIdList != NULL) {
        TCHAR* buffer = (TCHAR*)lpMalloc->Alloc(_MAX_PATH);
        if (buffer != NULL) {

          // Convert itemIdlist to fullPath buffer
          // 2015/07/15 Added (PCIDLIST_ABSOLUTE) 
          if (SHGetPathFromIDList((PCIDLIST_ABSOLUTE)itemIdList, buffer)) {
            selectedFullPath = buffer;
            selectedFolder   = buffer;
            rc = TRUE;
            profile.setFolderBrowserFolder(buffer);
          }
        }
        lpMalloc->Free(buffer);
        lpMalloc->Free(itemIdList);
    } 

    lpMalloc->Release();
    return rc;
  }

  BOOL show(String& selectedFullPath)
  {
    BOOL    rc = FALSE;
    TCHAR folder[MAX_PATH] = {0};;
    profile.getFolderBrowserFolder(folder, CountOf(folder));
    const TCHAR* startingDir = nullptr;
    if (strlen(folder)>0) {  
       startingDir = (const TCHAR*)folder;
    } else  if (startingDir == nullptr || strlen(startingDir) == 0) {
      startingDir = _T("C:\\");
    }
    
    LPMALLOC  lpMalloc = NULL;

    if (FAILED(SHGetMalloc(&lpMalloc))) {
      return rc;
    }

    TCHAR fileName[_MAX_PATH];

    BROWSEINFO bi;
    memset(&bi, 0, sizeof(bi));

    bi.hwndOwner  = this->hwnd;
    bi.pidlRoot    = NULL;
    bi.pszDisplayName = fileName;
    bi.lpszTitle  =  (TCHAR*)(this->title);  //
    bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_SHAREABLE|\
      BIF_USENEWUI|BIF_BROWSEFORCOMPUTER|BIF_VALIDATE;

    bi.lpfn   = BrowseForFolderCallback;       
    bi.lParam = (LPARAM)startingDir;  
    
    // Display Folder Selection Dialog and wait a user's selection.
    LPITEMIDLIST  itemIdList = SHBrowseForFolder(&bi);
    if (itemIdList != NULL) {
      TCHAR* buffer = (TCHAR*)lpMalloc->Alloc(_MAX_PATH);
      if (buffer != NULL) {
        // Convert itemIdlist to fullPath buffer
        // 2015/07/15 Added (PCIDLIST_ABSOLUTE) 
        if (SHGetPathFromIDList((PCIDLIST_ABSOLUTE)itemIdList, buffer)) {
          selectedFullPath = buffer;
          selectedFolder   = buffer;
            
          rc = TRUE;
          profile.setFolderBrowserFolder(buffer);
        }
      }
      lpMalloc->Free(buffer);
      lpMalloc->Free(itemIdList);
    } 

    lpMalloc->Release();
    return rc;
  }

private:
  /**
  */
  static  int CALLBACK BrowseForFolderCallback(HWND hWnd, UINT uMsg, 
      LPARAM lParam, LPARAM lpData)
  {
    if (uMsg == BFFM_INITIALIZED) {
      if (lpData !=NULL) {
        //lpData = bi.lParam = startingDir
        SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
      }
    }
    return 0;
  }

};

}





