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
 *  TcpTableOwnerPid.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/net/TcpTable.h> 

namespace SOL {
 
class TcpTableOwnerPid :public TcpTable {
/*
typedef struct {
  DWORD                dwNumEntries;
  MIB_TCPROW_OWNER_PID table[ANY_SIZE];
}MIB_TCPTABLE_OWNER_PID, *PMIB_TCPTABLE_OWNER_PID;
*/
private:
  MIB_TCPTABLE_OWNER_PID *table;

private:
  MIB_TCPTABLE_OWNER_PID* getTcpTable()
  {
    return table;
  }

public:
  TcpTableOwnerPid()
  :table(NULL)
  {
  }

public:
  ~TcpTableOwnerPid() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {  
    bool rc = false;
    DWORD dwSize=0;

    clear();

    if (GetExtendedTcpTable(NULL,&dwSize, TRUE,
      AF_INET,
      TCP_TABLE_OWNER_PID_ALL,
      0) == ERROR_INSUFFICIENT_BUFFER)
    {
          
      table = (PMIB_TCPTABLE_OWNER_PID)new char[dwSize];
       DWORD r = NO_ERROR;  
      if ((r = GetExtendedTcpTable(
                table, &dwSize, TRUE,
          AF_INET,TCP_TABLE_OWNER_PID_ALL,0)) == NO_ERROR){
  
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
typedef struct _MIB_TCPROW_OWNER_PID {
  DWORD         dwState;
  DWORD         dwLocalAddr;
  DWORD         dwLocalPort;
  DWORD         dwRemoteAddr;
  DWORD         dwRemotePort;
  DWORD         dwOwningPid;
}MIB_TCPROW_OWNER_PID, *PMIB_TCPROW_OWNER_PID;
*/
public:
  virtual void display(MIB_TCPROW_OWNER_PID& table)
  {
    StringT<char> localIP;
    getIPAddress(table.dwLocalAddr, localIP);
    
    unsigned int localPort = getPort(table.dwLocalPort);
    
    StringT<char> remoteIP; 
    getIPAddress(table.dwRemoteAddr, remoteIP);
 
    unsigned int remotePort = getPort(table.dwRemotePort);
  
    if(table.dwRemoteAddr==0) {
      remotePort=0;
     }

    printf("TcpOwnerModule  LocalIP=%s:%d\t RemoteIP=%s:%d\tState=%s\tPID=%d\n"
                     ,(const char*)localIP
                     ,localPort
                     ,(const char*)remoteIP
                     ,remotePort
                     ,getState(table.dwState),
           table.dwOwningPid);
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
