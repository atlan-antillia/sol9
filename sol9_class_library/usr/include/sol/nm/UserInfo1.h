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
 *  UserInfo1.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/UserInfo.h>

namespace SOL {

class UserInfo1 :public UserInfo {

public:
  UserInfo1()
  :UserInfo(1)
  {

  }

public:
/*
typedef struct _USER_INFO_1 {
  LPWSTR usri1_name;
  LPWSTR usri1_password;
  DWORD  usri1_password_age;
  DWORD  usri1_priv;
  LPWSTR usri1_home_dir;
  LPWSTR usri1_comment;
  DWORD  usri1_flags;
  LPWSTR usri1_script_path;
}USER_INFO_1, *PUSER_INFO_1, *LPUSER_INFO_1;
*/

  USER_INFO_1* getInfo()
  {
    return (USER_INFO_1*)getBuffer();
  }
public:
  void display()
  {
    USER_INFO_1* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("USER_INFO_1 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("Name: %S\n", ptr->usri1_name);

        printf("Pasword: %S\n", ptr->usri1_password);
        printf("PasswordAge: %d\n", ptr->usri1_password_age);
        printf("Privilage: %d\n", ptr->usri1_priv);
        printf("HomeDir: %S\n", ptr->usri1_home_dir);
        printf("Comment: %S\n", ptr->usri1_comment);
        printf("Flags: %d\n", ptr->usri1_flags);
        printf("ScriptPath: %S\n", ptr->usri1_script_path);
        printf("\n");
      }
      ptr++;  
    }
  }
};

}
