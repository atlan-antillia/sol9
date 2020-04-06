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
 *  ToolBar.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class ToolBar :public Primitive {

private:
  static TBBUTTON* getTBButtons(int* count=NULL)
  {
  
  static TBBUTTON buttons[] =  {

    {STD_FILENEW,  STD_FILENEW,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 0},

    {  STD_FILEOPEN, STD_FILEOPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,   0, 1},

    {STD_FILESAVE, STD_FILESAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,  0, 2},

    {STD_PRINTPRE, STD_PRINTPRE,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 3},

    {STD_PRINT,   STD_PRINT,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 4},
    { 0,  FALSE,   FALSE,           TBSTYLE_SEP,    
    0,0, 0,0},

    {STD_CUT, STD_CUT,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 5},

    {STD_COPY, STD_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 6},

    {STD_PASTE,  STD_PASTE,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0, 7},

    {STD_UNDO, STD_UNDO,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0, 8},
    {STD_REDOW, STD_REDOW,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0,9},
    {STD_DELETE, STD_DELETE,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0, 0,10},
    {STD_FIND, STD_FIND,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0,11},
    {STD_REPLACE, STD_REPLACE,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0,12},
    {STD_PROPERTIES, STD_PROPERTIES,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0,13},
    { 0,  FALSE,   FALSE,           TBSTYLE_SEP,    
    0,0,0, 0},
    {STD_HELP, STD_HELP,TBSTATE_ENABLED, TBSTYLE_BUTTON, 
    0,0,0,14},
    };

    if (count) {
      *count = XtNumber(buttons);
    }
    return buttons;
  }

public:
  ToolBar():Primitive() { }
 
public:
  //2012/06/25
  ToolBar(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,
      args.set(XmNpredefined, TRUE)
          .set(XmNstyle, TBSTYLE_TOOLTIPS)
          .set(XmNclassName, (LONG_PTR)TOOLBARCLASSNAME));

    send(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

    setValues(args);

    return rc;
  }

public:
  void setValues(Args& args)
  {
//  Primitive::setValues(args);
    LONG_PTR val = args.get(XmNtoolBarBitmapID);
    TBADDBITMAP addbmp;  
    memset(&addbmp, 0, sizeof(TBADDBITMAP));
    int count = 0;
    TBBUTTON* buttons = getTBButtons(&count);
  
    if(val == IDB_STD_SMALL_COLOR || val ==IDB_STD_LARGE_COLOR) {
      addbmp.hInst = HINST_COMMCTRL;
      addbmp.nID   = (int)val;
      send(TB_ADDBITMAP, count-2, (LPARAM)&addbmp);
      send(TB_ADDBUTTONS, count, (LPARAM)buttons);
    }
    else if(val) {
      addbmp.hInst = getInstanceHandle();
      LONG_PTR num = args.get(XmNnumBitmaps);
      addbmp.nID   = (int)val;  //val should be a bitmaphandle.
      send(TB_ADDBITMAP, num, (LPARAM)&addbmp);
    }
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNgetButtonInfoCallback,  (LONG_PTR)TBN_GETBUTTONINFO},
    {XmNbeginDragCallback,      (LONG_PTR)TBN_BEGINDRAG},
    {XmNendDragCallback,        (LONG_PTR)TBN_ENDDRAG},
    {XmNbeginAdjustCallback,    (LONG_PTR)TBN_BEGINADJUST},
    {XmNendAdjustCallback,      (LONG_PTR)TBN_ENDADJUST},
    {XmNresetCallback,          (LONG_PTR)TBN_RESET},
    {XmNqueryInsertCallback,    (LONG_PTR)TBN_QUERYINSERT},
    {XmNqueryDeleteCallback,    (LONG_PTR)TBN_QUERYDELETE},
    {XmNtoolbarChangeCallback,  (LONG_PTR)TBN_TOOLBARCHANGE},
    {XmNcustHelpCallback,       (LONG_PTR)TBN_CUSTHELP},
    };
 
     *num = XtNumber(table);
    return table;
  }

