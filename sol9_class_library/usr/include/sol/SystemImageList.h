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
 *  SystemImageList.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.06.26
#pragma once

#include <sol\ImageList.h>

namespace SOL {

class SystemImageList :public ImageList {
private:
  UINT flag;

public:
  SystemImageList(UINT flag1 = (SHGFI_SYSICONINDEX|SHGFI_SMALLICON))
  :ImageList(),
  flag(flag1)
  {  
    TCHAR dir[MAX_PATH];
    ::GetWindowsDirectory(dir, CountOf(dir)); //2012/06/21
  
    SHFILEINFO sfi;
    memset(&sfi, 0, sizeof(sfi));

    HIMAGELIST himl = (HIMAGELIST)::SHGetFileInfo (dir, 0, &sfi, 
              sizeof(sfi), flag); 
    setImageList(himl);  

  }

public:
  ~SystemImageList() 
  { 
    detachImageList(); 
  }

public:
  int  getIconIndex (const TCHAR* fileName, DWORD attr, UINT nflag=0) 
  {
    SHFILEINFO   sfi;
    memset(&sfi, 0, sizeof(sfi));  
    ::SHGetFileInfo(fileName, attr, &sfi, sizeof(sfi), 
        (flag | SHGFI_USEFILEATTRIBUTES|nflag));
    return sfi.iIcon;
  }

public:
  int  getDirectoryIndex (const TCHAR* dir) 
  {
    return getIconIndex(dir, FILE_ATTRIBUTE_DIRECTORY);
  }

public:
  int  getOpenDirectoryIndex (const TCHAR* dir) 
  {
    return getIconIndex(dir, FILE_ATTRIBUTE_DIRECTORY, SHGFI_OPENICON);
  }

public:
  int  getNormalFileIndex (const TCHAR* dir) 
  {
    return getIconIndex(dir, FILE_ATTRIBUTE_NORMAL);
  }


};

}

