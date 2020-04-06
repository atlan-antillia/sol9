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
 *  Header.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\Primitive.h>


namespace SOL {

class Header :public Primitive {

public:
  Header(): Primitive() { }

public:
  Header(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/22
  Header(View* parent, const TCHAR* name, Args& args)
    :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
        args.set(XmNpredefined, TRUE)
            .set(XmNclassName, (LONG_PTR)WC_HEADER));

    setValues(args);
    return rc;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNitemChangingCallback,  HDN_ITEMCHANGING},
    {XmNitemChangedCallback,   HDN_ITEMCHANGED}, 
    {XmNitemClickCallback,     HDN_ITEMCLICK},
    {XmNitemDoubleClickCallback,  HDN_ITEMDBLCLICK},  
    {XmNdividerDoubleClickCallback,  HDN_DIVIDERDBLCLICK},
    {XmNbeginTrackCallback,       HDN_BEGINTRACK},
    {XmNendTrackCallback,       HDN_ENDTRACK},
    {XmNtrackCallback,         HDN_TRACK},
    };
    *num = XtNumber(table);
    return table;  
  }


  int    getItemCount() {
      return (int)send(HDM_GETITEMCOUNT, 0, 0L);
  }

  int    insertItem(int i, HD_ITEM* phdi) {
      return (int)send(HDM_INSERTITEM, (WPARAM)i, (LPARAM)phdi);
  }
  BOOL  deleteItem(int i) {
         return (BOOL)send(HDM_DELETEITEM, (WPARAM)i, 0L);
  }
  BOOL  getItem(int i, HD_ITEM* phdi) {
      return (BOOL)send(HDM_GETITEM, (WPARAM)i, (LPARAM)phdi);
  }

  BOOL  setItem(int i, HD_ITEM* phdi) {
      return (BOOL)send(HDM_SETITEM, (WPARAM)i, (LPARAM)phdi);
  }
  BOOL  layout(HD_LAYOUT* layout) {
      return (BOOL)send(HDM_LAYOUT, 0, (LPARAM)layout);
  }
};

}

