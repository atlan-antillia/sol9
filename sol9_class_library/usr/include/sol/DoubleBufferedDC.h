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
 *  DoubleBufferedDC.h
 *
 *****************************************************************************/

#pragma once

#include <sol/View.h>
#include <sol/SmartPtrs.h>
#include <sol/ClientDC.h>
#include <sol/BackMemoryBitmap.h>
#include <sol/DeviceDependentBitmap.h>


namespace SOL {
  
class DoubleBufferedDC :public ClientDC {
private:  
  SmartPtr<BackMemoryBitmap>      backMemoryBitmap;
  
public:
  DoubleBufferedDC(View* view = nullptr)
  :ClientDC(view)
  {
  }
  
  
  void write( const BITMAPINFOHEADER* bmiHeader,
              const void*       bmpData,           
              const BITMAPINFO* bmi,
              DWORD             bmInit = CBM_INIT,
              UINT              usage  = SRCCOPY)
  {
    if (bmiHeader == nullptr || bmpData == nullptr || bmi == nullptr) {
      throw IException("Invalid parameter.");
    }
    
    HDC hdc = getDC();
    int bmpWidth  = bi.bmiHeader.biWidth;
    int bmpHeight = bi.bmiHeader.biHeight; 

    backMemoryBitmap = new BackMemoryBitmap(view, bmpWidth, bmpHeight);

    //1 Create a device-dependent bitmap.    
    DeviceDependentBitmap deviceDependentBitmap( hdc, //view,
                                bmiHeader, bmInit, bmpData, bmi, usage );
    
    
    HDC hBackMemoryDC = backMemoryBitmp.getMemoryDC();
    HDC hDDBMemoryeDC = deviceIndepentBitmap.getMemoryDC();

    //2 Copy the device dpendent bitmap to the back memory bitmap. 
    ::BitBlt(hBackMemoryDC, 0, 0, bmpWidth, bmpHeight,
               hDDBMemoryDC, 0, 0, usage );
  }

  ~DoubleBufferedDC()
  {
  }
  
 
  virtual void resize(int w, int h)
  {    
   // Define your own method in the subclass derived from this class
  }
  

  void bitBlt(int destX, int destY, int destWidth, int destHeight)
  {
    HDC hBackMemoryDC = backMemoryBitmp.getMemoryDC();

    if ( hBackMemoryDC ) {
      DC::bitBlt(destX, destY, destWidth, destHeight, hBackMemoryDc, 0, 0, SRCCOPY);
    }
  }

  void strethBlt(float destX, float destY, float destWidth, float destHeight)
  {
    HDC hBackMemoryDC = backMemoryBitmp.getMemoryDC();

    if ( hBackMemoryDC ) {
      float scrX = 0.0;
      float srcY = 0.0;

      float scrWidth  =  (float)backMemoryBitmap.getBufferWidth();
      float srcHeight =  (float)backMemoryBitmap.getBufferHeight();
      DC::strtchBlt(destX, destY, destWidth, destHeight,
        hBackMemoryDC, srcX, srcY, srcWidth, srcHeight,
        SRCCOPY):
    }
  }

  void strethBlt(float destX, float destY, float destWidth, float destHeight,
                 float srcX,  float srcY, float srcWidth, float srcHeight)
  {
    HDC hBackMemoryDC = backMemoryBitmp.getMemoryDC();

    if ( hBackMemoryDC ) {

      float bufferWidth  =  (float)backMemoryBitmap.getBufferWidth();
      float bufferHeight =  (float)backMemoryBitmap.getBufferHeight();
      if (scrWidth < bufferWidth && srcHeight < bufferHeight) {
        DC::strtchBlt(destX, destY, destWidth, destHeight,
            hBackMemoryDC, srcX, srcY, srcWidth, srcHeight,
            SRCCOPY);
      }
    }
  }

};

}
