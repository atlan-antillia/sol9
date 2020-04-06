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
 *  JPGFileReader.h
 *
 *****************************************************************************/


#pragma once

// See https://github.com/LuaDist/libjpeg/blob/master/example.c

#include <sol/JPGFile.h>

namespace SOL {

class JPGFileReader :public JPGFile {
private:

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;

  int width;
  int height;
  int rowBytes;
  int depth;

  bool deleteImageData;
  unsigned char* data;

public:
  //2016/10/16
  
  JPGFileReader(const char* filename, bool deleteData=true)
  :JPGFile(READER, filename),
  width(0),
  height(0),
  rowBytes(0),
  depth(0),
  deleteImageData(deleteData),
  data(NULL)
  {
    memset(&cinfo, 0, sizeof(cinfo));
    memset(&jerr,  0, sizeof(jerr));

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);

    FILE* fp = getFP();
    jpeg_stdio_src(&cinfo,  fp);
  }

  ~JPGFileReader()
  {
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    //2016/10/16
    if (deleteImageData) {
      delete [] data;
      data = NULL;
    }
  }

  int getImageWidth()
  {
    return width;
  }

  int getImageHeight()
  {
    return height;
  }

  int getDepth()
  {
    return depth;
  }

  unsigned char* getImageData()
  {
    return data;
  }

  int getRowBytes()
  {
    return rowBytes;
  }
  
public:
  int read()
  {
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    width = cinfo.output_width;
    height = cinfo.output_height;
    printf("width %d height %d\n", width, height);
    rowBytes = width * 4;
    
    data = new unsigned char [width*height*4];
    unsigned char* ptr = data;

    int row_stride = width * cinfo.output_components ;
    JSAMPARRAY pJpegBuffer = 
       (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, 
                   JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height) {
      unsigned char a,r,g,b;

      jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
      for (int x=0; x < width; x++) {
        a = 0; 
        r = pJpegBuffer[0][cinfo.output_components*x];

        if (cinfo.output_components>2) {
          g = pJpegBuffer[0][cinfo.output_components*x+1];
          b = pJpegBuffer[0][cinfo.output_components*x+2];
        } else {
          g = r;
          b = r;
        }
       *(ptr++) = b;
       *(ptr++) = g;
       *(ptr++) = r;
       *(ptr++) = a;
     }
   }

   depth = 32;
   return 0;
  }
};

}
 
