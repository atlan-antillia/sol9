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
// 2009/04/02
// 2009/04/06 Added a getSerialNumber(String&) method.
// 2009/04/06 Added getNotBefore(String&) and getNotAfter(String&) methods.


#pragma once

#include <sol/Object.h>
#include <wincrypt.h>
#include <sol/crypt/X509ASNDecoder.h>


namespace SOL {

class CertInfo :public Object {

private:
  PCERT_INFO pCertInfo;


public:
  CertInfo(PCERT_INFO pInfo=NULL)
  :pCertInfo(pInfo)
  {

  }

public:
  ~CertInfo() 
  {
    //Don't delete pCertInfo
  }

public:
  void set(PCERT_INFO pInfo)
  {
    pCertInfo = pInfo;
  }

public:
  int getVersion(DWORD& version) 
  {
    int rc = -1;
    if (pCertInfo) {
      version = pCertInfo->dwVersion;
      rc = NO_ERROR;
    } 
    return rc;
  }

public:

  int getSerialNumber(Bytes& serialNumber) 
  {
    int rc = -1;
    if (pCertInfo) {
      serialNumber.set(pCertInfo->SerialNumber.pbData, 
              pCertInfo->SerialNumber.cbData);
      rc = NO_ERROR;
    } 
    return rc;
  }


public:
  //2009/04/06
  int getSerialNumber(String& serialNumber)
  {
    int rc = -1;

    if (pCertInfo) {
      size_t dwData = pCertInfo->SerialNumber.cbData;
      size_t bsize = dwData*2 + 1;
      char* buffer = new char[bsize];
      memset(buffer, 0, bsize);
      for (size_t n = 0; n<dwData; n++) {
        //sprintf(&buffer[n*2], "%02x", pCertInfo->SerialNumber.pbData[dwData - (n + 1)]);
        sprintf_s(&buffer[n*2], bsize - n*2, "%02x", pCertInfo->SerialNumber.pbData[dwData - (n + 1)]);
      }
      serialNumber =buffer;
      delete [] buffer;
      rc = NO_ERROR;

    }
    return rc;
  }


public:
  int getSignatureAlgorithm(String& algorithm, Bytes& params)
  {
    int rc = -1;
    if (pCertInfo) {
      algorithm = pCertInfo->SignatureAlgorithm.pszObjId;
      // 2011/09/05 Check that Parameter-data-size is greater than 0.     
      if (pCertInfo->SignatureAlgorithm.Parameters.cbData>0) {
        params.set(pCertInfo->SignatureAlgorithm.Parameters.pbData,
          pCertInfo->SignatureAlgorithm.Parameters.cbData);
      }

      rc = NO_ERROR;
    }
    return rc;
  }

public:
  int getIssuer(String& issuer) 
  {
    int rc = -1;
    X509ASNDecoder decoder;
    if (pCertInfo && (decoder.toString(pCertInfo->Issuer, issuer) ==NO_ERROR)) {
      rc = NO_ERROR;
    }
    return rc;
  }

public:
  int getNotBefore(SYSTEMTIME& st) 
  {
    int rc = -1;
    if (pCertInfo) {
      FILETIME lt;
      FileTimeToLocalFileTime(&(pCertInfo->NotBefore), &lt);
      FileTimeToSystemTime(&lt, &st);
      rc = NO_ERROR;
    }
    return rc;
  }
public:
  //2009/04/06
  int getNotBefore(String& string) 
  {
    int rc = NO_ERROR;

    SYSTEMTIME notBefore;
    getNotBefore(notBefore); 
    char dateTime[128];
  
    sprintf_s(dateTime, CountOf(dateTime), "%04d/%02d/%02d %02d:%02d\n",
                                            notBefore.wYear,
                                            notBefore.wMonth,
                                            notBefore.wDay,
                                            notBefore.wHour,
                                            notBefore.wMinute);
    string = dateTime;
    return rc;
  }

public:
  int getNotAfter(SYSTEMTIME& st) 
  {
    int rc = -1;
    if (pCertInfo) {
      FILETIME lt;
      FileTimeToLocalFileTime(&(pCertInfo->NotAfter), &lt);
      FileTimeToSystemTime(&lt, &st);
      rc = NO_ERROR;
    }
    return rc;
  }

public:
  //2009/04/06
  int getNotAfter(String& string) 
  {
    int rc = NO_ERROR;

    SYSTEMTIME notAfter;
    getNotAfter(notAfter); 
    char dateTime[128];
  
    sprintf_s(dateTime, CountOf(dateTime), "%04d/%02d/%02d %02d:%02d\n",
                                            notAfter.wYear,
                                            notAfter.wMonth,
                                            notAfter.wDay,
                                            notAfter.wHour,
                                            notAfter.wMinute);
    string = dateTime;
    return rc;
  }


public:
  int getSubject(String& subject) 
  {
    int rc = -1;
    X509ASNDecoder decoder;
    if (pCertInfo && (decoder.toString(pCertInfo->Subject, subject) ==NO_ERROR)) {
      rc = NO_ERROR;
    }
    return rc;
  }

public:

