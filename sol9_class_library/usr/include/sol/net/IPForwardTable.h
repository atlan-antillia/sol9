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
 *  IPForwardTable.h
 *b
 *****************************************************************************/

// SOL9
// 2009/09/01

#pragma once
#include <sol/net/IfTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class IPForwardTable :public IfTable {
/*
typedef struct _MIB_IPFORWARD_TABLE2 {
  ULONG              NumEntries;
  MIB_IPFORWARD_ROW2 Table[ANY_SIZE];
}MIB_IPFORWARD_TABLE2, *PMIB_IPFORWARD_TABLE2;
 */
private:
  PMIB_IPFORWARD_TABLE2 table;

private:
  ADDRESS_FAMILY family;

public:
  IPForwardTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {
  }

public:
  ~IPForwardTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetIpForwardTable2(family, &table)) == NO_ERROR) {
      r = true;
    } else {
      //printf("GetIpNetTable2 for AF_UNSPEC  table returned error: %ld\n", r);
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

public:
  const char* getRouteProtocol(int value)
  {    
    static const ArgT<char> types[] = {  
    {"Other",              MIB_IPPROTO_OTHER},
    {"Local",              MIB_IPPROTO_LOCAL}, 
    {"NetGmt",             MIB_IPPROTO_NETMGMT},  
    {"Icmp",               MIB_IPPROTO_ICMP},  
    {"Egp",                MIB_IPPROTO_EGP},  
    {"Ggp",                MIB_IPPROTO_GGP},  
    {"Hello",              MIB_IPPROTO_HELLO},  
    {"Rip",                MIB_IPPROTO_RIP},  
    {"IsIs",               MIB_IPPROTO_IS_IS},  
    {"EsIs",               MIB_IPPROTO_ES_IS},  
    {"Cisco",              MIB_IPPROTO_CISCO},  
    {"Bbn",                MIB_IPPROTO_BBN},  
    {"Ospf",               MIB_IPPROTO_OSPF},  
    {"Bgp",                MIB_IPPROTO_BGP},  
    {"Nt AutoStatic",      MIB_IPPROTO_NT_AUTOSTATIC},  
    {"Nt Static",          MIB_IPPROTO_NT_STATIC},  
    {"Nt Static Non Dod ", MIB_IPPROTO_NT_STATIC_NON_DOD},
    };

    const char* name = "";
    int count = XtNumber(types);

    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

public:
  const char* getRouteOrigin(int value)
  {    
    static const ArgT<char> types[] = {  

    {"NlroManual",              NlroManual},  
    {"NlroWellKnown",           NlroWellKnown},  
    {"NlroDHCP",                NlroDHCP},  
    {"NlroRouterAdvertisement", NlroRouterAdvertisement},  
    {"Nlro6to4",                Nlro6to4}
    };
    const char* name = "";
    int count = XtNumber(types);

    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }



/*
typedef struct _IP_ADDRESS_PREFIX {
  SOCKADDR_INET Prefix;
  UINT8         PrefixLength;
}IP_ADDRESS_PREFIX, *PIP_ADDRESS_PREFIX;Members

*/
/*
typedef struct _MIB_IPFORWARD_ROW2 {
  NET_LUID          InterfaceLuid;
  NET_IFINDEX       InterfaceIndex;
  IP_ADDRESS_PREFIX DestinationPrefix;
  SOCKADDR_INET      NextHop;
  UCHAR             SitePrefixLength;
  ULONG             ValidLifetime;
  ULONG             PreferredLifetime;
  ULONG             Metric;
  NL_ROUTE_PROTOCOL Protocol;
  BOOLEAN           Loopback;
  BOOLEAN           AutoconfigureAddress;
  BOOLEAN           Publish;
  BOOLEAN           Immortal;
  ULONG             Age;
  NL_ROUTE_ORIGIN   Origin;
}MIB_IPFORWARD_ROW2, *PMIB_IPFORWARD_ROW2;
 */
public:
  virtual void display(MIB_IPFORWARD_ROW2& table)
  {
    printf("Interface Index : %lu\n", table.InterfaceIndex);
    printf("Interface LUID NetLuidIndex : %lu\n",table.InterfaceLuid.Info.NetLuidIndex);
    //2009/09/01 Added 
    char interfaceName[MAX_PATH];
    if (ConvertInterfaceLuidToNameA(&(table.InterfaceLuid),interfaceName, sizeof(interfaceName)) == NO_ERROR) {
      printf("Interface LUID Name : %s\n", interfaceName);
    }

    printf("Interface LUID IfType : %s\n",
    getInterfaceType(table.InterfaceLuid.Info.IfType));

  
    StringT<char> family;
    StringT<char> address;
    unsigned short port;
    getIPAddress(table.DestinationPrefix.Prefix, family, address, port);

    printf("DesitinationPrefix : %s %s\n", (const char*)family, (const char*)address);

    StringT<char> nextHop;
    getIPAddress(table.NextHop, nextHop);
    printf("NextHop : %s\n", (const char*)nextHop);

    printf("SitePrefixLength : %d\n" ,table.SitePrefixLength);

    printf("ValidLifetime : %lu\n", table.ValidLifetime);

    printf("PreferredLifetime : %lu\n", table.PreferredLifetime);
    printf("Metric : %lu\n", table.Metric);

    printf("Route Protocol : %s\n", getRouteProtocol(table.Protocol));

    printf("Loopback : %s \n", getBoolean(table.Loopback));
    printf("AutoconfigureAddress : %s \n", getBoolean(table.AutoconfigureAddress));
    printf("Publish : %s \n", getBoolean(table.Publish));
    printf("Immortal : %s \n", getBoolean(table.Immortal));

    printf("Age : %lu\n", table.Age);

    printf("Origin : %s \n", getRouteOrigin(table.Origin));

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
