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
 *  TreeView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2008/07/28
// 2008/08/04
// 2008/12/12 Added some methods to take a wchar_t* text parameter.
// 2009/08/11 Added the following method.
//  HTREEITEM addItem(HTREEITEM parent, HTREEITEM after, char* text, long lParam, 
//              int imageId, int selImageId)

// 2009/06/25
// 2009/09/15 Added a getItemByLong method.
// 2009/09/22 Added a getItemText method.
// 2012/06/25

#pragma once

#include <sol\Primitive.h>
#include <sol\ImageList.h>
#include <sol\TreeItem.h>

namespace SOL {

class TreeView :public Primitive {

public:
  TreeView():Primitive()  { }

public:
  //2012/06/25
  TreeView(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }


public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name,   
      args.set(XmNstyle, (LONG_PTR)(WS_TABSTOP|WS_BORDER))
          .set(XmNpredefined, TRUE)
          .set(XmNclassName, (LONG_PTR)WC_TREEVIEW));

    setValues(args);  
    return rc;
  }

public:
  Arg* getCallbackTable(int* num)
  {
    static Arg table[] = {
  
    {XmNselChangingCallback,  TVN_SELCHANGING},
    {XmNselChangedCallback,    TVN_SELCHANGED},
     {XmNgetDispInfoCallback,  TVN_GETDISPINFO},
    {XmNsetDispInfoCallback,  TVN_SETDISPINFO},
    {XmNitemExpandingCallback,  TVN_ITEMEXPANDING},
    {XmNitemExpandedCallback,  TVN_ITEMEXPANDED},

    {XmNbeginDragCallback,    TVN_BEGINDRAG},
    {XmNbeginRDragCallback,    TVN_BEGINRDRAG},
    {XmNdeleteItemCallback,    TVN_DELETEITEM},
     {XmNbeginLabelEditCallback, TVN_BEGINLABELEDIT},
    {XmNendLabelEditCallback,  TVN_ENDLABELEDIT},
    {XmNkeyDownCallback,    TVN_KEYDOWN},
    };

    *num = XtNumber(table);
    return table; 
  }

public:
  HTREEITEM addItem(HTREEITEM parent, HTREEITEM after, TreeItem* treeItem)
  {
    return addItem(parent, after, treeItem->text, 
        treeItem->imageId, treeItem->selImageId);
  }
  
public:
  HTREEITEM addItem(HTREEITEM parent, HTREEITEM after, TCHAR* text)
  {
    TV_ITEM item;
    TV_INSERTSTRUCT insertStruct;
    memset(&item, 0, sizeof(TV_ITEM));
    memset(&insertStruct, 0, sizeof(TV_INSERTSTRUCT));
    item.mask = TVIF_TEXT;
    item.pszText = text;
    insertStruct.item = item;
    insertStruct.hInsertAfter = after;
    insertStruct.hParent = parent;
    return insertItem(&insertStruct);
  }

public:
  HTREEITEM addItem(HTREEITEM parent, HTREEITEM after, TCHAR* text, 
              int imageId, int selImageId)
  {
    TV_ITEM item;
    memset(&item, 0, sizeof(TV_ITEM));
    item.mask       = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
    item.pszText    = text;
    item.cchTextMax = strlen(text);
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;

    TV_INSERTSTRUCT insertStruct;
    memset(&insertStruct, 0, sizeof(TV_INSERTSTRUCT));
    insertStruct.item = item;
    insertStruct.hInsertAfter = after;
    insertStruct.hParent = parent;
    return insertItem(&insertStruct);
  }

