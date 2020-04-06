/******************************************************************************
 *
 * Copyright (c) 1999-2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  View.h
 *
 *****************************************************************************/

// SOL9

// 1999.08.14
// 2000.02.18
// 2001.03.11 to-arai: Added a create method.
// 2012/07/22 Updated getCallbackName method
// 2015/08/22 Added activate method.
// 2016/08/10 Added the virtual specifier to postRewieRequest, and postRenderRequest methods.

#pragma once

#include <sol/Wchardef.h>
#include <sol\Window.h>
#include <sol\Application.h>

#include <sol\Args.h>
#include <sol\CallbackList.h>
#include <sol\HandlerList.h>
#include <sol\Dimension.h>
#include <sol\LinkedList.h>
#include <sol\Layoutable.h>
#include <sol\stdio.h>
#include <sol\Font.h>
#include <sol\InvalidWindowException.h>


namespace SOL {

class Font;
class Layoutable;

class View :public Window, public Layoutable {
private:
  View*      parent;
  Font*      font;  
  CallbackList  callbackList;
  HandlerList    handlerList;
  Boolean      editable;
  Boolean      destructable;
  Dimension    preferredSize;
  
  public:
  static const long  DEFAULT_WIN_CLASS_STYLE = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;


protected:
   virtual long destroy(Event& event)
  {
    ::PostQuitMessage(0);
    return 0L;
  }

protected:
   virtual LRESULT defaultProc(Event& event)
  {
    return ::DefWindowProc(getWindow(), event.getMessage(),
           event.getWParam(),
           event.getLParam());
  }

protected:
  View(View* parview)
    :parent(parview),
    font(NULL),
    editable(False),
    destructable(True),
    preferredSize(100, 100)
  {
    //
  }

public:
  View()
    :parent(NULL),
    font(NULL),
    editable(False),
    destructable(True),
    preferredSize(100, 100)
  {
  }

public:
  View(View* parview, const TCHAR* name, Args& args)
    :parent(parview),
    font(NULL),
    editable(False),
    destructable(True),
    preferredSize(100, 100)
  {
    Boolean rc = create(parview, name, args);
    if (rc == False) {
      throw IException("Failed to create a window");
    }
  }


public:
  ~View()
  {
    HWND hwnd = getWindow();
    if(isWindow() && destructable) {
      destroyWindow();
    }
    Application::remove(hwnd);
  }

public:
  virtual void  addCallback(const TCHAR* name, Object* object,
           Callback proc, void* data)
  {
    if(parent) {
      parent -> addCallback(name, (const Key)getWindow(), object, 
              proc, data);
    }
  }


public:
  void  addCallback(const TCHAR* name, const Key key, Object* object,
           Callback proc, void* data)
  {
    callbackList.add(name, key, object, proc, data);
  }


public:
  void  addEventHandler(UINT message, Object* object,
               Handler proc, void* data)
  {
    handlerList.add(message, object, proc, data);
  }

public:
  void  callCallback(const TCHAR* name, const Key key, 
      void* value, Event& event)
  {
    callbackList.call(name, key, value, event);
  }
  
public:
  virtual Boolean create(View* parview, const TCHAR* name, Args& args)
  {
    Boolean rc = False;

    parent = parview;
    font   = NULL;
    editable = False;
    destructable = True;

    // If a window were created, return False.
    if (getWindow()) {
      return rc;
    }

    if (args.get(XmNdialogUnit)) {
      args.toPixelUnit();
    }

    const TCHAR* className = nullptr;
    className = (const TCHAR*)args.get(XmNclassName);//, &val);
    //MessageBox(NULL, className, _T("ClassName"), MB_OK);
    if (className == nullptr) {
      className = _T("View");
      args.set(XmNclassName, (LONG_PTR)className);
    }

    if (args.get(XmNpredefined) == False){
      registerClass(args);
    }

    HFONT hfont = NULL;

    HWND hparent = NULL;
    Font* pfont =NULL;

    if (parent) {
      hparent = parent->getWindow();

      //If parent has a Font, then we use it.
      pfont    = parent->getFont();
      if (pfont) {
        hfont = pfont->getFont();
      }
    }
    Application& applet = Application::getApplet(NULL);
    HINSTANCE hInstance = applet.getInstance();
    
    HWND hwnd= ::CreateWindowEx(
          (DWORD)args.get(XmNexStyle),  //2017/09/10
          className, name,
          (DWORD)args.get(XmNstyle),
          (int) args.get(XmNx),
          (int) args.get(XmNy),
          (int) args.get(XmNwidth),
          (int) args.get(XmNheight),
          hparent, NULL,
          hInstance,  //Application::getInstance(),
          (LPSTR)args.get(XmNparam));
  
    if(hwnd) {
      setWindow(hwnd);

      Application::add(hwnd, this);
      setViewId((int)args.get(XmNid));
    
      //<added date="2008/06/27">
      TCHAR* useDefaultFont = (TCHAR*)args.get(XmNuseDefaultFont);

      if (hfont && useDefaultFont) {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True,0));
        if (pfont) {
          setFont(pfont);
        }
      }
      //</added>
      if(parent == NULL) {
        addEventHandler(WM_DESTROY, this,
               (Handler)&View::destroy, NULL);
      }
      rc = True;
    }
    else {
      //2012/07/20
      throw TException(_T("Failed to CreateWindow className:'%s'"), className);
    }
    return rc;
  }

  BOOL registerClass(Args& args)
  {
    BOOL rc = FALSE;
    //Application& applet = getInstance();
    Application& applet = Application::getApplet(NULL);
    HINSTANCE hInstance = applet.getInstance();

    WNDCLASS wc;
    const TCHAR* className = (const TCHAR*)args.get(XmNclassName);

   // MessageBox(NULL, (_TCHAR*)className, _T("Register DEBUG"), MB_OK);
    if (::GetClassInfo(hInstance, (_TCHAR*)className, &wc)) {
      return TRUE;
    }
    HINSTANCE  prevInstance = applet.getPrevInstance(); 

    if (!prevInstance) {
    
      memset(&wc, 0, sizeof(WNDCLASS));
      wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
      wc.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
      wc.lpszClassName = (_TCHAR*)className;
      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
      wc.hInstance     = hInstance;
      wc.style         = DEFAULT_WIN_CLASS_STYLE;
      //CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
      wc.lpfnWndProc   = View::procedure;

      LONG_PTR val=0;
      if (args.get(XmNclassStyle, &val)) {
        wc.style      = (unsigned int)val;
      }
      if (args.get(XmNclsExtra, &val)) {
        wc.cbClsExtra = (unsigned int)val;
      }
      if (args.get(XmNwndExtra, &val)) {
        wc.cbWndExtra  = (unsigned int)val;
      }
      if (args.get(XmNwndProc, &val)) {
        wc.lpfnWndProc = (WNDPROC)val;
      }
      if (args.get(XmNbackground, &val)) {
        wc.hbrBackground = (HBRUSH)val;
      }
      if (args.get(XmNicon, &val)) {
        wc.hIcon      = (HICON)val;
      }
      if (args.get(XmNcursor, &val)) {
        wc.hCursor    = (HCURSOR)val;
      }
      //return 
      rc = ::RegisterClass(&wc);
      if (rc) {
        return rc;
      } else {
        throw TException(_T("Failed to RegisterClass"));
      }
    }
    return rc;
  }

  // 2001.03.11
