/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ProtocolInformation.h
 *
 *****************************************************************************/


// SOL9 2.0

// 2010/12/13
#pragma once
  
#include <sol/Object.h>
#include <sol/ArgT.h>
#include <sol/StringT.h>
#include <sol/StringBufferT.h>

#include <sol/Exception.h>
#include <sol/Guid.h>
#include <sol/net/SocketDefinition.h>

#pragma comment(lib, "ws2_32.lib")    

namespace SOL {

/*
typedef struct _WSAPROTOCOL_INFO {
  DWORD dwServiceFlags1;
  DWORD dwServiceFlags2;  //Reserved
  DWORD dwServiceFlags3;  //Reserved
  DWORD dwServiceFlags4;  //Reserved
  DWORD dwProviderFlags;
  GUID ProviderId;
  DWORD dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int iVersion;
  int iAddressFamily;
  int iMaxSockAddr;
  int iMinSockAddr;
  int iSocketType;
  int iProtocol;
  int iProtocolMaxOffset;
  int iNetworkByteOrder;
  int iSecurityScheme;
  DWORD dwMessageSize;
  DWORD dwProviderReserved;
  TCHAR szProtocol[WSAPROTOCOL_LEN+1];
} WSAPROTOCOL_INFO, *LPWSAPROTOCOL_INFO;
*/


class ProtocolInformation :public Object {

private:
    WSAPROTOCOL_INFO* pInfos;
  int count;
  
public:
  ProtocolInformation()
  :pInfos(NULL),
  count(0)
  {
  }

public:
  ~ProtocolInformation()
  {
    clear();
  }  


public:
  const WSAPROTOCOL_INFO* getInfos()
  {
    return this->pInfos;
  }

public:
  int getCount()
  {
    return this->count;
  }


public:
  void clear()
  {
    if (pInfos) {
      delete [] (char*)pInfos;
      pInfos = NULL;
      count = 0;
    }
  }

public:
  int enumerate()
  {
    clear();

    DWORD dwLen = 0;

    WSAEnumProtocols(NULL, NULL, &dwLen);   
   
        this->pInfos = (WSAPROTOCOL_INFO*)new char[dwLen];   
        
    this->count  = WSAEnumProtocols(NULL, pInfos, &dwLen);
    if (this->count == SOCKET_ERROR) {
      throw Exception("ProtocolInformation::enumerate error.", WSAGetLastError());
    }
    return this->count;
  }
   
public:
  void display(const WSAPROTOCOL_INFO& info)
  {
    StringT<TCHAR> flags1;
    StringT<TCHAR> providerFlags;
    StringT<TCHAR> id;
    Guid guid;
    SocketDefinition sockDef;

    _tprintf(_T("Protocol = %s\n"),  info.szProtocol);
    _tprintf(_T("ServiceFlags1 = %s\n"), getServiceFlags1(info.dwServiceFlags1, flags1));
    _tprintf(_T("ServiceFlags2 = %d\n"), info.dwServiceFlags2);
    _tprintf(_T("ServiceFlags3 = %d\n"), info.dwServiceFlags3);
    _tprintf(_T("ServiceFlags4 = %d\n"), info.dwServiceFlags4);
    _tprintf(_T("ProviderFlags = %s\n"), getProviderFlags(info.dwProviderFlags, providerFlags));
    _tprintf(_T("ProviderId = %s\n"),   guid.toString(info.ProviderId, id));

    _tprintf(_T("CatalogEntryId = %d\n"),  info.dwCatalogEntryId);
    _tprintf(_T("iVersion = %d\n"),   info.iVersion);
    _tprintf(_T("iAddressFamily = %s\n"), sockDef.getFamily(info.iAddressFamily));
    _tprintf(_T("iMaxSockAddr = %d\n"),   info.iMaxSockAddr);
    _tprintf(_T("iMinSockAddr = %d\n"),    info.iMinSockAddr);
    _tprintf(_T("iSocketType = %s\n"),    sockDef.getSocketType(info.iSocketType));
    _tprintf(_T("iProtocol = %s\n"),     sockDef.getProtocol(info.iProtocol));
    _tprintf(_T("iProtocolMaxOffset = %d\n"), info.iProtocolMaxOffset);
    _tprintf(_T("iNetworkByteOrder = %s\n"), getNetworkByteOrder(info.iNetworkByteOrder));
    _tprintf(_T("iSecurityScheme = %d\n"),    info.iSecurityScheme);
    _tprintf(_T("MessageSize = %d\n"), info.dwMessageSize);
    _tprintf(_T("ProtocolChain.ChainLen = %d "), info.ProtocolChain.ChainLen);
    if (info.ProtocolChain.ChainLen == 1) { 
      _tprintf(_T("(Base Service Provider)\n"));
    
    } else if (info.ProtocolChain.ChainLen > 1){
           _tprintf(_T("ProtocolChain layered to base protocol\n"));
       for (int j=0; j<info.ProtocolChain.ChainLen; j++) {
               _tprintf(_T("\tChain Catalog Entry Id = %u\n"),
                     info.ProtocolChain.ChainEntries[j]);
       }
    } else if (info.ProtocolChain.ChainLen==0) {
           _tprintf(_T("Layered Service Provider\n"));
    }
  }

public:
  virtual void display()
  {
    if (this->pInfos) {
      for (int i = 0; i < this->count; i++ ) {   
        const WSAPROTOCOL_INFO& info  = *(pInfos + i); 
        display(info);
        _tprintf(_T("\n"));
      }
    }
  }   

public:
  const TCHAR* getServiceFlags1(DWORD flags, StringT<TCHAR>& string)
  {
    static const ArgT<TCHAR> names[] = {
    {_T("XP1_CONNECTIONLESS"),     XP1_CONNECTIONLESS},
    {_T("XP1_GUARANTEED_DELIVERY"),   XP1_GUARANTEED_DELIVERY},
    {_T("XP1_GUARANTEED_ORDER"),   XP1_GUARANTEED_ORDER},
    {_T("XP1_MESSAGE_ORIENTED"),   XP1_MESSAGE_ORIENTED},
    {_T("XP1_PSEUDO_STREAM"),     XP1_PSEUDO_STREAM},
    {_T("XP1_GRACEFUL_CLOSE"),     XP1_GRACEFUL_CLOSE},
    {_T("XP1_EXPEDITED_DATA"),     XP1_EXPEDITED_DATA},
    {_T("XP1_CONNECT_DATA"),     XP1_CONNECT_DATA},
    {_T("XP1_DISCONNECT_DATA"),   XP1_DISCONNECT_DATA},
    {_T("XP1_SUPPORT_BROADCAST"),   XP1_SUPPORT_BROADCAST},
    {_T("XP1_SUPPORT_MULTIPOINT"),   XP1_SUPPORT_MULTIPOINT},
    {_T("XP1_MULTIPOINT_CONTROL_PLANE"),XP1_MULTIPOINT_CONTROL_PLANE},
    {_T("XP1_MULTIPOINT_DATA_PLANE"),   XP1_MULTIPOINT_DATA_PLANE},
    {_T("XP1_QOS_SUPPORTED"),     XP1_QOS_SUPPORTED},
    {_T("XP1_INTERRUPT"),       XP1_INTERRUPT},
    {_T("XP1_UNI_SEND"),       XP1_UNI_SEND},
    {_T("XP1_UNI_RECV"),       XP1_UNI_RECV},
    {_T("XP1_IFS_HANDLES"),     XP1_IFS_HANDLES},
    {_T("XP1_PARTIAL_MESSAGE"),   XP1_PARTIAL_MESSAGE},
    };

    StringBufferT<TCHAR> buffer;
    int c = 0;

    for (int i = 0; i<CountOf(names); i++) {
      if (flags & names[i].value) {
        if (c > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        c++;
      }
    }
    string = buffer.getBuffer();

    return (const TCHAR*)string;
  }

public:
  const TCHAR* getProviderFlags(DWORD flags, StringT<TCHAR>& string)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("PFL_MULTIPLE_PROTO_ENTRIES"), PFL_MULTIPLE_PROTO_ENTRIES}, 
      {_T("PFL_RECOMMENDED_PROTO_ENTRY"), PFL_RECOMMENDED_PROTO_ENTRY}, 
      {_T("PFL_HIDDEN"), PFL_HIDDEN}, 
      {_T("PFL_MATCHES_PROTOCOL_ZERO"), PFL_MATCHES_PROTOCOL_ZERO}, 
    };

    StringBufferT<TCHAR> buffer;
    int c = 0;

    for (int i = 0; i<CountOf(names); i++) {
      if (flags & names[i].value) {
        if (c > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        c++;
      }
    }
    if (c == 0) {
      buffer.append(_T("0"));
    }
    string = buffer.getBuffer();

    return (const TCHAR*)string;

  }

public:
  const TCHAR* getNetworkByteOrder(__in int order)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("LittleEndian"), LITTLEENDIAN},
      {_T("BigEndian"), BIGENDIAN},
    };

    const TCHAR* name = _T("");
    for (int i =0; i< CountOf(names); i++) {
      if ((int)names[i].value == order){
        name = names[i].name;
        break;
      }
    }
    return name;
  }
};

}
