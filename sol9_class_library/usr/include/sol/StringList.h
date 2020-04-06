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
 *  StringList.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.03 Added two add method to take a reference or pointer to String.
// 1999.09.04 Added two add method to take a feference or pointer to StringList.
// 2008/07/07 Modified Boolean to bool
#pragma once

#include <sol\LinkedList.h>
#include <sol\String.h>


namespace SOL {

class StringList :public LinkedList {

public:
  StringList() { }

  // 1999.09.03
public:
  bool add(const String& string) {
      return LinkedList::addLast(new String(string));
  }

  // 1999.09.03
public:
  bool add(const String* string) {
      return LinkedList::addLast(new String(string));
  }

public:
  bool  add(const TCHAR* string) {
      return LinkedList::addLast(new String(string));       
  }

public:
  bool  addLast(const TCHAR* string) {
      return LinkedList::addLast(new String(string));   
  }

public:
  bool  addFirst(const TCHAR* string) {
      return LinkedList::addFirst(new String(string));   
  }

  // 1999.09.04
  //bool add(const StringList& list);
  // 1999.09.04
  //bool add(const StringList* list);
public:
  bool add(const StringList& list) 
  { 
    bool rc = true;
    if (list.getLength() > 0) {
      ListEntry* p = list.getEntry();
      while (p != NULL) {
        String* string = (String*)p -> getObject();
        if (string) {
          add(string);
        }
        p = p -> getNext();
      }
    }
    return rc;
  }

public:
  bool add(const StringList* list) 
  { 
    bool rc = true;
    if (list != NULL && list -> getLength() > 0) {
      ListEntry* p = list -> getEntry();
      while (p != NULL) {
        String* string = (String*)p -> getObject();
        if (string) {
          add(string);
        }
        p = p -> getNext();
      }
    }
    return rc;
  }

public:
  String*  getNth(int n) {
      return (String*)LinkedList::getNth(n);
  }
};

}


