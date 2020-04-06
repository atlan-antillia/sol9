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
 *  ShareInfo2.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/ShareInfo.h>

namespace SOL {


class ShareInfo2 :public ShareInfo {

public:
  ShareInfo2()
  :ShareInfo(2)
  {

  }

public:
/*
typedef struct _SHARE_INFO_2 {
  LPWSTR shi2_netname;
  DWORD  shi2_type;
  LPWSTR shi2_remark;
  DWORD  shi2_permissions;
  DWORD  shi2_max_uses;
  DWORD  shi2_current_uses;
  LPWSTR shi2_path;
  LPWSTR shi2_passwd;
} SHARE_INFO_2, *PSHARE_INFO_2, *LPSHARE_INFO_2;
*/

  SHARE_INFO_2* getInfo()
  {
    return (SHARE_INFO_2*)getBuffer();
  }


public:
  void display()
  {
    SHARE_INFO_2* ptr = getInfo();
    int count = getEntriesRead();
    printf("SHARE_INFO_2 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
         printf("NetName: %S\n", ptr->shi2_netname);
        printf("Type: %d\n",   ptr->shi2_type);
        printf("Remark: %S\n",   ptr->shi2_remark);
        printf("Permission: %d\n", ptr->shi2_permissions);
        printf("MaxUser: %d\n", ptr->shi2_max_uses);
        printf("CurrentUsers: %d\n", ptr->shi2_current_uses);
        printf("Path: %S\n", ptr->shi2_path);
          printf("Passowrd: %S\n", ptr->shi2_passwd);
        printf("\n");    
      }
      ptr++;
    }
  }
};  


}
