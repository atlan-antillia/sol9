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
 *  SocketDatagram.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\Socket.h>
#include <sol\StringBuffer.h>

#include <sol\InetAddress.h>

namespace SOL {

class SocketDatagram :public Socket {
private:
  sockaddr_in sender;

public:
  /**
   *
   */
  SocketDatagram() 
    :Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
  {
    memset(&sender, 0, sizeof(sender));
  }

public:
  /**
   * Given socket from caller, and simply set it to a member of this class
   */
  SocketDatagram(SOCKET soc) 
    :Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
  {
    setSocket(soc);
    memset(&sender, 0, sizeof(sender));
  }

public:
  /**
   *
   */
  ~SocketDatagram() 
  {
  }

public:
  /**
   *
   */
  int bind(unsigned short port) {

    SOCKET soc = getSocket();
    InetAddress inet(port);

    return ::bind(soc, (sockaddr*)inet.getAddress(), inet.getSize());
  }

public:
  /**
   *
   */
  int bind(const char* host, unsigned short port) {

    SOCKET soc = getSocket();
    InetAddress inet(host, port);
    return ::bind(soc, (sockaddr*)inet.getAddress(), inet.getSize());
  }

public:
  /**
   *
   */

  int bind(InetAddress& inet) {

    SOCKET soc = getSocket();
    return ::bind(soc, (sockaddr*)inet.getAddress(), inet.getSize());
  }

public:
  /**
   *
   */
  int enableBroadcast() {
    int enable = 1;
    setOption(SO_BROADCAST, (char*)enable, sizeof(enable));
  }

public:
  /**
   *
   */
  int sendTo(InetAddress& to, const char* buf, int len, int flag=0) {
    int rc = 0;
    if (buf && len>0) {
      sockaddr_in* addr = to.getAddress();
      int tolen = to.getSize();

      SOCKET soc = getSocket();
      rc = ::sendto(soc, buf, len, flag, 
        (sockaddr*)addr, tolen);
    }
    return rc;  
  }
public:
  /**
   *
   */
  int sendTo(const char* host, unsigned short port,
    const char* buf, int len, int flag =0) {
    int rc = 0;

    if (host && port>=0) {
      InetAddress to(host, port);
      rc = this->sendTo(to, buf, len, flag);
    }
    return rc;  
  }

public:
  int recvFrom(InetAddress& from, char* buf, int len, int flag=0) {
    int rc =0;
    if (buf && len>0) {
      SOCKET soc = getSocket();

      int fromLen= sizeof(this->sender);
      rc = ::recvfrom(soc, buf, len, flag, 
        (sockaddr*)&(this->sender), &fromLen);

      buf[len-1] = ZERO;
      if (rc >0 && rc<len) {
        buf[rc] = ZERO;  //Terminate by NULL.
      }
    }
    return rc;
  }


public:
  int recvFrom(unsigned short port, char* buf, int len, int flag=0) {
    int rc =0;
    if (port>=0) {
      InetAddress from(port);
      rc = recvFrom(from, buf, len, flag);
    }
    return rc;
  }

public:

  sockaddr_in* getSender() {
    return &sender;
  }

public:
  int replyTo(const char* buf, int len, int flag=0) {
    int rc = 0;
    if (buf && len>0) {
      sockaddr_in* addr = getSender();
      int tolen = sizeof(sockaddr_in);

      SOCKET soc = getSocket();
      rc = ::sendto(soc, buf, len, flag, 
        (sockaddr*)addr, tolen);
    }
    return rc;  
  }
};

}


