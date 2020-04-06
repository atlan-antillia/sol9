/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FilePropertyViewer.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/16
// 2012/06/22

#include <sol\PopupView.h>
#include <sol\ListView.h>
#include <sol\PushButton.h>
#include <sol/StringConverter.h>
#include <sol\MessageFont.h>
#include <sol\FileAttributes.h>

namespace SOL {

class FilePropertyViewer: public PopupView {

private:
//  FileProperty  version;
  ListView  listview;
  PushButton  ok;
  MessageFont mfont;
  bool columns;

public:
  FilePropertyViewer()
    :PopupView()
  {
  }

public:
  //2012/06/22
  FilePropertyViewer(View* parent, const TCHAR* label, Args& args)
  :PopupView()
  {
    create(parent, label, args);
  }

public:
  Boolean create(View* parent)
  {
    Boolean rc = False;
    Args args;
    args.set(XmNwidth, 540);
    args.set(XmNheight, 300);
    args.set(XmNstyle, WS_SIZEBOX|WS_THICKFRAME);

    rc = PopupView::create(parent, _T("FileProperty"), args);

    Args ar;
    //ar.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE);
    ar.set(XmNstyle, (LONG_PTR)LVS_REPORT);
    listview.create(this, "", ar);
    //const TCHAR* labels[] = {"Name", "Value"};
    //listview.setColumn(labels, 2);
    ListViewColumn columns[] = {
      {_T("Name"),  LVCFMT_LEFT, 140},
      {_T("Value"), LVCFMT_LEFT, 380},
    };

    listview.setColumn(columns, 2);

    ar.reset();
    ok.create(this, _T("OK"), ar);
    mfont.create();
  
    ok.setFont(mfont.getFont());
    ok.addCallback(XmNactivateCallback, this,
          (Callback)&FilePropertyViewer::popdown, NULL);
    resize();
    const TCHAR* fileName = (const TCHAR*)args.get(XmNfileName);
    
    showFileInfo(fileName);
    addEventHandler(WM_SIZE, this, 
      (Handler)&FilePropertyViewer::size, NULL);

    return rc;          
  }


private:
  void setWindowTitle(const TCHAR* title) {
    if (title) {
      if (strlen(title)>0) {
        TCHAR msg[1024];
        _stprintf_s(msg, CountOf(msg), _T("%s - FileProperty"), title);
        setText(msg);
      }
    }
  }

public:
  bool showFileInfo(const TCHAR* fileName)
  {
    bool rc = false;

    listview.clear();
  
    if (fileName == NULL) {
      return rc;
    }

    try {
      int n=0;
      FileAttributes attrs(fileName);

      setWindowTitle(fileName);

      const TCHAR* text[2];
      text[0] = _T("Name");
      String fileName;
      attrs.getFileName(fileName);

      text[1] = (TCHAR*)(const TCHAR*)fileName;
      listview.insertLine(n++, text, 2);

      text[0] = _T("Size");
      String fileSize;
      attrs.getFileKBSize(fileSize);
      text[1] = (TCHAR*)(const TCHAR*)fileSize;
      listview.insertLine(n++, text, 2);

      text[0] = _T("CreationTime");
      String creationTime;
      attrs.getCreationTime(creationTime);
      text[1] = (TCHAR*)(const TCHAR*)creationTime;
      listview.insertLine(n++, text, 2);

      text[0] = _T("LastAccessTime");
      String lastAccessTime;
      attrs.getLastAccessTime(lastAccessTime);
      text[1] = (TCHAR*)(const TCHAR*)lastAccessTime;
      listview.insertLine(n++, text, 2);

      text[0] = _T("LastModifiedTime");
      String lastModifiedTime;
      attrs.getLastModifiedTime(lastModifiedTime);
      text[1] = (TCHAR*)(const TCHAR*)lastModifiedTime;
      listview.insertLine(n++, text, 2);

      text[0] = _T("Type");
      String type;
      attrs.getFileType(type);
      text[1] = (TCHAR*)(const TCHAR*)type;
      listview.insertLine(n++, text, 2);

      text[0] = _T("Attributes");
      String fileAttrs;
      attrs.getAttributes(fileAttrs);

      text[1] = (TCHAR*)(const TCHAR*)fileAttrs;
      listview.insertLine(n++, text, 2);

      text[0] = _T("Owner");
      String owner;
      attrs.getOwnerName(owner);
      text[1] = (TCHAR*)(const TCHAR*)owner;
      listview.insertLine(n++, text, 2);
    
      text[0] = _T("Domain");
      String domain;
      attrs.getOwnerDomain(domain);
      text[1] = (TCHAR*)(const TCHAR*)domain;
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

