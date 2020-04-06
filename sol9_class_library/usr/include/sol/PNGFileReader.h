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
 *  PNGFileReader.h
 *
 *****************************************************************************/

// 2015/07/22 This is a very simple PNG file reader based on libpng.
// See https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures 

#pragma once

#include <sol/PNGFile.h>
#include <sol/Pair.h>

namespace SOL {

class PNGFileReader :public PNGFile {
  
public:
  PNGFileReader(const char* filename, bool deleteData=true)
  :PNGFile(READ, filename, deleteData)
  {
  }

  ~PNGFileReader()
  {
  }

public:
  void read(bool flipVertical = false) 
  {
    if (validateSignature() == false) {
      throw IException("Invalid header");
    }

    // Set the header signature bytes.
    setSignatureBytes(SIGNATURE_SIZE);

    // Read a png_info. 
    readInfo();

    // Get the png_info header withoud interlaceMethod, 
    // compressionMethod and filterMethod. 
    png_uint_32 width = 0;
    png_uint_32 height = 0;
    int bitDepth = 0;
    int colorType = 0;

    getInfoHeader(width, height, bitDepth, colorType);

    //setBackground();

    expandPalette();

    // Update the png_info
    updateInfo();

    // Get a row bytes.
    int rowbytes = getRowBytes();
    
    // Allocate a row_pointers. 
    png_bytep* rows = new png_bytep[height];

    // Allocate an imageData 
    png_byte* imageData = new png_byte[rowbytes * height];

    setImageData(imageData);

    // Set the rows pointer from the imageData 
    for (size_t i = 0; i < height; ++i) {
      if (flipVertical) {
        rows[height - 1 - i] = imageData + i * rowbytes;
      } else {
        rows[i] = imageData + i * rowbytes;
      }
    }

    // Read the imageData into the rows.
    readImage(rows);

    readEnd();

    delete [] rows;

    close();
  }

  void readInfo()
  {
    if (setJump()) {
      throw IException("Failed to png_read_info.");
    }
    png_read_info(png_ptr, info_ptr);
  }

  // Get png_info header withoud interlaceMethod, compressionMethod and filterMethod.
  int getInfoHeader(png_uint_32& width, png_uint_32& height,
        int& bitDepth, int& colorType)
  {
    if (setJump()) {
      throw IException("Failed to png_get_IHDR.");
    }

    return png_get_IHDR(png_ptr, info_ptr, &width, &height,
           &bitDepth, &colorType,
           NULL, NULL, NULL);
  }

  // Get png_info header
  int getInfoHeader(png_uint_32& width, png_uint_32& height,
        int& bitDepth, int& colorType, int& interlaceMethod,
        int& compressionMethod, int& filterMethod)
  {
    if (setJump()) {
      throw IException("Failed to png_get_IHDR.");
    } 
    return png_get_IHDR(png_ptr, info_ptr, &width, &height,
           &bitDepth, &colorType,
           &interlaceMethod, &compressionMethod, &filterMethod);
  }

 // Read the png into imageData
  void readImage(png_bytep* rows)
  {
    if (setJump()) {
      throw IException("Failed to png_read_image.");
    }

    png_read_image(png_ptr, rows);
  }

  void  readEnd()
  {
    if (setJump()) {
      throw IException("Failed to png_read_end.");
    }
    png_read_end(png_ptr, NULL);
  }

  void setFilter(int method, int filters)
  {
    if (setJump()) {
      throw IException("Failed to png_set_filter.");
    }
    png_set_filter(png_ptr, method, filters);
  }

  void properties()
  {
     printf("width:      %d\n", (int)getImageWidth()); 
     printf("height:     %d\n", (int)getImageHeight()); 
     printf("depth:      %d\n", (int)getBitDepth()); 
     printf("colorType:  %s\n", colorTypeToString(getColorType() )); 
  }

  const char* colorTypeToString(int type)
  {
     static Pair<int, const char*> pairs[] = {
      {PNG_COLOR_TYPE_GRAY,        "PNG_COLOR_TYPE_GRAY"},
      {PNG_COLOR_TYPE_GRAY_ALPHA,  "PNG_COLOR_TYPE_GRAY_ALPHA"},
      {PNG_COLOR_TYPE_PALETTE,     "PNG_COLOR_TYPE_PALETTE"},
      {PNG_COLOR_TYPE_RGB,         "PNG_COLOR_TYPE_RGB"},
      {PNG_COLOR_TYPE_RGB_ALPHA,   "PNG_COLOR_TYPE_RGB_ALPHA"},
      {PNG_COLOR_MASK_PALETTE,     "PNG_COLOR_MASK_PALETTE"},
      {PNG_COLOR_MASK_COLOR,       "PNG_COLOR_MASK_COLOR"},
      {PNG_COLOR_MASK_ALPHA,       "PNG_COLOR_MASK_ALPHA"},
    };
    const char* name = "";
    for (int i = 0; i<CountOf(pairs); i++) {
      if (pairs[i].first == type) {
        name = pairs[i].second;
        break;
      }
    } 
    return name;
  }
};
}