public:
  //2009/08/11
  HTREEITEM addItem(HTREEITEM parent, HTREEITEM after, TCHAR* text, long lParam, 
              int imageId, int selImageId)
  {
    TV_ITEM item;
    memset(&item, 0, sizeof(TV_ITEM));
    item.mask       = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
    item.pszText    = text;
    item.cchTextMax = strlen(text);
    item.lParam     = lParam;
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;

    TV_INSERTSTRUCT insertStruct;
    memset(&insertStruct, 0, sizeof(TV_INSERTSTRUCT));
    insertStruct.item = item;
    insertStruct.hInsertAfter = after;
    insertStruct.hParent = parent;
    return insertItem(&insertStruct);
  }

public:
  void expandChildren(HTREEITEM hItem, int flag)
  {  
    if(hItem) {
      expand(hItem, flag);

      HTREEITEM child = getChild(hItem);
      while(child) {
        HTREEITEM sibling = getNextSibling(child);    
        expandChildren(child, flag);
        child = sibling;
      }
    }
  }

public:
  void sortAllChildren(HTREEITEM hItem)
  {
    if(hItem) {
      sortChildren(hItem, 0);

      HTREEITEM child = getChild(hItem);
      while(child) {
        HTREEITEM sibling = getNextSibling(child);    
        sortAllChildren(child);
        child = sibling;
      }
    }
  }


  HTREEITEM insertItem(TV_INSERTSTRUCT* lpis) {
        return (HTREEITEM)send(TVM_INSERTITEM, 0, (LPARAM)lpis);
  }

#ifndef UNICODE
  HTREEITEM insertItem(TV_INSERTSTRUCTW* lpis) {
        return (HTREEITEM)send(TVM_INSERTITEMW, 0, (LPARAM)lpis);
  }
#endif

  BOOL  deleteItem(HTREEITEM hitem) {
        return (BOOL)send(TVM_DELETEITEM, 0, (LPARAM)hitem);
  }

  BOOL   deleteAllItems() {
        return (BOOL)send(TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
  }

  BOOL   expand(HTREEITEM hitem, int code) {
        return (BOOL)send(TVM_EXPAND, (WPARAM)code, (LPARAM)hitem);
  }

  void   getItemRect(HTREEITEM hitem, RECT* prc, BOOL flag) {
        send(TVM_GETITEMRECT, (WPARAM)flag, (LPARAM)prc);
  }

  int    getCount() {
        return (UINT)send(TVM_GETCOUNT, 0, 0);
  }

  int   getIndent() {
        return (UINT)send(TVM_GETINDENT, 0, 0);
  }

  BOOL   setIndent(int indent) {
        return (BOOL)send(TVM_SETINDENT, (WPARAM)indent, 0);
  }

  HIMAGELIST getImageList(int iImage) {
      return (HIMAGELIST)send(TVM_GETIMAGELIST, iImage, 0);
  }

  //2009/11/01
  //iImage is TVSIL_NORMAL or TVSIL_STATE 
  HIMAGELIST setImageList(HIMAGELIST himl, int iImage=TVSIL_NORMAL ) {
        return (HIMAGELIST)send(TVM_SETIMAGELIST, iImage, (LPARAM)himl);
  }

  HIMAGELIST setImageList(ImageList* iml, int iImage=TVSIL_NORMAL) {
        return (HIMAGELIST)send(TVM_SETIMAGELIST, iImage, (LPARAM)iml->getImageList());
  }

  HIMAGELIST setNormalImageList(HIMAGELIST himl) {
        return (HIMAGELIST)send(TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)himl);
  }

  HIMAGELIST setNormalImageList(ImageList* iml) {
        return (HIMAGELIST)send(TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)iml->getImageList());
  }
  //

  HTREEITEM getNextItem(HTREEITEM hitem, int code) {
        return (HTREEITEM)send(TVM_GETNEXTITEM, (WPARAM)code, (LPARAM)hitem);
  }
  HTREEITEM getChild(HTREEITEM hitem) {
      return  getNextItem(hitem, TVGN_CHILD);
  }

  HTREEITEM getNextSibling(HTREEITEM hitem) { 
      return  getNextItem(hitem, TVGN_NEXT);
  }

  HTREEITEM getPrevSibling(HTREEITEM hitem)  {
      return getNextItem(hitem, TVGN_PREVIOUS);
  }

  HTREEITEM getParent(HTREEITEM hitem) {
      return  getNextItem(hitem, TVGN_PARENT);
  }

  HTREEITEM getFirstVisible() {
      return  getNextItem(NULL,  TVGN_FIRSTVISIBLE);
  }
  HTREEITEM getNextVisible(HTREEITEM hitem) {  
      return getNextItem(hitem, TVGN_NEXTVISIBLE);
  }

  HTREEITEM getPrevVisible(HTREEITEM hitem) {
      return getNextItem(hitem, TVGN_PREVIOUSVISIBLE);
  }
  HTREEITEM getSelection() {
      return  getNextItem(NULL,  TVGN_CARET);
  }
  HTREEITEM getDropHilight() {
      return getNextItem(NULL,  TVGN_DROPHILITE);
  }
  HTREEITEM getRoot() {
      return getNextItem(NULL,  TVGN_ROOT);
  }

  HTREEITEM select(HTREEITEM hitem, int code) {
        return (HTREEITEM)send(TVM_SELECTITEM, (WPARAM)code, (LPARAM)hitem);
  }

  HTREEITEM selectItem(HTREEITEM hitem) {
      return  select(hitem, TVGN_CARET);
  }

  HTREEITEM selectDropTarget(HTREEITEM hitem) {
      return  select(hitem, TVGN_DROPHILITE);
  }

  HTREEITEM selectSetFirstVisible(HTREEITEM hitem) {
      return select(hitem, TVGN_FIRSTVISIBLE);
  }

  BOOL   getItem(TV_ITEM* pitem) {
        return (BOOL)send(TVM_GETITEM, 0, (LPARAM)(TV_ITEM FAR*)(pitem));
  }
  
  //2008/12/12
