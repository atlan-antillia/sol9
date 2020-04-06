/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DIBSection.h
 *
 *****************************************************************************/

// SOL++2000

// 2012/06/28 Added saveAs method.

#pragma once

#include <sol\GdiObject.h>
#include <sol\MemoryDC.h>
#include <sol\BinaryFile.h>
#include <sol\gdiplus\ImageTransformer.h>

namespace SOL {

class DIBSection :public GdiObject {

//private:
protected:
  
  MemoryDC  memDC;
  HBITMAP    hbitmap;
  HBITMAP    hprevBitmap;
  unsigned char*  buffer;

  BITMAPINFO*  bi;
  int      bitCount;
  int      bmiSize;

  int      sx;
  int      sy;
  int      ratio;    //Stretching ratio in % unit.
  DWORD    operation;  //Raster operation

  int      colorCount;

private:
  HBITMAP create(DC& dc) 
  {
    if (bi == NULL) {
      return NULL;
    }

    HDC hdc = dc.get();
    
    HDC cdc = ::CreateCompatibleDC(hdc);
    
    memDC.set(cdc);

    int width  = bi->bmiHeader.biWidth;
    int height = bi->bmiHeader.biHeight ;
  
    //Printf("DIBSection::create  bitCount %d\r\n", bitCount);
  
    buffer    = NULL;

    hbitmap = ::CreateDIBSection(cdc, bi,
          DIB_RGB_COLORS, (void**)&buffer, NULL, 0);

    if (hbitmap && buffer) {
      hprevBitmap = (HBITMAP)memDC.select(hbitmap);
    } else {
      destroy();
      MessageBox(NULL, _T("Failed to create DIBSection"), _T("SOL++ Fatal Error"),
      MB_OK);
    }

    return hbitmap;
  }

  unsigned char getColorIndex(COLORREF color)
  {
    unsigned char index = 0;

    if (bitCount <16) {

      if (bi && hbitmap ) {

        RGBQUAD* rgb = bi->bmiColors;

        for(int i = 0; i<colorCount; i++) {
          if (color == RGB(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue)) {
            index = (unsigned char)i; //2000/11/18
            break;
          }
          rgb++;
        }
      }
    }
    return index;
  }


  RGBTRIPLE* getRGBTriple(int x, int y)
  {
    unsigned char* triple = NULL;

    int width  = getWidth();
    int height = getHeight();
  
    if (bitCount == 24 && width >0 && height > 0) {
      
      if (buffer && x >= 0 && x <width &&
        y >= 0 && y < height && hbitmap ) {

        unsigned char* tripleBuffer    = buffer;
      
        int dwLength = 0;
        int twidth = width * 3;
        if ( ((twidth) % 4) ==0) {
          dwLength = twidth;
        }
        else {
          dwLength = twidth + (4 - twidth % 4);
        }
      
        triple = (tripleBuffer + (height - y -1) * dwLength + x * 3);
        unsigned char* top = buffer + (height) * dwLength;

        if (triple >= top) {
          return NULL;
        }
      }
    }
    return (RGBTRIPLE*)triple;
  }


  WORD getColor(int x, int y)
  {
    WORD color = 0;
    int width  = getWidth();
    int height = getHeight();

    if (bitCount == 16 && width >0 && height > 0) {  
      if (buffer && x >= 0 && x <width &&
        y >= 0 && y <height && hbitmap ) {
      
        WORD* colorBuffer    = (WORD*)buffer;

        WORD* buff = colorBuffer + (height - y -1) * width + x;
        WORD* top  = colorBuffer + (height) * width;

        if (buff >= top) {
          return color;
        }
        color = *buff;
      }    
    }
    return color;
  }