public:
  int getHeight()
  {
    RECT r;
    getWindowRect(&r);
    return r.bottom - r.top;
  }


  BOOL  addBitmap(int num, TBADDBITMAP* bitmaps) {
      return (BOOL)send(TB_ADDBITMAP, num, (LPARAM)bitmaps);
  }
 
  BOOL  addButtons(int num, TBBUTTON* buttons) {
      return (BOOL)send(TB_ADDBUTTONS, num, (LPARAM)buttons);
  }
  int    addString(const TCHAR* strings) {
      return (int)send(TB_ADDSTRING, 0, (LPARAM)strings);
  }
  void  autoSize() {
      send(TB_AUTOSIZE, 0, 0);
  }
  int    buttonCount() {
      return (int)send(TB_BUTTONCOUNT, 0, 0L);
  }
  void  buttonStructSize() {
      send(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0L);
  }
  void  changeBitmap(int id, int idBitmap ) {
       send(TB_CHECKBUTTON, id, idBitmap);
  }
  void  checkButton(int id) {
       send(TB_CHECKBUTTON, id, TRUE);
  }

  int    commandToIndex(int cmd) {
      return (int)send(TB_COMMANDTOINDEX, cmd, 0L);
  }
  void   customize() {
      send(TB_CUSTOMIZE, 0, 0);
  }

  BOOL   deleteButton(int id) {
      return (BOOL)send(TB_DELETEBUTTON, id, 0L);
  }
  BOOL   disableButton(int id) {
       return (BOOL)send(TB_ENABLEBUTTON, id, FALSE);
  }
  BOOL   enableButton(int id) {
       return (BOOL)send(TB_ENABLEBUTTON, id, TRUE);
  }

  BOOL   getButton(int id, TBBUTTON* lpb) {
      return (BOOL)send(TB_GETBUTTON, id, (LPARAM)lpb);
  }
  int   getButtonText(int id, TCHAR* text) {
      return (int)send(TB_GETBUTTONTEXT, id, (LPARAM)text);
  }
  int    getBitmap(int id) {
      return (int)send(TB_GETBITMAP, id, 0);
  }

  int     getBitmapFlags() {
      return (int)send(TB_GETBITMAPFLAGS, 0, 0);
  }


  BOOL   getItemRect(int id, RECT* rect) {
      return (BOOL)send(TB_GETITEMRECT, id, (LPARAM)rect);
  }
  int    getRows() {
      return (int)send(TB_GETROWS, 0, 0);
  }
  BOOL  getState(int id) {
      return (BOOL)send(TB_GETSTATE, id, 0L);
  }

  HWND  getTooltips() {
      return (HWND)send(TB_GETTOOLTIPS, 0, 0);
  }
  void   hideButton(int id) {
       send(TB_HIDEBUTTON, id, TRUE);
  }

  BOOL   indeterminate(int id, BOOL flag) {
      return (BOOL)send(TB_INDETERMINATE, id, flag); 
  }
  BOOL   insertButton(int id, TBBUTTON* tbbutton) {
      return (BOOL)send(TB_INSERTBUTTON, id, (LPARAM)tbbutton);
   }

  BOOL   isButtonEnabled(int id) {
      return (BOOL)send(TB_ISBUTTONENABLED, id, 0L);
  }
  BOOL   isButtonChecked(int id) {
      return (BOOL)send(TB_ISBUTTONCHECKED, id, 0L);
  }
  BOOL   isButtonPressed(int id) {
      return (BOOL)send(TB_ISBUTTONPRESSED, id, 0L);
  }
  BOOL   isButtonHidden(int id) {
      return (BOOL)send(TB_ISBUTTONHIDDEN, id, 0L);
  }
  BOOL   isButtonIndeterminate(int id) {
      return (BOOL)send(TB_ISBUTTONINDETERMINATE, id, 0L);
  }
  void   pressButton(int id) {
       send(TB_PRESSBUTTON, id, TRUE);
  }

  BOOL   setBitmapSize(int dx, int dy) {
      return (BOOL)send(TB_SETBITMAPSIZE, 0, MAKELONG(dx, dy));
  }
  BOOL   setButtonSize(int dx, int dy) {
      return (BOOL)send(TB_SETBUTTONSIZE, 0, MAKELONG(dx, dy));
  }
  BOOL   setCmdId(int indx, int cmdId) {
         return (BOOL)send(TB_SETCMDID, indx, cmdId);
  }
  void   setParent(HWND parent) {
      send(TB_SETPARENT, (WPARAM)parent, 0);
  }
  void   setRows(int rows, int flag, RECT* rc) {
      send(TB_SETROWS, MAKELONG(rows, flag), (LPARAM)rc);
  }

  void   setState(int id) {
      send(TB_SETSTATE, id, 0);
  }
  void   setTooltips(HWND tooltip) {
      send(TB_SETTOOLTIPS, (WPARAM)tooltip, 0);  
  }
//  void  setValues(Args& args);

  void   showButton(int id) {
       send(TB_HIDEBUTTON, id, FALSE);
  }

  void   ynCheckButton(int id) {
       send(TB_CHECKBUTTON, id, FALSE);
  }
  void   unpressButton(int id) {
       send(TB_PRESSBUTTON, id, FALSE);
  }
};

}
