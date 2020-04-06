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
 *  PropertyDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2009/11/04 Modified not to depend on SOL::PropertyPage class.
// 2012/06/25

#pragma once
#include <sol\PopupView.h>

namespace SOL {

class PropertyDialog :public PopupView {
private:
  int  pages;
  int  curIndex;
  PROPSHEETPAGE*   psp;
  PROPSHEETHEADER* psh;

public:
  PropertyDialog(): PopupView() { }

public:
  /**
   * Constructor
   */
  //2012/06/25
  PropertyDialog(View* parent, const TCHAR* caption, Args& args)
  :PopupView()
  {
    create(parent, caption, args);
  }


public:
  ~PropertyDialog() 
  { 
    delete psh;
    delete [] psp;
  }

public:
  Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = True;

    View::setParent(parent);

    psh = new PROPSHEETHEADER;
    memset(psh, 0, sizeof(PROPSHEETHEADER));
    pages = 5;  // default
    LONG_PTR val = args.get(XmNpages);
    if(val) {
      pages = (int)val;
    }
    curIndex = 0;

    psp = new PROPSHEETPAGE[pages];

    psh->ppsp = (LPCPROPSHEETPAGE)psp;
    psh->nPages = curIndex;
    psh->nStartPage = 0;
    psh->dwSize     = sizeof(PROPSHEETHEADER);
    psh->dwFlags    = PSH_PROPSHEETPAGE; //|PSH_PROPTITLE;

    if(parent) {
      psh -> hwndParent = parent->getWindow();
    }
    //Application& applet = Application::getApplet(NULL);

    psh->hInstance  = GetModuleHandle(NULL);//applet.getInstance();//Application::getInstance();
    psh->pszCaption = caption;

    setValues(args);

    return rc;
  }


public:
  PROPSHEETPAGE* getCurPage() 
  {
    if(curIndex<pages) {
      return &psp[curIndex];
    }
    else {
      return NULL;
    }
  }

/*
VOID CALLBACK PropertyDialog::SheetCallback(HWND  hwndDlg,  
    UINT  message,  LPARAM  lParam)
{
  if(message == PSCB_INITIALIZED) {
    View* self = (View*)lParam;
    if(self) {
      Application::Add(hwndDlg, self);
    }
  }  
}
*/


public:
  BOOL addPage(HPROPSHEETPAGE hPage) //PropertyPage* page) 
  {
    BOOL rc = FALSE;
    //if(page) {
      if(hPage) {//page->getPageHandle()) {
        send(PSM_ADDPAGE, 0, (LPARAM)hPage);//page->getPageHandle());
        rc = TRUE;
      }
      curIndex++;
    //}
    return rc;
  }


public:
  void popup(Action& action) 
  { 
    psh -> nPages = curIndex;
    action.setResult(::PropertySheet(psh));
  }

public:
  void setValues(Args& args)
  {
    LONG_PTR val = NULL;
    val = args.get(XmNflags);
    if(val) { 
      psh -> dwFlags |= val;
    }

    val = args.get(XmNicon);
    if(val) { 
      psh -> hIcon = (HICON)val;
    }

    val = args.get(XmNstartPage);
    if(val) {
      psh -> nStartPage = (int)val;
    }
  }


public:
  int    getCurIndex() { return curIndex; }

public:
  void  setCurSel(int indx, HPROPSHEETPAGE hPage) //PropertyPage* page) {
  {
         send(PSM_SETCURSEL, indx, (LPARAM)hPage);//page->getPageHandle());
  }

public:
  void  removePage(int indx, HPROPSHEETPAGE hPage) //PropertyPage* page) {
  {
      send(PSM_REMOVEPAGE, indx, (LPARAM)hPage);//page->getPageHandle());
  }

public:
  void  changed(HPROPSHEETPAGE hPage) //PropertyPage* page) {
  {
      send(PSM_CHANGED, (WPARAM)hPage,
        //page->getPageHandle(),
        0);
  }  

public:
  void  unChanged(HPROPSHEETPAGE hPage) //PropertyPage* page) {
  {
      send(PSM_UNCHANGED, (WPARAM)hPage,
        //page->getPageHandle(), 
        0);
  }  

public:
  void  restartWindows() {
      send(PSM_RESTARTWINDOWS, 0, 0);      
  }

public:
  void  rebootSystem() {
      send(PSM_REBOOTSYSTEM, 0, 0);      
  }

public:
  void  cancelToClose() {
      send(PSM_CANCELTOCLOSE, 0, 0);      
  }

public:
  void  querySiblings(WPARAM wParam, LPARAM lParam) {
      send(PSM_QUERYSIBLINGS, wParam, lParam);
  }

public:
  void  apply() {
      send(PSM_APPLY, 0, 0);        
  }  

public:
  void  setTitle(WPARAM style, TCHAR* title) {
      send(PSM_SETTITLE, style, (LPARAM)title);
  }

public:
  void  setWizButtons(LPARAM flags) {
      send(PSM_SETWIZBUTTONS, 0, (LPARAM)flags);
  }

public:
  void  pressButton(int idbutton) {
      send(PSM_PRESSBUTTON, idbutton, 0);
  }

public:
  void  setCurSelByID(int id) {
      send(PSM_SETCURSELID, 0, (LPARAM)id);
  }

public:
  void  setFinishText(TCHAR* text) {
      send(PSM_SETFINISHTEXT, 0, (LPARAM)text);
  }

public:
  HWND  getTabControl() {
      return (HWND)send(PSM_GETTABCONTROL, 0, 0);
  }

public:
  BOOL  isDialogMessage(MSG* pMsg) {
      return (BOOL)send(PSM_ISDIALOGMESSAGE, 0, (LPARAM)pMsg);
  }

public:
  HWND  getCurrentPageHwnd() {
      return (HWND)send(PSM_GETCURRENTPAGEHWND, 0, 0L);
  }
};

}


