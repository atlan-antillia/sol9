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
 *  ArgList.h
 *
 *****************************************************************************/


// SOL9
// 2009/09/24
// 2015/12/21

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>

namespace SOL {

class ArgList :public Object {

private:
  const Arg* arg;

private:
  size_t  count;

public:
  /**
   * Constructor
   */
  ArgList(const Arg* argList, size_t size)
    :arg(argList),    //Shallow pointer copy for Arg array. 
    count(size)
  {
    if (arg == NULL || size <=0) {
      throw ERROR_BAD_ARGUMENTS;
    }
  }
  
  ArgList(const ArgList&  argList)
    :arg(argList.arg),    
    count(argList.count)
  {
  }

  ArgList& operator=(ArgList&  argList)
  {
    arg   = argList.arg;    
    count = argList.count;
    return *this;
  }

public:
  const TCHAR* getName(int value)
  {
    const TCHAR* name = _T("");
    if (arg) {
      for (size_t i = 0; i<count; i++) {
        if((int)arg[i].value == value) {
          name = arg[i].name;
          break;
        } 
      }
    }
    return name;
  }
};

}