public:
  virtual Boolean create(View* parview)
  {
    parent  = parview;
    font  = NULL;
    editable = False;
    destructable = True;
    Dimension d(100,100);
    preferredSize.set(d);
    return True;
  }

public:
  virtual void disable()
  {
    show(SW_HIDE);
    enableWindow(False);
    show(SW_NORMAL);
  }

public:
  virtual LRESULT  dispatch(Event& event)
  {
    LONG_PTR value = NULL;
    event.handled(false);
    if(handlerList.call(event, &value)) {
      event.handled(true);
      return value;
    }
    return defaultProc(event);
  }

public:
  virtual void  enable()
  {
    show(SW_HIDE);
    enableWindow(True);
    show(SW_NORMAL);
  }

public:
  LONG_PTR get(const TCHAR* name)
  {
    LONG_PTR val;
    Args args;
    args.set(name, (LONG_PTR)&val);
    getValues(args);
    return val;
  }


public:
  void get(const TCHAR* name, LONG_PTR* val)
  {
    Args args;
    args.set(name, (LONG_PTR)val);
    getValues(args);
  }
  
public:
  virtual Arg*  getCallbackTable(int* num)
  {
    *num = 0;
    return NULL;
  }

public:
  virtual const TCHAR* getCallbackName(Event& event)
  {
    int  num = 0;
    Arg* table = NULL;

    table = getCallbackTable(&num);

    LONG_PTR val = (LONG_PTR)event.getNotification();
    //2012/07/22
    const TCHAR* name = NULL;
    //const TCHAR* name = XmNactivateCallback;

    for(int i = 0; i<num; i++) {
      if(table[i].value == val) {
        name = table[i].name;
        break;          
      } 
    }
    return name;
  }

