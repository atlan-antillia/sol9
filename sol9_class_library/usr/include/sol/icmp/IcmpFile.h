/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IcmpFile.h
 *
 *****************************************************************************/

// SOL9
// 2010/10/31

#pragma once
#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/icmp/IcmpEchoReply.h>

/*
typedef struct {
    unsigned char Ttl;                         // Time To Live
    unsigned char Tos;                         // Type Of Service
    unsigned char Flags;                       // IP header flags
    unsigned char OptionsSize;                 // Size in bytes of options data
    unsigned char *OptionsData;                // Pointer to options data
} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;
*/

namespace SOL {

class IcmpFile :public Object {
private:
  HANDLE hIcmp;

public:
  IcmpFile()
  :hIcmp(NULL)
  {
    this->hIcmp = IcmpCreateFile();
    
    if (hIcmp == INVALID_HANDLE_VALUE) {
      throw Exception("Invalid handle.");
    }
  }

public:
  ~IcmpFile()
  {
    if (hIcmp) {
      IcmpCloseHandle(hIcmp);
      hIcmp = NULL;
    }
  }

public:

  DWORD sendEcho(__in const char* destinationAddress, //IPAddress or HostName String 
      __in const char* requestData,
      __out IcmpEchoReply& echoReply,
      __in_opt PIP_OPTION_INFORMATION requestOptions=NULL,
      __in_opt DWORD timeout=1000)
  {
    if (destinationAddress == NULL || requestData==NULL) {
      throw Exception("Invalid parameter");
    }
    addrinfo *destAddrInfo = NULL;

    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_INET;
    int ai_err = getaddrinfo(destinationAddress, 0, &hints, &destAddrInfo);
    if (ai_err) {
      throw Exception(gai_strerror(ai_err));      
    }

    in_addr inaddr = ((sockaddr_in *)destAddrInfo->ai_addr)->sin_addr;
    IPAddr ipaddr;
    memcpy(&ipaddr, &inaddr, sizeof(ipaddr));

    DWORD replySize = 0;
    WORD requestSize = (WORD)strlen(requestData) + 1;
    void* replyBuffer = echoReply.alloc(requestSize, replySize);

    DWORD rc = IcmpSendEcho(hIcmp, ipaddr, 
        (void*)requestData, 
        requestSize, 
        requestOptions, 
        replyBuffer, 
        replySize, 
        timeout);

    freeaddrinfo(destAddrInfo);
    if (rc == 0) {
      throw GetLastError();
    }

    return rc;
  }

public:

  DWORD sendEcho2(
    __in const char* destinationAddress, //IPAddress or HostName String 
    __in const char* requestData,
    __in PIP_OPTION_INFORMATION requestOptions,
    __out IcmpEchoReply& echoReply,
    __in_opt   HANDLE event=NULL,
    //FARPROC is for Windows Server 2003 and XP. PIO_APC_ROUTINE is for Vista and later version 
#ifdef PIO_APC_ROUTINE_DEFINED
    __in_opt PIO_APC_ROUTINE apcRoutine=NULL,
#else
    __in_opt FARPROC apcRoutine=NULL,
#endif
    __in_opt   void* apcContext=NULL,
    __in_opt   DWORD timeout=1000)
  {
    if (destinationAddress == NULL || requestData==NULL) {
      throw Exception("Invalid parameter");
    }

    addrinfo *destAddrInfo = NULL;

    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_INET;
    int ai_err = getaddrinfo(destinationAddress, 0, &hints, &destAddrInfo);
    if (ai_err) {
      throw Exception(gai_strerror(ai_err));      
    }

    in_addr inaddr = ((sockaddr_in *)destAddrInfo->ai_addr)->sin_addr;
    IPAddr ipaddr;
    memcpy(&ipaddr, &inaddr, sizeof(ipaddr));

    DWORD replySize = 0;
    WORD requestSize = (WORD)strlen(requestData) + 1;

    void* replyBuffer = echoReply.alloc(requestSize, replySize);

    DWORD rc = IcmpSendEcho2(
      hIcmp,
      event,
      apcRoutine,
      apcContext,
      ipaddr,
      (void*)requestData,
      requestSize,
      requestOptions,
      replyBuffer,
      replySize,
      timeout);

    freeaddrinfo(destAddrInfo);

    if (event !=NULL && apcRoutine !=NULL && apcContext !=NULL) {
      //async
      if (rc !=ERROR_IO_PENDING ) {
        throw GetLastError();
      }
    } else {
      //sync
      if (rc == 0) {
        throw GetLastError();
      }
    }

    return rc;
  }
};

}
