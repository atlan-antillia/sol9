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
 *  ImageBlender.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/22
// 2012/05/31 Updated
// 2012/06/16 Updated

#pragma once

#include <sol/Object.h>
#include <sol/File.h>
#include <sol/WString.h>
#include <sol/gdiplus/ImageTransformer.h>
#include <sol/gdiplus/ImageFilters.h>
#include <sol/gdiplus/ImageFileFilter.h>

#include <sol/LinkedList.h>

namespace SOL {

class ImageBlender :public ImageTransformer {

public:
  ImageBlender()
  {
  }

public:
  ~ImageBlender()
  {
  }

public:
  //
  bool blend(const wchar_t* sourceFileName, const wchar_t* backImageFileName, const wchar_t* saveFileName, const wchar_t* name)
  {
    bool rc = false;
    if (sourceFileName == NULL || backImageFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* blendedBitmap = blendImage(sourceFileName, backImageFileName, name);
    if (blendedBitmap) {
      try {
        rc = saveAs(blendedBitmap, saveFileName);
      } catch (...) {

      }
      delete blendedBitmap;
    }
    return rc;    
  }

public:
  /*
  */
  bool blend(const TCHAR* backColorName, LinkedList& imageFileList, const TCHAR* saveFileName)
  {
    bool rc = false;
    Gdiplus::Bitmap* blendedBitmap = blendImage(backColorName, imageFileList);
    if (blendedBitmap){
      rc = saveAs(blendedBitmap, _bstr_t(saveFileName));

      delete blendedBitmap;
    }
    return rc;
  }

public:
  // name takes 'alpha:scale' where scale is a float type alpha blending scale parameter.
  //2012/05/31
  Gdiplus::Bitmap* blendImage(const wchar_t* sourceFileName, const wchar_t* backImageFileName, const wchar_t* name)
  {
    if (sourceFileName == NULL || backImageFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* blendedBitmap = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);

      Gdiplus::Bitmap* backBitmap = new Gdiplus::Bitmap(backImageFileName, TRUE);
      if (backBitmap && backBitmap-> GetLastStatus() == Gdiplus::Ok) {

        ImageFilters filters;
        Gdiplus::ColorMatrix matrix;
        if (filters.getColorMatrix(name, matrix)) {

          blendedBitmap = createBlendedBitmap(bitmap, backBitmap, matrix);

          if (blendedBitmap && blendedBitmap-> GetLastStatus() != Gdiplus::Ok) {
            delete blendedBitmap;
            blendedBitmap = NULL;
          }
        }
        delete backBitmap;
      }
      delete bitmap;
    }
    return blendedBitmap;
  }

public:
  // name takes 'alpha:scale' where scale is a float type alpha blending scale parameter.
  //2012/05/31
  Gdiplus::Bitmap* blendImage(const wchar_t* sourceFileName, Gdiplus::Bitmap* backBitmap, const wchar_t* name)
  {
    if (sourceFileName == NULL ) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* blendedBitmap = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);

      if (backBitmap && backBitmap-> GetLastStatus() == Gdiplus::Ok) {

        ImageFilters filters;
        Gdiplus::ColorMatrix matrix;
        if (filters.getColorMatrix(name, matrix)) {

          blendedBitmap = createBlendedBitmap(bitmap, backBitmap, matrix);

          if (blendedBitmap && blendedBitmap-> GetLastStatus() != Gdiplus::Ok) {
            delete blendedBitmap;
            blendedBitmap = NULL;
          }
        }
        //delete backBitmap;
      }
      delete bitmap;
    }
    return blendedBitmap;
  }

