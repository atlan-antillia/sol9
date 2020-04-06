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
 *  InetSockAddress.h
 *
 *****************************************************************************/

// SOL9
// 2010/12/20

#pragma once

#include <sol/Object.h>
#include <sol/net/IPv4Address.h>
#include <sol/net/IPv6Address.h>


namespace SOL {

/*
struct sockaddr {
  u_short    sa_family;
  char       sa_data[14];
};

struct sockaddr_in{
   short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};

typedef struct sockaddr_in6 {
  ADDRESS_FAMILY  sin6_family;
  USHORT  sin6_port;
  ULONG  sin6_flowinfo;
  IN6_ADDR  sin6_addr;
  union {
    ULONG  sin6_scope_id;
    SCOPE_ID  sin6_scope_struct;
   };
};

typedef union _SOCKADDR_INET {
  SOCKADDR_IN    Ipv4;
  SOCKADDR_IN6   Ipv6;
  ADDRESS_FAMILY si_family;
}SOCKADDR_INET, *PSOCKADDR_INET;
*/

class InetSockAddress :public Object {

private:
  sockaddr_in    ipv4;

private:
  sockaddr_in6   ipv6;

private:
  ADDRESS_FAMILY family;

public:
  InetSockAddress()
  {
    memset(&ipv4, 0, sizeof(ipv4));
    memset(&ipv6, 0, sizeof(ipv6));
    family= 0;
  }

public:
  InetSockAddress(__in sockaddr_in& addr)
  {
    memset(&ipv6, 0, sizeof(ipv6));
    copy(&addr);
  }


public:
  InetSockAddress(sockaddr_in6& addr)
  {
    memset(&ipv4, 0, sizeof(ipv4));
    copy(&addr);
  }


public:
  InetSockAddress(__in sockaddr* addr)
  {
    memset(&ipv4, 0, sizeof(ipv4));
    memset(&ipv6, 0, sizeof(ipv6));
    copy(addr);
  }

public:
  void copy(__in sockaddr* addr) 
  {
    if (addr) {
      if (addr->sa_family == AF_INET) {
        copy((sockaddr_in*)addr);
      }
      if (addr->sa_family == AF_INET6) {
        copy((sockaddr_in6*)addr);
      }
    }
  }

public:
  InetSockAddress(__in sockaddr_in* addr)
  {
    memset(&ipv6, 0, sizeof(ipv6));
    copy(addr);
  }


public:
  InetSockAddress(sockaddr_in6* addr)
  {
    memset(&ipv4, 0, sizeof(ipv4));
    copy(addr);
  }

public:
  ~InetSockAddress()
  {
  }

public:
  InetSockAddress& operator=(__in const sockaddr_in& addr)
  { 
    copy(&addr);
    return *this;
  }

public:
  InetSockAddress& operator=(__in const sockaddr_in6& addr)
  { 
    copy(&addr);
    return *this;
  }

public:
  InetSockAddress& operator=(__in const sockaddr_in* addr)
  { 
    copy(addr);
    return *this;
  }

public:
  InetSockAddress& operator=(__in const sockaddr_in6* addr)
  { 
    copy(addr);
    return *this;
  }

public:
  void copy(__in const sockaddr_in* addr)
  {
    if (addr) {
      memcpy(&ipv4, addr, sizeof(ipv4));
      family= AF_INET;
    }
  }


public:
  void copy(__in const sockaddr_in6* addr)
  {
    if (addr) {
      memcpy(&ipv6, addr, sizeof(ipv6));
      family= AF_INET6;
    }
  }

public:
  operator const sockaddr_in*() const
  {
    return &ipv4;
  }

public:
  operator const sockaddr_in6*() const
  {
    return &ipv6;
  }

public:
  ADDRESS_FAMILY getFamily()
  {
    return family;
  }

public:
  const sockaddr_in& getIPv4Address()
  {
    return ipv4;
  }

public:
  const sockaddr_in6& getIPv6Address()
  {      
    return ipv6;
  }

public:
  bool isIPv4()
  {
    bool rc = false;
    if (family == AF_INET) {
      rc = true;
    }
    return rc;
  }


public:
  bool isIPv6()
  {
    bool rc = false;
    if (family == AF_INET6) {
      rc = true;
    }
    return rc;
  }

/*
struct in_addr {
  union {
          struct { u_char s_b1,s_b2,s_b3,s_b4; }   S_un_b;
          struct { u_short s_w1,s_w2; }            S_un_w;
          u_long                                   S_addr;
  } S_un;
};
*/
public:
  bool getIPv4Address(__out unsigned short& port, __out in_addr& addr)
  {
    bool rc = false;
    if (family == AF_INET) {
      port = ipv4.sin_port;
      memcpy(&addr, &(ipv4.sin_addr), sizeof(addr));
      rc = true;
     }
    return rc;
  }

/*
typedef struct in6_addr {
  union {
      u_char Byte[16];
      u_short Word[8];
  } u;
} in6_addr;
*/
public:
  bool getIPv6Address(__out unsigned short& port, __out in6_addr& addr)
  {
    bool rc = false;
    if (family == AF_INET6) {
      port = ipv6.sin6_port;
      memcpy(&addr, &(ipv6.sin6_addr), sizeof(addr));
      rc = true;
     }
    return rc;
  }

public:
  void display()
  {
    _tprintf(_T("Family : %d\n"), family);
    unsigned short port;
    if (family == AF_INET) {
      in_addr v4addr;
      getIPv4Address(port, v4addr);
      IPv4Address ipv4address(&v4addr);
      StringT<TCHAR> string;
      ipv4address.toString(string);
      _tprintf(_T("IPv4: %d  %s\n"), port, (const TCHAR*)string);
    }
    if (family == AF_INET6) {
      in6_addr v6addr;
      getIPv6Address(port, v6addr);  
      IPv6Address ipv6address(&v6addr);
      StringT<TCHAR> string;
      ipv6address.toString(string);
      _tprintf(_T("IPv6: %d  %s\n"), port, (const TCHAR*)string);
      
    }

  }

};

}
