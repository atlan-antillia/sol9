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
 *  BitmapFile.cpp
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\BinaryFile.h>
#include <sol\GlobalMemory.h>


namespace SOL {
#define MAX 32000

class BitmapFile :public BinaryFile {
  char*  bmi;


protected:
  int getColorCount(BITMAPINFOHEADER* bi)
  {
    if (bi->biClrUsed != 0) {
      return (int)bi->biClrUsed;
    }
    int bits = bi->biBitCount;

    switch (bits){
    case 1:
      return 2;
    case 4:
      return 16;
        case 8:
      return 256;
        default:
      break;
    }
    return 0;
  }


public:
  BitmapFile() {  bmi  = NULL; }

  ~BitmapFile() {  
    if(bmi) 
      delete [] bmi; 
  }


public:
  HBITMAP extract(HDC hdc)
  {
    char* buffer = new char[MAX];  
    BinaryFile::read(0L, buffer, MAX);
    if(strncmp(buffer, "BM", 2) != 0) return NULL;

    BITMAPFILEHEADER* fileHeader = (BITMAPFILEHEADER*)buffer;
    DWORD offset = fileHeader -> bfOffBits;
    DWORD size   = fileLength() - offset;

    int  n = sizeof(BITMAPFILEHEADER);
    BITMAPINFOHEADER* bi = (BITMAPINFOHEADER*)&buffer[n];

    int colorCount = getColorCount(bi);
    int infoSize   = sizeof(BITMAPINFOHEADER) +
       sizeof(RGBQUAD) * colorCount;

    bmi = new char[infoSize];
    for(int i = 0; i < infoSize; i++) {
      bmi[i] = buffer[n++];
    }
    BITMAPINFO* bitmapInfo = (BITMAPINFO*)bmi;

    HBITMAP hbitmap = NULL;

    GlobalMemory gmemory(size);

    char* bits = (char*) gmemory.getBuffer();
    char* ptr  = bits;

    while(size > MAX) {
      read(offset, ptr, MAX);
      ptr    += MAX;
      offset += MAX;
      size   -= MAX;
    }
    BinaryFile::read(offset, ptr, (WORD)size);
    hbitmap = ::CreateDIBitmap(hdc, 
       &(bitmapInfo->bmiHeader),
       CBM_INIT,  bits,
       bitmapInfo, DIB_RGB_COLORS);
  
    delete [] buffer;

    return hbitmap;
  }

};

}


