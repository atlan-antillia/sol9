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
 *  DnsData.h
 *
 *****************************************************************************/

// SOL9
// 2011/1/3
// 2011/1/20 Added setValues methods to set parameters to each DNS_*_DATA object.
//    Note that pointer parameters are set to correspoingding fields to the DNS_*_DATA
//    structures, copied to the fields without duplicating the pointer parameters.

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/ArgListT.h>

#include <sol/net/IPv4Address.h>
#include <sol/net/IPv4String.h>
#include <sol/net/IPv6String.h>
#include <sol/net/IPv6Address.h>

namespace SOL {

class DnsData :public DnsObject {
// Having no data members.

public:
  /**
   * Constructor
   */
  DnsData()
  {
  }


public:
  /**
   * Destructor
   */
  ~DnsData()
  {
  }

// Instance methods to handle the first DNS_*_DATA object 
//
/*
typedef struct{
    IP4_ADDRESS     IpAddress;
}DNS_A_DATA, *PDNS_A_DATA;
*/
  // A = IPv4
public:
  void setValues(DNS_A_DATA& data, const TCHAR* ipString)
  {
    in_addr addr;
    IPv4String ipv4string;
    TCHAR* terminator= NULL;

    if (ipv4string.toAddress(ipString, TRUE, &terminator, &addr)) {
      data.IpAddress = addr.S_un.S_addr;
    }
  }

public:
  void display(DNS_A_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    StringT<TCHAR> string;
    IPv4Address ipv4Address;
    ipv4Address.toString(data.IpAddress, string);
    _tprintf(_T("IP4_ADDRESS=%s\n"), (const TCHAR*)string);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameHost;
}DNS_PTR_DATAW, *PDNS_PTR_DATAW;
*/
  // PTR = Pointer Data
public:
  void setValues(DNS_PTR_DATA& data, TCHAR* nameHost)
  {
    data.pNameHost = nameHost;
  }

public:
  void display(DNS_PTR_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    _tprintf(_T("NameHost=%s\n"), data.pNameHost);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    IP4_ADDRESS     IpAddress;
    UCHAR           chProtocol;
    BYTE            BitMask[1];
}DNS_WKS_DATA, *PDNS_WKS_DATA;
*/
  //WKS = Well Known Service
public:
  void setValues(DNS_WKS_DATA& data, const TCHAR* ipString, 
    UCHAR chProtocol, 
    BYTE* bmask, 
    WORD maskCount)
  {
    in_addr addr;
    IPv4String ipv4string;
    TCHAR* terminator=NULL;
    if (ipv4string.toAddress(ipString, TRUE, &terminator, &addr)) {
      data.IpAddress = addr.S_un.S_addr;
    }
    data.chProtocol = chProtocol;
    for (int i = 0; i<maskCount; i++) {
      data.BitMask[i] = bmask[i];
    }
  }


public:
  void display(DNS_WKS_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    static const ArgT<TCHAR> names[] = {
      {_T("TCP"), 6},
      {_T("UDP"), 17},
    };
    ArgListT<TCHAR> protocolNames(names, CountOf(names));

    StringT<TCHAR> string;
    IPv4Address ipv4Address;
    ipv4Address.toString(data.IpAddress, string);
    _tprintf(_T("IP4_ADDRESS=%s\n"), (const TCHAR*)string);
    _tprintf(_T("Protocol=%d (%s)\n"), data.chProtocol, protocolNames.getName(data.chProtocol));
    _tprintf(_T("BitMask=%d\n"), data.BitMask);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    BYTE            AddressType;
    BYTE            Address[ DNS_ATMA_MAX_ADDR_LENGTH ];
} DNS_ATMA_DATA, *PDNS_ATMA_DATA;
*/
public:
  void setValues(DNS_ATMA_DATA& data,
    BYTE addressType,
    int addressLength,
    BYTE* address)
  {
    data.AddressType = addressType;
    int length = DNS_ATMA_MAX_ADDR_LENGTH;
    if (addressLength>0 && addressLength<DNS_ATMA_MAX_ADDR_LENGTH) {
      length = addressLength;
    }
    for(int i=0; i<length; i++) {
      data.Address[i] = address[i];
    }
  }

public:
  void display(DNS_ATMA_DATA& data, const TCHAR* label)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    static const ArgT<TCHAR> names[] = {
      {_T("AESA"), DNS_ATMA_FORMAT_AESA},
      {_T("E164"), DNS_ATMA_FORMAT_E164},
    };
    ArgListT<TCHAR> addrTypeNames(names, CountOf(names));
    _tprintf(_T("AddressType=%d (%s)\n"), data.AddressType, addrTypeNames.getName(data.AddressType));

