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
 *  ServerTransportInfo0.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/ServerTransportInfo.h>

namespace SOL {

class ServerTransportInfo0 :public ServerTransportInfo {

public:
  ServerTransportInfo0()
  :ServerTransportInfo(0)
  {

  }

public:
/*
typedef struct _SERVER_TRANSPORT_INFO_0 {
  DWORD  svti0_numberofvcs;
  LMSTR  svti0_transportname;
  LPBYTE svti0_transportaddress;
  DWORD  svti0_transportaddresslength;
  LMSTR  svti0_networkaddress;
}SERVER_TRANSPORT_INFO_0, *PSERVER_TRANSPORT_INFO_0, *LPSERVER_TRANSPORT_INFO_0;
*/
  SERVER_TRANSPORT_INFO_0* getInfo()
  {
    return (SERVER_TRANSPORT_INFO_0*)getBuffer();
  }

public:
  void display()
  {
    SERVER_TRANSPORT_INFO_0* ptr = getInfo();
    
    int count = getEntriesRead();
    printf("SERVER_TRANSPORT_INFO_0 count=%d\n", count);
    for (int i = 0; i<count; i++) {
      if (ptr) {
        printf("NumberOfVCS: %d\n", ptr->svti0_numberofvcs);
        printf("TransportName: %S\n", ptr->svti0_transportname);
        LPBYTE  bytes = ptr->svti0_transportaddress;
        for (int n = 0; n< ptr->svti0_transportaddresslength; n++) {
          printf("0x%02x ", *bytes++);
        }
        printf("\n");
        printf("NetworkAddress: %S\n", ptr->svti0_networkaddress);
        printf("\n");
      }
      ptr++;
    }
  }
};

}
