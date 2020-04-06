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
 *  DnsAnyRecordQuery.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/1  DNS Any Type(DNS_TYPE_ANY) Resource Record Query

// 2011/1/18 Modified class name to be DnsAnyRecordQuery from DnsRecordList

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/dns/IPv4AddressArray.h>
#include <sol/net/IPv4AddressInfoList.h>
#include <sol/dns/DnsData.h>
#include <sol/dns/DnsRecord.h>

namespace SOL {

class DnsAnyRecordQuery :public DnsRecord {

private:
  WORD    type;

private:
  IPv4AddressArray ipv4Array;

public:
  /**
   * Constructor
   */
  DnsAnyRecordQuery(__in const TCHAR* primaryDNSServer=NULL, 
      __in const TCHAR* secondaryDNSServer=NULL)
    :type(DNS_TYPE_ANY)
  {
    int count = 0;
    if (primaryDNSServer) {
      count++;
    }
    if (secondaryDNSServer) {
      count++;
    }

    if (count > 0) {
      ipv4Array.allocArray(count);
      int n = 0;
      if (primaryDNSServer) {
        try {
          IPv4AddressInfoList infoList;
          infoList.getAddrInfo(primaryDNSServer);
          in_addr addr;
          infoList.getFirst(addr);
          ipv4Array.setNth(n++, addr);
        } catch (...) {
          ;//Ignore error
        }
      }

      if (secondaryDNSServer) {
        try {
          IPv4AddressInfoList infoList;
          infoList.getAddrInfo(secondaryDNSServer);
          in_addr addr;
          infoList.getFirst(addr);
          ipv4Array.setNth(n++, addr);
        } catch (...) {
          ;//Ignore error
        }
      }
    }//count?0
  }

public:
  /**
   * Destructor
   */
  ~DnsAnyRecordQuery()
  {
    clear();
  }

public:
  void clear()
  {
    DNS_RECORD* pRecord = getRecord();

    if (pRecord) {
      DnsRecordListFree(pRecord, DnsFreeRecordList);
    }
  }

public:
  /**
   * Call DnsQuery API and store the result to dataArray 
   */
  int query(__in const TCHAR* hostDomain, __in DWORD options=DNS_QUERY_STANDARD)
  {
    clear();

    DNS_RECORD* pRecord = NULL; 
    DWORD rc =   DnsQuery(hostDomain, this->type, 
            options,
            NULL, &pRecord, NULL);

    if (rc != ERROR_SUCCESS) {
      throw Exception("DnsRecordListT::query failed", rc);
    }

    setRecord(pRecord);

    return rc;
  }

};

}
