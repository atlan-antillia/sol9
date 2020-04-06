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
 *  SessionInfo1.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/SessionInfo.h>

namespace SOL {

class SessionInfo1 :public SessionInfo {

public:
  SessionInfo1()
  :SessionInfo(1)
  {

  }


public:
/*
typedef struct _SESSION_INFO_1 {
  LPWSTR sesi1_cname;
  LPWSTR sesi1_username;
  DWORD  sesi1_num_opens;
  DWORD  sesi1_time;
  DWORD  sesi1_idle_time;
  DWORD  sesi1_user_flags;
} SESSION_INFO_1, *PSESSION_INFO_1, *LPSESSION_INFO_1;

sesi1_user_flags:Specifies a DWORD value that describes how the user established the session.

SESS_GUEST     //The user specified by the sesi2_username member established the session using a guest account. 
SESS_NOENCRYPTION //The user specified by the sesi2_username member established the session without using 
  password encryption.
*/

  SESSION_INFO_1* getInfo()
  {
    return (SESSION_INFO_1*)getBuffer();
  }

public:
  void display()
  {
    SESSION_INFO_1* ptr = getInfo();

    int count = getEntriesRead();
    printf("SESSION_INFO_1 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("ComputerName: %S\n", ptr->sesi1_cname);
        printf("UserName: %S\n", ptr->sesi1_username);

        printf("NumOpens: %d\n",  ptr->sesi1_num_opens);
         printf("Time: %d\n", ptr->sesi1_time);
         printf("IdleTime: %d\n", ptr->sesi1_idle_time);
        printf("UserFlags: %d\n", ptr->sesi1_user_flags);
        printf("\n");
      }
      ptr++;
    }
  }
};


}
