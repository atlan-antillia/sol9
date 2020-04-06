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
 *  ImageBox.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/08
#pragma once

#include <sol\Primitive.h>
#include <sol\PaintDC.h>

#include <gdiplus.h>
#include <sol/Brush.h>
#include <sol/gdiplus/ImageFilters.h>

#include <sol\File.h>
#include <sol/ole/FileDownloaderThread.h>

//using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

namespace SOL {

class ImageBox :public Primitive {
private:
  HICON hIcon;

private:
  Gdiplus::Bitmap* image;
  int  scaling;

  String imageFileName;

private:
  String downloadedFileName;

private:
  String imageUrlName;

private:
  FileDownloaderThread* downloader;

public:
  int getScaling()
  {
    return scaling;
  }

public:
  enum STRETCH_MODE {
    StretchImage  = 0,
    StretchWindow = 1
  };

public:
  ImageBox()
  :image(NULL), //2012/07/02
  hIcon(NULL),
  Primitive() { }

public:
  ImageBox(View* parent, const TCHAR* name, Args& args)
    :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    this->downloader = NULL;

    image = NULL;
    scaling = (int)args.get(XmNscaling);

    Boolean rc = Primitive::create(parent, name,
        args.set(XmNclassName, _T("_ImageBox_"))
            .set(XmNbackground, (LONG_PTR)GetStockObject(NULL_BRUSH)) );


    const TCHAR* fileName = (const TCHAR*)args.get(XmNimageFileName);
    if (fileName) {
      loadImage(fileName);
    }

    hIcon = NULL;
    HINSTANCE hInst = getInstanceHandle();
    const TCHAR* iconResourceName = (const TCHAR*)args.get(XmNiconResourceName);
    if (iconResourceName) {

      hIcon = (HICON)LoadImage(hInst, iconResourceName,IMAGE_ICON,0,0, LR_CREATEDIBSECTION);

      if (hIcon) {
        loadImage(hIcon);
      }
    }
    addEventHandler(WM_PAINT, this,
      (Handler)&ImageBox::paint, NULL);

    setValues(args);

    addEventHandler(FileDownloaderThread::WM_FILEDOWNLOADED, this,
      (Handler)&ImageBox::downloaded, NULL);

    return rc;
  }

public:
  ~ImageBox()
  {
    clear();
  }

public:
  void clear()
  {
    if (image) {
      if (hIcon) {
        DeleteObject(hIcon);
        hIcon = NULL;  //2012/08/05
      }
      delete image;
      image = NULL;
    }
  }


public:
  const TCHAR* getImageFileName()
  {
    return (const TCHAR*)imageFileName;
  }

public:
  void setImageFileName(const TCHAR* fileName)
  {
    imageFileName = fileName;
  }

public:
  void setImage(Gdiplus::Bitmap* image)
  {
    if (image) {
      clear();
      this->image = image;
    }
  }

public:
  Gdiplus::Bitmap* getImage()
  {
    return this->image;
  }

public:
  bool getImageSize(int& width, int& height)
  {
    bool rc = false;
    width  = 0;
    height = 0;
    if (image) {
      width = image->GetWidth();
      height = image->GetHeight();
      rc = true;    
    }
  }

public:
  void loadImage(const TCHAR* fileName)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
      clear();
      this->imageFileName = fileName;
      this->image = new Gdiplus::Bitmap((const wchar_t*)_bstr_t(fileName), TRUE);
  
      invalidateAll();
      update();
    }
  }

public:
  void loadImage(HICON hIcon)
  {
    //File file;
    if (hIcon) {
      clear();
    
      this->imageFileName = _T(""); 
      this->image = Gdiplus::Bitmap::FromHICON(hIcon);
  
      invalidateAll();
      update();
    }
  }

public:
  bool downloadImage(const TCHAR* url, const TCHAR* saveFileName)
  {
    DWORD flag = 0; 
    if (!InternetGetConnectedState(&flag, 0)) {
      MessageBox(getWindow(), _T("There is no Internet connection. Can't download a file."),
          (const TCHAR*)saveFileName, MB_ICONERROR);
      return false;
    }

    if (downloader) {
      //Now downloading, so return false.
      return false;
    } else {  
      //Create a downloading-thread, and start it.
      imageUrlName       = url;
      downloadedFileName = saveFileName;
      //Create an instance of FileDownloaderThread. 
      downloader = new FileDownloaderThread(url, saveFileName, getWindow());
      downloader->start();
      return true;
    }
  }

public:
  long downloaded(Event& event)
  {  
    //Completed to downloading an image from a web site.
    downloader = NULL;
    //SetCursor(LoadCursor(0, IDC_ARROW));

    BOOL rc = (BOOL)event.getWParam();
    if (rc) {
      //Succeeded to download.
      File file;
      if (file.isExistent((const TCHAR*)downloadedFileName)) {
        //If a download file exists, load it into this window.
        loadImage((const TCHAR*)downloadedFileName);
        downloadedFileName = "";
      } else {        
        MessageBox(getWindow(), _T("Failed to open a downloaded file"),
          (const TCHAR*)downloadedFileName, MB_ICONERROR);
      }
    } else {
      //Faield to download an image file, 
      // Most likely causes:
      //There might be a typing error in the image url.
      //Maybe, you are not connected to the Internet.
      MessageBox(getWindow(), _T("Failed to download a file of url"),
        (const TCHAR*)imageUrlName,  MB_ICONERROR);
    }
    return 0;
  }


  //2012/05/28 Modified to be a public virtual method
public:
  virtual long paint(Event& event)
  {
    PaintDC pdc(this);
  
    RECT r;
    //Get the size of this window.
    getClientRect(&r);
  
    Gdiplus::Graphics graphics(pdc.get());
    if (image) {
      if (scaling == StretchImage) {

        Gdiplus::Rect rect(r.left, r.top, r.right-r.left, r.bottom-r.top);
        //Draw resized image in the rectangle of 'rect'. 
        graphics.DrawImage(image, rect);
      }
      if (scaling == StretchWindow) {
        UINT width = image->GetWidth();
        UINT height = image->GetHeight();
        //Resize this window to display the whole area of the image with real size.
        resize(width, height);
        //Draw real image in the resized window.
        graphics.DrawImage(image, 0, 0, width, height);
      }
    } else {
      //2012/06/05
      Brush white(RGB(0xff,0xff,0xff));
      pdc.fillRect(&r, (HBRUSH)white);
    }
    return 0;
  }

public:
  void loadImage(const TCHAR* fileName, COLORREF color, const TCHAR* name)
  {
    File file;
    if (fileName && file.isExistent(fileName)) {
  
      try {
        const TCHAR* imageFileName = getImageFileName();
        if (imageFileName==NULL || (imageFileName && _stricmp(imageFileName, fileName)) ) {
        
          Gdiplus::Bitmap* bitmap = blend((const wchar_t*)_bstr_t(fileName), color, (const wchar_t*)_bstr_t(name));
          if (bitmap) {
            clear();

            setImageFileName(fileName);

            setImage(bitmap);
      
            invalidateAll();
            update();
          } 
        }
      } catch (...) {

      }
    }
  }

public:
  //
  Gdiplus::Bitmap* blend(const wchar_t* sourceFileName, COLORREF backColor, const wchar_t* name)
  {
    bool rc = false;
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

        if (!(blendedBitmap && blendedBitmap-> GetLastStatus() == Gdiplus::Ok)) {
          delete blendedBitmap;
          blendedBitmap = NULL;
        }
      }
      delete bitmap;
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

};

}

