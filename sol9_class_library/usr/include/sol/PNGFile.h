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
 *  PNGFile.h
 *
 *****************************************************************************/

//2015/07/22
//2015/08/22 Added setJump method.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

#include <png.h>
#include <pngstruct.h>
#include <pnginfo.h>

//2016/10/16 Added the following two lines.
#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "zlib.lib")

namespace SOL {

class PNGFile :public Object {
  
protected:
  static const int SIGNATURE_SIZE = 8;

protected:
  typedef enum {
    READ  = 0,
    WRITE = 1,
  } OPERATION;

protected:
  png_structp png_ptr;
  png_infop   info_ptr;

private:
  FILE* fp;
  OPERATION operation;
  png_byte signature[SIGNATURE_SIZE];

  bool     deleteImageData;
  png_byte* imageData;
  size_t     imageDataSize;
private:
  PNGFile()
  :png_ptr(NULL),
   info_ptr(NULL),
   fp(NULL),
   deleteImageData(false),
   imageData(NULL),
  imageDataSize(0)
  {
    //This constructor will prohibit an instantiation outside this class. 
  }

protected:
  PNGFile(OPERATION operation, const char* filename, bool deleteData)
  :png_ptr(NULL),
   info_ptr(NULL),
   fp(NULL),
   operation(operation),
   deleteImageData(deleteData),
   imageData(NULL),
  imageDataSize(0)
  {
    if (filename == NULL) {
      throw IException("Invalid argument");
    }
    static const char* mode[] =  { "rb", "wb" };

    if (operation == READ) {
      if (exists(filename)) {
        errno_t err = fopen_s(&fp, filename, mode[operation]);
        if (err != 0) {
          throw IException("Faield to open file:%s", filename);
        }
      } else {
          throw IException("File not found %s", filename);
      }  
      // Create png_read struct
      png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
        NULL, NULL);
      if (png_ptr == NULL) {
        throw IException("Failed to png_create_read_struct");
      }
    } 
    if (operation == WRITE) {
      errno_t err = fopen_s(&fp, filename, mode[operation]);
      if (err != 0) {
        throw IException("Faield to open file:%s", filename);
      }
      // Create png_write_struct
      png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL,
         NULL, NULL);
      if (png_ptr == NULL) {
        throw IException("Failed to png_create_write_struct");
      }
    }
    
    //Create png_info_struct
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
      throw IException("Failed to png_create_info_struct");
    }
    
    memset(signature, 0, sizeof(signature));
  
    //Initialize reader or writer.
    initIO(); //2015/08/22
  }