    for(int i=0; i<DNS_ATMA_MAX_ADDR_LENGTH; i++) {
      _tprintf(_T("%02x "), data.Address[i]);
    }
    if (label) _tprintf(_T("</%s>\n"), label);
  }

public:
/*
DNS
typedef struct {
  DWORD IP6Dword[4];
} IP6_ADDRESS, *PIP6_ADDRESS;

typedef struct in6_addr {
  union {
    u_char  Byte[16];
    u_short Word[8];
  } u;
} IN6_ADDR, *PIN6_ADDR, FAR *LPIN6_ADDR;
*/
/*
typedef struct{
    IP6_ADDRESS     Ip6Address;
}DNS_AAAA_DATA, *PDNS_AAAA_DATA;
*/
  // AAAA= IPv6
public:
  void setValues(DNS_AAAA_DATA& data, const TCHAR* ip6String)
  {
    in6_addr addr;
    IPv6String ipv6string;
    TCHAR* terminator=NULL;
    if (ipv6string.toAddress(ip6String, &terminator, &addr)) {
      memcpy(&(data.Ip6Address), &addr, sizeof(addr));
    }
  }

public:
  void display(DNS_AAAA_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
  
    //IPv6
    IN6_ADDR addr;
    memcpy(&addr, &(data.Ip6Address), sizeof(addr));
    StringT<TCHAR> string;
    IPv6Address ipv6Address;
    ipv6Address.toString(addr, string);
    _tprintf(_T("IP6_ADDRESS=%s\n"), (const TCHAR*)string);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameExchange;
    WORD            wPreference;
    WORD            Pad;        // keep ptrs DWORD aligned
}DNS_MX_DATAW, *PDNS_MX_DATAW;
*/
  // Mail Exchange
public:
  void setValues(DNS_MX_DATA& data, TCHAR* nameExchange, WORD preference)
  {
    data.pNameExchange = nameExchange;
    data.wPreference = preference;
  }

public:
  void display(DNS_MX_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NameExchange=%s\n"), data.pNameExchange);
    _tprintf(_T("Preference=%d\n"), data.wPreference);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNamePrimaryServer;
    PWSTR           pNameAdministrator;
    DWORD           dwSerialNo;
    DWORD           dwRefresh;
    DWORD           dwRetry;
    DWORD           dwExpire;
    DWORD           dwDefaultTtl;
}DNS_SOA_DATAW, *PDNS_SOA_DATAW;
*/
  // SOA = Start Of Authority
public:
  void setValues(DNS_SOA_DATA& data, 
    TCHAR* namePrimaryServer,
    TCHAR* nameAdministrator,
    DWORD serialNo,
    DWORD refresh,
    DWORD retry,
    DWORD expire,
    DWORD defaultTtl)
  {
    data.pNamePrimaryServer = namePrimaryServer;
    data.pNameAdministrator = nameAdministrator;
    data.dwSerialNo = serialNo;
    data.dwRefresh = refresh;
    data.dwRetry = retry;
    data.dwExpire = expire;
    data.dwDefaultTtl= defaultTtl;
  }

public:
  void display(DNS_SOA_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NamePrimaryServer=%s\n"), data.pNamePrimaryServer);
    _tprintf(_T("NameAdministrator=%s\n"), data.pNameAdministrator);
    _tprintf(_T("SerialNo=%d\n"), data.dwSerialNo);
    _tprintf(_T("Refresh=%d\n"), data.dwRefresh);
    _tprintf(_T("Retry=%d\n"), data.dwRetry);
    _tprintf(_T("Expire=%d\n"), data.dwExpire);
    _tprintf(_T("DefaultTtl=%d\n"), data.dwDefaultTtl);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameMailbox;
    PWSTR           pNameErrorsMailbox;
}DNS_MINFO_DATAW, *PDNS_MINFO_DATAW;
*/
  // MINFO = Mail Information
public:
  void setValues(DNS_MINFO_DATA& data,
    TCHAR* nameMailbox,
    TCHAR* nameErrorsMailbox) 
  {
    data.pNameMailbox = nameMailbox;
    data.pNameErrorsMailbox = nameErrorsMailbox; 
  }

public:
  void display(DNS_MINFO_DATA& data, const TCHAR* label=NULL)
  {
    //Mail Info
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NameMailbox=%s\n"), data.pNameMailbox);
    _tprintf(_T("NameErrorsMailbox=%s\n"), data.pNameErrorsMailbox);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    DWORD           dwByteCount;
#ifdef MIDL_PASS
    [size_is(dwByteCount)] BYTE Data[];
#else
    BYTE            Data[1];
#endif
}DNS_NULL_DATA, *PDNS_NULL_DATA;
*/
  // NULL = NULL Data
public:
  void setValues(DNS_NULL_DATA& data, const BYTE* bytes, int byteCount)
  {

    data.dwByteCount = byteCount;

    for(int i=0; i<byteCount; i++) {
      data.Data[i] = bytes[i];
    }
  }

public:
  void display(DNS_NULL_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    for(DWORD i=0; i<data.dwByteCount; i++) {
      _tprintf(_T("%02x "), data.Data[i]);
    }
    _tprintf(_T("\n"));
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    DWORD           dwStringCount;
#ifdef MIDL_PASS
    [size_is(dwStringCount)] PWSTR pStringArray[];
#else
    PWSTR           pStringArray[1];
#endif
}DNS_TXT_DATAW, *PDNS_TXT_DATAW;
*/
  //TXT = Text Data
public:
  void setValues(DNS_TXT_DATA& data, TCHAR** strings, 
      int stringCount)
  {
    data.dwStringCount = stringCount;

    //Text Data
    for (int i = 0; i<stringCount; i++) {
      data.pStringArray[i] = strings[i];
    }
  }

public:
  void display(DNS_TXT_DATA& data, TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    //Text Data
    //printf("count =%d\n", data.dwStringCount);
    for (DWORD i = 0; i<data.dwStringCount; i++) {
      // 2011/09/05 Added the following NULL check, it's probably needless.
      if (data.pStringArray[i] !=NULL) {
        _tprintf(_T("String[%d]=%s\n"), i, data.pStringArray[i]);
      }
    }
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    WORD            wFlags;
    BYTE            chProtocol;
    BYTE            chAlgorithm;
    BYTE            Key[1];
}DNS_KEY_DATA, *PDNS_KEY_DATA;
*/
  // KEY = Key; DNS security
public:
  void setValues(DNS_KEY_DATA& data,
    WORD flags,
    BYTE protocol,
    BYTE algorithm,
    int keyLength,
    BYTE* key)
  {
    data.wFlags = flags;
    data.chProtocol = protocol;
    data.chAlgorithm = algorithm;
    for (int i = 0; i<keyLength; i++) {
      data.Key[i] = key[i];
    }
  }

public:
  void display(DNS_KEY_DATA& data, const TCHAR* label=NULL)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("NONE"), 0},
      {_T("TLS"), 1},

      {_T("EMAIL"), 2},
      {_T("DNSSEC"), 3},
      {_T("IPSEC"), 4},
      {_T("ALL"), 255},
    };
    ArgListT<TCHAR> protocolNames(names, CountOf(names));

    static const ArgT<TCHAR> anames[] = {
      {_T("RSAMD5"), 1},
      {_T("DH"), 2},
      {_T("DSA"), 3},
      {_T("ECC"), 4},
      {_T("DIRECT"), 252},
      {_T("PRIVATEDNS"), 253},
      {_T("PRIVATEOID"), 254},
    };
    ArgListT<TCHAR> algNames(anames, CountOf(anames));

    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("Flags=%d\n"), data.wFlags);
    _tprintf(_T("Protocol=%d (%s)\n"), data.chProtocol, protocolNames.getName(data.chProtocol));
    _tprintf(_T("Algorithm=%d (%s)\n"), data.chAlgorithm, algNames.getName(data.chAlgorithm));
    //the public key for the algorithm in chAlgorithm, represented in base 64, as described in Appendix A of RFC 2535.
    _tprintf(_T("Key=%s\n"), data.Key);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PSTR            pNameSigner;
    WORD            wTypeCovered;
    BYTE            chAlgorithm;
    BYTE            chLabelCount;
    DWORD           dwOriginalTtl;
    DWORD           dwExpiration;
    DWORD           dwTimeSigned;
    WORD            wKeyTag;
    WORD            Pad;            // keep byte field aligned
    BYTE            Signature[1];
}DNS_SIG_DATAA, *PDNS_SIG_DATAA;
*/
  // SIG = Signature; DNS security
