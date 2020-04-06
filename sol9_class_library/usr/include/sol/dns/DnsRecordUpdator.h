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
 *  DnsRecordUpdator.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/16

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/dns/IPv4AddressArray.h>
#include <sol/net/IPv4AddressInfoList.h>
#include <sol/dns/DnsRecordArrayT.h>
#include <sol/dns/DnsContext.h>
#include <sol/net/SecurityAuthIdentity.h>

namespace SOL {

class DnsRecordUpdator :public DnsObject {

private:
  DnsContext context;

private:
  SecurityAuthIdentity identity;

public:
  /**
   * Constructor
   */
  DnsRecordUpdator(__in const TCHAR* user=NULL, __in const TCHAR* password=NULL, 
      __in const TCHAR* domain=NULL)
  :identity(user, password, domain)
  {
    context.acquire(identity);
  }

public:
  /**
   * Destructor
   */
  ~DnsRecordUpdator()
  {
  }


/**
  @options A value that contains a bitmap of the following DNS Update Options. 
      Options can be combined and all options override DNS_UPDATE_SECURITY_USE_DEFAULT.

    DNS_UPDATE_SECURITY_USE_DEFAULT
    DNS_UPDATE_SECURITY_OFF
    DNS_UPDATE_SECURITY_ON 
    DNS_UPDATE_SECURITY_ONLY
    DNS_UPDATE_CACHE_SECURITY_CONTEXT
    DNS_UPDATE_TEST_USE_LOCAL_SYS_ACCT
    DNS_UPDATE_FORCE_SECURITY_NEGO     
    DNS_UPDATE_TRY_ALL_MASTER_SERVERS  
    DNS_UPDATE_SKIP_NO_UPDATE_ADAPTERS
    DNS_UPDATE_REMOTE_SERVER
    DNS_UPDATE_RESERVED     
*/

public:
  DNS_STATUS addRecords(
    __in DNS_RECORD* addRecords,
    __in DWORD options=DNS_UPDATE_SECURITY_USE_DEFAULT)
  {
    if (addRecords == NULL) {
      throw ERROR_INVALID_PARAMETER;
    }

    DNS_STATUS rc = 0;
    if ((rc = DnsModifyRecordsInSet(
        addRecords,
        NULL,  
        options,
        (HANDLE)context,
        NULL,
        NULL)) !=ERROR_SUCCESS) {
      throw Exception("DnsRecordUpdator::addRecords failed", rc);
    }      

    return rc;
  }

public:
  DNS_STATUS deleteRecords(
    __in DNS_RECORD* deleteRecords,
    __in DWORD  options=DNS_UPDATE_SECURITY_USE_DEFAULT)
  {
    if (deleteRecords == NULL) {
      throw ERROR_INVALID_PARAMETER;
    }

    DNS_STATUS rc = 0;
    if ((rc = DnsModifyRecordsInSet(
        NULL,
        deleteRecords,
        options,
        (HANDLE)context,
        NULL,
        NULL)) != ERROR_SUCCESS) {
      throw Exception("DnsRecordUpdator::deleteRecords failed", rc);
    }      

    return rc;
  }

public:
  DNS_STATUS replaceRecords(
    __in DNS_RECORD* replaceSet,
    __in DWORD options=DNS_UPDATE_SECURITY_USE_DEFAULT)
  {
    if (replaceSet == NULL) {
      throw ERROR_INVALID_PARAMETER;
    }
  
    DNS_STATUS rc = 0;
    if ((rc = DnsReplaceRecordSetW(
         replaceSet,
        options,
        (HANDLE)context,
         NULL,
        NULL)) != ERROR_SUCCESS) {
      throw Exception("DnsRecordUpdator::replaceRecords failed", rc);
    }      

    return rc;
  }

};

}