public:
  Gdiplus::Bitmap* createBlendedBitmap(Gdiplus::Bitmap* sourceBitmap,
    Gdiplus::Bitmap* backBitmap, Gdiplus::ColorMatrix& matrix)
  {
    int width  = sourceBitmap->GetWidth();
    int height = sourceBitmap->GetHeight();

    int bwidth  = backBitmap->GetWidth();
    int bheight = backBitmap->GetHeight();

    Gdiplus::Graphics* desktopGraphics = Gdiplus::Graphics::FromHWND(NULL);

    Gdiplus::Bitmap* destBitmap = new Gdiplus::Bitmap(width, height, desktopGraphics);

    Gdiplus::Graphics* destGraphics = new Gdiplus::Graphics(destBitmap);

    //1 Draw the bacBitmap 
    destGraphics->DrawImage(backBitmap, 0, 0, bwidth, bheight);

    Gdiplus::ImageAttributes imageAttributes;
    imageAttributes.SetColorMatrix(&matrix,
        Gdiplus::ColorMatrixFlagsDefault, 
                        Gdiplus::ColorAdjustTypeBitmap);
    //2 Draw the sourceBitmap with a imageAttribute onto the backBitmap 
    destGraphics->DrawImage(sourceBitmap, 
      Gdiplus::RectF((Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)width, (Gdiplus::REAL)height),
      (Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)width, (Gdiplus::REAL)height, 
      Gdiplus::UnitPixel,
      &imageAttributes);
    
    delete desktopGraphics;    
    delete destGraphics;

    return destBitmap;
  }

public:
  //
  bool blend(const wchar_t* sourceFileName, COLORREF backColor, 
    const wchar_t* saveFileName, const wchar_t* name)
  {
    bool rc = false;
    if (sourceFileName == NULL || saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }
    
    Gdiplus::Bitmap* blendedBitmap = blendImage(sourceFileName, backColor, name);
    if (blendedBitmap) {
      try {
        rc = saveAs(blendedBitmap, saveFileName);
      } catch (...) {
        
      }
      delete blendedBitmap;
    }
    return rc;    
  }

public:
  /*
  */
  //2012/06/16 Updated
  Gdiplus::Bitmap* blendImage(const TCHAR* backColorName, LinkedList& imageFileList)
  {
    COLORREF backColor = 0;
    if (toColor(backColorName, backColor) != true) {
      throw Exception (0, _T("Exception: Invalid backColorName '%s'."), backColorName);
    }
    return blendImage(backColor, imageFileList);
    /*
    if (imageFileList.getLength() ==0) {
      throw Exception (0, _T("Exception: ImageFileFilter list is empty."));
    }

    ListEntry* entry = imageFileList.getEntry();
    // 1 Get maxwidth and maxHeight from imageFileList;

    int width = 0;
    int height= 0;    
    while (entry) {
      ImageFileFilter* imageFileFilter = (ImageFileFilter*)entry->getObject();
      const wchar_t* fileName = imageFileFilter->getFileName();
      int w, h;
      getImageSize(fileName, w, h);  
      if (w > width) {
        width = w;
      }
      if (h > height) {
        height = h;
      }
      entry = entry->getNext();
    }
    return blendImage(width, height, backColor, imageFileList);
    */
  }

public:
  /*
  */
  //2012/06/16 Updated
  Gdiplus::Bitmap* blendImage(COLORREF backColor,LinkedList& imageFileList)
  {
    /*
    COLORREF backColor = 0;
    if (toColor(backColorName, backColor) != true) {
      throw Exception (0, _T("Exception: Invalid backColorName '%s'."), backColorName);
    }
    */

    if (imageFileList.getLength() ==0) {
      throw Exception (0, _T("Exception: ImageFileFilter list is empty."));
    }

    ListEntry* entry = imageFileList.getEntry();
    // 1 Get maxwidth and maxHeight from imageFileList;

    int width = 0;
    int height= 0;    
    while (entry) {
      ImageFileFilter* imageFileFilter = (ImageFileFilter*)entry->getObject();
      const wchar_t* fileName = imageFileFilter->getFileName();
      int w, h;
      getImageSize(fileName, w, h);  
      if (w > width) {
        width = w;
      }
      if (h > height) {
        height = h;
      }
      entry = entry->getNext();
    }
    return blendImage(width, height, backColor, imageFileList);
  }

