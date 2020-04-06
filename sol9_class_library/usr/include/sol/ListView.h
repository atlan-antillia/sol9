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
 *  ListView.h
 *
 *****************************************************************************/

// 2000.02.18
// 2008/07/28
// 2010/04/12 Modified getSelectedItemText method.
// 2012/06/25
// 2019/05/27

#pragma once

#include <sol\Primitive.h>
#include <sol\StringList.h>
#include <sol\ImageList.h>
#include <sol\IntegerList.h>
#include <sol\Stdio.h>
#include <sol/StringT.h>
#include <sol/FileStream.h>
#include <sol/StringTokenizerT.h>

namespace SOL {

//2008/07/28
typedef struct {
  const TCHAR* label;
  int   format;
  int   size;  
} ListViewColumn;

class ListView :public Primitive {
private:
  static const long STYLE = (WS_TABSTOP|WS_BORDER|WS_HSCROLL);

public:
  ListView(): Primitive() { }

public:
    ListView(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  ListView(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {  
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
          .set(XmNstyle, (LONG_PTR)STYLE)
          .set(XmNclassName, (LONG_PTR)WC_LISTVIEW));

    setValues(args);
    return rc;
  }


public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNitemChangingCallback,    (LONG_PTR)LVN_ITEMCHANGING},
    {XmNitemChangedCallback,     (LONG_PTR)LVN_ITEMCHANGED},
    {XmNinsertItemCallback,      (LONG_PTR)LVN_INSERTITEM},
    {XmNdeleteItemCallback,      (LONG_PTR)LVN_DELETEITEM},
    {XmNdeleteAllItemsCallback,  (LONG_PTR)LVN_DELETEALLITEMS},
    {XmNbeginLabelEditCallback,  (LONG_PTR)LVN_BEGINLABELEDIT},
    {XmNenableEditCallback,      (LONG_PTR)LVN_ENDLABELEDIT},
    {XmNcolumnClickCallback,     (LONG_PTR)LVN_COLUMNCLICK},
    {XmNbeginDragCallback,       (LONG_PTR)LVN_BEGINDRAG},
    {XmNbeginRDragCallback,      (LONG_PTR)LVN_BEGINRDRAG},
    {XmNgetDispInfoCallback,     (LONG_PTR)LVN_GETDISPINFO},
    {XmNsetDispInfoCallback,     (LONG_PTR)LVN_SETDISPINFO},
    {XmNkeyDownCallback,         (LONG_PTR)LVN_KEYDOWN},
    };
  
    *num = XtNumber(table);
    return table;
  }

public:
  void setColumn(StringList* list, int fmt = LVCFMT_LEFT)
  {
    if (list ==NULL) {
      return;
    }

    int num = list->getLength();
    if (num == 0) {
      return;
    }

    LV_COLUMN column;
    memset(&column, 0, sizeof(LV_COLUMN));
    column.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
    column.fmt  = fmt;
    column.cx   = 100;
    int i = 0;
    ClientDC cdc(this);

    int width  = 0;
    int height = 0;
    getClientSize(width, height);
    int avwidth = width/num;
    Printf(_T("ListView#setColumn,num=%d width=%d av=%d\r\n"), num, width, avwidth);

    ListEntry* ptr = list->getEntry();
    while(ptr) {
      String* string = (String*)(ptr->getObject());
      TCHAR* str = string->getContents();
      column.pszText = str;
      //2000.04.22
      SIZE size;
      cdc.getTextExtent(str, (int)strlen(str), &size);
  
      //2008/07/02
      if (avwidth ==0) {
        column.cx = size.cx+10;
      } else {
        column.cx = avwidth;
      }
      insertColumn(i++, &column);

      ptr = ptr ->getNext();
    }
  }

