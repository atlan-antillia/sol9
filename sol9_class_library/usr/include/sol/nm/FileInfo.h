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
 *  FileInfo.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/NetInfo.h>

namespace SOL {

class FileInfo: public NetInfo {

public:
  /**
   * Constructor
   */
  FileInfo(int lv=0)
  :NetInfo(lv)
  {
  }

public:
  /**
   * Destructor
   */
  ~FileInfo()
  {
  }

protected:
  const wchar_t* getPermission(DWORD value, __out StringBufferT<wchar_t>& buffer)
  {
    static const ArgT<wchar_t> types[] = {
      {L"FILE_READ", PERM_FILE_READ},    //Permission to read a resource and, by default, execute the resource.
      {L"FILE_WRITE",PERM_FILE_WRITE},  //Permission to write to a resource.
      {L"FILE_CREATE",PERM_FILE_CREATE}  //Permission to create a resource; data can be written when creating the resource.
     };

    int count = XtNumber(types);
    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (types[i].value & value) {
        if (matched>0) {
          buffer.append(L" | ");
        }
        buffer.append(types[i].name);
        matched++;
      }
    }
    return (const wchar_t*)buffer;
  }

};

}