public:
  /*
  */
  //2012/06/16 Updated
  Gdiplus::Bitmap* blendImage(unsigned int width, unsigned int height, 
    COLORREF backColor, LinkedList& imageFileList)
  {
    if (imageFileList.getLength() ==0) {
      return NULL;
    }
    
    Gdiplus::Graphics* desktopGraphics = Gdiplus::Graphics::FromHWND(NULL);

    Gdiplus::Bitmap* blendedBitmap = new Gdiplus::Bitmap(width, height, desktopGraphics);

    Gdiplus::Graphics* destGraphics = new Gdiplus::Graphics(blendedBitmap);

    Gdiplus::Color color;
    color.SetFromCOLORREF(backColor);
     Gdiplus::SolidBrush colorBrush(color);

    //1 Draw a rectangle with a colorBrush specified by backColor
    destGraphics->FillRectangle(&colorBrush, 0, 0, width, height);
  
    ListEntry* entry = imageFileList.getEntry();

    while (entry) {
      ImageFileFilter* imageFileFilter = (ImageFileFilter*)entry->getObject();
      const wchar_t* fileName = imageFileFilter->getFileName();
      const wchar_t* filerName = imageFileFilter->getFilterName();
      const wchar_t* alignment = imageFileFilter->getAlignment();
      const wchar_t* resize    = imageFileFilter->getSize();
      int percent = 100;
      WString string = resize;
      if (string.contains(L"%")) {
        WString spercent, any;
        if (string.split((wchar_t)'%', spercent, any)==1) {
          percent = atoi((const wchar_t*)spercent);
        }
      }
      Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(fileName, TRUE);
      if (bitmap) {
        if (bitmap->GetLastStatus() == Gdiplus::Ok) {
          int ww = bitmap->GetWidth();
          int hh = bitmap->GetHeight();
          int www = (ww * percent)/100;
          int hhh = (hh * percent)/100;

          ImageFilters filters;
          Gdiplus::ColorMatrix matrix;
          if (filters.getColorMatrix(filerName, matrix)) {
    
            Gdiplus::ImageAttributes imageAttributes;
    
            imageAttributes.SetColorMatrix(&matrix,
              Gdiplus::ColorMatrixFlagsDefault, 
              Gdiplus::ColorAdjustTypeBitmap);

              // 2 Draw the bitmap with an imageAttribute onto the blendedBitmap 
              //LeftTop
          
              int destX = 0;
              int destY = 0;

              if (_wcsicmp(alignment, L"Center") == 0) {
                 destX = (width-www)/2;
                 destY = (height-hhh)/2;
               }
               if (_wcsicmp(alignment, L"LeftTop") == 0) {
                 destX = 0;
                 destY = 0;
               }
               if (_wcsicmp(alignment, L"LeftBottom") ==0) {
                 destX = 0;
                 destY = (height-hhh);
               }
               if (_wcsicmp(alignment, L"RightTop") ==0) {
                 destX = (width-www);
                 destY = 0;
               }
               if (_wcsicmp(alignment, L"RightBottom") == 0) {
                 destX = (width-www);
                 destY = (height-hhh);
               }
               destGraphics->DrawImage(bitmap, 
                  Gdiplus::Rect(destX, destY, www, hhh),
                  0, 0, ww, hh,
                  Gdiplus::UnitPixel,
                  &imageAttributes);
          }
        }
        delete bitmap;
      }
      entry = entry->getNext();
    }

    return blendedBitmap;
  }

