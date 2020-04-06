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
 *  IPNeighborTable.h
 *b
 *****************************************************************************/

// SOL9
// 2009/08/31
// 2012/11/29 Updated display method.

#pragma once
#include <sol/net/IfTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class IPNeighborTable :public IfTable {
/*
typedef struct _MIB_IPNET_TABLE2 {
  ULONG       NumEntries;
  MIB_IF_ROW2 Table[ANY_SIZE];
}MIB_IPNET_TABLE2, *PMIB_IPNET_TABLE2;
 */
private:
  PMIB_IPNET_TABLE2 table;

private:
  ADDRESS_FAMILY family;

public:
  IPNeighborTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {
  }

public:
  ~IPNeighborTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetIpNetTable2(family, &table)) == NO_ERROR) {
      r = true;
    } else {
      throw r;
    }
    return rc;
  }

public:
  void clear()
  {
    if (table) {
      FreeMibTable(table);
      table = NULL;
    }
  }

protected:
  const char* getNeighborState(int value)
  {
    static const ArgT<char> states[] = {
      {"NlnsUnreachable", NlnsUnreachable},
      {"NlnsIncomplete",  NlnsIncomplete},
      {"NlnsProbe",       NlnsProbe},
      {"NlnsDelay",       NlnsDelay},
      {"NlnsStale",       NlnsStale},
      {"NlnsReachable",   NlnsReachable},
      {"NlnsPermanent",   NlnsPermanent}
      };

    const char* name = "Unknown";
    int count = XtNumber(states);
    for (int i = 0; i<count; i++) {
      if ((int)states[i].value == value) {
        name = states[i].name;
        break;
      }
    }
    return name;
  }

/*
typedef struct sockaddr_in6 
{  
  ADDRESS_FAMILY  sin6_family;
  USHORT  sin6_port;
  ULONG  sin6_flowinfo;
  IN6_ADDR  sin6_addr;  
  union {
    ULONG  sin6_scope_id;    
    SCOPE_ID  
    sin6_scope_struct;   
  };
} SOCKADDR_IN6, *PSOCKADDR_IN6;

typedef union _SOCKADDR_INET {
  SOCKADDR_IN    Ipv4;
  SOCKADDR_IN6   Ipv6;
  ADDRESS_FAMILY si_family;
}SOCKADDR_INET, *PSOCKADDR_INET;
 */
/*
typedef struct _MIB_IPNET_ROW2 {
  SOCKADDR_INET     Address;
  NET_IFINDEX       InterfaceIndex;
  NET_LUID          InterfaceLuid;
   UCHAR            PhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
  ULONG             PhysicalAddressLength;
  NL_NEIGHBOR_STATE State;
  union {
    struct {
      BOOLEAN IsRouter  :1;
      BOOLEAN IsUnreachable  :1;
    } ;
    UCHAR Flags;
  } ;
  union {
    ULONG LastReachable;
    ULONG LastUnreachable;
  } ReachabilityTime;
}MIB_IPNET_ROW2, *PMIB_IPNET_ROW2;
 */
public:
  virtual void display(MIB_IPNET_ROW2& table)
  {
    StringT<char> address;

    if (table.Address.si_family == AF_INET) {
      printf("IPv4 Address : %s\n", (int)         //2012/11/29  "... %sd\n\\" -> "... %s\n"
                   inet_ntoa(table.Address.Ipv4.sin_addr));
          //ntohs(table.Address.Ipv4.sin_port));
    }
    if (table.Address.si_family == AF_INET6) {
      getIPAddress(table.Address.Ipv6.sin6_addr, address);
      printf("IPv6 Address : %s\n", 
        (const char*)address);
        // ntohs(table.Address.Ipv6.sin6_port));  
    }

    printf("Interface index : %lu\n", table.InterfaceIndex);
    printf("Interface LUID NetLuidIndex : %lu\n",table.InterfaceLuid.Info.NetLuidIndex);

        printf("Interface LUID IfType : %s\n",
    getInterfaceType(table.InterfaceLuid.Info.IfType));
 
    StringT<char> physicalAddress = "";
    getPhysicalAddress(table.PhysicalAddress, table.PhysicalAddressLength, physicalAddress);
    printf("Physical Address : %s \n", (const char*)physicalAddress);

    printf("Neighbor State : %s \n", (const char*)getNeighborState(table.State));

    printf("Flags : %u\n", (unsigned char) table.Flags);

    printf("ReachabilityTime: %lu\n", table.ReachabilityTime);
  }


public:
  virtual void display()
  {
    if (table == NULL) {
      getTable();
    }
    if (table) {
      for (int i = 0 ; i < (int)table->NumEntries; i++) {
        display(table->Table[i]);
        printf("\n");
      }
    }
  } 
};

}