public:
  void  getGeometry(int& x, int& y, int& width, int& height)
  {
    RECT r;
    getWindowRect(&r);
    x   = r.left;
    y   = r.top;
    width  = r.right  - r.left;
    height = r.bottom - r.top;

    if(parent) {
      POINT p;
      p.x = x;
      p.y = y;
      parent -> toClient(&p);
      x = p.x;
      y = p.y;
    }
  }

public:
  void  getNormalPlacement(RECT* r)
  {
    WINDOWPLACEMENT pl;
    pl.length = sizeof(WINDOWPLACEMENT);
    pl.showCmd = SW_SHOWNORMAL;
    getPlacement(&pl);
    *r = pl.rcNormalPosition;
  }

public:
  View*  getParent() { 
    return parent; 
  }
  
public:
  void  getSize(int& width, int& height)
  {
    RECT r;
    getWindowRect(&r);
    width  = r.right  - r.left;
    height = r.bottom - r.top;
  }

public:
  void  getLocation(int& x, int& y)
  {
    int width, height;
    getGeometry(x, y, width, height);
  }

public:
  int    getViewId() { 
    return getId(); 
  }
  
public:
  virtual void  layout(int x, int y, int w, int h)
  {
    reshape(x, y, w, h);
  }

public:
  Boolean  isEditable() { 
    return editable; 
  }
  
public:
  void  map() { 
    show(SW_NORMAL); 
  }

public:
  virtual void  getValues(Args& args)
  {
    int x, y, w, h;
    getGeometry(x, y, w, h);

    Arg ar[4];
    XtSetArg(ar[0], XmNx,     x);
    XtSetArg(ar[1], XmNy,     y);
    XtSetArg(ar[2], XmNwidth, w);
    XtSetArg(ar[3], XmNheight,h);

    HINSTANCE ins = getInstanceHandle();

    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    LONG style   = (LONG)(getWindowLongPtr(GWL_STYLE));
    LONG exStyle = (LONG)(getWindowLongPtr(GWL_EXSTYLE));

    for(int j = 0; j<num; j++) {
      const TCHAR*   name  = arg[j].name;
      LONG_PTR* val  = (LONG_PTR*)arg[j].value;
      if(name == XmNstyle) {
        *val = style;
        continue;
      }
      if(name == XmNexStyle) {
        *val = exStyle;
        continue;
      }
      if(name == XmNid) {
        *val = getViewId();
        continue;
      }
      if(name == XmNinstance) {
        *val = (LONG_PTR)ins;
        continue;
      }
      if(name == XmNgroup) {
        *val = False;
        if(style & WS_GROUP) 
          *val = True;
        continue;
      }
      if(name == XmNacceptFiles) {
        *val = False;
        if(exStyle & WS_EX_ACCEPTFILES)
          *val = True;
        continue;
      }
  
      if(name == XmNlabelString) {
        int len = getTextLength();
        TCHAR* buff = new TCHAR[len+1];
        getText(buff, len+1);
        *val = (LONG_PTR)buff;
      }
    
      for(int i = 0; i<4; i++) {
        if(name == ar[i].name) {
           *val = (LONG_PTR)ar[i].value;
        }
      }
    }
  }


