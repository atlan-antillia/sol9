/******************************************************************************
 *
 * Copyright (c) 2009  TOSHIYUKI ARAI. ALL RIGHTS RESERVED. 
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
 *  CertPhysicalStore.h
 *
 *****************************************************************************/

//2009/03/13

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>


namespace SOL {

/*
typedef struct _CERT_PHYSICAL_STORE_INFO {
  DWORD               cbSize;
  LPSTR               pszOpenStoreProvider;
  DWORD               dwOpenEncodingType;
  DWORD               dwOpenFlags;
  CRYPT_DATA_BLOB     OpenParameters;
  DWORD               dwFlags;
  DWORD               dwPriority;
} CERT_PHYSICAL_STORE_INFO, *PCERT_PHYSICAL_STORE_INFO;
*/

class CertPhysicalStore :public Object {

private:
  static BOOL WINAPI enumPhysicalStoreCallback(const void *pvSystemStore, 
      DWORD dwFlags, 
      LPCWSTR pwszStoreName, 
      PCERT_PHYSICAL_STORE_INFO pStoreInfo, 
      void *pvReserved, 
      void *pvArg) 
  {
    //
    BOOL rc = FALSE;
    CertPhysicalStore* physicalStore = (CertPhysicalStore*)pvArg;
    if (physicalStore) {
      physicalStore->enumerate(pvSystemStore, dwFlags, pwszStoreName,
        pStoreInfo,
        pvReserved);
      rc = TRUE;
    }
    return rc;
  }

public:
  /**
   * Constructor
   */
  CertPhysicalStore()
  {
    //
  }

public:
  void enumStore(const TCHAR* name,
      DWORD flags=CERT_SYSTEM_STORE_CURRENT_USER) 
  {

    CertEnumPhysicalStore(name, 
      CERT_SYSTEM_STORE_CURRENT_USER, this,
       enumPhysicalStoreCallback);
    
  }

public:

  virtual void enumerate(const void *pvSystemStore, 
    DWORD dwFlags, 
    LPCWSTR pwszStoreName, 
    PCERT_PHYSICAL_STORE_INFO pStoreInfo, 
    void *pvReserved) 
  {
    //Do something
    //_tprintf(_T("Provider=%S, StoreName=%S\n"),
    //2009/11/10
    wprintf(L"Provider=%S, StoreName=%s\n",

      pStoreInfo->pszOpenStoreProvider,
      pwszStoreName);

    HCERTSTORE hStore = CertOpenStore(pStoreInfo->pszOpenStoreProvider, 
      pStoreInfo->dwOpenEncodingType, 
      0, 
      pStoreInfo->dwOpenFlags, 
      pStoreInfo->OpenParameters.pbData);

    if (hStore) {
      _tprintf(_T("OK, opened a store\n"));
      if (CertCloseStore(hStore, 0)) {
        _tprintf(_T("Closed\n"));

      } else {
        _tprintf(_T("Failed to close\n"));
      }
    } else {
      _tprintf(_T("Failed to open\n"));
    }
  }  
};

}
