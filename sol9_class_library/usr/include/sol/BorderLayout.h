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
 *  BorderLayout.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\LayoutManager.h>
#include <sol/View.h>

namespace SOL {

class BorderLayout :public LayoutManager {
private:
  View*  north;
  View*  south;
  View*  east;
  View*  west;
  View*  center;
 
public:

  static const int NORTH = 0;
  static const int SOUTH = 1;
  static const int EAST  = 2;
  static const int WEST  = 3;
  static const int CENTER = 4;

public:
  BorderLayout::BorderLayout() 
  :north(NULL),
  south(NULL),
  east(NULL),
  west(NULL),
  center(NULL)
  {
  }

public:
  ~BorderLayout()
  {
  }

public:
  virtual void BorderLayout::add(View* view, int pos) 
  {
    if (pos == NORTH) north = view;
    if (pos == SOUTH) south = view;
    if (pos == EAST) east = view;
    if (pos == WEST) west = view;
    if (pos == CENTER) center = view;

  }

public:
  virtual void BorderLayout::layout(int x, int y, int w, int h) 
  {
    int px = 0;
    int py = 0;
    Dimension northD, southD, eastD, westD, centerD;

    if (north) {
      north -> set(XmNwidth, w);
      north -> getPreferredSize(northD);
      north -> layout(x, y, w, northD.getHeight());
    }
    if (south) {
      south -> set(XmNwidth, w);
      south -> getPreferredSize(southD);
      south -> layout(x, y+h-southD.getHeight(), 
        w, southD.getHeight());
    }
    if (west) {
      west -> set(XmNheight, h-northD.getHeight()-southD.getHeight());
      west -> getPreferredSize(westD);
      west -> layout(x, y+northD.getHeight(), 
        westD.getWidth(), h-northD.getHeight()-southD.getHeight());      
    }
    if (east) {
      east -> set(XmNheight, h-northD.getHeight()-southD.getHeight());

      east -> getPreferredSize(eastD);
      east -> layout(x+w-eastD.getWidth(), 
        y+northD.getHeight(), eastD.getWidth(), 
        h-northD.getHeight()-southD.getHeight());      
    }
    if (center) {
      center -> layout(x+westD.getWidth(), y+northD.getHeight(), 
        w-westD.getWidth()-eastD.getWidth(),
        h-northD.getHeight()-southD.getHeight());
    }
  }

};

}