public:
  static LRESULT CALLBACK procedure(HWND hwnd, UINT message, 
      WPARAM wParam, LPARAM lParam)
  {
    Event event(message, wParam, lParam);

    View* view = Application::lookup(hwnd);

    if (view && view->isWindow()) {
      return view -> dispatch(event);
    }
    return ::DefWindowProc(hwnd, message, wParam, lParam);
  }

public:
  void  removeEventHandler()
  {
    handlerList.clear();
  }

public:
  void  set(const TCHAR* name, LONG_PTR val)
  {
    Args args;
    args.set(name, val);
    setValues(args);
  }


public:
  void  setDestructable(Boolean val) { 
    destructable = val;
  }

public:
  void  setEditable(Boolean val) { 
    editable = val; 
  }
  
public:
  void  setLocation(int x, int y)
  {
    int xx, yy, width, height;

    getGeometry(xx, yy, width, height);
    reshape(x, y, width, height);
    update(NULL);
  }

public:
  void  setSize(int w, int h)
  {
    int xx, yy, width, height;

    getGeometry(xx, yy, width, height);
    reshape(xx, yy, w, h);
    update(NULL);
  }

  
public:
  void  setParent(View* parent1) { 
    parent = parent1; 
  }

public:
  void  setViewId(int id)
  {
    setId(id);
    LONG style = (LONG)getWindowLongPtr(GWL_STYLE);
    if(style & WS_CHILD) {
      setWindowLongPtr(GWLP_ID, (LONG_PTR)id);
    }
  }


public:
  void  setVisible(Boolean flag) 
  {
    if (flag) 
      map();
    else 
      unmap();
  }

public:
  virtual void  setValues(Args& args)
  {
    int x, y, w, h;

    getGeometry(x, y, w, h); 
    Arg ar[4];
    XtSetArg(ar[0], XmNx,     x);
    XtSetArg(ar[1], XmNy,     y);
    XtSetArg(ar[2], XmNwidth, w);
    XtSetArg(ar[3], XmNheight,h);

    Boolean mustmove = False;
    int num  = args.getCount();
    Arg* arg = args.getArgList();
    int i, j;
    for(j = 0; j<num; j++) {
      for(i = 0; i<4; i++) {
        if(ar[i].name == arg[j].name) {
           ar[i].value = arg[j].value;
          mustmove = True;
        }
      }
    }
    Boolean config = (Boolean)args.get(XmNnoConfiguration);
    if(!config) {
      if(mustmove && (ar[2].value != (LONG_PTR)CW_USEDEFAULT) ||
                       (ar[3].value != (LONG_PTR)CW_USEDEFAULT)) {
        reshape((int)ar[0].value, (int)ar[1].value,
                   (int)ar[2].value, (int)ar[3].value);
      }
    }
    LONG_PTR val = 0;
    LONG_PTR style   = (LONG_PTR)getWindowLongPtr(GWL_STYLE);
    LONG_PTR exStyle = (LONG_PTR)getWindowLongPtr(GWL_EXSTYLE);

    if(args.get(XmNgroup, &val)) {
      if(val) {
        style |= WS_GROUP;
      }
      else {
        if(style & WS_GROUP) 
          style ^= WS_GROUP;
      }
      setWindowLongPtr(GWL_STYLE, (LONG_PTR)style);
    }

    if(args.get(XmNacceptFiles, &val)) {
      if(val) {
        exStyle |= WS_EX_ACCEPTFILES;
      }
      else {
        if(exStyle & WS_EX_ACCEPTFILES)
          exStyle ^= WS_EX_ACCEPTFILES;
      }
      setWindowLongPtr(GWL_EXSTYLE, (LONG_PTR)exStyle);
    }
    if(args.get(XmNlabelString, &val)) {
      setText((TCHAR*)val);
    }

    if(args.get(XmNid, &val)) {
      setViewId((int)val);
    }
  }