public:
  void setColumn(StringList* list, IntegerList* format)
  {
    if (list == NULL || format == NULL) {
      return;
    }
    int lnum = list->getLength();
    int fnum = format->getLength();

    if (lnum == 0 || fnum == 0) {
      return;
    }

    if (lnum !=  fnum) {
      return;
    }

    int width  = 0;
    int height = 0;
    getClientSize(width, height);

    int avwidth = width/lnum;

    LV_COLUMN column;
    memset(&column, 0, sizeof(LV_COLUMN));
    column.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
    column.cx   = 100;
    int i = 0;
    ClientDC cdc(this);
    ListEntry* ptr = list->getEntry();
    ListEntry* itr = format-> getEntry();
    while (ptr) {
      String* string = (String*)   (ptr -> getObject());
      Integer* integer = (Integer*)(itr -> getObject());
      TCHAR* str = string->getContents();
      column.pszText = str;
      column.fmt     = integer -> getContents();
    
      //2000.04.22
      SIZE size;
      cdc.getTextExtent(str, (int)strlen(str), &size);
      if (avwidth == 0) {
        column.cx      = size.cx+10;
        //2008/07/02
      } else {
        column.cx = avwidth;
      }
      insertColumn(i++, &column);
      ptr = ptr -> getNext();
      itr = itr -> getNext();
    }
  }

public:
  void setColumn(const TCHAR** labels, int num)
  {
    if (labels == NULL || num<1) {
      return;
    }

    int width  = 0;
    int height = 0;
    getClientSize(width, height);

    int avwidth = width/num;

    LV_COLUMN column;
    memset(&column, 0, sizeof(LV_COLUMN));
    column.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
    column.fmt  = LVCFMT_LEFT;
    column.cx   = avwidth;
    for(int i = 0; i<num; i++) {
      column.pszText = (TCHAR*)labels[i];
      insertColumn(i, &column);
    }
  }

public:
  void setColumn(const TCHAR** labels, int* colwidth, int num)
  {
    if (labels == NULL || num<1) {
      return;
    }

    int width  = 0;
    int height = 0;
    getClientSize(width, height);

    LV_COLUMN column;
    memset(&column, 0, sizeof(LV_COLUMN));
    column.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
    column.fmt  = LVCFMT_LEFT;
    for(int i = 0; i<num; i++) {
      column.cx   = colwidth[i];

      column.pszText = (TCHAR*)labels[i];
      insertColumn(i, &column);
    }
  }

public:
  void setItemState(int i, int data, int mask) 
  { 
    LV_ITEM item;
    memset(&item, 0, sizeof(LV_ITEM));
    item.stateMask = mask;
      item.state     = data;
      send( LVM_SETITEMSTATE, (WPARAM)i, (LPARAM)&item);
  }

public:
  //2012/05/27
  int insertItemParam(int itemID, int subItemID, long lParam)
  {
    LV_ITEM item;
    memset(&item, 0, sizeof(LV_ITEM));
    item.mask     = LVIF_PARAM;
    item.iItem    = itemID;
    item.iSubItem = subItemID;
    item.lParam   = lParam;
    return insertItem(&item);
  }

  void insertItemText(int itemID, int subItemID, const TCHAR* text)
  {
    LV_ITEM item;
    memset(&item, 0, sizeof(LV_ITEM));
    item.mask     = LVIF_TEXT;
    item.iItem    = itemID;
    item.iSubItem = subItemID;
      item.cchTextMax = (int)strlen(text);
      item.pszText    = (TCHAR*)text;

    insertItem(&item);
  }

public:
  //2012/05/27
  LPARAM getItemParam(int itemID, int subItemID=0)
  {
    LVITEM item;
    memset(&item, 0, sizeof(LVITEM));
    item.mask     = LVIF_PARAM;
    item.iItem    = itemID;
    item.iSubItem = subItemID;
    getItem(&item);

    return item.lParam;
  }

public:
  void getItemText(int i, int subItem, TCHAR* text, int textMax)
  { 
    LV_ITEM item;
    memset(&item, 0, sizeof(LV_ITEM));
    item.iSubItem   = subItem;
      item.cchTextMax = textMax;
      item.pszText    = text;
      send(LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)&item);
  }

