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
 *  IPv6TcpTableOwnerPid.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/24

#pragma once
#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/net/TcpTable.h> 

namespace SOL {
 
class IPv6TcpTableOwnerPid :public TcpTable {
/*
typedef struct {
  DWORD                dwNumEntries;
  MIB_TCP6ROW_OWNER_PID table[ANY_SIZE];
}MIB_TCP6TABLE_OWNER_PID, *PMIB_TCP6TABLE_OWNER_PID;
*/
private:
  MIB_TCP6TABLE_OWNER_PID *table;


public:
  IPv6TcpTableOwnerPid()
  :table(NULL)
  {
  }

public:
  ~IPv6TcpTableOwnerPid() 
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
      AF_INET6,
      TCP_TABLE_OWNER_PID_ALL, 0) == ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_TCP6TABLE_OWNER_PID)new char[dwSize];
       DWORD r = NO_ERROR;  
      if ((r = GetExtendedTcpTable(
                table, &dwSize, TRUE,
          AF_INET6,
          TCP_TABLE_OWNER_PID_ALL, 0)) == NO_ERROR){
      
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
typedef struct _MIB_TCP6ROW_OWNER_PID {
  UCHAR         ucLocalAddr[16];
  DWORD         dwLocalScopeId;
  DWORD         dwLocalPort;
  UCHAR         ucRemoteAddr[16];
  DWORD         dwRemoteScopeId;
  DWORD         dwRemotePort;
  DWORD         dwState;
  DWORD         dwOwningPid;
  } MIB_TCP6ROW_OWNER_PID;
*/
public:
  virtual void display(MIB_TCP6ROW_OWNER_PID& table)
  {
    StringT<char> localIP;
    getIPAddress(table.ucLocalAddr, localIP);
    
    unsigned int localPort = getPort(table.dwLocalPort);
    
    StringT<char> remoteIP; 
    getIPAddress(table.ucRemoteAddr, remoteIP);
 
    unsigned int remotePort = getPort(table.dwRemotePort);
  
    printf("TcpIPv6OwnerPid  LocalIP=[%s]:%d\tRemoteIP=[%s]:%d\tState=%s\tPID=%d\n"
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
