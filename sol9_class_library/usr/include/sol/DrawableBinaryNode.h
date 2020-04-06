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
 *  DrawableBinaryNode.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\BinaryNode.h>
#include <sol\DC.h>
#include <sol\StockObject.h>
#include <sol\Brush.h>


namespace SOL {

class DrawableBinaryNode :public BinaryNode {
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
  DrawableBinaryNode(DrawableBinaryNode* parent, 
      const TCHAR* name, Object* object=NULL)
      :BinaryNode(parent, name, object)
  {
    px = 0;
    py = 0;
    status = FALSE;
    setDefaultColor();

  }

public:

  DrawableBinaryNode(DrawableBinaryNode* parent, const TCHAR*  name, 
      DrawableBinaryNode* left,
      DrawableBinaryNode* right)
  :BinaryNode(parent, name, left, right)
  {
    px = 0;
    py = 0;
    status = FALSE;
    setDefaultColor();
  }

public:

  void arrange(int width, int height, 
         int leftMargin, int topMargin)
  {
    px = (int)(getX() * (float)width ) + leftMargin;
    py = (int)(getY() * (float)height) + topMargin;

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> arrange(width, height, leftMargin, topMargin);
    }
    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> arrange(width, height, leftMargin, topMargin);
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

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> arrange(dc, px + width, height, leftMargin, topMargin);
    }
    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> arrange(dc, px + width, height, leftMargin, topMargin);
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
  void draw(DC* dc, DrawableBinaryNode* root, int policy, int x, int y)
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

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      dc -> moveTo(x + px + xext+yext,
                 y + py + yext/2, NULL);

      left -> draw(dc, root, policy, x, y);
    }
    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      dc -> moveTo(x + px + xext+yext,
                 y + py + yext/2, NULL);

      right -> draw(dc, root, policy, x, y);
    }
  }

public:
  void setBackground(COLORREF normal, COLORREF active)
  {
    normalBackground = normal;
    activeBackground = active;

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> setBackground(normal, active);
    }

    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> setBackground(normal, active);

    }
  }

public:
  void setTextColor(COLORREF normal, COLORREF active)
  {
    normalTextColor = normal;
    activeTextColor = active;

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> setTextColor(normal, active);
    }

    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> setTextColor(normal, active);
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

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> getExtent(dc, maxx, maxy);
    }

    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> getExtent(dc, maxx, maxy);
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

    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      left -> nodeMaxLength(dc, max);
    }

    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      right -> nodeMaxLength(dc, max);
    }
  
    return max;
  }

public:
  DrawableBinaryNode* search(DC* dc, int x1, int y1)
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
    DrawableBinaryNode* found = NULL;
    DrawableBinaryNode* left = (DrawableBinaryNode*)getLeft();
    if (left) {
      found = left -> search(dc, x1, y1);
      if (found) {
        return found;
      }
    }

    DrawableBinaryNode* right = (DrawableBinaryNode*)getRight();
    if (right) {
      found = right -> search(dc, x1, y1);
      if (found) {
        return found;
      }
    }
    return NULL;
  }


  BOOL    getStatus() { 
    return status; 
  }

  //2009/10/10 Added the const.
  DrawableBinaryNode*   search(const TCHAR* name) {

      return (DrawableBinaryNode*)BinaryNode::search(name);
  }

  DrawableBinaryNode*   search(int id) {
      return (DrawableBinaryNode*)BinaryNode::search(id);
  }


  void  setStatus(BOOL flag) { 
    status = flag; 
  }
};

}