public:
  void setValues(DNS_SIG_DATA& data,
    TCHAR* nameSigner,
    WORD typeConvered,
    BYTE algorithm,
    BYTE labelCount,
    DWORD originalTtl,
    DWORD expiration,
    DWORD timeSigned,
    WORD keyTag,
    //WORD pad, Unused
    int sigLength,
    BYTE* signature)
  {

    data.pNameSigner = nameSigner;
    data.wTypeCovered = typeConvered;
    data.chAlgorithm = algorithm;

    data.chLabelCount = labelCount;
    data.dwOriginalTtl = originalTtl;
    data.dwExpiration = expiration;
    data.dwTimeSigned = timeSigned;
    data.wKeyTag = keyTag;
    //data.Pad = pad;

    for (int i = 0; i<sigLength; i++) {
      data.Signature[i] = signature[i];
    }
  }

public:
  void display(DNS_SIG_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);
    static const ArgT<TCHAR> anames[] = {
      {_T("RSAMD5"), 1},
      {_T("DH"), 2},
      {_T("DSA"), 3},
      {_T("ECC"), 4},
      {_T("DIRECT"), 252},
      {_T("PRIVATEDNS"), 253},
      {_T("PRIVATEOID"), 254},
    };
    ArgListT<TCHAR> algNames(anames, CountOf(anames));
    //Signature Data
    _tprintf(_T("NameSigner=%s\n"), data.pNameSigner);
    _tprintf(_T("TypeCovered=%d\n"), data.wTypeCovered);
    _tprintf(_T("Algorithm=%d (%s)\n"), data.chAlgorithm, algNames.getName(data.chAlgorithm));

    _tprintf(_T("LabelCount=%d\n"), data.chLabelCount);
    _tprintf(_T("OriginalTtl=%d\n"), data.dwOriginalTtl);
    _tprintf(_T("Expiration=%d\n"), data.dwExpiration);
    _tprintf(_T("TimeSigned=%d\n"), data.dwTimeSigned);
    _tprintf(_T("KeyTag=%d\n"), data.wKeyTag);
    // 2011/09/05 _tprintf(_T("Pad=%d\n"), data.Pad);
    //Signature, represented in base 64, formatted as defined in RFC 2535, Appendix A.
    _tprintf(_T("Signature=%s\n"), data.Signature);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameNext;
    WORD            wNumTypes;
    WORD            wTypes[1];
}DNS_NXT_DATAW, *PDNS_NXT_DATAW;
*/
  // NXT = Secure negative response
