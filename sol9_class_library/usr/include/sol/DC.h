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
 *  DC.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.6.15 Added a new 'select' method, and moved 'set' method to a public section.
// 2008/09/15  Added the following method.
//  BOOL  getTextExtentPoint32(const TCHAR* string, int num, SIZE* size) {
// 2012/05/30 Added saveDC and restoreDC methods.

#pragma once

#include <sol\Object.h>
//#include <sol\Font.h>
//2009/11/04
#include <sol/IGdiObject.h>


namespace SOL {

class Font;

class DC :public Object {

  HDC  hdc;
 
public:
  DC() {
    hdc = NULL;
  }

  DC(HDC hdc1) {
    hdc = hdc1;
  }

  BOOL  arc(int x1, int y1, int x2, int y2, 
        int x3, int y3, int x4, int y4) {
      return ::Arc(hdc, x1, y1, x2, y2, x3, y3, x4, y4);
  }

  BOOL  chord(int x1, int y1, int x2, int y2, 
        int x3, int y3, int x4, int y4) {
      return ::Chord(hdc, x1, y1, x2, y2, x3, y3, x4, y4);
  }

  BOOL  toLP(POINT* pt, int num) {
      return ::DPtoLP(hdc, pt, num);
  }

  BOOL   drawEdge(LPRECT qrc, UINT edge, UINT grfFlags) {  
      return  ::DrawEdge(hdc,  qrc, edge,grfFlags);
  }

  BOOL   drawFrameControl(RECT* rect, UINT controlType, UINT controlStyle) {  
      return ::DrawFrameControl(hdc, rect, controlType, controlStyle);  
  }

  void  drawFocusRect(RECT* rect) {
      ::DrawFocusRect(hdc, rect);
  }

  int    drawText(const TCHAR* string, int num, RECT* rect, WORD format) {
      return ::DrawText(hdc, string, num, rect, format);
  }

  BOOL  ellipse(int x1, int y1, int x2, int y2) {
      return ::Ellipse(hdc, x1, y1, x2, y2);
  }

  int    enumFontFamilies(const TCHAR* family, FONTENUMPROC proc,
        LPARAM lParam) {
      return ::EnumFontFamilies(hdc, family, proc, lParam); 
  }

  int    enumFontFamilies(LOGFONT* logFont, FONTENUMPROC proc,
        LPARAM lParam, DWORD flags) {
      return ::EnumFontFamiliesEx(hdc,logFont, proc, lParam, flags); 
  }

  int    escape(int func, int count, const char* inData,TCHAR* outData) {
           return ::Escape(hdc, func, count, inData, outData);
  }

  BOOL  extFloodFill(int x, int y, COLORREF color, WORD type) {
      return ::ExtFloodFill(hdc, x, y, color, type);
  }

  BOOL  extTextOut(int x, int y, WORD option, RECT* rect,
          TCHAR* string, int num, int* dx) {
      return ::ExtTextOut(hdc, x, y, option, rect, string, num, dx);
  }

  BOOL  fillRect(RECT* r, HBRUSH hbr) {
      return ::FillRect(hdc, r, hbr);
  }

  BOOL  frameRect(RECT* r, HBRUSH hbr) {
      return ::FrameRect(hdc, r, hbr);
  }

  BOOL  floodFill(int x, int y, COLORREF color) {
      return ::FloodFill(hdc, x, y, color);
  }

  HDC    get() { return hdc; }

  //2012/06/22
  operator HDC(){
    return hdc;
  }

  int    getDeviceCaps(int indx) {
      return ::GetDeviceCaps(hdc, indx);
  }

  DWORD  getBkColor() { return ::GetBkColor(hdc); }

  int    getBkMode() { return ::GetBkMode(hdc); }

  BOOL  getBrushOrg(POINT* pt) { return ::GetBrushOrgEx(hdc, pt); }

  int    getClipBox(RECT* rect) {
      return ::GetClipBox(hdc, rect);
  }

  BOOL  getCurrentPosition(POINT* pt) { 
      return ::GetCurrentPositionEx(hdc, pt); 
  }

