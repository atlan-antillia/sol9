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
 *  DefaultLayout.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol/Composite.h>

#include <sol\LinkedList.h>

#include <sol\LayoutManager.h>

namespace SOL {

class View;

class DefaultLayout :public LayoutManager {
private:
  LinkedList list;
  
public:
  DefaultLayout()
  :list(False)
  {
  //
  }

public:
  virtual void add(View* view)
  {
    if (view) {
      list.add(view);
    }
  }

public:
  virtual void layout(int x, int y, int w, int h) 
  {

    ListEntry* ptr = list.getEntry();
    while (ptr) {
        View* view = (View*)ptr->getObject();
        if (view) {
          view->reshape(x, y, w, h);
        }
        ptr = ptr->getNext();
    }
  }

/*  DefaultLayout();
  virtual  void add(View* view);
  virtual void layout(int x, int y, int w, int h);
  */
};

}

