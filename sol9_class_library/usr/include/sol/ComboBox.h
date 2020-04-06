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
 *  ComboBox.h
 *
 *****************************************************************************/

// SOL++2000
// 2000/02/18
// 2001/03/19 Added getPreferredSize method.
// 2001/03/29 Added getControlHeight, setControlHeight methods.
// 2001/03/29 Added static variables itemsListDelim, heightMargin.

// 2009/09/22 Added getString method
// 2012/06/22

#pragma once

#include <sol\Primitive.h>
#include <sol\WString.h>
#include <sol/StringConverter.h>

namespace SOL {

class ComboBox :public Primitive {

private:
  // 2001/03/29 Added CBS_AUTOHSCROLL style
  static const long STYLE = (const long)(WS_TABSTOP|WS_VSCROLL|CBS_NOINTEGRALHEIGHT|CBS_AUTOHSCROLL);

  static const TCHAR itemsListDelim = '\n';

  static const int heightMargin = 2;

  static int stylesCount()
  {
    int count = 0;
    styles(&count);
    return count;
  }

  static Arg*  styles(int* count=NULL)
  {
    static  Arg _styles[] = {
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
  ComboBox():Primitive() { }

  ComboBox(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/22
  ComboBox(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = False;
    rc = Primitive::create(parent, name, 
      args.set(styles(), stylesCount())
          .set(XmNpredefined, TRUE)
          .set(XmNstyle, (LONG_PTR)STYLE)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName, _T("ComboBox")));

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
    {XmNsetFocusCallback,    CBN_SETFOCUS}
    };

    *num = XtNumber(table);
    return table;
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
      // 2001/03/31
      // Compute the length of string buffer to store all 
      // item-texts separated with a new line .
      for(int n = 0; n< count; n++) {
        buffLen = buffLen + getLBTextLen(n) + 1; //strlen("\n");  
      }   

      TCHAR* list = new TCHAR[buffLen];
      *list      = NULL;
      TCHAR* buff = list;
      for(int i = 0; i< count; i++) {
        int len = getLBTextLen(i);
        getLBText(i, buff);
        buff += len;
      
        if(i < count -1) {
          *buff = itemsListDelim;
        }
        buff++;
      }
      *buff = ZERO;
      *val  = (LONG_PTR)list;
    }
  }

public:
  // 2001/03/29
  void setValues(Args& args)
  {  
    LONG_PTR v;
    if (!args.get(XmNwidth, &v) ) {
      args.set(XmNwidth, 100);
    }
    if (!args.get(XmNheight, &v) ) {
      args.set(XmNheight, 100);
    }
  

    Primitive::setValues(args);

    updateStyle(args, styles(), stylesCount());

    /*
    */
  
    LONG_PTR  val;
    if (args.get(XmNmaxLength, &val))
      limitText((int)val);

    if (args.get(XmNlabelString, &val))
      setText((TCHAR*)val);

    // XmNitems & XmNitemCount;
    TCHAR** items = NULL;
    int     count = 0;
    if (args.get(XmNitemCount, &val))
      count = (int)val;
    if (args.get(XmNitems, &val))
      items = (TCHAR**)val;
    if (count> 0 && items) {
      resetContent();
      for(int i = 0; i<count; i++) {
        addString(items[i]);
      }
    }

    // XmNitemsList
    TCHAR* list = NULL;
    if (args.get(XmNitemsList, &val)) {
      resetContent();
      TCHAR* item = (TCHAR*)val;
      size_t slen = strlen(item)+1;
      list = new TCHAR[slen];
      strcpy_s(list, slen, item);
    }

    if (list) {
      TCHAR* str = list;
      TCHAR* ptr = list;
      while(*ptr) {
        if(*ptr == itemsListDelim) {  //2001/04/01
          *ptr++ = NULL;
          addString(str);
          str = ptr;
        }
        else {
          ptr++;
        }
      }
      if(str)  addString(str);
      if(list) delete[] list;
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
    ComboBox::findFiles(attr, pattern);  
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


// 2001/03/19
public:
  void getPreferredSize(Dimension& d)
  {
    int w, h;
    getSize(w, h);

    LONG style   = (LONG)getWindowLongPtr(GWL_STYLE);
    if ((style & CBS_DROPDOWN) ||
      (style & CBS_DROPDOWNLIST )) {
      h = getControlHeight() + heightMargin;
    }
    d.set(w, h);
  }


  int   addString(const TCHAR* string) {
      return (int)send(CB_ADDSTRING, 0, (LPARAM)string);
  }

  //2017/07/30
  int   addString(const WString* string) {
    StringConverter converter;
    StringT<char> mb;
    converter.toMultiByte((const wchar_t*)(*string), mb);
     return (int)send(CB_ADDSTRING, 0, (LPARAM)(const char*)mb );
  }

  const TCHAR*  defaultCallbackName() { 
    return XmNdefaultActionCallback; 
  }

  void clear()
  {
    resetContent();
  }

  int   deleteString(int indx) {
      return (int)send(CB_DELETESTRING, indx, 0L);
  }
  int    dir(int attr, const TCHAR* string) {
      return (int)send(CB_DIR, attr, (LPARAM)string);
  }

  int    findString(int indx, TCHAR* string) {
      return (int)send(CB_FINDSTRING, indx, (LPARAM)string);
  }
  int    findStringExact(int indx, TCHAR* string) {
      return (int)send(CB_FINDSTRINGEXACT, indx, (LPARAM)string);
  }
  
//  Arg*  getCallbackTable(int* num);

  int   getCount() {
      return (int)send(CB_GETCOUNT, 0, 0L);
  }

  int    getCurSel() {
      return (int)send(CB_GETCURSEL, 0, 0L);
  }

  int    getDroppedControlRect(RECT* rect) {
      return (int)send(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)rect);
  }

  int    getDroppedState() {
      return (int)send(CB_GETDROPPEDSTATE, 0, 0L);
  }

  LRESULT  getEditSel() {
      return send(CB_GETEDITSEL, 0, 0L);
  }

  int    getExtendedUI() {
      return (int)send(CB_GETEXTENDEDUI, 0, 0L);
  }

  LRESULT  getItemData(int indx) {
      return send(CB_GETITEMDATA, indx, 0L);
  }

  int    getItemHeight(int indx) {
      return (int)send(CB_GETITEMHEIGHT, indx, 0L);
  }

  // 2001/03/29
  int     getControlHeight() {
            //Return the height of the edit control(or static-text) portion of the combo box.
      return (int)send(CB_GETITEMHEIGHT, (WPARAM)-1, 0L);
  }

  bool  getString(int indx, String& string)
  {
    bool rc = false;
    int len = getLBTextLen(indx);

    if (len >0) {
      TCHAR* buffer = new TCHAR[len+1];
      memset(buffer, (TCHAR)0, len+1);
      if (getLBText(indx, buffer)) {

        string.shallowCopy(buffer);
        rc = true;
      }
    }
    return rc;
  }

  bool  getString(int indx, WString& string)
  {
    bool rc = false;
    int len = getLBTextLen(indx);

    if (len >0) {
      wchar_t* buffer = new wchar_t[len+1];
      memset(buffer, (wchar_t)0, len+1);
      if (send(CB_GETLBTEXT, indx, (LPARAM)buffer)) {

        string.shallowCopy(buffer);
        rc = true;
      }
    }
    return rc;
  }
  
  int    getLBText(int indx, TCHAR* buffer) {
      return (int)send(CB_GETLBTEXT, indx, (LPARAM)buffer);
  }

  int    getLBTextLen(int indx) {
      return (int)send(CB_GETLBTEXTLEN, indx, 0L);
  }

//  void  getValues(Args& args);

  int   insertString(int indx, TCHAR* string) {
      return (int)send(CB_INSERTSTRING, indx, (LPARAM)string);
  }
  int    limitText(int len) {
      return (int)send(CB_LIMITTEXT, len, 0L);
  }
  void  resetContent() {
      send(CB_RESETCONTENT, 0, 0L);
  }

  int    selectString(int indx, TCHAR* string) {
      return (int)send(CB_SELECTSTRING, indx, (LPARAM)string);
  }

  int    setCurSel(int indx) {
      return (int)send(CB_SETCURSEL, indx, 0L);
  }
  
  int    setEditSel(int start, int end) {
      return (int)send(CB_SETEDITSEL, 0, MAKELONG(start, end));
  }
  int    setExtendedUI(int flag) {
      return (int)send(CB_SETEXTENDEDUI, flag, 0L);
  }
  int    setItemData(int indx, LONG data) {
      return (int)send(CB_SETITEMDATA, indx, data);
  }
  int    setItemHeight(int indx, int height) {
      return (int)send(CB_SETITEMHEIGHT, indx, (LPARAM)height);
  }
  int     setControlHeight(int height) {
      return (int)send(CB_SETITEMHEIGHT, (WPARAM)-1, (LPARAM)height);
  }

//  void  setValues(Args& args);  

  void  showDropDown(int showCmd) {
      send(CB_SHOWDROPDOWN, showCmd, 0L);
  }

  LRESULT   getLocale() {
      return send(CB_GETLOCALE, 0, 0L);
  }

  LRESULT   setLocale(long localeId) {
       return send(CB_SETLOCALE, (WPARAM)localeId, 0L);
  }

  String getCurrentSelection()
  {
    int i = getCurSel();
    if (i >=0 ) {
      TCHAR text[MAX_PATH];

      getLBText(i, text);
      return String(text);
    } else {
      throw IException("Not item selected");
    }
  }
  
  int    setCurrentSelection(int indx) {
      return (int)send(CB_SETCURSEL, indx, 0L);
  }

  void  setDroppedWidth(int width)
  {
    send(CB_SETDROPPEDWIDTH, width, 0);
  }
  
};

}

