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
 *  FolderTreeDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\TextField.h>
#include <sol\Static.h>
#include <sol\PushButton.h>

#include <sol\DynamicDialog.h>
#include <sol\Font.h>
#include <sol\FolderTreeView.h>
#include <sol\ClientDC.h>


namespace SOL {

class FolderTreeDialog :public DynamicDialog {
private:
  BOOL    initialized;
  int      th;
  int      bwidth;
  Static    label;
  Font    font;
  TextField  textf;
  FolderTreeView treev;
  PushButton  ok;
  PushButton  cancel;
private:
//  long  size(Event& event);
//  void  expanding(Action& action);
//  void  selChanging(Action& action);
private:
  long size(Event& event)
  {
    LPARAM s = event.getLParam();
    
    int w = LOWORD(s);
    int h = HIWORD(s);

    label.reshape(0, 2,  w, th);
    textf.reshape(0, 2+th, w, th+8); 
    treev.reshape(0, th+th+10, w, h-th-th-10-th-20);

    ok.reshape(w-bwidth*2-20, h - th-16, bwidth, th+12);
    cancel.reshape(w-bwidth-10, h - th-16, bwidth, th+12);
    
    return 0;
  }

private:
  void expanding(Action& action)
  {               
    Event& event = action.getEvent();  
    NM_TREEVIEW* nmtreev = (NM_TREEVIEW*)event.getLParam();
    HTREEITEM htreeItem = nmtreev->itemNew.hItem;
    //2015/12/12
    StringBufferT<TCHAR> dir;
    treev.getHierachy(htreeItem, dir, _T("\\"));

    treev.findDirectories(htreeItem, dir, 0, 2);
    treev.sortChildren(htreeItem, TRUE);
  }


private:
  void selChanging(Action& action)
  {               
    Event& event = action.getEvent();  
    NM_TREEVIEW* nmtreev = (NM_TREEVIEW*)event.getLParam();
    HTREEITEM htreeItem = nmtreev->itemNew.hItem;
    //2015/12/12
    StringBufferT<TCHAR> dir;
    treev.getHierachy(htreeItem, dir, _T("\\"));
    textf.setText(dir);
  }

public:
  FolderTreeDialog():DynamicDialog() { }

public:
  //2012/06/22
  FolderTreeDialog(View* parent, 
            const TCHAR* name, Args& args)
  :DynamicDialog()
  {
    create(parent, name, args);
  }

public:
  ~FolderTreeDialog() 
  { 
  }


public:
  virtual Boolean create(View* parent, 
            const TCHAR* name, Args& args)

  {
    Boolean rc = DynamicDialog::create(parent, name,
      args.set(XmNstyle, (LONG_PTR)WS_THICKFRAME)
          .set(XmNbackground, (COLOR_BTNFACE+1)));

    initialized = FALSE;
    Args ar;
    ar.reset();
    ar.set(XmNheight, -12);
    //  ar.set(XmNTCHARSet, (LONG_PTR)SHIFTJIS_CHARSET);  
    //  ar.set(XmNfaceName, "‚l‚r –¾’©");
    font.create(ar);

    ar.reset();
    label.create(this, _T("Folder"), ar);
    label.setFont(&font);

    ar.reset();
    textf.create(this, _T(""), ar);
    textf.limitText(_MAX_PATH);
    textf.setFont(&font);

    ClientDC cdc(&textf);

    HFONT pfont = (HFONT)cdc.select(&font);
    th = cdc.getTextHeight();

    SIZE size;
    TCHAR* string = _T(" OK ");
    cdc.getTextExtent(string, strlen(string), &size);            
    cdc.select(pfont);

    bwidth = size.cx+ size.cy*2;

    ar.reset();
    ar.set(XmNexStyle, (LONG_PTR)WS_EX_CLIENTEDGE);
    ar.set(XmNstyle, (LONG_PTR)TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT);
    treev.create(this, _T(""), ar);

  // 
    treev.addCallback(XmNitemExpandingCallback, this,
        (Callback)&FolderTreeDialog::expanding, NULL);

    treev.addCallback(XmNselChangingCallback, this,
      (Callback)&FolderTreeDialog::selChanging, NULL);

    ar.reset();
    ar.set(XmNid, IDOK);
    ok.create(this, _T(" OK "), ar);
    ok.setFont(&font);

    ar.reset();
    ar.set(XmNid, IDCANCEL);
    cancel.create(this, _T("Cancel"), ar);
    cancel.setFont(&font);
    cancel.addCallback(XmNactivateCallback, this,
      (Callback)&PopupView::popdown, NULL);
  
    addEventHandler(WM_SIZE, this,
      (Handler)&FolderTreeDialog::size, NULL);

    resize();

    return rc;
  }

public:
  int  getFolder(TCHAR* buffer, int len) 
  {
    int rc = 0;
    rc = textf.getText(buffer, len);
    return rc;
  }

public:
  void setFolder(const TCHAR* name)
  {
    textf.setText(name);
  }

public:
  void popup(Action& action)
  {
    if(initialized == FALSE) {
      capture();
      ::SetCursor(::LoadCursor(NULL, IDC_WAIT));
      treev.buildDirTree();
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
      ::ReleaseCapture();

      initialized = TRUE;
    }
    disableOwner();

    raise();
    show(SW_NORMAL);
  }

public:
  void addOkCallback(Object* object,
              Callback callback)
  {
    ok.addCallback(XmNactivateCallback, object,
        callback, NULL);
  }
};

}



