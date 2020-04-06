/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  HandlerEntry.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/07/03 Modified call method to check if an object is NULL.

#pragma once

#include <sol\Entry.h>
#include <sol\Event.h>


typedef long (Object::*Handler)(Event&);

namespace SOL {

class HandlerEntry :public Entry {
private:
  UINT        message;
  Handler       handler;
  HandlerEntry* next;

public:
  HandlerEntry(UINT msg, Object* object, Handler proc, void* data) 
  :Entry(object, data),
    message(msg),
    handler(proc),
    next(NULL)
  {
  }

public:
  long  call(Event& event)
  {
    Object* object = getObject();
    event.setData(getData());
    //2012/07/03
    if (object) {
      return (object->*handler)(event);
    } else {
      return 0;
    }
  }

  void  add(HandlerEntry* entry) { next = entry; }

  UINT  getMessage() { return message; }
  HandlerEntry* getNext() { return next; }
};

}

