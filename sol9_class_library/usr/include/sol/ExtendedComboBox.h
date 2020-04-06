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
 *  ExtendedComboBox.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.23 Modified the super class from Primitive to ComboBox.
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\ComboBox.h>
#include <sol/ImageList.h>

namespace SOL {

class ExtendedComboBox :public ComboBox {

private:
  static const long STYLE = (const long)(WS_TABSTOP|WS_VSCROLL|CBS_NOINTEGRALHEIGHT);

  static int stylesCount()
  {
    int count = 0;
    styles(&count);
    return count;
  }

private:
  static Arg*  styles(int* count=NULL)
  {
// ExtendedComboBox can use the standard combobox style
    static Arg _styles[] = {
    {XmNsortItems,        CBS_SORT},
    {XmNdisableNoScroll, CBS_DISABLENOSCROLL},
    {XmNoemConvert,      CBS_OEMCONVERT}
    };
    if (count) {
      *count = XtNumber(_styles);
    }
    return _styles;
  }  

public:
  ExtendedComboBox():ComboBox() { }

    ExtendedComboBox(View* parent, HWND hwnd)
    :ComboBox(parent, hwnd) { }



public:
  //2012/06/21
  ExtendedComboBox(View* parent, const TCHAR* name, Args& args)
  :ComboBox()
  {
    create(parent, name, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = ComboBox::create(parent, name, 
      args.set(styles(), stylesCount())
          .set(XmNpredefined, TRUE)
          .set(XmNstyle, (LONG_PTR)STYLE)
          .set(XmNclassName, (LONG_PTR)WC_COMBOBOXEX));


    setValues(args);

    return rc;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNcloseUpCallback,    CBN_CLOSEUP},
     {XmNdefaultActionCallback,  CBN_DBLCLK},
     {XmNdropDownCallback,    CBN_DROPDOWN},
    {XmNeditChangeCallback,    CBN_EDITCHANGE},
    {XmNeditUpdateCallback,    CBN_EDITUPDATE},
    {XmNerrorSpaceCallback,    (LONG_PTR)CBN_ERRSPACE},

    {XmNkillFocusCallback,    CBN_KILLFOCUS},
    {XmNselChangeCallback,    CBN_SELCHANGE},
    {XmNselEndCancelCallback,  CBN_SELENDCANCEL},
    {XmNselEndOkCallback,    CBN_SELENDOK},
    {XmNsetFocusCallback,    CBN_SETFOCUS},

    {XmNbeginEditCallback,    CBEN_BEGINEDIT},
     {XmNdeleteItemCallback,    CBEN_DELETEITEM},
     {XmNdragBeginCallback,    CBEN_DRAGBEGIN},
    {XmNendEditCallback,    CBEN_ENDEDIT},
    {XmNgetDispInfoCallback,  CBEN_GETDISPINFO},
    {XmNinsertItemCallback,    CBEN_INSERTITEM},
    };

    *num = XtNumber(table);
    return table;
  }


  int  deleteItem(int index) {
    return (int)send(CBEM_DELETEITEM, index, 0);
  }

  HWND  getComboControl() {
      return (HWND)send(CBEM_GETCOMBOCONTROL, 0, 0);
  }

  HWND  getEditControl() {
      return (HWND)send(CBEM_GETEDITCONTROL, 0, 0);
  }
  DWORD  getExtendedStyle() {
      return (DWORD)send(CBEM_GETEXTENDEDSTYLE, 0, 0);
  }

  HIMAGELIST  getImageList() {
        return (HIMAGELIST)send(CBEM_GETIMAGELIST, 0, 0L);
  }

  int    getItem(COMBOBOXEXITEM* item) {
      return (int)send(CBEM_GETITEM, 0, (LPARAM)item);
  }

  int    getUnicodeFormat() {
      return (int)send(CBEM_GETUNICODEFORMAT, 0, 0);
  }

  int    hasEditChanged() {
      return (int)send(CBEM_HASEDITCHANGED, 0, 0);
  }

  int    insertItem(COMBOBOXEXITEM* item) {
    if (item) {
      return (int)send(CBEM_INSERTITEM, 0, (LPARAM)item);
    } else {
      return -1;
    }
  }

  DWORD  setExtendedStyle(DWORD mask, DWORD style) {
      return (DWORD)send(CBEM_SETEXTENDEDSTYLE, mask, style);
  }

  HIMAGELIST  setImageList(ImageList* imageList) {
    if (imageList) {
      return (HIMAGELIST)send(CBEM_SETIMAGELIST, 0, (LPARAM)imageList->getImageList());
    } else {
      return NULL;
    }
  }

  //2009/11/06
  HIMAGELIST  setImageList(ImageList& imageList) {
    return (HIMAGELIST)send(CBEM_SETIMAGELIST, 0, (LPARAM)imageList.getImageList());
  }

  HIMAGELIST  setImageList(HIMAGELIST himl) {
        return (HIMAGELIST)send(CBEM_SETIMAGELIST, 0, (LPARAM)himl);
  }

  int    setItem(COMBOBOXEXITEM* item) {
    if (item) {
      return (int)send(CBEM_SETITEM, 0, (LPARAM)item);
    } else {
      return -1;
    }
  }

  int    setUnicodeFormat(BOOL flag) {
      return (int)send(CBEM_GETUNICODEFORMAT, (WPARAM)flag, 0);
  }
};

}

