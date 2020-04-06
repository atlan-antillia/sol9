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
 *  MibTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/24

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/String.h>
#include <sol/StringT.h>

#include <sol/ArgList.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>

#include <Mstcpip.h>
#include <time.h>

namespace SOL {

typedef LPTSTR (NTAPI *IPv6AddressToString)(const IN6_ADDR *Addr, char* stri);


class MibTable :public Object {

public:
  //Pure virtual fuction
  virtual bool getTable() = 0; 

public:
  virtual void display(HWND hwnd) {};

public:
  virtual void clear() {};

public:
  //Pure virtual function
  virtual void display() = 0;

private:
  // For Ntdll.dll module
  HMODULE         hNtdll;

private:
  //Utility function to convert IPV6 Address (IN6_ADDR structure) to a string
  IPv6AddressToString  ipv6ToString;

public:
  /**
   */
  MibTable()
    :hNtdll(NULL),
    ipv6ToString(NULL)
  {
    //2009/09/03
    //hNtdll = GetModuleHandle("Ntdll.dll");
    hNtdll = LoadLibrary(_T("Ntdll.dll"));

    if (hNtdll) {
      ipv6ToString = (IPv6AddressToString)GetProcAddress(hNtdll, "RtlIpv6AddressToStringA");
    } else {
      //printf("Failed to get ipV6ToString\n");
    }
  }

public:
  /**
   * Destructor
   */
  ~MibTable()
  {
    if (hNtdll) {
      FreeLibrary(hNtdll);
      hNtdll = NULL;
    }
  }

  //
protected:
  unsigned short getPort(DWORD port)
  {
    return ntohs((unsigned short)port);
  }

protected:
  unsigned long getScopeId(DWORD scopeId)
  {
    return ntohl(scopeId);
  }


/*
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
}
 SOCKADDR_IN6, *PSOCKADDR_IN6;
*/

/*
typedef union _SOCKADDR_INET {
  SOCKADDR_IN    Ipv4;
  SOCKADDR_IN6   Ipv6;
  ADDRESS_FAMILY si_family;
}SOCKADDR_INET, *PSOCKADDR_INET;
*/
protected:
  bool getPhysicalAddress(__in unsigned char* physAddr,
    __in size_t size,
    __out StringT<char>& string)
  {
    bool rc = false;
    if (physAddr && size == 6) {
      char buffer[128];
      sprintf_s(buffer, CountOf(buffer), "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
        physAddr[0],
        physAddr[1],
        physAddr[2],
        physAddr[3],
        physAddr[4],
        physAddr[5]);
      rc = true;
      string = buffer;
    }
    return rc;  
  }

public:
  bool getIPAddress(__in SOCKADDR_INET& inet,
     __out StringT<char>& family,
     __out StringT<char>& address,
     __out unsigned short& port)
  {
    bool rc = false;
    if (inet.si_family == AF_INET) {
      family = "IPv4";
      //
      getIPAddress(inet.Ipv4.sin_addr, address);
      port = getPort(inet.Ipv4.sin_port);
      rc = true;
    }
    if (inet.si_family == AF_INET6) {
      family = "IPv6";
      //IN6_ADDR
      getIPAddress(inet.Ipv6.sin6_addr, address);
      //call ntohs
      port = getPort(inet.Ipv6.sin6_port);
      rc = true;
    }

    return rc;
  }

public:
  bool getIPAddress(__in SOCKADDR_INET& inet,
     __out StringT<char>& address)
  {
    bool rc = false;
    if (inet.si_family == AF_INET) {
      //
      getIPAddress(inet.Ipv4.sin_addr, address);
      rc = true;
    }
    if (inet.si_family == AF_INET6) {
      //IN6_ADDR
      getIPAddress(inet.Ipv6.sin6_addr, address);
      rc = true;
    }
    return rc;
  }



protected:
  //IPv4
  bool getIPAddress(__in in_addr address, __out StringT<char>& string)
  {
    bool rc = false;
    char* addr = inet_ntoa(address);
    if (addr) {
      string = addr;
      rc = true;  
    }
    return rc;  
  }

protected:
  //IPv4
  bool getIPAddress(__in DWORD address, __out StringT<char>& string)
  {
    bool rc = false;
    //IPv4
       in_addr ipAddr;
    memset(&ipAddr, 0, sizeof(ipAddr));
    ipAddr.S_un.S_addr = address;

    char* addr = inet_ntoa(ipAddr);
    if (addr) {
      string = addr;
      rc = true;  
    }
    return rc;  
  }

protected:
  //IPv6
  bool getIPAddress(__in IN6_ADDR address, __out StringT<char>& string)
  {
    bool rc = false;
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    if (ipv6ToString) {
      if ((*ipv6ToString)(&address, buffer)) {
        rc = true;
        string = buffer;
      }
    }
    return rc;  
  }

protected:
  //IPv6 
  bool getIPAddress(__in unsigned char* address, __out StringT<char>& string)
  {
    bool rc = false;
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    if (ipv6ToString) {
      if ((*ipv6ToString)((IN6_ADDR*)address, buffer)) {
        rc = true;
        string = buffer;
      }
    }
    return rc;  
  }


public:
  // 2009/09/03 Moved here from IPInterfaceTable
  bool getLocalTime32(__in time_t t, __out StringT<char>& localTime)
  {
    bool rc = false;
    struct tm _tm;
    errno_t  error = _localtime32_s(&_tm, (__time32_t* )&t);
      
    if (error) {
      return rc;
    }

    char buffer[32];
    memset(buffer, 0, sizeof(buffer));
    error = asctime_s(buffer, sizeof(buffer), &_tm);        
    if (error) {
      return rc;
    }

    localTime = buffer;
    rc = true;
    return rc;
  }

public:
  bool getLocalTime(__in LARGE_INTEGER t, __out StringT<char>& localTime)
  {
    bool rc = false;
    struct tm _tm;

  //  errno_t error;
    if (_localtime64_s(&_tm, (const __time64_t *)&t) ) {
    //if (localtime_s(&_tm, (const time_t*) &t) ) {

      //printf("Error1\n");
      return rc;
    }

    char buffer[32];
    if (asctime_s(buffer, sizeof(buffer), &_tm)) {
          printf("Invalid Argument to asctime_s\n");
      return rc;
    }
    localTime = buffer;

    rc = true;

    return rc;
  }

public:
  const char* getBoolean(BOOL value)
  {
    static const ArgT<char> types[] = {
    {"No", FALSE},
    {"Yes", TRUE}
    };

    ArgListT<char> argList(types, XtNumber(types));

    return argList.getName((int)value);
  }

protected:
  const char* getState(DWORD state)
  {
    static const char* states[] = {
    "",
     "CLOSED",
    "LISTEN",
    "SYN_SENT", 
    "SYN_RCVD", 
    "ESTABLISHED", 
    "FIN_WAIT1",
    "FIN_WAIT2", 

    "CLOSE_WAIT", 
    "CLOSING", 
    "LAST_ACK", 
    "TIME_WAIT",
    "DELETE_TCB",
    };

    const char* name = "";
    int count = XtNumber(states);
    if (state >0 && (int)state < count) {
      name = states[state];
    }
    return name;
  }
};

}
