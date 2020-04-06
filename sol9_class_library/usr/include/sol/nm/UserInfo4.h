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
 *  UserInfo4.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/UserInfo.h>

namespace SOL {

class UserInfo4 :public UserInfo {

public:
  UserInfo4()
  :UserInfo(4)
  {

  }

public:
/*
typedef struct _USER_INFO_4 {
  LPWSTR usri4_name;
  LPWSTR usri4_password;
  DWORD  usri4_password_age;
  DWORD  usri4_priv;
  LPWSTR usri4_home_dir;
  LPWSTR usri4_comment;
  DWORD  usri4_flags;
  LPWSTR usri4_script_path;
  DWORD  usri4_auth_flags;
  LPWSTR usri4_full_name;
  LPWSTR usri4_usr_comment;
  LPWSTR usri4_parms;
  LPWSTR usri4_workstations;
  DWORD  usri4_last_logon;
  DWORD  usri4_last_logoff;
  DWORD  usri4_acct_expires;
  DWORD  usri4_max_storage;
  DWORD  usri4_units_per_week;
  PBYTE  usri4_logon_hours;
  DWORD  usri4_bad_pw_count;
  DWORD  usri4_num_logons;
  LPWSTR usri4_logon_server;
  DWORD  usri4_country_code;
  DWORD  usri4_code_page; //USER_INFO_2

  PSID   usri4_user_sid;
  DWORD  usri4_primary_group_id;
  LPWSTR usri4_profile;
  LPWSTR usri4_home_dir_drive;
  DWORD  usri4_password_expired;
}USER_INFO_4, *PUSER_INFO_4, *LPUSER_INFO_4;

*/

  USER_INFO_4* getInfo()
  {
    return (USER_INFO_4*)getBuffer();
  }

  /*
  usri4_logon_hours
  Pointer to a 21-byte (168 bits) bit string that specifies the times during 
  which the user can log on. Each bit represents a unique hour in the week, in Greenwich Mean Time (GMT). 

  The first bit (bit 0, word 0) is Sunday, 0:00 to 0:59; the second bit (bit 1, word 0) is Sunday,
  1:00 to 1:59; and so on. Note that bit 0 in word 0 represents Sunday from 0:00 to 0:59 only if you are in the GMT time zone. In all other cases you must adjust the bits 
  according to your time zone offset (for example, GMT minus 8 hours for Pacific Standard Time).

  Specify a NULL pointer in this member when calling the NetUserAdd function to indicate no time restriction. 
  Specify a NULL pointer when calling the NetUserSetInfo function to indicate that no change is to be made to the times during which the user can log on.

   */

public:
  void display()
  {
    USER_INFO_4* ptr = getInfo();
    
      int count = getEntriesRead();
      printf("USER_INFO_4 count=%d\n", count);
      for (int i = 0; i<count; i++) {
        if (ptr) {
          printf("Name: %S\n", ptr->usri4_name);

          printf("Pasword: %S\n", ptr->usri4_password);
          printf("PasswordAge: %d\n", ptr->usri4_password_age);

          printf("Privilage: %d\n", ptr->usri4_priv);
          printf("HomeDir: %S\n", ptr->usri4_home_dir);
          printf("Comment: %S\n", ptr->usri4_comment);
          printf("Flags: %d\n", ptr->usri4_flags);
          printf("ScriptPath: %S\n", ptr->usri4_script_path);

          printf("AuthFlags: %d\n", ptr->usri4_auth_flags);
          printf("FullName: %S\n", ptr->usri4_full_name);
          printf("UserComment: %S\n", ptr->usri4_usr_comment);
          printf("Parms: %S\n", ptr->usri4_parms);
          printf("WorkStation: %S\n", ptr->usri4_workstations);
          printf("LastLogon: %d\n", ptr->usri4_last_logon);
          printf("LastLogOff: %d\n", ptr->usri4_last_logoff);
          printf("AccountExpire: %d\n", ptr->usri4_acct_expires);
          printf("MaxStorage: %d\n", ptr->usri4_max_storage);
          printf("UnitsPerWeek: %d\n", ptr->usri4_units_per_week);
          printf("LogonHours: %d\n", ptr->usri4_logon_hours);

          printf("BadPasswordCount: %d\n", ptr->usri4_bad_pw_count);
          printf("NumLogons: %d\n", ptr->usri4_num_logons);
          printf("LogonServer: %S\n", ptr->usri4_logon_server);
          printf("CountryCode: %d\n", ptr->usri4_country_code);
          printf("CodePage: %d\n", ptr->usri4_code_page);
          
          //printf("SID: %s\n",  ptr->usri4_user_sid);
          //PSID   usri4_user_sid;
          printf("PrimaryGroupId: %d\n", ptr->usri4_primary_group_id);
          printf("Profile: %S\n", ptr->usri4_profile);
          printf("HomeDirDrive: %S\n", ptr-> usri4_home_dir_drive);
          printf("PasswordExpired: %d\n", ptr->usri4_password_expired);

          printf("\n");
        }
        ptr++;
      }
  }
};

}
