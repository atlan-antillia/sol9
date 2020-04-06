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
 *  RichText.h
 *
 *****************************************************************************/

// SOL9
// 2012/02/12 Updated streamIn and streamOut method for UNICODE.
// 2012/06/25

#pragma once

#include <sol\text.h>

#include <richedit.h>
#include <richole.h>

namespace SOL {

class RichText :public Text {
private:
  static DWORD CALLBACK streamInProc(DWORD dwCookies, 
            LPBYTE buff, LONG cb, LONG* pcb)
  {
    HANDLE hfile = (HANDLE)dwCookies;
    ::ReadFile(hfile, buff, cb, (unsigned long*)pcb, NULL);
    if(*pcb <= 0) {
      *pcb = 0;
    }
    return 0;
  }

  static DWORD CALLBACK streamOutProc(DWORD dwCookies, 
            LPBYTE buff, LONG cb, LONG* pcb)
  {
    HANDLE hfile = (HANDLE)dwCookies;
    ::WriteFile(hfile, buff, cb, (unsigned long*)pcb, NULL);
    if(*pcb <= 0){
      *pcb = 0;
    }
    return 0;
  }

public:
  RichText(): Text() { }

public:
  //2012/06/25
  RichText(View* parent, const TCHAR* name, Args& args)
  :Text()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    return Text::create(parent, name, 
      args.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE)
          .set(XmNpredefined, TRUE)
        .set(XmNclassName, RICHEDIT_CLASS)); //_T("RICHEDIT")));

  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    // WM_COMMAND
    {XmNchangeCallback,    EN_CHANGE},
    {XmNerrorSpaceCallback,  EN_ERRSPACE},
    {XmNhorizScrollCallback, EN_HSCROLL},
    {XmNkillFocusCallback,  EN_KILLFOCUS},
    {XmNmaxTextCallback,  EN_MAXTEXT},
    {XmNsetFocusCallback,  EN_SETFOCUS},
    {XmNupdateCallback,    EN_UPDATE},
    {XmNvertScrollCallback,  EN_VSCROLL},

    // WM_NOTIFY 
    {XmNcorrectTextCallback, EN_CORRECTTEXT},
    {XmNdropFilesCallback,   EN_DROPFILES},
    //  {XmNimeChangeCallback,   EN_IMECHANGE},
    {XmNmsgFilterCallback,   EN_MSGFILTER},
    {XmNprotectedCallback,   EN_PROTECTED},
    {XmNrequestResizeCallback, EN_REQUESTRESIZE},
    {XmNstopNoUndoCallback,    EN_STOPNOUNDO},
    {XmNselChangeCallback,   EN_SELCHANGE},
    };
    *num = XtNumber(table);
    return table;
  }


public:
  virtual void add(const TCHAR* string)
  {
    int len = getTextLength();
    CHARRANGE range;
    range.cpMin = len;
    range.cpMax = len;
    //SetSel(len, len);
    exSetSel(&range);
    replaceSel(string);

    len = getTextLength();
    range.cpMin = len;
    range.cpMax = len;

    //SetSel(len, len);
    exSetSel(&range);
    replaceSel(_T("\r\n"));
    send(WM_SETREDRAW, 1, 0L);
  }

public:
// no \r\n.
  virtual void append(const TCHAR* string)
  {
    int len = getTextLength();
    CHARRANGE range;
    range.cpMin = len;
    range.cpMax = len;
    //SetSel(len, len);
    exSetSel(&range);

    replaceSel(string);
    send(WM_SETREDRAW, 1, 0L);
  }

public:
#ifdef UNICODE
  // no \r\n.
  virtual void append(const char* string)
  {
    StringConverter converter;
    wchar_t* wstring = converter.toWideChar(string);
    int len = getTextLength();

    CHARRANGE range;
    range.cpMin = len;
    range.cpMax = len;
    //SetSel(len, len);
    exSetSel(&range);

    replaceSel(wstring);
    send(WM_SETREDRAW, 1, 0L);

    delete [] wstring;
  }
#endif

public:
  BOOL streamIn(const TCHAR* filename, UINT format)
  {
    File file;
    if(file.openReadOnly(filename)) {
      //<Updated at="2012/02/11">
      unsigned char bom[2];
      file.read(bom, sizeof(bom));
      if (bom[0] ==0xff && bom[1] == 0xfe) {
        //UNICODE BOM
        format |= SF_UNICODE;
      } else {
        file.seekBegin(0);
      }
      //</Updated>

      EDITSTREAM es;
      es.dwCookie = (DWORD)file.getHandle();
      es.dwError = 0;
      es.pfnCallback = (EDITSTREAMCALLBACK)&RichText::streamInProc;
      send(EM_STREAMIN, (WPARAM)format, (LPARAM)&es);
      
      file.close();
      return TRUE;
    }  
    return FALSE;
  }

