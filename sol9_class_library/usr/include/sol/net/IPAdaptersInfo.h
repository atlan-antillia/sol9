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
 *  IPAdaptersInfo.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/27
// 2015/12/21 Updated.
 
#pragma once

//2009/09/03
#include <sol/net/MibTable.h>
#include <sol/Arg.h>
#include <sol/String.h>


namespace SOL {

class IPAdaptersInfo :public MibTable {

/*
typedef struct _IP_ADAPTER_INFO {
  struct _IP_ADAPTER_INFO *Next;
  DWORD                   ComboIndex;
  char                    AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
  char                    Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
  UINT                    AddressLength;
  BYTE                    Address[MAX_ADAPTER_ADDRESS_LENGTH];
  DWORD                   Index;
  UINT                    Type;
  UINT                    DhcpEnabled;
  PIP_ADDR_STRING         CurrentIpAddress;
  IP_ADDR_STRING          IpAddressList;
  IP_ADDR_STRING          GatewayList;
  IP_ADDR_STRING          DhcpServer;
  BOOL                    HaveWins;
  IP_ADDR_STRING          PrimaryWinsServer;
  IP_ADDR_STRING          SecondaryWinsServer;
  time_t                  LeaseObtained;
  time_t                  LeaseExpires;
}IP_ADAPTER_INFO, *PIP_ADAPTER_INFO;
 */

private:
  IP_ADAPTER_INFO *info;

public:
  /**
   * Constructor
   */
  IPAdaptersInfo()
  :info(NULL) 
  {
  }


public:
  /**
   * Destructor
   */
  ~IPAdaptersInfo()
  {
    clear();
  }

public:
  void clear()
  {
    if (info) {
      delete [] (char*)info;
      info = NULL;
    }
  }


public:
  //2009/09/03
  bool getTable()
  {
    return getInfo();
  }

public:
  /**
   * Get adapters informaiton by call GetAdaptersInfo
   */
  bool getInfo()
  {
    clear();
        
    bool rc = false;
    DWORD dwSize = 0;
    if (GetAdaptersInfo(NULL, &dwSize) == ERROR_BUFFER_OVERFLOW) {
          info = (IP_ADAPTER_INFO *)new char[dwSize];
    
      if (GetAdaptersInfo(info, &dwSize) == NO_ERROR) {
        rc = true;    
      } else {
        clear();
        throw GetLastError();
      }
    }
    return rc;
  }

protected:
  const char* getType(int type)
  {
    static const ArgT<char> types[] = {
      {"OTHER",     MIB_IF_TYPE_OTHER},
      {"ETHERNET",  MIB_IF_TYPE_ETHERNET},
      {"TOKENRING", MIB_IF_TYPE_TOKENRING},
      {"FDD",       MIB_IF_TYPE_FDDI},
      {"PPP",       MIB_IF_TYPE_PPP},
      {"LOOPBACK",  MIB_IF_TYPE_LOOPBACK},
      {"SLIP",      MIB_IF_TYPE_SLIP},
      };
    int count = XtNumber(types);
    const char* name = "";
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == type) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }



protected:
  // This returns a string of format "00-22-64-70-50-72" for the address
  bool getAdapterAddress(__in const BYTE* bytes, __in size_t length, __out StringT<char>& address)
  {
    bool rc = false;
    if (bytes == NULL) {
      return rc;
    }
    const int BSIZE = 128;
    char buffer[BSIZE];
    memset(buffer, 0, sizeof(buffer));
    
    char* ptr = buffer;
    int bsize = BSIZE;
    for (size_t i = 0; i < length; i++) {      
      if (i == (length - 1)) {            
        sprintf_s(ptr, bsize, "%.2X", (int)bytes[i]);
        ptr = ptr + 2;
        bsize -= 2;
      } else {
        sprintf_s(ptr, bsize, "%.2X-", (int)bytes[i]);
        ptr = ptr + 3;
        bsize -= 3;
      }
    }
    address = buffer;
    rc = true;
    return rc;
  }


public:
  virtual void display(__in IP_ADAPTER_INFO *adapter)
  {      
    printf("Adapter Name: %s\n", adapter->AdapterName);        
    printf("Adapter Desc: %s\n", adapter->Description);
        
    StringT<char> adapterAddr;
    getAdapterAddress(adapter->Address, adapter->AddressLength, adapterAddr);
    printf("Adapter Addr: %s\n", (const char*)adapterAddr);

    printf("Type : %s\n", getType(adapter->Type));  
    printf("IP Address: %s\n", adapter->IpAddressList.IpAddress.String);        
    printf("IP Mask: %s\n", adapter->IpAddressList.IpMask.String);
    printf("Gateway: %s\n", adapter->GatewayList.IpAddress.String);
        
    if (adapter->DhcpEnabled) {            
      printf("Dhcp Enabled: TRUE\n");
      printf("Dhcp Server: %s\n", adapter->DhcpServer.IpAddress.String);
      
      StringT<char> leaseObtained;
      getLocalTime32(adapter->LeaseObtained, leaseObtained);
      
      StringT<char> leaseExpires;
      getLocalTime32(adapter->LeaseExpires, leaseExpires);

      printf("Lease Obtained: %s", (const char*)leaseObtained);
      printf("Lease Expires: %s", (const char*)leaseExpires);
    } else {    
      printf("DHCP Enabled: FALSE\n");
    }
        
    if (adapter->HaveWins) {
      printf("Have Wins: TRUE\n");
      printf("Primary Wins Server: %s\n", adapter->PrimaryWinsServer.IpAddress.String);  
      printf("Secondary Wins Server: %s\n", adapter->SecondaryWinsServer.IpAddress.String);
    } else {
      printf("Have Wins: FALSE\n");
    }
        printf("\n");
    }

public:
  virtual void display()
  {
    if (getInfo()) {
      if (info) {
        IP_ADAPTER_INFO *ptr = info;
        while (ptr) {
          display(ptr);
          ptr = ptr ->Next;
        }
      }
    }    
  }
};


}