  int getPublicKeyInfo(Bytes& keyInfo, String& keyAlgorithm, DWORD& keySize, DWORD& unusedBits ) 
  {
    int rc = -1;
    if (pCertInfo) {
      keyInfo.set(pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData, 
              pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData);
      keyAlgorithm = pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId;

      keySize = pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData;

      unusedBits = pCertInfo->SubjectPublicKeyInfo.PublicKey.cUnusedBits;

      rc = NO_ERROR;
    } 
    return rc;
  }

public:

  int getIssuerUniqueId(Bytes& uniqueId) 
  {
    int rc = -1;
    if (pCertInfo) {
      if (pCertInfo->IssuerUniqueId.pbData) {
        uniqueId.set(pCertInfo->IssuerUniqueId.pbData, 
              pCertInfo->IssuerUniqueId.cbData);
        rc = NO_ERROR;
      }
    } 
    return rc;
  }

public:

  int getSubjectUniqueId(Bytes& uniqueId) 
  {
    int rc = -1;
    if (pCertInfo) {
      if (pCertInfo->SubjectUniqueId.pbData) {

        uniqueId.set(pCertInfo->SubjectUniqueId.pbData, 
              pCertInfo->SubjectUniqueId.cbData);
        rc = NO_ERROR;
      }
    } 
    return rc;
  }

public:
  int getExtension(DWORD& count, PCERT_EXTENSION* ppCertExtension)
  {
    int rc = -1;
    if (pCertInfo) {
      count = pCertInfo->cExtension;
      *ppCertExtension = pCertInfo->rgExtension;
      rc = NO_ERROR;
    }
    return rc;
  }

public:
  // return 0:valid, -1:not valid yet, 1:expired
  int verifyTimeValidity(__in_opt LPFILETIME pTime=NULL) 
  {
    int rc = -1;
    if (pCertInfo) {
      rc = (int)CertVerifyTimeValidity(
          pTime,
          this->pCertInfo);
    }
    return rc;
  }


public:
  void dump()
  {
    //Version
    DWORD version;
    getVersion(version);
     _tprintf(_T("Version:%d\n"), version);
    /*
    */
    //2009/04/06
    String serialNumber;
    getSerialNumber(serialNumber);
    _tprintf(_T("SerialNumber: %s\n"), (const TCHAR*)serialNumber);

    String algorithm;
    Bytes  params;
    getSignatureAlgorithm(algorithm, params);
    _tprintf(_T("SignatureAlgorithm: %s\n"), (const TCHAR*)algorithm);

    String issuer;
    getIssuer(issuer);
    _tprintf(_T("Issuer: %s\n"), (const TCHAR*)issuer);

    SYSTEMTIME notBefore;
    getNotBefore(notBefore); 
    _tprintf(_T("NotBefore: %04d/%02d/%02d %02d:%02d\n"),
                                            notBefore.wYear,
                                            notBefore.wMonth,
                                            notBefore.wDay,
                                            notBefore.wHour,
                                            notBefore.wMinute);


    SYSTEMTIME notAfter;
    getNotAfter(notAfter);
    _tprintf(_T("NotAfter: %04d/%02d/%02d %02d:%02d\n"),
                                            notAfter.wYear,
                                            notAfter.wMonth,
                                            notAfter.wDay,
                                            notAfter.wHour,
                                            notAfter.wMinute);
    
    String subject;
    getSubject(subject);
    _tprintf(_T("Subject: %s\n"), (const TCHAR*)subject);

    Bytes keyInfo;
    String keyAlgorithm;
    DWORD keySize;
    DWORD unusedBits;
    getPublicKeyInfo(keyInfo, keyAlgorithm, keySize, unusedBits);
    _tprintf(_T("PublicKeyInfo: Algorithm=%s keySize=%d unusedBits=%d\n"),
      (const TCHAR*)keyAlgorithm, keySize, unusedBits);

    Bytes issuerUniqueId;
    getIssuerUniqueId(issuerUniqueId); 
    _tprintf(_T("IssuerUniqueId: "));
    issuerUniqueId.dump();

    Bytes subjectUniqueId;
    getSubjectUniqueId(subjectUniqueId);
    _tprintf(_T("SubjectUniqueId: "));
    subjectUniqueId.dump();

    DWORD exCount = 0;
    PCERT_EXTENSION pCertExtension;

    getExtension(exCount, &pCertExtension);
    _tprintf(_T("Extension count=%d\n"), exCount);
  }

};

}
