/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileInfo3.h
 *
 *****************************************************************************/

// 2012/10/12 Updated
#pragma once

#include <sol/nm/FileInfo.h>

//#include "FileInfoListView.h"

namespace SOL {

class FileInfo3 :public FileInfo {

public:
  FileInfo3()
  :FileInfo(3)
  {

  }


public:
/*
typedef struct _FILE_INFO_3 {
  DWORD fi3_id;
  DWORD fi3_permissions;
  DWORD fi3_num_locks;
  LMSTR fi3_pathname;
  LMSTR fi3_username;
}FILE_INFO_3, *PFILE_INFO_3, *LPFILE_INFO_3;Members

fi3_id
  Specifies a DWORD value that contains the identification number assigned to the resource when it is opened.

fi3_permissions
  Specifies a DWORD value that contains the access permissions associated with the opening application. 
  This member can be one or more of the following values. 

  PERM_FILE_READ: Permission to read a resource and, by default, execute the resource.
  PERM_FILE_WRITE: Permission to write to a resource.
  PERM_FILE_CREATE: Permission to create a resource; data can be written when creating the resource.
 
fi3_num_locks
  Specifies a DWORD value that contains the number of file locks on the file, device, or pipe.

fi3_pathname
  Pointer to a string that specifies the path of the opened resource.
 
fi3_username
  Pointer to a string that specifies which user (on servers that have user-level security) or which 
  computer (on servers that have share-level security) opened the resource. 
*/

  FILE_INFO_3* getInfo()
  {
    return (FILE_INFO_3*)getBuffer();
  }

public:
  void display(HWND hwnd=NULL) //(FileInfoListView& listv)
  {
    FILE_INFO_3* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("FILE_INFO_3 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("ID: %d\n", ptr->fi3_id);
        StringBufferT<wchar_t> permissions;
        getPermission(ptr->fi3_permissions, permissions);
        printf("Permission: %S\n", (const wchar_t*)permissions);
        printf("NumLocks: %d\n", ptr->fi3_num_locks);
        printf("PathName: %S\n", ptr->fi3_pathname);
        printf("UserName: %S\n", ptr->fi3_username);

        printf("\n");
      }
      ptr++;
    }
  }

};


}
