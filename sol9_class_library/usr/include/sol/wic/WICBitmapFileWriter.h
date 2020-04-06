/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WICBitmapFileWriter.h
 *
 *****************************************************************************/

#pragma once

#include <wincodecsdk.h>
#include <sol/Pair.h>
#include <sol/StringT.h>

#include <sol/wic/WICBitmapEncoder.h>
#include <sol/wic/WICBitmapFrameEncode.h>
#include <sol/wic/WICFormatConverter.h>

#include <sol/wic/WICStream.h>

namespace SOL {
  
class WICBitmapFileWriter : public WICBitmapEncoder {
private:
  GUID formatGuid(const wchar_t* filename)
  {
    if (filename == NULL) {
      throw IException("Invalid argument. filename is NULL.");
    }
    Pair<wchar_t*,  GUID> format[] = {
        
      {L".bmp", GUID_ContainerFormatBmp},
      
      {L".png", GUID_ContainerFormatPng},
      {L".ico", GUID_ContainerFormatIco},
      {L".jpg", GUID_ContainerFormatJpeg},
      {L".jpeg", GUID_ContainerFormatJpeg},
      {L".gif", GUID_ContainerFormatGif},
      {L".tif", GUID_ContainerFormatTiff},
      {L".tiff", GUID_ContainerFormatTiff},
      {L".wmp", GUID_ContainerFormatWmp},
    };
    GUID guid = GUID_ContainerFormatPng;
    bool found = false;
    for (int i = 0; i<CountOf(format); i++) {
      if (StringT<wchar_t>::endsWithIgnoreCase(filename, format[i].first)) {
        guid = format[i].second;
        found = true;
        break;
      }
    }
    if (found) {
      return guid;
    } else {
      throw IException("Invalid file type.");
    }
  }
  
private:
  WICStream*       stream;
  
public:
  WICBitmapFileWriter(IWICImagingFactory* factory, const wchar_t* filename)
  :WICBitmapEncoder(factory, formatGuid(filename), NULL),
  stream(NULL)
  {
    stream = new WICStream(factory);
    stream -> initializeFromFilename(filename, GENERIC_WRITE);
    this -> initialize(*stream, WICBitmapEncoderNoCache); 
  }
  
  ~WICBitmapFileWriter()
  {
    delete stream;
  }
  
  bool write(IWICBitmap* pWICBitmap)
  {
    bool rc = false;
    WICBitmapFrameEncode* frame   = NULL;

    WICFormatConverter* converter = NULL;  

    WICPixelFormatGUID format = GUID_WICPixelFormatDontCare;
    UINT width = 0;
    UINT height = 0;
    pWICBitmap ->GetSize(&width, &height);
    try {
      frame = new WICBitmapFrameEncode(*this);// = NUL
      frame -> initialize(NULL); 
      frame -> setSize(width, height);
      frame -> setPixelFormat(&format);

      frame -> writeSource(pWICBitmap, NULL);
    
      frame -> commit();
      this  -> commit();
      rc = true;
    } catch (Exception& ex) {
      ex.display(); 
    }
    delete frame;
    delete converter;
    return rc;
  }
};

}

