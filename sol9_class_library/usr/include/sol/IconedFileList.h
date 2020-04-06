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
 *  IconedFileList.h
 *
 *****************************************************************************/


// SOL++2000
// 2000.07.01
// 2012/06/23
// 2012/07/24

#pragma once

#include <sol\ListView.h>

#include <sol\SystemImageList.h>
#include <sol\FileFinder.h>
#include <sol/FileInfo.h>

namespace SOL {

class IconedFileList :public ListView {
private:
  SystemImageList  imglist;

private:
  TCHAR  currentDir[1024];

private:
  bool  scanning;

private:
  virtual void addColumn() 
  {
    ListViewColumn items[] = {
      {_T("FileName"),  LVCFMT_LEFT, 260},
      {_T("Type"),      LVCFMT_LEFT, 120},
      {_T("Size(KB)"),   LVCFMT_RIGHT,   100},
      {_T("DateTime"),    LVCFMT_LEFT, 150},
    };
    setColumn(items, CountOf(items));
  }

public:
  /**
   * Constructor
   */
  IconedFileList()
    :ListView()
  { 
    memset(currentDir, (TCHAR)0, CountOf(currentDir));
  }

public:
  /**
   * Constructor
   */
  //2012/06/23
  IconedFileList(View* parent, const TCHAR* name, Args& args)
  :ListView() 
  { 
    create(parent, name, args);
  }

public:
  ~IconedFileList()
  {  
    setImageList((HIMAGELIST)NULL, LVSIL_SMALL);
    setImageList((HIMAGELIST)NULL, LVSIL_NORMAL);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args) 
  {
    Boolean rc = ListView::create(parent, name, args);

    memset(currentDir, (TCHAR)0, CountOf(currentDir)); //2012/06/23

    setImageList(&imglist, LVSIL_SMALL);
    setImageList(&imglist, LVSIL_NORMAL);

    addColumn();

    return rc;
  }

public:
  void findFiles(const TCHAR* dir)
  {
    if (dir == NULL) {
      return;
    }

    strcpy_s(currentDir, CountOf(currentDir), dir);

    setRedraw(FALSE);

    clear();

    // Note: typedef WIN32_FIND_DATA FindData;
    WIN32_FIND_DATA  data;

    TCHAR buffer[_MAX_PATH];
    _stprintf_s(buffer, CountOf(buffer), _T("%s\\*"), dir);
    TCHAR fullPath[1024];

    // Create an instance of FileFinder.
    FileFinder fileFinder(buffer);
  
    if (fileFinder.getFirst(&data)) {
      do {
        TCHAR size[80];
        TCHAR date[128];
        //2009/11/06
        if (String::endsWith(dir, _T("\\"))) {
          _stprintf_s(fullPath, CountOf(fullPath), _T("%s%s"), 
            dir, data.cFileName);
        } else {
          _stprintf_s(fullPath, CountOf(fullPath), _T("%s\\%s"), 
            dir, data.cFileName);
        }

        String type = "";
        FileInfo fileInfo;

        fileInfo.getFileType(fullPath, type);

        size[0] = ZERO;
        date[0] = ZERO;

        // Get a file time from ftLastWriteTime field of FindData structure.
        SYSTEMTIME time;
        FILETIME   ltime;
        ::FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ltime);
        ::FileTimeToSystemTime(&ltime, &time);

        _stprintf_s(date, CountOf(date), _T("%.4u/%.2u/%.2u  %.2u:%.2u:%.2u"), 
          time.wYear, time.wMonth, time.wDay,
          time.wHour, time.wMinute, time.wSecond);

        LV_ITEM item;
        memset(&item, 0, sizeof(LV_ITEM));

        DWORD attr = 0;
        int  iconId = 0;

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          iconId = imglist.getDirectoryIndex(data.cFileName);
        } else {
          iconId = imglist.getNormalFileIndex(data.cFileName);
          int kb = (data.nFileSizeLow/1024);
          int remain = (data.nFileSizeLow%1024);
          if (remain>0) {
            kb++;
          }
          _stprintf_s(size, CountOf(size), _T("%lu"), kb);
        }

        if (strcmp(_T("."), data.cFileName) != 0 &&
          strcmp(_T(".."), data.cFileName) != 0) {
          // Insert an item having an iconIndex and a filename into this listView.
          item.mask       = LVIF_TEXT|LVIF_IMAGE;
          item.iImage      = iconId;
          item.pszText    = data.cFileName;
          item.cchTextMax = _MAX_PATH;
          int m = insertItem(&item);

          int n = 1;
          // Set type, size, filedatetime to the line of index m.
          setItemText(m, n++, (const TCHAR*)type);

          setItemText(m, n++, size);
          setItemText(m, n++, date);
        }

      } while(fileFinder.getNext(&data)); 
    }

    setRedraw(TRUE);
  }

