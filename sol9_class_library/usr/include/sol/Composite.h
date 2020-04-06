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
 *  Composite.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.10.09 Modified layout to be virtual.
// 1999.10.09 Added a getLayoutManager method.
// 2000.02.18
// 2001.03.11 Added a create method.
// SOL9
// 2009/09/07 Added setIcon method to sepecifiy an Icon Id in resource file(*.rc)
// 2012/07/15 Modified doHorizScroll and doVertScroll to be virtual functions.

#pragma once

#include <sol\View.h>
#include <sol\Extent.h>
#include <sol\LayoutManager.h>
#include <sol\Primitive.h>
#include <sol\LayoutManager.h>
#include <sol\Font.h>
#include <sol\Application.h>
#include <sol\ScrollBar.h>
#include <shellapi.h>  
#include <sol\stdio.h>
#include <sol\Button.h>
#include <sol\ListBox.h>
#include <sol\ComboBox.h>
#include <sol\Text.h>
#include <sol\ClientDC.h>
#include <sol\stdio.h>

namespace SOL {

#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#define Min(a,b)    (((a) < (b)) ? (a) : (b))


class Composite :public View {

private:
  static int stylesCount()
  {
    int count = 0;
    styles(&count);

    return count;
  }

  static Arg* styles(int* count=NULL)
  {
    static Arg _styles[] = {
      {XmNhorizScrollBar, WS_HSCROLL},
      {XmNvertScrollBar,  WS_VSCROLL},
    };

    if (count) {
      *count = XtNumber(_styles);
    }
    return _styles;
  }

  HICON   hicon;
  HWND  hfocus;

  Extent  extent;
  int    pageIncrement;
  int    lineIncrement;
  Boolean  enableThumbTrack;
  LayoutManager* layoutManager;
  
