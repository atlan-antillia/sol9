/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  CertInfo.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/06

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>
#include <locale.h>

#pragma comment (lib, "crypt32.lib")

/*
CERT_SYSTEM_STORE_CURRENT_USER
CERT_SYSTEM_STORE_LOCAL_MACHINE
CERT_SYSTEM_STORE_CURRENT_SERVICE 
*/

namespace SOL {

class CertSystemStoreEnum : public Object {

public:
  /**
   * Constructor
   */
  CertSystemStoreEnum()
  {
    //Use SOL;;Locale class
    //_tsetlocale(LC_ALL, lang);  // "Japanese_Japan.20932";
  }

protected:
  /**
   * This is a virtual method which can be called from static method enumCallback.
   * This simply shows a storeName and a localized name of each enumerated store.
   */
  virtual BOOL enumStore(const void *pvSystemStore, 
    DWORD dwFlags, 
    PCERT_SYSTEM_STORE_INFO pStoreInfo)
  {
    const wchar_t* systemStore = (const wchar_t*)pvSystemStore;

    const wchar_t* name = CryptFindLocalizedName(systemStore);
    if (systemStore && wcslen(systemStore)>0 && name) {
      wprintf(L"%s (%s)\n", systemStore, name);
    }
    return TRUE;
  }


public:
  /**
   */
  void enumerate(DWORD dwFlags = CERT_SYSTEM_STORE_CURRENT_USER)
  {
    CertEnumSystemStore(dwFlags, NULL, this, enumCallback);
  }

private:
  static BOOL WINAPI enumCallback(const void *pvSystemStore, 
    DWORD dwFlags, 
    PCERT_SYSTEM_STORE_INFO pStoreInfo, 
    void *pvReserved, 
    void *pvArg)
  {
    BOOL rc = FALSE;    
    CertSystemStoreEnum* storeEnum = (CertSystemStoreEnum*)pvArg;
    if (storeEnum) {
      // Call protected virtual method enumStore.
      rc =storeEnum -> enumStore(pvSystemStore, dwFlags, pStoreInfo);

    }
    return rc;

  }
};

}
