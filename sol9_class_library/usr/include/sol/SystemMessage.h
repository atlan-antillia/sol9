/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SystemMessage.h
 *
 *****************************************************************************/

// SOL9
// 2010/10/31

#pragma once
#include <sol/Object.h>

namespace SOL {

class SystemMessage :public Object {

private:
  static const int size = 1024;
  char  buffer[size];
  bool  result;

private:
  static const DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM;

public:
  SystemMessage(__in DWORD dwMessageId)
  {
    result = true;
    memset(buffer, 0, size);
    DWORD rc = FormatMessage(dwFlags,
      NULL, 
      dwMessageId,
      0,
      buffer, 
      size, 
      NULL);
    if (rc == 0) {
      result = false;
      memset(buffer, 0, size);
    }
  }

public:
  void show() {
    if (result) {
      ::printf("%s\n", buffer);  
    }
  }

public:
  const char* getMessage()
  {
    return buffer;
  }
};

}
