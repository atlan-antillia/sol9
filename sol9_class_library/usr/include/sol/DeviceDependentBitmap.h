/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DeviceDependentBitmap.h
 *
 *****************************************************************************/

#pragma once

#include <sol/View.h>
#include <sol/SmartPtrs.h>
#include <sol/ClientDC.h>

namespace SOL {
  
class DeviceDependentBitmap :public Object {
private:  
  int     bitmapWidth;  
  int     bitmapHeight;
  
  HBITMAP hDDBitmap;
  HBITMP  hPrevDDBitmap;

  HDC     hDDBMemoryDC;
  
public:
  DeviceDependentBitmap(View* view, const BITMAPINFOHEADER* bmiHeader,
              DWORD             bmInit,             //CBM_INIT    
              const void*       bmpData,           
              const BITMAPINFO* bmi,       
              UINT              usage) //DIB_RGB_COLORS
  :Object(),
  bitmapWidth(width),
  bitmapHeight(height),
  hDDBitmap(nullptr),
  hPrevdDDBitmap(nullptr),
  hDDBMemoryDC(nullptr)
  {
    if (view == nullptr) {
      throw IException("Invalid parameter: view is nullptr");
    }
    if (bmiHeader == nullptr || bmi == nullptr) {
      throw IException("Invalid parameter: BITMAPINFOHEADER or BITMAPINFO is nullptr");
    }
    
    ClientDC cdc(view);
    
    bitmapWidth  = bmiHeader->bmi.width;
    bitmapHeight = bmiHeader->bmi.height;
    
    hDDBitmap = cdc.createDIBitmap(bmiHeader, bmInit, bmpData, bmi, usage);	
 
    
    if (hDDBitmap== nullptr) {
      throw IException("Failed to createDIBitmap");
    }
    hDDBMemoryDC = cdc.createCompatibleDC();
    
    if (hDDBMemoryDC == nullptr) {
      throw IException("Failed to createCompatibleDC.");
    }
    hPrevDDBitmap = SelectObject(hDDBMemoryDC, hDDBitmap); 
  }

  ~DeviceDependentBitmap()
  {
    SelectObject(hDDBMemoryDC, hPrevDDBitmap);
    DeleteObject(hDDBitmap);
    DelectDC(hDDBMemoryDC);
  }
  

  virtual void resize(int w, int h)
  {    
   // Define your own method in the subclass derived from this class
    
  }
  
  HDC getDDBMemoryDC()
  {
    return hDDBMemoryDC;
  }
  
  void bitBlt(HDC& hDcDest, int destX, int destY, int destWidth, int destHeight)
  {
    if (view) {
      if (hDDBMemoryDC ) {
        BitBlt(hdc, destX, destY, destWidth, destHeight, hDDBMemoryDC, 0, 0, SRCCOPY);
      }
    }
  }
  
    
};

}
