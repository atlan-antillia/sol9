/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ThreadSafeQueueT.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Collection.h>
#include <sol/ListEntryT.h>
#include <sol/CriticalSection.h>

namespace SOL {

template <class T> class ThreadSafeQueueT :public Collection {
	
private:
  CriticalSection  cs;
  ListEntryT<T>* head;
  ListEntryT<T>* tail;

public:
  ThreadSafeQueueT()
    :head(NULL), tail(NULL)
  {
  }

public:
  ~ThreadSafeQueueT()
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
    cs.enter();

    ListEntryT<T>* ent = new ListEntryT<T>(obj);
    if(head == NULL) {
      head = ent;
      tail = ent;
    } else {

      tail -> setNext(ent);
      tail = ent;
    }
    cs.leave();
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

    cs.enter();

    ListEntryT<T>* ent = new ListEntryT<T>(obj);
    if(head == NULL) {
      head = ent;
      tail = ent;
    } else {
      ent -> setNext(head);
      head = ent;
    }

    cs.leave();
    return rc;
  }

public:
  T*  get()  
  {
    T* t = NULL;
    cs.enter();
    if(head) {
      ListEntryT<T>* ent = head;
      head = head -> getNext();
      t = ent->getObject(); 
    }
    cs.leave();
    return t;
  }


public:
  T*  peek() 
  {
    T* t = NULL;
    cs.enter();
    if(head) {
      ListEntryT<T>* ent = head;
      t = ent->getObject(); 
    }
    cs.leave();
    return t;
  }

public:
  void clear()
  {
    if(head==NULL && tail== NULL) {
      return ;
    }
    cs.enter();

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
    cs.leave();
  }

public:
  int  getLength() 
  {
    int n = 0;
    if(head==NULL && tail== NULL) {
      return n;
    }
    cs.enter(); 
    if(head) {
      ListEntryT<T>* ent = head;
      while(ent) {
        ent = ent -> getNext();
        n++;
      }
    }
    cs.leave();

    return n;
  }
/*
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
*/
};

}

