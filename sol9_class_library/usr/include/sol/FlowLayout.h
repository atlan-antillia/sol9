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
 *  FlowLayout.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\LayoutManager.h>
#include <sol\LinkedList.h>
#include <sol/View.h>

namespace SOL {

class View;
//class Panel;

class FlowLayout :public LayoutManager {
private:
  LinkedList list;
  int    direction;
  int    vgap;
  int    hgap;
  int    vspacing;
  int    hspacing;
  int    alignment;
public:
  // Direction

  static const int HORIZONTAL = 0;
  static const int VERTICAL   = 1;

  // Alignment
  static const int LEFT   = 0;
  static const int CENTER = 1;
  static const int RIGHT  = 2;

public:
  //2009/06/27
  FlowLayout(int dir=HORIZONTAL, int align = LEFT) 
    :list(False),
    direction(dir),
    vgap(4),
    hgap(4),
    vspacing(4),
    hspacing(4),
    alignment(align)
  {
  }

public:
  ~FlowLayout()
  {
  }

public:
  virtual void add(View* view) 
  {
    list.addLast(view);
  }

public:
  virtual void getExtension(Dimension& dim, int w, int h)
  {
    ListEntry* ptr = list.getEntry();
    int maxX = 0;
    int maxY = 0;
    int x = 0;
    int y = 0;
    int maxHeight = 0;

    if (alignment == LEFT) {
      x = hspacing;
      y = vspacing;
  
      while (ptr) {
        View* view = (View*)ptr -> getObject();
        Dimension d;
        view ->getPreferredSize(d);
        if (d.getHeight() > maxHeight) {
          maxHeight = d.getHeight();
        }

        if (direction == HORIZONTAL && (x+d.getWidth() >w )) {
          x = hspacing;
          y += maxHeight + vgap;
          maxHeight = 0;
        }
        //
        if (x + d.getWidth() > maxX) {
          maxX = x+d.getWidth();
        }
        if (y + d.getHeight() > maxY) {
          maxY = y+d.getHeight();
        }

        if (direction == HORIZONTAL) {
          x += d.getWidth() + hgap;
        } else {
          y += d.getHeight() + vgap;
        }
        ptr = ptr -> getNext();
      }
      maxX += hspacing;
      maxY += vspacing;
      dim.set(maxX, maxY);
    }
  
    if (alignment == CENTER && direction == HORIZONTAL) {
      y = vspacing;
      maxY = y;
      int tw = 0;
      ListEntry* sptr = ptr;
      int x1 = 0;
      while (ptr) {
        Dimension d;
        View* view = (View*)ptr -> getObject();
        view ->getPreferredSize(d);
        if ((tw + d.getWidth()) > w) {
          x1 = (w - (tw - hgap))/2;
          maxHeight = 0;
          ListEntry* end = ptr;
          if (ptr ->getNext() == NULL) end = NULL;
          while(sptr != end) {
            View* v = (View*)sptr ->getObject();
            Dimension s;
            v -> getPreferredSize(s);

            if (x1 + s.getWidth() > maxX) {
              maxX = x1 + s.getWidth();
            }
            x1 += s.getWidth() + hgap;
            if (s.getHeight() > maxHeight) {
              maxHeight = s.getHeight();
            }
            sptr = sptr -> getNext();
          }
          sptr = ptr;
          y += maxHeight + vgap;
          maxY = y;
          tw = d.getWidth() + hgap;
        }
        else {
          tw += d.getWidth() + hgap;
        }

        ptr = ptr -> getNext();
      }

      maxHeight = 0;
      while (sptr) {
        View* v = (View*)sptr ->getObject();
        Dimension s;
        v -> getPreferredSize(s);

        if (x1 + s.getWidth() > maxX) {
          maxX = x1 + s.getWidth();
        }
        x1 += s.getWidth() + hgap;

        if (s.getHeight() > maxHeight) {
          maxHeight = s.getHeight();
        }
        sptr = sptr -> getNext();
      }
      maxY += maxHeight + vgap;

      maxY -= vgap;
      maxX += hspacing;
      maxY += vspacing;
      dim.set(maxX, maxY);
    }
  }

public:
  virtual void layout(int x, int y, int w, int h) 
  {
    x = hspacing;
    y = vspacing;
  
    int maxHeight = 0;

    ListEntry* ptr = list.getEntry();
    if (alignment == LEFT) {
      x = hspacing;
      y = vspacing;
  
      int maxHeight = 0;
      while (ptr) {
        View* view = (View*)ptr -> getObject();
        Dimension d;
        view ->getPreferredSize(d);
        if (d.getHeight() > maxHeight) {
          maxHeight = d.getHeight();
        }

        if (direction == HORIZONTAL && (x+d.getWidth() >w )) {
          x = hspacing;
          y += maxHeight + vgap;
          maxHeight = 0;
        }
        view ->layout(x, y, d.getWidth(), d.getHeight());

        if (direction == HORIZONTAL) {
          x += d.getWidth() + hgap;
        } else {
          y += d.getHeight() + vgap;
        }
        ptr = ptr -> getNext();
      }
    }

    if (alignment == CENTER && direction == HORIZONTAL) {
      int tw = 0;
      ListEntry* sptr = ptr;
      int x1 = 0;
      while (ptr) {
        Dimension d;
        View* view = (View*)ptr -> getObject();
        view ->getPreferredSize(d);
        if ((tw + d.getWidth()) > w ) {
          x1 = (w - (tw - hgap))/2;
          maxHeight = 0;
          ListEntry* end = ptr;
          while(sptr != end) {
            View* v = (View*)sptr ->getObject();
            Dimension s;
            v -> getPreferredSize(s);
            v -> layout(x1, y, s.getWidth(), s.getHeight());
            x1 += s.getWidth() + hgap;
            if (s.getHeight() > maxHeight) {
              maxHeight = s.getHeight();
            }
            sptr = sptr -> getNext();
          }
          sptr = ptr;
          y += maxHeight + vgap;
          tw = d.getWidth() + hgap;
        }
        else {
          tw += d.getWidth() + hgap;
        }

        ptr = ptr -> getNext();
      }

      x1 = (w - (tw - hgap))/2;
      while (sptr) {
        View* v = (View*)sptr ->getObject();
        Dimension s;
        v -> getPreferredSize(s);
        v -> layout(x1, y, s.getWidth(), s.getHeight());
        x1 += s.getWidth() + hgap;
        sptr = sptr -> getNext();
      }
    }
  }

public:
  void  setAlignment(int align) { alignment = align; }
  
public:
  void  setVertSpacing(int v) { vspacing = v; }

public:
  void  setHorizSpacing(int v) { hspacing = v; }
  
public:
  void  setVertGap(int v) { vgap = v; }

public:
  void  setHorizGap(int v) { hgap = v; }
  
};

}


