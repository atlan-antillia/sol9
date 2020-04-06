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
 *  Text.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.03 Added getStringList method.
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>
#include <sol\StringList.h>
#include <sol\StringTokenizer.h>
#include <sol/StringConverter.h>

namespace SOL {

class Text :public Primitive {
private:
  static int stylesCount() {
    int count = 0;
    styles(&count);
    return count;
  }


private:
  static Arg* styles(int* count=NULL) {

    static Arg _styles[] = {
    {XmNlowerCase,       ES_LOWERCASE},
    {XmNmultiLine,       ES_MULTILINE},
    {XmNnoHideSel,       ES_NOHIDESEL},
    {XmNoemConvert,      ES_OEMCONVERT},
    {XmNpassword,       ES_PASSWORD},
    {XmNreadOnly,       ES_READONLY},
    {XmNupperCase,       ES_UPPERCASE},
    };
    if (count) {
      *count = XtNumber(_styles);
    }
    return _styles;

  }

public:
  Text(): Primitive() { }
  Text(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/06/25
  Text(View* parent, const TCHAR* name, Args& args)
    :Primitive()
  {
    create(parent, name, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {     
    Boolean rc = Primitive::create(parent, name, 
      args.set(styles(), stylesCount())
          .set(XmNstyle, (LONG_PTR)(WS_TABSTOP|ES_AUTOHSCROLL))
          .set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE)
        .set(XmNpredefined, TRUE)
        .set(XmNuseDefaultFont, _T("true"))
          .set(XmNclassName,  _T("Edit")) );

    setValues(args);
    return rc;
  }

public:
  virtual void add(const TCHAR* string)
  {
    int len = getTextLength();
    setSel(len, len);
    replaceSel(string);
    len = getTextLength();
    setSel(len, len);
    replaceSel(_T("\r\n"));
    send(WM_SETREDRAW, 1, 0L);
  }

public:
  virtual void append(const TCHAR* string)
  {
    int len = getTextLength();
    setSel(len, len);
    replaceSel(string);
    send(WM_SETREDRAW, 1, 0L);
  }

public:
#ifdef UNICODE
  virtual void append(const char* string)
  {
    StringConverter converter;
    wchar_t* wstring = converter.toWideChar(string);

    int len = getTextLength();
    setSel(len, len);
    replaceSel(wstring);
    send(WM_SETREDRAW, 1, 0L);
    delete [] wstring;
  }
#endif

public:
// 1999.08.19 
  virtual void printf(const TCHAR* format,...)
  {
    TCHAR* buffer = new TCHAR[1024];

    va_list pos;
    va_start(pos, format);
    //vsprintf_s(buffer, 1024, format, pos);
    _vstprintf_s(buffer, 1024, format, pos);

    va_end(pos);

    append(buffer);

    delete [] buffer;
  }

public:
#ifdef UNICODE
  virtual void printf(const char* format,...)
  {
    char* buffer = new char[1024];

    va_list pos;
    va_start(pos, format);
    vsprintf_s(buffer, 1024, format, pos);
    //_vstprintf_s(buffer, 1024, format, pos);

    va_end(pos);

    append(buffer);

    delete [] buffer;
  }

#endif

public:
  int getLine(int n, TCHAR* string, int num)
  {
    *string     = LOBYTE(num);
    *(string+1) = HIBYTE(num);
    int len = (int) send(EM_GETLINE, n, (LPARAM)string);
    string[len] = NULL;
    return len;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNchangeCallback,    EN_CHANGE},
    {XmNerrorSpaceCallback,  EN_ERRSPACE},
    {XmNhorizScrollCallback, EN_HSCROLL},
    {XmNkillFocusCallback,  EN_KILLFOCUS},
    {XmNmaxTextCallback,  EN_MAXTEXT},
    {XmNsetFocusCallback,  EN_SETFOCUS},
    {XmNupdateCallback,    EN_UPDATE},
    {XmNvertScrollCallback,  EN_VSCROLL},
    };
    *num = XtNumber(table);
    return table;
  }

public:
  void getSel(int* start, int* end)
  {
    int s, e;
    send(EM_GETSEL, (WPARAM)&s, (LPARAM)&e);
    *start = s;
    *end   = e;
  }

public:
  void getValues(Args& args)
  {
    Primitive::getValues(args);

    getStyle(args, styles(), stylesCount());

    LONG_PTR* val = (LONG_PTR*)args.get(XmNvalue);
    if(val) {
      //HWND hwnd = getWindow();
      int len = getTextLength();
      TCHAR* buff = new TCHAR[len+1];
      getText(buff, len+1);
      *val = (LONG_PTR)buff;
    }
  }

public:
  BOOL load(TCHAR* filename)
  {
    HANDLE  fd = ::CreateFile(filename,
        GENERIC_READ,        // Access mode 
        1,                    // 2017/01/29 Modified to be true. Share mode 
        NULL,                 // Security descriptor 
        OPEN_EXISTING,        // How to create 
        FILE_ATTRIBUTE_READONLY,  // File attributes 
        NULL);           

     if(fd != INVALID_HANDLE_VALUE) {
      int size   = ::GetFileSize(fd, NULL);
      //2009/10/12 
      //if(size < 64000) {
      if (size <65535) {
        char* buff = new char[size+1];
        if(buff) {
          unsigned long len = 0;
          ::ReadFile(fd, buff, size, &len, NULL);
          buff[len] = NULL;
          setText(buff);
          delete [] buff;
        }
      } else {
        MessageBox(NULL, 
          _T("Text size is too large!,\r\nCannot read the content of this file into this EditControl\n"),
                _T("SOL9"), MB_OK);

      }
      ::CloseHandle(fd);

      return TRUE;
    }
    return FALSE;
  }

public:
  BOOL  save(TCHAR* filename)
  {
    HANDLE fd = ::CreateFile(filename,   
        GENERIC_WRITE,      // Access mode 
        0,            // Share mode 
      NULL,          // Security descriptor 
        CREATE_ALWAYS,      // How to create: Create always 
        FILE_ATTRIBUTE_NORMAL,  // File attributes 
        NULL); 

    if(fd != INVALID_HANDLE_VALUE) {
      int size = getCharTextLength();
      if (size <65535) {
        char* buff = new char[size+1];
        if(buff) {
        // size + 1
          size_t rc     = getText(buff, size+1);
          buff[rc]   = NULL;
          unsigned int len = 0;
        
          ::WriteFile(fd, buff, size, (unsigned long*)&len, NULL);
          ::CloseHandle(fd);

          delete [] buff;
          return TRUE;
        }
      } else {
        MessageBox(NULL, _T("Text size is too large!,\r\nCannot save the Text of this EditControl to a file\n"),
                _T("SOL9"), MB_OK);

      }
    }
    return FALSE;
  }

public:
  void setValues(Args& args)
  {
    Primitive::setValues(args);
    updateStyle(args, styles(), stylesCount());

    LONG_PTR val;
    if(args.get(XmNvalue, &val))
      setText((TCHAR*)val);
  }

public:
  // 1999.09.03
  int getStringList(StringList& list)
  {
  // Flatten the text by replacing "\r\n" with "  ".
    TCHAR* text = getText();
    int rc = 0;
    if (text && strlen(text)) {
      TCHAR* ptr = text;
   
      while (ptr = (TCHAR*)strstr(ptr, _T("\r\n")) ) {
        *ptr = ' ';
        *(ptr+1) = ' ';
        ptr = ptr + 2;
      }

      StringTokenizer tokenizer(text);
      String token = _T("");

      // Get a token and append it to the list.
      while (tokenizer.getToken(token)) {
        if (token.getLength() >0) {
          list.add((const TCHAR*)token);
          rc++;
        }
        token = _T("");
      }
      delete [] text;
    }
    return rc;
  }