  Font  defaultFont;

private:
  //2008/06/23
  void setDefaultFont()
  {
    LOGFONT lf;
    getDisplayFont(lf);

    defaultFont.create(&lf);

    View::setFont(&defaultFont);
  }


public:
  static const int HORIZONTAL = (int)SB_HORZ;
  static const int VERTICAL   = (int)SB_VERT;

public:
  Composite():View() {
    hicon    = NULL;
    hfocus    = NULL;
    pageIncrement = 16;
    lineIncrement = 2;
    enableThumbTrack =False;
    layoutManager = NULL;
  }


public:
  int Composite::moveThumb(Event& event, int type)
  {
    int pos  = getScrollPos(type);
    int prev = pos;

    SCROLLINFO scInfo;
    //<modified date="2000.05.08">
    memset(&scInfo, 0, sizeof(scInfo));
    scInfo.cbSize = sizeof(scInfo);
    //</modified>
    scInfo.fMask = SIF_ALL;

    int min, max;
    getScrollRange(type, &min, &max);
    int range = max - min;

    int request = LOWORD(event.getWParam());

    switch(request) {

    case SB_PAGEDOWN: pos += pageIncrement;
    case SB_LINEDOWN: pos = Min(range, pos + lineIncrement);
      break;

    case SB_PAGEUP:  pos -= pageIncrement;
    case SB_LINEUP:  pos = Max(0, pos - lineIncrement);
      break;

    case SB_TOP: pos = 0;
      break;

    case SB_BOTTOM:  pos = range;
      break;

    case SB_THUMBPOSITION:
      getScrollInfo(type, &scInfo);
      pos = scInfo.nTrackPos;
      break;

    case SB_THUMBTRACK:
      if(enableThumbTrack) {
        getScrollInfo(type, &scInfo);
        pos = scInfo.nTrackPos;
      }
      else {
        return 0;
      }
      break;

    default:
      break;
      }
    setScrollPos(type, pos);
    return  prev - pos;
  }
  

public:
  //2012/07/15
  virtual void doHorizScroll(Action& action)
  {
    int diff = action.getIntValue();
    scroll(diff, 0, NULL, NULL);
    update();
  }

public:
  //2012/07/15
  virtual void doVertScroll(Action& action)
  {
    int diff = (int)action.getIntValue();
    scroll(0, diff, NULL, NULL);
    update();
  }


protected:
  virtual long horizScroll(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();

    int  diff = 0;

    if(hwnd) { // scrollbar control.
      ScrollBar* scb = (ScrollBar*)Application::lookup(hwnd);
      if(scb)  diff = scb -> moveThumb(event);
    }
    else {     // standard scrollbar
      hwnd = getWindow();
      diff = moveThumb(event, SB_HORZ);
    }
    callCallback(XmNhorizScrollCallback, (Key)hwnd, (void*)diff, event);
    return NULL;
  }

protected:
  virtual long vertScroll(Event& event)
  {
    HWND hwnd = (HWND)event.getLParam();

    int  diff = 0;

    if(hwnd) {// scrollbar control.
      ScrollBar* scb = (ScrollBar*)Application::lookup(hwnd);
      if(scb)  diff = scb -> moveThumb(event);
    }
    else {    // standard scrollbar
      hwnd = getWindow();
      diff = moveThumb(event, SB_VERT);
    }
    callCallback(XmNvertScrollCallback, (Key)hwnd, (void*)diff, event);
    return NULL;
  }


protected:
  virtual long command(Event& event) 
  {
    WORD menuId = (WORD)event.getMenuId();
    HWND child  = event.getChild();

    //  Printf("Composite::Command \r\n");
    if(event.isMenuSelected() == TRUE ||
      event.fromAccelerator() == TRUE) {
      // menu or accelarator has been selected. 
      callCallback(XmNmenuCallback, (Key)menuId,
        NULL,event);
    }
    else {
      //2009/11/01
      if (child && IsWindow(child)) {
        View* view = (View*)Application::lookup(child);
        const TCHAR* name = XmNactivateCallback;
        if(view) {
          name = view->getCallbackName(event);
        }
      //  Printf("Composite::Command %s\r\n", name);
        callCallback(name, (Key)child, NULL, event);
      }
    }

    // Return a result of callback.
    return event.getResult();
  }

protected:
  // Common notification from common controls.
  const TCHAR* isCommonNotification(Event& event)
  {
    static Arg table[] = {
    {XmNerrorSpaceCallback, (LONG_PTR)NM_OUTOFMEMORY},
    {XmNclickCallback,      (LONG_PTR)NM_CLICK},
    {XmNdoubleClickCallback,(LONG_PTR)NM_DBLCLK},
    {XmNreturnCallback,     (LONG_PTR)NM_RETURN},
    {XmNrightClickCallback,       (LONG_PTR)NM_RCLICK},
    {XmNrightDoubleClickCallback, (LONG_PTR)NM_RDBLCLK},
    {XmNsetFocusCallback,         (LONG_PTR)NM_SETFOCUS},
    {XmNkillFocusCallback,        (LONG_PTR)NM_KILLFOCUS},
    };

    const TCHAR* name = NULL;
    LONG_PTR   code = event.getNotification();
    for(int i = 0; i<XtNumber(table); i++) {
      if(table[i].value == code) {
        name = table[i].name;
        break;
      }
    }
    return name;
  }

protected:
// EventHandler for message WM_NOTIFY.
  virtual long notify(Event& event) 
  {
    NMHDR* hdr  = (NMHDR*)event.getLParam();
    HWND sender  = hdr->hwndFrom;

    View* view = (View*)Application::lookup(sender);
    const TCHAR* name = NULL;
  
    if(view) {
      name = isCommonNotification(event);
      if(name == NULL) {
        name = view->getCallbackName(event);
      }
      if(name) {
        callCallback(name, (Key)sender, NULL, event);
      }
    }
    // Return a result of callback.
    return event.getResult();
  }

public:
  //2012/06/22
  // Used for Modeless and Modal Dialog.
  Composite(View* parent)
    :View()
  {
    create(parent);
  }

public:
// 2001/03/11
// Used for Modeless and Modal Dialog.
  virtual Boolean create(View* parent)
  {
    Boolean rc = View::create(parent);

    hicon    = NULL;
    hfocus    = NULL;
    pageIncrement = 16;
    lineIncrement = 2;
    enableThumbTrack =False;
    layoutManager = NULL;

    //2008/06/25
    setDefaultFont();

    addEventHandler(WM_COMMAND, this, 
      (Handler)&Composite::command, NULL);
    addEventHandler(WM_NOTIFY, this, 
      (Handler)&Composite::notify, NULL);

    addEventHandler(WM_HSCROLL, this,
      (Handler)&Composite::horizScroll, NULL);
    addEventHandler(WM_VSCROLL, this,
      (Handler)&Composite::vertScroll, NULL);
    addEventHandler(WM_SIZE, this,
      (Handler)&Composite::size, NULL);

    return rc;
  }

public:
  //2012/06/23
  Composite(View* parent, const TCHAR* name, Args& args)
  :View(),
    hicon(NULL),
    hfocus(NULL),
    pageIncrement(16),
    lineIncrement(2),
    enableThumbTrack(False),
    layoutManager(NULL)
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    //<modified date="2001/03/11">
    Boolean rc = View::create(parent, name, args.set(styles(), stylesCount()));

