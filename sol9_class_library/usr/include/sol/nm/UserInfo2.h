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
 *  UserInfo2.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/UserInfo.h>

namespace SOL {

class UserInfo2 :public UserInfo {

public:
  UserInfo2()
  :UserInfo(2)
  {

  }

public:
/*
typedef struct _USER_INFO_2 {
  LPWSTR usri2_name;
  LPWSTR usri2_password;
  DWORD  usri2_password_age;
  DWORD  usri2_priv;
  LPWSTR usri2_home_dir;
  LPWSTR usri2_comment;
  DWORD  usri2_flags;
  LPWSTR usri2_script_path;
  DWORD  usri2_auth_flags;
  LPWSTR usri2_full_name;
  LPWSTR usri2_usr_comment;
  LPWSTR usri2_parms;
  LPWSTR usri2_workstations;
  DWORD  usri2_last_logon;
  DWORD  usri2_last_logoff;
  DWORD  usri2_acct_expires;
  DWORD  usri2_max_storage;
  DWORD  usri2_units_per_week;
  PBYTE  usri2_logon_hours;
  DWORD  usri2_bad_pw_count;
  DWORD  usri2_num_logons;
  LPWSTR usri2_logon_server;
  DWORD  usri2_country_code;
  DWORD  usri2_code_page;
}USER_INFO_2, *PUSER_INFO_2, *LPUSER_INFO_2;
*/

  USER_INFO_2* getInfo()
  {
    return (USER_INFO_2*)getBuffer();
  }
  /*
  usri2_logon_hours
Pointer to a 21-byte (168 bits) bit string that specifies the times during which the user can log on. Each bit represents a unique hour in the week, in Greenwich Mean Time (GMT). 

The first bit (bit 0, word 0) is Sunday, 0:00 to 0:59; the second bit (bit 1, word 0) is Sunday, 1:00 to 1:59; and so on. Note that bit 0 in word 0 represents Sunday from 0:00 to 0:59 only if you are in the GMT time zone. In all other cases you must adjust the bits according to your time zone offset (for example, GMT minus 8 hours for Pacific Standard Time).

Specify a NULL pointer in this member when calling the NetUserAdd function to indicate no time restriction. Specify a NULL pointer when calling the NetUserSetInfo function to indicate that no change is to be made to the times during which the user can log on.

   */
public:
  void display()
  {
    USER_INFO_2* ptr = getInfo();
    
      int count = getEntriesRead();
      printf("USER_INFO_2 count=%d\n", count);
      for (int i = 0; i<count; i++) {
        if (ptr) {
          printf("Name: %S\n", ptr->usri2_name);

          printf("Pasword: %S\n", ptr->usri2_password);
          printf("PasswordAge: %d\n", ptr->usri2_password_age);

          printf("Privilage: %d\n", ptr->usri2_priv);
          printf("HomeDir: %S\n", ptr->usri2_home_dir);
          printf("Comment: %S\n", ptr->usri2_comment);
          printf("Flags: %d\n", ptr->usri2_flags);
          printf("ScriptPath: %S\n", ptr->usri2_script_path);

          printf("AuthFlags: %d\n", ptr->usri2_auth_flags);
          printf("FullName: %S\n", ptr->usri2_full_name);
          printf("UserComment: %S\n", ptr->usri2_usr_comment);
          printf("Parms: %S\n", ptr->usri2_parms);
          printf("WorkStation: %S\n", ptr->usri2_workstations);
          printf("LastLogon: %d\n", ptr->usri2_last_logon);
          printf("LastLogOff: %d\n", ptr->usri2_last_logoff);
          printf("AccountExpire: %d\n", ptr->usri2_acct_expires);
          printf("MaxStorage: %d\n", ptr->usri2_max_storage);
          printf("UnitsPerWeek: %d\n", ptr->usri2_units_per_week);
          printf("LogonHours: %p\n", ptr->usri2_logon_hours);
          printf("BadPasswordCount: %d\n", ptr->usri2_bad_pw_count);
          printf("NumLogons: %d\n", ptr->usri2_num_logons);
          printf("LogonServer: %S\n", ptr->usri2_logon_server);
          printf("CountryCode: %d\n", ptr->usri2_country_code);
          printf("CodePage: %d\n", ptr->usri2_code_page);
          printf("\n");
        }
        ptr++;
      }
  }
};

}
