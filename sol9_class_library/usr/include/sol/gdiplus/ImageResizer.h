
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
 *  ImageResizer.h
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

class ImageResizer : public ImageTransformer {

public:
  ImageResizer()
  {
  }

public:
  ~ImageResizer()
  {
  }

public:
  /** resizeParam takes one of the following formats:
    resizePercentage%         Ex. 50%
    resizeWidth,*             Ex. 400,* 
    *,reisizeHeight           Ex.  *,300
    resizeWidth,risizeHeight: Ex. 400,300
  */
  bool resize(const wchar_t* sourceFileName, const wchar_t* saveFileName, const TCHAR* resizeParam)
  {
    bool rc = false;
    String string = resizeParam;
    String swidth, sheight;
    String spercent, any;

    if (string.contains(_T("%"))) {
      if (string.split('%', spercent, any)==1) {
        int percentage = atoi((const TCHAR*)spercent);
        _tprintf(_T("percentage = [%s]\n"), (const TCHAR*)spercent);
        return resize(sourceFileName, saveFileName, percentage);
      }
    }
    else if(string.endsWith(_T(",*")) ) {
      if (string.split(',', swidth, any) ==2) {
        int width = atoi((const TCHAR*)swidth);
        _tprintf(_T("width = [%s] height = [%s]\n"), 
          (const TCHAR*)swidth,
          (const TCHAR*)any);
        return resize(sourceFileName, saveFileName, width, 0);
      }
    }
    else if (string.startsWith(_T("*,")) ){
      if (string.split(',', any, sheight) ==2) {
        int height = atoi((const TCHAR*)sheight);
        _tprintf(_T("width = [%s] height = [%s]\n"), 
          (const TCHAR*)any,
          (const TCHAR*)sheight);
        return resize(sourceFileName, saveFileName, 0, height);
      }
    }
    else if (string.contains(_T(",")) ) {
      if (string.split(',', swidth, sheight) ==2) {
        int width = atoi((const TCHAR*)swidth);
        int height = atoi((const TCHAR*)sheight);
        _tprintf(_T("width = [%s] height = [%s]\n"), 
          (const TCHAR*)swidth,
          (const TCHAR*)sheight);
        return resize(sourceFileName, saveFileName, width, height);
      }
    } else {
      //Unsupported resizing resizeParame
      throw Exception(0, "Exception: Invalid resizing resizeParameter: %s", resizeParam);
    }
    return rc;
  }

public:
  bool resize(const wchar_t* sourceFileName, const wchar_t* saveFileName, int percentage)
  {
    bool rc = false;
    if (sourceFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    if (percentage <=0 || percentage>1000) {
      throw Exception (0, "Exception: Percentage is invalid. It's 1<percentage <=1000. ");
    }

    Gdiplus::Bitmap* resizedBitmap = resizeImage(sourceFileName, percentage);
    if (resizedBitmap) {
      try {
        rc = saveAs(resizedBitmap, saveFileName);
      } catch (...) {

      }
      delete resizedBitmap;
    }
    return rc;    
  }

public:
  // 2012/06/01
  Gdiplus::Bitmap* resizeImage(const wchar_t* sourceFileName, int percentage)
  {
    if (sourceFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    if (percentage <=0 || percentage>1000) {
      throw Exception (0, "Exception: Percentage is invalid. It's 1<percentage <=1000. ");
    }

    Gdiplus::Bitmap* resizedBitmap = NULL;
        
    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);
  
      if (w > 0 && h > 0 ) {
        int width  = (w * percentage)/100;
        int height = (h * percentage)/100;

        Gdiplus::Bitmap* resizedBitmap = createResizeBitmap(bitmap, width, height);

        if (resizedBitmap && resizedBitmap-> GetLastStatus() != Gdiplus::Ok) {
          delete resizedBitmap;
          resizedBitmap = NULL;
        }
      }
      delete bitmap;
    }
    return resizedBitmap;    
  }


public:
  bool resize(const wchar_t* sourceFileName, const wchar_t* saveFileName, int width, int height)
  {
    bool rc = false;
    if (sourceFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* resizedBitmap = resizeImage(sourceFileName, width, height);

    if (resizedBitmap) { 
      try {
        rc = saveAs(resizedBitmap, saveFileName);
      } catch(...) {

      }
      delete resizedBitmap;
    }
    return rc;    
  }

public:
  // 2012/06/01
  Gdiplus::Bitmap* resizeImage(const wchar_t* sourceFileName, int width, int height)
  {
    if (sourceFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* resizedBitmap = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);
  
      if (w > 0 && h > 0 ) {
        if (width >0 && height == 0) {
          height = (h * width)/w;
        }
        if (width == 0 && height > 0) {
          width = (w * height)/h;
        }

        Gdiplus::Bitmap* resizedBitmap = createResizeBitmap(bitmap, width, height);

        if (resizedBitmap && resizedBitmap-> GetLastStatus() != Gdiplus::Ok) {
          delete resizedBitmap;
          resizedBitmap = NULL;
        }
      }
      delete bitmap;
    }
    return resizedBitmap;    
  }


public:
  //Create a resized bitmap from a sourceBitmap. 
  Gdiplus::Bitmap* createResizeBitmap(Gdiplus::Bitmap* sourceBitmap,int width, int height)
  {
    Gdiplus::Graphics* desktopGraphics = Gdiplus::Graphics::FromHWND(NULL);

    Gdiplus::Bitmap* destBitmap = new Gdiplus::Bitmap(width, height, desktopGraphics);

    Gdiplus::Graphics* destGraphics = new Gdiplus::Graphics(destBitmap);

    destGraphics->DrawImage(sourceBitmap, 0, 0, width, height);
    
    delete desktopGraphics;    
    delete destGraphics;

    return destBitmap;
  }

};

}
