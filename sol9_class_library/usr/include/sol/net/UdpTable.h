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
 *  UdpTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/MibTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class UdpTable :public MibTable {
/*
typedef struct _MIB_UDPTABLE {
  DWORD      dwNumEntries;
  MIB_UDPROW table[ANY_SIZE];
}MIB_UDPTABLE, *PMIB_UDPTABLE;
 */
private:
  PMIB_UDPTABLE table;

public:
  UdpTable()
  :table(NULL)
  {
  }

public:
  ~UdpTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;

    DWORD dwSize = 0;
    if (GetUdpTable(NULL, &dwSize, FALSE)== ERROR_INSUFFICIENT_BUFFER) {

      table = (PMIB_UDPTABLE)new char[dwSize];
      DWORD r = NO_ERROR;  
      if ((r = GetUdpTable(table, &dwSize, FALSE)) == NO_ERROR) {
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
typedef struct _MIB_UDPROW {
  DWORD dwLocalAddr;
  DWORD dwLocalPort;
}MIB_UDPROW, *PMIB_UDPROW;
*/
public:
  virtual void display(MIB_UDPROW& table)
  {
    StringT<char> localIP;
    getIPAddress(table.dwLocalAddr, localIP);
 
    unsigned short localPort = getPort(table.dwLocalPort);
    printf("UDP  LocalIP=%s:%d\n",
                     (const char*)localIP,
                     localPort);
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
