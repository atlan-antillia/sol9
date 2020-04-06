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
 *  IPPathTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/IfTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class IPPathTable :public IfTable {
/*
typedef struct _MIB_IPPATH_TABLE {
  ULONG          NumEntries;
  MIB_IPPATH_ROW Table[ANY_SIZE];
}MIB_IPPATH_TABLE, *PMIB_IPPATH_TABLE;
*/
private:
  PMIB_IPPATH_TABLE table;

private:
  ADDRESS_FAMILY  family;

public:
  IPPathTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {

  }

public:
  ~IPPathTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetIpPathTable(family, &table)) == NO_ERROR){
      rc = true;
    } else {
      clear();
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

/*
typedef struct _MIB_IPPATH_ROW {
  SOCKADDR_INET  Source;
  SOCKADDR_INET  Destination;
  NET_LUID      InterfaceLuid;
  NET_IFINDEX   InterfaceIndex;
  SOCKADDR_INET  CurrentNextHop;
  ULONG         PathMtu;
  ULONG         RttMean;
  ULONG         RttDeviation;
  union {
    ULONG LastReachable;
    ULONG LastUnreachable;
  } ;
  BOOLEAN       IsReachable;
  ULONG64       LinkTransmitSpeed;
  ULONG64       LinkReceiveSpeed;
}MIB_IPPATH_ROW, *PMIB_IPPATH_ROW;
*/

public:
  virtual void display(MIB_IPPATH_ROW& table)
  {
    StringT<char> source;
    StringT<char> destination;

    getIPAddress(table.Source, source);

    getIPAddress(table.Destination, destination);

    printf("Source : %s\n", (const char*)source);

    printf("Destination : %s\n", (const char*)destination);
        printf("Interface Index : %lu\n", table.InterfaceIndex);
        printf("Interface LUID NetLuidIndex : %lu\n",table.InterfaceLuid.Info.NetLuidIndex);
    //2009/09/01 Added 
    char interfaceName[MAX_PATH];
    if (ConvertInterfaceLuidToNameA(&(table.InterfaceLuid),interfaceName, sizeof(interfaceName)) == NO_ERROR) {
      printf("Interface LUID Name : %s\n", interfaceName);
    }

        printf("Interface LUID IfType : %s\n",
        getInterfaceType(table.InterfaceLuid.Info.IfType));
    
    StringT<char> currentNextHop;

    getIPAddress(table.CurrentNextHop, currentNextHop);
    printf("Current Next Hop : %s\n", (const char*)currentNextHop);
    

    printf("PathMtu : %lu\n", table.PathMtu);
    printf("RttMean : %lu\n", table.RttMean);
    printf("RttDeviation : %lu\n", table.RttDeviation);
    /*
    union {
    ULONG LastReachable;
    ULONG LastUnreachable;
    } ;
    */
    printf("IsReachable :%s\n", getBoolean(table.IsReachable));

    
    printf("LinkTransmit : %llu\n", table.LinkTransmitSpeed);
    printf("LinkReceiveSpeed: %llu\n", table.LinkReceiveSpeed);
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