  RGBQUAD* getRGBQuad(int x, int y) 
  {
    RGBQUAD* quad = NULL;

    if (bi == NULL || buffer == NULL || hbitmap == NULL) {
      return quad;
    }

    int width  = getWidth();
    int height = getHeight();

    if (width <= 0 || height <= 0) {
      return quad;
    }

    if (x <0 || x >= width || y <0 || y >= height) {
      return quad;
    }

    if (bitCount==32) {
      RGBQUAD* quadBuffer    = (RGBQUAD*)buffer;
      quad = quadBuffer + (height - y -1)*width + x;
      RGBQUAD* top = quadBuffer + (height)*width ;

      if (quad >= top) {
        return NULL;
      }
      return quad;
    }

    // Sorry, not implemented for case of bitCount = 16;

    if (bitCount == 8) {
      quad = NULL;
      
      int nwidth = width;
      nwidth = (nwidth + 3)/4 *4;

      unsigned char* buff = (buffer + (height- y -1) * nwidth + x);
      unsigned char* top  = buffer + (height) * nwidth;
    
      if (buff < top) {
        unsigned char index = *buff;
        if (index >=0 && index <colorCount) {
          RGBQUAD* rgbQuad = bi->bmiColors;
          if (rgbQuad) {
            quad = &rgbQuad[index];
          }
        }
      }
      return quad;
    }


    if (bitCount == 4) {
      quad = NULL;

      int nwidth = (width +7)/8 * 8;
      unsigned char* buff = buffer + ((height- y -1) * nwidth + x)/2;
      unsigned char* top  = buffer + (height ) * nwidth;

      if (buff >= top) {
        return quad;
      }

      unsigned char index = *buff;
          
      if ((x % 2) == 0) {
        index = (unsigned char)(index >>4);

      } else {
        index = (unsigned char)(index & 0xf);
      }

      if (index >=0 && index <colorCount) {
        RGBQUAD* rgbQuad = bi->bmiColors;
        if (rgbQuad) {
          quad = &rgbQuad[index];
        }
      }

      return quad;
    }
  
    return quad;
  }


  int getColorCount(BITMAPINFOHEADER* bi)
  {
    if (bi == NULL) {
      return 0;
    }

    if (bi->biClrUsed != 0) {
      return (int)bi->biClrUsed;
    }

    return getColorCount(bi->biBitCount);
  }



  int getColorCount(int bits)
  {
    switch (bits){
    case 1:
      return 2;
    case 4:
      return 16;
    case 8:
      return 256;
        default:
      break;
    }
    return 0;
  }


//
public:
  DIBSection()
  :GdiObject(NULL), 
  memDC(),
  hbitmap(NULL),
  hprevBitmap(NULL),
  bi(NULL), 
  buffer(NULL)
  { 
    sx      = 0;
    sy      = 0;
    ratio    = 100;    
    operation  = SRCCOPY;
    bitCount  = 32;
    bmiSize     = 0;
    colorCount  = 0;
    bmiSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorCount;
  }


public:
  DIBSection(DC& dc, int width, int height)
  :GdiObject(NULL), 
  memDC(dc), 
  hbitmap(NULL), 
  hprevBitmap(NULL),
  bi(NULL), 
  bmiSize(0),
  buffer(NULL)
{ 
    sx      = 0;
    sy      = 0;
    ratio    = 100;   
    operation  = SRCCOPY;
    bitCount    = 32;
    colorCount  = getColorCount(bitCount);

    bmiSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorCount;

    bi = (BITMAPINFO*)new char[bmiSize];
    memset(bi, 0, bmiSize);

    if (width > 0 && height > 0) {
  
      bi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
      bi->bmiHeader.biWidth       = width;
      bi->bmiHeader.biHeight      = height;
      bi->bmiHeader.biPlanes      = 1;
      bi->bmiHeader.biBitCount    = (WORD)bitCount; //2000/11/18
      bi->bmiHeader.biCompression = BI_RGB;

      //Printf("DIBSection::DIBSection(DC& dc, int width, int height, int count=%d\r\n",
      //  bitCount);

      hbitmap = ::CreateDIBSection(memDC.get(), bi,  
        DIB_RGB_COLORS, (void**)&buffer, NULL, 0);

      if (hbitmap && buffer) {
        hprevBitmap = (HBITMAP)memDC.select(hbitmap);
      
      } else {
        destroy();
        MessageBox(NULL, _T("Failed to create DIBSection"), _T("SOL++ Fatal Error"),
          MB_OK);
      }
    }
  }

public:
  ~DIBSection()
  {
    destroy();
  }

public:
  void draw(DC& dc, int x, int y)
  {
    draw(dc.get(), x, y);
  }

public:
  void draw(HDC hdc, int x, int y)
  {
    if(hbitmap) {
      int w = getWidth();
      int h = getHeight();
      ::StretchBlt(hdc,   x, y, w*ratio/100, h*ratio/100,
            memDC.get(), sx, sy, w, h, operation);
    }
  }

public:
  void destroy()
  {
    if (hbitmap) {
      memDC.select(hprevBitmap);

      DIBSECTION ds;
      ::GetObject(hbitmap, sizeof(ds), &ds);
      ::CloseHandle(ds.dshSection);
      ::DeleteObject(hbitmap);
      hbitmap = NULL;
      hprevBitmap = NULL;
    }

    char* tmp = (char*)bi;
    delete [] tmp;
    bi = NULL;

    buffer    = NULL;
  }

public:
  int getWidth() 
  {
    int w = 0;
    if (bi) {
      w = bi->bmiHeader.biWidth;
    }
    return w;
  }

public:
  int getHeight() 
  {
    int h = 0;
    if (bi) {
      h = bi->bmiHeader.biHeight;
    }
    return h;
  }

public:
  void  clear()
  {
    for(int y = 0; y<getHeight(); y++) {
      for(int x = 0; x<getWidth(); x++) {
        setPixel(x, y, RGB(255, 255, 255));
      }
    }

    flush();
  }


public:
  HBITMAP create(DC& dc, int width, int height, int bits=32)
  {
    if (width <=0 || height <= 0) {
      return NULL;
    }

    destroy();

    bitCount = bits; //24; //32;
    colorCount = getColorCount(bitCount);

    int  size = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorCount;

    bi = (BITMAPINFO*)new char[size];
    memset(bi, 0, size);
    
  //Printf("DIBSection::create/4 bitCount=%d\r\n", bitCount);

    memset(&(bi->bmiHeader), 0, sizeof(bi->bmiHeader));

    bi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);

