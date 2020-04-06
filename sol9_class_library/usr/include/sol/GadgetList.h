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
 *  GadgetList.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\LinkedList.h>
#include <sol\Gadget.h>
#include <sol\DC.h>


namespace SOL {

class GadgetList :public LinkedList {
public:
  GadgetList() { }

  BOOL  addLast(Gadget* gadget) {
      return LinkedList::addLast(gadget);   
  }

  BOOL  addFirst(Gadget* gadget) {
      return LinkedList::addFirst(gadget);   
  }

  Gadget*  getNth(int n) {
      return (Gadget*)LinkedList::getNth(n);
  }

public:
  void GadgetList::draw(DC* dc)
  {
    GadgetList::draw(dc, 0, 0);
  }

public:
  void draw(DC* dc, int x, int y)
  {
    ListEntry* ptr = getEntry();
    while(ptr) {
      Gadget* gadget = (Gadget*) ptr -> getObject();
      if(gadget) {
        gadget -> draw(dc, x, y);
      }
      ptr  = ptr -> getNext();
    }
  }

public:
  virtual void getExtent(int* width, int* height)
  {
    *width  = 0;
    *height = 0;
    ListEntry* ptr = getEntry();
    while(ptr) {
      Gadget* gadget = (Gadget*) ptr -> getObject();
      if(gadget) {
        RECT r;
        gadget -> getRect(&r);

        if(r.right >= *width) {
          *width = r.right;
        }
        if(r.bottom >= *height) {
          *height = r.bottom;
        }
      }
      ptr  = ptr -> getNext();
    }
  }


};

}


