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
 *  CryptObject.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/15

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>


namespace SOL {

class CryptObject :public Object {

private:
  HCERTSTORE hStore;
  HCRYPTMSG hMsg; 

  DWORD dwEncoding;
  DWORD dwContentType;
  DWORD dwFormatType;

public:
  /**
   * Constructor
   */
  CryptObject()
  :hStore(NULL),
   hMsg(NULL) 
  {

  }

public:
  /**
   *
   * @param fileName A pointer to a NULL-terminated Unicode string that contains 
   *          the path and name of the file to query.

   * Open a signed file of fileName and get handles of HCERTSTORE and HCRYPTMSG.
   *
    @param expectedContentTypeFlags Indicates the expected content type. 
        CERT_QUERY_CONTENT_FLAG_ALL 
        CERT_QUERY_CONTENT_FLAG_CERT 
        CERT_QUERY_CONTENT_FLAG_CERT_PAIR
        CERT_QUERY_CONTENT_FLAG_CRL
        CERT_QUERY_CONTENT_FLAG_CTL
        CERT_QUERY_CONTENT_FLAG_PFX
        CERT_QUERY_CONTENT_FLAG_PFX_AND_LOAD
        CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED
        CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED
        CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED
        CERT_QUERY_CONTENT_FLAG_PKCS10
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE
 
    @param expectedFormatTypeFlags Indicates the expected format of the returned type.
        CERT_QUERY_FORMAT_FLAG_ALL 
        CERT_QUERY_FORMAT_FLAG_ASN_ASCII_HEX_ENCODED
        CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED 
        CERT_QUERY_FORMAT_FLAG_BINARY
 
   */
  int query(__in const CERT_BLOB* blob, 
      __in DWORD expectedContentType=CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
      __in DWORD expectedFormatType=CERT_QUERY_FORMAT_FLAG_BINARY) 
  {

    int rc = NO_ERROR;
    /*
      BOOL WINAPI CryptQueryObject(
        __in   DWORD dwObjectType,
        __in   const void *pvObject,
        __in   DWORD dwExpectedContentTypeFlags,
        __in   DWORD dwExpectedFormatTypeFlags,
        __in   DWORD dwFlags,
       __out  DWORD *pdwMsgAndCertEncodingType,
       __out  DWORD *pdwContentType,
       __out  DWORD *pdwFormatType,
       __out  HCERTSTORE *phCertStore,
      __out  HCRYPTMSG *phMsg,
      __out  const void **ppvContext
    );

    */
    if (CryptQueryObject(CERT_QUERY_OBJECT_BLOB,
                                   blob,
                                   expectedContentType,  //CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
                                   expectedFormatType,    //CERT_QUERY_FORMAT_FLAG_BINARY,
                                   0,
                                   &dwEncoding,
                                   &dwContentType,
                                   &dwFormatType,

                                   &hStore,
                                   &hMsg,
                                   NULL) != TRUE) {
      return GetLastError();
    }

    return rc;
  } 


  public:
  /**
   *
   * @param fileName A pointer to a NULL-terminated Unicode string that contains 
   *          the path and name of the file to query.

   * Open a signed file of fileName and get handles of HCERTSTORE and HCRYPTMSG.
   *
    @param expectedContentTypeFlags Indicates the expected content type. 
        CERT_QUERY_CONTENT_FLAG_ALL 
        CERT_QUERY_CONTENT_FLAG_CERT 
        CERT_QUERY_CONTENT_FLAG_CERT_PAIR
        CERT_QUERY_CONTENT_FLAG_CRL
        CERT_QUERY_CONTENT_FLAG_CTL
        CERT_QUERY_CONTENT_FLAG_PFX
        CERT_QUERY_CONTENT_FLAG_PFX_AND_LOAD
        CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED
        CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED
        CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED
        CERT_QUERY_CONTENT_FLAG_PKCS10
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL
        CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE
 
    @param expectedFormatTypeFlags Indicates the expected format of the returned type.
        CERT_QUERY_FORMAT_FLAG_ALL 
        CERT_QUERY_FORMAT_FLAG_ASN_ASCII_HEX_ENCODED
        CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED 
        CERT_QUERY_FORMAT_FLAG_BINARY
 
   */
  int query(__in const wchar_t* fileName, 
      __in DWORD expectedContentType=CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
      __in DWORD expectedFormatType=CERT_QUERY_FORMAT_FLAG_BINARY) 
  {

    int rc = NO_ERROR;
    /*
      BOOL WINAPI CryptQueryObject(
        __in   DWORD dwObjectType,
        __in   const void *pvObject,
        __in   DWORD dwExpectedContentTypeFlags,
        __in   DWORD dwExpectedFormatTypeFlags,
        __in   DWORD dwFlags,
       __out  DWORD *pdwMsgAndCertEncodingType,
       __out  DWORD *pdwContentType,
       __out  DWORD *pdwFormatType,
       __out  HCERTSTORE *phCertStore,
      __out  HCRYPTMSG *phMsg,
      __out  const void **ppvContext
    );

    */
    if (CryptQueryObject(CERT_QUERY_OBJECT_FILE,
                                   fileName,
                                   expectedContentType,  //CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
                                   expectedFormatType,    //CERT_QUERY_FORMAT_FLAG_BINARY,
                                   0,
                                   &dwEncoding,
                                   &dwContentType,
                                   &dwFormatType,

                                   &hStore,
                                   &hMsg,
                                   NULL) != TRUE) {
      return GetLastError();
    }

    return rc;
  } 

public:
  ~CryptObject()
  {
  }


public:
  HCERTSTORE getCertStore() {
    return hStore; 
  }

public:
  HCRYPTMSG getCryptMsg() {
    return hMsg; 
  }

};


}
