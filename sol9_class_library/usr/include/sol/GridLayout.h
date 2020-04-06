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
 *  GridLayout.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\LayoutManager.h>
#include <sol/View.h>

namespace SOL {

class View;
//class Panel;

class GridLayout :public LayoutManager {
private:
  int    row;
  int    column;
  View**  views;
  int    count;
  
public:
  GridLayout(int row, int column) 
  {
    this-> row = 0;
    this-> column = 0;
    views = NULL;
    count = 0;
    if (row > 0 && column > 0) {
      this->row = row;
      this->column = column;
      views = new View*[row*column];
      for(int i = 0; i<row*column; i++) {
        views[i] = NULL;
      }
    }
  }

public:
  ~GridLayout()
  {
    delete [] views;
  }

public:
  virtual void add(View* view) 
  {
    if (count <row*column && view) {
      views[count++] = view;
    }
  }

public:
  virtual void layout(int x, int y, int w, int h) 
  {
    if (row > 0 && column > 0) {
      int n = 0;
      int px= 0;
      int py= 0;
      int minWidth = w/column;
      int minHeight = h/row;
      for(int i = 0; i<row; i++) {
        px = 0;
        for(int j = 0; j<column; j++) {
          if (views[n]) {
            views[n]->layout(px+x, py+y, minWidth, minHeight);
            px += minWidth;
            n++;
          } else { 
            break;
          }
        }
        py += minHeight;
      }
    }
  }

};

}