#ifndef UNICODE
  BOOL   getItem(TV_ITEMW* pitem) {
    
        return (BOOL)send(TVM_GETITEMW, 0, (LPARAM)(TV_ITEM FAR*)(pitem));
  }
#endif
  BOOL   setItem(TV_ITEM* pitem) {
        return (BOOL)send(TVM_SETITEM, 0, (LPARAM)(const TV_ITEM FAR*)(pitem));
  }
  //2008/12/12
#ifndef UNICODE
  BOOL   setItem(TV_ITEMW* pitem) {
        return (BOOL)send(TVM_SETITEMW, 0, (LPARAM)(const TV_ITEMW FAR*)(pitem));
  }

#endif
  HWND   editLabel(HTREEITEM hitem) {
        return (HWND)send(TVM_EDITLABEL, 0, (LPARAM)hitem);
  }

  HWND  getEditControl() {
        return (HWND)send(TVM_GETEDITCONTROL, 0, 0);
  }

  int   getVisibleCount() {
        return (UINT)send(TVM_GETVISIBLECOUNT, 0, 0);
  }

  HTREEITEM hitTest(TV_HITTESTINFO* lpht) {
        return (HTREEITEM)send(TVM_HITTEST, 0, (LPARAM)lpht);
  }

  HIMAGELIST createDragImage(HTREEITEM hitem) {
        return (HIMAGELIST)send(TVM_CREATEDRAGIMAGE, 0, (LPARAM)hitem);
  }

  BOOL   sortChildren(HTREEITEM hitem, int recurse) {
        return (BOOL)send(TVM_SORTCHILDREN, (WPARAM)recurse, (LPARAM)hitem);
  }

  BOOL   ensureVisible(HTREEITEM hitem) {
        return (BOOL)send(TVM_ENSUREVISIBLE, 0, (LPARAM)(HTREEITEM)(hitem));
  }

  BOOL   sortChildrenCB(TV_SORTCB* psort, int recurse) {
        return (BOOL)send(TVM_SORTCHILDRENCB, (WPARAM)recurse, (LPARAM)psort);
  }

  BOOL   endEditLabelNow(int fCancel) {
        return (BOOL)send(TVM_ENDEDITLABELNOW, (WPARAM)fCancel, 0);
  }

  BOOL   getISearchString(TCHAR* lpsz) {
      return (BOOL)send(TVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz);
  }

