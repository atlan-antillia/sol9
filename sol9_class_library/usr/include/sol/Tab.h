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
 *  Tab.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class Tab :public Primitive {
  public:
  Tab(): Primitive() { }

public:
  //2012/06/25
  Tab(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {    
    Boolean rc = Primitive::create(parent, name, 
       args.set(XmNpredefined, TRUE)
        .set(XmNuseDefaultFont, _T("true"))
         .set(XmNclassName, (LONG_PTR)WC_TABCONTROL));
    setValues(args);
    return rc;
  }

public:
  int addItem(const TCHAR* text)
  {
    int n =  getItemCount();
    TC_ITEM item;
    memset(&item, 0, sizeof(TC_ITEM));
    item.mask = TCIF_TEXT;
    item.pszText = (TCHAR*)text;
    item.cchTextMax = strlen(text);
    return insertItem(n, &item);
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNkeyDownCallback,  TCN_KEYDOWN  },
    {XmNselChangeCallback,  TCN_SELCHANGE},
    {XmNselChangingCallback,TCN_SELCHANGING}
    };
    *num = XtNumber(table);
    return table;
  }


//  Tab(View* parent, const TCHAR* name, Args& args);

//  virtual Boolean create(View* parent, const TCHAR* name, Args& args);

//  int    addItem(const TCHAR* text);

//  Arg*   getCallbackTable(int* num);

   HIMAGELIST getImageList() {
      return (HIMAGELIST)send(TCM_GETIMAGELIST, 0, 0L);
  }
  HIMAGELIST setImageList(HIMAGELIST himl) {
      return (HIMAGELIST)send(TCM_SETIMAGELIST, 0, (LPARAM)himl);
  }
  int   getItemCount() {
      return (int)send(TCM_GETITEMCOUNT, 0, 0L);
  }
  BOOL   getItem(int iItem, TC_ITEM* pitem) {
         return (BOOL)send(TCM_GETITEM, (WPARAM)iItem, (LPARAM)pitem);
  }
  BOOL  setItem(int iItem, TC_ITEM* pitem) {
      return (BOOL)send(TCM_SETITEM, (WPARAM)iItem, (LPARAM)pitem);
  }
  int    insertItem(int iItem, TC_ITEM* pitem)   {
      return (int)send(TCM_INSERTITEM, (WPARAM)iItem, (LPARAM)pitem);
  }

  BOOL  deleteItem(int i) {
      return (BOOL)send(TCM_DELETEITEM, (WPARAM)i, 0L);
  }

  BOOL  deleteAllItems() {
      return (BOOL)send(TCM_DELETEALLITEMS, 0, 0L);
  }

  BOOL   getItemRect(int i, RECT* prc) {
      return (BOOL)send(TCM_GETITEMRECT, (WPARAM)i, (LPARAM)prc);
  }
   int    getCurSel() {
      return (int)send(TCM_GETCURSEL, 0, 0);
  }

  int    setCurSel(int i) {
      return (int)send(TCM_SETCURSEL, (WPARAM)i, 0);
  }
  int   hitTest(TC_HITTESTINFO* pinfo) {
      return (int)send(TCM_HITTEST, 0, (LPARAM)pinfo);
  }

  BOOL  setItemExtra(WPARAM cb) {
      return (BOOL)send(TCM_SETITEMEXTRA, (WPARAM)cb, 0L);
  }

  int   adjustRect(BOOL bLarger, RECT* prc) {
       return (int)send(TCM_ADJUSTRECT, (WPARAM)bLarger, (LPARAM)prc);
  }

  DWORD   setItemSize(int x, int y) {
      return (DWORD)send(TCM_SETITEMSIZE, 0, MAKELPARAM(x,y));
  }

  void  removeImage(int i) {
      send(TCM_REMOVEIMAGE, i, 0L);
  }

  void  setPadding(int cx, int cy) {
      send(TCM_SETPADDING, 0, MAKELPARAM(cx, cy));
  }

  int    getRowCount() {
      return (int)send(TCM_GETROWCOUNT, 0, 0L);
  }

  HWND  getToolTips() {
      return (HWND)send(TCM_GETTOOLTIPS, 0, 0L);
  }

  void   setToolTips(HWND hwndTT) {
      send(TCM_SETTOOLTIPS, (WPARAM)hwndTT, 0L);
  }

  int    getCurFocus() {
      return (int)send(TCM_GETCURFOCUS, 0, 0);
  }
  void  setCurFocus(int i) {
       send(TCM_SETCURFOCUS, i, 0);
  }
};

}