public:
  void setValues(DNS_NXT_DATA& data,
    TCHAR* nameNext, 
    WORD numTypes, 
    WORD* types) 
  {
    data.pNameNext = nameNext;
    data.wNumTypes = numTypes; 
  
    for (int i = 0; i<numTypes; i++) {
      data.wTypes[i] = types[i];
    }
  }

public:
  void display(DNS_NXT_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NameNext=%s\n"), data.pNameNext);
    _tprintf(_T("NumTypes=%d\n"), data.wNumTypes);
    _tprintf(_T("NumTypes:"));

    for (int i = 0; i<data.wNumTypes; i++) {
      _tprintf(_T("%d %02x "), i, data.wTypes[i]);
    }
    _tprintf(_T("\n"));

    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameTarget;
    WORD            wPriority;
    WORD            wWeight;
    WORD            wPort;
    WORD            Pad;            // keep ptrs DWORD aligned
}DNS_SRV_DATAW, *PDNS_SRV_DATAW;
*/
  // SRV Service location
public:
  void setValues(DNS_SRV_DATA& data,
    TCHAR* nameTarget, 
    WORD priority, 
    WORD weight, 
    WORD port) 
  {
    data.pNameTarget = nameTarget;
    data.wPriority = priority; 

    data.wWeight = weight; 
    data.wPort = port; 
  }

