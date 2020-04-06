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
 *  FileInfo2.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/FileInfo.h>

namespace SOL {

class FileInfo2 :public FileInfo {

public:
  FileInfo2()
  :FileInfo(2)
  {

  }


public:
/*
typedef struct _FILE_INFO_2 {
  DWORD fi2_id;
}FILE_INFO_2, *PFILE_INFO_2, *LPFILE_INFO_2;Members
fi2_id
Specifies a DWORD value that contains the identification number assigned to the resource when it is opened.

*/

  FILE_INFO_2* getInfo()
  {
    return (FILE_INFO_2*)getBuffer();
  }

public:
  void display()
  {
    FILE_INFO_2* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("FILE_INFO_2 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("ID: %d\n", ptr->fi2_id);
        printf("\n");
      }
      ptr++;
    }
  }
};


}