public:
  void setItemText(int i, int subItem, const char* text) 
  { 
    //2009/09/26
    const char* string = text;
    if (string == NULL){
      //Set an emptyr string "" to string;
      string = "";
    }

    LV_ITEMA item;
    memset(&item, 0, sizeof(item));
    item.iItem = i;
    item.mask = LVIF_TEXT;
    item.iSubItem = subItem;
    item.pszText  = (char*)string;    //text;
      send(LVM_SETITEMTEXTA, (WPARAM)i, (LPARAM)&item);
  }

public:
//#ifndef UNICODE
  void setItemText(int i, int subItem, const wchar_t* text) 
  { 
    //2009/09/26
    const wchar_t* string = text;
    if (string == NULL){
      //Set an emptyr string "" to string;
      string = L"";
    }

    LV_ITEMW item;
    memset(&item, 0, sizeof(item));
    item.iItem = i;
    item.mask = LVIF_TEXT;
    item.iSubItem = subItem;
    item.pszText  = (wchar_t*)string;    //text;
      send(LVM_SETITEMTEXTW, (WPARAM)i, (LPARAM)&item);
  }
//#endif

public:
  //2012/04/10
  void insertText(int n, const TCHAR* string)
  {
    if (string == NULL) {
        //Set an emptyr string "" to string;
      string = _T("");
    }

    LV_ITEM item;
    memset(&item, 0, sizeof(LV_ITEM));
    item.mask = LVIF_TEXT;
    item.pszText = (TCHAR*)string;      
    item.iItem = n;
    insertItem(&item);
  }


public:
  //2012/06/10
  int insertLine(int n, const char** text, int num)
  {
    int index = 0;
    //2009/09/26
    if (text && num>0) {
      const char* string = text[0];
      if (string == NULL) {
        //Set an emptyr string "" to string;
        string = "";
      }

      LV_ITEMA item;
      memset(&item, 0, sizeof(LV_ITEMA));
      item.mask = LVIF_TEXT;
      item.pszText = (char*)string;      //(TCHAR*)text[0];
      item.iItem = n;
      index = insertItem(&item);
      for(int i = 1; i<num; i++) {
        setItemText(index, i, text[i]);
      }
    }
    return index;
  }

public:
  //2012/11/29
  int addStringWithIcon(const TCHAR* string, int iconId=0)
  {
    int n = getItemCount();
    int index = 0;
    if (string) {

      LV_ITEM item;
      memset(&item, 0, sizeof(item));
      item.mask = LVIF_TEXT|LVIF_IMAGE;
      item.iImage = iconId;
      
      item.pszText = (TCHAR*)string;
      item.iItem = n;
      index = insertItem(&item);
    }
    return index;
  }

public:
  //2012/11/30
  int addStringsWithIcon(const TCHAR** text, int num, int iconId)
  {
    int n = getItemCount();
    int index = 0;

    if (text && num>0) {
      LV_ITEM item;
      memset(&item, 0, sizeof(item));
      item.mask = LVIF_TEXT|LVIF_IMAGE;
      item.iImage = iconId;
      
      item.pszText = (TCHAR*)text[0];
      item.iItem = n;
      index = insertItem(&item);

      for(int i = 1; i<num; i++) {
        setItemText(index, i, text[i]);
      }
    }
    return index;
  }

public:
  //2009/11/01
  int insertLineWithIcon(int n, const TCHAR** text, int num, int iconId)
  {
    int index = 0;
    //2009/09/26
    if (text && num>0) {
      const TCHAR* string = text[0];
      if (string == NULL) {
        string = _T("");
      }

      LV_ITEM item;
      memset(&item, 0, sizeof(item));
      item.mask = LVIF_TEXT|LVIF_IMAGE;
      item.iImage = iconId;
      
      item.pszText = (TCHAR*)string;      //(TCHAR*)text[0];
      item.iItem = n;
      index = insertItem(&item);

      for(int i = 1; i<num; i++) {
        setItemText(index, i, text[i]);
      }
    }
    return index;
  }


