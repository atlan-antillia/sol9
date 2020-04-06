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
 *  GenericTreeView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\Composite.h>
#include <sol\DC.h>
#include <sol\DrawableTree.h>
#include <sol\ClientDC.h>
#include <sol\PaintDC.h>
#include <sol\stdio.h>


namespace SOL {

class GenericTreeView :public Composite {
private:

  int      range;
  DrawableTree* tree;
  
protected:

  long  paint(Event& event)
  {
    PaintDC pdc(this);
    int x = getScrollPos(SB_HORZ);
    int y = getScrollPos(SB_VERT);

    if(tree) {
      HFONT hfont = NULL;
      Font* font = getDefaultFont();
      if (font) {
        hfont = pdc.select(font); 
      }
      tree -> draw(&pdc, -x, -y);
      if(range == FALSE) {
        setTreeScrollRange(&pdc);
      }
      if (hfont) {
        pdc.select(hfont);
      }

    }
    return NULL;
  }


  long  leftButtonDown(Event& event)
  {
    int  x, y;
    event.getMousePosition(x, y);
    DrawableNode* node = search(x, y);
    if(node) {
      int mx = getScrollPos(SB_HORZ);
      int my = getScrollPos(SB_VERT);
      ClientDC cdc(this);
      tree -> setActiveNode(node, &cdc, mx, my);

      callCallback(XmNbrowseSelectionCallback,
        (Key)getWindow(), node, event);
    }
    return NULL;
  }


  long  leftButtonDoubleClick(Event& event)
  {
    int  x, y;
    event.getMousePosition(x, y);
    DrawableNode* node = search(x, y);
    if(node) {
      int mx = getScrollPos(SB_HORZ);
      int my = getScrollPos(SB_VERT);
      ClientDC cdc(this);
      tree -> setActiveNode(node, &cdc, mx, my);

      callCallback(XmNdefaultActionCallback, 
        (Key)getWindow(), node, event);
    }
    return NULL;
  }

  void  setTreeScrollRange(DC* dev)
  {
    DrawableNode* root = (DrawableNode*) tree->getRoot();

    int maxx = 0;
    int maxy = 0;
    root -> getExtent(dev, &maxx, &maxy);
    maxx = maxx + tree->getLeftMargin();
    maxy = maxy + tree->getTopMargin() ;
    setScrollRange(SB_HORZ, 0, maxx);
    setScrollRange(SB_VERT, 0, maxy);

    setScrollExtent(maxx, maxy);

    range = TRUE;
  }


  long  size(Event& event) { return 0L; }

public:
  GenericTreeView(): Composite() { }

public:
  //2012/06/22
  GenericTreeView(View* parent, const char* caption, Args& args)
  :Composite()
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(View* parent, const char* caption, Args& args)
  {
    tree  = NULL;
    range = FALSE;

    Boolean rc = Composite::create(parent, caption,
      args.set(XmNexStyle, (LONG_PTR)(WS_EX_CLIENTEDGE))
            .set(XmNstyle, (LONG_PTR)(WS_VISIBLE|WS_HSCROLL|WS_VSCROLL)) );

    addEventHandler(WM_PAINT, this,
      (Handler)&GenericTreeView::paint, NULL);
    addEventHandler(WM_LBUTTONDOWN, this,
      (Handler)&GenericTreeView::leftButtonDown, NULL);
    addEventHandler(WM_LBUTTONDBLCLK, this,
      (Handler)&GenericTreeView::leftButtonDoubleClick, NULL);

    return rc;
  }


public:
  void setTree(DrawableTree* tree1)
  {
    if(tree) delete tree;
    tree  = tree1;
    range = FALSE;

    setScrollPos(SB_HORZ, 0);
    setScrollPos(SB_VERT, 0);
  }


public:
  ~GenericTreeView()
  {
    if(tree) delete tree;
  }


public:
  void addCallback(const char* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }


public:
  DrawableNode* search(int x, int y)
  {
    int x1 = getScrollPos(SB_HORZ);
    int y1 = getScrollPos(SB_VERT);
    DrawableNode* node = NULL;
    if(tree) {
      ClientDC cdc(this);
      node = tree->search(&cdc, x+x1, y+y1);
    }
    return node;
  }

public:
  DrawableTree* getTree() { 
    return tree; 
  }
};

}


