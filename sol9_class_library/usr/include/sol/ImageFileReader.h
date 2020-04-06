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
 *  ImageFileReader.h
 *
 *****************************************************************************/

//2016/10/20 This is a simple JPG and PNG imageFileReader.
// ImageInfo structure contains some information to draw the imageData in ImageInfo,
// You have to delete the imageData (BYTE*) in ImagInfo, when it is no longer needed,

 
#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <sol/PNGFileReader.h>
#include <sol/JPGFileReader.h>
#include <sol/ImageInfo.h>

//#include <dxgi1_4.h>

namespace SOL {

class ImageFileReader :public Object {

public:
  ImageFileReader()
  {
  }

  ImageFileReader(
    __in const char*  filename,
    __out ImageInfo&  imageInfo)
  {
    read(filename, imageInfo);
  }
  
  
  void read(
        __in  const char* filename, 
        __out ImageInfo&  imageInfo)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    
    if (String::endsWithIgnoreCase(filename, ".png")) {
      readFromPNGFile(
              filename,
              imageInfo);

    } else if (String::endsWithIgnoreCase(filename, ".jpg")) {
      readFromJPGFile(
              filename,
              imageInfo);
    } else {
      ;//Unsupported file types
      throw IException("Invalid file types");  
    }
  }

  void readFromPNGFile(
          __in  const char* filename,
          __out ImageInfo&  imageInfo)
  {
    //As you know, in general, an image width or height must be the power of 2.
    PNGFileReader* reader = NULL;
    try {
      //Don not delete the image data read in by PNGFileReader.
      bool deleteImageData = false;
      PNGFileReader reader(filename, deleteImageData); 
      reader.version();
      reader.read();

      void* image = reader.getImageData(); 
      if (image) {
        
        int ctype = 0;
        reader.getInfoHeader(
          imageInfo.width, 
          imageInfo.height, 
          imageInfo.bitDepth, 
          ctype);

        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        if (ctype == PNG_COLOR_TYPE_RGB_ALPHA) {
          format = DXGI_FORMAT_R8G8B8A8_UNORM; //RGBA
        } else if (ctype == PNG_COLOR_TYPE_RGB) {
          format = DXGI_FORMAT_R8G8B8A8_SNORM; // RGB; DXGI_FORMAT_B8G8R8X8_UNORM
        }
        
        if (format == DXGI_FORMAT_UNKNOWN) {
          throw IException("Invali PNG file format.");
        }
        imageInfo.format = format;
        imageInfo.rowBytes = reader.getRowBytes();
        imageInfo.format = DXGI_FORMAT_R8G8B8A8_UNORM;;

        imageInfo.imageData = (BYTE*)image;
        imageInfo.imageDataSize = imageInfo.rowBytes * imageInfo.height;
        
      } else {
          throw IException("Image data is NULL");
      }
        
    } catch (Exception& ex) {
      ex.display();
    }
  }

 
  void readFromJPGFile(
          __in  const char* filename,
          __out ImageInfo&  imageInfo)
  {
    //As you know, in general, an image width or height must be the power of 2.
    try {
    
      //Do not delete the image data read in by JPGFileReader.
      bool deleteImageData = false;
      JPGFileReader reader(filename, deleteImageData); 
      reader.read();

      void* image = reader.getImageData(); 
      if (image) {
        imageInfo.width     = reader.getImageWidth(); 
        imageInfo.height    = reader.getImageHeight();
        imageInfo.rowBytes  = reader.getRowBytes();
        
        imageInfo.format = DXGI_FORMAT_B8G8R8A8_UNORM;// Blue Green Red Alpha
        imageInfo.bitDepth  = reader.getDepth();
        
        imageInfo.imageData = (BYTE*)image;
        imageInfo.imageDataSize = imageInfo.rowBytes * imageInfo.height;
        
      } else {
        throw IException("Image data is NULL");
      }
    } catch (Exception& ex) {
      ex.display();
    }
  }
};

}