public:
  void  getStyle(Args& args, Arg* arg, int num)
  {
    LONG_PTR style = (LONG_PTR)getWindowLongPtr(GWL_STYLE);

    for(int i = 0; i<num; i++) {
      LONG_PTR* val = (LONG_PTR*)args.get(arg[i].name);
      if(val) {
        *val = False;
        if(style & (DWORD)arg[i].value)
          *val = True;
      }
    }
  }

public:
  void  unmap() { 
    show(SW_HIDE); 
  }

  //2015/07/26
public:
  void  refresh()
  {
    invalidateAll();
    update();
  }
  
public:
  void  refresh(RECT* rect)
  {
    invalidate(rect);
    update();
  }

public:
  void refresh(int x, int y, int width, int height)
  {
    RECT rect;
    rect.left   = x;
    rect.top    = y;
    rect.right  = x+width;
    rect.bottom = y+height;
    invalidate(&rect);
    update();
  }


public:
  void  updateStyle(Args& args, Arg* arg, int num)
  {
    for(int i = 0; i<num; i++) {
      LONG_PTR style = (LONG_PTR)getWindowLongPtr(GWL_STYLE);
      LONG_PTR val;
      DWORD st = (DWORD)arg[i].value;
      if(args.get(arg[i].name, &val)) {
        if(val) {
          style |= st;
        }
        else {
          if(style & st)
            style ^= st;
        }
        setWindowLongPtr(GWL_STYLE, (LONG_PTR)style);
      }
    }
  }


public:
  Font*  getFont() { 
    return font; 
  }

  virtual void  setFont(HFONT hfont) {
      send(WM_SETFONT, (WPARAM)hfont, MAKELPARAM(TRUE,0));
  }

  virtual void  setFont(Font* font)
  {
    this->font = font;
    if(font) {
      send(WM_SETFONT, (WPARAM)font->getFont(),
          MAKELPARAM(True,0));
    }
  }

  virtual void  setFont(Font& font1)
  {
    font = &font1;
    if(font) {
      send(WM_SETFONT, (WPARAM)font->getFont(),
          MAKELPARAM(True,0));
    }
  }


  void setSysCursor(const TCHAR* name)
  {
    ::SetCursor(::LoadCursor(NULL, name));    
  }

  virtual void getPreferredSize(Dimension& d) 
  {
    preferredSize.get(d);
  }


  virtual void setPreferredSize(Dimension& d) 
  {
    setSize(d.getWidth(), d.getHeight());
    preferredSize.set(d);
  }


public:
  BOOL getDisplayFont(LOGFONT& lf) {
    
    NONCLIENTMETRICS ncm;
    memset(&ncm, 0, sizeof(ncm)); 
    ncm.cbSize = sizeof(ncm); 

    BOOL rc = SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0); 
    if (rc) {
      lf = ncm.lfMessageFont; 
    }
    return rc;
  }

  //2009/11/01
public:
  operator HWND(){
    return (HWND)Window::getWindow();
  }

  //2015/08/22
public:
  void activate()
  {
    HWND hwnd = getWindow();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
        SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
  }

  void bringUp()
  {
    HWND hwnd = getWindow();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
        SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
    raise();
  }

  void setTopMost()
  {
    HWND hwnd = getWindow();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
  }
  
  void setTopMost(int x, int y, int width, int height)
  {
    HWND hwnd = getWindow();
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, width, height,
        SWP_SHOWWINDOW);
  }

  //2015/11/26
  void setNoCopyBits()
  {
    HWND hwnd = getWindow();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE );
    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
        SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE  |SWP_NOCOPYBITS);
  }
  
  //2015/10/17
  //2016/09/10 Added virtual qualifier
public:
  virtual void postResizeRequest()
  {
    RECT r;
    getClientRect(&r);
    int w = r.right - r.left;
    int h = r.bottom - r.top;
    post(WM_SIZE, 0, MAKELONG(w, h));
  }
  
  virtual void postResizeRequest(int w, int h)
  {
    post(WM_SIZE, 0, MAKELONG(w, h));
  }

  //2016/02/16
  virtual void postRenderRequest()
  {
    post(WM_PAINT, 0, 0);
  }

  //2016/12/04
  virtual void display()
  {
  }
  
  CallbackList& getCallbackList()
  {
    return callbackList;
  }
  
};

}


