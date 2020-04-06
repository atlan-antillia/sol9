/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileInfo.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/05

#pragma once

#include <sol\String.h>

namespace SOL {

/**
 * FileInfo class
 */
class FileInfo :public Object {
private:
  SHFILEINFO fileInfo;

public:
  FileInfo()  {
    memset(&fileInfo, 0, sizeof(fileInfo));

  }


public:
  int getFileType(const TCHAR* filePath, String& string)
  {
    int rc = 0;
    memset(&fileInfo, 0, sizeof(fileInfo));

    if (filePath) {
    
      int rc = SHGetFileInfo(filePath, 0, &fileInfo, sizeof(SHFILEINFO),
                SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);
      if (rc) {
        string = fileInfo.szTypeName;
      }
    }
    return rc;
  }

public:
  int getIconIndex(const TCHAR* fileName)
  {
    int id = -1;
    memset(&fileInfo, 0, sizeof(fileInfo));
    if (fileName) {
      int rc = (int)SHGetFileInfo(fileName,0,&fileInfo,sizeof(SHFILEINFO),
        SHGFI_ICON | SHGFI_SMALLICON);
      if (rc) {
        //non zero success
        id = fileInfo.iIcon;  
        DestroyIcon(fileInfo.hIcon);
      }
    }
    return id;
  }

public:
  int getSmallIconIndex(const TCHAR* fileName)
  {
    int id = -1;
    memset(&fileInfo, 0, sizeof(fileInfo));
    if (fileName) {
      int rc = (int)SHGetFileInfo(fileName,0,&fileInfo,sizeof(SHFILEINFO),
        SHGFI_ICON | SHGFI_SMALLICON);
      if (rc) {
        //non zero success
        id = fileInfo.iIcon;  
        DestroyIcon(fileInfo.hIcon);
      }
    }
    return id;
  }

public:
  int getLargeIconIndex(const TCHAR* fileName)
  {
    int id = -1;
    memset(&fileInfo, 0, sizeof(fileInfo));
    if (fileName) {
      int rc = (int)SHGetFileInfo(fileName,0,&fileInfo,sizeof(SHFILEINFO),
        SHGFI_ICON | SHGFI_LARGEICON);
      if (rc) {
        //non zero success
        id = fileInfo.iIcon;  
        DestroyIcon(fileInfo.hIcon);
      }
    }
    return id;
  }


public:
  //Get a small icon from a file of fileName.
  HICON getSmallIcon(const TCHAR* fileName)
  {
    HICON hIcon= NULL;
    memset(&fileInfo, 0, sizeof(fileInfo));
    if (fileName) {
      int rc = (int)SHGetFileInfo(fileName,0,&fileInfo,sizeof(SHFILEINFO),
        SHGFI_ICON | SHGFI_SMALLICON);
      if (rc) {
        hIcon = fileInfo.hIcon;
      }
    }
    return hIcon;
  }

public:
  //Get a large icon from a file of fileName.
  HICON getLargeIcon(const TCHAR* fileName)
  {
    HICON hIcon= NULL;
    memset(&fileInfo, 0, sizeof(fileInfo));
    if (fileName) {
      int rc = (int)SHGetFileInfo(fileName,0,&fileInfo,sizeof(SHFILEINFO),
        SHGFI_ICON | SHGFI_LARGEICON);
      if (rc) {
        hIcon = fileInfo.hIcon;
      }
    }
    return hIcon;
  }
};


}
