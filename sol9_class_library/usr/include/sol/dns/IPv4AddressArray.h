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
 *  IPv4AddressArray.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/1 

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/StringT.h>
#include <sol/net/IPv4Address.h>

/*
typedef DWORD IP4_ADDRESS;
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

typedef struct _IP4_ARRAY 
{ 
DWORD AddrCount; 
#ifdef MIDL_PASS 
[size_is( AddrCount )] IP4_ADDRESS AddrArray[]; 
#else 
IP4_ADDRESS AddrArray[1]; 
#endif 
} IP4_ARRAY, *PIP4_ARRAY; 

*/

namespace SOL {

class IPv4AddressArray :public Object {
private:
  size_t      count;

private:
  IP4_ARRAY* ipv4Array;

public:

  IPv4AddressArray()
    :count(0),
    ipv4Array(NULL)
  {
  }

public:
  ~IPv4AddressArray()
  {
    clear();
  }


public:
  void allocArray(size_t c)
  {
    if (c > 0) {
      count = c;
      int allocSize = sizeof(DWORD) + sizeof(IP4_ADDRESS)*count;
      ipv4Array = (IP4_ARRAY*)new char[allocSize];
      
      memset(ipv4Array, 0, allocSize);
      ipv4Array->AddrCount = count;

    } else {
      throw -1;
    }
  }

public:
  void clear()
  {
    if (ipv4Array) {
      delete [] (char*)ipv4Array;
      ipv4Array = NULL;
      count = 0;
    }
  }

public:
  void setNth(int n, in_addr addr)
  {
    if (n>= 0 && n< (int)count) {
      if (ipv4Array) {
        ipv4Array->AddrArray[n] = addr.s_addr;
        //printf("setNth(%s)\n", inet_ntoa(addr));
      } else {
        throw -1;
      }
    } else {
      throw -1;
    }
  }

public:
  IP4_ARRAY* getArray() 
  {
    return ipv4Array;
  }

public:
  operator const IP4_ARRAY*() const
  {
    return ipv4Array;
  }


public:
  size_t getCount()
  {
    return count;
  }

public:
  void display()
  {
    if (ipv4Array && count>0) {
      _tprintf(_T("DnsServer: IPv4AddressArray(count=%d)\n"), count);
      for (size_t i = 0; i < count; i++) {
        IPv4Address ipv4address;
        StringT<TCHAR> string;
        ipv4address.toString(ipv4Array->AddrArray[i], string);
        _tprintf(_T("\tIP4_ADDRESS[%d]=%s\n"), i, (const TCHAR*)string);
      }
    }
  }
};

}
