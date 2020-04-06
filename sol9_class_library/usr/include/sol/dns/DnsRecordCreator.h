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
 *  DnsRecordCreator.h
 *
 *****************************************************************************/

// SOL9
// 2010/1/16  DNS_RECORD creator in a client side. 

#pragma once
#include <sol/dns/DnsObject.h>

#include <sol/net/IPv4Address.h>
#include <sol/net/IPv4String.h>
#include <sol/net/IPv6String.h>
#include <sol/net/IPv6Address.h>

#include <sol/dns/DnsData.h>
#include <sol/dns/DnsRecord.h>


namespace SOL {
/**
 * DnsRecordCreator creates a list of  DNS_RECORDs allocated by using C++ new operator.
 * To free the list, we cannot use DnsRecordListFree API, because we are in a different world from the
 * memory space allocated by Windows DLLs.
 */

class DnsRecordCreator :public DnsRecord {
private:
  //Default Dns record flags;
  DNS_RECORD_FLAGS flags;

//private:
  //Pointer to the first element of DNS_RECORDs linked list 
  //DNS_RECORD* pRecord;

public:
  /**
   * Constructor
   */
  DnsRecordCreator()
  :DnsRecord()
  {
    memset(&flags, 0, sizeof(flags));

    flags.Section = DnsSectionAnswer;
#ifdef UNICODE
    flags.CharSet = DnsCharSetUnicode;
#else
    flags.CharSet = DnsCharSetAnsi;
#endif
  }


public:
  ~DnsRecordCreator()
  {
    clear();
  }

public:
  void clear()
  {
    DNS_RECORD* pRecord = getRecord();

    if (pRecord) {
      DNS_RECORD* ptr = pRecord;
      while (ptr) {
        DNS_RECORD* current = ptr;
        ptr = ptr ->pNext;
        //Delete each DNS_RECORD, but doesn't delete fields of the DNS_RECORD
        delete [] (BYTE*)current;
      }  
    }
  }

private:
  DNS_RECORD* alloc(const TCHAR* name, WORD type, int dataSize)
  {
    DNS_RECORD* aRecord =NULL;

    if (dataSize > 0) {
      DNS_RECORD r;
      int headerSize = sizeof(r) - sizeof(r.Data);
      
      //Record size(in bytes) for DNS_RECORD 
      int recordSize = sizeof(DNS_RECORD);
      
      int requiredSize = headerSize + dataSize;
      if (requiredSize > recordSize) {
        recordSize = requiredSize;
      }
      //printf("RecordSize=%d \n", recordSize);      
      aRecord = (DNS_RECORD*) new BYTE[recordSize];
      memset(aRecord, 0, recordSize);
      
      addRecord(aRecord);

      aRecord->pNext = NULL;
      aRecord->pName = (TCHAR*)name;//strdup(name);
      aRecord->wType = type;
      aRecord->dwTtl  = 0;
      aRecord->wDataLength = (WORD)dataSize;
      aRecord->Flags.S = this->flags;

    } else {
      throw ERROR_INVALID_PARAMETER;
    }
    return aRecord;
  }

public:
  const DNS_RECORD* create(const DNS_A_DATA& data, const TCHAR* name, WORD type,
    const TCHAR* ipString)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_A_DATA* pData = (DNS_A_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, ipString);

    return aRecord; 
  }

public:
  DNS_RECORD* create(const DNS_AAAA_DATA& data, const TCHAR* name, WORD type,
    const TCHAR* ip6String)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_AAAA_DATA* pData = (DNS_AAAA_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, ip6String);

    return aRecord;
  }


public:
  const DNS_RECORD* create(DNS_MX_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameExchange, WORD preference)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_MX_DATA* pData = (DNS_MX_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, nameExchange, preference);

    return aRecord; 
  }

public:
  const DNS_RECORD* create(DNS_NULL_DATA& data, const TCHAR* name, WORD type,
      const BYTE* bytes, int byteCount)
  {
    //The size of DNS_NULL_DATA
    int dataSize = sizeof(data.dwByteCount) + sizeof(data.Data) * byteCount;
    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_NULL_DATA* pData = (DNS_NULL_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, bytes, byteCount);

    return aRecord;
  }


