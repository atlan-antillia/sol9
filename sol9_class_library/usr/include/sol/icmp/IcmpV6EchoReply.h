/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IcmpV6EchoReply.h
 *
 *****************************************************************************/

// SOL9
// 2010/08/27

#pragma once
#include <sol/Object.h>
#include <icmpapi.h>
#include <sol/String.h>

#pragma comment(lib, "iphlpapi.lib")

/*
struct sockaddr_in6 {
    sa_family_t     sin6_family;   
    in_port_t       sin6_port;     
    uint32_t        sin6_flowinfo; 
    struct in6_addr sin6_addr;     
    uint32_t        sin6_scope_id;
};

typedef struct in6_addr {
  union {
    u_char  Byte[16];
    u_short Word[8];
  } u;
} IN6_ADDR, *PIN6_ADDR, FAR *LPIN6_ADDR;

typedef struct _IPV6_ADDRESS_EX_LH {
  USHORT sin6_port;
  ULONG  sin6_flowinfo;
  USHORT sin6_addr[8];
  ULONG  sin6_scope_id;
} IPV6_ADDRESS_EX, *PIPV6_ADDRESS_EX;

typedef struct icmpv6_echo_reply_lh {
  IPV6_ADDRESS_EX Address;
  ULONG           Status;
  unsigned int    RoundTripTime;
} ICMPV6_ECHO_REPLY, *PICMPV6_ECHO_REPLY;

*/

namespace SOL {
 
class IcmpV6EchoReply :public Object {
private:
  PICMPV6_ECHO_REPLY pIcmpEchoReply;

private:
  DWORD replySize;

public:
  IcmpV6EchoReply()
    :pIcmpEchoReply(NULL),
    replySize(0)
  {
  }


public:
  ~IcmpV6EchoReply()
  {
    if (pIcmpEchoReply) {
      delete [] (char*) pIcmpEchoReply;
      pIcmpEchoReply = NULL;
    }
  }

public:
  void* alloc(int dataSize, DWORD& bufferLen)
  {
    bufferLen = sizeof(ICMPV6_ECHO_REPLY) + dataSize;
    replySize = bufferLen;

    void* replyBuffer = new char[bufferLen];
    memset(replyBuffer, 0, bufferLen);

    pIcmpEchoReply = (PICMPV6_ECHO_REPLY)replyBuffer;
    return replyBuffer;
  }

public:
  ULONG getStatus()
  {
    return pIcmpEchoReply->Status;
  }

public:
  ULONG getStatus(String& status)
  {
       switch (pIcmpEchoReply->Status) {
        case IP_DEST_HOST_UNREACHABLE:
            status = "Destination host was unreachable";
            break;
        case IP_DEST_NET_UNREACHABLE:
            status = "Destination Network was unreachabl";
            break;
        case IP_REQ_TIMED_OUT:
            status = "Request timed out";
            break;
        default:
            status = "";
            break;
        }
    return pIcmpEchoReply->Status;
  }

public:
  ULONG getRoundTripTime()
  {
    return pIcmpEchoReply->RoundTripTime;
  }


public:
  USHORT* getReplyAddr(int& size)
  {
    size = 8;
    return pIcmpEchoReply->Address.sin6_addr;
  }

public:
  void* getReplyBuffer()
  {
    return (void*) pIcmpEchoReply;
  }

public:
  DWORD getReplySize()
  {
    return replySize;
  }

public:
  DWORD parse()
  {
    return Icmp6ParseReplies(getReplyBuffer(), getReplySize()); 
  }
public:
  USHORT getPort()
  {
    return pIcmpEchoReply->Address.sin6_port;
  }

public:
  USHORT* getAddress(int& size)
  {
    size = 8;
    return pIcmpEchoReply->Address.sin6_addr;
  }

public:
  ULONG getFlowInfo()
  {
    return pIcmpEchoReply->Address.sin6_flowinfo;
  }

public:
  ULONG getScopeId()
  {
    return pIcmpEchoReply->Address.sin6_scope_id;
  }


public:
  void display()
  {
    String strStatus;
    ULONG status = getStatus(strStatus);

    //ULONG roundTripTime = getRoundTripTime();

    printf("Status       : %d %s\n",  status, (const char*)strStatus);
    printf("RoundTripTime: %d\n",  getRoundTripTime() );
    printf("Address port    : %d\n", getPort() );
    printf("Address flowInfo: %ld\n", getFlowInfo() );
    printf("Address address : ");
    int size = 0;
    USHORT* addr = getAddress(size);
    for (int i = 0; i<size; i++) {
      printf("%d ", addr[i]);
    }
    printf("\n");
    printf("Address scope   : %ld\n", getScopeId() );
  }

};


}
