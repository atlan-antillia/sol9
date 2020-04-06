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
 *  CertContext.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/13
// 2009/03/15 Modified construcotr, and ddded create and dump methods.
// 2009/03/18 Added a method getNameString to get String property and return SOL::String.
// 2009/03/20 Added a method getProperty.
// 2009/04/02 Added a method getCertInfo().
// 2009/04/17 Added a clear method, and modified set method to call clear method beforing setting.

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>
#include <sol/String.h>
#include <sol/crypt/CertInfo.h>

namespace SOL {

class CertContext :public Object {

private:
  PCCERT_CONTEXT pContext;

public:
  /**
   * @param  context  PCCERT_CONTEXT
   *      option parameter.
   */
  //2009/03/15 context=NULL
  CertContext(PCCERT_CONTEXT context=NULL)
  :pContext(context)
  {
    //Simple shallow copy for the pointer context;
  }

public:
  /**
   * Destructor
   */
  ~CertContext() {
    //2009/04/17
    clear();
  }

public:
  //2009/04/17
  void clear() {
    if (pContext) {
      CertFreeCertificateContext(pContext);
      pContext = NULL;
    }
  }

public:
  void set(PCCERT_CONTEXT context) 
  {
    //200904/17
    clear();
    this->pContext = context;
  }


public:
  //2009/04/17
  PCCERT_CONTEXT get() 
  {
    return this->pContext;
  }

public:

  int acquireCertificatePrivateKey(HCRYPTPROV* phCryptProv, DWORD* pKeySpec) {
    int rc = NO_ERROR;
    HCRYPTPROV hProv = NULL;
    DWORD dwSpec = 0;
    if(!(CryptAcquireCertificatePrivateKey(
        pContext,
        0,
        NULL,
        &hProv,
        &dwSpec,
        NULL))) {
        *phCryptProv = hProv;
        *pKeySpec    = dwSpec;
    } else {
      rc = GetLastError();
    }
    return rc;
  }


public:
  /**
   */

  int create(__in DWORD encoding, __in const BYTE* data, __in DWORD dataSize) {
    int rc = NO_ERROR;
    if ((pContext = CertCreateCertificateContext(encoding,  //X509_ASN_ENCODING
        data, dataSize)) ) {
      //OK
    } else {
      rc = GetLastError();
    }
    return rc;
  }
/*
DWORD WINAPI CertGetNameString(
  __in   PCCERT_CONTEXT pCertContext,
  __in   DWORD dwType,
  __in   DWORD dwFlags,
  __in   void *pvTypePara,
  __out  LPTSTR pszNameString,
  __in   DWORD cchNameString
);

*/

public:

