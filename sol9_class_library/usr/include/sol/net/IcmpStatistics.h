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
 *  IcmpStatistics.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/08

#pragma once
#include <sol/net/MibTable.h>

namespace SOL {
 
class IcmpStatistics :public MibTable {

/*
typedef struct _MIBICMPSTATS_EX {
  DWORD dwMsgs;
  DWORD dwErrors;
  DWORD rgdwTypeCount[256];
}MIBICMPSTATS_EX, *PMIBICMPSTATS_EX;

typedef struct _MIB_ICMP_EX {
  MIBICMPSTATS_EX icmpInStats;
  MIBICMPSTATS_EX icmpOutStats;
}MIB_ICMP_EX, *PMIB_ICMP_EX;
*/
private:
  MIB_ICMP_EX table; 

private:
  ADDRESS_FAMILY  family;

public:
  /**
   * family must be AF_INET or AF_INET6
   */

  IcmpStatistics(ADDRESS_FAMILY f=AF_INET)
  :family(f)
  {
    clear();
  }

public:
  ~IcmpStatistics() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    
    DWORD r = NO_ERROR;
    if ((r = GetIcmpStatisticsEx(&table, family)) == NO_ERROR){
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
  virtual void display(MIB_ICMP_EX& table)
  {
    printf("Number of Sent Messages : %lu\n", table.icmpOutStats.dwMsgs);
    printf("Number of Sent Errors : %lu \n", table.icmpOutStats.dwErrors);

    printf("Number of Received Messages : %lu\n", table.icmpInStats.dwMsgs);
    printf("Number of Received Errors : %lu\n", table.icmpInStats.dwErrors);

  }


public:
  virtual void display()
  {
    getTable();

    display(table);
  } 
};

}
