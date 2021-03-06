/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IPv4AddressInfoList.h
 *
 *****************************************************************************/


// SOL9
// 2010/11/20

#pragma once
#include <sol/net/AddressInfoList.h>

#include <sol/net/IPv4AddressInfo.h>


namespace SOL {

class IPv4AddressInfoList :public AddressInfoList {

public:
  IPv4AddressInfoList()
  {

  }

public:
  ~IPv4AddressInfoList()
  {
  }


public:
  /**
   * Get AddressInformation by calling Windows API getaddrinfo.
   * This returns the number of entries of a list of the addresses obtained.
   */
  int getAddrInfo(__in const TCHAR*ipaddr, __in_opt const TCHAR* service=NULL)
  {
    ADDRINFOT hints;
    memset(&hints, 0, sizeof(hints));
    //hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_INET;
    return AddressInfoList::getAddrInfo(ipaddr, service, &hints);
  }

public:
  /**
   * Get a copy of IPv4AddressInfo in the first addrinfo.  
   */
  bool getFirst(__out IPv4AddressInfo& info) 
  {
    return getNth(0, info);
  }

public:
  /**
   * Get a copy of IPv4AddressInfo in n-th addrinfo.  
   */
  bool getNth(__in const int n, __out IPv4AddressInfo& info) 
  {
    bool rc = false;
    const ADDRINFOT* ptr = AddressInfoList::getNth(n);
    if (ptr && ptr->ai_family == AF_INET) {
      info.copy(ptr);
      rc = true;
    }
    return rc;
  }

public:
  /**
   * Get a copy of IPv4 sockaddr_in in the first addrinfo.  
   */
  bool getFirst(__out sockaddr_in& sockaddr) 
  {
    return getNth(0, sockaddr);
  }


public:
  /**
   * Get a copy of IPv4 sockaddr_in in n-th addrinfo.  
   */
  bool getNth(__in const int n, __out sockaddr_in& sockaddr) 
  {
    bool rc = false;
    const ADDRINFOT* ptr = AddressInfoList::getNth(n);
    if (ptr && ptr->ai_family == AF_INET) {
      sockaddr_in* addr = (sockaddr_in*) ptr->ai_addr;
      if (addr) {
        memcpy(&sockaddr, addr, sizeof(sockaddr));
        rc = true;
      }
    }
    return rc;
  }

/*
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
*/
public:
  /**
   * Get a in_addr of IPv4 sockaddr_in in the first addrinfo.  
   */
  bool getFirst(__out in_addr& addr) 
  {
    return getNth(0, addr);

  }

public:
  /**
   * Get a in_addr of IPv4 sockaddr_in in n-th addrinfo.  
   */
  bool getNth(__in const int n, __out in_addr& addr) 
  {
    bool rc = false;
    const ADDRINFOT* ptr = AddressInfoList::getNth(n);
    if (ptr && ptr->ai_family == AF_INET) {
      sockaddr_in* sockaddr = (sockaddr_in*) ptr->ai_addr;
      if (sockaddr) {
        memcpy(&addr, &sockaddr->sin_addr, sizeof(addr));
        rc = true;
      }
    }
    return rc;
  }
};

}

