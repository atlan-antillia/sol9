/******************************************************************************
 *
 * Copyright (c) 1999-2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Window.h
 *
 *****************************************************************************/

//2017/03/10 Added getWindowLongPtr and setWindowLongPtr.

#pragma once

#include <sol\Object.h>
#include <sol\Typedef.h>
#include <sol\String.h>
#include <sol\StringT.h>
#include <sol\Event.h>

//2017/09/15 Removed #ifdef #endif
#pragma comment(linker,"\"/manifestdependency:type='win32' \
           name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
           processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace SOL {

class Window :public Object {
private:
  HWND    hwnd;

public:
  Window()
  :hwnd(NULL)
  {
    //
  }

public:
  ~Window()
  {
  }

public:
  TCHAR* getText()
  {
    int len = getTextLength();
    TCHAR* text = new TCHAR[len + 1];
    if(text) {
      ::GetWindowText(hwnd, text, len+1);
    }
    return text;     
  }


  HWND  childWindowFromPoint(POINT pt) {
      return ::ChildWindowFromPoint(hwnd, pt);
  }

  void  destroyWindow() {
      if (isWindow())
      ::DestroyWindow(hwnd);
  }

  Boolean  isEqual(HWND handle) {
      return (hwnd == handle);
  }
  void  enableWindow(Boolean flag) {
      ::EnableWindow(hwnd, flag);
  }
  void  getClassName(TCHAR* name, int size) {
      ::GetClassName(hwnd, name, size);
  }

  HWND  getFocus() {
      return ::GetFocus();
  }

  HINSTANCE  getInstanceHandle() {
      return reinterpret_cast<HINSTANCE>(getWindowLongPtr(GWLP_HINSTANCE));
  }

  Boolean  getPlacement(WINDOWPLACEMENT* place) {
      return ::GetWindowPlacement(hwnd, place);
  }

  HANDLE  getProp(const TCHAR* name) {
      return ::GetProp(hwnd, name);
  }

  HWND  getWindow() { return hwnd; }

  //2017/03/10
  long  getWindowLong(int indx) {
    return (long)::GetWindowLongPtr(hwnd, indx);
  }
 
  void  setWindowLong(int indx, LONG_PTR value) {
    ::SetWindowLongPtr(hwnd, indx, (LONG_PTR)value);
  }

  LONG_PTR   getWindowLongPtr(int index) {
    return ::GetWindowLongPtr(hwnd, index);
  }
  
  WORD  getWindowWord(int indx) {
      return ::GetWindowWord(hwnd, indx);
  }
   long  getClassLong(int indx) {
      return ::GetClassLong(hwnd, indx);
  }
   WORD  getClassWord(int indx) {
      return ::GetClassWord(hwnd, indx);
  }

  //2008/07/02
  virtual void getClientSize(int& width, int& height) {
      RECT r;
      ::GetClientRect(hwnd, &r);
      width  = r.right - r.left;
      height = r.bottom - r.top;
  }

  virtual void getClientRect(RECT* rect) {
      ::GetClientRect(hwnd, rect);
  }

  void  getWindowRect(RECT* rect) {
      ::GetWindowRect(hwnd, rect);
  }

  //2015/11/26
  void  getWindowSize(int& width, int& height) {
      RECT r;
      ::GetWindowRect(hwnd, &r);
      width  = r.right - r.left;
      height = r.bottom - r.top;    
  }

  Boolean  isEnabled() {
      return ::IsWindowEnabled(hwnd);
  }
  Boolean  isVisible() {
      return ::IsWindowVisible(hwnd);
  }
  Boolean  isWindow()  {
      return ::IsWindow(hwnd);
  }
  Boolean  killTimer(UINT id) {
      return ::KillTimer(hwnd, id);
  }

  virtual void  move(int x, int y, int width, int height, Boolean flag = TRUE) {
      ::MoveWindow(hwnd, x, y, width, height, flag);
  }

  virtual void  reshape(int x, int y, int width, int height, Boolean flag = TRUE) {
      ::MoveWindow(hwnd, x, y, width, height, flag);
  }


  //2009/10/17
  size_t    getText(__out String& text) {
    size_t size = ::GetWindowTextLength(hwnd);
    if (size>0) {
      TCHAR* tstring = new TCHAR[size+1];
      if (GetWindowText(hwnd, tstring, (int)size+1)>0) {
        text.shallowCopy(tstring);
      }    
    }
    return size;
  }

  //2009/10/18
  size_t    getText(__out StringT<char>& text) {
    size_t size = ::GetWindowTextLengthA(hwnd);
    if (size>0) {
      char* string = new char[size+1];
      if (GetWindowTextA(hwnd, string, (int)size+1)>0) {
        text.shallowCopy(string);
      }    
    }
    return size;
  }

  //2009/10/18
  size_t    getText(__out StringT<wchar_t>& text) {
    size_t size = ::GetWindowTextLengthW(hwnd);
    if (size>0) {
      wchar_t* string = new wchar_t[size+1];
      if (
        GetWindowTextW(hwnd, string, (int)size+1)>0) {
        text.shallowCopy(string);
      }    
    }
    return size;
  }

  size_t    getText(char* text, size_t len) {
      return ::GetWindowTextA(hwnd, text, (int)len);
  }

  size_t    getText(wchar_t* text, size_t len) {
      return ::GetWindowTextW(hwnd, text, (int)len);
  }

  int    getTextLength() {
      return ::GetWindowTextLength(hwnd);
  }

  int    getCharTextLength() {
      return ::GetWindowTextLengthA(hwnd);
  }

  int    getWCharTextLength() {
      return ::GetWindowTextLengthW(hwnd);
  }

  void  getCursorPos(POINT* p) {
      ::GetCursorPos(p);
  }

  //2012/04/08
  Boolean  invalidateAll() {
      RECT r;
      getClientRect(&r);
      return ::InvalidateRect(hwnd, &r, TRUE);
  }
  
  
  Boolean  invalidate(const RECT* rect, Boolean flag = TRUE) {
      return ::InvalidateRect(hwnd, rect, flag);
  }

  Boolean  invalidate(HRGN r, Boolean flag = TRUE) {
      return ::InvalidateRgn(hwnd, r, flag);
  }

  long  post(UINT message, WPARAM wParam=0, LPARAM lParam=0) {  //2012/09/27
      return ::PostMessage(hwnd, message, wParam, lParam);
  }

  HANDLE  removeProp(const TCHAR* name) {
      return ::RemoveProp(hwnd, name);
  }

  Boolean  releaseCapture() {
      return ::ReleaseCapture();
  }
  int    showCursor(Boolean flag) {
      return ::ShowCursor(flag);
  }

  Boolean  scroll(int dx, int dy, RECT* scroll, RECT* clip,
        HRGN  hrgnUpdate=NULL,LPRECT  prcUpdate=NULL,
      UINT flags = SW_ERASE|SW_INVALIDATE|SW_SCROLLCHILDREN) {
      return ::ScrollWindowEx(hwnd, dx, dy, scroll, clip,
          hrgnUpdate, prcUpdate, flags);
  }

  LRESULT  send(UINT message, WPARAM wParam, LPARAM lParam) {
      return ::SendMessage(hwnd, message, wParam, lParam);
  }
  void  setClassLong(int indx, long val) {
      ::SetClassLong(hwnd, indx, val);
  }
  void  setClassWord(int indx, WORD val) {
      ::SetClassWord(hwnd, indx, val);
  }
  HWND  setFocus(HWND target) {
      return ::SetFocus(target);
  }

  HWND  setFocus() {
      return ::SetFocus(hwnd);
  }

  void  setParent(HWND hParent) {
        ::SetParent(hwnd, hParent);
  }
  Boolean  setPlacement(WINDOWPLACEMENT* place) {
      return ::SetWindowPlacement(hwnd, place);
  }
  Boolean  setPos(HWND insertAfter, int x, int y, int width,
        int height, UINT flag) {
      return ::SetWindowPos(hwnd, insertAfter, x, y,
        width, height, flag);
  }
  Boolean  setProp(const TCHAR* name, HANDLE data) {
      return ::SetProp(hwnd, name, data);
  }

  //<modified date="2009/10/12">
  void  setText(const char* text) {
      ::SetWindowTextA(hwnd, text);
  }

  void  setText(const wchar_t* text) {
      ::SetWindowTextW(hwnd, text);
  }

  void  setText(int number) {
    TCHAR string[256];
    _stprintf_s(string, CountOf(string), _T("%d"), number);
    setText(string);
  }

  //</modified>

  UINT_PTR  setTimer(UINT id, UINT elapse, TIMERPROC proc) {
      return ::SetTimer(hwnd, id, elapse, proc);
  }

  void  setWindow(HWND hwnd1) {
      hwnd = hwnd1;
  }

  void  capture() {
      ::SetCapture(hwnd);
  }

  Boolean  setForegroundWindow() {
      return ::SetForegroundWindow(hwnd);
  }

  //2017/03/10
  //void  setWindowLong(int indx, LONG val) {
  //    ::SetWindowLong(hwnd, indx, val);
  //}
  //2017/03/10
  LONG_PTR  setWindowLongPtr(int index, LONG_PTR dwNewLong)
  {
    return SetWindowLongPtr(hwnd, index, dwNewLong);
  }
  
  void  setWindowWord(int indx, WORD val) {
      ::SetWindowWord(hwnd, indx, val);
  }
  //2012/07/5
  void    hide() {
      ::ShowWindow(hwnd, SW_HIDE);    
  }
  void  show() {
      ::ShowWindow(hwnd, SW_NORMAL);
  }

  void  show(int cmd) {
      ::ShowWindow(hwnd, cmd);
  }
  void  toClient(POINT* pt) {
      ::ScreenToClient(hwnd, pt);
  }
  void  toScreen(POINT* pt) {
      ::ClientToScreen(hwnd, pt);
  }
  void  update() {
      ::UpdateWindow(hwnd);
  }
  void  update(const RECT* r) {
      invalidate(r);
      ::UpdateWindow(hwnd);
  }

  Boolean  flash(Boolean invert) {
      return ::FlashWindow(hwnd, invert);      
  }

  HWND  getLastActivePopup() {
      return ::GetLastActivePopup(hwnd);
  }

  HWND  getTopWindow() {
      return ::GetTopWindow(hwnd);
  }
  DWORD  getThreadProcessId(DWORD* processId) {
      return ::GetWindowThreadProcessId(hwnd, processId);
  }

  Boolean  redraw(const RECT* rect, HRGN rgn, UINT flags) {
      return ::RedrawWindow(hwnd, rect, rgn, flags);
  }

  Boolean  validate(const RECT* r) {
      return ::ValidateRect(hwnd, r);
  }
  Boolean  validate(HRGN  r) {
      return ::ValidateRgn(hwnd, r);
  }

  Boolean  send(UINT message, WPARAM wParam, LPARAM lParam,
          SENDASYNCPROC callback, DWORD data) {
      return ::SendMessageCallback(hwnd, message,
          wParam, lParam,  callback, data);
  }

  LRESULT  send(UINT message, WPARAM wParam, LPARAM lParam,
          UINT flags, UINT timeOut, PDWORD_PTR result) {
      return ::SendMessageTimeout(hwnd, message,
          wParam, lParam, flags, timeOut, result);
  }
  long  sendNotify(UINT message, WPARAM wParam, LPARAM lParam) {
      return ::SendNotifyMessage(hwnd, message,
          wParam, lParam);
  }
  Boolean  showAsync(int cmd) {
      return ::ShowWindowAsync(hwnd, cmd);
  }
  Boolean  hideOwnedPopups() {
      return ::ShowOwnedPopups(hwnd, FALSE);
  }
  Boolean  showOwnedPopups() {
      return ::ShowOwnedPopups(hwnd, TRUE);
  }

//2008/08/13
public:
  void   setRedraw(BOOL flag) {
    send(WM_SETREDRAW, flag, 0);
  }

public:
  //2009/11/04
  virtual BOOL  translate(MSG*  msg) { 
    return FALSE;
  }

public:
  void setSmallIcon(HICON hIcon)
  {
    send(WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  }

public:
  void setBigIcon(HICON hIcon)
  {
    send(WM_SETICON, ICON_BIG, (LPARAM)hIcon);
  }
public:
  HICON loadIcon(int resourceId)
  {
    HINSTANCE hInst = getInstanceHandle();
    return LoadIcon(hInst, MAKEINTRESOURCE(resourceId));
  }

public:
  //2012/04/08
  virtual void resize(int width, int height)
  {  
    WINDOWPLACEMENT pl;
    pl.length = sizeof(pl); 
    getPlacement(&pl);

    RECT r = pl.rcNormalPosition;
    r.right = r.left + width;
    r.bottom = r.top + height;
    pl.rcNormalPosition = r;
    setPlacement(&pl); 
  }

public:
  //2012/06/17
  int    getScrollPos(int type) {
      return ::GetScrollPos(getWindow(), type);
  }
  void  getScrollRange(int type, int* min, int* max) {
      ::GetScrollRange(getWindow(), type, min, max);
  }
  Boolean  enableScrollBar(UINT sbFlags, UINT arrows) {
      return ::EnableScrollBar(getWindow(), sbFlags,  arrows);
  }
  
  void  raise() {
      ::BringWindowToTop(getWindow());
  }


  void   setScrollPos(int type, int pos) {
      ::SetScrollPos(getWindow(), type, pos, TRUE);
  }

  void  setScrollRange(int type, int min, int max) {
      ::SetScrollRange(getWindow(), type, min, max, TRUE);
  }

  //2015/08/03
  void activate() {
    SetWindowPos(getWindow(), HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(getWindow(), HWND_NOTOPMOST, 0, 0, 0, 0,
        SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
  }
  
  //2015/11/10
  //Please your own render method in the class derived from this class,
  virtual void render()
  {
  }
  
  //2017/01/26
  int  width()
  {
      RECT r;
      ::GetClientRect(hwnd, &r);
      return  r.right - r.left;
  }
  
  //2017/01/26
  int  height()
  {
      RECT r;
      ::GetClientRect(hwnd, &r);
      return  r.bottom - r.top;
  }

  void dragAcceptFiles(BOOL flag=TRUE)
  {
    DragAcceptFiles(hwnd, flag);
  }
};

}


