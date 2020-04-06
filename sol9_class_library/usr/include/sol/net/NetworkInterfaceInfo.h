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
 *  NetworkInterfaceList.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/15

// 2008/11/10 Modified a bug in the method isConnectedToInternet.

#pragma once

#include <sol\Object.h>
#include <sol\String.h>

//#pragma comment("lib", "ws2_32.lib")
//#pragma comment("lib", "iphlpapi.lib")

#ifndef _SOL_NETWORKINTERFACEINFO
#define _SOL_NETWORKINTERFACEINFO

namespace SOL {

class NetworkInterfaceInfo :public Object {

private:
  INTERFACE_INFO  list[40];
  int    listNum;      //The number of size of list.
  int    upCount;      //The number of UP state.

public:
  /**
   * Constructor
   */
  NetworkInterfaceInfo()
  :listNum(0),
  upCount(0)
  {
  }

public:
  /**
   * Listup all network interface information using WSAIoctl(sd, SIO_GET_INTERFACE_LIST...)
   */
  int listup() 
  {
    clear();

    SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
    if (sd == SOCKET_ERROR) {
      throw SOCKET_ERROR;
    }

    unsigned long nBytes =0;

    if (WSAIoctl(sd, SIO_GET_INTERFACE_LIST, 0, 0, &list,
      sizeof(list), &nBytes, 0, 0) == SOCKET_ERROR) {
      throw SOCKET_ERROR;
    }

    closesocket(sd);
    
    this->listNum = nBytes/sizeof(INTERFACE_INFO);

    this->upCount = getUpCount(listNum);
    
    return this->upCount;

  }

private:
  /**
   * Compute the count of Up network interfaces. 
   */
  int getUpCount(int listNum)
  {
    int  n = 0;  //Get the number of up-interfaces,not including a LOOPBACK.
    for (int i = 0; i <listNum; i++) {
      u_long nFlags = list[i].iiFlags;
      
          if (nFlags & IFF_LOOPBACK) {
        continue;  //Skip loopback
      }
      
      if (nFlags & IFF_UP) {// "up";
        n++;
      }
    }
    return n;
  }
 
public:
  /**
   * Destructor
   */
  ~NetworkInterfaceInfo() {
    clear();
  }


private: 
  void clear() {
    memset(list, 0, sizeof(list));

    this->upCount = 0;
    this->listNum = 0;
  }


public:
  /**
   * Get the count of UP network interfaces, not including a loopback(127....).
   */
  int getUpCount() {
    return this->upCount;
  }


public:
  /**
   * Get the IP address of UP network interfaces, not including a loopback(127....).
   *
   */
  bool getUpIPAddress(int index, __out StringT<char>& address) 
  {
    bool rc = false;

    address = "";

    if (index <0 || index>=upCount) {
      // should throw OutOfRangeException.
      return rc;
    }

    int n = 0;
    for (int i = 0; i <listNum; i++) {
      u_long nFlags = list[i].iiFlags;
      
          if (nFlags & IFF_LOOPBACK) {
        continue;  //Skip loopback
      }
      
      if (nFlags & IFF_UP) {
        if (n == index) {
          sockaddr_in *addr = (sockaddr_in *)&(list[i].iiAddress);
          address = inet_ntoa(addr->sin_addr);
          rc = true;
          break;
        }
        n++;
      }    
    }
    return rc;
  }

public:
  /**
   * Get the IP address of UP network interfaces, not including a loopback(127....).
   *
   */
  //2009/11/01
  bool getUpIPAddress(int index, __out String& address) 
  {
    bool rc = false;

    address = "";

    if (index <0 || index>=upCount) {
      // should throw OutOfRangeException.
      return rc;
    }

    int n = 0;
    for (int i = 0; i <listNum; i++) {
      u_long nFlags = list[i].iiFlags;
      
          if (nFlags & IFF_LOOPBACK) {
        continue;  //Skip loopback
      }
      
      if (nFlags & IFF_UP) {
        if (n == index) {
          sockaddr_in *addr = (sockaddr_in *)&(list[i].iiAddress);
          address = inet_ntoa(addr->sin_addr);
          rc = true;
          break;
        }
        n++;
      }    
    }
    return rc;
  }

public:
  /**
   * Get UP-network interfaces info, not including a loopback(127....).
   *
   */
  bool getUpInterface(int index, INTERFACE_INFO& info) 
  {
    bool rc = false;


    if (index <0 || index>=upCount) {
      // should throw OutOfRangeException.
      return rc;
    }

    int n = 0;
    for (int i = 0; i <listNum; i++) {
      u_long nFlags = list[i].iiFlags;
      
          if (nFlags & IFF_LOOPBACK) {
        continue;  //Skip loopback
      }
      
      if (nFlags & IFF_UP) {
        if (n == index) {
          memcpy(&info, &list[i], sizeof(INTERFACE_INFO));
          rc = true;
          break;
        }
        n++;
      }    
    }
    return rc;
  }

public:
  /**
   * Is connected to Internet?
   */
  //2008/11/10 Modified
  bool isConnectedToInternet() 
  {
    bool rc = false;
    static const char* CLASS_C = "192.";

    //2008/11/10 Modifed (upCount > 1) 
    if (upCount > 0) {

      for (int i = 0; i< upCount; i++) {
        StringT<char> address = "";
        getUpIPAddress(i, address);
        if (!address.startsWith(CLASS_C)) {
          rc = true;
          break;
        }
      }
    }
    return rc;
  }

public:
  /**
   * Is connected to local private address(Class C private) only,
   * not including a loopback?
   * 
   */
  bool isClassCPrivateAddressOnly() {
    static const char* CLASS_C_PRIVATE = "192.168.";
    
    bool rc = false;
    if (upCount == 1) {
      StringT<char> address = "";
      getUpIPAddress(0, address);
      if (address.startsWith(CLASS_C_PRIVATE)) {
        rc = true;
      }
    }
    return rc;
  }

public:
  void dump()
  {
    for (int i = 0; i <listNum; i++) {
      u_long nFlags = list[i].iiFlags;
        
      sockaddr_in *addr = (sockaddr_in *)&(list[i].iiAddress);
      char* address = inet_ntoa(addr->sin_addr);
      char* state = "Unknown";
      if (nFlags & IFF_UP) {
        state = "Up  ";
      } 
      printf("%s %s\n", state, address);
    }

  }

};

}

#endif