    hicon   = NULL;
    hfocus  = NULL;
    pageIncrement = 16;
    lineIncrement = 2;
    enableThumbTrack = False;
    layoutManager = NULL;
    //</modified>

    //2008/06/25
    setDefaultFont();

    addEventHandler(WM_COMMAND, this, 
         (Handler)&Composite::command, NULL);
    addEventHandler(WM_NOTIFY, this, 
         (Handler)&Composite::notify, NULL);

    addEventHandler(WM_HSCROLL, this,
      (Handler)&Composite::horizScroll, NULL);
    addEventHandler(WM_VSCROLL, this,
      (Handler)&Composite::vertScroll, NULL);
    addEventHandler(WM_ACTIVATE, this,
      (Handler)&Composite::activate, NULL);

    addEventHandler(WM_SIZE, this,
      (Handler)&Composite::size, NULL);

    setValues(args);

    addCallback(XmNhorizScrollCallback, (Key)getWindow(), this,
      (Callback)&Composite::doHorizScroll, NULL);
    addCallback(XmNvertScrollCallback, (Key)getWindow(), this,
      (Callback)&Composite::doVertScroll,  NULL);
    return rc;
  }

public:
  ~Composite()
  {
    //Don't delete the layoutManager;

    if(hicon) {
      DestroyIcon(hicon);
      hicon = NULL;
    }
  }

public:
  //2009/09/07
  // Specifiy an Icon Id in resource file(*.rc)
  bool setIcon(int iconId)
  {
    bool rc = false;
    HINSTANCE hInst = getInstanceHandle();

    HICON hLoadedIcon = LoadIcon(hInst, MAKEINTRESOURCE(iconId));
    if (hLoadedIcon) {

      hicon = hLoadedIcon;
      send(WM_SETICON, ICON_SMALL, (LPARAM)hicon);
      send(WM_SETICON, ICON_BIG, (LPARAM)hicon);
      rc = true;
    }
    return rc;
  }

public:
  //2009/09/07
  // Specifiy an Icon Id in resource file(*.rc)
  bool setIcon(const TCHAR* iconName)
  {
    bool rc = false;
    HINSTANCE hInst = getInstanceHandle();

    HICON hLoadedIcon = LoadIcon(hInst, iconName);
    if (hLoadedIcon) {

      hicon = hLoadedIcon;
      send(WM_SETICON, ICON_SMALL, (LPARAM)hicon);
      send(WM_SETICON, ICON_BIG, (LPARAM)hicon);
      rc = true;
    }
    return rc;
  }


protected:
  virtual long activate(Event& event)
  {
    if(LOWORD(event.getWParam()) == WA_INACTIVE) {
      hfocus = getFocus();
    }
    else if (hfocus) {
      setFocus(hfocus);  
    }
    return NULL;
  }

public:
  void layout(int x, int y, int w, int h)
  {
    if (getParent() != NULL) {
      reshape(x, y, w, h);
    }
    if (layoutManager) {
      layoutManager->layout(0, 0, w, h);
    }
  }

protected:
  virtual long size(Event& event) 
  {
    int w, h;
    event.getSize(w, h);
    int x, y;
    getLocation(x, y);
    
    layout(x, y, w, h);

    return 0L;
  }

public:
  void setValues(Args& args)
  {
    View::setValues(args);

    updateStyle(args, styles(), stylesCount());

    LONG_PTR  val;
    if(args.get(XmNpageIncrement, &val))
      pageIncrement = (int)val;
    if(args.get(XmNlineIncrement, &val))
      lineIncrement = (int)val;

    if(args.get(XmNenableThumbTrack, &val))
      enableThumbTrack = (BOOL)val;

    int max, min;
    int type = SB_HORZ;
    getScrollRange(type, &min, &max);
    if(args.get(XmNhorizScrollMaximum, &val))
      setScrollRange(type, min, (int)val);
    getScrollRange(type, &min, &max);
    if(args.get(XmNhorizScrollMinimum, &val))
      setScrollRange(type, (int)val, max);

    type = SB_VERT;
    getScrollRange(type, &min, &max);
    if(args.get(XmNvertScrollMaximum, &val))
      setScrollRange(type, min, (int)val);
    getScrollRange(type, &min, &max);
    if(args.get(XmNvertScrollMinimum, &val))
      setScrollRange(type, (int)val, max);

    if(args.get(XmNhorizThumbPosition, &val))
      setScrollPos(SB_HORZ, (int)val);
    if(args.get(XmNvertThumbPosition, &val))
      setScrollPos(SB_VERT, (int)val);

    // Extract an icon from *.ico or *.exe and set it.
    // CreateIcon API will be called;

    if(args.get(XmNiconFile, &val)) {
      TCHAR* name  = (TCHAR*)val; // file name
      get(XmNinstance, &val);
      HICON temp = ::ExtractIcon((HINSTANCE)val, name, 0);
      if(temp) {
        setClassLong(GCLP_HICON, (LONG_PTR)temp);
        if(hicon) ::DestroyIcon(hicon);
        hicon = temp;
      }
    }
    // Get an icon handle and set it.
    if(args.get(XmNwindowIcon, &val)) {
      //setClassLong(GCLP_HICON, (LONG_PTR)val); 
      //2017/09/10
      send(WM_SETICON, ICON_SMALL, (LPARAM)val);
      send(WM_SETICON, ICON_BIG, (LPARAM)val);      
    }
  }

public:
  void realize()
  {
    show(SW_SHOWNORMAL);
  }

protected:
  const TCHAR* findCallbackName(Event& event, HWND child)
  {
    TCHAR name[1024];
    ::GetClassName(child, name, CountOf(name)); //2012/06/21

    if(strcmp(name, _T("Button")) == 0) {
      Button button(NULL, child);
      return button.getCallbackName(event);
    }  
    if(strcmp(name, _T("Edit")) == 0) {
      Text  text(NULL, child);
      return text.getCallbackName(event);
    }  
    if(strcmp(name, _T("ListBox")) == 0) {
      ListBox listbox(NULL, child);
      return listbox.getCallbackName(event);
    }  
    if(strcmp(name, _T("ComboBox")) == 0) {
      ComboBox combobox(NULL, child);
      return combobox.getCallbackName(event);
    }
  // Add lines here for new controls. 
  //
    return XmNactivateCallback;    
  }

public:
  void  getValues(Args& args)
  {
    View::getValues(args);
    getStyle(args, styles(), stylesCount());

    int num   = args.getCount();
    Arg* arg  = args.getArgList();
    int max, min;

    for(int i = 0; i<num; i++) {
      const TCHAR*    name = arg[i].name;
      LONG_PTR* val  = (LONG_PTR*)arg[i].value;
      if(name == XmNpageIncrement) {
        *val =  lineIncrement;
        continue;
      }
      if(name == XmNlineIncrement) {
        *val =  lineIncrement;
        continue;
      }
      if(name == XmNhorizScrollMaximum) {
        getScrollRange(SB_HORZ, &min, &max);
        *val = max;
        continue;
      }
      if(name == XmNhorizScrollMinimum) {
        getScrollRange(SB_HORZ, &min, &max);
        *val = min;
        continue;
      }
      if(name == XmNhorizThumbPosition) {
        *val = (LONG_PTR)getScrollPos(SB_HORZ);        
        continue;
      }
      if(name == XmNvertScrollMaximum) {
        getScrollRange(SB_VERT, &min, &max);
        *val = max;
        continue;
      }
      if(name == XmNvertScrollMinimum) {
        getScrollRange(SB_VERT, &min, &max);
        *val = min;
        continue;
      }
      if(name == XmNvertThumbPosition) {
        *val = (LONG_PTR)getScrollPos(SB_VERT);        
        continue;
      }
    }
  }

public:
  void setScrollExtent(UINT w, UINT h)
  {
    extent.set(w, h);
    justifyScrollRange();
  }  

public:
  void justifyScrollRange()
  {
    RECT r;
    getClientRect(&r);
    int maxx, maxy;
    UINT w, h;
    extent.get(&w, &h); 
    maxx = w - (r.right - r.left);
    maxy = h - (r.bottom - r.top);
    if(maxx < 0) maxx = 0;
    //<modified date="2000.05.09">
    //if(maxx < 0) maxy = 0;
    if(maxy < 0) maxy = 0;
    //</modified>

    setScrollRange(SB_HORZ, 0, maxx);
    setScrollRange(SB_VERT, 0, maxy);

    // Justify
    getClientRect(&r);
    maxx = w - (r.right - r.left);
    maxy = h - (r.bottom - r.top);
    if(maxx < 0) maxx = 0;
    //<modified date="2000.05.09">
    //if(maxx < 0) maxy = 0;
    if(maxy < 0) maxy = 0;
    //</modified>

    setScrollRange(SB_HORZ, 0, maxx);
    setScrollRange(SB_VERT, 0, maxy);
  }


public:
  BOOL getScrollInfo(int type, SCROLLINFO* scInfo) 
  {
    BOOL rc = FALSE;
    if(scInfo) {
      scInfo->cbSize = sizeof(SCROLLINFO);
      rc  = ::GetScrollInfo(getWindow(), type, scInfo);
    }
    return rc;
  }
  
public:
  int  setScrollInfo(int type, SCROLLINFO* scInfo) 
  {
    int pos = 0;
    if(scInfo) {
      scInfo->cbSize = sizeof(SCROLLINFO);
      pos = ::SetScrollInfo(getWindow(), type, scInfo, TRUE);
    }
    return pos;
  }

public:
  void getPreferredSize(Dimension& d)
  {
    if (layoutManager == NULL) {
      View::getPreferredSize(d);
    }
    else {
      int w, h;
      getSize(w, h);
      layoutManager -> getExtension(d, w, h);
    }
  }

public:
  void pack()
  {
    int w, h;
    getSize(w, h);
    send(WM_SIZE, 0, MAKELONG(w, h));
  }

