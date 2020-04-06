/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  NetworkParams.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/05

#pragma once
#include <sol/Object.h>
#include <sol/ArgT.h>


namespace SOL {

class NetworkParams: public Object {

/*
typedef struct {
  char            HostName[MAX_HOSTNAME_LEN + 4];
  char            DomainName[MAX_DOMAIN_NAME_LEN + 4];
  PIP_ADDR_STRING CurrentDnsServer;
  IP_ADDR_STRING  DnsServerList;
  UINT            NodeType;
  char            ScopeId[MAX_SCOPE_ID_LEN + 4];
  UINT            EnableRouting;
  UINT            EnableProxy;
  UINT            EnableDns;
}FIXED_INFO, *PFIXED_INFO;
*/
private:
  FIXED_INFO*  fixedInfo;

public:
  NetworkParams()
  :fixedInfo(NULL)
  {

  }

public:
  ~NetworkParams()
  {
    clear();
  }

public:
  void clear()
  {
    if (fixedInfo) {
      delete [] (char*)fixedInfo;
      fixedInfo = NULL;
    }
  }

public:
  bool getParams()
  {
    clear();

    bool rc = false;

    DWORD dwSize = 0;
    if (GetNetworkParams(NULL, &dwSize) == ERROR_BUFFER_OVERFLOW) {
      fixedInfo = (FIXED_INFO *) new char[dwSize];
      DWORD r = NO_ERROR;
      if ((r = GetNetworkParams(fixedInfo, &dwSize)) == NO_ERROR) {
           rc = true;
      } else {
        throw r;
      }
    }
    return rc;
  }

public:
  const char* getNodeType(int value)
  {
    static const ArgT<char> types[] = {
      {"Broadcast",    1},
      {"Peer to peer", 2},
      {"Mixed",        4},
      {"Hybrid",       8},
    };
    int count = XtNumber(types);
    const char* name = "";

    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }

    }
    return name;
  }

public:
  void display(FIXED_INFO* info)
  {
    printf("Host Name : %s\n", info -> HostName );
    printf("Domain Name : %s\n", info -> DomainName );

    // This parameter may be not used.
    //printf("Current DNS Server: %s\n", info->CurrentDnsServer);

    // DNS Server List
    printf("DNS Servers :\n");
    printf("\t%s\n", info -> DnsServerList.IpAddress.String );

    PIP_ADDR_STRING pIPAddr = info -> DnsServerList.Next;
    while ( pIPAddr ) {
          printf("\t%s\n", pIPAddr -> IpAddress.String );
          pIPAddr = pIPAddr -> Next;
    }

    printf("Node Type : %s\n", getNodeType(info->NodeType));

    printf("ScopeId : %s\n", info->ScopeId);
  
    printf("EnableRouting : %d\n", info->EnableRouting);
    printf("EnableProxy : %d\n", info->EnableProxy);
    printf("EnableDns : %d\n", info->EnableDns);

  }

public:
  void display()
  {
    if (fixedInfo == NULL) {
      getParams();
    }
    display(fixedInfo);

  }
};

}
