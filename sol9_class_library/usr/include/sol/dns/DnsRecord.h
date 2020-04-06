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
 *  DnsRecord.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/18 

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/dns/IPv4AddressArray.h>
#include <sol/net/IPv4AddressInfoList.h>
#include <sol/dns/DnsData.h>

namespace SOL {

class DnsRecord :public DnsObject {

private:
  PDNS_RECORD pRecord;

public:
  /**
   * Constructor
   */
  DnsRecord()
    :pRecord(NULL)
  {
  }

public:
  /**
   * Destrucotr
   */
  virtual ~DnsRecord() 
  {
    pRecord = NULL;
  }

public:
  PDNS_RECORD getRecord()
  {
    return this->pRecord;
  }

public:
  void setRecord(DNS_RECORD* aRecord)
  {
    this->pRecord = aRecord;  
  }

public:
  void addRecord(DNS_RECORD* aRecord)
  {
  //If this->record is NULL, then set the above aRecord to this->record;
    if (this->pRecord == NULL) {
      this->pRecord = aRecord;
    } else {
      //else get a last DNS_RECORD from this->pRecord, and set the above aRecord to it;
      DNS_RECORD* ptr = this->pRecord;
      while (ptr->pNext != NULL) {
        ptr = ptr ->pNext;
      }
      ptr ->pNext = aRecord;
    }
  }


public:
  int getCount() 
  {
    PDNS_RECORD ptr = this->pRecord;
    int count = 0;
    while (ptr) {
      count++;
      ptr = ptr->pNext;
    } 
    return count;
  }

public:
  PDNS_RECORD getNth(int n) 
  {
    PDNS_RECORD rec = NULL;
    PDNS_RECORD ptr = this->pRecord;
    int count = 0;
    while (ptr) {
      if (count == n) {
        rec = ptr;
        break;
      }
      count++;
      ptr = ptr->pNext;
    } 
    return rec;
  }


public:
  virtual void display()
  {
    PDNS_RECORD ptr = this->pRecord;
    _tprintf(_T("<?xml version=\"1.0\"?>\n"));

    _tprintf(_T("<DNS_RECORD_LIST>\n"));
    while (ptr) {
      display(ptr);  
      ptr = ptr->pNext;
    } 
    _tprintf(_T("</DNS_RECORD_LIST>\n"));
  }

public:
  void display(PDNS_RECORD ptr)
  {
    DnsData dnsData;
    _tprintf(_T("<DNS_RECORD Name=\"%s\" Type=\"%d\" Section=\"%d\" CharSet=\"%d\" DataLength=\"%d\">\n"), 
      ptr->pName, 
      ptr->wType,
      ptr->Flags.S.Section,
      ptr->Flags.S.CharSet,
      ptr->wDataLength);

    switch(ptr->wType)
    {
    case DNS_TYPE_A:
      dnsData.display(ptr->Data.A, _T("A"));
      break;

    case DNS_TYPE_SOA:
      dnsData.display(ptr->Data.Soa, _T("SOA"));
      break;

    //<Data T="DNS_PTR_DATA">
    case DNS_TYPE_PTR:
      dnsData.display(ptr->Data.Ptr, _T("PTR"));
      break;

    case DNS_TYPE_NS:
      dnsData.display(ptr->Data.Ns, _T("NS"));
      break;
    
    case DNS_TYPE_CNAME:
      dnsData.display(ptr->Data.Cname, _T("CNAME"));
      break;

    case DNS_TYPE_DNAME:
      dnsData.display(ptr->Data.Dname, _T("DNAME"));
      break;

    case DNS_TYPE_MD:
      dnsData.display(ptr->Data.Md, _T("MD"));
      break;

    case DNS_TYPE_MF:
      dnsData.display(ptr->Data.Mf, _T("MF"));
      break;

    case DNS_TYPE_MG:
      dnsData.display(ptr->Data.Mg, _T("MG"));
      break;

    case DNS_TYPE_MR:
      dnsData.display(ptr->Data.Mr, _T("MR"));
      break;
    //</Data>

    //<Data T="DNS_MINFO_DATA">
    case DNS_TYPE_MINFO:
      dnsData.display(ptr->Data.Minfo, _T("MINFO"));
      break;

    case DNS_TYPE_RP:
      dnsData.display(ptr->Data.Rp, _T("RP"));
      break;
    //</Data>

    //<Data T="DNS_MX_DATA">
    case DNS_TYPE_MX:
      dnsData.display(ptr->Data.Mx, _T("MX"));
      break;

    case DNS_TYPE_AFSDB:
      dnsData.display(ptr->Data.Afsdb, _T("AFSDB"));
      break;

    case DNS_TYPE_RT:
      dnsData.display(ptr->Data.Rt, _T("RT"));
      break; 
    //</Data>

    //<Data T="DNS_TYPE_TEXT">
    case DNS_TYPE_TEXT:
      dnsData.display(ptr->Data.Txt, _T("TEXT"));
      break;

    case DNS_TYPE_HINFO:
      dnsData.display(ptr->Data.Hinfo, _T("HINFO"));
      break;

    case DNS_TYPE_ISDN:
      dnsData.display(ptr->Data.Isdn, _T("ISDN"));
      break;
    case DNS_TYPE_X25:
      dnsData.display(ptr->Data.X25, _T("X25"));
      break;
    //</Data>

    case DNS_TYPE_NULL:
      dnsData.display(ptr->Data.Null, _T("NULL"));
      break;

    case DNS_TYPE_WKS:
      dnsData.display(ptr->Data.Wks, _T("WKS"));
      break;

    case DNS_TYPE_AAAA:
      dnsData.display(ptr->Data.AAAA, _T("AAAA"));
      break;

    case DNS_TYPE_KEY:
      dnsData.display(ptr->Data.Key, _T("KEY"));
      break;

    case DNS_TYPE_SIG:
      dnsData.display(ptr->Data.Sig, _T("SIG"));
      break;

    case DNS_TYPE_ATMA:
      dnsData.display(ptr->Data.Atma, _T("ATMA"));
      break;

    case DNS_TYPE_NXT:
      dnsData.display(ptr->Data.Nxt, _T("NXT"));
      break;
  
    case DNS_TYPE_SRV:
      dnsData.display(ptr->Data.Srv, _T("SRV"));
      break;

    case DNS_TYPE_NAPTR:
      dnsData.display(ptr->Data.Naptr, _T("NAPTR"));
      break;

    case DNS_TYPE_TKEY:
      dnsData.display(ptr->Data.Tkey, _T("TKEY"));
      break;

    case DNS_TYPE_TSIG:
      dnsData.display(ptr->Data.Tsig, _T("TSIG"));
      break;

    case DNS_TYPE_WINS:
      dnsData.display(ptr->Data.Wins, _T("WINS"));
      break;

    case DNS_TYPE_WINSR:
      dnsData.display(ptr->Data.WinsR, _T("WINSR"));
      break;

    default:
      break;
    }
    _tprintf(_T("</DNS_RECORD>\n"));
  }

};

}
