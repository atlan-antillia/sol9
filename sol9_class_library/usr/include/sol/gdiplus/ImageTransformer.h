/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * ar
 e met:
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
 *  ImageTransformer.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/08
// 2012/04/30 Updated.

#pragma once

#include <sol\Object.h>
#include <sol/gdiplus/ImageEncoders.h>
#include <sol/WString.h>
#include <sol\Folder.h>
#include <sol\WFileFinder.h>
#include <sol\WFileFindData.h>

namespace SOL {

class ImageTransformer :public Object {

private:
  ImageEncoders encoders;

public:
  ImageTransformer()
  {
  }

public:
  ~ImageTransformer()
  {
  }

public:
  // 2012/04/30
  int getImageSize(const wchar_t* imageFolderName)
  {
    int rc = 0;
    Folder source(imageFolderName);
    
    if (source.exists() == false) {
      throw Exception(0, _T("Exception: Not found an imageFolder: %s"), imageFolderName);
    }

    WString sourceDir = source.getDirectory();
    WString extension = source.getExtension();

    WString format = L"\\*."; 
    if (extension.getLength() > 0) {
      format = format + extension; 
    } else {
      format = format + L"*";
    }
  
    WString sourceFileNames = sourceDir;
    sourceFileNames = sourceFileNames + format;
    wprintf(L"SourceFileNames=%s\n", (const wchar_t*)sourceFileNames);
    
    WFileFinder finder(sourceFileNames);
    WIN32_FIND_DATAW findData;

    if (finder.getFirst(findData)) {
      rc += getImageSize(sourceDir, findData);

      while (finder.getNext(findData)) {
        rc += getImageSize(sourceDir, findData);
      }
    }
    return rc;
  }

public:
  int getImageSize(const wchar_t* sourceDir, WIN32_FIND_DATAW findData)
  {
    int rc = 0;
    const wchar_t* sourceFileName = findData.cFileName; 
  
    WFileFindData wfindData(findData);
    if (wfindData.isDirectory()) { 
      if (!(wcscmp(sourceFileName, L".") == 0 ||
        wcscmp(sourceFileName, L"..") == 0) ) {

        wchar_t subDirectory[1024];  
        swprintf(subDirectory,  CountOf(subDirectory), L"%s\\%s\\", 
          (const wchar_t*)sourceDir, sourceFileName);
        //Recursively call getImageSize method.
        rc = getImageSize(subDirectory);      
      }
      return rc;
    } else {

      try {
        const wchar_t* format = getImageFormat(sourceFileName);
        WString wsourceFile = sourceFileName;

        if (format || wsourceFile.endsWithIgnoreCase(L".ico")) {
          //Format is one of the following values "BMP", "PNG", "GIF", "JPEG", "TIFF" or "ICO";
          wchar_t imageFileName[1024];  
          swprintf(imageFileName,  CountOf(imageFileName), L"%s\\%s", 
            (const wchar_t*)sourceDir, sourceFileName);
        
          int width, height;
          if (getImageSize(imageFileName, width, height)) {
            wprintf(L"ImageFile: '%s'  width = %d height = %d.\n",
            imageFileName, width, height);
            rc++;
          }
        }
      } catch (Exception& ){
        //This will happens when fileName is unsupported image file format or folder. 
      }
    }
    return rc;
  }

public:
  bool getImageSize(const wchar_t* sourceFileName, int& width, int& height)
  {
    bool rc = false;

    if (sourceFileName) {    
      Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap((const wchar_t*)sourceFileName);

      if (bitmap) {
        if (bitmap-> GetLastStatus() == Gdiplus::Ok) {
          width  = bitmap->GetWidth();
          height = bitmap->GetHeight();
          rc = true;
        }
        delete bitmap;
      }
    }
    return rc;
  }

public:
  bool getEncoderByName(const wchar_t* name, CLSID& clsId)
  {
    return encoders.getClsIdByName(name, clsId);
  }

public:
  bool getEncoderByMimeType(const wchar_t* name, CLSID& clsId)
  {
    return encoders.getClsIdByMimeType(name, clsId);
  }

public:
  const wchar_t* getImageFormat(const wchar_t* fileName)
  {
    static const wchar_t* BMP  = L"BMP";
    static const wchar_t* PNG  = L"PNG";
    static const wchar_t* GIF  = L"GIF";
    static const wchar_t* JPEG = L"JPEG";
    static const wchar_t* TIFF = L"TIFF";
    
    const wchar_t* format = NULL;

    const wchar_t* extension = wcsrchr(fileName, (wchar_t)'.');
    if (extension == NULL) {
      throw Exception (0, L"Exception: Invalid fileName: %s", fileName);
    } else {
      extension++;
      if (_wcsicmp(extension, L"BMP") == 0) {
        format = BMP;
      }
      else if (_wcsicmp(extension, L"PNG") == 0) {
        format = PNG; 
      }
      else if (_wcsicmp(extension, L"GIF") == 0) {
        format = GIF;
      }
      else if (_wcsicmp(extension, L"JPEG") == 0 || _wcsicmp(extension, L"JPG") == 0) {
        format = JPEG;
      }
      else if (_wcsicmp(extension, L"TIFF") == 0 || _wcsicmp(extension, L"TIF") == 0) {
        format = TIFF;
      } 
      else {
        throw Exception (0, L"Exception: Invalid fileName: %s. It must end with '.bmp', '.png', '.gif', '.jpg', or '.tif'",
          fileName);
      }
    }
    return format;
  }

  //2012/06/01
public:
  bool saveAs(Gdiplus::Image* image,  const wchar_t* saveFileName)
  {
    bool rc = false;
    if (image == NULL) {
      throw Exception (0, "Exception: Image is NULL.");
    }
    if (saveFileName == NULL) {
      throw Exception (0, "Exception: FileName is NULL.");
    }

    if (image && image-> GetLastStatus() == Gdiplus::Ok) {
      const wchar_t* format = getImageFormat(saveFileName);

      if (format) {
        CLSID clsId;
        if (getEncoderByName(format, clsId)) {
          if (image->Save(saveFileName, &clsId) == Gdiplus::Ok) {
            UINT w = image->GetWidth();
            UINT h = image->GetHeight();      
            wprintf(L"Saved as '%s' :width=%d height=%d\n",
              saveFileName, w, h);

            rc = true; 
          }
        }
      }
    }
    return rc;
  }

  //2012/07/13
public:
  bool getImageFormat(Gdiplus::Image* image, String& format)
  {
    bool rc = false;
    if (image == NULL) {
      throw Exception (0, "Exception: Image is NULL.");
    }

    struct Rawformat{GUID  guid; const TCHAR* name;};
    static const  Rawformat rawFormats[] = {
      {Gdiplus::ImageFormatBMP, _T("bmp") },
      {Gdiplus::ImageFormatEMF, _T("emf") },
      {Gdiplus::ImageFormatEXIF, _T("jpg") },
      {Gdiplus::ImageFormatGIF, _T("gif") },
      {Gdiplus::ImageFormatIcon, _T("ico") },
      {Gdiplus::ImageFormatJPEG, _T("jpg")},
      {Gdiplus::ImageFormatPNG,  _T("png") },
      {Gdiplus::ImageFormatTIFF, _T("tif") }
    };

    GUID guid;
    Gdiplus::Status stat = image->GetRawFormat(&guid);
    if (stat == Gdiplus::Ok) {
      for (int i = 0; i<CountOf(rawFormats); i++) {
        if (guid == rawFormats[i].guid) {
          format = rawFormats[i].name;
          rc = true;
          break;
        }
      }
    }
    return rc;
  }
};

}