    bi->bmiHeader.biWidth       = width;
    bi->bmiHeader.biHeight      = height;
    bi->bmiHeader.biPlanes      = 1;
    bi->bmiHeader.biBitCount    = (WORD)bitCount; //2000/11/18
    bi->bmiHeader.biCompression = BI_RGB;
  
    bi->bmiColors->rgbBlue     = 0;
    bi->bmiColors->rgbGreen    = 0;
    bi->bmiColors->rgbRed      = 0;
    bi->bmiColors->rgbReserved = 0;

    HDC hdc = dc.get();
    
    HDC cdc = ::CreateCompatibleDC(hdc);
    
    memDC.set(cdc);
    buffer     = NULL;

    hbitmap = ::CreateDIBSection(cdc, bi,
          DIB_RGB_COLORS, (void**)&buffer, NULL, 0);
    
    if (hbitmap && buffer) {
      hprevBitmap = (HBITMAP)memDC.select(hbitmap);
    } else {
      destroy();
      MessageBox(NULL, _T("Failed to create DIBSection"), _T("SOL++ Fatal Error"),
        MB_OK);
    }
    return hbitmap;
  }


public:
  DC&    getDC() { 
    return memDC; 
  }

  HBITMAP  getBitmap() { 
      return hbitmap; 
  }


public:
  COLORREF getPixel(int x, int y) 
  {  
    COLORREF color = 0;
    if (bitCount == 24) {
      RGBTRIPLE* triple = getRGBTriple(x, y);
      if (triple) {
        color = RGB(triple->rgbtRed, triple->rgbtGreen, triple->rgbtBlue);
      }
      return color;
    }

    // bitCount == 32, 8, 4
    RGBQUAD*  quad = getRGBQuad(x, y);
    color = 0;  
    if (quad) {
      color = RGB(quad->rgbRed, quad->rgbGreen, quad->rgbBlue);
    }
    return color;
  }

public:
  BOOL getPixel(int x, int y, int& r, int& g, int& b) 
  {
    BOOL  rc = FALSE;

    if (bitCount == 24) {
      RGBTRIPLE* triple = getRGBTriple(x, y);
      if (triple) {
        r  = triple->rgbtRed;
        g  = triple->rgbtGreen;
        b  = triple->rgbtBlue;
        rc = TRUE;
      } 
      return rc;    
    }

    RGBQUAD*  quad = getRGBQuad(x, y);
    if (quad) {
      r  = quad->rgbRed;
      g  = quad->rgbGreen;
      b  = quad->rgbBlue;
      rc = TRUE;
    }
    return rc;
  }

public:
  void DIBSection::setPixel(int x, int y, COLORREF color) 
  {
    if (bi == NULL || buffer == NULL || hbitmap == NULL) {
      return;
    }

    int width  = getWidth();
    int height = getHeight();

    if (width <= 0 || height <= 0) {
      return;  
    }

    if (x < 0 || x >=width || y <0 || y >= height) {
      return;
    }

    if (bitCount == 32) {
      RGBQUAD*  quad = getRGBQuad(x, y);
      if (quad) {
        quad->rgbRed   = GetRValue(color);
        quad->rgbGreen = GetGValue(color);
        quad->rgbBlue  = GetBValue(color);
      }
    }

    if (bitCount == 24) {
      RGBTRIPLE*  quad = getRGBTriple(x, y);
      if (quad) {
        quad->rgbtRed   = GetRValue(color);
        quad->rgbtGreen = GetGValue(color);
        quad->rgbtBlue  = GetBValue(color);
      }
    }
    // Sorry, not implemented for the cases of lower bitCount.
  }

