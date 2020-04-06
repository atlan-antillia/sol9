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
 *  HashTable.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/04/22

#pragma once

#include <sol\Object.h>
#include <sol\HashEntry.h>

namespace SOL {

class HashTable  :public Object {
private:
  int   size;
  HashEntry** table;

  Key   hash(const Key key) { return (key % size); }

private:
  Key hash(const char* key)
  {
    long sum = 0;
    size_t len  = strlen(key);

    for(size_t i = 0; i<len; i++) {
      sum = sum + ((int)*key % size);
      key++;
    }
    return (Key)(sum % size);
  }
  
private:
  Key hash(const wchar_t* key)
  {
    long sum = 0;
    size_t len  = wcslen(key);

    for(size_t i = 0; i<len; i++) {
      sum = sum + ((int)*key % size);
      key++;
    }
    return (Key)(sum % size);
  }

public:
  HashTable(int size1)
  {
    size = size1;
    table = new HashEntry*[size];

    for (int i =0 ; i<size; i++) {
      table[i] = NULL;
    }
  }

public:
  void  add(Key key, Object* object)
  {
    Key n = hash(key);
    HashEntry* entry = new HashEntry(key, object);
    entry -> add(table[n]);
    table[n] = entry;
  }

public:
  void  add(const char* key, Object* object)
  {
    Key  n = hash(key);
    HashEntry* entry = new HashEntry(key, object);
    entry -> add(table[n]);
    table[n] = entry;
  }

public:
  void  add(const wchar_t* key, Object* object)
  {
    Key  n = hash(key);
    HashEntry* entry = new HashEntry(key, object);
    entry -> add(table[n]);
    table[n] = entry;
  }

public:
  Object* lookup(Key key)
  {
    Object* object = NULL;
    Key  n = hash(key);
    HashEntry* ptr = table[n];

    while (ptr) {
      if (ptr -> getIntKey() == key) {
        object = ptr -> getObject();
        break;
      }
      ptr = ptr -> getNext();
    }
    return object;
  }

public:
  Object* lookup(const char* key)
  {
    Key n = hash(key);
    HashEntry* ptr = table[n];
    Object* object = NULL;

    while (ptr) {
      if(strcmp(ptr -> getCharKey(), key)==0) {
        object = ptr->getObject();
        break;
      }
      ptr = ptr -> getNext();
    }
    return object;
  }

  Object* lookup(const wchar_t* key)
  {
    Key n = hash(key);
    HashEntry* ptr = table[n];
    Object* object = NULL;

    while (ptr) {
      if(wcscmp(ptr -> getWcharKey(), key)==0) {
        object = ptr->getObject();
        break;
      }
      ptr = ptr -> getNext();
    }
    return object;
  }


public:
  int remove(HashEntry* prev, HashEntry* ptr, Key n) // int n)
  {
    if (ptr == NULL) {
      return False;
    }
    if (prev == ptr) {
      table[n] = ptr -> getNext();
    }
    else {
      prev -> add(ptr -> getNext());
    }
    delete ptr;
    return True;
  }

public:
  int remove(Key key)
  {
    Key n = hash(key);
    HashEntry* ptr  = table[n];
    HashEntry* prev = ptr;

    while(ptr) {
      if(ptr -> getIntKey() == key) {
        remove(prev, ptr, n);
        return True;
      }
      prev = ptr;
      ptr  = ptr -> getNext();
    }
    return False;
  }

public:
  int remove(const char* key)
  {
    Key n = hash(key);
    HashEntry* ptr  = table[n];
    HashEntry* prev = ptr;

    while (ptr) {
      if(strcmp(ptr -> getCharKey(), key)==0 ) {
        remove(prev, ptr, n);
        return True;
      }
      prev = ptr;
      ptr  = ptr -> getNext();
    }
    return False;
  }

  int remove(const wchar_t* key)
  {
    Key n = hash(key);
    HashEntry* ptr  = table[n];
    HashEntry* prev = ptr;

    while (ptr) {
      if (wcscmp(ptr -> getWcharKey(), key)==0 ) {
        remove(prev, ptr, n);
        return True;
      }
      prev = ptr;
      ptr  = ptr -> getNext();
    }
    return False;
  }

public:
  ~HashTable()
  {
    for(int i = 0; i < size; i++) {
      HashEntry* ptr  = table[i];
      HashEntry* prev = ptr;
      while(ptr) {
        prev = ptr;
        ptr  = ptr -> getNext();
        delete prev;
      }
    }

    delete [] table;
  }
};

}


