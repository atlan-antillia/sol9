/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IPAdapterAddresses.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/28

#pragma once


#include <sol\Object.h>
#include <sol\String.h>
#include <sol\StringConverter.h>
#include <sol\ByteArray.h>
#include <sol/ArgT.h>

namespace SOL {
/*
typedef struct {
  const char* name;
  int value;
} NamedValue;
*/

class IPAdapterAddresses: public Object {

private:
  PIP_ADAPTER_ADDRESSES adapters;
  int count;

public:
  /**
   * Constructor
   */
  IPAdapterAddresses()
    :adapters(NULL),
    count(0)
  {
  }

  
public:
  int  listup()
  {
    clear();

    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    // default to unspecified address family (both)
      ULONG family = AF_UNSPEC;

    ULONG len = 0;   

    // Get bytes-ValidCount to enumereate adapters.
    DWORD rc = GetAdaptersAddresses(family, flags, 0, 0, &len);

    if (len <= 0) {
      return 0;
    }

       this->adapters = (PIP_ADAPTER_ADDRESSES)new BYTE[len];

    //Enumerate adapters
    rc = GetAdaptersAddresses(family, flags, 0, this->adapters, &len);   

       if(rc != ERROR_SUCCESS){  
            delete [] adapters;
            throw rc;
       }
    this->count = getAvailableAdapterCount();
    return this->count;
  }

public:
  int getAvailableAdapterCount()
  {
    int count = 0;
    for(PIP_ADAPTER_ADDRESSES adpt = this->adapters; adpt; adpt = adpt->Next){
      count++;
      //Don't ignore data_link or loop_back
      /*
      if(adpt->PhysicalAddressLength == 0 ||  
         adpt->IfType == IF_TYPE_SOFTWARE_LOOPBACK ) {
        printf("Ignore \n");
        continue;     // Ignore
      }
      */
       } //for
    return count;
  }


public:
  bool getNameInfo(PIP_ADAPTER_UNICAST_ADDRESS unicastAddress,
      String& name, String& prefix, String& suffix)
  {
    bool rc = false;  
    if (unicastAddress) {
      char address[NI_MAXHOST];
      memset(address, 0, sizeof(address));    
      if (getnameinfo(unicastAddress->Address.lpSockaddr,
            unicastAddress->Address.iSockaddrLength,
            address, sizeof(address), NULL, 0,
            NI_NUMERICHOST) ==0) {
        name = address;
        nameForIPPrefixOrigin(unicastAddress->PrefixOrigin, prefix);
        nameForIPSuffixOrigin(unicastAddress->SuffixOrigin, suffix);

        rc = true;
      }
      }
    return rc;
  }

public:
  bool getFamilyName(SOCKET_ADDRESS& sockAddress, String& name) 
  {
    bool rc = false;

    static const ArgT<char> types[] ={
    {"IPv4",    AF_INET},  
    {"IPv6",    AF_INET6}, 
    };

    int family = sockAddress.lpSockaddr->sa_family;

    int num = CountOf(types);///sizeof(types[0]);
    for (int j = 0; j<num; j++) {
      if (family == (int)types[j].value) {
        name = types[j].name;
        rc = true;
        break;
      }
    }
    return rc;
  }


public:
  bool getNameOfAddress(SOCKET_ADDRESS& sockAddress, String& name)
  {
    bool rc = false;    
    char address[NI_MAXHOST];
    memset(address, 0, sizeof(address));    
    if (getnameinfo(sockAddress.lpSockaddr,
      sockAddress.iSockaddrLength,
      address, sizeof(address), NULL, 0,NI_NUMERICHOST) ==0) {
    
      name = address;
      rc = true;
    }

    return rc;
  }

public:
  bool nameForIPPrefixOrigin(IP_PREFIX_ORIGIN index, String& name)
  {
    bool rc = false;

      const char* items[] = {
    "Other",
    "Manual",
    "WellKnown",
    "Dhcp",
    "RouterAdvertisement"};
    
    if (index>=0 && index < sizeof(items)/sizeof(items[0])) {
      name = items[index];
      rc = true;
    }
    return rc;;
  }


public:
  bool nameForIPSuffixOrigin(IP_SUFFIX_ORIGIN index, String& name)
  {
    bool rc = false;

    const char* items[] = {
    "Other",
    "Manual",
    "WellKnown",
    "Dhcp",
    "LinkLayerAddress",
    "Random"};

    if (index>=0 && index < sizeof(items)/sizeof(items[0])) {
      name = items[index];
      rc = true;
    }
    return rc;
  }


public:
  bool getNameOfOperStatus(int status, __out String& name) {

    bool rc = false;
    static const ArgT<char> types[] ={
    {"Up",      IfOperStatusUp},  
    {"Down",    IfOperStatusDown}, 
    {"Testing",   IfOperStatusTesting},
    {"Unknown",    IfOperStatusUnknown},
    {"Dormant",    IfOperStatusDormant},
    {"NotPresent",  IfOperStatusNotPresent},
    {"LowerLayerDown", IfOperStatusLowerLayerDown}
    };
    
    int num = sizeof(types)/sizeof(types[0]);
    for (int j = 0; j<num; j++) {
      if (status == (int)types[j].value) {
        name = types[j].name;
        rc = true;
        break;
      }
    }
    return rc;
  }

public:
  bool getNameOfIfType(int type, String& name) {
    bool rc = false;
    static const ArgT<char> types[] ={
    {"ETHERNET_CSMACD",    IF_TYPE_ETHERNET_CSMACD},
    {"PPP",                IF_TYPE_PPP},
    {"SOFTWARE_LOOPBACK",  IF_TYPE_SOFTWARE_LOOPBACK},
    {"TUNNEL",             IF_TYPE_TUNNEL},
    };

    int num = sizeof(types)/sizeof(types[0]);
    
    for (int j = 0; j<num; j++) {
      if (type == (int)types[j].value) {
        name = types[j].name;
        rc = true;
        break;
      }
    }
    return rc;
  }


public:

