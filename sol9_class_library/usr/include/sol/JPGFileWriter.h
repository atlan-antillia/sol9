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
 *  JPGFileWriter.h
 *
 *****************************************************************************/

// 2015/08/22 Update write method to take a vertFlip parameter.
//  void write(int width, int height, int depth, unsigned char* data, int quality, bool vertFlip) 

#pragma once

#include <sol/JPGFile.h>

namespace SOL {

class JPGFileWriter :public JPGFile {

private:
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

public:
  JPGFileWriter(const char* filename)
  :JPGFile(WRITER, filename)
  {
    memset(&cinfo, 0, sizeof(cinfo));
    memset(&jerr, 0, sizeof(jerr));

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    FILE* fp = getFP();
    jpeg_stdio_dest(&cinfo, fp);
  }

  ~JPGFileWriter()
  {
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    close();
  }

public:
  //quality may take a value between 0 and 100.
  //2015/08/22 Updated
  void write(int width, int height, int depth, int channels, unsigned char* data, int quality, bool vertFlip) 
  {
    if (data == NULL) {
      throw IException("Invalid argument: data is NULL");
    }
    if (width <=0 || height <= 0) {
      throw IException("Invalid argument; widht or height is <=0");
    }
    
    cinfo.image_width  = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);
    printf("channels %d\n", channels);
    while (cinfo.next_scanline < cinfo.image_height) {
      JSAMPROW row;
      if (vertFlip) {
        row = (JSAMPROW) &data[(height - cinfo.next_scanline - 1) * channels * width];
      } else {
        row = (JSAMPROW) &data[cinfo.next_scanline * channels * width];
      }
      jpeg_write_scanlines(&cinfo, &row, 1);
    }
  }
};

}

