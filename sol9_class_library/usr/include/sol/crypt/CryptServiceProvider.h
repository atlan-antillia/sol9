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
 *  CryptServiceProvider.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/17
// 2009/03/04 Modified getProviderName
// 2009/03/15 Added two methods exportPublicKeyInfo, importPublicKeyInfo
// 2003/03/23 Added a method hashPublicKeyInfo.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/String.h>
#include <sol/SmartPtrs.h>
#include <wincrypt.h>
#include <sol/crypt/CryptError.h>

namespace SOL {

class CryptServiceProvider :public Object {

private:
  HCRYPTPROV hCryptProv;


public:
  /**
   * Constructor
   * @param type
    PROV_RSA_AES;    //RC2,RC4,AES
    PROV_RSA_SCHANNEL;  //RC4,DES,TripleDES
    PROV_DSS;      //2009/03/04
    PROV_DSS_DH;    //CYLINK_MEK,
    PROV_DH_SCHANNEL;  //DES,Triple DES
   */
  CryptServiceProvider(__in const DWORD type=PROV_RSA_AES)
  :hCryptProv(NULL) {

    TCHAR* name = _T("");

    getProviderName(type, &name);

    if (!CryptAcquireContext(
      &hCryptProv, 
      NULL,      // Container name
      name,  // Provider name
      type,  // Provider type
      CRYPT_VERIFYCONTEXT))  {
      //CRYPT_NEWKEYSET))  {
  
      throw Exception(GetLastError(),
        "CryptServiceProvider#CryptServiceProvider,1,CryptAcquireContext failed");
    
    } 
  }

public:
  /**
   * Constructor
   * @param type
    PROV_RSA_AES;    //RC2,RC4,AES
    PROV_RSA_SCHANNEL;  //RC4,DES,TripleDES
    PROV_DSS;      //2009/03/04
    PROV_DSS_DH;    //CYLINK_MEK,
    PROV_DH_SCHANNEL;  //DES,Triple DES
   */
  CryptServiceProvider(__in const TCHAR* container, 
        __in const DWORD type=PROV_RSA_FULL, 
        __in const TCHAR* name=NULL)
  :hCryptProv(NULL) {

    if (!CryptAcquireContext(
      &hCryptProv,
      container,    // Container name 
      name,  // Provider name
      type,  // Provider type
      CRYPT_MACHINE_KEYSET))  {

      //DWORD rc = GetLastError();
      //if (rc == NTE_BAD_KEYSET) {
  
        if (!CryptAcquireContext(
          &hCryptProv, 
          container, 
          name,
          type,  
          CRYPT_MACHINE_KEYSET|CRYPT_NEWKEYSET)) {

          //
          throw Exception(GetLastError(),
            "CryptServiceProvider#CryptServiceProvider,1,CryptAcquireContext failed");
         
        }
      //}
    }
  }

public:
  //Destructor
  ~CryptServiceProvider() {
    if (hCryptProv) {
      CryptReleaseContext(hCryptProv, 0);
      hCryptProv = NULL;
    }
  }

public:
  // Get the name of the CSP.
  int  getProviderName(__out String& string){
    int size = 0;
    int rc = NO_ERROR;
    
    CryptGetProvParam(
      hCryptProv, 
      PP_NAME, 
      NULL, 
      (DWORD*)&size, 0);
    if (size > 0) {
      SmartPtrs<char> name = new char[size+1];
      if (!CryptGetProvParam(
        hCryptProv, 
        PP_NAME, 
        (BYTE*)(const char*)name, 
        (DWORD*)&size, 0)) {
        string = "";
        rc = GetLastError();
      } else {
        string = (const char*)name;  
      }
    }
    return rc;
  }


public:
  // Get the name of the KeyContainer.
  int  getKeyContainer(__out String& string) {
    int size = 0;
    int rc = NO_ERROR;
    
    CryptGetProvParam(
      hCryptProv, 
      PP_CONTAINER, 
      NULL, 
      (DWORD*)&size, 0);
    if (size > 0) {
      SmartPtrs<char> name = new char[size+1];
      if (!CryptGetProvParam(
        hCryptProv, 
        PP_CONTAINER, 
        (BYTE*)(const char*)name, 
        (DWORD*)&size, 0)) {
        string = "";
        rc = GetLastError();
      } else {
        string = (const char*)name;  
      }
    }
    return rc;
  }


public:
  HCRYPTPROV getProviderHandle() {
    return this->hCryptProv;
  }


private:
  static bool getProviderName(__in const DWORD type, TCHAR** name)
  {
    bool rc = true;

    switch (type) {
    case PROV_RSA_AES:
      *name = MS_ENH_RSA_AES_PROV;
      break;

    case PROV_RSA_SCHANNEL:
      *name = MS_DEF_RSA_SCHANNEL_PROV;
      break;

    case PROV_DSS_DH:
      *name = MS_DEF_DSS_DH_PROV;
      break;

    case PROV_DH_SCHANNEL:
      *name = MS_DEF_DH_SCHANNEL_PROV;
      break;

      //2009/03/04
    case PROV_DSS:
      *name = MS_DEF_DSS_PROV;
      break;

    default:
      rc = false;
      break;
    }
    return rc;
  }

public:
  int stat()
  {
    int rc = 0;
    BYTE pbData[1000];
    //First time only    
    DWORD dwFlags =CRYPT_FIRST;

    DWORD dwDataLen = 1000;
    bool looping = true;
    while (looping) {
      // Enumerate the supported algorithms.
      CryptGetProvParam(this->hCryptProv, PP_ENUMALGS, pbData, &dwDataLen, dwFlags);
      rc= GetLastError();
      if (rc == ERROR_NO_MORE_ITEMS){
        break;
      }
      dwFlags = 0;

      // Extract algorithm information from 'pbData'.
      BYTE *ptr = pbData;
      ALG_ID algid = *(ALG_ID *)ptr;
      ptr += sizeof(ALG_ID);
      DWORD dwBits = *(DWORD *)ptr;
      ptr += sizeof(DWORD);

      DWORD dwNameLen = *(DWORD *)ptr;
      ptr += sizeof(DWORD);
      char algName[256];
      memset(algName, 0, CountOf(algName));
      strncpy_s(algName, CountOf(algName), (char*)ptr, dwNameLen);
      TCHAR* algType = NULL;

      switch (GET_ALG_CLASS(algid)) {
      case ALG_CLASS_DATA_ENCRYPT:
        algType = _T("Encrypt  ");
        break;
      case ALG_CLASS_HASH:
        algType = _T("Hash     ");
        break;
      case ALG_CLASS_KEY_EXCHANGE:
        algType = _T("Exchange ");
        break;
      case ALG_CLASS_SIGNATURE:
        algType = _T("Signature");
        break;
      default:
        algType = _T("Unknown  ");
        break;
      }
      String algorithm = algName;
      //2009/11/10
      _tprintf(_T("Name:%-14s Type:%s  Bits:%-4d AlgId:0x%8.8x\n"),
        (const TCHAR*)algorithm, algType, dwBits, algid);
    
    }

    return rc;
  }

public:
  // 2009/03/15
  int exportPublicKeyInfo(__in DWORD keySpec, 
        __in DWORD encodingType, 
        __out PCERT_PUBLIC_KEY_INFO* ppKeyInfo)
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    if (CryptExportPublicKeyInfo(hCryptProv, keySpec, encodingType, //X509_ASN_ENCODING, 
      NULL, &size)) {
      PCERT_PUBLIC_KEY_INFO pKeyInfo = (PCERT_PUBLIC_KEY_INFO)new BYTE[size];

      if (CryptExportPublicKeyInfo(hCryptProv, keySpec, encodingType, 
          pKeyInfo, &size)) {
        *ppKeyInfo = pKeyInfo;
      } else {
        delete pKeyInfo;
        rc = GetLastError();
      }
      
    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  // 2009/03/15
  int importPublicKeyInfo(__in DWORD encodingType, 
        __in PCERT_PUBLIC_KEY_INFO pInfo,
        __out HCRYPTKEY *phKey) 
  {
    int rc = NO_ERROR;
    HCRYPTKEY hKey = NULL;
    if (CryptImportPublicKeyInfo(
      hCryptProv,
      encodingType,
      pInfo,
      &hKey)) {
      //OK
      *phKey = hKey;  
    } else {
      rc = GetLastError();
    }

    return rc;
  }


/*
BOOL WINAPI CryptSignAndEncodeCertificate(
  HCRYPTPROV hCryptProv,
  DWORD dwKeySpec,
  DWORD dwCertEncodingType,
  LPCSTR lpszStructType,
  const void *pvStructInfo,
  PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm,
  const void *pvHashAuxInfo,
  PBYTE pbEncoded,
  DWORD *pcbEncoded
);
*/

public:
  // 2009/03/17
  int signAndEncodeCertificate(
      __in PCERT_INFO certInfo,
      __in DWORD keySpec,
      __in DWORD encodingType,

      __out BYTE** encData,
      __out DWORD *encDataSize)
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    if (CryptSignAndEncodeCertificate(hCryptProv, 
        keySpec, 
        encodingType,    //X509_ASN_ENCODING, 
        (LPSTR)X509_CERT_TO_BE_SIGNED, 
        certInfo, 
        &(certInfo->SignatureAlgorithm), 
        NULL, 
        NULL, 
        &size)) {

      BYTE* data = new BYTE[size];
      if (CryptSignAndEncodeCertificate(hCryptProv, 
                keySpec, 
                encodingType,    //X509_ASN_ENCODING, 
                (LPSTR)X509_CERT_TO_BE_SIGNED, 
                certInfo, 
                &(certInfo->SignatureAlgorithm), 
                NULL, 
                data, 
                &size)) {

        *encData = data;
        *encDataSize = size;
      } else {

        delete [] data;
        rc = GetLastError();
      }
    } else {
      rc = GetLastError();
    }

    return rc;
  }

public:
  /**
   * @param hashAlg  A hash alogorithm (Ex. CALG_SHA1 CALG_MD5,...)
   * @param dwKeySpec A keyspec (AT_SIGNATURE or AT_KEYEXCHANGE)
   * @param ppHashData  A pointer to pointer to a hash byte array.
   * @param pHashDataSize A pointer to DWORD to return byte size of hash-data.
   */
  //2003/03/23
  int hashPublicKeyInfo(__in DWORD hashAlg, __in DWORD dwKeySpec, 
      __out BYTE** ppHashData, 
      __out DWORD* pHashDataSize)
  {
    int rc = NO_ERROR;
    DWORD dwSize = 0;
    DWORD encodingType = X509_ASN_ENCODING;

    if (!CryptExportPublicKeyInfo(hCryptProv, dwKeySpec, encodingType, NULL, &dwSize)) {
      return GetLastError();
    }
      
    PCERT_PUBLIC_KEY_INFO publicKeyInfo = (PCERT_PUBLIC_KEY_INFO)new BYTE[dwSize];
    if (!CryptExportPublicKeyInfo(hCryptProv, dwKeySpec, encodingType, publicKeyInfo, &dwSize)) {
      delete publicKeyInfo;
      return GetLastError(); 
    }

    dwSize = 0;
    if (!CryptHashPublicKeyInfo(hCryptProv, hashAlg, 0, encodingType, publicKeyInfo, NULL, &dwSize)) {
      delete publicKeyInfo;
      return GetLastError();     
    }

    BYTE* publicKeyHash =  new BYTE[dwSize];

    if (CryptHashPublicKeyInfo(hCryptProv, hashAlg, 0, encodingType, publicKeyInfo, publicKeyHash, &dwSize)) {
      *ppHashData = publicKeyHash;
      *pHashDataSize = dwSize;

    } else {
      delete [] publicKeyHash; 
      rc = GetLastError();
    }
    delete publicKeyInfo;
    return rc;
    
  }
};

}