  int    getMapMode() { return ::GetMapMode(hdc); }

  DWORD  getNearestColor(COLORREF color) {
      return ::GetNearestColor(hdc, color);
  }

  DWORD  getPixel(int x, int y) {
      return ::GetPixel(hdc, x, y);
  }

  int    getPolyFillMode() { return ::GetPolyFillMode(hdc); }

  int    getROP2() { return ::GetROP2(hdc); }

  int    getStretchBltMode() {
      return ::GetStretchBltMode(hdc);
  }

  // 2000/11/18 to-arai: WORD -> UINT
  UINT  getSystemPaletteEntries(UINT indx, UINT num,
          PALETTEENTRY* entry) { 
      return ::GetSystemPaletteEntries(hdc, indx, num, entry);
  }
  DWORD  getTabbedTextExtent(const TCHAR* string, int num, int tabNum,
            int* tabPos) {
      return ::GetTabbedTextExtent(hdc, string, num, tabNum,
            tabPos);
  }
  // 2000/11/18 to-arai: WORD -> UINT
  UINT  getTextAlign() { return ::GetTextAlign(hdc); }

  DWORD  getTextColor() { return ::GetTextColor(hdc); }

  UINT  getTextCharsetInfo(LPFONTSIGNATURE sig) {
      return ::GetTextCharsetInfo(hdc, sig, 0);
  }

  BOOL  getTextExtent(const TCHAR* string, int num, SIZE* size) {
      return ::GetTextExtentPoint(hdc, string, num, size);
  }
  //2008/09/15
  BOOL  getTextExtentPoint32(const TCHAR* string, int num, SIZE* size) {
      return ::GetTextExtentPoint32(hdc, string, num, size);
  }

  int    getTextFace(TCHAR* buffer, int len) {
      return ::GetTextFace(hdc, len, buffer);
  }
  //2009/11/04
  int    getTextHeight(){
    SIZE size;
    getTextExtent(_T("A"), 1, &size);
    return size.cy;
  }

  BOOL  getTextMetrics(TEXTMETRIC* metrics) {
      return ::GetTextMetrics(hdc, metrics);
  }

  BOOL  getViewportExt(SIZE* size) { return ::GetViewportExtEx(hdc, size); }

  BOOL  getViewportOrg(POINT* pt) { return ::GetViewportOrgEx(hdc, pt); }

  BOOL  getWindowExt(SIZE* size) { return ::GetWindowExtEx(hdc, size); }

  BOOL  getWindowOrg(POINT* pt) { return ::GetWindowOrgEx(hdc, pt); }

  int    intersectClipRect(int x1, int y1, int x2, int y2) {
      return ::IntersectClipRect(hdc, x1, y1, x2, y2);
  }

  BOOL  invert(const RECT* rect) {
      return ::InvertRect(hdc, rect);
  }
  BOOL  invert(HRGN r) {
      return ::InvertRgn(hdc, r);
  }

  BOOL  isPtVisible(int x, int y) {
      return ::PtVisible(hdc, x, y);
  }
  BOOL  isRectVisible(const RECT* rect) {
      return ::RectVisible(hdc, rect);
  }

  BOOL  lineTo(int x, int y) { return ::LineTo(hdc, x, y); }

  BOOL  toDP(POINT* pt, int num) {
      return ::LPtoDP(hdc, pt, num);
  }

  BOOL  moveTo(int x, int y) {
       return ::MoveToEx(hdc, x, y, NULL);
  }
  BOOL  moveTo(int x, int y, POINT* pt) { 
      return ::MoveToEx(hdc, x, y, pt); 
  }

  BOOL  offsetViewportOrg(int x, int y, POINT* pt) { 
      return ::OffsetViewportOrgEx(hdc, x, y, pt);
  }
  BOOL  offsetWindowOrg(int x, int y, POINT* pt) { 
      return ::OffsetWindowOrgEx(hdc, x, y, pt);
  }

  DWORD  offsetClipRgn(int x, int y) { 
      return ::OffsetClipRgn(hdc, x, y);
  }

