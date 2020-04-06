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
 *  CertStore.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/10
// 2009/03/15 Added new method findCert.
// 2009/03/16 Added new method addCertContext and addEncodedCerticate.
// 2009/03/24 Added a new method getRecipientCert.

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>
#include <sol/crypt/CryptServiceProvider.h>


namespace SOL {

class CertStore :public Object {

private:
  HCERTSTORE hCertStore;


public:
  /**
   * Constructor
   */
  CertStore()
  :hCertStore(NULL) {
    //
  }

public:
  /**
   * Destructor
   */
  ~CertStore() {
    if (hCertStore) {
      CertCloseStore(hCertStore, 0);
      hCertStore = NULL;
    }
  }

public:
  int open(CryptServiceProvider& csp, const TCHAR* subSystem) {

    return open(csp.getProviderHandle(), subSystem);
  }


public:
  int open(HCRYPTPROV hCryptProv, const TCHAR* subSystem) {

    int rc = NO_ERROR;
    this->hCertStore = CertOpenSystemStore(
        hCryptProv, 
        subSystem);
    if (this->hCertStore==NULL) {
      throw Exception(GetLastError(), "CertStore#open,1,Failed");
    }
    return rc;
  }
/*
HCERTSTORE WINAPI CertOpenSystemStore(
  HCRYPTPROV hProv,
  LPCTSTR szSubsystemProtocol
);
*/

public:
  int open(CryptServiceProvider& csp, 
      const char* storeProvider, 
      DWORD encodingType, 
      DWORD flags, 
      const void *pvPara) {

      return open(csp.getProviderHandle(), storeProvider, encodingType, flags, pvPara);
  }


public:

  /**
    storeProvider:
      CERT_STORE_PROV_MSG
      CERT_STORE_PROV_MEMORY
      CERT_STORE_PROV_FILE
      CERT_STORE_PROV_REG
      CERT_STORE_PROV_PKCS7
      CERT_STORE_PROV_SERIALIZED
      CERT_STORE_PROV_FILENAME
      CERT_STORE_PROV_SYSTEM
      CERT_STORE_PROV_COLLECTION
      CERT_STORE_PROV_SYSTEM_REGISTRY
      CERT_STORE_PROV_PHYSICAL

    encodingType

    flags:  

      CERT_STORE_NO_CRYPT_RELEASE_FLAG
      CERT_STORE_SET_LOCALIZED_NAME_FLAG
      CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG
      CERT_STORE_DELETE_FLAG
      CERT_STORE_UNSAFE_PHYSICAL_FLAG
      CERT_STORE_SHARE_STORE_FLAG
      CERT_STORE_SHARE_CONTEXT_FLAG
      CERT_STORE_MANIFOLD_FLAG
      CERT_STORE_ENUM_ARCHIVED_FLAG
      CERT_STORE_UPDATE_KEYID_FLAG
      CERT_STORE_BACKUP_RESTORE_FLAG
      CERT_STORE_READONLY_FLAG
      CERT_STORE_OPEN_EXISTING_FLAG
      CERT_STORE_CREATE_NEW_FLAG
      CERT_STORE_MAXIMUM_ALLOWED_FLAG
      ...
  */
  int open(HCRYPTPROV hCryptProv, 
      const char* storeProvider, 
      DWORD encodingType, 
      DWORD flags, 
      const void *pvPara) {

    int rc = NO_ERROR;
    
    this->hCertStore = CertOpenStore(
        storeProvider,
        encodingType,
        hCryptProv,
        flags,
        pvPara);
    if (this->hCertStore == NULL) {
      throw Exception(GetLastError(), "CertStore#open,1,Failed");
    }
    return rc;
  }


public:
  HCERTSTORE getStoreHandle() {
    return hCertStore;
  }

public:
  void setStoreHandle(HCERTSTORE hStore) {
    hCertStore = hStore;
  }



public:

  PCCERT_CONTEXT enumCertificate(PCCERT_CONTEXT pPrevCertContext)
  {
    return CertEnumCertificatesInStore(hCertStore, pPrevCertContext);
  }

public:
  /**
   */
  void enumCertificates() {
    PCCERT_CONTEXT pContext = NULL;
    TCHAR          buffer[256];

    while((pContext = enumCertificate(pContext)) !=NULL) {
    
      CertGetNameString(pContext, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, 
        buffer, CountOf(buffer));

      _tprintf(_T("CertName:%s\n"), buffer);
    }
  }

 
public:
  //
  PCCERT_CONTEXT findAny(DWORD certEncodingType, 
    DWORD findFlags, 
    PCCERT_CONTEXT prevContext=NULL) {

    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_ANY, 
      NULL, 
      prevContext);
  }

public:
  //
  PCCERT_CONTEXT findCertId(DWORD certEncodingType, 
    DWORD findFlags, 
    CERT_ID* certId, 
    PCCERT_CONTEXT prevContext=NULL) {


    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_CERT_ID, 
      certId, 
      prevContext);
  }

