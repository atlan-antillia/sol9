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
 *  PNGFileWriter.h
 *
 *****************************************************************************/

// 2015/07/22 This is a very simple PNG file writer based on libpng.
// 2015/08/22 Fixed some bugs and, added write method.

#pragma once

#include <sol/PNGFile.h>

namespace SOL {

class PNGFileWriter :public PNGFile {
public:
  //2015/08/20 Modified
  PNGFileWriter(const char* filename, bool deleteData=true)
  :PNGFile(WRITE, filename, deleteData)
  {
  }

  ~PNGFileWriter()
  {
  }


  void writeInfo()
  {
    if (setJump()) {
      throw IException("Failed to write info-header");
    }
    png_write_info(png_ptr, info_ptr);
  }

  // Set png_info header
  void setInfoHeader(png_uint_32 width, png_uint_32 height,
        int bitDepth, int colorType, int interlaceMethod,
        int compressionMethod, int filterMethod)
  {
    if (setJump()) {
      throw IException("Failed to write a png header");
    }
    png_set_IHDR(png_ptr, info_ptr, width, height,
           bitDepth, colorType,
           interlaceMethod, compressionMethod, filterMethod);
  }

 // Write imageData through rows 
  void writeImage(png_bytep* rows)
  {
    if (setJump()) {
      throw IException("Failed to write image data");
    }
    png_write_image(png_ptr, rows);
  }

  void  writeEnd()
  {
    if (setJump()) {
      throw IException("Failed to write end.");
    }
    png_write_end(png_ptr, NULL);
  }

  //2015/08/20 Added this write method based on the lpng1617\example.c
  //(bitDepth takes one of the values 1, 2, 4, 8 and 16.

  void write(png_uint_32 width, png_uint_32 height,
        int bitDepth, 
        int channels,
        unsigned char* data,

        bool vertFlip = true,
        int colorType =  PNG_COLOR_TYPE_RGBA,
        int interlaceMethod = PNG_INTERLACE_NONE,
        int compressionMethod = PNG_COMPRESSION_TYPE_BASE,
        int filterMethod = PNG_FILTER_TYPE_BASE)
  {
    if (data == NULL) {
      throw IException("Invalid argument: data is NULL");
    }
  
    if (width <=0 || height <= 0) {
      throw IException("Invalid argument; widht or height is <=0");
    }

    //set info header
    setInfoHeader(width, height,
                     bitDepth, colorType, 
                   interlaceMethod, 
                     compressionMethod, filterMethod);

    setPalette();
    
    setPacking();

    
    //write info
    writeInfo();
    
    png_bytep* rows = (png_bytep*) new png_bytep[height];
    for (int i = 0; i<height; i++) {
      if (vertFlip) {
        rows[height-i-1] = data + width * channels * i;
      } else {
         rows[i] = data + width * channels * i;
      }
    }
    
    //write rows
    writeImage(rows);

    delete [] rows;

   //write end  
    writeEnd();
  }



};
}

