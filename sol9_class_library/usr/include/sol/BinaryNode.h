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
 *  BinaryNode.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>
#include <sol\stdio.h>


namespace SOL {

class BinaryNode :public Object {
private:
  float  x;
  float  y;
  TCHAR*  name;
  Object* object;
  BinaryNode*  parent;
  BinaryNode*  left;
  BinaryNode*  right;

public:

  BinaryNode(BinaryNode* parent1, const TCHAR* name1, 
             Object* object1=NULL)
    :x(0.0),
    y(0.0),
    name(NULL),
    parent(parent1),
    object(object1),
    left(NULL),
    right(NULL)
  {
    if(name1) {
      int slen = strlen(name1)+1;
      name = new TCHAR[slen];
      strcpy_s(name, slen, name1);
    }
  }


public:
  BinaryNode(BinaryNode* parent1, const TCHAR*  name1, 
    BinaryNode* left1, BinaryNode* right1)
    :x(0.0),
    y(0.0),
    name(NULL),
    parent(parent1),
    object(NULL),
    left(left1),
    right(right1)
  {
    if (name1) {
      int slen = strlen(name1)+1;
      name = new TCHAR[slen];
      strcpy_s(name, slen, name1);
    }
  }

public:
  ~BinaryNode()
  {
    delete [] name;
    delete object;
    delete left;
    delete right;
  }

public:
  int configure(int nx, int ny)
  {
    x = (float)nx;
    y = (float)ny;

    nx++;
    int num = 0;
    int n = ny;
    if (left) {
      n = left -> configure(nx, n);
      n++;
      num++;
    }
    if (right) {
      n = right -> configure(nx, n);
      n++;
      num++;
    }

    if (num > 0) n--;
    return n;
  }

public:
  float reconfigure()
  {
    int   num = 0;
    float sum = (float)0.0;
    if (left) {
      sum = sum +  left -> reconfigure();
      num++;
    }
    if (right) {
      sum = sum +  right -> reconfigure();
      num++;
    }

    //if (right) {
    //}
    if (num > 0) y = sum/(float)num;
    return y;
  }

public:
  BinaryNode* search(const TCHAR* name1)
  {
    BinaryNode* found = NULL;

    if (name1 == NULL || *name1 == ZERO) {
      return NULL;
    }

    if (strcmp(name, name1) == 0) {
      return this;
    }
    if (left) {
      found = left -> search(name1);
      if (found) {
        return found;
      }
    }

    if (right) {
      found = right -> search(name1);
      if (found) {
        return found;
      }
    }
    return found;
  }

public:
  BinaryNode* search(int nid)
  {
    int id = getId();
    BinaryNode* found = NULL;

    if (id == nid) {
      return this;
    }

    if (left) {
      found = left -> search(nid);
      if (found) {
        return found;
      }
    }

    if (right) {
      found = right -> search(nid);
      if (found) {
        return found;
      }
    }
    return found;
  }

public:
  void print()
  {
    if (name) {
      Printf(_T(">%s %d %d \r\n"), name, (int)x, (int)y);
    }
    if (left) {
      left -> print();
    }
    if (right) {
      right -> print();
    }
  }
  
  TCHAR*     getName() { return name; }
  Object*    getObject() { return object; }

  BinaryNode*  getParent() { return parent; }
  BinaryNode*  getLeft() { return left; }
  BinaryNode* getRight() { return right; }
  float    getX() { return x; }
  float    getY() { return y; }

  void    setName(const TCHAR* name1);

  void    setObject(Object* obj) { object = obj; }

  void  setParent(BinaryNode* parent1) { parent = parent1; }

  void   setLeft(BinaryNode* node) { left = node; }

  void  setRight(BinaryNode* node) { right = node; }

};

}


