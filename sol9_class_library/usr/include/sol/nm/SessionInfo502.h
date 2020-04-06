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
 *  SessionInfo502.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/SessionInfo.h>

namespace SOL {

class SessionInfo502 :public SessionInfo {

public:
  SessionInfo502()
  :SessionInfo(502)
  {

  }


public:
/*
typedef struct _SESSION_INFO_502 {
  LPWSTR sesi502_cname;
  LPWSTR sesi502_username;
  DWORD  sesi502_num_opens;
  DWORD  sesi502_time;
  DWORD  sesi502_idle_time;
  DWORD  sesi502_user_flags;
  LPWSTR sesi502_cltype_name;
  LPWSTR sesi502_transport;
}SESSION_INFO_502, *PSESSION_INFO_502, *LPSESSION_INFO_502;
*/

  SESSION_INFO_502* getInfo()
  {
    return (SESSION_INFO_502*)getBuffer();
  }

public:
  void display()
  {
    SESSION_INFO_502* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("SESSION_INFO_2 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("ComputerName: %S\n", ptr->sesi502_cname);
        printf("UserName: %S\n", ptr->sesi502_username);

        printf("NumOpens: %d\n",  ptr->sesi502_num_opens);
         printf("Time: %d\n", ptr->sesi502_time);      

         printf("IdleTime: %d\n", ptr->sesi502_idle_time);
        printf("UserFlags: %S\n", getUserFlags(ptr->sesi502_user_flags));
        printf("ClientType: %S\n", ptr->sesi502_cltype_name);
        printf("Transport: %S\n", ptr->sesi502_transport);

        printf("\n");
      }
      ptr++;
    }
  }
};


}
