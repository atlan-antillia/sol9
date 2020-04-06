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
 *  IPv6Address.h
 *
 *****************************************************************************/

// SOL9
// 2010/09/01
// 2010/12/07 Modified to have a member variable of IN6_ADDR.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/String.h>
#include <sol/StringT.h>
#include <mstcpip.h>

namespace SOL {

/*
LPTSTR NTAPI RtlIpv6AddressToString(
  __in   const IN6_ADDR *Addr,
  __out  LPTSTR S
);
LONG NTAPI RtlIpv6AddressToStringEx(
  __in     const IN6_ADDR *Address,
  __in     ULONG ScopeId,
  __in     USHORT Port,
  __out    LPTSTR AddressString,
  __inout  PULONG AddressStringLength
);
*/

typedef char* (NTAPI *_Ipv6AddressToString)(__in const IN6_ADDR *address, __out TCHAR* addressString);
typedef LONG  (NTAPI *_Ipv6AddressToStringEx)(__in const IN6_ADDR *address, __in ULONG scopeId, __in USHORT port,
                        __out TCHAR* addressString, __inout ULONG* addressStringLength);

class IPv6Address :public Object {
private:
  IN6_ADDR inaddr;

private:
  // For Ntdll.dll module
  HMODULE  hNtdll;

private:
  //Utility functions to convert an IPV6 Address (IN6_ADDR structure) to a string.
  _Ipv6AddressToString   ipv6ToString;
  _Ipv6AddressToStringEx ipv6ToStringEx;

public:
  /**
   * Constructor
   */
  //2010/12/07: Modified to be able to take a parameter of a pointer to IN6_ADDR structure.
  IPv6Address(IN6_ADDR* addr=NULL)
    :hNtdll(NULL),
    ipv6ToString(NULL),
    ipv6ToStringEx(NULL)
  {
    memset(&inaddr, 0, sizeof(inaddr));
    if (addr) {
      memcpy(&inaddr, addr, sizeof(inaddr));
    }

    hNtdll = LoadLibrary(_T("Ntdll.dll"));

    if (hNtdll) {
#ifdef UNICODE
      ipv6ToString   = (_Ipv6AddressToString)GetProcAddress(hNtdll, "RtlIpv6AddressToStringW");
      ipv6ToStringEx = (_Ipv6AddressToStringEx)GetProcAddress(hNtdll, "RtlIpv6AddressToStringExW");
#else
      ipv6ToString   = (_Ipv6AddressToString)GetProcAddress(hNtdll, "RtlIpv6AddressToStringA");
      ipv6ToStringEx = (_Ipv6AddressToStringEx)GetProcAddress(hNtdll, "RtlIpv6AddressToStringExA");
#endif
      if (ipv6ToString == NULL) {
        throw Exception("Failed to get a procAddress for Ipv6AddressToStringsA");
      }
      if (ipv6ToStringEx == NULL) {
        throw Exception("Failed to get a procAddress for Ipv6AddressToStringExA");
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
  ~IPv6Address()
  {
    if (hNtdll) {
      FreeLibrary(hNtdll);
      hNtdll = NULL;
    }
  }


public:
  void getAddress(__out IN6_ADDR& addr)
  {
    memcpy(&addr, &inaddr, sizeof(inaddr));
  }

public:
  bool toString(__out TCHAR* addressString)
  {
    // Convert this->inaddr of IN_ADDR to a string. 
    return toString(&inaddr, addressString);
  }

public:
  bool toString(__out StringT<TCHAR>& addressString)
  {
    // Convert this->inaddr of IN_ADDR to a string. 
    return toString(&inaddr, addressString);
  }

public:
  bool toStringEx(__in ULONG scopeId, __in USHORT port, 
    __out TCHAR* addressString, __inout ULONG* addressStringLength)
  {
    // Convert this->inaddr of IN_ADDR to a string. 
    return toStringEx(&inaddr, scopeId, port, addressString, addressStringLength);
  }

public:
  bool toString(__in const IN6_ADDR* address, __out StringT<TCHAR>& addressString)
  {
    bool rc = false;
  
    if (ipv6ToString) {
      TCHAR buffer[128];
      memset(buffer, (TCHAR)0, CountOf(buffer));
      if ((*ipv6ToString)(address, buffer)) {
        rc = true;
        addressString = buffer;
      }
    }
    return rc;  
  }

public:
  bool toString(__in const IN6_ADDR& address, __out StringT<TCHAR>& addressString)
  {
    bool rc = false;
  
    if (ipv6ToString) {
      TCHAR buffer[128];
      memset(buffer, (TCHAR)0, CountOf(buffer));
      if ((*ipv6ToString)(&address, buffer)) {
        rc = true;
        addressString = buffer;
      }
    }
    return rc;  
  }

public:
  bool toString(__in const IN6_ADDR* address, __out TCHAR* addressString)
  {
    bool rc = false;
  
    if (ipv6ToString) {
      if ((*ipv6ToString)(address, addressString)) {
        rc = true;
      }
    }
    return rc;  
  }

public:
  bool toStringEx(__in const IN6_ADDR *address, __in ULONG scopeId, __in USHORT port, 
    __out TCHAR* addressString, __inout ULONG* addressStringLength)
  {
    bool rc = false;
  
    if (ipv6ToStringEx) {
      if ((*ipv6ToStringEx)(address, scopeId, port, addressString, addressStringLength)) {
        rc = true;
      }
    }
    return rc;  
  }

};

}