  void  add(View* view) {
      layoutManager->add(view);
  }

  void  add(View* view, int pos) {
      layoutManager->add(view, pos);
  }

  void  add(View& view) {
      layoutManager->add(&view);
  }
  void  add(View& view, int pos) {
      layoutManager->add(&view, pos);
  }

  LayoutManager* getLayoutManager() { return layoutManager; }

  void  raise() {
      ::BringWindowToTop(getWindow());
  }

  void  setLayout(LayoutManager* layout) {
      layoutManager = layout;
  }


  virtual BOOL  translate(MSG*  msg) { 
    return FALSE;
  }

  int    dirList(const TCHAR* filename, int idList, int idStatic, 
          UINT fileType) {
      return ::DlgDirList(getWindow(), (TCHAR*)filename, idList, 
        idStatic, fileType);
  }
  int    dirListComboBox(const TCHAR* pathName, int idCombo, int idStatic, 
          UINT fileType) {
      return ::DlgDirListComboBox(getWindow(), (TCHAR*)pathName, 
        idCombo,  idStatic, fileType);
  }

  int    dirSelect(const TCHAR* pathName, int len, int idList) {
      return ::DlgDirSelectEx(getWindow(), (TCHAR*)pathName, len, idList);
  }

  int    dirSelectComboBox(const TCHAR* pathName, int len, int idCombo) {
      return ::DlgDirSelectComboBoxEx(getWindow(), (TCHAR*)pathName, 
        len, idCombo);
  }

