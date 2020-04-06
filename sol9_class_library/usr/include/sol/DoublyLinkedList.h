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
 *  DoublyLinkedList.h
 *
 *****************************************************************************/

// SOL++2000
//  
#pragma once

#include <sol\List.h>

#include <sol\ListEntry.h>


namespace SOL {

class DoublyLinkedList :public List {
private:
  ListEntry*  head;
  ListEntry*  tail;
  bool    gc;

public:
  DoublyLinkedList(bool gc1=true)
    :head(NULL), 
    tail(NULL),
    gc(gc1)
  {
  }

public:
  bool addFirst(Object* object)
  {
    ListEntry* newEntry = new ListEntry(object, NULL, head);
    if (newEntry == NULL) {
      return false;
    }
  
    if (head != NULL) {
      head ->setPrev(newEntry);
    }  

    // Set the head to be a newEntry. 
    head = newEntry;

    // If tail is NULL, set tail to be a newEntry
    if (tail == NULL) {
      tail = newEntry;
    }

    return true;
  }


public:
  // Add an object to the tail of this list.
  bool add(Object* object)
  {
    ListEntry* newEntry= new ListEntry(object, tail, NULL);
    if (newEntry == NULL) {
      return false;
    }
    if (tail != NULL) {
      tail -> setNext(newEntry); 
    }

    // Set tail to be a newEntry. 

    tail = newEntry;

    // If head is NULL, set head to be a newEntry
    if (head == NULL) {
      head = newEntry;
    }
    return true;
  }

public:
  bool remove(Object* object)
  {
    bool rc = false;
    ListEntry* ptr  = head;
    ListEntry* prev = ptr;

    while (ptr) {
      Object* obj = ptr -> getObject();

      if (obj == object) {
        if (ptr != head && ptr != tail) {
          ListEntry* next = ptr -> getNext();
          prev -> setNext(next);
          if (next != NULL) {
            next -> setPrev(prev);
          }    
        }

        // If matched on the head of this list.

        if (ptr == head) {
          // Update the head.
          head = ptr -> getNext();
          head -> setPrev(NULL);
          ptr -> setPrev(NULL);
        }
        // If ptr were tail, update the tail. 
        if (ptr == tail) {
          tail = ptr -> getPrev();
          tail ->setNext(NULL);
        }

        if (gc == false) {
          ptr -> setObject(NULL);
        }

        // delete the ptr of ListEntry
        delete ptr;
        rc = true;
        break;

      } else {
        prev = ptr;
        ptr  = ptr -> getNext();
      }
    }
    return rc;
  }


public:
  ~DoublyLinkedList()
  {
    clear();
  }

public:
  bool isContained(Object* obj)
  {
    bool rc = false;

    ListEntry* ptr  = head;

    while (ptr) {
      if (ptr -> getObject() == obj) {
        rc = true;
        break;
      }
      ptr = ptr -> getNext();
    }
    return rc;
  }

public:
  void clear()
  {
    ListEntry* ptr  = head;
    ListEntry* prev = ptr;

    while (ptr) {
      prev = ptr;
      ptr = ptr -> getNext();
      if (gc == false) {
        prev ->setObject(NULL);
      }
      delete prev;
    }
    head = NULL;
    tail = NULL;
  }

public:
  int getLength() const
  {
    ListEntry* ptr = head;
    int n = 0;
    while(ptr) {
      ptr = ptr -> getNext();
      n++;
    }
    return n;
  }

public:
  Object* getNth(int n)
  {
    int m = 0;

    Object* object = NULL;
    ListEntry* ptr = head;

    while(ptr) {
      if(m == n) {
        object = ptr ->getObject();
        break;
      }
      ptr = ptr -> getNext();
      m++;
    }
    return object;
  }

public:
  // Simple selection sort
  void sort(SortDirection dir)
  {
    int length = getLength();
    int i = 0;
    ListEntry* ith = head;
   
    while (i<length-1) {  
      ListEntry* cth = ith;
      ListEntry* jth = ith -> getNext();
      Object*    obj = ith -> getObject();

      while (jth) {
        Object* jthObj = jth->getObject();
        if (dir == ASCENDING) {
          if (jthObj -> compare(obj) > 0) {
            cth = jth;
            obj = jth -> getObject();
          }  
        }
        if (dir == DESCENDING) {
          if (jthObj -> compare(obj) < 0) {
            cth = jth;
            obj = jth -> getObject();
          }  
        }
        jth = jth -> getNext();
      }

      cth -> setObject(ith->getObject());
      ith -> setObject(obj);

      ith = ith -> getNext();
      i++;
    }  // wile
  }

public:
  void reverse()
  {
    ListEntry* tmp = head;
    ListEntry* ptr = tail;
    ListEntry* rev = NULL;
        
    while (ptr) {
      ListEntry* prev = ptr -> getPrev();
      ListEntry* next = ptr -> getNext();
      ptr -> setNext(prev);
      ptr -> setPrev(next);
      ptr = prev;
    }

    head = tail;
    tail = tmp;
  }


  bool  addLast(Object* object) { 
    return add(object); 
  }

  ListEntry*  getHead() const { 
    return head; 
  }

  ListEntry*  getTail() const { 
    return tail; 
  }

  void  enableGC() {
      gc = true;
  }
  void  disableGC() {
      gc = false;
  }
};

}


