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
 *  UdpStatistics.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/04

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class UdpStatistics :public MibTable {
/*
typedef struct _MIB_UDPSTATS {
  DWORD dwInDatagrams;
  DWORD dwNoPorts;
  DWORD dwInErrors;
  DWORD dwOutDatagrams;
  DWORD dwNumAddrs;
}MIB_UDPSTATS, *PMIB_UDPSTATS;
*/
private:
  MIB_UDPSTATS table; 

private:
  ADDRESS_FAMILY  family;

public:
  UdpStatistics(ADDRESS_FAMILY f=AF_INET)
  :family(f)
  {
    clear();
  }

public:
  ~UdpStatistics() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetUdpStatisticsEx(&table, family)) == NO_ERROR){
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



/*
*/

public:
  virtual void display(MIB_UDPSTATS& table)
  {
    printf("InDatagrams : %lu\n", table.dwInDatagrams);
    printf("NoPorts : %lu\n", table.dwNoPorts);
    printf("InErrors : %lu\n", table.dwInErrors);
    printf("OutDatagrams : %lu\n", table.dwOutDatagrams);
    printf("NumAddrs : %lu\n", table.dwNumAddrs);
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