  int    getItemText(int id, TCHAR* buffer, int max) {
        return ::GetDlgItemText(getWindow(), id, buffer, max);
  }
  int    getItemInt(int id, BOOL* translated, BOOL sign) {
        return ::GetDlgItemInt(getWindow(), id,
        translated, sign);
  }
  HWND  getItem(int id) {
        return ::GetDlgItem(getWindow(), id);
  }
  HWND  getNextGroupItem(HWND control, BOOL prev) {
        return ::GetNextDlgGroupItem(getWindow(), control, prev);
  }
  HWND  getNextTabItem(HWND control, BOOL prev) {
        return ::GetNextDlgTabItem(getWindow(), control, prev);
  }

  void  checkButton(int id, UINT flag) {
        ::CheckDlgButton(getWindow(), id, flag);
  }
  void  checkButton(int firstId, int lastId, int checkId) {
        ::CheckRadioButton(getWindow(), firstId, lastId, checkId);
  }
  UINT  isButtonChecked(int id) {
        return ::IsDlgButtonChecked(getWindow(), id);
  }
  LRESULT  sendDlgItem(int id, UINT message, WPARAM wParam, LPARAM lParam) {
      return ::SendDlgItemMessage(getWindow(), id, 
          message, wParam, lParam);
  }
  void  setItemText(int id, const TCHAR* string) {
        ::SetDlgItemText(getWindow(), id, string);
  }
  void  setItemInt(int id, UINT val, BOOL sign) {
        ::SetDlgItemInt(getWindow(), id, val, sign);
  }

  void  getScrollExtent(UINT* w, UINT* h) {
      extent.get(w, h);
  }

public:
  Font*  getDefaultFont() { return &defaultFont; }

public:
  //2011/02/20
  virtual IOleInPlaceFrame* getInPlaceFrame() 
  {
    return NULL;
  }
  
  virtual IOleObject* getOleObject() 
  {
    return NULL;
  }

};

}

