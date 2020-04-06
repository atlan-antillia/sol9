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
 *  CallbackList.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\CallbackEntry.h>
#include <sol\List.h>


namespace SOL {

class CallbackList :public List {
private:
  CallbackEntry* entry;

public:
  CallbackList() 
  { 
    entry = NULL; 
  }

public:

  ~CallbackList()
  {
    CallbackEntry* ptr = entry;
    CallbackEntry* prev;
    while(ptr) {
      prev = ptr;
      ptr  = ptr -> getNext();
      delete prev;
    }
  }

public:
  void add(const TCHAR* name, Key key, Object* object, 
      Callback proc, void* data) 
  {
    CallbackEntry* ent = new CallbackEntry(name, key, 
        object, proc, data);
    ent -> add(entry);
    entry = ent;
  }

public:
  void call(const TCHAR* name, Key key, void* value, Event& event) 
  {
    Action action(value, event);
    CallbackEntry* ptr = entry;
    while(ptr) {
      HWND hwnd = (HWND)key;
      Key id = 0;
      if(::IsWindow(hwnd)) {
        id = (Key)::GetWindowLong(hwnd, GWL_ID);
      }
      
      if(( key  == ptr->getKey() || id == ptr->getKey() ) && 
        name == ptr->getName() ) {
        Sleep(0);//2009/11/16
        ptr -> call(action);
        // Set callback result to event;
        event.setResult(action.getResult());
        break;
      }
      ptr = ptr -> getNext();
    }
  }

  void display(HWND self) 
  {
    CallbackEntry* ptr = entry;
    while(ptr) {
      HWND hwnd = (HWND)ptr->getKey();
      TCHAR value[128];
      
      _stprintf_s(value, CountOf(value), _T("SELF %0x HWND %0x"), (LONG)(LONG_PTR)self,        (LONG)(LONG_PTR)hwnd);
      
      MessageBox(NULL, value, ptr->getName(), MB_OK);
      
      ptr = ptr -> getNext();
    }
  }


};

}