public:
  const DNS_RECORD* create(const DNS_PTR_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameHost)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_PTR_DATA* pData = (DNS_PTR_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, nameHost);

    return aRecord; 
  }



public:
  //WKS=Well Known Service
  const DNS_RECORD*  create(DNS_WKS_DATA& data, const TCHAR* name, WORD type,
    const TCHAR* ipString, 
    UCHAR chProtocol, 
    BYTE* bmask, 
    WORD maskCount)
  {
    int dataSize = sizeof(data.IpAddress) + sizeof(data.chProtocol) + sizeof(data.BitMask) * maskCount;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_WKS_DATA* pData = (DNS_WKS_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, ipString, 
      chProtocol, 
      bmask, 
      maskCount);
    return aRecord;
  }

public:
  const DNS_RECORD* create(DNS_TXT_DATA& data, const TCHAR* name, WORD type,
      TCHAR** strings, 
      int stringCount)
  {
    int dataSize = sizeof(data.dwStringCount) +  sizeof(data.pStringArray) * stringCount;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_TXT_DATA* pData = (DNS_TXT_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, strings, 
      stringCount);
    return aRecord;
  }

public:
  // SOA=Start Of Authority
  const DNS_RECORD* create(DNS_SOA_DATA& data, const TCHAR* name, WORD type,
    TCHAR* namePrimaryServer,
    TCHAR* nameAdministrator,
    DWORD serialNo,
    DWORD refresh,
    DWORD retry,
    DWORD expire,
    DWORD defaultTtl)
  {
    int dataSize = sizeof(data);
    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_SOA_DATA* pData = (DNS_SOA_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      namePrimaryServer,
      nameAdministrator,
      serialNo,
      refresh,
      retry,
      expire,
      defaultTtl);

    return aRecord;
  }

public:
  const DNS_RECORD* create(DNS_MINFO_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameMailbox,
    TCHAR* nameErrorsMailbox) 
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_MINFO_DATA* pData = (DNS_MINFO_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameMailbox,
      nameErrorsMailbox); 

    return aRecord;
  }

public:
  const DNS_RECORD* create(DNS_ATMA_DATA& data, const TCHAR* name, WORD type,
    BYTE addressType,
    int addressLength,      //DNS_ATMA_MAX_ADDR_LENGTH 
    BYTE* address)
  {
    int dataSize = sizeof(data.AddressType) + sizeof(data.Address);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_ATMA_DATA* pData = (DNS_ATMA_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData, 
      addressType,
      addressLength,
      address);
    return aRecord;
  }

public:
  const DNS_RECORD* create(DNS_KEY_DATA& data, const TCHAR* name, WORD type,
    WORD flags,
    BYTE protocol,
    BYTE algorithm,
    int keyLength,
    BYTE* key)
  {
    int dataSize = sizeof(data) - sizeof(data.Key) + sizeof(data.Key) * keyLength;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_KEY_DATA* pData = (DNS_KEY_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      flags,
      protocol,
      algorithm,
      keyLength,
      key);
    return aRecord;
  }

public:
  const DNS_RECORD* create(DNS_SIG_DATA& data, const TCHAR* name, const WORD type,
    TCHAR* nameSigner,
    WORD typeConvered,
    BYTE algorithm,
    BYTE labelCount,
    DWORD originalTtl,
    DWORD expiration,
    DWORD timeSigned,
    WORD keyTag,
    //WORD pad,
    int sigLength,
    BYTE* signature)
  {
    int dataSize = sizeof(data) - sizeof(data.Signature) +  sizeof(data.Signature) * sigLength;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_SIG_DATA* pData = (DNS_SIG_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameSigner,
      typeConvered,
      algorithm,
      labelCount,
      originalTtl,
      expiration,
      timeSigned,
      keyTag,
      //pad,
      sigLength,
      signature);

      return aRecord;
  }