  /**
   * Call GetNameString and return it as a SOL::String.
   */
  // 2009/03/19
  int getNameString(
      __in   DWORD dwType,
      __out String& name, 
      __in_opt DWORD dwFlags = 0,
      __in_opt void *pvTypePara = NULL
      )  
  {
    int rc = NO_ERROR;

    size_t size = 0;
    if ( (size = CertGetNameString(pContext, 
        dwType, dwFlags, pvTypePara, NULL, 0)) >0 ){
      //OK
      TCHAR* buffer = new TCHAR[size];
      if ( CertGetNameString(pContext, 
        dwType, dwFlags, pvTypePara, buffer, size) > 0) { 
        //OK
        name.shallowCopy(buffer);
      } else {
        delete [] buffer;
        rc = GetLastError();
      }
    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  //2009/03/19 subject 
  int getSubjectName(__out String& name, DWORD dwFlags=0) 
  {
    //return NO_ERROR;

    return getNameString(CERT_NAME_SIMPLE_DISPLAY_TYPE, name, dwFlags);
  }

  /**
   * Simple display name(subject)
   */
  DWORD getName(TCHAR* buffer, size_t size, DWORD dwFlags=0)  
  {
    return CertGetNameString(pContext, 
      CERT_NAME_SIMPLE_DISPLAY_TYPE, dwFlags, NULL, buffer, size);
  }

public:
  //2009/03/19
  int getIssuerName(__out String& name, DWORD dwFlags=CERT_NAME_ISSUER_FLAG)
  {
    return getNameString(CERT_NAME_SIMPLE_DISPLAY_TYPE, name, dwFlags);
  }

  /**
   * Simple display name for Issuer
   */
  DWORD getIssuerName(TCHAR* buffer, size_t size, DWORD dwFlags=0)
  {
    return CertGetNameString(pContext, 
      CERT_NAME_SIMPLE_DISPLAY_TYPE, (dwFlags|CERT_NAME_ISSUER_FLAG), NULL, buffer, size);
  }

public:
  //2009/03/19
  int getFriendlyName(__out String& name, DWORD dwFlags=0)
  {
    return getNameString(CERT_NAME_FRIENDLY_DISPLAY_TYPE, name, dwFlags);
  }

  /**
   * Friendly display name
   */
  DWORD getFriendlyName(TCHAR* buffer, size_t size, DWORD dwFlags=0)  
  {
    return CertGetNameString(pContext, 
      CERT_NAME_FRIENDLY_DISPLAY_TYPE, dwFlags, NULL, buffer, size);
  }

public:

  //2009/03/19
  int getRDNName(__out String& name, DWORD dwFlags=0)
  {
    return getNameString(CERT_NAME_RDN_TYPE, name, dwFlags);
  }


  /**
   * RDN name
   */
  DWORD getRDNName(TCHAR* buffer, size_t size, DWORD *dwStrType=NULL, DWORD dwFlags=0)
  {
    return CertGetNameString(pContext, 
      CERT_NAME_RDN_TYPE, dwFlags, dwStrType, buffer, size);
  }

public:

  //2009/03/19
  int getEmail(__out String& name, DWORD dwFlags=0)
  {
    return getNameString(CERT_NAME_EMAIL_TYPE, name, dwFlags);
  }

  /**
   * EMAIL name
   */
  DWORD getEMail(TCHAR* buffer, size_t size, DWORD dwFlags=0)
  {
    return CertGetNameString(pContext, 
      CERT_NAME_EMAIL_TYPE, dwFlags, NULL, buffer, size);
  }

  //2009/03/19
  int getUrl(__out String& name, DWORD dwFlags=0)
  {
    return getNameString(CERT_NAME_URL_TYPE, name, dwFlags);
  }

public:

  //2009/03/19
  int getCNName(__out String& name, DWORD dwFlags=0)
  {
    TCHAR* CN_OID = _T("2.5.4.3");
    return getNameString(CERT_NAME_ATTR_TYPE, name, dwFlags, CN_OID);
  }

  /**
   * Attribute name CN of "2.5.4.5"
   */
  //Modified to getCNName
  DWORD getCNName(TCHAR* buffer, size_t size, DWORD dwFlags=0)
  {
    const TCHAR* MAGIC =  _T("2.5.4.3");
    return CertGetNameString(pContext, 
      CERT_NAME_ATTR_TYPE, dwFlags, (TCHAR*)MAGIC, buffer, size);
  }
public:
  /**
   * Cast opeator
   * PCCERT_CONTEXT pContext;
   * ...
   * CertContext cert(pContext);
   * PCCERT_CONTEXT pCert = (PCCERT_CONTEXT)cert;
   */
  operator PCCERT_CONTEXT() const 
  { 
    return pContext; 
  }

public:
  /**
   *
   */
  //2009/03/15
  //2009/03/19 Modified some lines to avoid memory leakage.
  void dump()
  {
    TCHAR* szName = NULL;

    // Print Serial Number.
    _tprintf(_T("Serial Number: "));
    DWORD dwData = pContext->pCertInfo->SerialNumber.cbData;
   
    for (DWORD n = 0; n < dwData; n++) {
      printf("0x%02x ", pContext->pCertInfo->SerialNumber.pbData[dwData - (n + 1)]);
    }
        _tprintf(_T("\n"));

    // Get Issuer name size.
    if ((dwData = CertGetNameString(pContext, 
                                         CERT_NAME_SIMPLE_DISPLAY_TYPE,
                                         CERT_NAME_ISSUER_FLAG,
                                         NULL,
                                         NULL,
                                         0)) >0) {

      szName = new TCHAR[dwData];

      // Get Issuer name.
      if (CertGetNameString(pContext, 
                                CERT_NAME_SIMPLE_DISPLAY_TYPE,
                                CERT_NAME_ISSUER_FLAG,
                                NULL,
                                szName,
                                dwData) > 0) {

        _tprintf(_T("Issuer Name: %s\n"), szName);
      } else {
        
      }
      delete [] szName;
    }
    
    // Get Subject name size.
        
    if ((dwData = CertGetNameString(pContext, 
                                         CERT_NAME_SIMPLE_DISPLAY_TYPE,
                                         0,
                                         NULL,
                                         NULL,
                                         0)) > 0) {
      szName =  new TCHAR[dwData];
      // Get subject name.
      if (CertGetNameString(pContext, 
                                CERT_NAME_SIMPLE_DISPLAY_TYPE,
                                0,
                                NULL,
                                szName,
                                dwData) >0 ) {

        // Print Subject Name.
             _tprintf(_T("Subject Name: %s\n"), szName);
      } else {

      }
      delete [] szName;

    }
  }

public:
  /**
   * Get a property-value from a certContext with propId. 
   */
  //2009/03/20
  int getProperty(DWORD dwPropId, void** ppvData, size_t* pDataSize)
  {
    int rc = NO_ERROR;

    DWORD cbData = 0;
       if (CertGetCertificateContextProperty(
             pContext, 
             dwPropId , 
             NULL, 
             &cbData)) {
  
      BYTE* pvData = new BYTE[cbData];

      if (CertGetCertificateContextProperty(
        pContext,
        dwPropId,
         pvData, 
         &cbData)) {
        
        //OK
        *ppvData = (void*)pvData;
        *pDataSize = cbData;
      } else {
        delete [] pvData;
        rc = GetLastError();

      }
    } else {
      rc = GetLastError();

    }
    return rc;
  }


public:
  
  //2009/04/01
  int getCertInfo(CertInfo& certInfo) 
  {
    int rc = NO_ERROR;
    if (pContext && pContext->pCertInfo) {
      certInfo.set(pContext->pCertInfo);
    } else {
      rc = -1;
    }
    return rc;
  }
};

}
