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
 *  TcpStatistics.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/04

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class TcpStatistics :public MibTable {
/*
typedef struct _MIB_TCPSTATS {
  DWORD dwRtoAlgorithm;
  DWORD dwRtoMin;
  DWORD dwRtoMax;
  DWORD dwMaxConn;
  DWORD dwActiveOpens;
  DWORD dwPassiveOpens;
  DWORD dwAttemptFails;
  DWORD dwEstabResets;
  DWORD dwCurrEstab;
  DWORD dwInSegs;
  DWORD dwOutSegs;
  DWORD dwRetransSegs;
  DWORD dwInErrs;
  DWORD dwOutRsts;
  DWORD dwNumConns;
}MIB_TCPSTATS, *PMIB_TCPSTATS;
*/
private:
  MIB_TCPSTATS table; 

private:
  ADDRESS_FAMILY  family;

public:
  TcpStatistics(ADDRESS_FAMILY f=AF_INET)
  :family(f)
  {
    clear();
  }

public:
  ~TcpStatistics() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetTcpStatisticsEx(&table, family)) == NO_ERROR){
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
  const char* getRtoAlgorithm(int value)
  {
    //The retransmission time-out (RTO) algorithm in use

    static const ArgT<char> types[] = {

    {"TCP_RTO_OTHER",    MIB_TCP_RTO_OTHER},
    {"TCP_RTO_CONSTANT", MIB_TCP_RTO_CONSTANT},
    {"TCP_RTO_RSRE",     MIB_TCP_RTO_RSRE},
    {"TCP_RTO_VANJ",     MIB_TCP_RTO_VANJ},
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
*/

public:
  virtual void display(MIB_TCPSTATS& table)
  {
    printf("RTO Algorithm : %s\n", getRtoAlgorithm(table.dwRtoAlgorithm));
    printf("RTO Minimum : %lu\n", table.dwRtoMin);
    printf("RTO Maximum : %lu\n", table.dwRtoMax);
    if (table.dwMaxConn == -1) {
      printf("Maximum Connections : Variable\n");

    } else {
      printf("Maximum Connections : %lu\n", table.dwMaxConn);
    }
    printf("Active Opens : %lu\n", table.dwActiveOpens);
    printf("Passive Opens : %lu\n", table.dwPassiveOpens);
    printf("Failed Connection Attempts : %lu\n", table.dwAttemptFails);
    printf("Reset Established Connections : %lu\n", table.dwEstabResets);
    printf("Currently Established Connections: %lu\n", table.dwCurrEstab);
    printf("Received Segments : %lu\n", table.dwInSegs);
    printf("Transmitted Segments : %lu\n", table.dwOutSegs);
    printf("Retransmitted Segments : %lu\n", table.dwRetransSegs);
    printf("Received Errors : %lu\n", table.dwInErrs);
    printf("Transmitted Segments with Reset : %lu\n", table.dwOutRsts);
    printf("Current Connections : %lu\n", table. dwNumConns);
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
