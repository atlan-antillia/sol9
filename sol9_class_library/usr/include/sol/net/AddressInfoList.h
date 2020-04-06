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
 *  AddressInfoList.h
 *
 *****************************************************************************/


// SOL9
// 2010/11/20

#pragma once

#include <sol/Object.h>

#include <sol/Exception.h>
#include <sol/net/IPv4Address.h>
#include <sol/net/IPv6Address.h>
#include <sol/net/IPv4AddressInfo.h>
#include <sol/net/IPv6AddressInfo.h>

/*
typedef struct addrinfo {
  int             ai_flags;
  int             ai_family;
  int             ai_socktype;
  int             ai_protocol;
  size_t          ai_addrlen;
  char            *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
} ADDRINFOA, *PADDRINFOA;
*/

namespace SOL {

class AddressInfoList :public Object {
private:
  ADDRINFOT *info;

public:
  AddressInfoList()
  :info(NULL)
  {
  }

public:
  ~AddressInfoList()
  {
    clear();
  }

public:
  void clear()
  {
    if (info) {
      FreeAddrInfo(info);
      info = NULL;
    }
  }


public:
  /**
   * Get AddressInformation by calling Windows API getaddrinfo.
   * This returns the number of entries of a list of the addresses obtained.
   */
  int getAddrInfo(__in const TCHAR*ipaddr, __in_opt const TCHAR* service=NULL, __in_opt ADDRINFOT* hints=NULL)
  {
    clear();

    int ai_err = GetAddrInfo(ipaddr, service, hints, &info);
    if (ai_err) {
      throw Exception(ai_err, gai_strerror(ai_err));      
    }
    return getCount();
  }

public:
  /**
   * Return n-th pointer to addrinfo structure where n=>0 and n <count.
   */
  const ADDRINFOT* getNth(int n)
  {
    int i = 0;
    ADDRINFOT* ptr = NULL;
    int count = getCount();
    if (n < 0 || n >= count) {
      throw Exception("Index is out of range");
    }
      for(ptr = this->info; ptr!= NULL; ptr=ptr->ai_next) {
      if (i == n) {
        break;
      }    
      i++;
    }
    return ptr;
  }  


public:
  /**
   * Return a copy of AddressInfo of n-th entry of addrinfo structure where n=>0 and n <count.
   */
  const ADDRINFOT* getNth(__in int n, __out AddressInfo& addressInfo)
  {
    int i = 0;
    ADDRINFOT* ptr = NULL;
    int count = getCount();
    if (n < 0 || n >= count) {
      throw Exception("Index is out of range");
    }
      for(ptr = this->info; ptr!= NULL; ptr=ptr->ai_next) {
      if (i == n) {
        break;
      }    
      i++;
    }
    addressInfo.copy(ptr);

    return ptr;
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
  void display(__in const sockaddr_in* ipv4) const
  {
    if (ipv4) {
      _tprintf(_T("IPv4 family: %d\n"), ipv4->sin_family);
      _tprintf(_T("IPv4 port: %d\n"), ipv4->sin_port);
      IPv4Address ipv4addr;
      TCHAR string[128];
      //memset(string, 0, sizeof(string));
      if (ipv4addr.toString(&(ipv4->sin_addr), string)) {
        _tprintf(_T("IPv4 address: %s\n"), string);
      }
    }
  }
/*
struct sockaddr_in6 {
        short   sin6_family;
        u_short sin6_port;
        u_long  sin6_flowinfo;
        struct  in6_addr sin6_addr;
        u_long  sin6_scope_id;
};
*/

public:
  void display(__in const sockaddr_in6* ipv6) const
  {
    if (ipv6) {
      _tprintf(_T("IPv6 family: %d\n"), ipv6->sin6_family);
      _tprintf(_T("IPv6 port: %d\n"), ipv6->sin6_port);
      _tprintf(_T("IPv6 flowinfo: %ld\n"), ipv6->sin6_flowinfo);

      IPv6Address ipv6addr;
      TCHAR string[128];
      //memset(string, 0, sizeof(string));
      if (ipv6addr.toString(&(ipv6->sin6_addr), string)) {
        _tprintf(_T("IPv6 address: %s\n"), string);
      }
      _tprintf(_T("IPv6 scopeid: %ld\n"), ipv6->sin6_scope_id);
    }
  }

public:
  void display(__in const ADDRINFOT* ptr)
  {
    if (ptr) {
      AddressInfo info(ptr);
      info.display();
    }
  }


public:
  void display()
  {
    ADDRINFOT* ptr = NULL;  
    for(ptr = info; ptr!= NULL; ptr=ptr->ai_next) {
      display(ptr);
      _tprintf(_T("\n"));
    }      
  }  

public:
  int getCount()
  {    
    int count = 0;
    ADDRINFOT* ptr = NULL;
    for(ptr = info; ptr!= NULL; ptr=ptr->ai_next) {
      if (ptr) {
        count++;
      }
    }
    return count;
  }  
};

}

