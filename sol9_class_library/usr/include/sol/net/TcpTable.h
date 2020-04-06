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
 *  TcpTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class TcpTable :public MibTable {
/*
typedef struct _MIB_TCPTABLE {
  DWORD      dwNumEntries;
  MIB_TCPROW table[ANY_SIZE];
}MIB_TCPTABLE, *PMIB_TCPTABLE;
*/
private:
  PMIB_TCPTABLE table;

public:
  TcpTable()
  :table(NULL)
  {

  }

public:
  ~TcpTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;

    DWORD dwSize = 0;
    if (GetTcpTable(NULL, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_TCPTABLE)new char[dwSize];
      DWORD r = NO_ERROR;
      if ((r = GetTcpTable(table, &dwSize, FALSE)) == NO_ERROR){
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
typedef struct _MIB_TCPROW {
  DWORD dwState;
  DWORD dwLocalAddr;
  DWORD dwLocalPort;
  DWORD dwRemoteAddr;
  DWORD dwRemotePort;
}MIB_TCPROW, *PMIB_TCPROW;
*/
public:
  virtual void display(MIB_TCPROW& table)
  {
    StringT<char> localIP;
    getIPAddress(table.dwLocalAddr, localIP);
 
    unsigned short localPort = getPort(table.dwLocalPort);
 
    StringT<char> remoteIP;
    getIPAddress(table.dwRemoteAddr, remoteIP);
  
    unsigned short remotePort = getPort(table.dwRemotePort);

    if(table.dwRemoteAddr == 0) {
      remotePort=0;
     }
            
    printf("TCP  LocalIP=%s:%d\tRemoteIP=%s:%d\tState=%s\n",
                     (const char*)localIP,
                     localPort,
                     (const char*)remoteIP,
                     remotePort,
                     getState(table.dwState));
             
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