  BOOL  pie(int x1, int y1, int x2, int y2, 
        int x3, int y3, int x4, int y4) {
      return ::Pie(hdc, x1, y1, x2, y2, x3, y3, x4, y4);
  }

  //2012/06/28
  BOOL bitBlt(int x, int y, int cx, int cy, 
    HDC hdcSrc, int xSrc, int ySrc, DWORD rop)
  {
    return BitBlt(hdc, 
      x,  y, cx, cy, hdcSrc, xSrc, ySrc, rop);
  }
  
  BOOL stretchBlt(
      int destX,
      int destY, 
      int destWidth, 
      int destHeight,
      HDC hdcSrc, 
      int srcX, 
      int srcY, 
      int srcWidth, 
      int srcHeight, 
      DWORD dwRop)
  {
    return StretchBlt(hdc, destX, destY, destWidth, destHeight,
              hdcSrc, srcX, srcY, srcWidth, srcHeight, dwRop);
  }

  int stretchDIBits(
    int        xDest,
    int        yDest,
    int        destWidth,
    int        destHeight,
    int        xSrc,
    int        ySrc,
    int        srcWidth,
    int        srcHeight,
    const VOID       *lpBits,
    const BITMAPINFO *lpBitsInfo,
    UINT       iUsage,
    DWORD      dwRop)
  {
    return StretchDIBits(
            hdc,
            xDest,
            yDest,
            destWidth,
            destHeight,
            xSrc,
            ySrc,
            srcWidth,
            srcHeight,
            lpBits,
            lpBitsInfo,
            iUsage,
            dwRop);
  }

  int stretchDIBits(
    float        xDest,
    float        yDest,
    float        destWidth,
    float        destHeight,
    float        xSrc,
    float        ySrc,
    float        srcWidth,
    float        srcHeight,
    const VOID       *lpBits,
    const BITMAPINFO *lpBitsInfo,
    UINT       iUsage,
    DWORD      dwRop)
  {
    return StretchDIBits(
            hdc,
            (int)xDest,
            (int)yDest,
            (int)destWidth,
            (int)destHeight,
            (int)xSrc,
            (int)ySrc,
            (int)srcWidth,
            (int)srcHeight,
            lpBits,
            lpBitsInfo,
            iUsage,
            dwRop);
  }

// For Windows NT
  BOOL    maskBlt(int dx, int dy, int widht, int height,
         DC* srcDC, int sx, int sy,
         HBITMAP hbmMask, int xmask, int ymask, DWORD op) {
      return ::MaskBlt(hdc, dx, dy, widht, height,
         srcDC -> get(), sx, sy,
         hbmMask, xmask, ymask, op);
  }  

  BOOL    plgBlt(POINT* pt, DC* srcDC, int sx, int sy,
        int width, int height, HBITMAP hbmMask, 
        int xmask, int ymask) {
      return ::PlgBlt(hdc, pt, srcDC->get(), sx, sy,
      width, height, hbmMask, xmask, ymask);
  }  

  BOOL  polygon(POINT* pt, int num) {
      return ::Polygon(hdc, pt, num);
  }
  BOOL  polyline(POINT* pt, int num) {
      return ::Polyline(hdc, pt, num);
  }

  int    realizePalette() {
      return ::RealizePalette(hdc);
  }

  void  restore(int val) {
      ::RestoreDC(hdc, val);
  }

  BOOL  rectangle(int x1, int y1, int x2, int y2) {
      return ::Rectangle(hdc, x1, y1, x2, y2);
  }
  BOOL  roundRect(int x1, int y1, int x2, int y2, int x3, int y3) {
      return ::RoundRect(hdc, x1, y1, x2, y2, x3, y3);
  }
  int    save() {
      return ::SaveDC(hdc);
  }

