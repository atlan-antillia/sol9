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
 *  Resource.h
 *
 *****************************************************************************/

// SOL++2000
//2000.06.15 Added a new draw method.
#pragma once

#include <sol\Object.h>

namespace SOL {

class DC;

class Resource :public Object {
private:
  TCHAR*  name;
  HANDLE  handle;
 
public:
  Resource(const TCHAR* name1, HANDLE handle1) 
  {
    name = NULL;
    if(name1) {
  
      size_t slen = strlen(name1)+1;
      name = new TCHAR[slen];
      strcpy_s(name, slen, name1);
    }
    handle = handle1;
  }

public:
  ~Resource() 
  { 
    delete [] name;
  }

public:
  void  setHandle(HANDLE h) { handle = h; }

public:
  virtual  void  draw(HDC hdc, int x, int y) { }

public:
  //<added date="2000.06.15">
  virtual void  draw(DC& dc,  int x, int y) { }
  //</added>

public:
  HANDLE    get()     { return handle; }

public:
  TCHAR*    getName() { return name; }

  virtual void  getSize(int* width, int* height) { }

  virtual void  invert() { }

  virtual void  normalize() { }
};

}


