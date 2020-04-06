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
 *  IpStatistics.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/04

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class IpStatistics :public MibTable {
/*
typedef struct _MIB_IPSTATS {
  DWORD dwForwarding;
  DWORD dwDefaultTTL;
  DWORD dwInReceives;
  DWORD dwInHdrErrors;
  DWORD dwInAddrErrors;
  DWORD dwForwDatagrams;
  DWORD dwInUnknownProtos;
  DWORD dwInDiscards;
  DWORD dwInDelivers;
  DWORD dwOutRequests;
  DWORD dwRoutingDiscards;
  DWORD dwOutDiscards;
  DWORD dwOutNoRoutes;
  DWORD dwReasmTimeout;
  DWORD dwReasmReqds;
  DWORD dwReasmOks;
  DWORD dwReasmFails;
  DWORD dwFragOks;
  DWORD dwFragFails;
  DWORD dwFragCreates;
  DWORD dwNumIf;
  DWORD dwNumAddr;
  DWORD dwNumRoutes;
}MIB_IPSTATS, *PMIB_IPSTATS;Members
*/
private:
  MIB_IPSTATS table; 

private:
  ADDRESS_FAMILY  family;

public:
  IpStatistics(ADDRESS_FAMILY f=AF_INET)
  :family(f)
  {
    clear();
  }

public:
  ~IpStatistics() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetIpStatisticsEx(&table, family)) == NO_ERROR){
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
    memset(&table, 0, sizeof(table));
  }

public:
  const char* getForwarding(int value)
  {
    static const ArgT<char> types[] = {
      {"IP_FORWARDING",          MIB_IP_FORWARDING},
      {"IP_NOT_FORWARDING",      MIB_IP_NOT_FORWARDING},
      {"USE_CURRENT_FORWARDING", MIB_USE_CURRENT_FORWARDING}
    };

    int count = XtNumber(types);

    const char* name = "";

    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

public:
  virtual void display(MIB_IPSTATS& table)
  {
    printf("IP Forwarding : %s\n", getForwarding(table.dwForwarding));
    printf("Default TTL : %lu\n", table.dwDefaultTTL);  
    printf("Received Datagrams : %lu\n", table.dwInReceives);
    printf("Received Datagrams of Header Errors : %lu\n", table.dwInHdrErrors);
    printf("Received Datagrams of Address Errors : %lu\n", table.dwInAddrErrors);
    printf("Forwarded Datagrams : %lu\n", table.dwForwDatagrams);
    printf("Received Datagrams of Unknown Protocol : %lu\n", table.dwInUnknownProtos);
    printf("Received Datagrams Discarded : %lu\n", table.dwInDiscards);
    printf("Received Datagrams Delivered : %lu\n", table.dwInDelivers);
    printf("Outgoing Datagrams Requested  : %lu\n", table.dwOutRequests);
    printf("Outgoing Datagrams Discarded : %lu\n", table.dwRoutingDiscards);
    printf("Transmitted Datagrams Discarded : %lu\n", table.dwOutDiscards);
    printf("Outgoing Datagrams of No Routes : %lu\n", table.dwOutNoRoutes);
    printf("Reassembly Timeout : %lu\n", table.dwReasmTimeout);
    printf("Datagrams Required Reassembly : %lu\n", table.dwReasmReqds);
    printf("Datagrams of Reassembly Oks : %lu\n", table.dwReasmOks);
    printf("Datagrams of Not Reassembled : %lu\n", table.dwReasmFails);
    printf("Datagrams of Fragment Oks : %lu\n", table.dwFragOks);
    printf("Datagrams of Not Fragmented : %lu\n", table.dwFragFails);
    printf("Created Fragments : %lu\n", table.dwFragCreates);
    printf("Number of Interface : %lu\n", table.dwNumIf);
    printf("Number of Address : %lu\n", table.dwNumAddr);
    printf("Number of Routes : %lu\n", table.dwNumRoutes);
    printf("\n");

  }


public:
  virtual void display()
  {
    getTable();

    display(table);
  } 
};

}