public:
  //2012/06/10
  int insertLine(int n, StringList* list)
  {
    int index = -1;
    if (list) {
      LV_ITEM item;
      memset(&item, 0, sizeof(LV_ITEM));
      item.mask = LVIF_TEXT;
      ListEntry* ptr = list->getEntry();
      String* string = (String*)(ptr -> getObject());
      if (string) {
        TCHAR* text = string->getContents();
        item.pszText    = text;
        item.cchTextMax = (int)_tcslen(text);
        item.iItem      = n;
        index = insertItem(&item);

        ptr = ptr -> getNext();
        int  i = 1;
        while(ptr) {
          string = (String*)(ptr -> getObject());
          if (string) {
            TCHAR* text = string->getContents();
            setItemText(index, i++, text);
          }
          ptr = ptr -> getNext();
        }
      }
    }
    return index;
  }


  Boolean  clear() {
        return (Boolean)send(LVM_DELETEALLITEMS, 0, 0L);
  }


  COLORREF getBkColor() {
        return (COLORREF)send(LVM_GETBKCOLOR, 0, 0L);
  }

public:
  //2008/07/28
  void setColumn(ListViewColumn items[], int num)
  {
    //Delete all items
    deleteAllItems();

    //Delete all columns
    while(deleteColumn(0)) {
    }

    //Insert new columns
    LV_COLUMN listcol;
    memset(&listcol, 0, sizeof(listcol));
    listcol.mask = LVCF_FMT|LVCF_TEXT | LVCF_WIDTH;//|LVCF_SUBITEM;
    for(int n = 0 ; n< num; n++){
      listcol.fmt = items[n].format;
      listcol.pszText =(TCHAR*)items[n].label;
      listcol.cx = items[n].size;
      insertColumn(n, &listcol);
    }
  }

public:
  //2008/12/15 Added const
#ifndef UNICODE
  void  setColumn(const wchar_t** labels, int num) {
    if (labels == NULL || num<1) {
      return;
    }

    int width  = 0;
    int height = 0;
    getClientSize(width, height);

    int avwidth = width/num;

    LV_COLUMNW column;
  
    memset(&column, 0, sizeof(column));
    column.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
    column.fmt  = LVCFMT_LEFT;
    column.cx   = avwidth;
    for(int i = 0; i<num; i++) {
      column.pszText = (wchar_t*)labels[i];
      insertColumn(i, &column);
    }
  }
