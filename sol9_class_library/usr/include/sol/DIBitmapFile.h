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
 *  DIBitmapFile.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\BitmapFile.h>

#include <sol\DIBitmap.h>


typedef HANDLE HDIB;

namespace SOL {

#define MAX 32000

class DIBitmapFile :public BitmapFile {
public:
  
  DIBitmapFile() { }

public:
  ~DIBitmapFile() { }

public:

  DIBitmap* extract()
  {
    char* buffer = new char[MAX]; 
    read(0L, buffer, MAX);
    if(strncmp(buffer, "BM", 2) != 0) return NULL;

    DWORD size  = fileLength() - sizeof(BITMAPFILEHEADER);

    int  n = sizeof(BITMAPFILEHEADER);

    BITMAPINFOHEADER* bi = (BITMAPINFOHEADER*)&buffer[n];
    int colorCount = getColorCount(bi);
    
    if (bi->biSize == sizeof(BITMAPCOREHEADER)){
      ::MessageBox(NULL, _T("This version does not support this type of format."), 
        _T("class DIBitmapFile"), MB_OK);
      delete [] buffer;
      return NULL;
    }

    HDIB hdib = (HDIB)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
    if (hdib == 0) {
      delete [] buffer;
      return NULL;
    }

    char* bits = (char*)::GlobalLock(hdib);
    char* ptr  = bits;
    unsigned long offset = sizeof(BITMAPFILEHEADER);

    while(size > MAX) {
      read(offset, ptr, MAX);
      ptr    += MAX;
      offset += MAX;
      size   -= MAX;
    }
    read(offset, ptr, (WORD)size);

    ::GlobalUnlock(hdib);

    delete [] buffer;
    DIBitmap* dibitmap = new DIBitmap(_T(""), hdib, 
      bi->biWidth, bi->biHeight, colorCount);
    return dibitmap;
  }


};

}