  BOOL  scaleViewportExt(int xnum, int xdeno, int ynum, int ydeno, SIZE* size) {
      return ::ScaleViewportExtEx(hdc, xnum, xdeno, ynum, ydeno, size);
  }
  BOOL  scaleWindowExt(int xnum, int xdeno, int ynum, int ydeno, SIZE* size) {
      return ::ScaleWindowExtEx(hdc, xnum, xdeno, ynum, ydeno, size);
  }

  //<moved date="2000.06.15">
  void  set(HDC hdc1) { 
    hdc   = hdc1;
  }
  //</moved>

  DWORD  setBkColor(COLORREF color) { 
      return ::SetBkColor(hdc, color);
  }
  int    setBkMode(int mode) { return ::SetBkMode(hdc, mode); }

  BOOL  setBrushOrg(int x, int y, POINT* pt) { 
      return ::SetBrushOrgEx(hdc, x, y, pt); 
  }

  int    getGraphicsMode() {
      return ::GetGraphicsMode(hdc);
  }

  DWORD  getFontLanguageInfo() {
      return ::GetFontLanguageInfo(hdc);
  }
  DWORD  getFontData(DWORD table, DWORD offset, void* buffer,
        DWORD dataSize) {
      return ::GetFontData(hdc, table, offset, buffer, dataSize);
  }

  DWORD  setGraphicsMode(int mode) {
      return ::SetGraphicsMode(hdc, mode);
  }

  DWORD  setMapperFlags(DWORD flag) {
      return ::SetMapperFlags(hdc, flag);
  }

//  HPALETTE select(class Palette* palette, BOOL background);

  HPALETTE select(HPALETTE hpal, BOOL background) {
       return ::SelectPalette(hdc, hpal, background);
  }

  HGDIOBJ  select(IGdiObject* gdiObject) 
  {
    HGDIOBJ rc = NULL;
    if (gdiObject) {
      gdiObject -> set(this);
      rc = ::SelectObject(hdc, gdiObject->get());
    }
    return rc;
  }

  //<added date="2000.06.15">
  HGDIOBJ  select(IGdiObject& gdiObject) 
  {
    gdiObject.set(this);
    HGDIOBJ rc = ::SelectObject(hdc, gdiObject.get());
  
    return rc;
  }

  HGDIOBJ select(HGDIOBJ hgdiobj) {
      return ::SelectObject(hdc, hgdiobj);
  }

  int    setMapMode(int mode) {
      return ::SetMapMode(hdc, mode);
  }
  DWORD  setPixel(int x, int y, COLORREF color) {
      return ::SetPixel(hdc, x, y, color);
  }
  int    setPolyFillMode(int mode) {
      return ::SetPolyFillMode(hdc, mode);
  }
  int    setROP2(int mode) { 
      return ::SetROP2(hdc, mode); 
  }
  int    setStretchBltMode(int mode) {
      return ::SetStretchBltMode(hdc, mode);
  }
  int    setSystemPaletteUse(WORD usage) { 
      return ::SetSystemPaletteUse(hdc, usage);
  }
  // 2000/11/18 to-arai: WORD -> UINT
  UINT  setTextAlign(UINT flag) {
      return ::SetTextAlign(hdc, flag);
  }
  DWORD   setTextCharacterExtra(int extra) {
      return ::SetTextCharacterExtra(hdc, extra);
  }
  DWORD   setTextColor(COLORREF color) {
      return ::SetTextColor(hdc, color);
  }

  BOOL  setViewportExt(int x, int y, SIZE* size) {
      return ::SetViewportExtEx(hdc, x, y, size);
  }

  BOOL  setViewportOrg(int x, int y, POINT* pt) {
      return ::SetViewportOrgEx(hdc, x, y, pt);
  }
  BOOL  setWindowExt(int x, int y, SIZE* size) {
      return ::SetWindowExtEx(hdc, x, y, size);
  }

  BOOL  setWindowOrg(int x, int y, POINT* pt) {
      return ::SetWindowOrgEx(hdc, x, y, pt);
  }

