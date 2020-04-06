/******************************************************************************
 *
 * Copyright (c) 2014 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  QueueT.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Collection.h>
#include <sol/ListEntryT.h>

namespace SOL {

template <class T> class QueueT :public Collection {
  
private:
  ListEntryT<T>* head;
  ListEntryT<T>* tail;

public:
  QueueT()
    :head(NULL), tail(NULL)
  {
  }

public:
  ~QueueT()
  {
    clear(); 
  }

public:
  bool addLast(T* obj) 
  {
    bool rc = false;
    if (obj == NULL) {
      return rc;
    }
    rc = true;
    ListEntryT<T>* ent = new ListEntryT<T>(obj);
    if(head == NULL) {
      head = ent;
      tail = ent;
      return rc;
    }

    if(tail) {
      tail -> setNext(ent);
      tail = ent;
    }
    return rc;
  }

public:
  bool add(T* obj)
  {
    return addLast(obj);
  }

public:
  bool addFirst(T* obj) 
  {
    bool rc = false;
    if (obj == NULL) {
      return rc;
    }
    rc = true; 
    ListEntryT<T>* ent = new ListEntryT<T>(obj);
    if(head == NULL) {
      head = ent;
      tail = ent;
      return rc;
    }

    if(head) {
      ent -> setNext(head);
      head = ent;
    }
    return rc;
  }

public:
  T*  get()  
  {
    if(head) {
      ListEntryT<T>* ent = head;
      head = head -> getNext();
      return ent->getObject(); 
    }
    else {
      return NULL;
    }
  }


public:
  T*  peek() 
  {
    if(head) {
      ListEntryT<T>* ent = head;
      return ent->getObject(); 
    }
    else {
      return NULL;
    }
  }

public:
  void clear()
  {
    if(head==NULL && tail== NULL) {
      return ;
    }
    if(head) {
      ListEntryT<T>* ptr = head;
      ListEntryT<T>* prev = ptr;
      while(ptr) {
        prev = ptr;
        ptr = ptr -> getNext();
        prev->setObject(NULL);
        delete prev;
      }
    }
  }

public:
  int  getLength() 
  {
    int n = 0;
    if(head==NULL && tail== NULL) {
      return n;
    }
    if(head) {
      ListEntryT<T>* ent = head;
      while(ent) {
        ent = ent -> getNext();
        n++;
      }
    }
    return n;
  }
  
public:
  void  display() 
  {
    if(head==NULL && tail== NULL) {
      return;
    }
    if(head) {
      ListEntryT<T>* ent = head;
      while(ent) {
        T* object = ent -> getObject();
        if (object) {
          object -> display();
        }
        ent = ent -> getNext();
      }
    }
  }

public:
  void  dump() 
  {
    if(head==NULL && tail== NULL) {
      return;
    }
    if(head) {
      ListEntryT<T>* ent = head;
      while(ent) {
        T* object = ent -> getObject();
        if (object) {
          object -> dump();
        }
        ent = ent -> getNext();
      }
    }
  }

};

}

