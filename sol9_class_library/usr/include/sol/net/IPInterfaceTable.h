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
 *  IPInterfaceTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/28

#include <sol/net/IfTable.h>

#include <sol/Arg.h>

#pragma comment(lib, "iphlpapi.lib")

namespace SOL {

class IPInterfaceTable :public IfTable {

/*
typedef struct _MIB_IPINTERFACE_TABLE {
  ULONG               NumEntries;
  MIB_IPINTERFACE_ROW Table[ANY_SIZE];
}MIB_IPINTERFACE_TABLE, *PMIB_IPINTERFACE_TABLE;
*/
private:
    PMIB_IPINTERFACE_TABLE table;

private:
  ADDRESS_FAMILY family;

public:
  /**
   * Construcotr
   */
  IPInterfaceTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {
  }

public:
  /**
   * Destructor
   */
  ~IPInterfaceTable()
  {
    clear();
  }

public:
  void clear()
  {
    if (table) {
      FreeMibTable(table);
      table = NULL;
    }
  }

public:
  bool getTable()
  {
    clear();
    bool rc = false;

    DWORD r = 0;
    if ((r = GetIpInterfaceTable(family, &table)) == NO_ERROR){
      rc = true;
    } else {
      throw r;  
    }
    return rc;
  }

public:
  const char* getFamily(int type)
  {
    static const ArgT<char> types[] = {
    {"IPv4", AF_INET},
    {"IPv6", AF_INET6},
    };

    static char name[128];
    memset(name, 0, sizeof(name));
    sprintf_s(name, CountOf(name), "Unknown Family: %d", type);

    int count = XtNumber(types);
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == type) {
        strcpy_s(name, CountOf(name), types[i].name);
        break;
      }
    }
    return name;
  }