#endif

  Boolean  setBkColor(COLORREF clrBk) {
        return (Boolean)send(LVM_SETBKCOLOR, 0, (LPARAM)clrBk);
  }


  HIMAGELIST  getImageList(int iImageList) {
        return (HIMAGELIST)send(LVM_GETIMAGELIST, (WPARAM)iImageList, 0L);
  }

  //2009/11/01
  HIMAGELIST  setImageList(HIMAGELIST himl, int iImageList=LVSIL_SMALL) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(iImageList), (LPARAM)himl);
  }

  HIMAGELIST  setImageList(ImageList* imagelist, int iImageList=LVSIL_SMALL) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(iImageList), 
            (LPARAM)imagelist->getImageList());
  }

  HIMAGELIST  setSmallImageList(HIMAGELIST himl) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(LVSIL_SMALL), (LPARAM)himl);
  }

  HIMAGELIST  setSmallImageList(ImageList* imagelist) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(LVSIL_SMALL), 
            (LPARAM)imagelist->getImageList());
  }
  HIMAGELIST  setNormalImageList(HIMAGELIST himl) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(LVSIL_NORMAL), (LPARAM)himl);
  }

  HIMAGELIST  setNormalImageList(ImageList* imagelist) {
        return (HIMAGELIST)send(LVM_SETIMAGELIST, (WPARAM)(LVSIL_NORMAL), 
            (LPARAM)imagelist->getImageList());
  }

  //

  int    getItemCount() {
        return (int)send(LVM_GETITEMCOUNT, 0, 0L);
  }

  Boolean  getItem(LV_ITEMA* pitem) {
        return (Boolean)send(LVM_GETITEMA, 0, (LPARAM)pitem);
  }

  Boolean  getItem(LV_ITEMW* pitem) {
        return (Boolean)send(LVM_GETITEMW, 0, (LPARAM)pitem);
  }

  Boolean  setItem(LV_ITEMA* pitem) {
        return (Boolean)send(LVM_SETITEMA, 0, (LPARAM)pitem);
  }

  Boolean  setItem(LV_ITEMW* pitem) {
        return (Boolean)send(LVM_SETITEMW, 0, (LPARAM)pitem);
  }

  int    insertItem(LV_ITEMA* pitem) {
        return (int)send(LVM_INSERTITEM, 0, (LPARAM)pitem);
  }

  int    insertItem(LV_ITEMW* pitem) {
        return (int)send(LVM_INSERTITEMW, 0, (LPARAM)pitem);
  }

  //2009/09/26
  //2012/06/10 Modified to return index of the line.
  int  insertLine(int n, const wchar_t** text, int num) 
  {
    int index = -1;

    if (text !=NULL && num>0) {
      const wchar_t* string = text[0];
      if (string ==NULL) {
        string = L"";
      }
      LV_ITEMW item;
      memset(&item, 0, sizeof(item));
      item.mask = LVIF_TEXT;
      item.pszText = (wchar_t*)string;     //text[0];
      item.iItem = n;
      
      index = insertItem(&item);
      for(int i = 1; i<num; i++) {
        setItemText(index, i, text[i]);
      }
    }
    return index;
  }

//#endif

  Boolean  deleteItem(int i) {
        return (Boolean)send(LVM_DELETEITEM, (WPARAM)i, 0L);
  }

  Boolean  deleteAllItems() {
        return (Boolean)send(LVM_DELETEALLITEMS, 0, 0L);
  }

  Boolean  getCallbackMask() {
        return (Boolean)send(LVM_GETCALLBACKMASK, 0, 0);
  }

  Boolean  setCallbackMask(UINT mask) {
        return (Boolean)send(LVM_SETCALLBACKMASK, (WPARAM)mask, 0);
  }

  int   getNextItem(int i, int flags) {
        return (int)send(LVM_GETNEXTITEM, (WPARAM)i, MAKELPARAM(flags, 0));
  }

  int    findItem(int iStart, LV_FINDINFO* plvfi) {
        return (int)send(LVM_FINDITEM, (WPARAM)iStart, (LPARAM)plvfi);
  }

  Boolean  getItemRect(int i, RECT* prc, int code) {
      return (Boolean)send(LVM_GETITEMRECT, (WPARAM)(int)(i), 
               ((prc) ? (((RECT FAR *)(prc))->left = (code),(LPARAM)(RECT FAR*)(prc)) : (LPARAM)(RECT FAR*)NULL));
   }

  Boolean  setItemPosition(int i, int x, int y) {
        return (Boolean)send(LVM_SETITEMPOSITION, (WPARAM)i, MAKELPARAM((x), (y)));
  }

  Boolean  getItemPosition(int i, POINT* ppt) {
        return (Boolean)send(LVM_GETITEMPOSITION, (WPARAM)i, (LPARAM)ppt);
  }

  int    getStringWidth(TCHAR* psz) {
        return (int)send(LVM_GETSTRINGWIDTH, 0, (LPARAM)psz);
  }

  int    hitTest(LV_HITTESTINFO* pinfo) {
        return (int)send(LVM_HITTEST, 0, (LPARAM)pinfo);
  }

  Boolean  ensureVisible(int i, Boolean fPartialOK) {
        return (Boolean)send(LVM_ENSUREVISIBLE, (WPARAM)i, MAKELPARAM((fPartialOK), 0));
  }

  Boolean  scroll(int dx, int dy) {
        return (Boolean)send(LVM_SCROLL, (WPARAM)dx, (LPARAM)dy);
  }

  Boolean  redrawItems(int iFirst, int iLast) {
        return (Boolean)send(LVM_REDRAWITEMS, (WPARAM)iFirst, (LPARAM)iLast);
  }

  Boolean  arrange(UINT code) {
        return (Boolean)send(LVM_ARRANGE, (WPARAM)code, 0L);
  }

  HWND  editLabel(int i) {
        return (HWND)send(LVM_EDITLABEL, (WPARAM)i, 0L);
  }

  HWND   getEditControl() {
        return (HWND)send(LVM_GETEDITCONTROL, 0, 0L);
  }

  Boolean  getColumn(int indx, LV_COLUMN* pcol) {
        return (Boolean)send(LVM_GETCOLUMN, (WPARAM)indx, (LPARAM)pcol);
  }

  Boolean   setColumn(int indx, LV_COLUMN* pcol) {
        return (Boolean)send(LVM_SETCOLUMN, (WPARAM)indx, (LPARAM)pcol);
  }

  int   insertColumn(int indx, LV_COLUMN* pcol) {
        return (int)send(LVM_INSERTCOLUMN, (WPARAM)indx, (LPARAM)pcol);
  }