public:
  const DNS_RECORD* create(DNS_NXT_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameNext, 
    WORD numTypes, 
    WORD* types) 
  {
    int dataSize = sizeof(data.pNameNext) + sizeof(data.wNumTypes) + sizeof(data.wTypes) * numTypes;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_NXT_DATA* pData = (DNS_NXT_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameNext, 
      numTypes, 
      types);
    return aRecord;
  }

public:
  DNS_RECORD* create(DNS_SRV_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameTarget, 
    WORD priority, 
    WORD weight, 
    WORD port) 
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_SRV_DATA* pData = (DNS_SRV_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameTarget, 
      priority, 
      weight, 
      port);
    
    return aRecord;
  }


public:
  DNS_RECORD* create(DNS_NAPTR_DATA& data, const TCHAR* name, WORD type,
    WORD order,
    WORD preference,
    TCHAR* flags, 
    TCHAR* service,
    TCHAR* regularExpression,
    TCHAR* replacement)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_NAPTR_DATA* pData = (DNS_NAPTR_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      order,
      preference,
      flags,
      service,
      regularExpression,
      replacement);

    return aRecord;
  }


public:
  DNS_RECORD* create(DNS_TKEY_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameAlgorithm,
    BYTE* algorithmPacket,
    BYTE* key,
    //BYTE* otherData,
    DWORD createTime,
    DWORD expireTime,
    WORD mode,
    WORD error,
    WORD keyLength,
    //WORD otherLength,
    UCHAR algNameLength)
    //BOOL packetPointers)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_TKEY_DATA* pData = (DNS_TKEY_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameAlgorithm,
      algorithmPacket,
      key,
      //otherData,
      createTime,
      expireTime,
      mode,
      error,
      keyLength,
      //otherLength,
      algNameLength);
      //packetPointers);

    return aRecord;
  }

public:
  DNS_RECORD* create(DNS_TSIG_DATA& data, const TCHAR* name, WORD type,
    TCHAR* nameAlgorithm,
    BYTE* algorithmPacket,
    BYTE* signature,
    //BYTE* otherData,
    LONGLONG createTime,
    WORD fudgeTime,
    WORD originalXid,
    WORD error,
    WORD sigLength,
    //WORD otherLength,
    UCHAR algNameLength)
    //BOOL packetPointers)
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_TSIG_DATA* pData = (DNS_TSIG_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      nameAlgorithm,
      algorithmPacket,
      signature,
      //otherData,
      createTime,
      fudgeTime,
      originalXid,
      error,
      sigLength,
      //otherLength,
      algNameLength);
      //packetPointers);

    return aRecord;
  }


public:
  DNS_RECORD* create(DNS_WINS_DATA& data, const TCHAR* name, WORD type,
    DWORD mappingFlag, 
    DWORD lookupTimeout, 
    DWORD cacheTimeout,
    DWORD winsServerCount, 
    TCHAR* ipServers[]) 
  {
    int dataSize = sizeof(data.dwMappingFlag) + 
        sizeof( data.dwLookupTimeout) + sizeof(data.dwCacheTimeout) +
        sizeof(data.cWinsServerCount) + sizeof(data.WinsServers) * winsServerCount;

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_WINS_DATA* pData = (DNS_WINS_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      mappingFlag, 
      lookupTimeout, 
      cacheTimeout,
      winsServerCount, 
      ipServers);

    return aRecord;
  }


public:
  DNS_RECORD* create(DNS_WINSR_DATA& data, const TCHAR* name, WORD type,
    DWORD mappingFlag, 
    DWORD lookupTimeout, 
    DWORD cacheTimeout,
    TCHAR* nameResultDomain) 
  {
    int dataSize = sizeof(data);

    DNS_RECORD* aRecord = alloc(name, type, dataSize);

    DNS_WINSR_DATA* pData = (DNS_WINSR_DATA*)&(aRecord->Data);
    DnsData dnsData;
    dnsData.setValues(*pData,
      mappingFlag,
      lookupTimeout,
      cacheTimeout,
      nameResultDomain);

    return aRecord;
  }
};

}