//  void    expandChildren(HTREEITEM hItem, int flag);

//  void    sortAllChildren(HTREEITEM hItem);

  //
  //2008/07/28 Add an item of text to TVI_ROOT
  //2008/08/04 Added lParam=0 
  /*
  HTREEITEM addItem(TCHAR* text, long lParam=0) {
    TV_ITEM item;
    TV_INSERTSTRUCT insertStruct;
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));

    item.mask = TVIF_TEXT|TVIF_PARAM;
    item.pszText = text;
    item.lParam  = lParam; 

    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_ROOT;

    insertStruct.hParent = NULL;
    return insertItem(&insertStruct);
  }
  

  HTREEITEM addItem(wchar_t* text, long lParam=0) {
    TV_ITEMW item;
    TV_INSERTSTRUCTW insertStruct;
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));

    item.mask = TVIF_TEXT|TVIF_PARAM;
    item.pszText = text;
    item.lParam  = lParam; 

    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_ROOT;

    insertStruct.hParent = NULL;
    return insertItem(&insertStruct);
  }
  */

  //2008/12/12 Add an item of text to TVI_ROOT
  HTREEITEM addItem(TCHAR* text, long lParam=0, int imageId =0, int selImageId =0) {
    TV_ITEM item;
    TV_INSERTSTRUCT insertStruct;
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));
    item.mask = TVIF_TEXT|TVIF_PARAM;
    if (imageId >0) {    
      item.mask |= TVIF_IMAGE;
    }

    if (selImageId >0) {    
      item.mask |= TVIF_SELECTEDIMAGE;
    }
    item.pszText = text;
    item.lParam  = lParam; 
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;

    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_ROOT;

    insertStruct.hParent = NULL;
    return insertItem(&insertStruct);
  }

  //2008/12/12 Add an item of text to TVI_ROOT
#ifndef UNICODE
  HTREEITEM addItem(wchar_t* text, long lParam=0, int imageId =0, int selImageId =0) {
    TV_ITEMW item;
    TV_INSERTSTRUCTW insertStruct;
    
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));
    item.mask = TVIF_TEXT|TVIF_PARAM;
    if (imageId >0) {    
      item.mask |= TVIF_IMAGE;
    }

    if (selImageId >0) {    
      item.mask |= TVIF_SELECTEDIMAGE;
    }
    item.pszText = text;
    item.lParam  = lParam; 
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;
    
    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_ROOT;

    insertStruct.hParent = NULL;
    return insertItem(&insertStruct);
  }
#endif

  //2008/07/28 Add last an item of text to parent.
  //2008/08/04 Added lParam.
  HTREEITEM addItem(HTREEITEM parent, TCHAR* text, long lParam =0,
      int imageId =0, int selImageId =0) 
  {
    if (text == NULL) {
      text = _T("");
    }

    TV_ITEM item;
    TV_INSERTSTRUCT insertStruct;
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));


    //2008/08/01 TVIF_PARAM
    item.mask = TVIF_TEXT|TVIF_PARAM;
    item.pszText = text;
    item.lParam  = lParam;
    if (imageId >0) {    
      item.mask |= TVIF_IMAGE;
    }

    if (selImageId >0) {    
      item.mask |= TVIF_SELECTEDIMAGE;
    }
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;

    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_LAST;
    insertStruct.hParent = parent;
    return insertItem(&insertStruct);
  }

