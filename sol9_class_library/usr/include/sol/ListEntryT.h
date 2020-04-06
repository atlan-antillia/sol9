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
 *  ListEntryT.h
 *
 *****************************************************************************/

#pragma once

#include <sol\EntryT.h>


namespace SOL {
template <class T>class ListEntryT  :public EntryT<T> {
  ListEntryT<T>*  prev; 
  ListEntryT<T>*  next;
  
 public:
  ListEntryT(T* object)
  :EntryT<T>(object),
  prev(NULL), 
  next(NULL) 
  {
    //
  }

  ListEntryT(T* object, ListEntryT* nxt)
    :EntryT<T>(object),
    prev(NULL), next(nxt) 
  {
    //
  }

  ListEntryT(T* object, ListEntryT* pre, ListEntryT* nxt)
    :EntryT<T>(object),
    prev(pre), next(nxt) 
  {
    //
  }

  ~ListEntryT() 
  {
      T* object = getObject();
      delete object; //2017/12/25
  }

  void  setPrev(ListEntryT* entry) 
  {
      prev = entry;
  }

  void  setNext(ListEntryT* entry) 
  {
      next = entry;
  }

  ListEntryT*  getPrev() 
  { 
      return  prev;
  }

  ListEntryT*  getNext() 
  { 
      return  next;
  }
};

}


