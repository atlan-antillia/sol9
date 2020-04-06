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
 *  ServerInfo0.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/ServerInfo.h>

namespace SOL {

class ServerInfo100 :public ServerInfo {

public:
  ServerInfo100()
  :ServerInfo(100)
  {

  }

public:
/*
typedef struct _SERVER_INFO_100 {
  DWORD  sv100_platform_id;
  LPWSTR sv100_name;
}SERVER_INFO_100, *PSERVER_INFO_100, *LPSERVER_INFO_100;
*/
  SERVER_INFO_100* getInfo()
  {
    return (SERVER_INFO_100*)getBuffer();
  }

public:
  void display()
  {
    SERVER_INFO_100* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("SERVER_INFO_100 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("PlatformId: %d\n", ptr->sv100_platform_id);
        printf("Name: %S\n", ptr->sv100_name);
      }
      ptr++;
    }
  }
};

}
