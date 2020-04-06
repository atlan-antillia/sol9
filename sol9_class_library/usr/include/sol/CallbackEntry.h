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
 *  CallbackEntry.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Entry.h>
#include <sol\Action.h>


namespace SOL {

typedef void (Object::*Callback)(Action&);

class CallbackEntry :public Entry {
private:
  const TCHAR*  name;
  Key       key;
  Callback  callback;
  CallbackEntry*   next;

public:
  CallbackEntry(const TCHAR* name1, const Key k, Object* object, 
          Callback proc, void* data) 
  :Entry(object, data),
    name(name1), 
    key(k),
    callback(proc),
    next(NULL)
  {

  }

public:
  void call(Action& action)
  {
    Object* object = getObject();
    action.setData(getData());
    (object->*callback)(action);
  }

  void   add(CallbackEntry* entry) { next = entry; }

  Key    getKey(){ return key; }
  const TCHAR* getName() { return name; }
  CallbackEntry* getNext() { return next; }
};

}


