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
 *  InetAddress.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol\StringT.h>

/**
 * InetAddress class
 */
namespace SOL {

class InetAddress :public Object {
private:
  sockaddr_in    address;
  StringT<char>  dottedAddress;  //1999.08.06

public:
  /**
   *
   */
  InetAddress() {
    memset(&address, 0, sizeof(address));
  }

public:
  /**
   * Given port(in host byte order) only as an argument, address is INADDR_ANY.
   */
  //2008/07/11
  InetAddress(unsigned short port) 
  {
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);  
    //INADDR_ANY is really a 0x00000000, so htonl(INADDR_ANY)=INADDR_ANY

    address.sin_port = htons(port);
  }

public:
  /**
   * @param host  Internet host name
   * @param port  Port number(in host byte order)
   */
  InetAddress(const char* host, unsigned short port) 
  {
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    if (host) {
      unsigned long addr = inet_addr(host);
      if(addr == INADDR_NONE) {
        HOSTENT* hostEnt = gethostbyname(host);
        if(hostEnt == NULL) {
          throw Exception("InetAddress#InetAddress,1,Error in resolving address", 0); 
        }
        address.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
      }
    } else {
      //If host were NULL, throw the followig IException
      throw InvalidArgumentException("InetAddress#InetAddress,2,host name is NULL", 0);
    }
    address.sin_port = htons(port);
  }

public:
  // The port and addr must be in host-byte-order.
  InetAddress(unsigned short port, unsigned long addr) 
  {
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);         //Convert the port to the network byte-order
    address.sin_addr.s_addr = htonl(addr);  //Convert the addr to the network-byte-order.
  }

  sockaddr_in*  getAddress() {
      return &address;
  }

  int      getSize() {
      return sizeof(address);
  }

  unsigned long getHostAddress() {
      return address.sin_addr.s_addr;
  }

  const char*     getDottedAddress() {
      dottedAddress = inet_ntoa(address.sin_addr);
      return (const char*)dottedAddress;
  }

  unsigned short  getPort() {
      return address.sin_port;
  }

  void  setAddress(unsigned long addr) {
      address.sin_addr.s_addr = addr;
      
  }
  void  setPort(unsigned short port) {
      address.sin_port = port;
  }
};

}

