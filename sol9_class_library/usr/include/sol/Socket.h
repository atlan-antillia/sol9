/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Socket.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2010/12/08 Updated to be more applicable to IPv6 

// SOL++2000
// 1999.06.12  Added sendAll method. 
// 1999.07.03  Added readLine method.
// 1999.08.10  Added new bind method.
// 1999.08.16  Added a timeout argument to sendAll method.
// 1999.08.22  Added a printf method and a buffer variable to use printf method.
#pragma once

//2010/04/07
/*
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
*/
#include <sol\Object.h>
#include <sol\InvalidSocketException.h>
#include <time.h>

#include <sol\InetAddress.h>

#include <sol\StringBuffer.h>

/**
 * Socket class
 */
namespace SOL {

class Socket :public Object {
private:
  int     domain;
  int     type;
  int     protocol;
  SOCKET  fd;

public:
  /**
   * This constructor doesn't create a socket. You have to call 'create' method explicitly to get it.
   */
  Socket(int domain1=AF_INET) 
    :domain(domain1),
    type(SOCK_STREAM),
    protocol(0),
    fd(INVALID_SOCKET)
  {
    //You have to call Socket::create method to get a valid socket handle.
  }


public:
  /**
   * @domain: AF_INET or AF_INET6
   * @tyos : SOCK_STREAM or SOCK_DGRAM
   * @protocol: IPPROTO_TCP or IPPROTO_UDP
   */
  Socket(int domain1, int type1,  int protocol1) 
    :domain(domain1),
    type(type1),
    protocol(protocol1),
    fd(INVALID_SOCKET)
  {
    this->fd = ::socket(domain, type, protocol);

    if(this->fd == INVALID_SOCKET) {
      throw InvalidSocketException("Socket::Socket. Failed to create a socket", ::WSAGetLastError());
    
    }
  }

public:
  /**
   *
   */
  ~Socket() 
  {
    close();
  }

public:
  // 1999.08.10 int address -> unsigned long
  /**
   * @port  This is port number of host-byte-order.
   * @address IPv4 address.
   */
  // This is only for IPv4 
  int bind(unsigned short port, unsigned long address) 
  {
    //This is for IPv4, domain is AF_INET
    SOCKET soc = getSocket();

    sockaddr_in inet;
    memset(&inet, 0, sizeof(inet));
    inet.sin_family =(ADDRESS_FAMILY) domain;
    inet.sin_port   = htons(port);
    inet.sin_addr.s_addr = htonl(address);
    return ::bind(soc, (sockaddr*)&inet, sizeof(inet));
  }

// 1999.08.10
public:
  /**
   *
   */
  int bind(InetAddress& address)
  {
    //This is for IPv4
    SOCKET soc = getSocket();

    sockaddr_in* addr = address.getAddress();
    return ::bind(soc, (sockaddr*)addr, address.getSize());
  }

public:
  /**
   * @inet In practice, this s a pointer to sockaddr_in (IPv4) or sockaddr_in (IPv6).
   */
  //2010/12/4 
  int bind(sockaddr* inet) 
  {
    int rc = 0;;

    if (inet) {
      SOCKET soc = getSocket();
      int size = sizeof(sockaddr_in);  //IPv4;
      int family =  inet->sa_family;
      if (family == AF_INET6) {
        //IPv6
        size = sizeof(sockaddr_in6);
      }
      rc  = ::bind(soc, inet, size);
    } else {
      throw Exception("Socket::bind:Inavlid parameter.");
    }
    return rc;
  }


public:
  /**
   * 
   */
  //2010/12/4 
  int bind(sockaddr_in* inet) 
  {
    int rc = 0;;

    if (inet) {
      SOCKET soc = getSocket();
      int size = sizeof(sockaddr_in);  //IPv4;
      rc  = ::bind(soc, (sockaddr*)inet, size);
    } else {
      throw Exception("Socket::bind:Invalid parameter.");
    }
    return rc;
  }

public:
  /**
   * 
   */
  //2010/12/4 
  int bind(sockaddr_in6* inet) 
  {
    int rc = 0;;

    if (inet) {
      SOCKET soc = getSocket();
      int size = sizeof(sockaddr_in6);  //IPv6;
      rc  = ::bind(soc, (sockaddr*)inet, size);
    } else {
      throw Exception("Socket::bind:Invalid parameter.");
    }
    return rc;
  }
/*
typedef struct addrinfo {
  int             ai_flags;
  int             ai_family;
  int             ai_socktype;
  int             ai_protocol;
  size_t          ai_addrlen;
  char            *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
} ADDRINFOA, *PADDRINFOA;

public:
  /**
   * @info This s a pointer to addrinfo (IPv4 or IPv6).
   */
  //2010/12/4 
  int bind(ADDRINFO* info) 
  {
    int rc = 0;;

    if (info) {
      SOCKET soc = getSocket();
      rc  = ::bind(soc, info->ai_addr, info->ai_addrlen);
    } else {
      throw Exception("Socket::bind:Invalid parameter.");
    }
    return rc;
  }

public:
  /**
   *
   */
  bool close() 
  {
    bool rc = false;
    if(this->fd != INVALID_SOCKET) {
      ::closesocket(this->fd);
      this->fd = INVALID_SOCKET;
      rc= true;
    }
    return rc;
  }

public:
  /**
   *
   */
  SOCKET create(int domain, int type, int protocol) 
  {
    if(this->fd != INVALID_SOCKET) {
      //If already created, return it.
      return this->fd;
    }
    else {
      this -> domain = domain;
      this -> type   = type;
      this -> protocol = protocol;
      this ->fd = ::socket(domain, type, protocol);

      if(this->fd == INVALID_SOCKET) {
        throw InvalidSocketException("Socket::create. Failed to create a socket", 
          ::WSAGetLastError());
      }
      return this->fd;
    }
  }


public:
  /**
   *
   */
  int getOption(int optname, char* optval, int* optlen) 
  {
    SOCKET soc = getSocket();
    return ::getsockopt(soc, SOL_SOCKET, optname, optval, optlen);
  }

public:
  /**
   *
   */
  //IPv4
  int getName(InetAddress& address) 
  {
    sockaddr_in* addr = address.getAddress();
    return getName(addr);
  }

public:
  /**
   *
   */
  //IPv4
  int getName(sockaddr_in* addr) 
  {
    SOCKET soc = getSocket();
    int addrlen = sizeof(sockaddr_in);
    return ::getsockname(soc, (sockaddr*)addr, &addrlen);
  }

public:
  /**
   *
   */
  int setOption(int optname, char* optval, int optlen) 
  {
    SOCKET soc = getSocket();
    return::setsockopt(soc, SOL_SOCKET, optname, optval, optlen);
  }

public:
  /**
   *
   */
  int shutdown(int how) 
  {
    SOCKET soc = getSocket();
    return ::shutdown(soc, how);
  }

public:
  /**
   *
   */
  int    getDomain() { return domain; }

public:
  /**
   *
   */
  void  setSocket(SOCKET soc) {
    this->fd = soc;
  }

public:
  /**
   * Return socket descriptor fd, but throw an Exception if it's INVALID_SOCKET
   */
  SOCKET  getSocket() { 
    if(this->fd == INVALID_SOCKET) {
      throw InvalidSocketException("Socket::getSocket,1,InvalidSocket", 0);
    }
    return this->fd; 
  }

public:
  /**
   *
   */
  int    getType() { 
    return type; 
  }

public:
  /**
   *
   */
    int     ioctl(long cmd, u_long* argp) {
            return ioctlsocket(this->fd, cmd, argp);
    }

public:
  /**
   *
   */
    int     nonBlocking() {
            u_long block = 1;
            return ioctlsocket(this->fd, FIONBIO, &block);                
    }

};

}


