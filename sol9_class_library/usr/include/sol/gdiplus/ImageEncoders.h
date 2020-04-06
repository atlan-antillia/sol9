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
 *  ImageEncoders.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/08

#pragma once

#include <sol\Object.h>

#include <gdiplus.h>

namespace SOL {

class ImageEncoders :public Object {

private:
  UINT number;
  Gdiplus::ImageCodecInfo* pEncoders;

public:
  ImageEncoders()
  :number(0),
  pEncoders(NULL)
  {
    UINT size = 0;
    Gdiplus::GetImageEncodersSize(&number, &size);
    pEncoders = (Gdiplus::ImageCodecInfo*)new BYTE[size];
    Gdiplus::GetImageEncoders(number, size, pEncoders);
  }

public:
  ~ImageEncoders()
  {
    delete [] pEncoders;
    pEncoders = NULL;
  }

public:
  /**
   * @name : "BMP", "JPEG", "GIF", "PNG", "TIFF", ...
   */
  Gdiplus::ImageCodecInfo* getEncoderByName(__in const wchar_t* name)
  {
    Gdiplus::ImageCodecInfo* codec = NULL;

    for (size_t i = 0; i < number; i++) {
      if (_wcsicmp(pEncoders[i].FormatDescription, name) == 0) {
        codec = &pEncoders[i];
        break;
      }
    }
    return codec;
  }

public:
  /**
   * @name : "BMP", "JPEG", "GIF", "PNG", "TIFF", ...
   */
  bool getClsIdByName(__in const wchar_t* name, __out CLSID& clsId)
  {
    bool rc = false;

    for (size_t i = 0; i < number; i++) {
      if (_wcsicmp(pEncoders[i].FormatDescription, name) == 0) {
        clsId = pEncoders[i].Clsid;
        rc = true;
        break;
      }
    }
    return rc;
  }


public:
  /** 
   * @mimetype : "image/bmp", "image/jpeg", "image/png", "image/gif", "image/tiff"...
   */
  Gdiplus::ImageCodecInfo* getEncoderByMimeType(__in const wchar_t* mimetype)
  {
    Gdiplus::ImageCodecInfo* codec = NULL;

    for (size_t i = 0; i < number; i++) {
      if (_wcsicmp(pEncoders[i].MimeType, mimetype) == 0) {
        codec = &pEncoders[i];
        break;
      }
    }
    return codec;
  }

public:
  /** 
   * @mimetype : "image/bmp", "image/jpeg", "image/png", "image/gif", "image/tiff"...
   */
  bool getClsIdByMimeType(__in const wchar_t* mimetype, __out CLSID& clsId)
  {
    bool rc = false;

    for (size_t i = 0; i < number; i++) {
      if (_wcsicmp(pEncoders[i].MimeType, mimetype) == 0) {
        clsId= pEncoders[i].Clsid;
        rc = true;

        break;
      }
    }
    return rc;
  }

  void display()
  {
    for(UINT i = 0; i < number; i++) {
      wprintf(L"CodecName        : %s\n", pEncoders[i].CodecName);
      wprintf(L"DllName          : %s\n", pEncoders[i].DllName);
      wprintf(L"FormatDescription: %s\n", pEncoders[i].FormatDescription);
      wprintf(L"FilenameExtension: %s\n", pEncoders[i].FilenameExtension);
      wprintf(L"MimeType         : %s\n", pEncoders[i].MimeType);
      wprintf(L"Version          : %d\n", pEncoders[i].Version);
      wchar_t buff[128];
      if(StringFromGUID2(pEncoders[i].Clsid, buff, CountOf(buff))) {
        wprintf(L"Clsid            : %s\n", buff);
      }
      wprintf(L"\n");
    }
  }

};

}