  int    canUndo() {
      return (int)send(EM_CANUNDO, 0, 0L);
  }
  void   clear() {
      setText(_T(""));
  }
  void   copy() {
      send(WM_COPY, 0, 0L);
  }
  void   cut() {
      send(WM_CUT, 0, 0L);
  }
  void  emptyUndoBuffer() {
      send(EM_EMPTYUNDOBUFFER, 0, 0L);
  }

  void  enableWriting() {
      send(EM_SETREADONLY, FALSE, 0L);
  }

  int    fmtLines(int fmt) {
      return (int)send(EM_FMTLINES, fmt, 0L);
  }

//  Arg*   getCallbackTable(int* num);

  int    getFirstVisibleLine() {
      return (int)send(EM_GETFIRSTVISIBLELINE, 0, 0L);
  }

  HANDLE  getHandle() {
      return (HANDLE)send(EM_GETHANDLE, 0, 0L);
  }

//  int   getLine(int n, TCHAR* string, int num);  

  int    getLineCount() {
      return (int)send(EM_GETLINECOUNT, 0, 0L);
  }

  // 1999.09.03
//  int    getStringList(StringList& list);

  int    getModify() {
      return (int)send(EM_GETMODIFY, 0, 0L);
  }
  TCHAR  getPasswordChar() {
      return (TCHAR)send(EM_GETPASSWORDCHAR, 0, 0L);
  }
  void  getRect(RECT* rect) {
      send(EM_GETRECT, 0, (LPARAM)rect);
  }

//  void   getSel(int* start, int* end);

