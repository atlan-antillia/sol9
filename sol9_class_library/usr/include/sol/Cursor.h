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
 *  Cursor.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Resource.h>

#include <sol\DC.h>

namespace SOL {

class Cursor :public Resource {
private:
  int width;
  int height;

public:
  Cursor(const TCHAR* name, HCURSOR hcursor)
  :Resource(name, hcursor)
  {
    width  = ::GetSystemMetrics(SM_CXCURSOR);
    height = ::GetSystemMetrics(SM_CYCURSOR);
  }

public:
  ~Cursor()
  {
    ::DestroyCursor((HCURSOR)get());
  }

public:
  void draw(DC* dc, int x, int y)
  {
    HCURSOR hcursor = (HCURSOR)get();
    if(hcursor) {
      // This works well, because ...
      ::DrawIcon(dc->get(), x, y, hcursor); 
    }
  }

public:
  void draw(DC* dc)
  {
    draw(dc, 0, 0);
  }


/*
  Cursor(const TCHAR* name, HCURSOR hcursor);
  ~Cursor();
  void  draw(DC* dc);
  void  draw(DC* dc, int x, int y);
*/
  void  getSize(int* w, int* h) { *w = width; *h = height; }
};

}