public:
  //
  PCCERT_CONTEXT findEnhKeyUsage(DWORD certEncodingType, 
    DWORD findFlags, 
    CERT_ENHKEY_USAGE* usage, 
    PCCERT_CONTEXT prevContext=NULL) {

    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_ENHKEY_USAGE, 
      usage, 
      prevContext);
  }
public:
  //
  PCCERT_CONTEXT findExisting(DWORD certEncodingType, 
    DWORD findFlags, 
    CERT_CONTEXT* context, 
    PCCERT_CONTEXT prevContext=NULL) {

    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_EXISTING, 
      context, 
      prevContext);
  }

public:
  //
  PCCERT_CONTEXT findIssuer(DWORD certEncodingType, 
    DWORD findFlags, 
    const wchar_t* issuer, 
    PCCERT_CONTEXT prevContext=NULL) {

    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_ISSUER_STR, 
      issuer, 
      prevContext);
  }

public:
  //
  PCCERT_CONTEXT findSubject(DWORD certEncodingType, 
    DWORD findFlags, 
    const wchar_t* subject, 
    PCCERT_CONTEXT prevContext=NULL) {

    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_SUBJECT_STR, 
      subject, 
      prevContext);

  }


public:   
  /**
   * Find a certificate from signer's issuer and seril number.
   */
  //2009/03/15
  PCCERT_CONTEXT findCert(DWORD certEncodingType, 
    DWORD findFlags, 
    PCMSG_SIGNER_INFO pSignerInfo,
    PCCERT_CONTEXT prevContext=NULL)  {

    CERT_INFO certInfo;  
    memset(&certInfo, 0, sizeof(certInfo));

    certInfo.Issuer = pSignerInfo->Issuer;
        certInfo.SerialNumber = pSignerInfo->SerialNumber;


    return CertFindCertificateInStore(
      this->hCertStore, 
      certEncodingType, 
      findFlags, 
      CERT_FIND_SUBJECT_CERT, 
      &certInfo, 
      prevContext);

  }

public:
  // 2009/03/16
  int addCertContext(
      __in PCCERT_CONTEXT pContext,
      __in DWORD addDisposition = CERT_STORE_ADD_REPLACE_EXISTING,
      __out PCCERT_CONTEXT *ppCertContext=NULL) 
  {
    int rc = NO_ERROR;

    if (!CertAddCertificateContextToStore(
        this->hCertStore, 
        pContext, 
        addDisposition, 
        ppCertContext)) {
      //Failed
      rc = GetLastError();  
    }
    return rc;
  }

public:
  // 2009/03/16
  int addEncodedCertificate(
      __in DWORD encodingType, 
      __in const BYTE *encodedCert, 
      __in DWORD encodedCertSize, 
      __in DWORD addDisposition = CERT_STORE_ADD_REPLACE_EXISTING, 
      __out PCCERT_CONTEXT *ppCertContext=NULL)
  {
    int rc = NO_ERROR;
    if (!CertAddEncodedCertificateToStore(
        this->hCertStore, 
        encodingType, 
        encodedCert, 
        encodedCertSize, 
        addDisposition, 
        ppCertContext)) {
      //Failed
      rc = GetLastError();
    }
    return rc;
  }

