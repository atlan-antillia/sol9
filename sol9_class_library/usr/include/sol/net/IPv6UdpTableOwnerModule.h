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
 *  IPv6UdpTableOwnerModule.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/24

#pragma once
#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/net/UdpTable.h> 

namespace SOL {

class IPv6UdpTableOwnerModule :public UdpTable {

/*
typedef struct {
  DWORD                 dwNumEntries;
  MIB_UDP6ROW_OWNER_MODULE table[ANY_SIZE];
}MIB_UDP6TABLE_OWNER_MODULE, *PMIB_UDP6TABLE_OWNER_MODULE;
 */

private:
  MIB_UDP6TABLE_OWNER_MODULE *table;

public:
  IPv6UdpTableOwnerModule()
  :table(NULL)
  {
  }


public:
  ~IPv6UdpTableOwnerModule() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {  
    bool rc = false;
    DWORD dwSize=0;

    clear();

    if (GetExtendedUdpTable(NULL, &dwSize, TRUE,
      AF_INET6,
      UDP_TABLE_OWNER_MODULE,
      0) == ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_UDP6TABLE_OWNER_MODULE)new char[dwSize];
       DWORD r = NO_ERROR;  
      if ((r = GetExtendedUdpTable(table, &dwSize, TRUE,
          AF_INET6, 
          UDP_TABLE_OWNER_MODULE,
          0)) == NO_ERROR){
        
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

  bool getOwnerModule(PMIB_UDP6ROW_OWNER_MODULE pEntry, _bstr_t& moduleName, _bstr_t& modulePath)
  {
    bool rc = false;

    DWORD dwSize = 0; 
    
    //DWORD drc = 
    GetOwnerModuleFromUdp6Entry(
      pEntry,
      TCPIP_OWNER_MODULE_INFO_BASIC ,
      NULL,
      &dwSize);

    TCPIP_OWNER_MODULE_BASIC_INFO* info = (TCPIP_OWNER_MODULE_BASIC_INFO*)new char[dwSize];
      
    if ( GetOwnerModuleFromUdp6Entry(
      pEntry,
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

typedef struct _MIB_UDP6ROW_OWNER_MODULE {
  UCHAR         ucLocalAddr[16];
  DWORD         dwLocalScopeId;
  DWORD         dwLocalPort;
  DWORD         dwOwningPid;
  LARGE_INTEGER liCreateTimestamp;
  union {
    struct {
      int SpecificPortBind  :1;
    } ;
    int dwFlags;
  } ;
  ULONGLONG     OwningModuleInfo[TCPIP_OWNING_MODULE_SIZE];
}MIB_UDP6ROW_OWNER_MODULE, *PMIB_UDP6ROW_OWNER_MODULE;
*/
public:
  virtual void display(MIB_UDP6ROW_OWNER_MODULE& table)
  {
    StringT<char> localIP;
    getIPAddress(table.ucLocalAddr, localIP);
    
    unsigned int localPort = getPort(table.dwLocalPort);

    _bstr_t moduleName = L"";
    _bstr_t modulePath = L"";
    
    MIB_UDP6ROW_OWNER_MODULE tmp;
    memset(&tmp, 0, sizeof(tmp));
    memcpy(&tmp, &table, sizeof(table));

    getOwnerModule(&tmp, moduleName, modulePath);


    printf("UdpIPv6  LocalIP=[%s]:%d\tPID=%d\tModuleName=%s\tModulePath=%s\n"
                     ,(const char*)localIP
                     ,localPort
           ,table.dwOwningPid,
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
