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
 *  IcmpEchoReply.h
 *
 *****************************************************************************/

// SOL9
// 2010/08/27

#pragma once
#include <sol/Object.h>
#include <icmpapi.h>
#include <sol/String.h>

/*
typedef struct icmp_echo_reply {
  IPAddr                       Address;
  ULONG                        Status;
  ULONG                        RoundTripTime;
  USHORT                       DataSize;
  USHORT                       Reserved;
  PVOID                        Data;
  struct ip_option_information Options;
} ICMP_ECHO_REPLY, *PICMP_ECHO_REPLY;
*/

namespace SOL {
 
class IcmpEchoReply :public Object {
private:
  PICMP_ECHO_REPLY pIcmpEchoReply;
private:
  DWORD replySize;

public:
  IcmpEchoReply()
    :pIcmpEchoReply(NULL),
    replySize(0)
  {
  }


public:
  ~IcmpEchoReply()
  {
    if (pIcmpEchoReply) {
      delete [] (char*) pIcmpEchoReply;
      pIcmpEchoReply = NULL;
    }
  }

public:
  void* alloc(int dataSize, DWORD& bufferLen)
  {
    bufferLen = sizeof(ICMP_ECHO_REPLY) + dataSize;
    replySize = bufferLen;

    void* replyBuffer = new char[bufferLen];
    memset(replyBuffer, 0, bufferLen);

    pIcmpEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
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
  USHORT getDataSize(){
    return pIcmpEchoReply->DataSize;
  }

public:
  char* getData() {
    return (char*)pIcmpEchoReply->Data;
  }

public:
  in_addr getReplyAddr()
  {
    struct in_addr replyAddr;
    replyAddr.S_un.S_addr = pIcmpEchoReply->Address;
    return replyAddr;
  }

public:
  void getReplyAddr(String& addr)
  {
    in_addr replyAddr = getReplyAddr();
    addr =  inet_ntoa(replyAddr);
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
    return IcmpParseReplies(getReplyBuffer(), getReplySize()); 
  }

public:
  void display()
  {
    String strStatus;
    ULONG status = getStatus(strStatus);
    String addr;
    getReplyAddr(addr);

    char* data = getData();
    ULONG roundTripTime = getRoundTripTime();

    printf("Status       : %d %s\n", status, (const char*)strStatus);
    printf("ReplyAddress : %s\n", (const char*)addr);
    printf("RoundTripTime: %d\n", roundTripTime);
    printf("Data         : %s\n", data);

  }

};


}