public:
  int exportPFX(
    __in PCCERT_CONTEXT  pContext, 
    __in const TCHAR* pfxFileName, 
    __in const wchar_t* password,
    __in_opt DWORD flags = EXPORT_PRIVATE_KEYS)
  {
    int rc = NO_ERROR;

    HCERTSTORE hMemoryStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 
      0, NULL,
       0, NULL);
    if (hMemoryStore == NULL) {
      return GetLastError();
    }

    if (!CertAddCertificateContextToStore(hMemoryStore, pContext,
       CERT_STORE_ADD_ALWAYS, NULL)) {
      printf("Failed to addCertificateContextToStore hMemoryStore\n");
      CertCloseStore(hMemoryStore, CERT_CLOSE_STORE_CHECK_FLAG);
      return GetLastError();
    }

    CRYPT_DATA_BLOB data;
    memset(&data, 0, sizeof(data));

    data.pbData = NULL;
    if (!PFXExportCertStoreEx(hMemoryStore, &data, password, NULL, flags)) {
      printf("1 Failed to PFXExportCertStoreEx:%x\n", GetLastError());
      CertCloseStore(hMemoryStore, CERT_CLOSE_STORE_CHECK_FLAG);
      return GetLastError();
    }

    data.pbData = (LPBYTE)CryptMemAlloc(data.cbData);
    if (!PFXExportCertStoreEx(hMemoryStore, &data, password, NULL, flags)){
      printf("2 Failed to PFXExportCertStoreEx:%x\n", GetLastError());

      CryptMemFree(data.pbData);
      CertCloseStore(hMemoryStore, CERT_CLOSE_STORE_CHECK_FLAG);
      return GetLastError();
    }  

    HANDLE hFile = CreateFile(pfxFileName, 
      GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
      DWORD writtenBytes = 0;
      if (WriteFile(hFile, data.pbData, data.cbData, &writtenBytes, NULL)) {
        printf("3 Written to a pfx file\n");
        //OK
      } else {
        rc = GetLastError();
      }
      CloseHandle(hFile);
    } else {
      _tprintf(_T("4 Failed to open a file %s\n"), pfxFileName);
      rc = GetLastError();
    }

    CryptMemFree(data.pbData);
    CertCloseStore(hMemoryStore, CERT_CLOSE_STORE_CHECK_FLAG);

    return rc;
  }

public:
  /**
   * Import a pfx file.
   * @param pfxFileName  A pfx file name.
   * @param password    A password string
   */
  // 2009/03/17
  int importPFX(
      __in const TCHAR* pfxFileName, 
      __in const wchar_t* password,
      __in_opt DWORD flags = (CRYPT_EXPORTABLE|CRYPT_USER_PROTECTED))
  {
    int rc = NO_ERROR;
    CRYPT_DATA_BLOB data;
    memset(&data, 0, sizeof(data));

    HANDLE hFile = CreateFile(pfxFileName, 
      GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {

      data.cbData = GetFileSize(hFile, NULL);
      data.pbData = (LPBYTE)CryptMemAlloc(data.cbData);
      DWORD readBytes = 0;
      if (ReadFile(hFile, data.pbData, data.cbData, &readBytes, NULL)) {

        CloseHandle(hFile);
        return GetLastError();
      }
      CloseHandle(hFile);

      if (!PFXIsPFXBlob(&data)) {
        CryptMemFree(data.pbData);
        return GetLastError();
      }

      if (!PFXVerifyPassword(&data, password, 0)) {
        CryptMemFree(data.pbData);
        return GetLastError();
      }
    }
  
    //Import a pfx file and create a temporaray memory-based certstore
    HCERTSTORE  hMemoryStore = PFXImportCertStore(&data, 
      password, flags);
    if (hMemoryStore != NULL) {
      PCCERT_CONTEXT  pContext = NULL;

      while ((pContext = CertEnumCertificatesInStore(hMemoryStore, pContext)) !=NULL  ) {
        CertAddCertificateContextToStore(this->hCertStore, pContext, CERT_STORE_ADD_ALWAYS, NULL);
      }
      CertCloseStore(hMemoryStore, 0);
    }
    else {
      rc = GetLastError();
      //printf("Failed to importPFX");
    }
    if (data.pbData) {
      CryptMemFree(data.pbData);
    }
    return rc;
  }

public:
  // 2009/03/24
  PCCERT_CONTEXT getRecipientCert()
  { 
    PCCERT_CONTEXT pRecipientCert = NULL; 

    PCCERT_CONTEXT pContext = NULL; 

    CRYPT_KEY_PROV_INFO* pKeyInfo = NULL; 

    DWORD propId = CERT_KEY_PROV_INFO_PROP_ID; 

    while((pContext= CertFindCertificateInStore( 
        hCertStore,  
        0, 
           0, 
           CERT_FIND_PROPERTY, 
           &propId, 
           pContext)) !=NULL) { 

      DWORD dwSize = 0;

      if (!(CertGetCertificateContextProperty( 
        pContext, 
        propId,  
        NULL, &dwSize))) { 
    
        break;
      } 

      if(pKeyInfo) {
        delete pKeyInfo;
      } 
      pKeyInfo = (CRYPT_KEY_PROV_INFO*)new BYTE[dwSize];
      

      if(!(CertGetCertificateContextProperty( 
        pContext, 
        propId,
        pKeyInfo, 
        &dwSize))) { 

        break;
      } 

      //Found a certiciate of keyexchange 
      if(pKeyInfo->dwKeySpec == AT_KEYEXCHANGE) { 
        pRecipientCert = pContext;
        //printf("Found a key of KeyExhange\n");
          break; 
      } 
    } 

    if(pKeyInfo) {
      delete pKeyInfo;
    } 
    return pRecipientCert; 
  } 


};

}
