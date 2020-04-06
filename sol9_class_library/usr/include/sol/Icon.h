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
 *  Icon.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/06/29 Updated

#pragma once

#include <sol\Resource.h>

//2009/10/13
#include <sol/MessageFont.h>

namespace SOL {

class Icon :public Resource {
private:
  int x;
  int y;
  int width;
  int height;
  BOOL destructable;
  MessageFont mfont;

public:
  //2012/06/29
  Icon(int iconId, int w = 0, int h = 0, int flag = LR_DEFAULTCOLOR)
  :Resource(_T(""), NULL)
  {
    x = 0;
    y = 0;

    loadImage(MAKEINTRESOURCE(iconId), w, h, flag);

    mfont.create(9);
  }

public:
  //2012/06/30
  bool loadImage(const TCHAR* name, int cx = 0, int cy = 0, int flag = LR_DEFAULTCOLOR)
  {
    bool rc = false;
    clear();

    HICON hIcon = (HICON)LoadImage((HINSTANCE)GetModuleHandle(NULL),
               name, IMAGE_ICON, cx, cy, flag);
    if (hIcon) {
      width   = cx;
      height  = cy;
    
      if ((cx == 0 || cy == 0 ) && (flag & LR_DEFAULTSIZE)) {
        width  = ::GetSystemMetrics(SM_CXICON);
        height = ::GetSystemMetrics(SM_CYICON);
      }
      destructable = TRUE;
      setHandle(hIcon);
      rc = true;
    }

    return rc;
  }

public:
  Icon(const TCHAR* name, HICON hicon)
  :Resource(name, hicon)
  {
    x       = 0; 
    y       = 0;
    width   = ::GetSystemMetrics(SM_CXICON);
    height  = ::GetSystemMetrics(SM_CYICON);
    destructable = FALSE;

    mfont.create(9);
  }

public:
  ~Icon() { 
    clear();

  }
public:
  void clear()
  {
    if(destructable) {
      HICON hIcon = (HICON)get();
      if (hIcon) {
        ::DestroyIcon(hIcon);
      }
    }
  }

public:
  operator HICON()
  {
    return (HICON)get();
  }

public:
  void draw(HDC hdc, int x1, int y1) 
  {
    TCHAR* name = getName();
    SIZE size;
    ::GetTextExtentPoint(hdc, name, (int)strlen(name), &size);
    int   w    = size.cx;
    HGDIOBJ prev = SelectObject(hdc, mfont.getFont());
    ::DrawIcon(hdc, x+x1, y+y1, (HICON)get());
    ::TextOut(hdc, x+x1-(w-width)/2,
         y+y1+ height + 4 , 
         name, (int)strlen(name));
    SelectObject(hdc, prev);
  }

public:
  void draw(HDC hdc, int x1, int y1, int cx, int cy,
        UINT index, HBRUSH hbrSrc,
        UINT flags) 
  {
    TCHAR* name = getName();
    SIZE size;
    ::GetTextExtentPoint(hdc, name, (int)strlen(name), &size);
    int   w    = size.cx;
    HGDIOBJ prev = SelectObject(hdc, mfont.getFont());
    ::DrawIconEx(hdc, x+x1, y+y1, (HICON)get(),
      cx, cy, index, hbrSrc, flags);
    ::TextOut(hdc, x+x1-(w-width)/2,
         y+y1+ height + 4 , 
         name, (int)strlen(name));
    SelectObject(hdc, prev);

  }

public:
  BOOL  getIconInfo(ICONINFO* info) {
    info->fIcon = TRUE;
    return ::GetIconInfo((HICON)get(), info);
  }

public:
  BOOL  getIconInfo(ICONINFO& info) {
    info.fIcon = TRUE;
    return ::GetIconInfo((HICON)get(), &info);
  }

public:
  //2012/06/29
  BOOL  getIconSize(int& width, int& height, int& depth) {
    ICONINFO info;
    info.fIcon = TRUE;
    BOOL rc = GetIconInfo((HICON)get(), &info);
    if (rc) {
      BITMAP bitmap;
      if (info.hbmColor) {
        if (GetObject(info.hbmColor, sizeof(BITMAP), &bitmap)) {
          width = bitmap.bmWidth; 
          height = bitmap.bmHeight; 
          depth = bitmap.bmBitsPixel; 
        }
        DeleteObject(info.hbmColor); 
      }
      if (info.hbmMask) {
        //Ignore this case
        DeleteObject(info.hbmMask); 
      }

    }
    return rc;
  }

public:
  void  move(int x1, int y1) {
    x = x1;  
    y = y1;
  }

  void  setFlag(int flag) {
    destructable = flag;
  }
  void  getSize(int* w, int* h) {
      *w = width; *h = height;
  }
};

}


