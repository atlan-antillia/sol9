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
 *  ShareInfo1.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/ShareInfo.h>

namespace SOL {

class ShareInfo1 :public ShareInfo {

public:
  ShareInfo1()
  :ShareInfo(1)
  {

  }


public:
/*
typedef struct _SHARE_INFO_1 {
  LPWSTR shi1_netname;
  DWORD  shi1_type;
  LPWSTR shi1_remark;
} SHARE_INFO_1, *PSHARE_INFO_1, *LPSHARE_INFO_1;
*/

  SHARE_INFO_1* getInfo()
  {
    return (SHARE_INFO_1*)getBuffer();
  }

public:
  void display()
  {
    SHARE_INFO_1* ptr = getInfo();
  
    int count = getEntriesRead();
    printf("SHARE_INFO_1 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("NetName: %S\n", ptr->shi1_netname);
        printf("Type: %d\n",  ptr->shi1_type);
         printf("Remark: %S\n", ptr->shi1_remark);
        printf("\n");
      }
      ptr++;
    }
  }
};


}
