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
 *  ListBox.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>


namespace SOL {

class ListBox :public Primitive {
private:
  //2009/11/07 For findAllFiles method
  bool scanning;

private:

  static const long STYLE = (WS_TABSTOP|WS_BORDER|LBS_NOTIFY|WS_HSCROLL|WS_VSCROLL|\
        LBS_NOINTEGRALHEIGHT);

  static const TCHAR itemsListDelim = '\n';

  static int stylesCount()
  {
    int count = 0;
    styles(&count);
    return count;
  }

  static Arg* styles(int* count=NULL)
  {
    static Arg _styles[] = {
    {XmNdisableNoScroll,   LBS_DISABLENOSCROLL},
    {XmNextendedSel,       LBS_EXTENDEDSEL},
    {XmNmultiColumn,       LBS_MULTICOLUMN},
    {XmNmultipleSel,       LBS_MULTIPLESEL},
    {XmNsortItems,         LBS_SORT},
    {XmNuseTabStops,       LBS_USETABSTOPS},
    {XmNwantKeyboardInput, LBS_WANTKEYBOARDINPUT},
    };

    if (count){
      *count = XtNumber(_styles);
    }
    return _styles;
  }


public:
  ListBox():Primitive() { }

public:
  ListBox(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  ListBox(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(styles(), stylesCount())
          .set(XmNpredefined, TRUE)
          .set(XmNstyle,     (LONG_PTR)STYLE)
          .set(XmNexStyle,   (LONG_PTR)WS_EX_CLIENTEDGE)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName, _T("ListBox")));

    setValues(args);

    return rc;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNdefaultActionCallback,   LBN_DBLCLK},
    {XmNerrorSpaceCallback,    (LONG_PTR)LBN_ERRSPACE},
    {XmNkillFocusCallback,    LBN_KILLFOCUS},
    {XmNselCancelCallback,    LBN_SELCANCEL},
     {XmNselChangeCallback,    LBN_SELCHANGE},
     {XmNsetFocusCallback,    LBN_SETFOCUS},
     };

    *num = XtNumber(table);
    return table;
  }

public:
  int  getCurText(TCHAR* buffer) 
  {
    if(buffer) {
      *buffer = ZERO;
      int indx = getCurSel();
      if(indx != LB_ERR) {
        return getText(indx, buffer);
      }
      else {
        return 0;
      }
    }
    return 0;
  }

public:
  TCHAR* getCurText()
  {
    TCHAR* text = NULL;

    int indx = getCurSel();
    if(indx != LB_ERR) {
      int len = getTextLen(indx);
      text = new TCHAR[len+1];
      getText(indx, text);
    }
    return text;
  }

public:
  void getValues(Args& args)
  {
    Primitive::getValues(args);

    getStyle(args, styles(), stylesCount());

    LONG_PTR* val = (LONG_PTR*)args.get(XmNitemsList);
    if(val) {
      int buffLen = 0;
      int count  = getCount();
      for(int n = 0; n< count; n++) {
        buffLen = buffLen + getTextLen(n) + 1; //strlen("\n");
      }

      TCHAR* list = new TCHAR[buffLen];
      *list      = NULL;
      TCHAR* buff = list;

      for(int i = 0; i< count; i++) {
        int len = getTextLen(i);
        getText(i, buff);
        buff += len;
        if(i < count -1) {
          *buff  = itemsListDelim;
        }
        buff++;
      }
      *buff = ZERO;

      *val  = (LONG_PTR)list;
    }
  }

public:
  void setValues(Args& args)
  {
    Primitive::setValues(args);

    updateStyle(args, styles(), stylesCount());

    LONG_PTR  val;
    TCHAR** items = NULL;
    int     count = 0;
    if (args.get(XmNitemCount, &val))
      count = (int)val;
    if (args.get(XmNitems, &val))
      items = (TCHAR**)val;
    if (count >0 && items) {
      resetContent();
      for (int i = 0; i<count; i++) {
        addString(items[i]);
      }
    }

    // XmNitemsList

    TCHAR* list = NULL;
    if (args.get(XmNitemsList, &val)) {
      resetContent();
      TCHAR* s = (TCHAR*)val;
      size_t slen = strlen(s)+1;
      list = new TCHAR[slen];
      strcpy_s(list, slen, s);
    }
    if (list) {
      TCHAR* str = list;
      TCHAR* ptr = list;
      while(*ptr) {
        if(*ptr == itemsListDelim) {
          *ptr++ = NULL;
          addString(str);
          str = ptr;
        }
        else {
          ptr++;
        }
      }
      if (str)  addString(str);
      if (list) delete list;
    }
  }

