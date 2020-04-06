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
 *  CommandLine.h
 *
 *****************************************************************************/

// SOL++2000
// SOL9 2009/10/08


#pragma once

#include <sol\Object.h>

#include <sol\String.h>


namespace SOL {

class CommandLine :public Object {
private:
  String arguments;

public:
  CommandLine(const TCHAR* cmd)
    :arguments(_T(""))
  {
    if (cmd) {
      arguments = cmd;// = new String(cmd);
    }
  }

public:
  ~CommandLine()
  {
  }

public:
  int getArgv(TCHAR* argv[], int maxArgs)
  {
    int argc = 0;
    //2009/10/19
    TCHAR* ptr = (TCHAR*)arguments;
    while(*ptr) {
      ptr = getToken(ptr, &argv[argc++]);
      if(argc == _MAX_PATH){
        break;
      }
    }
    return argc;
  }

public:
  TCHAR*  getToken(TCHAR* p, TCHAR** pos)
  {
    while(*p == (TCHAR)' ' || *p == (TCHAR)'\t') p++;

    int   doubleq = 0;
    if(*p == (TCHAR)'"') {
      doubleq = 1;
      p++;
    }
    *pos = p;
    if(*p == NULL) return NULL;

    while(*p) {
      if(*p == (TCHAR)'"' && doubleq == 1) {
        p++;
        *(p - 1) = NULL;
        break;
      }
      if(doubleq == 0 && (*p == (TCHAR)' ' || *p == (TCHAR)'\t')) {
        p++;
        *(p - 1) = NULL;
        break;
      }
      p++;
    }
    while(*p == (TCHAR)' ' || *p == (TCHAR)'\t') p++;
    return p;
  }


};

}