  ~IPAdapterAddresses() {
    clear();
  }

private:
  void clear()
  {
    if (this->adapters) {
      delete [] this->adapters;    
      this->adapters = NULL;
    }
    this->count = 0;
  }

public:
  int getCount() {
    return this->count;
  }

public:

  PIP_ADAPTER_ADDRESSES getAdaptersAddresses(int& count) {
    count = this->count;
    return this->adapters;
  }

public:
  bool getAddress(int index, IP_ADAPTER_ADDRESSES& address) {
    bool rc = false;
    if (index>=0 && index< count) {

      //value= adapterName[index];
      memcpy(&address, &adapters[index], sizeof(IP_ADAPTER_ADDRESSES));
      rc = true;
    }
    return rc;
  }

public:
  void  dump()
  {
    int n = 0;

    StringConverter converter;

    for(PIP_ADAPTER_ADDRESSES adpt = this->adapters; 
        adpt!=NULL; adpt = adpt->Next){
      //Ignore loop_back
      
      if(  
         adpt->IfType == IF_TYPE_SOFTWARE_LOOPBACK ) {
        printf("Ignore %d\n", n);
        continue;     // Ignore 
      }
    
      printf("---\n");
      const char* cfname = adpt->AdapterName;
      printf("AdaperName:%s\n", cfname);

      String nameType;
      getNameOfIfType(adpt->IfType, nameType);
      
      printf("Type=%s\n", (const TCHAR*)nameType);

      String operStatus;
      getNameOfOperStatus(adpt->OperStatus, operStatus);
       

      //adpt->Description
      char *desc = converter.toMultiByte(adpt->Description);
      char* friendlyName = converter.toMultiByte(adpt->FriendlyName);
      printf("Description=%s FriendlyName=%s operStatus=%s \n", 
        desc, friendlyName,
        (const TCHAR*)operStatus);

      delete [] desc;
      delete [] friendlyName;

      printf("Unicast:\n");
      PIP_ADAPTER_UNICAST_ADDRESS unicastAddress = adpt->FirstUnicastAddress;
      while(unicastAddress) {
        String name;
        String prefix;
        String suffix;
        getNameInfo(unicastAddress, name, prefix, suffix);
        printf("Address=%s prefix=%s suffix=%s\n", 
          (const TCHAR*)name, (const TCHAR*)prefix, (const TCHAR*)suffix);
        unicastAddress = unicastAddress->Next;
      }

      printf("Anycast:\n");

      PIP_ADAPTER_ANYCAST_ADDRESS acAddress = adpt->FirstAnycastAddress;
      while(acAddress) {
        String name;
        getNameOfAddress(acAddress->Address, name);
        printf("%s\n", (const TCHAR*)name);

        acAddress = acAddress->Next;
      }

      printf("Multicast:\n");
      PIP_ADAPTER_MULTICAST_ADDRESS mcAddress = adpt->FirstMulticastAddress;
      while(mcAddress) {
        String name;

        getNameOfAddress(mcAddress->Address, name);
        printf("%s\n", (const TCHAR*)name);

        mcAddress = mcAddress->Next;

      }


      printf("DnsServer:\n");
      PIP_ADAPTER_DNS_SERVER_ADDRESS dsAddress = adpt->FirstDnsServerAddress;
      while(dsAddress) {
        String name;

        getNameOfAddress(dsAddress->Address, name);
        printf("%s\n", (const TCHAR*)name);

        dsAddress = dsAddress->Next;

      }
      if (adpt->PhysicalAddressLength>0) {
        ByteArray bytes;
        bytes.set(adpt->PhysicalAddress,
            adpt->PhysicalAddressLength);
         printf("PhysicalAddress:");
        bytes.dump();
      }

      n++;
       } //for

  }
};

}