#ifndef UNICODE
  Boolean   setColumn(int indx, LV_COLUMNW* pcol) {
        return (Boolean)send(LVM_SETCOLUMNW, (WPARAM)indx, (LPARAM)pcol);
  }
  int   insertColumn(int indx, LV_COLUMNW* pcol) {
        return (int)send(LVM_INSERTCOLUMNW, (WPARAM)indx, (LPARAM)pcol);
  }
#endif

  Boolean  deleteColumn(int indx) {
        return (Boolean)send(LVM_DELETECOLUMN, (WPARAM)indx, 0);
  }

  int    getColumnWidth(int indx) {
        return (int)send(LVM_GETCOLUMNWIDTH, (WPARAM)indx, 0);
  }

  Boolean  setColumnWidth(int column, int cx) {
        return (Boolean)send(LVM_SETCOLUMNWIDTH, (WPARAM)column, MAKELPARAM((cx), 0));
  }

  HIMAGELIST createDragImage(int i, POINT* upLeft) {
        return (HIMAGELIST)send(LVM_CREATEDRAGIMAGE, (WPARAM)i, (LPARAM)upLeft);
  }

  Boolean  getViewRect(RECT* rc) {
        return (Boolean)send(LVM_GETVIEWRECT, 0, (LPARAM)rc);
  }

  COLORREF getTextColor() {
        return (COLORREF)send(LVM_GETTEXTCOLOR, 0, 0L);
  }

  Boolean  setTextColor(COLORREF textColor) {
        return (Boolean)send(LVM_SETTEXTCOLOR, 0, (LPARAM)textColor);
  }

  COLORREF getTextBkColor()  {
        return (COLORREF)send(LVM_GETTEXTBKCOLOR, 0, 0L);
  }

  Boolean  setTextBkColor(COLORREF textBk) {
        return (Boolean)send(LVM_SETTEXTBKCOLOR, 0, (LPARAM)textBk);
   }

  int    getTopIndex() {
        return (int)send(LVM_GETTOPINDEX, 0, 0);
  }

  int   getCountPerPage() {
        return (int)send(LVM_GETCOUNTPERPAGE, 0, 0);
  }

  Boolean  getOrigin(POINT* ppt) {
        return (Boolean)send(LVM_GETORIGIN, 0, (LPARAM)ppt);
  }

  Boolean   update(int i) {
        return (Boolean)send(LVM_UPDATE, (WPARAM)i, 0L);
  }

//  void  setItemState(int i, int data, int mask);
  

  UINT  getItemState(int i, int mask) {
         return (UINT)send(LVM_GETITEMSTATE, (WPARAM)i, (LPARAM)mask);
  }

