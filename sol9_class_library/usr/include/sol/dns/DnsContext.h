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
 *  DnsContext.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/1 

#pragma once
#include <sol/dns/DnsObject.h>
// 2011/09/5 Modified to use SecurituAuthIdentity.h
#include <sol/net/SecurityAuthIdentity.h>


namespace SOL {

class DnsContext :public DnsObject {
private:
  HANDLE hContext;

public:
  DnsContext()
  :hContext(NULL)
  {
  }


public:
  /**
   * @credentialFlags A flag that indicates the character encoding. Set to TRUE for Unicode, FALSE for ANSI.
   */
  DNS_STATUS  acquire(__in_opt PSEC_WINNT_AUTH_IDENTITY credentials=NULL)
  {

#ifdef UNICODE
    DWORD credentialFlags = TRUE;
#else
    DWORD credentialFlags = FALSE;
#endif
    DNS_STATUS rc = DnsAcquireContextHandle(
        credentialFlags,
        (void*)credentials,
        &hContext);
    if (rc != ERROR_SUCCESS) {
      throw Exception("DnsContext::DnsContext failed", rc);
    }
    return rc;
  }

public:
  /**
   * @credentialFlags A flag that indicates the character encoding. Set to TRUE for Unicode, FALSE for ANSI.
   */
  DNS_STATUS acquire(__in SecurityAuthIdentity& identity)
  {

#ifdef UNICODE
    DWORD credentialFlags = TRUE;
#else
    DWORD credentialFlags = FALSE;
#endif
    const SEC_WINNT_AUTH_IDENTITY* credentials = NULL;
    if (identity.hasUserName()) {
      credentials = identity.getCredentials();
    }
    //_tprintf(_T("DnsContext::DnsContext SEC_WINNT_AUTH_IDENTITY=%ld\n"), credentials);

    DNS_STATUS rc = DnsAcquireContextHandle(
        credentialFlags,
        (void*)credentials,
        &hContext);
    if (rc != ERROR_SUCCESS) {
      throw Exception("DnsContext::DnsContext failed", rc);
    }      
    return rc;
  }


public:
  ~DnsContext()
  {
    if (hContext) {
      DnsReleaseContextHandle(hContext);
      hContext = NULL;
    }
  }

public:
  HANDLE getHandle()
  {
    return hContext;
  }

public:
  operator const HANDLE() const
  {
    return this->hContext;
  }
};

}

