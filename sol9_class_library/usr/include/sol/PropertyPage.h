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
 *  PropertyPage.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2009/11/04 Modified to implement on PropertyPage.h file. Removed PropertyPage.cpp
// 2012/06/25

#pragma once

#include <sol\PopupView.h>
#include <sol\Application.h>
#include <sol\PropertyPage.h>
#include <sol\stdio.h>
#include <sol\PropertyDialog.h>

namespace SOL {


class PropertyPage :public PopupView {
private:
  PROPSHEETPAGE* psp;
  HPROPSHEETPAGE hpage;

public:
  PropertyPage(): PopupView() { }

public:
  /**
   * Constructor
   */
  PropertyPage(PropertyDialog* parent, const TCHAR* title, Args& args)
  :PopupView()
  {
    create(parent, title, args);
  }

public:
  ~PropertyPage()
  {
    delete psp;
    if(hpage) {
      ::DestroyPropertySheetPage(hpage);
    }
  }


public:
  Boolean create(PropertyDialog* parent, const TCHAR* title, Args& args)
  {
    Boolean rc = True;
    View::setParent(parent);

    hpage = NULL;

    // Assuming that parent != NULL
    psp = parent->getCurPage();
    //Application& applet = Application::getApplet();
    if(psp) {
      memset(psp, 0, sizeof(PROPSHEETPAGE));
      psp -> dwSize = sizeof(PROPSHEETPAGE);
      // set default values
      psp -> dwFlags     = PSP_USETITLE|PSP_USECALLBACK;
      psp -> pfnDlgProc  = (DLGPROC)PropertyPage::procedure;
      psp -> hInstance   = GetModuleHandle(NULL);//applet.getInstance();//Application::getInstance();
    //  psp -> pfnCallback = (LPFNPSPCALLBACK)
    //        PropertyPage::pageCallback;
      
      psp -> pszTitle    = title;
      psp -> pszTemplate = (TCHAR*)args.get(XmNtemplateName);
      psp -> lParam      = (LPARAM)this;

      LONG_PTR val = NULL;
      val = args.get(XmNflags);
      if(val) {
        psp -> dwFlags |= val;
      }

      val = args.get(XmNicon);
      if(val) {
        psp -> pszIcon = (TCHAR*)val;
      }
      // 
      if(parent->isWindow()) {    
        hpage = ::CreatePropertySheetPage(psp);
      }    
      addEventHandler(WM_INITDIALOG, this,
        (Handler)&PropertyPage::initDialog, NULL);
    
      parent -> addPage(hpage);//this);
    }

    return rc;
  }

public:
  PROPSHEETPAGE* getPage() { return psp; }

public:
  HPROPSHEETPAGE getPageHandle() { return hpage; }

private:
  static UINT CALLBACK pageCallback(HWND  hwnd, UINT message,  
            LPPROPSHEETPAGE  ppsp)
  {
    //Printf("PageCallback hwnd = %d  message = %d\r\n", 
    //  (int)hwnd, message);
    if(message == PSPCB_CREATE) {

    }
    return TRUE;
  }

private:
  static BOOL procedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    PropertyPage* page = NULL;

    if (message == WM_INITDIALOG) {
      LPPROPSHEETPAGE  ppsp = (LPPROPSHEETPAGE)lParam;

      page = (PropertyPage*)ppsp->lParam;

    }
    if(page) {
      page -> setWindow(hwnd);

      Application::add(hwnd, page);
      HWND hparent = ::GetParent(hwnd);
      View* sheet = page -> getParent();
      if(sheet && sheet->getWindow() == NULL) {
      //  Printf("Set PageCallback hparent  %d 3\r\n",(int)hparent);
        sheet -> setWindow(hparent);
        Application::add(hparent, sheet);
      }
    } else {
      page = (PropertyPage*)Application::lookup(hwnd);
    }
    if(page == NULL) { 
      return FALSE;
    }
    if(message == WM_DESTROY) {
      Application::remove(hwnd);
      return FALSE;
    }

    Event event(message, wParam, lParam);

    return (BOOL)page -> dispatch(event);
  
  }

public:
  void addCallback(const TCHAR* name, Object* object,
           Callback proc, void* data)
  {
    View::addCallback(name, (Key)this, object, 
              proc, data);
  }


protected:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
    {XmNsetActiveCallback, PSN_SETACTIVE},
    {XmNkillActiveCallback, PSN_KILLACTIVE},
    {XmNapplyCallback,  PSN_APPLY},
    {XmNresetCallback,   PSN_RESET},
    {XmNhasHelpCallback, PSN_HELP},
    {XmNwizBackCallback, PSN_WIZBACK},
    {XmNwizNextCallback, PSN_WIZNEXT},
    {XmNwizFinishCallback, PSN_WIZFINISH},
    {XmNqueryCancelCallback, PSN_QUERYCANCEL},
    };
    *num = XtNumber(table);
    return table;
  }

protected:

  long command(Event& event) 
  {
    HWND child  = event.getChild();
    const TCHAR* name = findCallbackName(event, child);
    callCallback(name, (Key)child, NULL, event);

    return TRUE;
  }

protected:
  virtual long initDialog(Event& event)
  {
    return NULL;
  }
  
protected:
  long notify(Event& event)
  {
    NMHDR* hdr = (NMHDR*)event.getLParam();
    HWND  sender  = hdr->hwndFrom;

    HWND self = getWindow();
    HWND hparent = ::GetParent(self);
    const TCHAR* name = NULL;
    if(hparent == sender) {
      name = getCallbackName(event);
      if(name) {  
        callCallback(name, (Key)this , NULL, event);
      }
      return event.getResult();
    }

    View* view = (View*)Application::lookup(sender);
    if(view) {
      name = isCommonNotification(event);
      if(name == NULL) {
        name = view->getCallbackName(event);
      }
      if(name) {
        callCallback(name, (Key)sender, NULL, event);
      }
    }
      return event.getResult();
  }

public:

  void setMsgResult(long result)
  {
    setWindowLongPtr(DWLP_MSGRESULT, (LONG_PTR)result);
  }

};

}