public:
  //2012/05/31
  Gdiplus::Bitmap* blendImage(const wchar_t* sourceFileName, COLORREF backColor, 
    const wchar_t* name)
  {
    if (sourceFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    Gdiplus::Bitmap* blendedBitmap = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(sourceFileName, TRUE);

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {
      UINT w = bitmap->GetWidth();
      UINT h = bitmap->GetHeight();
      wprintf(L"SourceImageSize: width=%d height=%d  %s\n",
          w, h, sourceFileName);

      ImageFilters filters;
      Gdiplus::ColorMatrix matrix;
      if (filters.getColorMatrix(name, matrix)) {

        blendedBitmap = createBlendedBitmap(bitmap, backColor, matrix);

        if (blendedBitmap && blendedBitmap-> GetLastStatus() != Gdiplus::Ok) {
          delete blendedBitmap;
          blendedBitmap = NULL;
        }
      }
      delete bitmap;
    }
    return blendedBitmap;    
  }

public:
  //2012/06/-3
  Gdiplus::Bitmap* blendImage(Gdiplus::Bitmap* bitmap, COLORREF backColor, const wchar_t* name)
  {

    Gdiplus::Bitmap* blendedBitmap = NULL;

    if (bitmap && bitmap-> GetLastStatus() == Gdiplus::Ok) {

      ImageFilters filters;
      Gdiplus::ColorMatrix matrix;
      if (filters.getColorMatrix(name, matrix)) {

        blendedBitmap = createBlendedBitmap(bitmap, backColor, matrix);

        if (blendedBitmap && blendedBitmap-> GetLastStatus() != Gdiplus::Ok) {
          delete blendedBitmap;
          blendedBitmap = NULL;
        }
      }
    }
    return blendedBitmap;    
  }

public:
  Gdiplus::Bitmap* createBlendedBitmap(Gdiplus::Bitmap* sourceBitmap, COLORREF backColor, Gdiplus::ColorMatrix& matrix)
  {
    int width  = sourceBitmap->GetWidth();
    int height = sourceBitmap->GetHeight();

    Gdiplus::Graphics* desktopGraphics = Gdiplus::Graphics::FromHWND(NULL);

    Gdiplus::Bitmap* destBitmap = new Gdiplus::Bitmap(width, height, desktopGraphics);

    Gdiplus::Graphics* destGraphics = new Gdiplus::Graphics(destBitmap);

    Gdiplus::Color color;
    color.SetFromCOLORREF(backColor);
     Gdiplus::SolidBrush colorBrush(color);

    //1 Draw a rectangle with a colorBrush specified by backColor
    destGraphics->FillRectangle(&colorBrush, 0, 0, width, height);

    Gdiplus::ImageAttributes imageAttributes;
    imageAttributes.SetColorMatrix(&matrix,
        Gdiplus::ColorMatrixFlagsDefault, 
                        Gdiplus::ColorAdjustTypeBitmap);
    //2 Draw the sourceBitmap with a imageAttribute onto the rectabgke with a background color specified by backColorn 
    destGraphics->DrawImage(sourceBitmap, 
      Gdiplus::RectF((Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)width, (Gdiplus::REAL)height),
      (Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)width, (Gdiplus::REAL)height, 
      Gdiplus::UnitPixel,
      &imageAttributes);
    
    delete desktopGraphics;    
    delete destGraphics;

    return destBitmap;
  }

public:
  //
  // @color: takes the format "#RRGGBB";
  //
  bool toColor(__in const TCHAR* color, __out COLORREF& rgb)
  {
    bool rc = false;
    rgb = 0;
    if (color && *color == '#') {
      color++;
      if (strlen(color) == 6) {
        TCHAR r[3], g[3], b[3];
        memcpy(r, color, 2);
        r[2] = NULL;
        color +=2;

        memcpy(g, color, 2);
        g[2] = NULL;
        color +=2;
        memcpy(b, color, 2);
        b[2] = NULL;
      
        unsigned int rvalue = _tcstoul(r, NULL, 16);    
        unsigned int gvalue = _tcstoul(g, NULL, 16);
        unsigned int bvalue = _tcstoul(b, NULL, 16);

        rgb = RGB(rvalue,gvalue,bvalue);
        rc = true;
      }
    }
    return rc;
  }

};

}