  int    getTextLength() {
      return (int)send(WM_GETTEXTLENGTH, 0, 0L);
  }
  EDITWORDBREAKPROC  getWordBreakProc() {
      return (EDITWORDBREAKPROC)send(EM_GETWORDBREAKPROC, 0, 0L);
  }
//  void  getValues(Args& args);

//  BOOL  load(TCHAR* filename);

  void   limitText(int len) {
      send(EM_LIMITTEXT, len, 0L);
  }
  int    lineFromChar(int pos) {
      return (int)send(EM_LINEFROMCHAR, pos, 0L);
  }
  int    lineIndex(int line) {
      return (int)send(EM_LINEINDEX, line, 0L);
  }
  int    lineLength(int indx) {
      return (int)send(EM_LINELENGTH, indx, 0L);
  }
  void  lineScroll(int vert, int horiz) {
      send(EM_LINESCROLL, horiz, vert);
  }
  void   paste() {
      send(WM_PASTE, 0, 0L);
  }
  void   replaceSel(const TCHAR* string) {
      send(EM_REPLACESEL, 0, (LPARAM)string);
  }
//  BOOL  save(TCHAR* filename);

  void  setHandle(WORD handle) {
      send(EM_SETHANDLE, handle, 0L);
  }
  void  setModify(int flag) {
      send(EM_SETMODIFY, flag, 0L);
  }
  void  setPasswordChar(int ch) {
      send(EM_SETPASSWORDCHAR, ch, 0L);
  }
  void  setReadOnly() {
      send(EM_SETREADONLY, TRUE, 0L);
  }         

  void  setRect(LPRECT rect) {
      send(EM_SETRECT, 0, (LPARAM)rect);
  }
  void  setRectNP(LPRECT rect) {
      send(EM_SETRECTNP, 0, (LPARAM)rect);
  }
  void  setSel(int start, int end) {
      send(EM_SETSEL, start, end);
  }
  int    setTabStops(int num, int pos[]) {
      return (int)send(EM_SETTABSTOPS, num, (LPARAM)pos);
  }
//  void  setValues(Args& args);

  int    setWordBreakProc(FARPROC proc) {
      return (int)send(EM_SETWORDBREAKPROC, 0, (LPARAM)proc);
  }
  int    undo() {
      return (int)send(EM_UNDO, 0, 0L);
  }
  void   scroll(int action) {
       send(EM_SCROLL, (WPARAM)action, 0L);
  }  
  void   scrollCaret() {
       send(EM_SCROLLCARET, 0, 0L);
  }

  DWORD  getMargins() {
      return (DWORD)send(EM_GETMARGINS, 0, 0);
  }
  void  setLimitText(int length) {
      send(EM_SETLIMITTEXT, length, 0L);
  }
  LRESULT    getLimitText() {
      return send(EM_GETLIMITTEXT, 0, 0L);
  }
  LRESULT    getThumb() {
      return send(EM_GETTHUMB, 0, 0);
  }

  LRESULT  posFromChar(int charIndex) {
      return send(EM_POSFROMCHAR, (WPARAM)charIndex, 0);
  }
  void  setMargins(int flag, WORD left, WORD right) {
      send(EM_SETMARGINS, (WPARAM)flag, MAKELONG(left, right));
  }
};

}


