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
 *  IPv6UdpTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class IPv6UdpTable :public MibTable {
/*
typedef struct _MIB_UDP6TABLE {
  DWORD       dwNumEntries;
  MIB_UDP6ROW table[ANY_SIZE];
}MIB_UDP6TABLE, *PMIB_UDP6TABLE;
*/
private:
  PMIB_UDP6TABLE table;

public:
  IPv6UdpTable()
  :table(NULL)
  {
  }

public:
  ~IPv6UdpTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;

    DWORD dwSize = 0;
    if (GetUdp6Table(NULL, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_UDP6TABLE)new char[dwSize];
      DWORD r = NO_ERROR;
      if ((r = GetUdp6Table(table, &dwSize, FALSE)) == NO_ERROR){
        rc = true;
      } else {
        clear();
        throw r;
      }
    }
    return rc;
  }

public:
  void clear()
  {
    if (table) {
      delete [] (char*)table;
      table = NULL;
    }
  }


/*
typedef struct _MIB_UDP6ROW {
  IN6_ADDR dwLocalAddr;
  DWORD    dwLocalScopeId;
  DWORD    dwLocalPort;
}MIB_UDP6ROW, *PMIB_UDP6ROW;

The dwLocalScopeId and dwLocalPort members are in network byte order. 
In order to use the dwLocalScopeId and dwLocalPort members, 
the ntohs or inet_ntoa functions in Windows Sockets or similar functions may be needed. 
 */

public:
  virtual void display(MIB_UDP6ROW& table)
  {
    StringT<char> localIP;
    getIPAddress(table.dwLocalAddr, localIP);
 
    unsigned short localPort = getPort(table.dwLocalPort);

    //dwLocalScopedId can be converted by using nthos, so call getPort() 
    unsigned long localScopeId = getPort(table.dwLocalScopeId);
                
    printf("UDP6  LocalIP=[%s]:%d localScopeId(%ul)\n",
                     (const char*)localIP,
                     localPort, //);
                      localScopeId);
  }


public:
  virtual void display()
  {
    if (table == NULL) {
      getTable();
    }
    if (table) {
      for (int i = 0 ; i < (int)table->dwNumEntries; i++) {
        display(table->table[i]);
        printf("\n");
      }
    }
  } 

};

}
