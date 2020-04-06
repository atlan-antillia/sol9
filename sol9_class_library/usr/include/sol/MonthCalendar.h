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
 *  MonthCalendar.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

#include <sol\Primitive.h>

namespace SOL {

class MonthCalendar :public Primitive {
private:
  static const long STYLE = (WS_TABSTOP|WS_BORDER|WS_HSCROLL);

public:
  MonthCalendar(): Primitive() { }

   MonthCalendar(View* parent, HWND hwnd)
    :Primitive(parent, hwnd) { }

public:
  //2012/-6/23
  MonthCalendar(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
          .set(XmNstyle, (LONG_PTR)MCS_DAYSTATE)
          .set(XmNclassName, (LONG_PTR)MONTHCAL_CLASS));

    setValues(args);

    return rc;
  }

public:
  Arg* MonthCalendar::getCallbackTable(int* num)
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

  /* colorID takes 
    MCSC_BACKGROUND 
    MCSC_MONTHBK  
    MCSC_TEXT  
    MCSC_TITLEBK 
    MCSC_TITLETEXT 
    MCSC_TRAILINGTEXT 
  */
  COLORREF getColor(int colorID) {
      return (COLORREF)send(MCM_GETCOLOR, colorID, 0);
  }

  int    getCurSel(SYSTEMTIME* sysTime) {
      return (int)send(MCM_GETCURSEL, 0, (WPARAM)sysTime);
  }

  DWORD  getFirstDayOfWeek() {
      return (DWORD)send(MCM_GETFIRSTDAYOFWEEK, 0, 0);
  }

  int    getMaxSelCount() {
      return (int)send(MCM_GETMAXSELCOUNT, 0, 0);
  }

  int    getMinReqRect(RECT* rect) {
      return (int)send(MCM_GETMINREQRECT, 0, (LPARAM)rect);
  }

  int    getMonthDelta() {
      return (int)send(MCM_GETMONTHDELTA, 0, 0);
  }
  int    getMonthRange(int flag, SYSTEMTIME* sysTime) {
      return (int)send(MCM_GETMONTHRANGE, flag, (LPARAM)sysTime);
  }

  int    getRange(SYSTEMTIME* sysTimeArray) {
      return (int)send(MCM_GETRANGE, 0, (LPARAM)sysTimeArray);
  }

  int    getSelRange(SYSTEMTIME* sysTimeArray) {
      return (int)send(MCM_GETSELRANGE, 0, (LPARAM)sysTimeArray);
  }

  int    getToday(SYSTEMTIME* today) {
      return (int)send(MCM_GETSELRANGE, 0, (LPARAM)today);
  }

  int    getUnicodeFormat() {
      return (int)send(MCM_GETUNICODEFORMAT, 0, 0);
  }

  DWORD  getHitTest(MCHITTESTINFO* info) {
      return (DWORD)send(MCM_HITTEST, 0, (LPARAM)info);
  }

  COLORREF setColor(int i, COLORREF color) {
      return (DWORD)send(MCM_SETCOLOR, i, (LPARAM)color);
  }

  int   setCurSel(SYSTEMTIME* sysTime) {
      return (int)send(MCM_SETCURSEL, 0, (LPARAM)sysTime);
  }
  int   setDayState(int num, MONTHDAYSTATE* stateArray) {
      return (int)send(MCM_SETDAYSTATE, num, (LPARAM)stateArray);
  }
  int   setFirstDayOfWeek(int day) {
      return (int)send(MCM_SETFIRSTDAYOFWEEK, 0, (LPARAM)day);
  }
  int   setMaxSelCount(int max) {
      return (int)send(MCM_SETMAXSELCOUNT, max, 0);
  }
  int   setMonthDelta(int delta) {
      return (int)send(MCM_SETMONTHDELTA, delta, 0);
  }

  int   setRange(short whichLimit, SYSTEMTIME* sysTimeArray) {
      return (int)send(MCM_SETMAXSELCOUNT, whichLimit, (LPARAM)sysTimeArray);
  }
  int   setSelRange(SYSTEMTIME* sysTimeArray) {
      return (int)send(MCM_SETMAXSELCOUNT, 0, (LPARAM)sysTimeArray);
  }
  int   setToday(SYSTEMTIME* sysTime) {
      return (int)send(MCM_SETTODAY, 0, (LPARAM)sysTime);
  }

  int   setUnicodeFormat(BOOL flag) {
      return (int)send(MCM_SETUNICODEFORMAT, (WPARAM)flag, 0);
  }
};

}


