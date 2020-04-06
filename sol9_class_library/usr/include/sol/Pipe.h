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
 *  Pipe.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>

namespace SOL {

class Pipe :public Object {
private:
  HANDLE  hReader;
  HANDLE  hWriter;
  SECURITY_ATTRIBUTES sa;

public:
  Pipe(int buffsize =1024) 
  :hReader(INVALID_HANDLE_VALUE),
  hWriter(INVALID_HANDLE_VALUE)
  {
    memset(&sa, 0, sizeof(sa));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    if (CreatePipe(&hReader, &hWriter, &sa, buffsize) == False) {
      hReader = INVALID_HANDLE_VALUE;
      hWriter = INVALID_HANDLE_VALUE;
    }
  }

public:
// Create duplicated pipe.
  Pipe(Pipe& origPipe)
  :hReader(INVALID_HANDLE_VALUE),
  hWriter(INVALID_HANDLE_VALUE)
  {
    memset(&sa, 0, sizeof(sa));
    hReader = origPipe.duplicateReaderHandle();
    hWriter = origPipe.duplicateWriterHandle();
  }


public:
// Create duplicated pipe.
  Pipe(Pipe* origPipe)
  :hReader(INVALID_HANDLE_VALUE),
  hWriter(INVALID_HANDLE_VALUE)
  {
    memset(&sa, 0, sizeof(sa));
    if (origPipe) {
      hReader = origPipe -> duplicateReaderHandle();
      hWriter = origPipe -> duplicateWriterHandle();
    }
  }

public:
  ~Pipe() 
  {
    close();
  }

public:
  void close()
  {
    closeReaderHandle();
    closeWriterHandle();
  }

public:
  void closeReaderHandle() 
  {
    if (hReader != INVALID_HANDLE_VALUE) {
      ::CloseHandle(hReader);
    }
    hReader = NULL;
  }

public:
  void closeWriterHandle() 
  {
    if (hWriter != INVALID_HANDLE_VALUE) {
      ::CloseHandle(hWriter);
    }
    hWriter = NULL;
  }


public:
  HANDLE duplicateReaderHandle()
  {
    HANDLE hReaderDup = INVALID_HANDLE_VALUE;
    if (hReader != INVALID_HANDLE_VALUE &&
      !::DuplicateHandle(GetCurrentProcess(), hReader,
        GetCurrentProcess(), &hReaderDup , 0,
        FALSE,  DUPLICATE_SAME_ACCESS)) {
      hReaderDup = INVALID_HANDLE_VALUE;
    }
    return hReaderDup;
  }

public:
  HANDLE duplicateWriterHandle()
  {
    HANDLE hWriterDup = INVALID_HANDLE_VALUE;
    if (hWriter != INVALID_HANDLE_VALUE &&
      !::DuplicateHandle(GetCurrentProcess(), hWriter,
        GetCurrentProcess(), &hWriterDup , 0,
        FALSE,  DUPLICATE_SAME_ACCESS)) {
      hWriterDup = INVALID_HANDLE_VALUE;
    }
    return hWriterDup;
  }

public:
  int read(char* buffer, int len) 
  {
    unsigned long result = 0;
    if (hReader != INVALID_HANDLE_VALUE) {
      ::ReadFile(hReader, buffer, len, &result, 0);
    }
    return (int)result;
  }

public:
  int  write(const char* buffer, int len) 
  {
    unsigned long result = 0;
    if (hWriter !=INVALID_HANDLE_VALUE) {
      ::WriteFile(hWriter, buffer, len, &result, 0);
    }
    return (int)result;
  }


  HANDLE getReaderHandle() {
    return hReader;
  }

  HANDLE getWriterHandle() {
    return hWriter;

  }

};

}
