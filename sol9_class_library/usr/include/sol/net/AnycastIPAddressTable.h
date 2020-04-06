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
 *  AnycastIPAddressTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/03

#pragma once
#include <sol/net/IfTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class AnycastIPAddressTable :public IfTable {
/*
typedef struct _MIB_ANYCASTIPADDRESS_TABLE {
  ULONG                    NumEntries;
  MIB_ANYCASTIPADDRESS_ROW Table[ANY_SIZE];
}MIB_ANYCASTIPADDRESS_TABLE, *PMIB_ANYCASTIPADDRESS_TABLE;
*/
private:
  PMIB_ANYCASTIPADDRESS_TABLE table;

private:
  ADDRESS_FAMILY  family;

public:
  AnycastIPAddressTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {

  }

public:
  ~AnycastIPAddressTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    DWORD r = NO_ERROR;
    if ((r = GetAnycastIpAddressTable(family, &table)) == NO_ERROR){
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
    if (table) {
      FreeMibTable(table);
      table = NULL;
    }
  }

/*
typedef struct _MIB_ANYCASTIPADDRESS_ROW {
  SOCKADDR_INET Address;
  NET_LUID      InterfaceLuid;
  NET_IFINDEX   InterfaceIndex;
  SCOPE_ID      ScopeId;
}MIB_ANYCASTIPADDRESS_ROW, *PMIB_ANYCASTIPADDRESS_ROW;
*/

public:
  virtual void display(MIB_ANYCASTIPADDRESS_ROW& table)
  {
    StringT<char> family = "";
    StringT<char> address = "" ;
    unsigned short port = 0;
    getIPAddress(table.Address, family, address, port);
    printf("Family %s Address : %s\n", (const char*)family, (const char*)address);

    printf("Interface index : %lu\n", table.InterfaceIndex);
        printf("Interface LUID NetLuidIndex : %lu\n",table.InterfaceLuid.Info.NetLuidIndex);
    char interfaceName[MAX_PATH];
    if (ConvertInterfaceLuidToNameA(&(table.InterfaceLuid),interfaceName, sizeof(interfaceName)) == NO_ERROR) {
      printf("Interface LUID Name : %s\n", interfaceName);
    }

        printf("Interface LUID IfType : %s\n",
      getInterfaceType(table.InterfaceLuid.Info.IfType));
 
  }


public:
  virtual void display()
  {
    if (table == NULL) {
      getTable();
    }
    //printf("%d \n", table->NumEntries);
    if (table) {
      for (int i = 0 ; i < (int)table->NumEntries; i++) {
        display(table->Table[i]);
        printf("\n");
      }
    }
  } 
};

}
