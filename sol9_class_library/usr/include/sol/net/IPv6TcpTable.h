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
 *  IPv6TcpTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
/*
typedef struct _MIB_TCP6TABLE {
  DWORD       dwNumEntries;
  MIB_TCP6ROW table[ANY_SIZE];
}MIB_TCP6TABLE, *PMIB_TCP6TABLE;
 */
class IPv6TcpTable :public MibTable {

private:
  PMIB_TCP6TABLE table;

public:
  IPv6TcpTable()
  :table(NULL)
  {

  }


public:
  ~IPv6TcpTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;

    DWORD dwSize = 0;
    if (GetTcp6Table(NULL, &dwSize, FALSE)  == ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_TCP6TABLE)new char[dwSize];
      DWORD r = NO_ERROR;
      if ((r = GetTcp6Table(table, &dwSize, FALSE)) == NO_ERROR ){
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
typedef struct _MIB_TCP6ROW {
  MIB_TCP_STATE State;
  IN6_ADDR      LocalAddr;
  DWORD         dwLocalScopeId;
  DWORD         dwLocalPort;
  IN6_ADDR      RemoteAddr;
  DWORD         dwRemoteScopeId;
  DWORD         dwRemotePort;
}MIB_TCP6ROW, *PMIB_TCP6ROW;

The dwLocalScopeId, and dwRemoteScopeId members are in network byte order. 
In order to use the dwLocalScopeId or dwRemoteScopeId members, 
the ntohl or inet_ntoa functions in Windows Sockets or similar functions may be needed. 
*/
public:
  virtual void display(MIB_TCP6ROW& table)
  {
    StringT<char> localIP;
    getIPAddress(table.LocalAddr, localIP);
 
    unsigned short localPort = getPort(table.dwLocalPort);
 
    StringT<char> remoteIP;
    getIPAddress(table.RemoteAddr, remoteIP);
  
    unsigned short remotePort = getPort(table.dwRemotePort);

    unsigned long localScopeId = getScopeId(table.dwLocalScopeId);

    unsigned long remoteScopeId = getScopeId(table.dwRemoteScopeId);
                 
    printf("TcpIPv6  LocalIP=[%s]:%d %ul \tRemoteIP=[%s]:%d %ul \tState=%s\n",
                     (const char*)localIP,
                     localPort,
                     localScopeId,
                     (const char*)remoteIP,
                     remotePort,
                     remoteScopeId,
                     getState(table.State));
             
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
