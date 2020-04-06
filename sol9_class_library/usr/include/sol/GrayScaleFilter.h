/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  GrayScaleFilter.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.07.07
#pragma once


#include <sol\Object.h>

#include <sol\ImageFilter.h>


namespace SOL {

class GrayScaleFilter :public ImageFilter {

public:
  GrayScaleFilter() { }

public:

  DIBSection* filterRGB(DC& dc, DIBSection& image)
  {
    int w = image.getWidth();
    int h = image.getHeight();
    DIBSection* grayImage = new DIBSection(dc, w, h);
  
    if (grayImage == NULL) {
      return NULL;
    }

    for(int y = 0; y < h; y++) {

      for (int x = 0; x < w; x++) {
        int r = 0;
        int g = 0;
        int b = 0;
        image.getPixel(x, y, r, g, b);

      /*
      int v = (int) (0.298912*(double)r + 0.586611*(double)g + 0.114478*(double)b);
        
      int  v = (2 * r + 4 * g + b)/7; 
      */

        // Much faster way.
        int  v = ((r<<1) + (g<<2) + b)/7; 

        grayImage->setPixel(x, y, RGB(v, v, v));
      }
    }
    return grayImage;
  }

};

}



