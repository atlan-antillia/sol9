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
 *  UnicastIPAddressTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/03

#pragma once
#include <sol/net/IfTable.h>

#include <sol/Arg.h>
#include <sol/String.h>

namespace SOL {
 
class UnicastIPAddressTable :public IfTable {
/*
typedef struct _MIB_UNICASTIPADDRESS_TABLE {
  ULONG                    NumEntries;
  MIB_UNICASTIPADDRESS_ROW Table[ANY_SIZE];
}MIB_UNICASTIPADDRESS_TABLE, *PMIB_UNICASTIPADDRESS_TABLE;
*/
private:
  PMIB_UNICASTIPADDRESS_TABLE table;

private:
  ADDRESS_FAMILY  family;

public:
  UnicastIPAddressTable(ADDRESS_FAMILY f=AF_UNSPEC)
  :table(NULL),
  family(f)
  {

  }

public:
  ~UnicastIPAddressTable() 
  {
    clear();
  }

public:
  virtual bool getTable()
  {
    clear();

    bool rc = false;
    DWORD r = NO_ERROR;
    if ((r = GetUnicastIpAddressTable(family, &table)) == NO_ERROR){
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

public:
  const char* getDadState(int value)
  {
    //The duplicate Address detection (DAD) state. 
    //Duplicate address detection is applicable to both IPv6 and IPv4 addresses. 
    static const ArgT<char> types[] = {
      {"DadStateInvalid",    IpDadStateInvalid},
      {"DadStateTentative",  IpDadStateTentative},
      {"DadStateDuplicate",  IpDadStateDuplicate},
      {"DadStateDeprecated", IpDadStateDeprecated},
      {"DadStatePreferred",  IpDadStatePreferred}
    };

    int count = XtNumber(types);
    const char* name = "";
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
   }
public:
  const char* getPrefixOrigin(int value)
  {
    static const ArgT<char> types[] = {
    {"PrefixOriginOther",               IpPrefixOriginOther},
    {"PrefixOriginManual",              IpPrefixOriginManual},
    {"PrefixOriginWellKnown",           IpPrefixOriginWellKnown},
    {"PrefixOriginDhcp",                IpPrefixOriginDhcp},
    {"PrefixOriginRouterAdvertisement", IpPrefixOriginRouterAdvertisement},
    {"PrefixOriginUnchanged",           IpPrefixOriginUnchanged}
    };
    int count = XtNumber(types);

    const char* name = "";
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

public:
  const char* getSuffixOrigin(int value)
  {
    static const ArgT<char> types[] = {
    {"SuffixOriginOther",            IpSuffixOriginOther},  
    {"SuffixOriginManual",           IpSuffixOriginManual},  
    {"SuffixOriginWellKnown",        IpSuffixOriginWellKnown},  
    {"SuffixOriginDhcp",             IpSuffixOriginDhcp},  
    {"SuffixOriginLinkLayerAddress", IpSuffixOriginLinkLayerAddress},  
    {"SuffixOriginRandom",           IpSuffixOriginRandom},  
    {"SuffixOriginUnchanged",        IpSuffixOriginUnchanged}

    };
    int count = XtNumber(types);

    const char* name = "";
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }
/*
typedef struct _MIB_UNICASTIPADDRESS_ROW {
  SOCKADDR_INET    Address;
  NET_LUID         InterfaceLuid;
  NET_IFINDEX      InterfaceIndex;
  NL_PREFIX_ORIGIN PrefixOrigin;
  NL_SUFFIX_ORIGIN SuffixOrigin;
  ULONG            ValidLifetime;
  ULONG            PreferredLifetime;
  UINT8            OnLinkPrefixLength;
  BOOLEAN          SkipAsSource;
  NL_DAD_STATE     DadState;
  SCOPE_ID         ScopeId;
  LARGE_INTEGER    CreationTimeStamp;
}MIB_UNICASTIPADDRESS_ROW, *PMIB_UNICASTIPADDRESS_ROW;
*/
public:
  virtual void display(MIB_UNICASTIPADDRESS_ROW& table)
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
 
    printf("Prefix Origin : %s\n", getPrefixOrigin(table.PrefixOrigin));
    printf("Suffix Origin : %s\n", getSuffixOrigin(table.SuffixOrigin));
    
    printf("OnLinkPrefixLength : %d\n", table.OnLinkPrefixLength);
             
    printf("SkipAsSource : %s\n", getBoolean(table.SkipAsSource));

    printf("DadState : %s\n", getDadState(table.DadState));

    StringT<char> timeStamp = "";
    getLocalTime(table.CreationTimeStamp, timeStamp);
    printf("CreationTimeStamp : %s\n", (const char*)timeStamp);
  }


public:
  virtual void display()
  {
    if (table == NULL) {
      getTable();
    }

    if (table) {
      for (int i = 0 ; i < (int)table->NumEntries; i++) {
        display(table->Table[i]);
        printf("\n");
      }
    }
  } 
};

}
