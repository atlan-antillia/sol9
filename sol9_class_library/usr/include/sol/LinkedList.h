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
 *  LinkedList.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.04 Modified getLength and getEntry. 

#pragma once

#include <sol\List.h>
#include <sol\ListEntry.h>


/**
 * LinkedList class reprents a linear singly-linked list.
 */
namespace SOL {

class LinkedList :public List {
private:
  ListEntry* entry;
  bool    gc;

public:
  LinkedList(bool gc1=true)
    :entry(NULL), gc(gc1)
  {
  }

public:
  bool  addFirst(Object* object)
  {
    bool rc = true;
    entry = new ListEntry(object, entry);
    if(entry == NULL) {
      rc = false;
    }
    return rc;
  }

public:
  bool add(Object* object)
  {
    ListEntry* ptr  = entry;
    ListEntry* prev = ptr;

    ListEntry* newEntry= new ListEntry(object);
    if (newEntry == NULL) {
      return false;
    }

    if (ptr == NULL) {
      entry = newEntry;
    }
    else {
      while (ptr) {
        prev = ptr;
        ptr  = ptr -> getNext();
      }
      prev -> setNext(newEntry);
    }
    return true;
  }

public:
  bool remove(Object* object)
  {
    bool rc = false;
    ListEntry* ptr  = entry;
    ListEntry* prev = ptr;

    while (ptr) {
      Object* obj = ptr -> getObject();
      if (obj == object && prev == ptr) {
        entry = ptr -> getNext();
        if (gc == false) {
          ptr ->setObject(NULL);
        }
        delete ptr;
        rc = true;
        break;
      }
      if (obj == object && prev != ptr) {
        prev -> setNext(ptr->getNext());
        if (gc == false) {
          ptr ->setObject(NULL);
        }  

        delete ptr;
        rc = true;
        break;
      }
      else {
        prev = ptr;
        ptr  = ptr -> getNext();
      }
    }
    return rc;
  }

public:
  ~LinkedList()
  {
    clear();
  }

public:
  bool isContained(Object* obj)
  {
    bool rc = false;

    ListEntry* ptr  = entry;

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
    ListEntry* ptr  = entry;
    ListEntry* prev = ptr;

    while (ptr) {
      prev = ptr;
      ptr = ptr -> getNext();
      if (gc == False) {
        prev ->setObject(NULL);
      }
      delete prev;
    }
    entry = NULL;
  }

public:
  int getLength() const
  {
    ListEntry* ptr = entry;
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
    int m = 0;  // Start from 0 not 1 in SOL++ 3.0

    Object* object = NULL;
    ListEntry* ptr = entry;

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


// Simple selection sort
public:
  void sort(SortDirection dir)
  {
    int length = getLength();
    int i = 0;
    ListEntry* ith = entry;
   
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
    ListEntry* ptr = entry;
    ListEntry* rev = NULL;
        
    while (ptr) {
      ListEntry* next = ptr -> getNext();
      ptr -> setNext(NULL);

      if (rev) {
        ptr -> setNext(rev); 
        rev = ptr;
      } else {
        rev = ptr;
      }
      ptr = next;
    }

    entry = rev;
  }

//  LinkedList(bool gc = true);
//  ~LinkedList();

//  Boolean  add(Object* object);

  bool  addLast(Object* object) { 
    return add(object); 
  }

//  bool  addFirst(Object* object);

//  void  clear();
//  Boolean isContained(Object* object);

//  Boolean  remove(Object* object);
//  int    getLength() const;  // 1999.09.04

  ListEntry*  getEntry() const { 
    return  entry; 
  } 
  
  // 1999.09.04
  
  //Object*      getNth(int n);

  //void  sort(SortDirection dir);

  void  enableGC() {
      gc = true;
  }
  void  disableGC() {
      gc = false;
  }
  //void  reverse();
  

public:
  void display()
  {
    ListEntry* ptr  = entry;

    while (ptr) {
       Object* object = ptr -> getObject();
      if (object) {
        object -> display();  
      }
      ptr = ptr -> getNext();
    }
  }

};

}