public:
  void display(DNS_SRV_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("pNameTarget=%s\n"), data.pNameTarget);
    _tprintf(_T("Priority=%d\n"), data.wPriority);
    _tprintf(_T("Weight=%d\n"), data.wWeight);
    _tprintf(_T("Port=%d\n"), data.wPort);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    WORD            wOrder;
    WORD            wPreference;
    PWSTR           pFlags;
    PWSTR           pService;
    PWSTR           pRegularExpression;
    PWSTR           pReplacement;
}DNS_NAPTR_DATAW, *PDNS_NAPTR_DATAW;
*/
  // Naming Authority Pointer
public:
  void setValues(DNS_NAPTR_DATA& data,
    WORD order,
    WORD preference,
    TCHAR* flags, 
    TCHAR* service,
    TCHAR* regularExpression,
    TCHAR* replacement)
  {
    data.wOrder = order;
    data.wPreference = preference;
    data.pFlags = flags;
    data.pService = service;
    data.pRegularExpression = regularExpression;
    data.pReplacement = replacement;
  }


public:
  void display(DNS_NAPTR_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("Order=%d\n"), data. wOrder);
    _tprintf(_T("Preference=%d\n"), data. wPreference);

    _tprintf(_T("Flags=%s\n"), data.pFlags);
    _tprintf(_T("Service=%s\n"), data.pService);

    _tprintf(_T("RegularExpression=%s\n"), data.pRegularExpression);
    _tprintf(_T("Replacement=%s\n"), data. pReplacement);
    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pKey;
    PBYTE           pOtherData;
    DWORD           dwCreateTime;
    DWORD           dwExpireTime;
    WORD            wMode;
    WORD            wError;
    WORD            wKeyLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}DNS_TKEY_DATAW, *PDNS_TKEY_DATAW;
*/
public:
  void setValues(DNS_TKEY_DATA& data,
    TCHAR* nameAlgorithm,
    BYTE* algorithmPacket,
    BYTE* key,
    //Not used BYTE* otherData,
    DWORD createTime,
    DWORD expireTime,
    WORD mode,
    WORD error,
    WORD keyLength,
    //Not used WORD otherLength,
    UCHAR algNameLength)
    //Not used BOOL packetPointers)
  {
    data.pNameAlgorithm = nameAlgorithm;
    data.pAlgorithmPacket = algorithmPacket;
    data.pKey = key;
    data.pOtherData = NULL;//otherData;
    data.dwCreateTime = createTime;
    data.dwExpireTime = expireTime;
    data.wMode = mode;
    data.wError = error;

    data.wKeyLength = keyLength;
    data.wOtherLength = 0; //otherLength;

    data.cAlgNameLength =algNameLength;
    data.bPacketPointers = FALSE;//packetPointers;
  }

