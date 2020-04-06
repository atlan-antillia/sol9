/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileVersionDialog.h
 *
 *****************************************************************************/

// SOL9
// 2008/12/16
// 2012/09/28 Modified size

#include <sol\PopupView.h>
#include <sol\ListView.h>
#include <sol\PushButton.h>
#include <sol\MessageFont.h>
#include <sol\FileVersion.h>

#pragma  comment(lib,"version.lib")

namespace SOL {

class FileVersionDialog: public PopupView {
public:
  static const int WIDTH = 560;
  static const int HEIGHT = 380;

private:
  FileVersion  version;
  ListView  listview;
  PushButton  ok;
  MessageFont mfont;

public:
  FileVersionDialog()
    :PopupView()
  {
  }

public:
  FileVersionDialog(View* parent, const TCHAR* label, Args& args)
  :PopupView(parent, label,    
      args.set(XmNwidth, WIDTH)
        .set(XmNheight, HEIGHT)
        .set(XmNstyle, WS_SIZEBOX|WS_THICKFRAME))
  {
    Args ar;
    //2009/09/07
    //ar.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE);
    ar.set(XmNstyle, (LONG_PTR)LVS_REPORT);
    listview.create(this, _T(""), ar);
    
    ar.reset();
    ok.create(this, _T("OK"), ar);
    mfont.create();
  
    ok.setFont(mfont.getFont());
    ok.addCallback(XmNactivateCallback, this,
          (Callback)&FileVersionDialog::popdown, NULL);
    resize();
    
    showFileInfo();
    addEventHandler(WM_SIZE, this, 
      (Handler)&FileVersionDialog::size, NULL);
  }

public:
  Boolean create(View* parent)
  {
    Boolean rc = False;
    Args args;
    args.set(XmNwidth, WIDTH);
    args.set(XmNheight, HEIGHT);
    args.set(XmNstyle, WS_SIZEBOX|WS_THICKFRAME);

    rc = PopupView::create(parent, _T("FileVersion"), args);

    Args ar;
    //2009/09/07
    //ar.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE);
    ar.set(XmNstyle, (LONG_PTR)LVS_REPORT);
    listview.create(this, _T(""), ar);
    
    ar.reset();
    ok.create(this, _T("OK"), ar);
    mfont.create();
  
    ok.setFont(mfont.getFont());
    ok.addCallback(XmNactivateCallback, this,
          (Callback)&FileVersionDialog::popdown, NULL);
    resize();
    
    showFileInfo();
    addEventHandler(WM_SIZE, this, 
      (Handler)&FileVersionDialog::size, NULL);

    return rc;          
  }


private:
  void setWindowTitle(const TCHAR* title) {
    if (title) {
      if (strlen(title)>0) {
        TCHAR msg[1024];
        _stprintf_s(msg, CountOf(msg), _T("%s - FileVersion"), title);
        setText(msg);
      }
    }
  }

private:
  bool showFileInfo()
  {
    bool rc = false;

    listview.clear();
    const TCHAR* labels[] = {_T("Name"), _T("Value")};
    listview.setColumn(labels, 2);

    try {
      int n=0;

      setWindowTitle(version.getProgramName());

      const TCHAR* text[2];
      text[0] = _T("Comments");
      text[1] = (TCHAR*)version.getComments();
      listview.insertLine(n++, text, 2);

      text[0] = _T("CompanyName");
      text[1] = (TCHAR*)version.getCompanyName();
      listview.insertLine(n++, text, 2);

      text[0] = _T("FileDescription");
      text[1] = (TCHAR*)version.getFileDescription();
      listview.insertLine(n++, text, 2);

      text[0] = _T("FileVersion");
      text[1] = (TCHAR*)version.getFileVersion();
      listview.insertLine(n++, text, 2);

      text[0] = _T("InternalName");
      text[1] = (TCHAR*)version.getInternalName();
      listview.insertLine(n++, text, 2);
    
      text[0] = _T("LegalCopyRight");
      text[1] = (TCHAR*)version.getLegalCopyRight();
      listview.insertLine(n++, text, 2);

      text[0] = _T("LegalTrademarks");
      text[1] = (TCHAR*)version.getLegalTrademarks();
      listview.insertLine(n++, text, 2);

      text[0] = _T("OriginalFilename");
      text[1] = (TCHAR*)version.getOriginalFilename();
      listview.insertLine(n++, text, 2);
      
      text[0] = _T("ProductName");
      text[1] = (TCHAR*)version.getProductName();
      listview.insertLine(n++, text, 2);

      text[0] = _T("ProductVersion");
      text[1] = (TCHAR*)version.getProductVersion();
      listview.insertLine(n++, text, 2);

      text[0] = _T("PrivateBuild");
      text[1] = (TCHAR*)version.getPrivateBuild();
      listview.insertLine(n++, text, 2);

      text[0] = _T("SpecialBuild");
      text[1] = (TCHAR*)version.getPrivateBuild();
      listview.insertLine(n++, text, 2);
      rc = true;
    } catch (...) {
      ;//This has no version resource
    }
    return rc;    
  }

private:
  long size(Event& ev) {
    LPARAM lp = ev.getLParam();
    int w = LOWORD(lp);
    int h = HIWORD(lp);
    listview.move(4, 4, w-8, h-44, 1);
    ok.move(w-70, h-40+14, 50, 22, 1);
    return 0;
  }

};

}

