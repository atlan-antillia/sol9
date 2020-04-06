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
 *  IPv4String.h
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
typedef struct {
  union {
    struct {
      u_char s_b1,s_b2,s_b3,s_b4;
    } S_un_b;
    struct {
      u_short s_w1,s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
} IPAddr;

typedef struct in_addr {
  union {
    struct {
      u_char s_b1,s_b2,s_b3,s_b4;
    } S_un_b;
    struct {
      u_short s_w1,s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;

LONG NTAPI RtlIpv4StringToAddress(
  __in   PCTSTR S,
  __in   BOOLEAN Strict,
  __out  LPTSTR *Terminator,
  __out  IN_ADDR *Addr
);

LONG NTAPI RtlIpv4StringToAddressEx(
  __in   PCTSTR AddressString,
  __in   BOOLEAN Strict,
  __out  IN_ADDR *Address,
  __out  PUSHORT Port
);
*/
typedef LONG (NTAPI *_Ipv4StringToAddress)(__in const TCHAR* addressString, __in BOOLEAN strict, __out TCHAR** terminator, __out IN_ADDR *address);
typedef LONG (NTAPI *_Ipv4StringToAddressEx)(__in const TCHAR* addressString, __in BOOLEAN strict, __out IN_ADDR *address, __out USHORT* port);

class IPv4String :public Object {

private:
  // For Ntdll.dll module
  HMODULE  hNtdll;

private:
  //Utility functions to convert a string to IPV4 Address (IN6_ADDR structure)
  _Ipv4StringToAddress   ipv4ToAddress;
  _Ipv4StringToAddressEx ipv4ToAddressEx;

public:
  /**
   * Constructor
   */
  IPv4String()
    :hNtdll(NULL),
    ipv4ToAddress(NULL),
    ipv4ToAddressEx(NULL)
  {
    hNtdll = LoadLibrary(_T("Ntdll.dll"));

    if (hNtdll) {
#ifdef UNICODE
      ipv4ToAddress   = (_Ipv4StringToAddress)GetProcAddress(hNtdll, "RtlIpv4StringToAddressW");
      ipv4ToAddressEx = (_Ipv4StringToAddressEx)GetProcAddress(hNtdll, "RtlIpv4StringToAddressExW");
#else
      ipv4ToAddress   = (_Ipv4StringToAddress)GetProcAddress(hNtdll, "RtlIpv4StringToAddressA");
      ipv4ToAddressEx = (_Ipv4StringToAddressEx)GetProcAddress(hNtdll, "RtlIpv4StringToAddressExA");
#endif
      if (ipv4ToAddress == NULL) {
        throw Exception("Failed to get a procAddress for Ipv4StringToAddressA");
      }
      if (ipv4ToAddressEx == NULL) {
        throw Exception("Failed to get a procAddress for Ipv4StringToAddressExA");
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
  ~IPv4String()
  {
    if (hNtdll) {
      FreeLibrary(hNtdll);
      hNtdll = NULL;
    }
  }

public:
  bool toAddress(__in const TCHAR* addressString, 
      __in BOOLEAN strict, 
      __out TCHAR** terminator, 
      __out IN_ADDR* address)
  {
    bool rc = false;
    //2011/1/18  
    if (ipv4ToAddress) {
      if ((*ipv4ToAddress)(addressString, strict, terminator, address)==NO_ERROR) {
        rc = true;
      }
    }
    return rc;  
  }

public:
  bool toAddressEx(__in const TCHAR* addressString, 
      __in BOOLEAN strict, 
      __out IN_ADDR *address, 
      __out USHORT* port)
  {
    bool rc = false;
    //2011/1/18
    if (ipv4ToAddressEx) {
      if ((*ipv4ToAddressEx)(addressString, strict, address, port)==NO_ERROR) {
        rc = true;
      }
    }
    return rc;  
  }

};

}

