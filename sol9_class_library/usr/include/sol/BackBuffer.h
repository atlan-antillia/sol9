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
 *  BackBuffer.h
 *
 *****************************************************************************/

#pragma once

#include <sol/View.h>
#include <sol/SmartPtrs.h>
#include <sol/ClientDC.h>

namespace SOL {
  
class BackBuffer :public Object {
private:  
  ClientDC  cdc;

  int     bufferWidth;  
  int     bufferHeight;
  
  HGDIOBJ hBackBitmap;
  HGDIOBJ hPrevBitmap;

  HDC     hBackMemoryDC;
  
public:
  BackBuffer(View* view)
  :Object(),
  cdc(view),
  bufferWidth(0),
  bufferHeight(0),
  hBackBitmap(nullptr),
  hPrevBitmap(nullptr),
  hBackMemoryDC(nullptr)
  {
  }
  
  void create(int width, int height)
  {
    bufferWidth  = width;
    bufferHeight = height;
    hBackBitmap = cdc.createCompatibleBitmap(bufferWidth, bufferHeight);
    if (hBackBitmap == nullptr) {
      throw IException("Failed to createCompatibleBitmap: bufferWidth=%d  bufferHeight=%d",
              bufferWidth, bufferHeight);
    }
    
    hBackMemoryDC   = cdc.createCompatibleDC();
    if (hBackMemoryDC == nullptr) {
      throw IException("Failed to createCompatibleDC.");
    }
    hPrevBitmap = SelectObject(hBackMemoryDC, hBackBitmap); 
    
  }

  ~BackBuffer()
  {
    SelectObject(hBackMemoryDC, hPrevBitmap);
    DeleteObject(hBackBitmap);
    DeleteDC(hBackMemoryDC);
  }
  

  int getBufferWidth()
  {
    return bufferWidth;
  }

  int getBufferHeight()
  {
    return bufferHeight;
  }

  HDC getBackMemoryDC()
  {
    return hBackMemoryDC;
  }
  
  virtual void resize(int w, int h)
  {    
   // Define your own method in the subclass derived from this class
    
  }
    
  //Draw an image on hBackMemory to hDcDest
  //2017/03/20  
  void bitBlt(HDC hDestDC, float destX, float destY, float destWidth, float destHeight,
        DWORD dwRop=SRCCOPY)
  {
    if (hBackMemoryDC) {
      SetStretchBltMode(hDestDC, COLORONCOLOR);
      
      ::StretchBlt(hDestDC, (int)destX, (int)destY, (int)destWidth, (int)destHeight,
        hBackMemoryDC, 
        0, 0, bufferWidth, bufferHeight, dwRop);
    }
  }
/*
  void strechBlt(HDC hDestDC, float destX, float destY, float destWidth, float destHeight,
        DWORD dwRop=SRCCOPY)
  {
    if (hBackMemoryDC) {
      SetStretchBltMode(hDestDC, COLORONCOLOR);
      
      ::StretchBlt(hDestDC, (int)destX, (int)destY, (int)destWidth, (int)destHeight,
        hBackMemoryDC, 
        0, 0, bufferWidth, bufferHeight, dwRop);
    }
  }
*/
  void draw(OpenCVGC& gc)
  {
    if ( hBackMemoryDC == nullptr ) {
      return;
    }
    
    HWND hwnd = gc.getWindow(); 

    RECT r;
    GetClientRect(hwnd, &r);
    //destination size.
    float dw = float(r.right  - r.left);
    float dh = float(r.bottom - r.top);
    
    //source size
    float sw = float(bufferWidth );
    float sh = float(bufferHeight);
      
    float tw = sw;  
    float th = sh;
    float dx = 0.0;
    float dy = 0.0;
        
    bool keepAspectRatio = gc.keepAspectRatio();
    //bool fitWindowSize   = gc.fitWindowSize();
    
    if ( !keepAspectRatio ) {
      bitBlt(gc.get(),
				    0.0, 0.0, dw, dh, 
				    //0.0, 0.0, sw, sh, 
				    //bmpData, &bmpInfo, DIB_RGB_COLORS, 
            SRCCOPY);
    } else {
      //sh should not be zero.
      //Keep the aspect ratio of the bitmap.
      if (dw >= sw && dh >= sh) {
        dx = (dw - tw)/2.0;
        dy = (dh - th)/2.0;
      } else if (dw <= sw && dh >= sh) {
        float rw = dw/sw;
        tw = sw * rw;
        th = sh * rw;
      } else if (dw <= sw && dh <= sh) {
        float rw = dw/sw;
        float rh = dh/sh;
        if (rw >= rh) {
          tw = sw * rw;
          th = sh * rw;
        } else {
          tw = sw * rh;
          th = sh * rh;
        }
      } else if (dw >= sw && dh <= sh) {
        float rh = dh / sh;
        tw = sw * rh;
        th = sh * rh;
      }
      dx = (dw - tw)/2.0;
      dy = (dh - th)/2.0;
      
      /*gc.stretchDIBits( 
				    dx, dy, tw, th, 
				    0.0, 0.0, sw, sh, 
				    bmpData, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);     
      */
      bitBlt(gc.get(), 
				    dx, dy, tw, th, 
				    SRCCOPY);
  
    }
  }    
  

};

}
