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
 *  SocketDefinitionn.h
 *
 *****************************************************************************/


// SOL9 2.0

// 2010/12/15
#pragma once
  
#include <sol/Object.h>
#include <sol/ArgT.h>
#include <sol/StringT.h>
#include <sol/StringBufferT.h>

namespace SOL {

class SocketDefinition :public Object {

public:
  SocketDefinition()
  {
  }

public:
  const TCHAR* getFamily(__in int family)
  {
    static const ArgT<TCHAR> families[] = {

    {_T("AF_UNSPEC"),  AF_UNSPEC},    // unspecified
    {_T("AF_UNIX"),    AF_UNIX},    // local to host (pipes, portals)
    {_T("AF_INET"),    AF_INET},    // internetwork: UDP, TCP, etc.
    {_T("AF_IMPLINK"),  AF_IMPLINK},  // arpanet imp addresses
    {_T("AF_PUP"),    AF_PUP},    // pup protocols: e.g. BSP
    {_T("AF_CHAOS"),  AF_CHAOS},    // mit CHAOS protocols
    {_T("AF_NS"),    AF_NS},      // XEROX NS protocols
    {_T("AF_IPX"),    AF_IPX},    // IPX protocols: IPX, SPX, etc.
    {_T("AF_ISO"),    AF_ISO},    // ISO protocols
    {_T("AF_OSIK"),    AF_OSI},    // OSI is ISO  
    {_T("AF_ECMA"),    AF_ECMA},    // european computer manufacturers
    {_T("AF_DATAKIT"),  AF_DATAKIT},  // datakit protocols
    {_T("AF_CCITT"),  AF_CCITT},    // CCITT protocols, X.25 etc
    {_T("AF_SNA"),    AF_SNA},    // IBM SNA
    {_T("AF_DECnet"),  AF_DECnet},    // DECnet
    {_T("AF_DLI"),    AF_DLI},    // Direct data link interface
    {_T("AF_LAT"),    AF_LAT},    // LAT
    {_T("AF_HYLINK"),  AF_HYLINK},    // NSC Hyperchannel
    {_T("AF_APPLETALK"),AF_APPLETALK},  // AppleTalk
    {_T("AF_NETBIOS"),  AF_NETBIOS},  // NetBios-style addresses
    {_T("AF_VOICEVIEW"),AF_VOICEVIEW},  // VoiceView
    {_T("AF_FIREFOX"),  AF_FIREFOX},  // Protocols from Firefox
    {_T("AF_UNKNOWN1"),  AF_UNKNOWN1},  // Somebody is using this!
    {_T("AF_BAN"),    AF_BAN},    // Banyan
    {_T("AF_ATM"),    AF_ATM},    //  Native ATM Services
    {_T("AF_INET6"),  AF_INET6},    // Internetwork Version 6
    {_T("AF_CLUSTER"),  AF_CLUSTER},  // Microsoft Wolfpack
    {_T("AF_12844"),  AF_12844},    // IEEE 1284.4 WG AF
    {_T("AF_IRDA"),    AF_IRDA},    // IrDA
    {_T("AF_NETDES"),  AF_NETDES},    // Network Designers OSI & gateway
    };
    const TCHAR* name = _T("Other");
    for (int i =0; i< CountOf(families); i++) {
      if ((int)families[i].value == family){
        name = families[i].name;
        break;
      }
    }
    return name;
  }

public:
  const TCHAR* getSocketType(__in int type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("Unspecified"),        0},
      {_T("SOCK_STREAM (Stream)"),  SOCK_STREAM},
      {_T("SOCK_DGRAM (Datagram)"),  SOCK_DGRAM},
      {_T("SOCK_RAW (Raw)"),      SOCK_RAW},
      {_T("SOCK_RDM (Reliable Message Datagram)"), SOCK_RDM},
      {_T("SOCK_SEQPACKET (Pseudo-Stream Packet)"), SOCK_SEQPACKET},
    };

     const TCHAR* name = _T("Other");
    for (int i =0; i< CountOf(names); i++) {
      if ((int)names[i].value == type){
        name = names[i].name;
        break;
      }
    }
    return name;
  }

public:
  const TCHAR* getProtocol(__in int protocol)
  {
    static const ArgT<TCHAR> names[] = {
    {_T("IPPROTO_HOPOPTS"), IPPROTO_HOPOPTS},  //= 0,  // IPv6 Hop-by-Hop options
    {_T("IPPROTO_ICMP"),  IPPROTO_ICMP},    //= 1,
    {_T("IPPROTO_IGMP"),  IPPROTO_IGMP},    //= 2,
    {_T("IPPROTO_GGP"),    IPPROTO_GGP},    //= 3,
    {_T("IPPROTO_IPV4"),  IPPROTO_IPV4},    //= 4,
    {_T("IPPROTO_ST"),    IPPROTO_ST},    //= 5,
    {_T("IPPROTO_TCP"),    IPPROTO_TCP},    //= 6,
    {_T("IPPROTO_CBT"),    IPPROTO_CBT},    //= 7,
    {_T("IPPROTO_EGP"),    IPPROTO_EGP},    //= 8,
    {_T("IPPROTO_IGP"),    IPPROTO_IGP},    //= 9,
    {_T("IPPROTO_PUP"),    IPPROTO_PUP},    //= 12,
    {_T("IPPROTO_UDP"),    IPPROTO_UDP},    //= 17,
    {_T("IPPROTO_IDP"),    IPPROTO_IDP},    //= 22,

    {_T("IPPROTO_RDP"),    IPPROTO_RDP},    //= 27,
    {_T("IPPROTO_IPV6"),  IPPROTO_IPV6},    //= 41, // IPv6 header
    {_T("PPROTO_ROUTING"),  IPPROTO_ROUTING},  //= 43, // IPv6 Routing header
    {_T("IPPROTO_FRAGMENT"),IPPROTO_FRAGMENT},  //= 44, // IPv6 fragmentation header
    {_T("IPPROTO_ESP"),    IPPROTO_ESP},    //= 50, // encapsulating security payload
    {_T("IPPROTO_AH"),    IPPROTO_AH},    //= 51, // authentication header
    {_T("IPPROTO_ICMPV6"),  IPPROTO_ICMPV6},  //= 58, // ICMPv6
    {_T("IPPROTO_NONE"),  IPPROTO_NONE},    //= 59, // IPv6 no next header
    {_T("IPPROTO_DSTOPTS"),  IPPROTO_DSTOPTS},  // = 60, // IPv6 Destination options

    {_T("IPPROTO_ND"),    IPPROTO_ND},    //= 77,
    {_T("IPPROTO_ICLFXBM"),  IPPROTO_ICLFXBM},  //= 78,
    {_T("IPPROTO_PIM"),    IPPROTO_PIM},    //= 103,
    {_T("IPPROTO_PGM"),    IPPROTO_PGM},    //= 113,
    {_T("IPPROTO_L2TP"),  IPPROTO_L2TP},    //= 115,
    {_T("IPPROTO_SCTP"),  IPPROTO_SCTP},    //= 132,
    {_T("IPPROTO_RAW"),    IPPROTO_RAW},    //= 255,

    {_T("IPPROTO_MAX"),    IPPROTO_MAX}    //= 256
    };


    const TCHAR* name = _T("Other");
    for (int i =0; i<CountOf(names); i++) {
      if ((int)names[i].value == protocol){
        name = names[i].name;
        break;
      }
    }
    return name;
  }

};

}
