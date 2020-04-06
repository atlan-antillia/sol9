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
 *  ImageView.h
 *
 *****************************************************************************/

// SOL9
// 2012/05/29 
// 2012/07/10

#pragma once

#include <sol\ImageBox.h>
#include <sol/gdiplus/ImageFilters.h>
#include <sol/gdiplus/ImageBlender.h>
#include <sol/gdiplus/ImageTuner.h>

namespace SOL {

class ImageView :public ImageBox {
private:
  ImageBlender blender;
  ImageTuner   tuner;

public:
  ImageView(): ImageBox() { }

public:
  ImageView(View* parent, 
      const TCHAR* name, Args& args)
  :ImageBox(parent, name, args)
  {
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    return   ImageBox::create(parent, name, args);//.set(XmNstyle, WS_VSCROLL|WS_HSCROLL));
  }

public:
  ~ImageView()
  {
  }


public:
  void blendImage(COLORREF backColor, const TCHAR* name)
  {
    Gdiplus::Bitmap* bitmap = getImage();
    if (bitmap) {  
      try {
        //ImageBlender blender;
        
        Gdiplus::Bitmap* newBitmap = blender.blendImage(bitmap,
              backColor, 
              (const wchar_t*)_bstr_t(name));
        if (newBitmap) {
          clear();

          setImage(newBitmap);
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }

public:
  void blendImage(const TCHAR* fileName, COLORREF backColor, const TCHAR* name)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();

        //ImageBlender blender;
        Gdiplus::Bitmap* bitmap = blender.blendImage((const wchar_t*)_bstr_t(fileName),
              backColor, 
              (const wchar_t*)_bstr_t(name));
        if (bitmap) {
          clear();

          setImageFileName(fileName);
          setImage(bitmap);
      
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }

public:
  void blendImage(const TCHAR* fileName, COLORREF backColor, const TCHAR* name, const TCHAR* resize)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();
        //ImageBlender blender;

        Gdiplus::Bitmap* bitmap = blender.blendImage((const wchar_t*)_bstr_t(fileName),
              backColor, 
              (const wchar_t*)_bstr_t(name));
        if (bitmap) {
          clear();

          setImageFileName(fileName);
          setImage(bitmap);
      
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }

public:
  void blendImage(const TCHAR* fileName, const TCHAR* backImageFileName, const TCHAR* name)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();
        //ImageBlender blender;

        Gdiplus::Bitmap* bitmap = blender.blendImage((const wchar_t*)_bstr_t(fileName), 
              (const wchar_t*)_bstr_t(backImageFileName),
              (const wchar_t*)_bstr_t(name));
        if (bitmap) {
          clear();

          setImageFileName(fileName);
          setImage(bitmap);
      
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }


public:
  void blendImage(const TCHAR* fileName, const TCHAR* name)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();
        //ImageBlender blender;
        Gdiplus::Bitmap* currentBitmap = getImage(); 
        Gdiplus::Bitmap* bitmap = blender.blendImage((const wchar_t*)_bstr_t(fileName), 
              currentBitmap,
              (const wchar_t*)_bstr_t(name));
        if (bitmap) {
          clear();

          setImageFileName(fileName);
          setImage(bitmap);
      
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }


public:
  bool saveAs(const TCHAR* fileName)
  {
    bool rc = false;
    Gdiplus::Bitmap* bitmap = getImage();
    if (bitmap) {  
      try {
        //ImageBlender blender;
        
        rc = blender.saveAs(bitmap, _bstr_t(fileName));
      } catch (...) {

      }
    }
    return rc;
  }

public:
  //2012/07/10
  void tuneImage(const TCHAR* fileName, const TCHAR* name)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();
        //ImageBlender blender;
        Gdiplus::Bitmap* currentBitmap = getImage(); 
        Gdiplus::Bitmap* bitmap = tuner.tuneImage((const wchar_t*)_bstr_t(fileName), 
              (const wchar_t*)_bstr_t(name));
        if (bitmap) {
          clear();

          setImageFileName(fileName);
          setImage(bitmap);
      
          invalidateAll();
          update();
        } 
      } catch (...) {

      }
    }
  }

};

}