public:
  //2012/06/15
  bool isItemChecked(int index)
  {
    bool rc = false;
    int state = (int)send(LVM_GETITEMSTATE, index,  
      (LPARAM)LVIS_STATEIMAGEMASK ); 
    if (state == INDEXTOSTATEIMAGEMASK(2)) {
      rc = true;
    } 
    if (state == INDEXTOSTATEIMAGEMASK(1)) {
      rc = false;
    }
    return rc;
  }

#ifndef UNICODE
  void  getItemText(int i, int subItem, wchar_t* text, int textMax) { 
    LV_ITEMW item;
    memset(&item, 0, sizeof(item));
    item.iSubItem   = subItem;
      item.cchTextMax = textMax;
      item.pszText    = text;
      send(LVM_GETITEMTEXTW, (WPARAM)i, (LPARAM)&item);
  }
#endif
/*
  void  setItemText(int i, int subItem, const wchar_t* text) { 
    const wchar_t* string = text;
    if (string == NULL) {
      string = L"";
    }

    LV_ITEMW item;
    memset(&item, 0, sizeof(item));
    item.iItem = i;
    item.mask = LVIF_TEXT;
    item.iSubItem = subItem;
    item.pszText  = (wchar_t*)string;    //text;
    item.cchTextMax = wcslen(string)+1;  //text)+1;
      send(LVM_SETITEMTEXTW, (WPARAM)i, (LPARAM)&item);
  }
*/

  void  setItemCount(WPARAM cItems) {
        send(LVM_SETITEMCOUNT, (WPARAM)cItems, 0);
  }
 
  Boolean  sortItems(PFNLVCOMPARE compare, void* param) {
        return (Boolean)send(LVM_SORTITEMS, (WPARAM)param,
            (LPARAM)compare);
  }
 
  void  setItemPosition32(int i, long x, long y) { 
      POINT pos = {x,y}; 
        send( LVM_SETITEMPOSITION32, (WPARAM)i, (LPARAM)&pos);
  }

  UINT  getSelectedCount() {
        return (UINT)send(LVM_GETSELECTEDCOUNT, 0, 0L);
  }

  DWORD   getItemSpacing(Boolean fSmall) {
          return (DWORD)send(LVM_GETITEMSPACING, fSmall, 0L);
  }

  Boolean  getISearchString(TCHAR* lpsz) {
      return (Boolean)send(LVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz);
  }

  long  getExtendedViewStyle() {
      return (long)send(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
  }

  void  setExtendedViewStyle(long style) {
      send(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, style);
  }

  void setFullRowSelectViewStyle()
  {
    send(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

  }
  
  Boolean  getSubItemRect(int iItem, int iSubItem, int code, RECT* prc) {
      return (Boolean)send(LVM_GETSUBITEMRECT, (WPARAM)(int)(iItem), 
                ((prc) ? ((((LPRECT)(prc))->top = iSubItem), 
        (((LPRECT)(prc))->left = code), (LPARAM)(prc)) : (LPARAM)(LPRECT)NULL));
  }
  int    subItemHitTest(LVHITTESTINFO* plvhti) {
      return (int)send(LVM_SUBITEMHITTEST, 0, (LPARAM)plvhti);
  }

  Boolean  setColumnOrderArray(int iCount, int* pi) {
      return (Boolean)send(LVM_SETCOLUMNORDERARRAY, (WPARAM)iCount, (LPARAM)pi);
  }

  Boolean  getColumnOrderArray(int iCount, int* pi) {
      return (Boolean)send(LVM_GETCOLUMNORDERARRAY, (WPARAM)iCount, (LPARAM)pi);
  }

  int    setHotItem(int i) {
      return (int)send(LVM_SETHOTITEM, (WPARAM)i, 0);
  }

  int    getHotItem() {
      return (int)send(LVM_GETHOTITEM, 0, 0);
  }

  HCURSOR  setHotCursor(HCURSOR hcur) {
      return (HCURSOR)send(LVM_SETHOTCURSOR, 0, (LPARAM)hcur);
  }

  HCURSOR  getHotCursor() {
      return (HCURSOR)send(LVM_GETHOTCURSOR, 0, 0);
  }

  DWORD  approximateViewRect(int iWidth, int iHeight, int iCount) {
        return (DWORD)send(LVM_APPROXIMATEVIEWRECT, iCount, MAKELPARAM(iWidth, iHeight));
  }

  Boolean  setWorkAreas(RECT* prc) {
      return (Boolean)send(LVM_SETWORKAREAS, 0, (LPARAM)prc);
  }

public:
  bool getSelectedItemText(__out String& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    TCHAR name[1024];
    memset(name, (TCHAR)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEM item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        rc = true;
        break;

      }
    } //for
    return rc;
  }

public:
  bool getSelectedItemText(__out int& index, __out String& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    TCHAR name[1024];
    memset(name, (TCHAR)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEM item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        index = i;
        rc = true;
        break;

      }
    } //for
    return rc;
  }


