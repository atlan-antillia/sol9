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
 *  SessionInfo2.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/SessionInfo.h>

namespace SOL {

class SessionInfo2 :public SessionInfo {

public:
  SessionInfo2()
  :SessionInfo(2)
  {

  }


public:
/*
typedef struct _SESSION_INFO_2 {
  LPWSTR sesi2_cname;
  LPWSTR sesi2_username;
  DWORD  sesi2_num_opens;
  DWORD  sesi2_time;
  DWORD  sesi2_idle_time;
  DWORD  sesi2_user_flags;
  LPWSTR sesi2_cltype_name;
} SESSION_INFO_2, *PSESSION_INFO_2, *LPSESSION_INFO_2;

sesi1_user_flags:Specifies a DWORD value that describes how the user established the session.
 SESS_GUEST     //The user specified by the sesi2_username member established the session using a guest account. 
 SESS_NOENCRYPTION //The user specified by the sesi2_username member established the session without using 
  password encryption.

sesi2_cltype_name: Pointer to a Unicode string that specifies the type of client that established the session. 
 DOS LM 1.0  // LAN Manager for MS-DOS 1.0 clients
 DOS LM 2.0  // LAN Manager for MS-DOS 2.0 clients
 OS/2 LM 1.0  // LAN Manager for MS-OS/2 1.0 clients
 OS/2 LM 2.0   //LAN Manager for MS-OS/2 2.0 clients
*/

  SESSION_INFO_2* getInfo()
  {
    return (SESSION_INFO_2*)getBuffer();
  }

public:
  void display()
  {
    SESSION_INFO_2* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("SESSION_INFO_2 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("ComputerName: %S\n", ptr->sesi2_cname);
        printf("UserName: %S\n", ptr->sesi2_username);

        printf("NumOpens: %d\n",  ptr->sesi2_num_opens);
         printf("Time: %d\n", ptr->sesi2_time);
         printf("IdleTime: %d\n", ptr->sesi2_idle_time);
        printf("UserFlags: %d\n", ptr->sesi2_user_flags);
        printf("ClientType: %S\n", ptr->sesi2_cltype_name);

        printf("\n");
      }
      ptr++;
    }
  }
};


}
