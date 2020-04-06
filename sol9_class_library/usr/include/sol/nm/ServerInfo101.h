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
 *  ServerInfo101.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/ServerInfo.h>

namespace SOL {

class ServerInfo101 :public ServerInfo {

public:
  ServerInfo101()
  :ServerInfo(101)
  {

  }

public:
/*
typedef struct _SERVER_INFO_101 {
  DWORD  sv101_platform_id;
  LPWSTR sv101_name;
  DWORD  sv101_version_major;
  DWORD  sv101_version_minor;
  DWORD  sv101_type;
  LPWSTR sv101_comment;
}SERVER_INFO_101, *PSERVER_INFO_101, *LPSERVER_INFO_101;
*/
  SERVER_INFO_101* getInfo()
  {
    return (SERVER_INFO_101*)getBuffer();
  }

public:
  void display()
  {
    SERVER_INFO_101* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("SERVER_INFO_101 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("PlatformId: %d\n", ptr->sv101_platform_id);
        printf("Name: %S\n", ptr->sv101_name);
        printf("VersionMajor: %d\n", ptr->sv101_version_major);
        printf("VersionMinor: %d\n",  ptr->sv101_version_minor);
        printf("Type: %d\n", ptr->sv101_type);
        printf("Comment: %S\n", ptr->sv101_comment);
        printf("\n");
      }
      ptr++;  
    }
  }
};

}
