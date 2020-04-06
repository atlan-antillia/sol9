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
 *  WebBrowser.h
 *
 *****************************************************************************/


// SOL++2000 
// 2008/08/10
// 2008/09/16 Added an event handler for WM_BROWSER_DOCUMENTCOMPLETE from SOL::BrowserEvent class.
// 2009/10/04 Modified a value of DEFAULT_WIN_CLASS_STYLE of class Application in Main function 
//in the follwing way to avoid a window redrawing.
//
//   Application::DEFAULT_WIN_CLASS_STYLE = CS_DBLCLKS;

#include <sol\PopupView.h>
#include <sol\ole\HTMLView.h>
#include <sol\ExtendedCombobox.h>

#include "resource.h"

namespace SOL {

/**
 * class WebBrowser based on SOL::PopupView
 */
class WebBrowser :public PopupView {
private:
  HTMLView htmlView;
  ExtendedComboBox comboBox;

public:
  WebBrowser()
    :PopupView()
  {
  }

public:
  /**
   * Constructor
   */
  WebBrowser(View* parent, const TCHAR* name, Args& args)
  :PopupView(parent, name, 
      args.set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
      .set(XmNstyle, WS_THICKFRAME|WS_POPUP|WS_CLIPCHILDREN) )
  {
    Args ar;
    ar.set(XmNstyle, (LONG_PTR)CBS_DROPDOWN);
    ar.set(XmNheight, 100);
    comboBox.create(this, _T(""), ar);
    comboBox.addCallback(XmNselChangeCallback, this, 
      (Callback)&WebBrowser::selChanged, NULL);

    ar.reset();
    
    ar.set(XmNclassStyle, CS_DBLCLKS);

    ar.set(XmNstyle, WS_CHILD|WS_VISIBLE);
    htmlView.create(this, _T(""), ar);


    addEventHandler(WM_SIZE, this, 
        (Handler)&WebBrowser::size, NULL);
    addEventHandler(WM_CLOSE, this, 
        (Handler)&WebBrowser::close, NULL);
    
    addEventHandler(WM_BROWSER_DOCUMENTCOMPLETE, this, 
      (Handler)&WebBrowser::complete, NULL);

    addEventHandler(WM_NOTIFY, this,(Handler)&WebBrowser::notify, NULL);

    resize();
  }

public:
  /**
   * Constructor
   */
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = PopupView::create(parent, name, 
      args.set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
      .set(XmNstyle, WS_THICKFRAME|WS_POPUP|WS_CLIPCHILDREN) );

    Args ar;
    ar.set(XmNstyle, (LONG_PTR)CBS_DROPDOWN);
    ar.set(XmNheight, 100);
    comboBox.create(this, _T(""), ar);
    comboBox.addCallback(XmNselChangeCallback, this, 
      (Callback)&WebBrowser::selChanged, NULL);

    ar.reset();
    
    ar.set(XmNclassStyle, CS_DBLCLKS);

    ar.set(XmNstyle, WS_CHILD|WS_VISIBLE);
    htmlView.create(this, _T(""), ar);


    addEventHandler(WM_SIZE, this, 
        (Handler)&WebBrowser::size, NULL);
    addEventHandler(WM_CLOSE, this, 
        (Handler)&WebBrowser::close, NULL);

    addEventHandler(WM_BROWSER_DOCUMENTCOMPLETE, this, 
        (Handler)&WebBrowser::complete, NULL);

    addEventHandler(WM_NOTIFY, this,
        (Handler)&WebBrowser::notify, NULL);

    resize();

    return rc;
  }

public:
  void disableComboBox()
  {
    comboBox.disable();
  }

public:
  void enableComboBox()
  {
    comboBox.enable();
  }

private:
  /**
   * CBN_SELCHANGE callback.
   * Get a url (current selection) of comboBox and navigate to the url.
   */
  void selChanged(Action& action) {
    COMBOBOXEXITEM ci;
    memset(&ci, 0, sizeof(ci));
    TCHAR url[1024];
    memset(url, (TCHAR)0, CountOf(url)); //2012/06/21
    ci.mask = CBEIF_TEXT;
    ci.pszText = url;
    ci.cchTextMax = CountOf(url);  //2012/06/21
    ci.iItem = -1;
    
    comboBox.send(CBEM_GETITEM, 0, (LPARAM)&ci);
    htmlView.navigate(url);
    TCHAR caption[1024];
    _stprintf_s(caption, CountOf(caption), _T("%s - WebBrowser"), (const TCHAR*)url);
    setText(caption);
  }

public:
  /**
   * WM_SIZE event handler.
   */
  long size(Event& event)
  {
    LPARAM l = event.getLParam();
    
    int w, h;
    comboBox.getSize(w, h);

    comboBox.reshape(0, 0, LOWORD(l), h);
    htmlView.reshape(0, h, LOWORD(l), HIWORD(l)-h);

    return 0;
  }

public:
  /**
   * Event handler for a user-defined WM_BROWSER_DOCUMENTCOMPLETE from SOL::BrowserEvent class.
   *  
   */
  long complete(Event& event)
  {
    //Implement your code to handle DISPID_COMPLETE
    String url = "";
    htmlView.getLocationURL(url);
    const TCHAR* curl = (const TCHAR*)url;
    
    if (curl && !(_stricmp(curl, _T("about:blank")) ==0 ||
      _stricmp(curl, _T("res://ieframe.dll/navcancl.htm")) ==0) ) {    
      comboBox.setText(curl);

      int e = comboBox.send(CB_FINDSTRINGEXACT, -1, (LPARAM)curl);
      if (e == CB_ERR) {
        //If comboBox has no entry for the curl, add it to the comboBox.
        COMBOBOXEXITEM cbei;
        memset(&cbei, 0, sizeof(cbei));
        cbei.mask = CBEIF_TEXT;

        cbei.iItem          = 0;
        cbei.pszText        = (TCHAR*)curl;
        cbei.cchTextMax     = strlen(curl);

        comboBox.send(CBEM_INSERTITEM, 0,(LPARAM)&cbei);
      }
    }
    return 0;
  }

public:
  long notify(Event& event) 
  {
    LPARAM lParam = event.getLParam();
  
    NMCOMBOBOXEX* nm = (NMCOMBOBOXEX*)lParam;
    if (nm->hdr.hwndFrom == comboBox.getWindow() &&
      nm->hdr.code==CBEN_ENDEDIT) {

      NMCBEENDEDIT* nme = (NMCBEENDEDIT*)nm;
      if (nme->iWhy == CBENF_RETURN) {
    
        TCHAR url[1024];
        memset(url, (TCHAR)0, CountOf(url));
        comboBox.getText(url, CountOf(url));
        if (strlen(url)>0) {
          navigate(url);
        }
      }
    }
    return 0;
  }


public:
  long close(Event& event)
  {
    //Popdown : Hide this window;
    show(SW_HIDE);
    return 0L;
  }

public:
  void navigate(const TCHAR* url) {
    //If you change font size, call zoom method with some level(0,1,2,3,4)
    //htmlView.zoom(2);

    htmlView.navigate(url);
    TCHAR caption[1024];
    
    _stprintf_s(caption, CountOf(caption), _T("%s - WebBrowser"), (const TCHAR*)url);
    setText(caption);
    comboBox.setText(url);
  }
};

}
