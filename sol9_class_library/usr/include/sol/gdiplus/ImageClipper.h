/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Imageclipper.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/08
// 2012/06/01 Updated

#pragma once

#include <sol/Object.h>
#include <sol/File.h>

#include <sol/gdiplus/ImageTransformer.h>


namespace SOL {

class ImageClipper :public ImageTransformer {

public:
  ImageClipper()
  {
  }

public:
  ~ImageClipper()
  {
  }


public:
  bool clip(const wchar_t* sourceFileName, const wchar_t* saveFileName,
    int x, int y, int width, int height)
  {
    bool rc = false;
    if (sourceFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL");
    } 

    Gdiplus::Bitmap* clippedBitmap = clipImage(sourceFileName, x, y, width, height);

    if (clippedBitmap) {
      try {
        rc = saveAs(clippedBitmap, saveFileName);
      } catch (...) {

      }
      delete clippedBitmap;
    }
    return rc;    
  }

public:
  //2012/06/01
  Gdiplus::Bitmap* clipImage(const wchar_t* sourceFileName,  
    int x, int y, int width, int height)
  {
    Gdiplus::Bitmap* clippedBitmap = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      int w = bitmap->GetWidth();
      int h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);
      //Check the reft-top corner position(x, y) of clipping rectangle
      if (x < 0 ) {
        x = 0;
        printf("Clipping x position has been changed to %d\n", x);
      }
      if (y < 0) {
        y = 0;
        printf("Clipping y position has been changed to %d\n", y);
      }
  
      if (w > 0 && h > 0) {
        if (x < w && y < h) {
          if ((x + width) > w) {
            int dw = x + width - w;
            width = width - dw;
            printf("Clipping width has been changed to %d\n", width);
          }
          if ( (y + height) > h) {
            int dh = y + height - h;
            height = height - dh;
            printf("Clipping height has been changed to %d\n", height);
          }
          Gdiplus::RectF rect((float)x, (float)y, (float)width, (float)height);

          clippedBitmap = bitmap->Clone(rect, bitmap->GetPixelFormat() );

          if (clippedBitmap && clippedBitmap-> GetLastStatus() != Gdiplus::Ok) {
            delete clippedBitmap;
            clippedBitmap = NULL;
          }
        } else {
          if (x >=w) {
            printf("Error:Invalid clipping x position: %d\n", x);
          }
          if (y >=h) {
            printf("Error:Invalid clipping y position: %d\n", y);
          }
        }
      }
      delete bitmap;
    }
    return clippedBitmap;    
  }

};

}
