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
 *  PropertyView.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/07
// 2009/11/24 Modified to use ImageList and show icon on the first item.
// 2012/06/25

#pragma once
#include <sol\ListView.h>
#include <sol\ImageList.h>

namespace SOL {

/**
 * PropertyView class to display a list of name-value pais.
 */
class PropertyView :public ListView {

private:
  ImageList imageList;
private:
  int iconIndex; 

public:
  PropertyView() 
  {
    iconIndex = -1;
  }

public:
  //2012/06/25
  PropertyView(View* parent, const TCHAR* name, Args& args)
    :ListView()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args) {
    Boolean rc = ListView::create(parent, name,   
        args.set(XmNstyle,  (LONG_PTR)LVS_REPORT));

    ListViewColumn items[] = {
      {_T("Name"),   LVCFMT_LEFT, 200},
      {_T("Value"),   LVCFMT_LEFT, 400},
    };

    setColumn(items, sizeof(items)/sizeof(items[0]));

    setExtendedViewStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); 
    
    iconIndex = -1;
    imageList.create(16, 16, ILC_COLOR32|ILC_MASK, 5, 1);

    return rc;
  }

public:
  // 2009/11/24
  void addIcon(int iconId) {
    HICON hIcon= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(iconId));
    if (hIcon) {
      iconIndex = imageList.addIcon(hIcon);
      setSmallImageList(&imageList);
    }
  }

public:
  /**
   * 
   */
  // 2009/04/07
  int addFirst(const TCHAR* name, const TCHAR* value) {
    int rc = -1;
    const TCHAR* val = value;
    if (val == NULL) {
      val = _T("(NULL)");
    }
    if (name && val) {  
      const TCHAR* items[2];

      items[0] = name;
      items[1] = val;
      int id = 0;

      insertLine(id, items, 2);
      rc = NO_ERROR;
    }
    return rc;
  }

public:
  int addFirst(const String& name, const String& value) {
    int rc = -1;
    const TCHAR* items[2];

    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)value;
    int id = 0;
    
    insertLine(id, items, 2);
    rc = NO_ERROR;
    return rc;
  }

public:
  /**
   * 
   */
  // 2009/04/06
  int addLast(const TCHAR* name, const TCHAR* value) {
    int rc = -1;
    const TCHAR* val = value;
    if (val == NULL) {
      val = _T("(NULL)");
    }
    if (name && val) {  
      const TCHAR* items[2];

      items[0] = name;
      items[1] = val;
      int id = getItemCount();
      if (iconIndex>0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
      } else {
        insertLine(++id, items, 2);
      }
      rc = NO_ERROR;
    }
    return rc;
  }

public:
  /**
   * 
   */
  // 2009/11/
  int addLast(const String& name, const String& value) {
    int rc = -1;
    const TCHAR* items[2];

    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)value;
    int id = getItemCount();
    if (iconIndex>0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
    } else {
      insertLine(++id, items, 2);
    }
    rc = NO_ERROR;
    return rc;
  }

public:
  int addLast(const String& name, DWORD value) {
    int rc = -1;
    const TCHAR* items[2];
    TCHAR v[128];
    _stprintf_s(v, CountOf(v), _T("%d"), value);
    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)v;
    int id = getItemCount();
    if (iconIndex> 0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
    } else {
      insertLine(++id, items, 2);
    }

    rc = NO_ERROR;
    return rc;
  }

public:
  int addLast(const TCHAR* name, DWORD value) {
    int rc = -1;
    const TCHAR* items[2];
    TCHAR v[128];
    _stprintf_s(v, CountOf(v), _T("%d"), value);
    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)v;
    int id = getItemCount();
    if (iconIndex> 0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
    } else {
      insertLine(++id, items, 2);
    }

    rc = NO_ERROR;
    return rc;
  }

public:
  int addLast(const TCHAR* name, long value) {
    int rc = -1;
    const TCHAR* items[2];
    TCHAR v[128];
    _stprintf_s(v, CountOf(v), _T("%d"), value);
    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)v;
    int id = getItemCount();
    if (iconIndex> 0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
    } else {
      insertLine(++id, items, 2);
    }

    rc = NO_ERROR;
    return rc;
  }

public:
  int addLast(const TCHAR* name, double value) {
    int rc = -1;
    const TCHAR* items[2];
    TCHAR v[128];
    _stprintf_s(v, CountOf(v), _T("%f"), value);
    items[0] = (const TCHAR*)name;
    items[1] = (const TCHAR*)v;
    int id = getItemCount();
    if (iconIndex> 0) {
        insertLineWithIcon(++id, items, 2, iconIndex);
    } else {
      insertLine(++id, items, 2);
    }

    rc = NO_ERROR;
    return rc;
  }

};

}
