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
 *  Item.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\object.h>
#include <sol/String.h>


namespace SOL {

class Item :public Object {
private:
  String  name;
  String  text;

public:
  Item()
  {
  }

public:
  Item(TCHAR* name1, TCHAR* text1) 
  {
    name = name1;
    text = text1;    
  }

public:
  Item(TCHAR* text1, Key n)
  {
    setText(text1);
    setId((int)n);
  }


public:
  ~Item()
  {
  }

public:
  void setText(const TCHAR* text1) 
  {  
    const TCHAR* string = text1;
    if (text1 == NULL) {
      string = _T("");
    }
    text = string;
  }


  const TCHAR*  getName() { 
    return (const TCHAR*)name; 
  }

  const TCHAR*   getText() { 
    return (const TCHAR*)text; 
  }

  void  setName(const TCHAR* name1) { 
    const TCHAR* string = name1;
    if (name1==NULL) {
      string = _T("");
    }
    name = string; 
  }

};

}


