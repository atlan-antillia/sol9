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
 *  SignedObject.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/18
// 2009/03/25 Added a new query method to return handles for SOL::CertStore and SOL::CryptMsg.
// 2009/04/03 Fixed a bug in query method

#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <sol/crypt/CryptMsg.h>
#include <sol/crypt/CertStore.h>
#include <sol/crypt/CertContext.h>

#pragma comment(lib, "crypt32.lib")

namespace SOL {

class SignedObject :public Object {
private:
  wchar_t wFileName[MAX_PATH];


public:
  /**
   *
   */
  SignedObject(const char* fileName) 
  {
    memset(wFileName, (wchar_t)0, CountOf(wFileName));
    if (fileName) {
      size_t rsize = 0;
      //if (mbstowcs(wFileName, fileName, MAX_PATH) == -1) {
      if (mbstowcs_s(&rsize, wFileName, CountOf(wFileName), fileName, MAX_PATH) != 0) {
        throw GetLastError();
      }
    }
  }

public:
  SignedObject(const wchar_t* fileName) 
  {
    memset(wFileName, (wchar_t)0, CountOf(wFileName));
    if (fileName) {
      wcscpy_s(wFileName, CountOf(wFileName), fileName);
    } 
  }

public:
  /**
   * Get a message handle and a store handle from the signed file of szFileName, and
   * return a certificateContext to the second parameter.
   * 
   * If the file is signed by authenticode, return NO_ERROR, if not signed this returns other code
   *
   */
  int query(
      __out CertContext& certContext,
      __in_opt DWORD dwExpectedContentTypeFlags=CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
      __in_opt DWORD dwExpectedFormatTypeFlag=CERT_QUERY_FORMAT_FLAG_BINARY,
      __in_opt DWORD dwFlags=0)
  {
    int rc = NO_ERROR;

    HCERTSTORE hStore = NULL;

    PCMSG_SIGNER_INFO pSignerInfo = NULL;
    /*
    typedef struct _CMSG_SIGNER_INFO {
      DWORD                      dwVersion;
      CERT_NAME_BLOB             Issuer;
      CRYPT_INTEGER_BLOB         SerialNumber;
      CRYPT_ALGORITHM_IDENTIFIER HashAlgorithm;
      CRYPT_ALGORITHM_IDENTIFIER HashEncryptionAlgorithm;
      CRYPT_DATA_BLOB            EncryptedHash;
      CRYPT_ATTRIBUTES           AuthAttrs;
      CRYPT_ATTRIBUTES           UnauthAttrs;
    } CMSG_SIGNER_INFO, *PCMSG_SIGNER_INFO;
    */

    try {

      HCRYPTMSG hMsg = NULL; 

      DWORD dwEncoding = 0;
      DWORD dwContentType = 0;
      DWORD dwFormatType =0;

      /*
      BOOL WINAPI CryptQueryObject(DWORD dwObjectType, 
        const void* pvObject, 
        DWORD dwExpectedContentTypeFlags, 
        DWORD dwExpectedFormatTypeFlags, 
        DWORD dwFlags, 
        DWORD* pdwMsgAndCertEncodingType,
        DWORD* pdwContentType, 
        DWORD* pdwFormatType, 
        HCERTSTORE* phCertStore, 
        HCRYPTMSG* phMsg, 
        const void** ppvContext); 
      */

      // Get message handle and store handle from the signed file of szFileName.
      if (!CryptQueryObject(CERT_QUERY_OBJECT_FILE,
          this->wFileName,
          dwExpectedContentTypeFlags,
          dwExpectedFormatTypeFlag,
          dwFlags,
          &dwEncoding,
          &dwContentType,
          &dwFormatType,
          &hStore,
          &hMsg,
                    NULL) ) {
        //Probably this file is not signed 
        //printf("Failed in CryptQueryObject hStore=%x %x\n", hStore, GetLastError());        
        throw GetLastError();
      }

      CryptMsg cryptMsg(hMsg);
      //Get SignerInfo from cryptMsg
      if (cryptMsg.getSignerInfo(&pSignerInfo) !=NO_ERROR) {
        throw GetLastError();
      }
  
      CERT_INFO certInfo;     
      memset(&certInfo, 0, sizeof(certInfo));
      certInfo.Issuer = pSignerInfo->Issuer;
      certInfo.SerialNumber = pSignerInfo->SerialNumber;
      //Find a certificate with the certInfo from the store hStore.

      PCCERT_CONTEXT pCertContext =  CertFindCertificateInStore(hStore,
                                                  (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING),
                                                  0,
                                                  CERT_FIND_SUBJECT_CERT,
                                                  (PVOID)&certInfo,
                                                  NULL);
      delete pSignerInfo;
      
      //2009/04/03
      pSignerInfo = NULL;

      if (!pCertContext) {
        //printf("CertFindCertificateInStore failed with %x\n", GetLastError());
        throw GetLastError();
      }
      // OK
      certContext.set(pCertContext);

    } catch (DWORD err) {
      rc = err;
    } catch (...) {
      rc = GetLastError();
    }
    
    if (pSignerInfo != NULL) {
      delete pSignerInfo;
    }
    
    if (hStore != NULL) {
      CertCloseStore(hStore, 0);
    }

    return rc;
  }

public:
  /**
   * Get a message handle and a store handle from the signed file of szFileName 
   * If the file is signed by authenticode, return NO_ERROR, if not signed this returns other code
   *
   */
  //2009/03/25
  int query(
      __out CertStore& certStore,
      __out CryptMsg& cryptMsg,

      __in_opt DWORD dwExpectedContentTypeFlags=CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
      __in_opt DWORD dwExpectedFormatTypeFlag=CERT_QUERY_FORMAT_FLAG_BINARY,
      __in_opt DWORD dwFlags=0)
  {
    int rc = NO_ERROR;

    try {
      HCERTSTORE hStore = NULL;
      HCRYPTMSG hMsg = NULL; 

      DWORD dwEncoding = 0;
      DWORD dwContentType = 0;
      DWORD dwFormatType =0;

      // Get message handle and store handle from the signed file of szFileName.
      if (!CryptQueryObject(CERT_QUERY_OBJECT_FILE,
          this->wFileName,
          dwExpectedContentTypeFlags, 
          dwExpectedFormatTypeFlag, 
          dwFlags,
          &dwEncoding,
          &dwContentType,
          &dwFormatType,
          &hStore,
          &hMsg,
                    NULL) ) {
        //Probably this file is not signed. 
        throw GetLastError();
      }

      //OK
      certStore.setStoreHandle(hStore);
      cryptMsg.setCryptMsg(hMsg);
  
    } catch (DWORD err) {
      rc = err;
    } catch (...) {
      rc = GetLastError();
    }
    
    return rc;
  }
};

}