public:
  void display(DNS_TKEY_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NameAlgorithm=%s\n"), data.pNameAlgorithm);
    _tprintf(_T("AlgorithmPacket:"));
    for (int i = 0; i<data.cAlgNameLength; i++) {
      _tprintf(_T("%02x "), data.pAlgorithmPacket[i]);
    }
    _tprintf(_T("\n"));

    _tprintf(_T("Key:"));
    for (int i = 0; i<data.wKeyLength; i++) {
      _tprintf(_T("%02x "), data.pKey[i]);
    }
    _tprintf(_T("\n"));

    //_tprintf(_T("OtherData=%s\n"), data.pOtherData);  //Not used 
    _tprintf(_T("CreateTime=%d\n"), data.dwCreateTime);
    _tprintf(_T("ExpireTime=%d\n"), data.dwExpireTime);
    _tprintf(_T("Mode=%d\n"), data.wMode);
    _tprintf(_T("Error=%d\n"), data.wError);

    _tprintf(_T("KeyLength=%d\n"), data.wKeyLength);
    //_tprintf(_T("OtherLength=%d\n"), data.wOtherLength);

    _tprintf(_T("AlgNameLength=%d\n"), data.cAlgNameLength);
    //_tprintf(_T("PacketPointers=%d\n"), data.bPacketPointers); //Not used

    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    PWSTR           pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pSignature;
    PBYTE           pOtherData;
    LONGLONG        i64CreateTime;
    WORD            wFudgeTime;
    WORD            wOriginalXid;
    WORD            wError;
    WORD            wSigLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}DNS_TSIG_DATAW, *PDNS_TSIG_DATAW;
*/
public:
  void setValues(DNS_TSIG_DATA& data,
    TCHAR* nameAlgorithm,
    BYTE* algorithmPacket,
    BYTE* signature,
    //Not used BYTE* otherData,
    LONGLONG createTime,
    WORD fudgeTime,
    WORD originalXid,
    WORD error,
    WORD sigLength,
    //Not used WORD otherLength,
    UCHAR algNameLength)
    //Not used BOOL packetPointers)
  {
    data.pNameAlgorithm = nameAlgorithm;
    data.pAlgorithmPacket = algorithmPacket;
    data.pSignature = signature;
    //data.pOtherData = otherData;
    data.i64CreateTime = createTime;
    data.wFudgeTime = fudgeTime;
    data.wOriginalXid = originalXid;
    data.wError = error;
    data.wSigLength = sigLength;
    //data.wOtherLength = otherLength;
    data.cAlgNameLength =algNameLength;
    //data.bPacketPointers = packetPointers;
  }

public:
  void display(DNS_TSIG_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    _tprintf(_T("NameAlgorithm=%s\n"), data.pNameAlgorithm);

    _tprintf(_T("AlgorithmPacket:")); //
    for (int i = 0; i<data.cAlgNameLength; i++) {
      _tprintf(_T("%02x "), data.pAlgorithmPacket[i]);
    }
    _tprintf(_T("\n"));

    _tprintf(_T("AlgorithmPacket=%s\n"), data.pAlgorithmPacket);

    _tprintf(_T("Signature:")); //
    for (int i = 0; i<data.wSigLength; i++) {
      _tprintf(_T("%02x "), data.pSignature[i]);
    }
    _tprintf(_T("\n"));//
    
    //_tprintf(_T("OtherData=%s\n"), data.pOtherData);
    _tprintf(_T("64CreateTime=%I64d\n"), data.i64CreateTime);

    _tprintf(_T("FudgeTime=%d\n"), data.wFudgeTime);
    _tprintf(_T("OriginalXid=%d\n"), data.wOriginalXid);
    _tprintf(_T("Error=%d\n"), data.wError);
    _tprintf(_T("SigLength=%d\n"), data.wSigLength);
    //_tprintf(_T("OtherLength=%d\n"), data.wOtherLength);
    _tprintf(_T("AlgNameLength=%d\n"), data.cAlgNameLength);

    //_tprintf(_T("PacketPointers=%d\n"), data.bPacketPointers);

    if (label) _tprintf(_T("</%s>\n"), label);
  }

