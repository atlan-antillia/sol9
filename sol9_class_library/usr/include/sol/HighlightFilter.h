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
 *  HighlightFilter.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

// 2000.07.07
#include <sol\ImageFilter.h>

namespace SOL {

#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#define Min(a,b)    (((a) < (b)) ? (a) : (b))

class HighlightFilter :public ImageFilter {

private:
  int  percent;

private:
  void  brighten(int& r, int& g, int& b) 
  {
    r = r + (percent * r) / 100;
    g = g + (percent * g) / 100;
    b = b + (percent * b) / 100;

    r = Min(Max(0, r), 255);
    g = Min(Max(0, g), 255);
    b = Min(Max(0, b), 255);
  }
public:
  HighlightFilter(int p) 
  {
    if (p < 0 ) 
      p = 0;
    if (p > 100) 
      p = 100;

    percent = p;
  }

public:
  DIBSection* HighlightFilter::filterRGB(DC& dc, DIBSection& image) 
  {

    int w = image.getWidth();
    int h = image.getHeight();

    DIBSection* newImage = new DIBSection(dc, w, h);

    for (int y = 0; y<h; y++) {
      for (int x = 0; x<w; x++) {
        int r = 0;
        int g = 0;
        int b = 0;
        COLORREF c = image.getPixel(x, y, r, g, b);
        brighten(r, g, b);
        newImage->setPixel(x, y, RGB(r, g, b));
      }
    }
    return newImage;
  }

};

}