public:
  const char* getDiscoveryBehavior(int value)
  {
    static const ArgT<char> types[] = {
    {"Disabled",  (LONG_PTR)RouterDiscoveryDisabled},        
    {"Enabled",   (LONG_PTR)RouterDiscoveryEnabled},  
    {"Dhcp",      (LONG_PTR)RouterDiscoveryDhcp},  
    {"Unchanged", (LONG_PTR)RouterDiscoveryUnchanged}
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
  const char* getLinkLocalAddressBehavior(int type)
  {
    static const ArgT<char> types[] = {
    {"AlwaysOff", (LONG_PTR)LinkLocalAlwaysOff},  
    {"Delayed",   (LONG_PTR)LinkLocalDelayed},  
    {"AlwaysOn",  (LONG_PTR)LinkLocalAlwaysOn},  
    {"Unchanged", (LONG_PTR)LinkLocalUnchanged} 
    };

    const char* name = "";    
    int count = XtNumber(types);
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == type) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }


/*
typedef struct _MIB_IPINTERFACE_ROW {
  ADDRESS_FAMILY                 Family;
  NET_LUID                       InterfaceLuid;
  NET_IFINDEX                    InterfaceIndex;
  ULONG                          MaxReassemblySize;
  ULONG64                        InterfaceIdentifier;
  ULONG                          MinRouterAdvertisementInterval;
  ULONG                          MaxRouterAdvertisementInterval;
  BOOLEAN                        AdvertisingEnabled;
  BOOLEAN                        ForwardingEnabled;
  BOOLEAN                        WeakHostSend;
  BOOLEAN                        WeakHostReceive;
  BOOLEAN                        UseAutomaticMetric;
  BOOLEAN                        UseNeighborUnreachabilityDetection;
  BOOLEAN                        ManagedAddressConfigurationSupported;
  BOOLEAN                        OtherStatefulConfigurationSupported;
  BOOLEAN                        AdvertiseDefaultRoute;
  NL_ROUTER_DISCOVERY_BEHAVIOR   RouterDiscoveryBehavior;
  ULONG                          DadTransmits;
  ULONG                          BaseReachableTime;
  ULONG                          RetransmitTime;
  ULONG                          PathMtuDiscoveryTimeout;
  NL_LINK_LOCAL_ADDRESS_BEHAVIOR LinkLocalAddressBehavior;
  ULONG                          LinkLocalAddressTimeout;
  ULONG                          ZoneIndices[ScopeLevelCount];
  ULONG                          SitePrefixLength;
  ULONG                          Metric;
  ULONG                          NlMtu;
  BOOLEAN                        Connected;
  BOOLEAN                        SupportsWakeUpPatterns;
  BOOLEAN                        SupportsNeighborDiscovery;
  BOOLEAN                        SupportsRouterDiscovery;
  ULONG                          ReachableTime;
  NL_INTERFACE_OFFLOAD_ROD       TransmitOffload;
  NL_INTERFACE_OFFLOAD_ROD       ReceiveOffload;
  BOOLEAN                        DisableDefaultRoutes;
}MIB_IPINTERFACE_ROW, *PMIB_IPINTERFACE_ROW;
 */

public:
  virtual void display(MIB_IPINTERFACE_ROW& table)
  {
    printf("Address Family : %s\n", getFamily(table.Family));
    printf("Interface LUID NetLuidIndex : %lu\n", table.InterfaceLuid.Info.NetLuidIndex);

    //2009/09/01 Added 
    char interfaceName[MAX_PATH];
    if (ConvertInterfaceLuidToNameA(&(table.InterfaceLuid),interfaceName, sizeof(interfaceName)) == NO_ERROR) {
      printf("Interface LUID Name : %s\n", interfaceName);
    }


    printf("Interface LUID IfType : %s\n", getInterfaceType(table.InterfaceLuid.Info.IfType));
    printf("Interface Index : %lu\n", table.InterfaceIndex);
    printf("Maximum Reassembly Size : %lu\n", table.MaxReassemblySize);
    printf("Advertising Enabled : %s\n", getBoolean(table.AdvertisingEnabled));
    printf("Forwarding Enabled : %s\n",  getBoolean(table.ForwardingEnabled));
    printf("WeakHostSend : %s\n", getBoolean(table.WeakHostSend));
    printf("WeakHostReceive : %s\n", getBoolean(table.WeakHostReceive));
    printf("UseAutomatic Metric : %s\n", getBoolean(table.UseAutomaticMetric));
    printf("Use Neighbor UnreachabilityDetection : %s\n", getBoolean(table.UseNeighborUnreachabilityDetection));
    printf("Managed Address Configuration Supported : %s\n", getBoolean(table.ManagedAddressConfigurationSupported));
    printf("Other Stateful Configuration Supported : %s\n", getBoolean(table.OtherStatefulConfigurationSupported));
    printf("Advertise Default Route : %s\n", getBoolean(table.AdvertiseDefaultRoute));
    printf("Router Discovery Behavior : %s\n", getDiscoveryBehavior(table.RouterDiscoveryBehavior));
    printf("Dad Transmits : %lu \n", table.DadTransmits);
    printf("Base Reachable Time : %lu \n", table.BaseReachableTime);
    printf("Retransmit Time : %lu \n", table.RetransmitTime);
    printf("Path Mtu Discovery Timeout : %lu\n", table.PathMtuDiscoveryTimeout);
    printf("Link Local Address Behavior : %s\n", getLinkLocalAddressBehavior(table.LinkLocalAddressBehavior));
    printf("Link Local Address Timeout : %lu\n", table.LinkLocalAddressTimeout);;
    printf("ZoneIndices : ");
    for (int i = 0; i<ScopeLevelCount; i++) {
      printf(" %lu", table.ZoneIndices[i]);
    }
    printf("\n");

    printf("Site Prefix Length : %lu\n", table.SitePrefixLength);
    printf("Metric : %lu\n", table.Metric);
    printf("Network Layer MTU : %lu\n", table.NlMtu);
    printf("Connected : %s\n", getBoolean(table.Connected));
    printf("Supports Wakeup Patterns : %s\n", getBoolean(table.SupportsWakeUpPatterns));
    printf("Supports Neighbor Discovery : %s\n", getBoolean(table.SupportsNeighborDiscovery));
    printf("Supports Router Discovery : %s\n",  getBoolean(table.SupportsRouterDiscovery));
  }

public:
  virtual void display()
  {
    if (getTable()) {
      if (table) {
        for (int i = 0; i < (int)table->NumEntries; i++) {
          display(table->Table[i]);
          printf("\n");
        }
      }
    }
  }
};

}