public:
  //2009/12/25
  bool getSelectedItemText(__out StringT<wchar_t>& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    wchar_t name[1024];
    //2010/04/12 memset(name, (TCHAR)0, CountOf(name));
    memset(name, (wchar_t)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEMW item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        rc = true;
        break;

      }
    } //for
    return rc;
  }

public:
  //2012/01/22
  bool getSelectedItemText(__out _bstr_t& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    wchar_t name[1024*3];
    //2010/04/12 memset(name, (TCHAR)0, CountOf(name));
    memset(name, (wchar_t)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEMW item;
        memset(&item, 0, sizeof(item));

        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        rc = true;
        break;

      }
    } //for
    return rc;
  }

public:
  //2012/11/30
  bool getSelectedSubItemText(int subItem, __out _bstr_t& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    wchar_t name[1024*3];

    memset(name, (wchar_t)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEMW item;
        memset(&item, 0, sizeof(item));
        item.iSubItem = subItem;
        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        rc = true;
        break;
      }
    } //for
    return rc;
  }

  //2012/11/30
  bool getSelectedSubItemText(int subItem, __out String& string)
  {
    bool rc = false;

    int count = getItemCount();
        
    char name[1024*3];

    memset(name, (wchar_t)0, CountOf(name));

    for (int i = 0; i<count; i++) {

      UINT state = getItemState(i, LVIS_SELECTED);
    
      if (state &  LVIS_SELECTED) {
        //Get a file name to buffer text
        LV_ITEMA item;
        memset(&item, 0, sizeof(item));
        item.iSubItem = subItem;
        item.iItem = i;
        item.pszText = name;
        item.mask = LVIF_TEXT;
        item.cchTextMax = CountOf(name); 
        getItem(&item);
        string = name;
        rc = true;
        break;
      }
    } //for
    return rc;
  }
  
  
  void readCSVFile(const TCHAR* fileName, Boolean hasHeader=True)
  {
    clear();
    FileStream stream;

    if(stream.openReadOnly(fileName)) {
      char line[SIZE_1KB*4];
      StringList list;
      int n = -1;
      while(stream.getLine(line, sizeof(line)-1)) {
        const char* ptr = line;
        if(line[0] == ';') {
          continue;  // comment line
        }
        if(strlen(line) == 0) {
          continue;  // empty line
        }

        list.clear();

        // 1999.09.23
        char token[128];
        StringTokenizerT<char> scanner(line);
        while(ptr) {
          token[0] = ZERO;
          ptr = scanner.getToken(token, CountOf(token));
          if (strlen(token) >0) {
            //_bstr_t btoken=token;
            StringConverter converter;
            StringT<TCHAR> tstring;
            converter.convert(token, tstring);
            list.add(new String((const TCHAR*)tstring));
          }
        }

        if (list.getLength() == 0) {
          continue;
        }

        if(n == -1) {
          if (hasHeader == False) {
            setColumn(&list);
            hasHeader = True;
          }
        } else {
          insertLine(n, &list);
        }
        n++;
      }
      stream.close();
    }
  }
};

}