public:
  BOOL streamOut(const TCHAR* filename, UINT format)
  {
    File file;
    if(file.create(filename)) {
      //<Updated at="2012/02/11">
      if (format & SF_UNICODE) {
        unsigned char bom[2] = {0xff, 0xfe};
        file.write(bom, sizeof(bom));
      }
      //</Updated>


      EDITSTREAM es;
      es.dwCookie = (DWORD)file.getHandle();
      es.dwError = 0;
      es.pfnCallback = (EDITSTREAMCALLBACK)&RichText::streamOutProc;
      send(EM_STREAMOUT, (WPARAM)format, (LPARAM)&es);
      
      file.close();
      return TRUE;
    }  
    return FALSE;
  }


  BOOL  canPaste(int cbformat) {
       return (BOOL)send(EM_CANPASTE, cbformat, 0);
  }

  BOOL  displayBand(LPRECT rect) {
      return send(EM_DISPLAYBAND, 0, (LPARAM)rect);
  }
  void  exGetSel(CHARRANGE*  charRange) {
      send(EM_EXGETSEL, 0, (LPARAM)charRange);
  }
  void  exLimitText(int chTextMax) {
      send(EM_EXLIMITTEXT, 0, (LPARAM)chTextMax);
  }
  int    exLineFromChar(DWORD chPos) {
      return (int)send(EM_EXLINEFROMCHAR, 0, (LPARAM)chPos);
  }
  int    exSetSel(CHARRANGE* charRange) {
      return (int)send(EM_EXSETSEL, 0, (LPARAM)charRange);
  }
  int    findText(UINT flag, FINDTEXT* findText) {
      return (int)send(EM_FINDTEXT, (WPARAM)flag, (LPARAM)findText);
  }
  int    findTextEx(UINT flag, FINDTEXTEX* findText) {
      return (int)send(EM_FINDTEXTEX, (WPARAM)flag, (LPARAM)findText);
  }

  DWORD  getCharFormat(BOOL flag, CHARFORMAT* charFormat) {
      return send(EM_GETCHARFORMAT, flag, (LPARAM)charFormat);
  }

  UINT  getEventMask() {
      return (UINT)send(EM_GETEVENTMASK,   0, 0);
  }

  DWORD  getOptions() {
      return send(EM_GETOPTIONS, 0, 0);
  }

  DWORD  getParaFormat(PARAFORMAT* paraFormat) {
      return send(EM_GETPARAFORMAT, 0, (LPARAM)paraFormat);
  }
  int    getSelText(TCHAR* buffer) {
      return send(EM_GETSELTEXT, 0, (LPARAM)buffer);
  }
  UINT  getWordWrapMode() {
      return (UINT)send(EM_GETWORDWRAPMODE, 0, 0);
  }

  void  hideSelection(BOOL fHide, BOOL fChangeStyle) {
      send(EM_HIDESELECTION, (WPARAM)fHide, (LPARAM)fChangeStyle);
  }
  void  pasteSpecial(UINT format) {
      send(EM_PASTESPECIAL, (WPARAM)format, 0);
  }
  void  requestResize() {
      send(EM_REQUESTRESIZE, 0, 0);
  }
  int    selectionType() {
      return send(EM_SELECTIONTYPE, 0, 0);
  }
  COLORREF setBackgroundColor(BOOL flag, COLORREF color) {
      return (COLORREF)send(EM_SETBKGNDCOLOR,(WPARAM)flag,
              (WPARAM)color);
  }
  BOOL  setCharFormat(BOOL flag, CHARFORMAT* format) {
      return (BOOL)send(EM_SETCHARFORMAT, (WPARAM)flag, (LPARAM)format);
  }

  DWORD  setEventMask(DWORD mask) {
      return send(EM_SETEVENTMASK, 0, (LPARAM)mask);
  }

  DWORD  setOleCallback(IRichEditOleCallback* callback) {
      return send(EM_SETOLECALLBACK, 0, (LPARAM)callback);
  }

  DWORD  setOptions(UINT operation, UINT options) {
      return send(EM_SETOPTIONS, (WPARAM)operation, (LPARAM)options);
  }

  BOOL  setParaFormat(PARAFORMAT* format) {
      return (BOOL)send(EM_SETPARAFORMAT, 0, (LPARAM)format);
  }

  BOOL  setTargetDevice(HDC hdc, int lineWidth) {
      return (BOOL)send(EM_SETTARGETDEVICE, (WPARAM)hdc, (LPARAM)lineWidth); 
  }

  UINT  setWordWrapMode(UINT options) {
      return (UINT)send(EM_SETWORDWRAPMODE, (WPARAM)options, 0);
  }

};

}