public:
  ~PNGFile()
  {
    png_structpp pngpp = NULL;
    if (png_ptr) {
      pngpp = &png_ptr;
    }

    png_infopp infopp = NULL;
    if (info_ptr) {
      infopp = &info_ptr;
    }

    if (operation == READ) {
      png_destroy_read_struct(pngpp, infopp, NULL);
    }

    if (operation == WRITE) {
      png_destroy_write_struct(pngpp, infopp);
    }

    png_ptr  = NULL;
    info_ptr = NULL;

    if (deleteImageData) {
      delete [] imageData;
      imageData = NULL;
    }
    
    close();
  }

  void close()
  {
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
  }

  bool exists(const char* filename)
  {
    bool rc = false;
    struct _stat sts;
    int r = _stat(filename, &sts);
    if (r == -1 && errno == ENOENT) {
        rc = false;
    } else {
      rc = true;
    }
    return rc;
  }

  FILE* getFP()
  {
    return fp;
  }

  const char* version()
  {
    //return PNG_LIBPNG_VER_STRING;
    return PNG_HEADER_VERSION_STRING;
  }

  //2015/08/22
  int setJump() 
  {
    return setjmp(png_jmpbuf(png_ptr));
  }
    
  void initIO()
  {
    assert(fp);
    assert(png_ptr);
    if (setJump()) {
      throw IException("Failed to init_io");
    }
    png_init_io(png_ptr, fp);
  }

  void  setSignature()
  {
    //http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html
    png_byte sig[SIGNATURE_SIZE] = 
        {0x89, 0x50,  0x4e,  0x47,  0x0d, 0x0a, 0x1a, 0x0a};
    memcpy(signature, sig, sizeof(sig));
  }

  png_byte* getSignature()
  {
    return signature;
  }

  void   setImageData(png_byte* data)
  {
    if (data) {
      if (imageData) {
        delete [] imageData;
      }
      imageData = data;
    }
  }

  png_byte* getImageData()
  {
    return imageData;
  }
 
  bool validateSignature()
  {
    bool rc = false;
    size_t hsize = sizeof(signature);

    size_t len = fread(signature, 1, sizeof(signature), fp);
    if (len == hsize) {
      
      if (png_sig_cmp(signature, 0, sizeof(signature)) == 0) {
        rc = true;
      }
    }
    return rc;
  }

  
  void setSignatureBytes(size_t size)
  {
    assert(png_ptr);
    if (setJump()) {
      throw IException("Failed to png_set_sig_bytes.");
    }
    png_set_sig_bytes(png_ptr, size);
  }

  int getImageWidth()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_image_width.");
    }

    return png_get_image_width(png_ptr, info_ptr);
  }
  
  size_t getImageDataSize()
  {
    return imageDataSize;
  }

  void setImageDataSize(size_t size)
  {
    imageDataSize = size;
  }
  
  int getImageHeight()
  {
    assert(png_ptr);
    assert(info_ptr);
    return png_get_image_height(png_ptr, info_ptr);
  }

  int getColorType()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_get_color_types.");
    }
    return png_get_color_type(png_ptr, info_ptr);
  }

  int getBitDepth()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_get_bit_depth");
    }

    return png_get_bit_depth(png_ptr, info_ptr);
  }

  int getChannels()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_get_channels.");
    }

    return png_get_channels(png_ptr, info_ptr);
  }

  void updateInfo()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_read_update_info.");
    }

    png_read_update_info(png_ptr, info_ptr);
  }

  int getRowBytes()
  {
    assert(png_ptr);
    assert(info_ptr);
    if (setJump()) {
      throw IException("Failed to png_get_rowbytes.");
    }
    
    return png_get_rowbytes(png_ptr, info_ptr);
  }

  void setFilter(int method, int filters)
  {
    assert(png_ptr);
    if (setJump()) {
      throw IException("Failed to png_set_filter.");
    }
    png_set_filter(png_ptr, method, filters);
  }

  void setBGR()
  {
    assert(png_ptr);
    if (setJump()) {
      throw IException("Failed to png_set_bgr.");
    }
    png_set_bgr(png_ptr);
  }

  void setBackground()
  {
    assert(png_ptr);
    assert(info_ptr);
 
    png_set_bgr(png_ptr);

    const double screen_gamma = 2.2;

    double image_gamma = 0.0;
    png_color_16p background;

    int intent;
    if (setJump()) {
      throw IException("Failed to png_set_gamma.");
    }

     if (png_get_sRGB(png_ptr, info_ptr, &intent)) {
         png_set_gamma(png_ptr, screen_gamma, 0.45455 );
     } else if( png_get_gAMA(png_ptr, info_ptr, &image_gamma)) {
         png_set_gamma(png_ptr, screen_gamma, image_gamma );
     }

     if ((getColorType() & PNG_COLOR_MASK_ALPHA )
          || png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
          if (setJump()) {
             throw IException("Failed to png_set_background.");
          }

          if( png_get_bKGD(png_ptr, info_ptr, &background)) {
             png_set_background(png_ptr, background,
                                     PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
         } else {
             png_color_16 background = {0, 0, 0, 0};
             png_set_background(png_ptr, &background,
                                     PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
         }
     }
  }


/*
typedef struct png_color_16_struct
{
    png_byte index;
    png_uint_16 red;
    png_uint_16 green;
    png_uint_16 blue;
    png_uint_16 gray;
} png_color_16;
*/
  
  int getBackground(unsigned char& red, unsigned char& green, unsigned char& blue)
  {
    assert(png_ptr);
    assert(info_ptr);

    int depth = info_ptr -> bit_depth ; 
    int colorType =  info_ptr->color_type;

    png_color_16p background;

    png_get_bKGD(png_ptr, info_ptr, &background);

   if (depth == 16) {
        red   = background->red   >> 8;
        green = background->green >> 8;
        blue  = background->blue  >> 8;
    } else if (colorType == PNG_COLOR_TYPE_GRAY && depth < 8) {

      //COLOR_TYPE is GRAY
      if (depth == 1) {
        red = green = blue = background->gray? 255 : 0;
      }
      else if (depth == 2)  {
        red = green = blue = (255/3) * background->gray;
      }
      else { // depth == 4
        red = green = blue = (255/15) * background->gray;
      }
    } else {
      red   = (unsigned char)background->red;
      green = (unsigned char)background->green;
      blue  = (unsigned char)background->blue;
    }
    return 0;
  }

  void expandPalette()
  {
    assert(png_ptr);
    assert(info_ptr);
    int color_type = getColorType();
    int bit_depth  = getBitDepth();

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_expand(png_ptr);
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);

  }
  
  void setPacking()
  {
   if (setJump()) {
      throw IException("Failed to png_set_packing.");
    }
 
    png_set_packing(png_ptr);
  }
  
  void setPalette()
  {
    png_colorp palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof(png_color));
    if (palette == NULL) {
      throw IException("Failed to png_color alloc");
    }
    
    if (setJump()) {
      throw IException("Failed to png_set_PLTE.");
    }
    png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);
  }
};

}



