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
 *  ImageTuner.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/20
// 2012/05/31 Updated

#pragma once

#include <sol/Object.h>
#include <sol/File.h>
#include <sol/WString.h>
#include <sol/gdiplus/ImageTransformer.h>
#include <sol/gdiplus/ImageFilters.h>


namespace SOL {

class ImageTuner :public ImageTransformer {

public:
  ImageTuner()
  {
  }

public:
  ~ImageTuner()
  {
  }

private:
  bool verifyFilterName(const wchar_t* name)
  {
    bool rc = false;
    WString wname = name;
    const wchar_t* filterNames[] = {L"gray", L"lightgray", L"sepia", L"negative", L"contrast:"};
    for (int i = 0; i < CountOf(filterNames); i++) {
      if (wname.findIgnoreCase(filterNames[i])) {
        rc = true;
        break;
      }
    }
    return rc;
  }

public:
  // The tuneFormat parameter takes one of the values: "gray", "lightgray", "sepia", "negative", "contrast:vslur".
  // This method creates a bitmap of sourceFileName, and creates a tuned bitmap from the bitmap by 
  // tuneFormat, and saves the tuned bitmap as saveFileName.
  //
  bool tune(const wchar_t* sourceFileName, const wchar_t* saveFileName, const wchar_t* tuneFormat)
  {
    bool rc = false;
    if (sourceFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    if (verifyFilterName(tuneFormat) == false) {
      throw Exception (0, _T("Exception: Invalid FilterName %s."), (const TCHAR*)_bstr_t(tuneFormat));
    }


    Gdiplus::Bitmap* tunedBitmap = tuneImage(sourceFileName, tuneFormat);

    if (tunedBitmap) {
      try {
        rc = saveAs(tunedBitmap, saveFileName);
      } catch (...) {

      }
      delete tunedBitmap;        
    }

    return rc;    
  }

public:
  // The tuneFormat parameter takes one of the values: "gray", "lightgray", "sepia", "negative", "contrast:value".
  // This method creates a bitmap of sourceFileName, and creates a tuned bitmap from the bitmap by 
  // tuneFormat, and returns the tuned bitmap.
  Gdiplus::Bitmap* tuneImage(const wchar_t* sourceFileName, const wchar_t* tuneFormat)
  {
    if (sourceFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }
        
    Gdiplus::Bitmap* tunedBitmap = NULL;

    if (verifyFilterName(tuneFormat) == false) {
      throw Exception (0, _T("Exception: Invalid FilterName %s."), (const TCHAR*)_bstr_t(tuneFormat));
    }

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);

      ImageFilters filters;
      Gdiplus::ColorMatrix matrix;
      if (filters.getColorMatrix(tuneFormat, matrix)) {

        tunedBitmap = createTunedBitmap(bitmap, matrix);

        if (tunedBitmap && tunedBitmap-> GetLastStatus() != Gdiplus::Ok) {
          delete tunedBitmap;
          tunedBitmap = NULL;
        }
      }

      delete bitmap;
    }
    return tunedBitmap;    
  }

public:
  Gdiplus::Bitmap* createTunedBitmap(Gdiplus::Bitmap* sourceBitmap, Gdiplus::ColorMatrix& matrix)
  {
    int width  = sourceBitmap->GetWidth();
    int height = sourceBitmap->GetHeight();

    Gdiplus::Graphics* desktopGraphics = Gdiplus::Graphics::FromHWND(NULL);

    Gdiplus::Bitmap* destBitmap = new Gdiplus::Bitmap(width, height, desktopGraphics);

    Gdiplus::Graphics* destGraphics = new Gdiplus::Graphics(destBitmap);


    Gdiplus::ImageAttributes attributes;
    attributes.SetColorMatrix(&matrix,
        Gdiplus::ColorMatrixFlagsDefault, 
                        Gdiplus::ColorAdjustTypeBitmap);
    
    destGraphics->DrawImage(sourceBitmap, Gdiplus::Rect(0, 0, width, height),
      0, 0, width, height, 
      Gdiplus::UnitPixel,
      &attributes);
    
    delete desktopGraphics;    
    delete destGraphics;

    return destBitmap;
  }
};

}
