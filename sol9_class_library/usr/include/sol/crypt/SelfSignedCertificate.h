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
 *  SelfSignedCertificate.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/17

#pragma once

#include <sol/Object.h>
#include <sol/crypt/CertContext.h>

#include <sol/crypt/X509ASNEncoder.h>


namespace SOL {

class SelfSignedCertificate :public CertContext {

public:
  /**
   * Constructor
   */
  SelfSignedCertificate()
  {

  }


public:
  /**
   * Create a self-signed certificate from a subjectAndIssuerName string by using
   * CertCreateSelfSignCertificate() API.
   *
   * @param hCryptProvOrNCryptKey  Handle for HCRYPTPROV or NCRYPT_KEY_HANDLE.
   *    This may take NULL for a default cryptprovider.
   * @param subjectAndIssuerName   Specify subject(owner) and issuer name as "CN=CertificatePublisher"
   * @return PCCERT_CONTEXT  Pointer to CERT_CONTEXT structure
   */

  int create(
    __in HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProvOrNCryptKey,
    __in const TCHAR* subjectAndIssuerName,
    __in_opt DWORD dwFlags = 0,
    __in_opt PCRYPT_KEY_PROV_INFO pKeyProvInfo = NULL,
    __in_opt PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm = NULL,
    __in_opt PSYSTEMTIME pStartTime = NULL,
    __in_opt PSYSTEMTIME pEndTime = NULL,
    __in_opt PCERT_EXTENSIONS pExtensions = NULL)

  {
    int rc = -1;

    X509ASNEncoder encoder;
    Bytes bytes;
    //Get a binary expression for the subjectAndIssuerName string.
    if (encoder.toName(subjectAndIssuerName, CERT_X500_NAME_STR, bytes) == NO_ERROR) {
      CERT_NAME_BLOB subjectAndIssuerBlob;

      subjectAndIssuerBlob.cbData = bytes.getSize();
      subjectAndIssuerBlob.pbData = bytes.getData();


      PCCERT_CONTEXT pContext = CertCreateSelfSignCertificate(
        hCryptProvOrNCryptKey,
        &subjectAndIssuerBlob,
        dwFlags,
        pKeyProvInfo,
        pSignatureAlgorithm,
        pStartTime,
        pEndTime,
        pExtensions);

      set(pContext);

      rc = NO_ERROR;

    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   * Added a certcontext to a cerstore of name of store 
   * @param store   StoreName ("MY", "CA", "ROOT",,..) to add a certiciate
   * @param pContext Pointer to CERT_CONTEXT.
   */
  int addToStore(const TCHAR* store=_T("MY"))
  {
    int rc = -1;

    HCERTSTORE hStore = CertOpenSystemStore(0, store);
    if (hStore == NULL) {
      return GetLastError();
    }

    PCCERT_CONTEXT pContext = get();
    if (pContext) {
      if (CertAddCertificateContextToStore(hStore, 
        pContext, 
        CERT_STORE_ADD_REPLACE_EXISTING, 
        NULL)) {

        rc = NO_ERROR;
      } else {
        //Error
        rc = GetLastError();
      } 
    }
    CertCloseStore(hStore, CERT_CLOSE_STORE_CHECK_FLAG);
    return rc;
  }

public:
  /**
   * Save a certcontext to a file of fileName.
   *
   * @param fileName FileName to save a certificate.
   */
  int saveToFile(const TCHAR* fileName)
  {
    int rc = -1;  

    HANDLE hFile = CreateFile(fileName, 
      GENERIC_WRITE, 
      0, NULL, 
      CREATE_ALWAYS, 
      FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {

      //Error to open
      return GetLastError();
    }

    DWORD  dwWrittenBytes = 0;

    PCCERT_CONTEXT pContext = get();
    if (pContext) {

      if (WriteFile(hFile, 
        pContext->pbCertEncoded, 
        pContext->cbCertEncoded, &dwWrittenBytes, NULL)) {
        rc = NO_ERROR;
      } else {
        rc = GetLastError();
      }
    }

    CloseHandle(hFile);

    return rc;
  }

};

}

