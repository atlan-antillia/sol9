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
 *  ProcessInf.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once


#include <sol\Object.h>

namespace SOL {

class ProcessInfo :public Object {
private:

  int    pid;
  TCHAR  name[_MAX_PATH*2];
  int    parentPID;

  int    cntThreads;

public:

  ProcessInfo(int pid1, const TCHAR* name1, int pid2=0, int threads=0) {
    pid    = pid1;
    strcpy_s(name, CountOf(name), name1);
    parentPID = pid2;  
    cntThreads = threads;

  }

  int      getProcessId() { return pid; }

  int      getParentProcessId() { return parentPID; }

  const TCHAR* getName() { return name; }

  int      getThreadsCount() { return cntThreads; }

  virtual  int  compare(Object* object) {
    ProcessInfo* info = (ProcessInfo*)object;
    const TCHAR* p = _T("");
    if (info) {
      p = info->getName();
    }
    return strcmp(name, p);
  }
};

}


