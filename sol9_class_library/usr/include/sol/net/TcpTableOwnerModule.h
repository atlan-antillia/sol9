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
 *  TcpTableOwnerModule.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/net/TcpTable.h> 

namespace SOL {
 
class TcpTableOwnerModule :public TcpTable {

/*
typedef struct {
  DWORD                   dwNumEntries;
  MIB_TCPROW_OWNER_MODULE table[ANY_SIZE];
}MIB_TCPTABLE_OWNER_MODULE, *PMIB_TCPTABLE_OWNER_MODULE;
*/
private:
  MIB_TCPTABLE_OWNER_MODULE *table;

private:
  MIB_TCPTABLE_OWNER_MODULE* getTcpTable()
  {
    return table;
  }

public:
  TcpTableOwnerModule()
  :table(NULL)
  {
  }

public:
  ~TcpTableOwnerModule() 
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
      TCP_TABLE_OWNER_MODULE_ALL,
      0) == ERROR_INSUFFICIENT_BUFFER) {
          
      table = (PMIB_TCPTABLE_OWNER_MODULE)new char[dwSize];
       DWORD r = NO_ERROR;  
      if ((r = GetExtendedTcpTable(
                table, &dwSize, TRUE,
          AF_INET,TCP_TABLE_OWNER_MODULE_ALL,0)) == NO_ERROR){
  
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


protected:
  bool getOwnerModule(PMIB_TCPROW_OWNER_MODULE pTcpEntry, _bstr_t& moduleName, _bstr_t& modulePath)
  {
    bool rc = false;

    DWORD dwSize = 0; 
    
    //DWORD drc = 
    GetOwnerModuleFromTcpEntry(
      pTcpEntry,
      TCPIP_OWNER_MODULE_INFO_BASIC ,
      NULL,
      &dwSize);

    TCPIP_OWNER_MODULE_BASIC_INFO* info = (TCPIP_OWNER_MODULE_BASIC_INFO*)new char[dwSize];
      
    if ( GetOwnerModuleFromTcpEntry(
      pTcpEntry,
      TCPIP_OWNER_MODULE_INFO_BASIC, 
      info,
      &dwSize) == NO_ERROR) {

      moduleName = info->pModuleName;
      modulePath = info->pModulePath;

      rc = true;
    }

    delete [] (char*)info;

    return rc;
  }

/*
typedef struct _MIB_TCPROW_OWNER_MODULE {
  DWORD         dwState;
  DWORD         dwLocalAddr;
  DWORD         dwLocalPort;
  DWORD         dwRemoteAddr;
  DWORD         dwRemotePort;
  DWORD         dwOwningPid;
  LARGE_INTEGER liCreateTimestamp;
  ULONGLONG     OwningModuleInfo[TCPIP_OWNING_MODULE_SIZE];
}MIB_TCPROW_OWNER_MODULE, *PMIB_TCPROW_OWNER_MODULE;
*/
public:
  virtual void display(MIB_TCPROW_OWNER_MODULE& table)
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

    _bstr_t moduleName = L"";
    _bstr_t modulePath = L"";
    getOwnerModule(&table, moduleName, modulePath); 
    printf("TcpOwnerModule  LocalIP=%s:%d\t RemoteIP=%s:%d\tState=%s\tPID=%d ModuleName=%s ModulePath=%s\n"
                     ,(const char*)localIP
                     ,localPort
                     ,(const char*)remoteIP
                     ,remotePort
                     ,getState(table.dwState),
           table.dwOwningPid,
          (const char*)moduleName,
          (const char*)modulePath);
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
