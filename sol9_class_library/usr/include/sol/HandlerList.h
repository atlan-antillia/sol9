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
 *  HandlerList.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\HandlerEntry.h>
#include <sol\List.h>

namespace SOL {

class HandlerList :public List {
private:
  HandlerEntry* entry;
  
public:
  HandlerList() { 
    entry = NULL; 
  }

public:
  ~HandlerList()
  {
    HandlerEntry* ptr = entry;
    HandlerEntry* prev;
    while(ptr) {
      prev = ptr;
      ptr  = ptr -> getNext();
      delete prev;
    }
  }

public:
  void add(UINT msg, Object* object, Handler proc, void* data)
  {
    HandlerEntry* ent = new HandlerEntry(msg, object, proc, data);
    ent -> add(entry);
    entry = ent;
  }

public:
  Boolean call(Event& event, LONG_PTR* value) 
  {
    UINT msg = event.getMessage();
    HandlerEntry* ptr = entry;
    while(ptr) {
      if(msg == ptr->getMessage()) {
        Sleep(0);  //2009/11/16
        *value = ptr -> call(event);
        return TRUE;
      }
      ptr = ptr -> getNext();
    }
    return FALSE;
  }

public:
  void HandlerList::clear()
  {
    HandlerEntry* ptr = entry;
    HandlerEntry* prev = entry;

    while(ptr) {
      prev = ptr;
      ptr = ptr -> getNext();
      delete prev;
    }
    entry = NULL;
  }

};

}

