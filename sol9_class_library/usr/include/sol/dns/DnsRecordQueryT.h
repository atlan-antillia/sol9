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
 *  DnsRecordQueryT.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/1 
// 2011/1/14 Updated
// 2011/1/18 Modified class name to be DnsRecordQueryT from DnsRecordListT

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/dns/IPv4AddressArray.h>
#include <sol/net/IPv4AddressInfoList.h>
#include <sol/dns/DnsRecordArrayT.h>
#include <sol/dns/DnsRecord.h>

/*
    Possible combinations of DNS query types and structures 
    -----------------------------------
        Structure           Type
    -----------------------------------
        DNS_A_DATA          DNS_TYPE_A
        DNS_SOA_DATA        DNS_TYPE_SOA

        DNS_PTR_DATA        DNS_TYPE_PTR
                            DNS_TYPE_NS
                            DNS_TYPE_CNAME
                            DNS_TYPE_DNAME
                            DNS_TYPE_MB
                            DNS_TYPE_MD
                            DNS_TYPE_MF
                            DNS_TYPE_MG
                            DNS_TYPE_MR

        DNS_MINFO_DATA      DNS_TYPE_MINFO
                            DNS_TYPE_RP

        DNS_MX_DATA         DNS_TYPE_MX
                            DNS_TYPE_AFSDB
                            DNS_TYPE_RT
        DNS_TXT_DATA        DNS_TYPE_HINFO
                            DNS_TYPE_ISDN
                            DNS_TYPE_TEXT
                            DNS_TYPE_X25

        DNS_NULL_DAT        DNS_TYPE_NULL
        DNS_WKS_DATA        DNS_TYPE_WKS
        DNS_AAAA_DAT        DNS_TYPE_AAAA
        DNS_KEY_DATA        DNS_TYPE_KEY
        DNS_SIG_DATA        DNS_TYPE_SIG
        DNS_ATMA_DATA       DNS_TYPE_ATMA
        DNS_NXT_DATA        DNS_TYPE_NXT
        DNS_SRV_DATA        DNS_TYPE_SRV
        DNS_NAPTR_DATA      DNS_TYPE_NAPTR
        DNS_TKEY_DATA       DNS_TYPE_TKEY
        DNS_TSIG_DATA       DNS_TYPE_TSIG
        DNS_WINS_DATA       DNS_TYPE_WINS
        DNS_WINSR_DATA      DNS_TYPE_WINSR
*/

namespace SOL {

template <typename T> class DnsRecordQueryT :public DnsRecord {

private:
  WORD    type;
  
private:
  IPv4AddressArray ipv4Array;

private:
  DnsRecordArrayT<T> recordArray;

public:
  /**
   * Constructor
   */
  DnsRecordQueryT(__in WORD qtype, __in const TCHAR* primaryDNSServer=NULL, 
      __in const TCHAR* secondaryDNSServer=NULL)
  :type(qtype)
  {
    //Check DNS query type
    if ((type >= DNS_TYPE_A     && type<=DNS_TYPE_OPT) ||
      (type >= DNS_TYPE_ADDRS && type<=DNS_TYPE_ANY) ||
      (type >=DNS_TYPE_WINS   && type<=DNS_TYPE_WINSR)) {    //2011/1/20 Added for Windows specific query types.
      ; //OK
    } else {
      throw Exception("DnsRecordQueryT::DnsRecordQueryT; Invalid type");
    }

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
          _tprintf(_T("primaryDNSServer %s\n"), primaryDNSServer);
          in_addr addr;
          infoList.getFirst(addr);
          ipv4Array.setNth(n++, addr);
        } catch (...) {
          ;//Ignore error
          _tprintf(_T("Error in IPv4AddressInfoList::getAddrInfo() for %s\n"), primaryDNSServer);
        }
      }

      if (secondaryDNSServer) {
        try {
          IPv4AddressInfoList infoList;

          infoList.getAddrInfo(secondaryDNSServer);
          _tprintf(_T("secondaryDNSServer %s\n"), secondaryDNSServer);

          in_addr addr;
          infoList.getFirst(addr);
          ipv4Array.setNth(n++, addr);
        } catch (...) {
          ;//Ignore error
          _tprintf(_T("Error in IPv4AddressInfoList::getAddrInfo() for %s\n"), secondaryDNSServer);

        }
      }
      //Reconfirm the values forIP4_ARRAY 
      ipv4Array.display();
    }
  }

public:
  /**
   *
   */
  ~DnsRecordQueryT()
  {
    clear();
  }

public:
  void clear()
  {
    recordArray.clear();
    DNS_RECORD* pRecord = getRecord();
    if (pRecord) {
      DnsRecordListFree(pRecord, DnsFreeRecordList);
    }
  }

public:
  /**
   * Call DnsQuery API and store the result to DNSRecordArrayT recordArray 
   */
  
//template <typename T>
  int query(__in const TCHAR* hostDomain, __in DWORD options=DNS_QUERY_STANDARD)
  {
    clear();

    size_t count = 0;
    DNS_RECORD* pRecord = NULL;

    DWORD rc =   DnsQuery(hostDomain, 
            this->type,        //DNS_TYPE_ANY,
            options,
            (void*)(const IP4_ARRAY*)ipv4Array,  //NULL, 
            &pRecord, NULL);

    if (rc != ERROR_SUCCESS) {
      throw Exception("DnsRecordQueryT::query failed", rc);
    } else {

      setRecord(pRecord);

      PDNS_RECORD ptr = pRecord;
      while (ptr) {
        if(ptr->wType == this->type) {
          count++;
        }
        ptr = ptr->pNext;
      }

      if (count >0) {
        //Allocate DNSRecordArrayT recordArray of count. 
        DnsRecordT<T>*  tarray = this->recordArray.alloc(type, count);


        PDNS_RECORD ptr = pRecord;
        while (ptr) {
          if(ptr->wType == this->type) {
            T* data = (T*)&(ptr->Data);
            if (data) {
              //Make a copy for data to tarray 
              tarray->copy(ptr->pName, ptr->wType, ptr->dwTtl, ptr->Flags.S, ptr->wDataLength, *data);
              tarray++;
            }
          }
          ptr = ptr->pNext;
        }
      }
    } 
    return count;
  }

public:
  void getFirst(T& t) 
  {
    getNth(0, t);
  }

public:
  void getNth(int n, T& t) 
  {
    DnsRecordT<T>& record = recordArray.getNth(n);
    t = record.getData();
  }

public:
  T& getFirst() 
  {
    return getNth(0);
  }

public:
  T& getNth(int n) 
  {
    DnsRecordT<T>& record = recordArray.getNth(n);
    return record.getData();
  }

public:
  bool getNth(int n, DnsRecordT<T>& record) 
  {
    bool rc = true;
    record = recordArray.getNth(n);
    return rc;
  }

public:
  void display()
  {
    recordArray.display();
  }

};

}