private:
  void dispatchMessage()
  {
    MSG msg;
    
    while(
      PeekMessage (&msg,NULL,0,0,PM_REMOVE)) {
      SleepEx(10, TRUE); //2012/07/24
      if (msg.message == WM_QUIT) {
        scanning = false;
        //Repost WM_QUIT message to your application message queue.
        PostMessage(NULL, WM_QUIT, 0, 0);
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

public:
  //2009/11/06
  void findAllFiles(const TCHAR* dir, const TCHAR* ext)
  {
    if (dir == NULL) {
      return;
    }

    strcpy_s(currentDir, CountOf(currentDir), dir);

    setRedraw(FALSE);

    clear();
    scanning = true;
    findAllFilesRecursively(dir, ext);
    scanning = false;

    setRedraw(TRUE);
  }

public:
  bool isScanning()
  {
    return scanning;
  }

public:
  void stopScanning()
  {
    scanning =false;
  }

private:
  //2009/11/06
  void findAllFilesRecursively(const TCHAR* dir, const TCHAR* ext)
  {
    if (scanning == false) {
      return;
    }

    // Note: typedef WIN32_FIND_DATA FindData;
    WIN32_FIND_DATA  data;

    TCHAR buffer[_MAX_PATH];
    _stprintf_s(buffer, CountOf(buffer), _T("%s\\*"), dir);
    TCHAR fullPath[1024];

    // Create an instance of FileFinder.
    FileFinder fileFinder(buffer);
        
    View* parent = getParent();
    if (parent) {
      TCHAR message[MAX_PATH*2];
      _stprintf_s(message, CountOf(message), _T("Scanning the folder: %s"), dir);
      parent->setText(message);
    }


    if (fileFinder.getFirst(&data)) {
      do {

        dispatchMessage();
        if (scanning == false) {
          break;
        }
        TCHAR size[80];
        TCHAR date[128];
        //2009/11/06
        if (String::endsWith(dir, _T("\\"))) {
          _stprintf_s(fullPath, CountOf(fullPath), _T("%s%s"), 
            dir, data.cFileName);
        } else {
          _stprintf_s(fullPath, CountOf(fullPath), _T("%s\\%s"), 
            dir, data.cFileName);
        }

        String type = "";
        FileInfo fileInfo;

        fileInfo.getFileType(fullPath, type);

        size[0] = ZERO;
        date[0] = ZERO;

        // Get a file time from ftLastWriteTime field of FindData structure.
        SYSTEMTIME time;
        FILETIME   ltime;
        ::FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ltime);
        ::FileTimeToSystemTime(&ltime, &time);

        _stprintf_s(date, CountOf(date), _T("%.4u/%.2u/%.2u  %.2u:%.2u:%.2u"), 
          time.wYear, time.wMonth, time.wDay,
          time.wHour, time.wMinute, time.wSecond);

        LV_ITEM item;
        memset(&item, 0, sizeof(LV_ITEM));

        DWORD attr = 0;
        int  iconId = 0;

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          iconId = imglist.getDirectoryIndex(fullPath);
        } else {
          iconId = imglist.getNormalFileIndex(fullPath);
          int kb = (data.nFileSizeLow/1024);
          int remain = (data.nFileSizeLow%1024);
          if (remain>0) {
            kb++;
          }
          _stprintf_s(size, CountOf(size), _T("%lu"), kb);
        }

        if (strcmp(_T("."), data.cFileName) != 0 &&
          strcmp(_T(".."), data.cFileName) != 0) {
          //If the file extension of data.cFileName were matched with ext, 
          if (String::endsWithIgnoreCase(data.cFileName, ext)) {
            // Insert an item having an iconIndex and a filename into this listView.
            item.mask       = LVIF_TEXT|LVIF_IMAGE;
            item.iImage      = iconId;
            item.pszText    = fullPath;
            item.cchTextMax = _MAX_PATH;
            int m = insertItem(&item);

            int n = 1;
            // Set type, size, filedatetime to the line of index m.
            setItemText(m, n++, (const TCHAR*)type);

            setItemText(m, n++, size);
            setItemText(m, n++, date);
          }

          if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            findAllFilesRecursively(fullPath, ext);
          }
        }
      } while(fileFinder.getNext(&data)); 
    }

    setRedraw(TRUE);
  }

//2012/07/24
public:
  void reshape(int x, int y, int w, int h)
  {
    View::reshape(x, y, w, h);
    int sx = GetSystemMetrics(SM_CXVSCROLL);

    int min = 260 + 120 + 100 + 150 + sx;
    if (w > min) {
      int nameWidth = w - (120 + 100 + 150 + sx);

      setColumnWidth(0, nameWidth);   
    }
  }

public:
  HIMAGELIST  detachImageList() 
  {
    setImageList((HIMAGELIST)NULL, LVSIL_SMALL);

    return setImageList((HIMAGELIST)NULL, LVSIL_NORMAL);
  }

public:
  bool getSelectedFilePath(__out String& fileName,__out String& filePath)
  {
    bool rc = false;

    int count = getItemCount();
        
    TCHAR name[1024];
    memset(name, (TCHAR)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEM item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        rc = true;
        break;
      }
    } //for
    if (rc) {
      TCHAR path[1024];
      _stprintf_s(path, CountOf(path), _T("%s\\%s"), currentDir, name);
      filePath = path;
      fileName = name;
    }
    return rc;
  }
  
public:
  bool getSelectedFileName(__out String& fileName)
  {
    bool rc = false;

    int count = getItemCount();
        
    TCHAR name[1024];
    memset(name, (TCHAR)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEM item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        rc = true;
        break;
      }
    } //for
    if (rc) {
      fileName = name;
    }
    return rc;
  }
  
public:
  const TCHAR* getCurrentDir() 
  {
    return currentDir;
  }

};

}