#ifndef UNICODE
  HTREEITEM addItem(HTREEITEM parent, wchar_t* text, long lParam =0,
          int imageId =0, int selImageId =0) 
  {
    //2009/09/29
    if (text == NULL) {
      text = L"";
    }

    TV_ITEMW item;
    TV_INSERTSTRUCTW insertStruct;
    memset(&item, 0, sizeof(item));
    memset(&insertStruct, 0, sizeof(insertStruct));

    item.mask = TVIF_TEXT|TVIF_PARAM;
    item.pszText = text;
    item.lParam  = lParam;
    if (imageId >0) {    
      item.mask |= TVIF_IMAGE;
    }

    if (selImageId >0) {    
      item.mask |= TVIF_SELECTEDIMAGE;
    }
    item.iImage     = imageId;
    item.iSelectedImage = selImageId;

    insertStruct.item = item;
    insertStruct.hInsertAfter = TVI_LAST;
    insertStruct.hParent = parent;
    return insertItem(&insertStruct);
  }
#endif

  //2008/07/28 Expand all children recursively from ROOT to LEAF.
  void  expandAllChildren() {
    expandChildren(TVI_ROOT, TVE_EXPAND);
  }

  //2008/07/28 Close all children recursively from ROOT to LEAF.
  void  collapseAllChildren() {
    expandChildren(TVI_ROOT, TVE_COLLAPSE);
  }

  //2008/08/04
  void   clear() {
        send(TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
  }

public:
  /** Get a HTREEITEM's  array from the root node to the selected node(selItem).
   *
   * This will return an array(items) of HTREEITEM.
   * You should call delete [] items after use;
   */
  HTREEITEM* getItemsListFromRoot(__out HTREEITEM selItem, __out int& count)
  {
    int c = 0;
    HTREEITEM citem = selItem;
    while (citem) {
      c++;
      citem = getParent(citem);
    }
    if (c==0) {
      count = 0;  //2009/09/29
      return NULL;    
    }

    count = c;

    HTREEITEM* items = new HTREEITEM[count];
    HTREEITEM item = selItem;
    while (c--) {
      items[c] = item;
      item = getParent(item);
      if (item == NULL) {
        break;
      }
    }
    return items;
  }

public:
  /**
   * Find an item of HTREEITEM from a tree node of hItem by lParam of member of TV_ITEM structure.
   */
  HTREEITEM getItemByLong(HTREEITEM hItem, LONG lParam)
  {
    HWND hWnd = getWindow();

    if (hItem == NULL) {
      hItem = (HTREEITEM)send(TVM_GETNEXTITEM,TVGN_ROOT, 0);
    }

    while (hItem != NULL) {
        
      TV_ITEM item;
      memset(&item, 0, sizeof(item));
      item.hItem = hItem;
    
      item.mask = TVIF_PARAM | TVIF_CHILDREN;

      send(TVM_GETITEM, 0, (LPARAM)&item);
    
      //OK. noed item.lParam and lParam mached, we found an item 
      if (item.lParam == lParam) {
        return hItem;
      }

        
      if (item.cChildren){
        // Recursively traverse child items.
        HTREEITEM hItemFound, hItemChild;

        hItemChild = (HTREEITEM)send(TVM_GETNEXTITEM,
                                                TVGN_CHILD, (LPARAM)hItem);

        hItemFound = getItemByLong(hItemChild, lParam);

        if (hItemFound != NULL) {
          return hItemFound;
        }
      }

      // Go to next sibling item.
      hItem = (HTREEITEM)send(TVM_GETNEXTITEM,
                                       TVGN_NEXT, (LPARAM)hItem);
    }

    return NULL;
  }

public:
  //2009/09/22

  bool getItemText(__in HTREEITEM hItem, __out String& string, __out LONG& param)
  {
    bool rc = false;
    TV_ITEM tvItem;
    memset(&tvItem, 0, sizeof(tvItem));
    TCHAR text[1024];
    memset(text, (TCHAR)0, CountOf(text));
    tvItem.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_TEXT;
    tvItem.hItem = hItem;
    tvItem.pszText = text;
    tvItem.cchTextMax = CountOf(text)-1;

    if (getItem(&tvItem)) {
      string = text;
      param = tvItem.lParam;
      rc = true;
    }
    
    return rc;
  }

public:
  //2009/12/24

  bool getItemText(__in HTREEITEM hItem, __out StringT<wchar_t>& string, __out LONG& param)
  {
    bool rc = false;
    TV_ITEMW tvItem;
    memset(&tvItem, 0, sizeof(tvItem));
    wchar_t text[1024];
    memset(text, (wchar_t)0, CountOf(text));
    tvItem.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_TEXT;
    tvItem.hItem = hItem;
    tvItem.pszText = text;
    tvItem.cchTextMax = CountOf(text)-1;

    if (getItem(&tvItem)) {
      string = text;
      param = tvItem.lParam;
      rc = true;
    }
    
    return rc;
  }

public:
  //2011/12/15
  bool getItemText(__in HTREEITEM hItem, __out _bstr_t& string, __out LONG& param)
  {
    bool rc = false;
    TV_ITEMW tvItem;
    memset(&tvItem, 0, sizeof(tvItem));
    wchar_t text[1024];
    memset(text, (wchar_t)0, CountOf(text));
    tvItem.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_TEXT;
    tvItem.hItem = hItem;
    tvItem.pszText = text;
    tvItem.cchTextMax = CountOf(text)-1;

    if (getItem(&tvItem)) {
      string = text;
      param = tvItem.lParam;
      rc = true;
    }
    
    return rc;
  }

public:
  HTREEITEM findDirectChildItem(HTREEITEM hItem, LONG lParam)
  {
    HTREEITEM hFound = NULL;
    if (hItem) {
        //Get a child item(direct child tree node).
        HTREEITEM child = getChild(hItem);
        while (child) {
          LONG id;
          String text = _T("");
          if (getItemText(child, text, id)) {
            //If a TV_ITEM.lParam of the child item matched with lParam 
            if (id == lParam) {
              //OK, we found an item
              hFound = child;
              break;
            }
          }
          // Get a next sibling item(tree node)
          child = getNextSibling(child);
        }
    }
    return hFound;
  }

public:
  HTREEITEM findDirectChildItem(HTREEITEM hItem, const TCHAR* name)
  {
    HTREEITEM hFound = NULL;
    if (hItem) {
        //Get a child item(direct child tree node).
        HTREEITEM child = getChild(hItem);
        while (child) {
          LONG id;
          String text="";
          
          if (getItemText(child, text, id)) {

            if (text.equals(name)) {
              //OK, we found an item
              hFound = child;
              break;
            }
          }
          // Get a next sibling item(tree node)
          child = getNextSibling(child);
        }
    }
    return hFound;
  }

public:
  //2011/12/13
  bool isLeafNode(HTREEITEM hItem)
  {
    TV_ITEM tvItem;
    memset(&tvItem, 0, sizeof(tvItem));
    tvItem.hItem = hItem; 
    
    tvItem.mask = TVIF_CHILDREN;

    send(TVM_GETITEM, 0, (LPARAM)&tvItem);

    bool isLeaf = true;
    if (tvItem.cChildren>0) {
      //This node has children
      isLeaf = false;
    }
    return isLeaf;
  }

public:
  //2011/12/13
  bool getParentItem(HTREEITEM hItem, TV_ITEM& parentItem)
  {
    bool rc = false;
    HTREEITEM hParentItem =getParent(hItem);
    if (hParentItem) {
      //TV_ITEM parentItem;
      memset(&parentItem, 0, sizeof(parentItem));
      parentItem.hItem = hParentItem;
    
      parentItem.mask = TVIF_PARAM;

      send(TVM_GETITEM, 0, (LPARAM)&parentItem);
      rc = true;  
    }
    return rc;
  }    


};

}