  long  tabbedTextOut(int x, int y, const TCHAR* string, int num,
      int tabStopNum, int* tabStop, int origin) {
      return ::TabbedTextOut(hdc, x, y, string, num,
          tabStopNum, tabStop,  origin);
  }
  BOOL  textOut(int x, int y, const TCHAR* string, int num) {
      return ::TextOut(hdc, x, y, string, num);
  }
  int    updateColors() {
      return ::UpdateColors(hdc);
  }

  HWND  windowFromDC() {
      return ::WindowFromDC(hdc);
  }

  int    startDoc(DOCINFO* docInfo) {
      return ::StartDoc(hdc, docInfo);
  }

  int    startPage() {
      return ::StartPage(hdc);
  }
  int    endDoc() {
      return ::EndDoc(hdc);
  }
  int    endPage() {
      return ::EndPage(hdc);
  }

  //2012/05/30
  void    saveDC()
  {
    ::SaveDC(hdc);
  }

  void    restoreDC(int n)
  {
    ::RestoreDC(hdc, n);
  }

//2012/06/28
  BOOL drawIcon(int x, int y, HICON hIcon)
  {
    return ::DrawIcon(hdc, x, y, hIcon);
  }

  BOOL drawIconEx(
    int xLeft,
    int yTop,
    HICON hIcon,
    int cxWidth,
    int cyWidth,
    UINT istepIfAniCur=0,
    HBRUSH hbrFlickerFreeDraw=NULL,
    UINT diFlags=DI_NORMAL)
  {
    return ::DrawIconEx(
            hdc,
            xLeft,
            yTop,
            hIcon,
            cxWidth,
            cyWidth,
            istepIfAniCur,
            hbrFlickerFreeDraw,
            diFlags);

  }

  int setDIBits(HBITMAP    hbmp,
        UINT       uStartScan,
        UINT       cScanLines,
        const VOID       *lpvBits,
        const BITMAPINFO *lpbmi,
        UINT       fuColorUse)
  {
    return ::SetDIBits(
            hdc,
            hbmp,
            uStartScan,
            cScanLines,
            lpvBits,
            lpbmi,
            fuColorUse);
  }
  
  //2017/03/20
  
  HBITMAP createCompatibleBitmap(int width, int height)
  {
    return CreateCompatibleBitmap(hdc, width, height );
  }
  
  HDC createCompatibleDC()
  {
    return CreateCompatibleDC(hdc);
  }
  
  HPALETTE createHalftonePalette()
  {
    return CreateHalftonePalette(hdc);
  }
  
  HBITMAP createDIBitmap(
      CONST BITMAPINFOHEADER *lpbmih,
      DWORD fdwInit,                 
      CONST VOID *lpbInit,           
      CONST BITMAPINFO *lpbmi,       
      UINT fuUsage)
  {
    return ::CreateDIBitmap(
            hdc,
            lpbmih,
            fdwInit,
            lpbInit,
            lpbmi, 
            fuUsage);
  }
  
  //2017/03/20  
  void strechHalfToneBlt(float destX, float destY, float destWidth, float destHeight,
        HDC hMemDC, float srcX, float srcY, float srcWidth, float srcHeight,
        DWORD dwRop=SRCCOPY)
  {
    if (hMemDC) {
      setStretchBltMode(HALFTONE);
      HPALETTE hPal     = createHalftonePalette();
      HPALETTE hPrevPal = select(hPal, FALSE);
      realizePalette();
      
      stretchBlt((int)destX, (int)destY, (int)destWidth, (int)destHeight, hMemDC, 
        srcX, srcY, srcWidth, srcHeight, dwRop);
      
      select(hPrevPal, FALSE);
      ::DeleteObject(hPal);
    }
  }

  //2017/03/20  
  void strechBlt(float destX, float destY, float destWidth, float destHeight,
        HDC hMemDC, float srcX, float srcY, float srcWidth, float srcHeight,
        DWORD dwRop=SRCCOPY)
  {
    if (hMemDC) {
      setStretchBltMode(COLORONCOLOR);
      
      stretchBlt((int)destX, (int)destY, (int)destWidth, (int)destHeight, hMemDC, 
        srcX, srcY, srcWidth, srcHeight, dwRop);
    }
  }


};

}


