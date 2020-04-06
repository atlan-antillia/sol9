/******************************************************************************
 *
 * Copyright (c) 1999-2014 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions, and the following disclaimer.
 * 
 * 2. The name of the author may not be used to endorse or promote products
 *  derived from this software without specific prior written permission.
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
 * StackT.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

namespace SOL {

template <class T> class StackT :public Object {

private:
  T** array;
  size_t size;
  size_t sp;
  
private:
 static const int AUTO_INCREMENT= 10;
  
public:
 StackT(size_t size1 = 100)
  :array(NULL), size(size1), sp(0)
 {
  assert(size>0);
  array = new T*[size];
  for(size_t i = 0; i<size; i++) {
    array[i] = NULL;
  }
 }

public:
 ~StackT()
 {
  if (array) {
   delete [] array;
   array = NULL;
  }
 }

public:
  void push(T* object) 
  {
    if(sp < size) {
      array[sp++] = object;
    } else {
      //2014/12/01 Expand array
      size_t tsize = size + AUTO_INCREMENT;
      T** tmp = new T*[tsize];
      for(size_t i = 0; i < tsize; i++) {
        tmp[i] = NULL; 
      }

      for(size_t i = 0; i <= sp; i++) {
        tmp[i] = array[i]; 
      }
      delete [] array;
    
      array = tmp;
      size = tsize;
      array[sp++] = object;
    }
  }

public:
 T* pop() 
 {
   T* object = NULL;
   if(sp >0) {
     object = array[--sp];
   }
   return object;
 }

public:
  void display()
  {
    for(size_t i = 0; i< sp; i++) {
      T* object = array[i];
      if (object) {
        object -> display();
      }
    }
  }
public:
  void dump()
  {
    for(size_t i = 0; i< sp; i++) {
      T* object = array[i];
      if (object) {
        object -> dump();
      }
    }
  }
  
};
  
}

