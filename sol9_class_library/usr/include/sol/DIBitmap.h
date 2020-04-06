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
 *  DIBitmap.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once
#include <sol\GdiObject.h>
#include <sol\Palette.h>


typedef HANDLE HDIB;

namespace SOL {

class DIBitmap :public GdiObject {
private:
  int    sx, sy;
  int    width;
  int    height;
  int    colors;
  int    destroy;
  Palette* palette;

//  BOOL  createPalette(HDIB hdib);
private:
  BOOL createPalette(HDIB hdib)
  {
    LPBITMAPINFO lpbmi = (LPBITMAPINFO)::GlobalLock(hdib);

    if (colors >0) {
      HANDLE hLogPal = ::GlobalAlloc(GHND, 
          sizeof(LOGPALETTE) + sizeof(PALETTEENTRY)*colors);

      if (hLogPal == 0) {
        ::GlobalUnlock(hdib);
        return FALSE;
      }

      LPLOGPALETTE pal = (LPLOGPALETTE)::GlobalLock(hLogPal);

      pal->palVersion = 0x300;
      pal->palNumEntries = (WORD)colors;
  
      for (int i = 0; i < (int)colors; i++) {
      
/*
      Printf("red  [%3d] = %3d;\r\n", i, lpbmi->bmiColors[i].rgbRed);
      Printf("green[%3d] = %3d;\r\n", i, lpbmi->bmiColors[i].rgbGreen);
      Printf("blue [%3d] = %3d;\r\n", i, lpbmi->bmiColors[i].rgbBlue);
      Printf("\t{%3d, %3d, %3d},  // %3d\r\n",
        lpbmi->bmiColors[i].rgbRed,
        lpbmi->bmiColors[i].rgbGreen,
        lpbmi->bmiColors[i].rgbBlue,
        i
        );
*/
        pal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
        pal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
        pal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
        pal->palPalEntry[i].peFlags = 0;
      }    
      palette = new Palette(pal);
      ::GlobalUnlock(hLogPal);
      ::GlobalFree(hLogPal);
    }
    ::GlobalUnlock(hdib);

    return TRUE;
  }

public:
  DIBitmap(const TCHAR* name, HDIB hdib, int w, int h, 
           int ncolors)
  :GdiObject(name, hdib),
  palette(NULL)
  {
    sx = sy = 0;

    width     = w;
    height    = h;
    colors    = ncolors; 
    createPalette(hdib);
  }

public:
  ~DIBitmap()
  {
    if(palette) {
      delete palette;
    }
    HDIB hdib = (HDIB)get();
    ::GlobalUnlock(hdib);
    ::GlobalFree(hdib);
  }


public:
  void setSource(int x, int y)
  {
    sx = x;
    sy = y;
  }

public:
  void draw(HDC hdc, int x, int y)
  {
    HDIB    hdib    = (HDIB)get();
    if(hdib) {  
      LPSTR header = (LPSTR)::GlobalLock(hdib);
      LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)header;

      LPSTR bits= header + lpbmi->biSize +
        colors* sizeof(RGBQUAD);

      HPALETTE pal = ::SelectPalette(hdc, 
            (HPALETTE)palette->get(), TRUE);      
      ::RealizePalette(hdc);


      int width  = lpbmi->biWidth;
         int height = lpbmi->biHeight;
  
      ::SetDIBitsToDevice(hdc,         
            x,             
            y,             
            width, 
            height,
            sx, 
            0, 
            sy, // 0,              
            height,
            bits,   
            (LPBITMAPINFO)header,  
            DIB_RGB_COLORS);
      ::SelectPalette(hdc, pal, FALSE);
    }
  }

public:
  void draw(DC& dc, int x, int y)
  {
    DIBitmap::draw(dc.get(), x, y);

  }

  void  getSize(int& w, int& h) { w=width; h=height; }

  //  void  setSource(int x, int y);

  Palette* getPalette() { return palette; }

};

}

