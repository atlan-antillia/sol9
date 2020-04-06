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
 *  AffineTransform.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.06.19
#pragma once

#include <sol\DC.h>

#include <sol\DIBSection.h>
#include <math.h>


/**
 * AffineTransform class.
 */
namespace SOL {

#define RADIAN(theta)  ((theta)*3.141592/180.0)

class AffineTransform :public Object {

private:

  // This is a typical linear-complement scheme.
  COLORREF AffineTransform::getNearestColor(DIBSection& dibs, double x1, double y1) 
  {
    int ix = (int)x1;
    int iy = (int)y1;

    if (x1 <=0) {
      ix = (int)(x1 - 1.0);
    }
    if ( y1 <=0) {
      iy = (int)(y1 - 1.0);
    }

    // Get colors of near lattice points for x1 and y1.
    COLORREF c1 = dibs.getPixel(ix,   iy  );
    COLORREF c2 = dibs.getPixel(ix+1, iy  );
    COLORREF c3 = dibs.getPixel(ix,   iy+1);
    COLORREF c4 = dibs.getPixel(ix+1, iy+1);

    double deltax = x1 - ix;
    double deltay = y1 - iy;

    // Compute the nearest RGB values from c1, c2, c3 and c4.
    double r = (1.0 - deltay) * ((1.0 - deltax) * GetRValue(c1)
        + deltax * GetRValue(c2) )
        + deltay * ((1.0 - deltax) * GetRValue(c3)
        + deltax * GetRValue(c4) );

    double g = (1.0 - deltay) * ((1.0 - deltax) * GetGValue(c1)
        + deltax * GetGValue(c2) )
        + deltay * ((1.0 - deltax) * GetGValue(c3)
        + deltax * GetGValue(c4) );

    double b = (1.0 - deltay) * ((1.0 - deltax) * GetBValue(c1)
        + deltax * GetBValue(c2) )
        + deltay * ((1.0 - deltax) * GetBValue(c3)
        + deltax * GetBValue(c4) );

    return RGB((int)r, (int)g, (int)b);
  }

public:
  AffineTransform() { }

public:
  ~AffineTransform() { }

public:
  DIBSection* translate(DC& dc, DIBSection& dibs, int dx, int dy)
  {
    int w = dibs.getWidth();
    int h = dibs.getHeight();

    DIBSection* image = new DIBSection(dc, w, h);

    for(int y = 0; y<h; y++) {
      for(int x = 0; x<w; x++) {
        COLORREF color = dibs.getPixel(x, y);
        image->setPixel(x + dx, y + dy, color);
      }
    }
    return image;
  }

  // Note: -90.0 <= angle <= 90.0
  DIBSection*  AffineTransform::rotate(DC& dc, DIBSection& dibs, double theta)
  {
    DIBSection* image = NULL;

    int angle = (int)theta;

    if (angle == 0 || angle == 360 || angle == -360) {
      return image;
    }

    if (theta >360.0 || theta < -360.0) {
      return image;
    }

    int w = dibs.getWidth();
    int h = dibs.getHeight();

    if (theta <0.0) {
      theta = 360.0 +theta;
    }

    double rad = RADIAN(theta);
    double s = sin(rad);
    double c = cos(rad);
  

    // 
    if (theta >=0.0 && theta <= 90.0) {
      int w1 = (int) ((double)w * cos(rad));
      int w2 = (int) ((double)h * sin(rad));
      int h1 = (int) ((double)w * sin(rad));
      int h2 = (int) ((double)h * cos(rad));
    
      image = new DIBSection(dc, (w1 + w2+1), h1 + h2+1);
    
      for(int y = -h1; y <= h2; y++) {
        for(int x = 0; x<= w1 + w2; x++) {
          double y1 = (double)x * s + (double)y * c;
          double x1 = (double)x * c - (double)y * s;
          COLORREF color = getNearestColor(dibs, x1, y1);
          image->setPixel(x, y+h1, color);
        }
      }
    }

    // 
    if (theta > 90.0 && theta <= 180.0) {
      rad = RADIAN(180.0) - rad;
      int w1 = (int) ((double)w * sin(rad));
      int w2 = (int) ((double)h * cos(rad));
      int h1 = (int) ((double)h * sin(rad));
      int h2 = (int) ((double)w * cos(rad));

      image = new DIBSection(dc, w1 + w2+1, h1 + h2+1);
  
      for(int y = -h1-h2; y <= 0; y++) {
        for(int x = -w2; x<= w1; x++) {
          double y1 = (double)x * s + (double)y * c;
          double x1 = (double)x * c - (double)y * s;
          COLORREF color = getNearestColor(dibs, x1, y1);
          image->setPixel(x+w2, y+h1+h2, color);
        }
      }
    }

    // 
    if (theta > 180.0 && theta <= 270.0) {
      rad = RADIAN(270.0) - rad;
      int w1 = (int) ((double)h * sin(rad));
      int w2 = (int) ((double)w * cos(rad));
      int h1 = (int) ((double)w * sin(rad));
      int h2 = (int) ((double)h * cos(rad));

      DIBSection* image = new DIBSection(dc, w1 + w2+1, h1 + h2+1);
    
      for(int y = -h1; y <= h2; y++) {
        for(int x = -w1-w2; x<= 0; x++) {
          double y1 = (double)x * s + (double)y * c;
          double x1 = (double)x * c - (double)y * s;
          COLORREF color = getNearestColor(dibs, x1, y1);
          image->setPixel(x+w1+w2, y+h1, color);
        }
      }
    }

    // 
    if (theta > 270.0 && theta <= 360.0) {
      rad = RADIAN(360.0) - rad;
      int w1 = (int) ((double)h * sin(rad));
      int w2 = (int) ((double)w * cos(rad));
      int h1 = (int) ((double)w * sin(rad));
      int h2 = (int) ((double)h * cos(rad));

      DIBSection* image = new DIBSection(dc, w1 + w2+1, h1 + h2+1);
  
      for(int y = 0; y <= h1+h2; y++) {
        for(int x = -w1; x<= w2; x++) {
          double y1 = (double)x * s + (double)y * c;
          double x1 = (double)x * c - (double)y * s;
          COLORREF color = getNearestColor(dibs, x1, y1);
          image->setPixel(x+w1, y, color);
        }
      }
    }

    return image;
  }

};

}

