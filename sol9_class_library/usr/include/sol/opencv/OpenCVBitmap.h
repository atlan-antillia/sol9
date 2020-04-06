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
 *  OpenCVBitmap.h
 *
 *****************************************************************************/

#pragma once

#include <sol/View.h>
#include <sol/SmartPtrs.h>

#include <sol/opencv/OpenCVObject.h>

namespace SOL {
  
class OpenCVBitmap :public OpenCVObject {
protected:
  BITMAPINFO          bmpInfo;
  SmartPtrs<uint32_t> bmpData;
  
public:
  OpenCVBitmap()
  :OpenCVObject(),
  bmpData(NULL)
  {
    memset(&bmpInfo, 0, sizeof(bmpInfo));
  }

  ~OpenCVBitmap()
  {
  }
  
  virtual void reload()
  {
  }
  
  virtual void resize(float ratio)
  {
   // Define your own method in the subclass derived from this class
    
  }
  
  int getWidth()
  {
    return bmpInfo.bmiHeader.biWidth;
  }
  
  int getHeight()
  {
    return bmpInfo.bmiHeader.biHeight;
  }
  
  void set(BITMAPINFO info, uint32_t* data)
  {
    bmpInfo = info;
    //bmpData = NULL;
    bmpData = data;
  }

  virtual void update()
  {
    
  }
  
  virtual cv::Mat& getMat()
  {
    throw IException("No cv::Mat image data.");
  }
  
  virtual void convertToBitmap()
  {
  }
  
  //void draw(PaintDC &pdc, float dx, float dy, float dw, float dh,
  //                        float sx, float sy, float sw, float sh)
	
  void draw(DC& pdc, float dx, float dy, float dw, float dh,
                          float sx, float sy, float sw, float sh)
  {
    pdc.stretchDIBits( 
				    dx, dy, dw, dh, 
				    sx, sy, sw, sh, 
				    bmpData, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);
  }
  
 /* void draw(OpenCVGC* gc) 
  {
    if ( gc == nullptr || bmpData == nullptr ) {
      return;
    }
    
    HWND hwnd = gc->getWindow(); 

    RECT r;
    GetClientRect(hwnd, &r);
    //destination size.
    float dw = float(r.right  - r.left);
    float dh = float(r.bottom - r.top);
    
    //source size
    float sw = float(bmpInfo.bmiHeader.biWidth );
    float sh = float(bmpInfo.bmiHeader.biHeight);
      
    float tw = sw;  
    float th = sh;
    float dx = 0.0;
    float dy = 0.0;
        
    bool keepAspectRatio = gc->keepAspectRatio();
    bool fitWindowSize   = gc->fitWindowSize();
      gc->stretchDIBits( 
				    0.0, 0.0, sw, sh, 
				    0.0, 0.0, sw, sh, 
				    bmpData, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);
    return;    
    if ( !keepAspectRatio ) {
      gc->stretchDIBits( 
				    0.0, 0.0, dw, dh, 
				    0.0, 0.0, sw, sh, 
				    bmpData, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);
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
      
      gc->stretchDIBits( 
				    dx, dy, tw, th, 
				    0.0, 0.0, sw, sh, 
				    bmpData, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);     
    }
   
  }
  */
};

}