  void  setOperation(DWORD op) { 
    operation = op; 
  }

  void  setSource(int x, int y) { 
    sx = x; sy = y; 
  }

  void   setStretchingRatio(int r) { 
    ratio = r; 
  }

public:
  BOOL load(DC& dc, const TCHAR* filename)
  {
    BinaryFile bmpFile;
    BOOL rc = FALSE;

    const int MAX_SIZE =  16000;
  
    if (bmpFile.openReadOnly(filename)) {
      char* fileHeader = new char[MAX_SIZE];
      bmpFile.read(0, fileHeader, MAX_SIZE);
    
      BITMAPFILEHEADER* fh = (BITMAPFILEHEADER*)fileHeader;
      DWORD offset = fh->bfOffBits;

      if(memcmp(fileHeader,"BM",2) != 0){
        return rc;
      }

      //Destroy previously loaded a bitmap image.
      destroy();

      int  n = sizeof(BITMAPFILEHEADER);

      BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)&fileHeader[n];
      colorCount = getColorCount(bih);

      bmiSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorCount;

      char* bmi = new char[bmiSize];
      memcpy(bmi, &fileHeader[n], bmiSize);

      bi = (BITMAPINFO*)bmi;  
    
      bitCount = bi->bmiHeader.biBitCount;
      long filesize = bmpFile.seek(0, FILE_END);
    
      long imageSize = filesize - fh->bfOffBits;
  
      //Printf("imageFile=[%s] filesize=[%d] bitCount=[%d]\r\n", filename, 
        //filesize, bitCount);
      //Printf("ImageSize = [%d]\r\n", filesize - fh->bfOffBits);
      //Printf("width %d height = %d size = %d sizeImage = %d\r\n",
      //  bi->bmiHeader.biWidth, bi->bmiHeader.biHeight,
      //  bi->bmiHeader.biSize,
      //  bi->bmiHeader.biSizeImage);

      if (create(dc) == NULL){
        delete [] fileHeader;
        return rc;
      }

      long readSize = 0;
      long restSize = imageSize;

      char* ptr = (char*)buffer;
      int    size = 32000;

      long  totalReadSize = 0;
    
      while(restSize> size) {    
        //Printf("ptr %d  offset = %d  RequestSize=[%d]  restSize=[%d]\r\n",
        //  ptr, offset, size, restSize);
        readSize  = bmpFile.read(offset, ptr,  size);
        offset   += readSize;
        ptr      += readSize;
        restSize -= readSize;

        if (readSize == 0) {
          break;
        }
        totalReadSize += readSize;
      }

      if (restSize > 0) {
        //Printf("Out ptr %d pos = %d  RequestSize=[%d]  rest=[%d]\r\n",
        //  ptr, offset, size, restSize);
        for(int i = 0; i<restSize; i++) {
          totalReadSize += bmpFile.read(offset++, ptr++, 1);
        }      
        //Printf("Out totalReadSize=[%d] rest=[%d]\r\n",
        //  totalReadSize, restSize);
      }

      delete [] fileHeader;

      rc = TRUE;
    
      flush();
    } 
    return rc;
  }

  int    getBitCount() { 
    return bitCount; 
  }

  int    getBmiSize() {
    return bmiSize; 
  }

  BITMAPINFO* getBitmapInfo() { 
    return bi; 
  }

  uchar* getBuffer()
  {
    return buffer;
  }
  
public:
  //2012/06/28
  bool saveAs(const TCHAR* filename)
  {
    bool rc = false;
    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromHBITMAP(hbitmap, NULL);
    if (bitmap) {
      if (bitmap-> GetLastStatus() == Gdiplus::Ok) {

        ImageTransformer transformer;
        rc = transformer.saveAs(bitmap, _bstr_t(filename));
      }
      delete bitmap;
    }
    return rc;
  }

};

}

