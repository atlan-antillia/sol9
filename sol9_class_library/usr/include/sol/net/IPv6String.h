/******************************************************************************
 *
 * Copyright (c) 2010-2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IPv6String.h
 *
 *****************************************************************************/

// SOL9
// 2010/09/01
// 2011/01/18 Fixed bugs on toAddress methods.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

#include <mstcpip.h>

namespace SOL {

/*
typedef struct in6_addr {
  union {
    u_char  Byte[16];
    u_short Word[8];
  } u;
} IN6_ADDR, *PIN6_ADDR, FAR *LPIN6_ADDR;

LONG NTAPI RtlIpv6StringToAddress(
  __in   PCTSTR S,
  __out  PCTSTR *Terminator,
  __out  IN6_ADDR *Addr
);

LONG NTAPI RtlIpv6StringToAddressEx(
  __in   PCTSTR AddressString,
  __out  IN6_ADDR *Address,
  __out  PULONG ScopeId,
  __out  PUSHORT Port
);

*/

typedef LONG (NTAPI *_Ipv6StringToAddress)(__in const TCHAR* addressString, __out TCHAR** terminator, __out IN6_ADDR *address);
typedef LONG (NTAPI *_Ipv6StringToAddressEx)(__in const TCHAR* addressString, __out IN6_ADDR *address, __out ULONG* scopeId, __out USHORT* port);

class IPv6String :public Object {

private:
  // For Ntdll.dll module
  HMODULE  hNtdll;

private:
  //Utility functions to convert a string to IPV6 Address (IN6_ADDR structure)
  _Ipv6StringToAddress   ipv6ToAddress;
  _Ipv6StringToAddressEx ipv6ToAddressEx;

public:
  /**
   * Constructor
   */
  IPv6String()
    :hNtdll(NULL),
    ipv6ToAddress(NULL),
    ipv6ToAddressEx(NULL)
  {
    hNtdll = LoadLibrary(_T("Ntdll.dll"));

    if (hNtdll) {
#ifdef UNICODE
      ipv6ToAddress   = (_Ipv6StringToAddress)GetProcAddress(hNtdll, "RtlIpv6StringToAddressW");
      ipv6ToAddressEx = (_Ipv6StringToAddressEx)GetProcAddress(hNtdll, "RtlIpv6StringToAddressExW");
#else
      ipv6ToAddress   = (_Ipv6StringToAddress)GetProcAddress(hNtdll, "RtlIpv6StringToAddressA");
      ipv6ToAddressEx = (_Ipv6StringToAddressEx)GetProcAddress(hNtdll, "RtlIpv6StringToAddressExA");
#endif
      if (ipv6ToAddress == NULL) {
        throw Exception("Failed to get a procAddress for Ipv6StringToAddressA");
      }
      if (ipv6ToAddressEx == NULL) {
        throw Exception("Failed to get a procAddress for Ipv6StringToAddressExA");
      }

    } else {
      //printf("Failed to get ipV6ToString\n");
      throw Exception("Failed to load Ntdll.dll");
    }
  }

public:
  /**
   * Destructor
   */
  ~IPv6String()
  {
    if (hNtdll) {
      FreeLibrary(hNtdll);
      hNtdll = NULL;
    }
  }

public:
  bool toAddress(__in const TCHAR* addressString, __out TCHAR** terminator, __out IN6_ADDR* address)
  {
    bool rc = false;
    //2011/1/18
    if (ipv6ToAddress) {
      if ((*ipv6ToAddress)(addressString, terminator, address) ==NO_ERROR) {
        rc = true;
      }
    }
    return rc;  
  }

public:
  bool toAddressEx(__in const TCHAR* addressString, __out IN6_ADDR *address, __out ULONG* scopeId, __out USHORT* port)
  {
    bool rc = false;
    //2011/1/18
    if (ipv6ToAddressEx) {
      if ((*ipv6ToAddressEx)(addressString, address, scopeId, port) == NO_ERROR) {
        rc = true;
      }
    }
    return rc;  
  }

};

}