/*
typedef struct{
    DWORD           dwMappingFlag;
    DWORD           dwLookupTimeout;
    DWORD           dwCacheTimeout;
    DWORD           cWinsServerCount;
    IP4_ADDRESS     WinsServers[1];
}DNS_WINS_DATA, *PDNS_WINS_DATA;
*/
public:
  void setValues(DNS_WINS_DATA& data,
    DWORD mappingFlag, 
    DWORD lookupTimeout, 
    DWORD cacheTimeout,
    DWORD winsServerCount, 
    TCHAR* ipServers[]) 
  {
    data.dwMappingFlag = mappingFlag;
    data.dwLookupTimeout = lookupTimeout;

    data.dwCacheTimeout = cacheTimeout;
    data.cWinsServerCount = winsServerCount;

    for (size_t i = 0; i < winsServerCount; i++) {
      in_addr addr;
      IPv4String ipv4string;
      TCHAR* terminator=NULL;
      if (ipv4string.toAddress(ipServers[i], TRUE, &terminator, &addr)) {
        data.WinsServers[i] = addr.S_un.S_addr;
      }
    }
  }

public:
  void display(DNS_WINS_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    static const ArgT<TCHAR> names[] = {
      {_T("SCOPE"), DNS_WINS_FLAG_SCOPE},
      {_T("LOCAL"), DNS_WINS_FLAG_LOCAL},
    };
    ArgListT<TCHAR> flagsNames(names, CountOf(names));

    _tprintf(_T("MappingFlag=%d (%s)\n"), data.dwMappingFlag, flagsNames.getName(data.dwMappingFlag));
    _tprintf(_T("LookupTimeout=%d\n"), data.dwLookupTimeout);

    _tprintf(_T("CacheTimeout=%d\n"), data.dwCacheTimeout);
    _tprintf(_T("WinsServerCount=%d\n"), data.cWinsServerCount);
    for (DWORD i = 0; i < data.cWinsServerCount; i++) {
      StringT<TCHAR> string;
      IPv4Address ipv4Address;
      ipv4Address.toString(data.WinsServers[i], string);
      _tprintf(_T("IP4_ADDRESS[%d]=%s\n"), i, (const TCHAR*)string);
    }

    if (label) _tprintf(_T("</%s>\n"), label);
  }
/*
typedef struct{
    DWORD           dwMappingFlag;
    DWORD           dwLookupTimeout;
    DWORD           dwCacheTimeout;
    PWSTR           pNameResultDomain;
}DNS_WINSR_DATAW, *PDNS_WINSR_DATAW;
*/
public:
  void setValues(DNS_WINSR_DATA& data,
    DWORD mappingFlag, 
    DWORD lookupTimeout, 
    DWORD cacheTimeout,
    TCHAR* nameResultDomain) 
  {
    data.dwMappingFlag = mappingFlag;
    data.dwLookupTimeout = lookupTimeout;
    data.dwCacheTimeout = cacheTimeout;
    data.pNameResultDomain = nameResultDomain;

  }

public:
  void display(DNS_WINSR_DATA& data, const TCHAR* label=NULL)
  {
    if (label) _tprintf(_T("<%s>\n"), label);

    static const ArgT<TCHAR> names[] = {
      {_T("SCOPE"), DNS_WINS_FLAG_SCOPE},
      {_T("LOCAL"), DNS_WINS_FLAG_LOCAL},
    };
    ArgListT<TCHAR> flagsNames(names, CountOf(names));

    _tprintf(_T("MappingFlag=%d (%s)\n"), data.dwMappingFlag, flagsNames.getName(data.dwMappingFlag));
    _tprintf(_T("LookupTimeout=%d\n"), data.dwLookupTimeout);
    _tprintf(_T("CacheTimeout=%d\n"), data.dwCacheTimeout);
    _tprintf(_T("NameResultDomain=%s\n"), data.pNameResultDomain);

    if (label) _tprintf(_T("</%s>\n"), label);
  }
};

}
