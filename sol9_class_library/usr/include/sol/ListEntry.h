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
 *  ListEntry.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.23 Added a member variable 'prev' and access(set/get) methods to it and 
// a constructor which takes three arguments.
#pragma once

#include <sol\Entry.h>


namespace SOL {

class ListEntry  :public Entry {
  ListEntry*  prev;  // 1999.09.23
  ListEntry*  next;
 public:
  ListEntry(Object* object)
    :Entry(object),
    prev(NULL), next(NULL) {
    //
  }

  ListEntry(Object* object, ListEntry* nxt)
    :Entry(object),
    prev(NULL), next(nxt) {
    //
  }
  // 1999.09.23 
  ListEntry(Object* object, ListEntry* pre, ListEntry* nxt)
    :Entry(object),
    prev(pre), next(nxt) {
    //
  }

  ~ListEntry() {
      Object* object = getObject();
      delete object;
  }

  void  setPrev(ListEntry* entry) {
      prev = entry;
  }

  void  setNext(ListEntry* entry) {
      next = entry;
  }

  ListEntry*  getPrev() { 
      return  prev;
  }

  ListEntry*  getNext() { 
      return  next;
  }
};

}


