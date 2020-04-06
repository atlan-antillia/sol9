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
 *  IconedDirTree.h
 *
 *****************************************************************************/


// SOL++2000 
// 2000.07.01
// 2012/06/23
// 2015/12/12

#pragma once

#include <sol\TreeView.h>

#include <sol\SystemImageList.h>
#include <sol\FileFinder.h>
#include <sol/FileInfo.h>
#include <sol/StringBufferT.h>

namespace SOL {

class IconedDirTree :public TreeView {
private:
  SystemImageList  imageList;

public:
  IconedDirTree(): TreeView() { }

public:
  /**
   * Constructor
   */
  //2012/06/23
  IconedDirTree(View* parent, const TCHAR* name, Args& args)
  :TreeView()
  {
    create(parent, name, args);
  }

public:
  ~IconedDirTree()
  {
    setImageList((HIMAGELIST)NULL, TVSIL_NORMAL);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = TreeView::create(parent, name, args);
    setImageList(&imageList, TVSIL_NORMAL);
    return rc;
  }

public:
  HTREEITEM addItemWithIcon(HTREEITEM parent, HTREEITEM item, TCHAR* path)
  {
    int id1 = imageList.getDirectoryIndex(path); 
    int id2 = imageList.getOpenDirectoryIndex(path);
    //FileInfo fileInfo;
    //String type = _T("");
    //fileInfo.getFileType(name, type);
    return addItem(parent, item, path, id1, id2);
  }

public:
  void findDirectories(HTREEITEM parent, const TCHAR* dir,
          int level, int max)
  {
    if(level < max) {
      WIN32_FIND_DATA  data;

      HTREEITEM item = (HTREEITEM)TVI_FIRST;

      TCHAR* buffer = new TCHAR[_MAX_PATH];
      _stprintf_s(buffer, _MAX_PATH, _T("%s\\*"), dir);
      FileFinder fileFinder(buffer);

      if (fileFinder.getFirst(&data)) {
        do {
          if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(_T("."), data.cFileName) != 0 && 
              strcmp(_T(".."), data.cFileName) != 0) {

              int id1 = imageList.getDirectoryIndex(data.cFileName); 
              int id2 = imageList.getOpenDirectoryIndex(data.cFileName);


              item = addItem(parent, item, data.cFileName, id1, id2);
              TCHAR* subDir = new TCHAR[_MAX_PATH];
              _stprintf_s(subDir, _MAX_PATH, _T("%s\\%s"), dir, data.cFileName);

              // Go to next level of trees.
              findDirectories(item, subDir, (level+1), max);
              delete [] subDir;
            }
          }
        } while (fileFinder.getNext(&data)); 
      }
      delete [] buffer;
    }
  }

public:
// Delete all children and siblings
  void deleteChildren(HTREEITEM htreeItem)
  {
    HTREEITEM child = getChild(htreeItem);
    while(child) {
      HTREEITEM sibling = getNextSibling(child);
      deleteItem(child);
      child = sibling;
    }
  }

public:
// Get fullpathname
  //2015/12/12
  void getHierachy(HTREEITEM selItem, StringBufferT<TCHAR>& buff, TCHAR* delim)
  {
    TV_ITEM hitem;

    HTREEITEM parent = getParent(selItem);
    if(parent) {
      //
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

public:
  HIMAGELIST  detachImageList() {
    return setImageList((HIMAGELIST)NULL, LVSIL_SMALL);
  }
};

}


