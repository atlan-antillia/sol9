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
 *  StringListT.h
 *
 *****************************************************************************/

// SOL++2000
// 2009/10/18

#pragma once

#include <sol\LinkedList.h>
#include <sol\StringT.h>


namespace SOL {
template <class T> class StringListT :public LinkedList {

public:
  StringListT() { }

public:
  bool add(const StringT<T>& string) {
      return LinkedList::addLast(new StringT<T>(string));
  }

public:
  bool add(const StringT<T>* string) {
      return LinkedList::addLast(new StringT<T>(string));
  }

public:
  bool  add(const T* string) {
      return LinkedList::addLast(new StringT<T>(string));       
  }


public:
  bool  addFirst(const T* string) {
      return LinkedList::addFirst(new StringT<T>(string));   
  }

public:
  bool add(const StringListT<T>& list) 
  { 
    bool rc = true;
    if (list.getLength() > 0) {
      ListEntry* p = list.getEntry();
      while (p != NULL) {
        StringT<T>* string = (StringT<T>*)p -> getObject();
        if (string) {
          add(string);
        }
        p = p -> getNext();
      }
    }
    return rc;
  }

public:
  bool add(const StringListT<T>* list) 
  { 
    bool rc = true;
    if (list != NULL && list -> getLength() > 0) {
      ListEntry* p = list -> getEntry();
      while (p != NULL) {
        StringT<T>* string = (StringT<T>*)p -> getObject();
        if (string) {
          add(string);
        }
        p = p -> getNext();
      }
    }
    return rc;
  }

public:
  StringT<T>*  getNth(int n) {
      return (StringT<T>*)LinkedList::getNth(n);
  }
};

}


