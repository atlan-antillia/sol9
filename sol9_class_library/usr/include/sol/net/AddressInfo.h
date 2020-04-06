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
 *  AddressInfo.h
 *
 *****************************************************************************/


// SOL9<
// 2010/12/14

#pragma once

#include <sol/Object.h>
#include <sol/ArgT.h>
#include <sol/Exception.h>
#include <sol/StringT.h>
#include <sol/StringBufferT.h>
#include <sol/String.h>
#include <sol/net/IPv4Address.h>
#include <sol/net/IPv6Address.h>
#include <sol/net/SocketDefinition.h>

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

class AddressInfo :public Object {
private:
  int             ai_flags;
  int             ai_family;
  int             ai_socktype;
  int             ai_protocol;
  size_t          ai_addrlen;
  StringT<TCHAR>  ai_canonname;  
  sockaddr*    ai_addr;

public:
  /**
   * Constructor
   */
  AddressInfo(__in const ADDRINFOT* ptr=NULL)
    :ai_flags(0),
    ai_family(0),
    ai_socktype(0),
    ai_protocol(0),
    ai_addrlen(0),
    ai_canonname(_T("")),
    ai_addr(NULL)
  {
    copy(ptr);
  }

public:
  /**
   * Destructor
   */
  ~AddressInfo()
  {
    clear();
  }


protected:
  void clear()
  {
    ai_flags = 0;
    ai_family = 0;
    ai_socktype = 0;
    ai_protocol = 0;
    ai_addrlen = 0;
    ai_canonname = _T("");  

    if (ai_addr) {
      delete [] (char*)ai_addr;
      ai_addr = NULL;
    }
  }


public:
  virtual void copy(__in const ADDRINFOT* ptr=NULL)
  {
    if (ptr) {
      clear();

      ai_flags = ptr->ai_flags;
      ai_family = ptr->ai_family;
      ai_socktype = ptr->ai_socktype;
      ai_protocol = ptr->ai_protocol;
      ai_addrlen  = ptr->ai_addrlen;
      if (ptr->ai_canonname) {
        ai_canonname = ptr->ai_canonname;
      }
      
      if (ai_addrlen == sizeof(sockaddr_in) || ai_addrlen== sizeof(sockaddr_in6) ) {
        ai_addr = (sockaddr*) new char[ai_addrlen];
        memcpy(ai_addr, ptr->ai_addr, ai_addrlen);
      }
    }
  }

//Getters
public:
  int  getFlags() {
    return ai_flags;
  }

public:
  int  getFamily() {
    return ai_family;
  }

public:
  int  getSockType() {
    return ai_socktype;
  }

public:
  int  getProtocol() {
    return ai_protocol;
  }

public:
  size_t getAddrLen() {
    return ai_addrlen;
  }

public:
  const TCHAR* getCanonName() {
    return (const TCHAR*)ai_canonname;
  }

public:
  const sockaddr* getSockAddr() {
    return ai_addr;
  }

public:
  operator const sockaddr*() const
  {
    return ai_addr;
  }

  //Setters
public:
  void  setFlags(int flags) {
    ai_flags = flags;
  }

public:
  void  setFamily(int family) {
    ai_family = family;
  }

public:
  void  setSockType(int type) {
    ai_socktype = type;
  }

public:
  void  setProtocol(int protocol) {
    ai_protocol = protocol;
  }

public:
  void setSockAddr(__in sockaddr* addr, __in size_t addrlen) {
    if (ai_addr !=NULL && 
      (addrlen == sizeof(sockaddr_in) || addrlen== sizeof(sockaddr_in6)) ) {
      //Free previous ai_addr
      delete [] (char*)ai_addr;
      
      ai_addrlen = addrlen;
      //Aloc new sockaddr of size addrlen (sockaddr_in or sockaddr_in6 structure)
      ai_addr = (sockaddr*) new char[ai_addrlen];
      memcpy(ai_addr, addr, addrlen);
    }
  }

public:
  void display(__in sockaddr_in* address)
  {
    _tprintf(_T("IPv4 family: %d\n"), address->sin_family);
    //Print a port number in host-bytes-order
    _tprintf(_T("IPv4 port: %d\n"),   ntohs(address->sin_port));
    IPv4Address ipv4addr;
    TCHAR string[128];
    memset(string, (TCHAR)0, CountOf(string));
    if (ipv4addr.toString(&(address->sin_addr), string)) {
      _tprintf(_T("IPv4 address: %s\n"), string);
    }
  }

public:
  void display(__in sockaddr_in6* address)
  {
    _tprintf(_T("IPv6 family: %d\n"), address->sin6_family);
    //Print a port number in host-byte-order.
    _tprintf(_T("IPv6 port: %d\n"),   ntohs(address->sin6_port));
    _tprintf(_T("IPv6 flowinfo: %ld\n"), address->sin6_flowinfo);
    
    IPv6Address ipv6addr;
    TCHAR string[128];
    memset(string, (TCHAR)0, CountOf(string));
    if (ipv6addr.toString(&(address->sin6_addr), string)) {
      _tprintf(_T("IPv6 address: %s\n"), string);
    }
    _tprintf(_T("IPv6 scopeid: %ld\n"), address->sin6_scope_id);
  }

public:
  bool isIPv4() 
  {
    bool rc = false;
    if (ai_addr) {
      if (ai_addrlen == sizeof(sockaddr_in)) {
        rc = true;
      }
    }
    return rc;
  }

public:
  bool isIPv6() 
  {
    bool rc = false;
    if (ai_addr) {
      if (ai_addrlen == sizeof(sockaddr_in6)) {
        rc = true;
      }
    }
    return rc;
  }

public:
  virtual void display()
  {
    StringT<TCHAR> flags;
    SocketDefinition sockDef;

    _tprintf(_T("Flags: 0x%x %s\n"), ai_flags, getFlags(ai_flags, flags));
    _tprintf(_T("Family: %s\n"),     sockDef.getFamily(ai_family));
    _tprintf(_T("SocketType: %s\n"), sockDef.getSocketType(ai_socktype));
    _tprintf(_T("Protocol: %s\n"),   sockDef.getProtocol(ai_protocol));
    _tprintf(_T("Length of sockaddr: %d\n"), ai_addrlen);
    _tprintf(_T("Canonical name: %s\n"),  (const TCHAR*)ai_canonname);
    if (ai_addr) {
      if (isIPv4()) {
        display((sockaddr_in*)ai_addr);
      }
      if (isIPv6()) {
        display((sockaddr_in6*)ai_addr);
      }
    }
    //printf("\n");
  }


private:
  const TCHAR* getFlags(__in int flags, __out StringT<TCHAR>& flagNames)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("Passive"),  AI_PASSIVE},
      {_T("Canonname"),  AI_CANONNAME},
      {_T("Numerichost"),  AI_NUMERICHOST}, 
      {_T("AddrConfig"),  AI_ADDRCONFIG},
      {_T("Nonauthoritative"), AI_NON_AUTHORITATIVE}, 
      {_T("Secure"),  AI_SECURE}, 
      {_T("Return preferred names"), AI_RETURN_PREFERRED_NAMES}
    };

    StringBufferT<TCHAR> buffer;
    int count = 0;
    for (int i =0; i<CountOf(names); i++) {
      if (flags & names[i].value) {
        if (count > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        count++;
      }
    }
    flagNames = buffer.getBuffer();

    return (const TCHAR*)flagNames;
  }
};

}