public:
  // List up long file names.
  void findFiles(DWORD attr, const TCHAR* pattern)
  {
    WIN32_FIND_DATA data;
    HANDLE hf = ::FindFirstFile(pattern, &data);
    if(hf != INVALID_HANDLE_VALUE) {
      do {
        if(data.dwFileAttributes & attr) {
          addString((TCHAR*)data.cFileName);
        }      
      } while(::FindNextFile(hf, &data));
      ::FindClose(hf);
    }
  }

public:
  void findFiles(const TCHAR* pattern)
  {
    DWORD attr = FILE_ATTRIBUTE_ARCHIVE|
    FILE_ATTRIBUTE_DIRECTORY|
    FILE_ATTRIBUTE_COMPRESSED|
    FILE_ATTRIBUTE_HIDDEN| 
    FILE_ATTRIBUTE_NORMAL|  
    FILE_ATTRIBUTE_READONLY| 
    FILE_ATTRIBUTE_SYSTEM;
    ListBox::findFiles(attr, pattern);  
  }

private:
  //2009/11/07
  void dispatchMessage()
  {
    MSG msg;
    
    while(
      PeekMessage (&msg,NULL,0,0,PM_REMOVE)) {
      SleepEx(10, TRUE);
      if (msg.message == WM_QUIT) {
        scanning = false;
        //Repost WM_QUIT message to your application message queue.
        PostMessage(NULL, WM_QUIT, 0, 0);
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

public:
  //2009/11/06
  //2009/11/06
  // List up all file name having an extension of ext.
  void findAllFiles(const TCHAR* dir, const TCHAR* ext)
  {
    if (dir == NULL || ext == NULL) {
      return;
    }

    setRedraw(FALSE);
    clear();
    scanning = true;
    
    findAllFilesRecursively(dir, ext);
    scanning = false;
    
    setRedraw(TRUE);
  }

public:
  bool isScanning()
  {
    return scanning;
  }

public:
  void stopScanning()
  {
    scanning = false;
  }

public:
  //2009/11/06
  // List up all file name having an extension of ext.
  void findAllFilesRecursively(const TCHAR* dir, const TCHAR* ext)
  {
    if (scanning == false) {
      return;
    }

    setRedraw(FALSE);

    WIN32_FIND_DATA data;
    TCHAR* path = new TCHAR[MAX_PATH];
    _stprintf_s(path, MAX_PATH, _T("%s\\%s"), dir, _T("*"));
    
    HANDLE hf = ::FindFirstFile(path, &data);
    if(hf != INVALID_HANDLE_VALUE) {
      do {
        dispatchMessage();
        if (scanning == false) {
          break;
        }
        if (!(strcmp(data.cFileName, _T(".")) == 0 ||
          strcmp(data.cFileName, _T("..")) == 0)) {
    
          TCHAR* fullPath = new TCHAR[MAX_PATH];
          _stprintf_s(fullPath, MAX_PATH, _T("%s\\%s"), dir, data.cFileName);

          if(String::endsWithIgnoreCase(data.cFileName, ext)) {
            addString((TCHAR*)fullPath);
          }
          // Recursively call findAllFile provided fullPath were a directory
          if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            findAllFilesRecursively(fullPath, ext); 
          }
          delete [] fullPath;
        }
      } while(::FindNextFile(hf, &data));
      ::FindClose(hf);
    }
    delete [] path;

    setRedraw(TRUE);
  }

public:
  // Find all subdirectories under dir.
  // Give a string such as "c:\\windows"  for dir.
  void findDirectories(const TCHAR* dir)
  {
    TCHAR pattern[_MAX_PATH];
    _stprintf_s(pattern, CountOf(pattern), _T("%s\\*.*"), dir);
    findFiles(FILE_ATTRIBUTE_DIRECTORY, pattern);
  }

  int   addString(const TCHAR* string) {
      return (int)send(LB_ADDSTRING, 0, (LPARAM)string);
  }

  // 1999.09.23
  void  clear() {
      send(LB_RESETCONTENT, 0, 0L);
  }

  const TCHAR*  defaultCallbackName() { 
    return XmNdefaultActionCallback; 
  }
  
  int   deleteString(int indx) {
      return (int)send(LB_DELETESTRING, indx, 0L);
  }

  int    dir(int attr, const TCHAR* string) {
      return (int)send(LB_DIR, attr, (LPARAM)string);
  }

  int    findString(int indx, const TCHAR* string) {
      return (int)send(LB_FINDSTRING, indx, (LPARAM)string);
  }

  int    findStringExact(int indx, const TCHAR* string) {
      return (int)send(LB_FINDSTRINGEXACT, indx, (LPARAM)string);
  }

  int   getCaretIndex() {
      return (int)send(LB_GETCARETINDEX, 0, 0L);
  }

  int   getCount() {
      return (int)send(LB_GETCOUNT, 0, 0L);
  }

  int    getCurSel() {
      return (int)send(LB_GETCURSEL, 0, 0L);
  }

  int    getHorizontalExtent() {
      return (int)send(LB_GETHORIZONTALEXTENT, 0, 0L);
  }

  LRESULT  getItemData(int indx) {
      return send(LB_GETITEMDATA, indx, 0L);
  }

  LRESULT  getItemHeight(int indx) {
      return send(LB_GETITEMHEIGHT, indx, 0L);
  }

  LRESULT    getItemRect(int indx, LPRECT rect) {
      return (int)send(LB_GETITEMRECT, indx, (LPARAM)rect);
  }

  int    getSel(int indx) {
      return (int)send(LB_GETSEL, indx, 0L);
  }

  int    getSelCount() {
      return (int)send(LB_GETSELCOUNT, 0, 0L);
  }

  int    getSelItems(int max, int array[]) {
      return (int)send(LB_GETSELITEMS, max, (LPARAM)array);
  }

  int   getText(int indx, TCHAR* buffer) {
      return (int)send(LB_GETTEXT, indx, (LPARAM)buffer);
  }

  int   getTextLen(int indx) {
      return (int)send(LB_GETTEXTLEN, indx, 0L);
  }

  int    getTopIndex() {
      return (int)send(LB_GETTOPINDEX, 0, 0L);
  }

  int   insertString(int indx, const TCHAR* string) {
      return (int)send(LB_INSERTSTRING, indx, (LPARAM)string);
  }

  void  resetContent() {
      send(LB_RESETCONTENT, 0, 0L);
  }

  int    selectString(int indx, const TCHAR* string) {
      return (int)send(LB_SELECTSTRING, indx, (LPARAM)string);
  }

  int    selItemRange(int sel, int first, int last) {
      return (int)send(LB_SELITEMRANGE, sel, MAKELPARAM(first,last));
  }

  void  setCaretIndex(int indx, int scroll) {
      send(LB_SETCARETINDEX, indx, MAKELPARAM(scroll, 0));
  }

  void  setColumnWidth(int width) {
      send(LB_SETCOLUMNWIDTH, width, 0L);
  }

  int    setCurSel(int indx) {
      return (int)send(LB_SETCURSEL, indx, 0L);
  }

  void  setHorizontalExtent(int width) {
      send(LB_SETHORIZONTALEXTENT, width, 0L);
  }

  int    setItemData(int indx, LPARAM data) {
      return (int)send(LB_SETITEMDATA, indx, data);
  }

  int    setItemHeight(int indx, int height) {
      return (int)send(LB_SETITEMHEIGHT, indx, MAKELPARAM(height,0));
  }

  int    setSel(int sel, int indx) {
      return (int)send(LB_SETSEL, sel, MAKELPARAM(indx, 0));
  }

  int    setTabStops(int num, int pos[]) {
      return (int)send(LB_SETTABSTOPS, num, (LPARAM)pos);
  }

  int    setTopIndex(int indx) {
      return (int)send(LB_SETTOPINDEX, indx, 0L);
  }
//  void  setValues(Args& args);

  int   getAnchorIndex() {
       return (int)send(LB_GETANCHORINDEX, 0, 0L);
  }

  LRESULT   getLocale() {
      return send(LB_GETLOCALE, 0, 0L);
  }

  void   setAnchorIndex(int indx) {
       send(LB_SETANCHORINDEX, (WPARAM)indx, 0L);
  }

  LRESULT   setLocale(long localeId) {
       return send(LB_SETLOCALE, (WPARAM)localeId, 0L);
  }
};

}


