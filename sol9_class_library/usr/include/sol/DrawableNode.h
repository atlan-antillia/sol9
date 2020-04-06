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
 *  DrawableNode.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Node.h>
#include <sol\DC.h>
#include <sol\StockObject.h>
#include <sol\Brush.h>


//enum {LINEAR,   ZIGZAG};

namespace SOL {

class DrawableNode :public Node {
private:
  int     px;
  int     py;
  BOOL    status;
  COLORREF  normalBackground;
  COLORREF  normalTextColor;
  COLORREF  activeBackground;
  COLORREF  activeTextColor;

private:

  void setDefaultColor()
  {
    normalBackground = ::GetSysColor(COLOR_BTNFACE);

    normalTextColor  = ::GetSysColor(COLOR_WINDOWTEXT);
    activeBackground = ::GetSysColor(COLOR_HIGHLIGHT);
    activeTextColor  = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
  }



public:
  static const int LINEAR = 0;
  static const int ZIGZAG = 1;


public:

  DrawableNode(const TCHAR* name, int id=0)
    :Node(name, id)
  {
    px = 0;
    py = 0;
    status = FALSE;
    setDefaultColor();
  }                       


public:
  DrawableNode(DrawableNode* parent, const TCHAR* name, int id=0)
  :Node(parent, name, id)
  {
    px = 0;
    py = 0;
    status = FALSE;
    setDefaultColor();
  }

public:
  DrawableNode(DrawableNode* parent, const TCHAR* name, 
               void* data, int id=0)
  :Node(parent, name, id)
  {
    px = 0;
    py = 0;
    setData(data);
    status = FALSE;
    setDefaultColor();
  }

public:
  void arrange(int width, int height, 
         int leftMargin, int topMargin)
  {
    px = (int)(getX() * (float)width ) + leftMargin;
    py = (int)(getY() * (float)height) + topMargin;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr != NULL) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      node -> arrange(width,  height, 
          leftMargin, topMargin);
      ptr = ptr -> getNext();
    }
  }

public:
  void arrange(DC* dc, int xposition, int height, 
         int leftMargin, int topMargin)
  {
    TCHAR* name = getName();
    SIZE size;
    dc -> getTextExtent(name, strlen(name), &size);

    int width   = size.cx + size.cy; 

    px = (xposition+leftMargin);
    py = (int)(getY() * (float)height) + topMargin;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();

    while(ptr) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      node -> arrange(dc, 
        px + width, 
        height, 
        leftMargin, topMargin);
      ptr = ptr -> getNext();
    }
  }

public:
  void drawSelf(DC* dc, int x, int y, SIZE* s)
  {
    TCHAR* name = getName();
    SIZE size;
    dc -> getTextExtent(name, strlen(name), &size);
    s->cx = size.cx;
    s->cy = size.cy;

    COLORREF backc = normalBackground;
    COLORREF textc = normalTextColor;
    if(status == TRUE) {
      backc = activeBackground;
      textc = activeTextColor;
    }

    HGDIOBJ hpen   = dc -> select(GetStockObject(BLACK_PEN));
    HGDIOBJ hbrush = dc -> select(GetStockObject(NULL_BRUSH));
    dc -> rectangle(x + px, y+py-2, x+px+size.cx+size.cy,
      y + py + size.cy + 2);
  
    Brush brush(backc);
    HGDIOBJ oldBrush= dc -> select(&brush);

    dc -> select(hpen);
    hpen = dc -> select(GetStockObject(NULL_PEN));

    dc -> rectangle(x + px, y+py-2, x+px+size.cx+size.cy,
      y + py + size.cy + 2);

    dc -> select(hpen);
    dc -> select(oldBrush);

    dc -> setBkMode(TRANSPARENT);
    dc -> setTextColor(textc);
    dc -> textOut(x + px+size.cy/2, y + py, name, strlen(name));
  }

public:
  void draw(DC* dc, DrawableNode* root, int policy, int x, int y)
  {
    SIZE size;
    drawSelf(dc, x, y, &size);
    int xext = size.cx;
    int yext = size.cy;

    if(this != root) {
      if(policy == ZIGZAG) {
        POINT pt; 
        dc -> getCurrentPosition(&pt);

        int xx = pt.x;  
        int yy = pt.y;

        dc -> lineTo(x+px - (x+px - xx)/2, yy);
        dc -> lineTo(x+px - (x+px - xx)/2, 
          y+ py + yext/2);
        dc -> lineTo(x+ px,
          y+ py + yext/2);
      }
      else {
        dc -> lineTo(x + px, y + py + yext/2);
      }
    }

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      dc -> moveTo(x + px + xext+yext,
                 y + py + yext/2, NULL);
      DrawableNode* node = (DrawableNode*) ptr -> getObject();
      node -> draw(dc, root, policy, x, y);
      ptr = ptr -> getNext();
    }
  }

public:
  void setBackground(COLORREF normal, COLORREF active)
  {
    normalBackground = normal;
    activeBackground = active;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      node -> setBackground(normal, active);
      ptr = ptr -> getNext();
    }
  }

public:
  void setTextColor(COLORREF normal, COLORREF active)
  {
    normalTextColor = normal;
    activeTextColor = active;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      node -> setTextColor(normal, active);
      ptr = ptr -> getNext();
    }
  }

public:
  void getExtent(DC* dc, int *maxx, int* maxy)
  {
    TCHAR* name = getName();

    SIZE size;
    dc -> getTextExtent(name, strlen(name), &size);

    int nx  = px + size.cx+size.cy; 
    int ny  = py + size.cy/2; 

    if(*maxx < nx) *maxx = nx;
    if(*maxy < ny) *maxy = ny;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      node -> getExtent(dc, maxx, maxy);
      ptr = ptr -> getNext();
    }
  }

public:
  int nodeMaxLength(DC* dc, int len)
  {
    int max = len;
    TCHAR* name = getName();

    SIZE size;
    dc -> getTextExtent(name, strlen(name), &size);
    int strLen  = size.cx;  
    if(strLen > max) max = strLen;

    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      DrawableNode* node = (DrawableNode*) ptr->getObject();
      max = node -> nodeMaxLength(dc, max);
      ptr = ptr -> getNext();
    }
    return max;
  }

public:
  DrawableNode* search(DC* dc, int x1, int y1)
  {
    TCHAR* name = getName();
    SIZE size;
    dc -> getTextExtent(name, strlen(name), &size);

    int nx  = px + size.cx+size.cy; 
    int ny  = py + size.cy;      
    if(x1 > px && x1 <nx &&
     y1 > py && y1 <ny ) {
      return this;
    }
    LinkedList* list = getChildren();
    ListEntry* ptr = list -> getEntry();
    while(ptr) {
      DrawableNode* node  = (DrawableNode*) ptr->getObject();
      DrawableNode* found = node -> search(dc, x1, y1);
      if(found) {
        return found;
      }
      ptr = ptr -> getNext();
    }
    return NULL;
  }



  BOOL    getStatus() { 
    return status; 
  }


  DrawableNode*   search(TCHAR* name) {
      return (DrawableNode*)Node::search(name);
  }

  DrawableNode*   search(int id) {
      return (DrawableNode*)Node::search(id);
  }

            
  void  setStatus(BOOL flag) { 
    status = flag; 
  }
};

}

