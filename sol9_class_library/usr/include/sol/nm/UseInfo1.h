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
 *  UseInfo0.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/UseInfo.h>

namespace SOL {

class UseInfo1 :public UseInfo {

public:
  UseInfo1()
  :UseInfo(1)
  {

  }

public:
/*
typedef struct _USE_INFO_1 {
  LMSTR ui1_local;
  LMSTR ui1_remote;
  LMSTR ui1_password;
  DWORD ui1_status;
  DWORD ui1_asg_type;
  DWORD ui1_refcount;
  DWORD ui1_usecount;
}USE_INFO_1, *PUSE_INFO_1, *LPUSE_INFO_1;
*/
  USE_INFO_1* getInfo()
  {
    return (USE_INFO_1*)getBuffer();
  }
public:
  void display()
  {
    USE_INFO_1* ptr = getInfo();
    
    int count = getEntriesRead();
    printf("USE_INFO_1 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("Local: %S\n", ptr->ui1_local);
        printf("Remote: %S\n", ptr->ui1_remote);
        printf("Passwor: %S\n", ptr->ui1_password);
        printf("Status: %d\n", ptr->ui1_status);
        printf("AsgType: %d\n", ptr->ui1_asg_type);
        printf("RefCount: %d\n", ptr->ui1_refcount);
        printf("UseCout: %d\n", ptr->ui1_usecount);
      }
      ptr++;
    }
  }
};

}
