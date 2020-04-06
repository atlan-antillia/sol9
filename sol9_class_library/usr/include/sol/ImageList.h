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
 *  ImageList.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol/Object.h>
#include <sol\View.h>
#include <sol\DC.h>


namespace SOL {

class ImageList : public Object {
private:
  HIMAGELIST  hImageList;

public:
  //date="2000.06.26" Changed to take a default argument.
  ImageList(HIMAGELIST img = NULL) {
    hImageList = img;
  }

  ImageList(int cx, int cy, UINT flags, int cInitial, int cGrow) {
     hImageList = ImageList_Create(cx, cy, flags, cInitial, cGrow);
  }

  //2008/12/26
  HIMAGELIST create(int cx, int cy, UINT flags, int cInitial, int cGrow) {
    if (hImageList) {
      ImageList_Destroy(hImageList);      
    }
     hImageList = ImageList_Create(cx, cy, flags, cInitial, cGrow);
    return hImageList;
  }

  ~ImageList() { 
    if (hImageList) {  
      ImageList_Destroy(hImageList);
    }
  }

  BOOL  clear() {
      return (BOOL) ImageList_Remove(hImageList, -1);
  }
  int    getImageCount() {
      return  ImageList_GetImageCount(hImageList);
  }
  int    add(HBITMAP hbmImage, HBITMAP hbmMask) {
      return ImageList_Add(hImageList, hbmImage, hbmMask);
  }

  int    addIcon(HICON hicon) {
      return ImageList_AddIcon(hImageList, hicon);
  }

  BOOL  draw(int i, HDC hdcDst, int x, int y, UINT fStyle) {
      return ImageList_Draw(hImageList, i, hdcDst, x, y, fStyle);
  }
  BOOL  draw(int i, DC* dc, int x, int y, UINT fStyle) {
      return ImageList_Draw(hImageList, i, dc->get(), x, y, fStyle);
  }

  int  replaceIcon(int i, HICON hicon) {        
      return ImageList_ReplaceIcon(hImageList, i, hicon);
  }
  COLORREF setBkColor(COLORREF clrBk) {
      return ImageList_SetBkColor(hImageList, clrBk);
  }
  COLORREF getBkColor() {
      return ImageList_GetBkColor(hImageList);
  }
  BOOL  setOverlayImage(int iImage, int iOverlay){
      return ImageList_SetOverlayImage(hImageList, iImage, iOverlay);
  }
  BOOL  replace(int i, HBITMAP hbmImage, HBITMAP hbmMask) {
      return ImageList_Replace(hImageList, i, hbmImage, hbmMask);
  }

  int  addMasked(HBITMAP hbmImage, COLORREF crMask) {
      return ImageList_AddMasked(hImageList, hbmImage, crMask);
  }
  BOOL    drawEx(int i, HDC hdcDst, int x, int y, int dx, int dy,
         COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {
      return ImageList_DrawEx(hImageList, i, hdcDst, x, y, dx, dy, 
      rgbBk, rgbFg, fStyle);
  }

  BOOL    remove(int i) {
      return  (BOOL)ImageList_Remove(hImageList, i);
  }
  HICON  getIcon(int i, UINT flags) {
      return  ImageList_GetIcon(hImageList, i, flags);
  }

   HIMAGELIST getImageList() {
      return hImageList;
  }

  void  loadImage(HINSTANCE hi, LPCTSTR lpbmp, int cx, int cGrow, 
        COLORREF crMask, UINT uType, UINT uFlags) {
      hImageList = ImageList_LoadImage(hi, lpbmp, cx, cGrow, 
        crMask, uType, uFlags);
  }
  BOOL  beginDrag(int iTrack, int dxHotspot, int dyHotspot) {      
      return ImageList_BeginDrag(hImageList, iTrack, dxHotspot, dyHotspot);
  }

  void  endDrag() {
      ImageList_EndDrag();
  }

  BOOL  dragEnter(int x, int y) {
      return ImageList_DragEnter(NULL, x, y);
  }

  BOOL  dragEnter(HWND hwndLock, int x, int y) {
      return ImageList_DragEnter(hwndLock, x, y);
  }
  BOOL  dragEnter(View* view, int x, int y) {
      return ImageList_DragEnter(view->getWindow(), x, y);
  }

  BOOL  dragLeave(HWND hwndLock) {
      return ImageList_DragLeave(hwndLock);
  }
  BOOL  dragLeave(View* view) {
      return ImageList_DragLeave(view->getWindow());
  }

  BOOL  dragMove(int x, int y) {
      return ImageList_DragMove(x, y);
  }  
  BOOL  setDragCursorImage(int iDrag, int dxHotspot, int dyHotspot) {
      return ImageList_SetDragCursorImage(hImageList, iDrag, dxHotspot, dyHotspot);
   }

  BOOL  dragShowNolock(BOOL fShow) {
      return ImageList_DragShowNolock(fShow);
  }
  HIMAGELIST  getDragImage(POINT* ppt,POINT* pptHotspot) {
      return ImageList_GetDragImage(ppt, pptHotspot);
  }
  BOOL  removeAll()  {
      return ImageList_Remove(hImageList, -1);
  }
  HICON  extractIcon(int i, UINT fstyle) {
       return (HICON)ImageList_GetIcon(hImageList, i, fstyle);
  }
  void  loadBitmap(HINSTANCE hi, TCHAR* lpbmp, int cx, int cGrow, COLORREF crMask, 
        UINT type, UINT flag) {
       hImageList = ImageList_LoadImage(hi, lpbmp, cx, cGrow, crMask, type, flag);
  }
  BOOL  getIconSize(int *cx, int *cy) {
      return ImageList_GetIconSize(hImageList, cx, cy);
  }
  BOOL  setIconSize(int cx, int cy)   {
        return ImageList_SetIconSize(hImageList, cx, cy);
  }
  BOOL  getImageInfo(int i, IMAGEINFO* pImageInfo) {
      return ImageList_GetImageInfo(hImageList, i, pImageInfo);
  }
  HIMAGELIST merge(HIMAGELIST hImageList2, int i2, int dx, int dy) {
      int i1 = getImageCount();
       return hImageList = ImageList_Merge(hImageList, i1, hImageList2, i2, dx, dy);
  }

  //<added date="2000.06.26">
  void  setImageList(HIMAGELIST hlist) {
    if (hImageList) {
      ImageList_Destroy(hImageList);
    }
    hImageList = hlist;
  }

  HIMAGELIST  detachImageList() {
    HIMAGELIST h = hImageList;
    hImageList = NULL;
    return h;
  }
  //</added>
};

}

