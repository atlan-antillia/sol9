/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FolderTreeView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22
// 2015/12/12

#pragma once

#include <sol\TreeView.h>

#include <sol\ImageList.h>

#include <sol\StringBufferT.h>

namespace SOL {

class FolderTreeView :public TreeView {
private:
  int    iconId;
  int    selIconId;
  ImageList* imageList;

private:

  HTREEITEM hasEntry(HTREEITEM child, const TCHAR* name)
  {
    HTREEITEM found = NULL;
    HTREEITEM item = child;
    while(item) {
      TV_ITEM hitem;

      TCHAR text[_MAX_PATH];
      hitem.mask       = TVIF_TEXT|TVIF_HANDLE;
      hitem.hItem      = item;
      hitem.pszText    = text;
      hitem.cchTextMax = _MAX_PATH;
      getItem(&hitem);
  
      if(strcmp(text, name) == 0) {
        found = item;
        break;
      }
      item = getNextSibling(item);
    }
    return found;
  }

public:    
  FolderTreeView():TreeView() { }


public:
  //2012/06/22
  FolderTreeView(View* parent, const TCHAR* name, Args& args)
  :TreeView()
  {
    create(parent, name, args);
  }

public:
  ~FolderTreeView()
  {
    delete imageList; 
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = TreeView::create(parent, name,
      args.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE)
        .set(XmNstyle, (LONG_PTR)TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT) );

    imageList = NULL;
    HINSTANCE hInst = getInstanceHandle();

    imageList = new ImageList(16, 16, ILC_COLOR24, 2,1);

    TCHAR dir[_MAX_PATH];
    ::GetWindowsDirectory(dir, CountOf(dir)); //2012/06/21
    SHFILEINFO shfi;
    ::SHGetFileInfo(dir, FILE_ATTRIBUTE_DIRECTORY,
      &shfi, sizeof(shfi), SHGFI_ICON|SHGFI_SMALLICON);

    imageList -> setBkColor(::GetSysColor(COLOR_WINDOW));
    iconId   = imageList -> addIcon(shfi.hIcon);

    ::SHGetFileInfo(dir, FILE_ATTRIBUTE_DIRECTORY,
      &shfi, sizeof(shfi), 
      SHGFI_ICON|SHGFI_OPENICON|SHGFI_SMALLICON);
    selIconId = imageList -> addIcon(shfi.hIcon); 

    setImageList(imageList, 0);

    return rc;
  }

public:
  void buildDirTree()
  {
    TCHAR dir[_MAX_PATH];
    ::GetWindowsDirectory(dir, CountOf(dir)); //2012/06/21

    TCHAR path[10];
    DWORD d = ::GetLogicalDrives();

    HTREEITEM item = NULL;
    for(int i = 0; i<26; i++) {
      if(d & 1) {
        //wsprintf(path, "%c:", 'A'+i);
        _stprintf_s(path, CountOf(path), _T("%c:"), 'A' + 1);

        item = addItem(NULL, TVI_LAST, path);
        findDirectories(item, dir, 0, 2);
        sortChildren(item, TRUE);
        if(path[0] == dir[0]) {
          expand(item, TVE_EXPAND);
        }
      }
      d = d >> 1;
    }
  }


public:
  void findDirectories(HTREEITEM parent, const TCHAR* dir,
          int level, int max)
  {
    if(level < max) {
      WIN32_FIND_DATA data;
      HTREEITEM item = (HTREEITEM)TVI_FIRST;

      TCHAR* buffer = new TCHAR[_MAX_PATH];
      _stprintf_s(buffer, _MAX_PATH, _T("%s\\*"), dir);
    
      HANDLE fFile= ::FindFirstFile(buffer, &data);

      HTREEITEM child = getChild(parent);

      if(fFile != INVALID_HANDLE_VALUE) {
        do {
          if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(_T("."), data.cFileName) != 0 && 
              strcmp(_T(".."), data.cFileName) != 0) {

              item = hasEntry(child, data.cFileName);

            // 
              if(item == NULL) {
                item = addItem(parent, item, 
                    data.cFileName,
                    iconId, selIconId);
              }
              TCHAR* subDir = new TCHAR[_MAX_PATH];
              _stprintf_s(subDir, _MAX_PATH, _T("%s\\%s"), dir, data.cFileName);
        
              findDirectories(item, (const TCHAR*)subDir,
                level+1, max);
              delete [] subDir;
            }
          }
        } while(FindNextFile(fFile, &data)); 
        ::FindClose(fFile);
      }
      delete [] buffer;
    }
  }

public:
  // 2015/12/12 Modified to use StringBufferT class.
  void getHierachy(HTREEITEM selItem, StringBufferT<TCHAR>& buff, TCHAR* delim)
  {
    TV_ITEM hitem;

    HTREEITEM parent = getParent(selItem);
    if(parent) {
      // parent node
      getHierachy(parent, buff, delim);
      TCHAR* text       = new TCHAR[_MAX_PATH];
      hitem.mask       = TVIF_TEXT|TVIF_HANDLE;
      hitem.hItem      = selItem;
      hitem.pszText    = text;
      hitem.cchTextMax = _MAX_PATH;
      getItem(&hitem);
      buff.append(delim);
      buff.append(text);
      delete [] text;
    }
    else {
      TCHAR* text       = new TCHAR[_MAX_PATH];
      hitem.mask       = TVIF_TEXT|TVIF_HANDLE;
      hitem.hItem      = selItem;
      hitem.pszText    = text;
      hitem.cchTextMax = _MAX_PATH;
      getItem(&hitem);
      buff.append(text);
      delete [] text;
    }
  }

};

}



