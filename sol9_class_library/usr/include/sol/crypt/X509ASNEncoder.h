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
 *  X509ASNEncoder.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/17

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>


namespace SOL {

class X509ASNEncoder :public Object {

private:
  DWORD encodingType;

public:
  /**
   * Constructor
   */
  X509ASNEncoder(DWORD encoding = (X509_ASN_ENCODING|PKCS_7_ASN_ENCODING))
  :encodingType(encoding)
  {

  }

public:
  int toName(__in const TCHAR* string, 
      __in DWORD stringType, 
      __out Bytes& name)
  {
    int rc = NO_ERROR;
    unsigned char* buffer = NULL;
    size_t size = 0;
    if ((rc = toName(string, stringType, &buffer, &size))== NO_ERROR) {
      name.shallowCopy(buffer, size);  
    }
    return rc;  
  }


public:
  /**
   * @param string A pointer to the NULL-terminated X.500 string to be converted. 
     @param stringType This takes the following value:
        CERT_SIMPLE_NAME_STR
        CERT_OID_NAME_STR 
        CERT_X500_NAME_STR
      The following options can also be combined with the value above.
        CERT_NAME_STR_COMMA_FLAG
        CERT_NAME_STR_SEMICOLON_FLAG
        CERT_NAME_STR_CRLF_FLAG
        CERT_NAME_STR_NO_PLUS_FLAG
        CERT_NAME_STR_NO_QUOTING_FLAG
        CERT_NAME_STR_DISABLE_IE4_UTF8_FLAG
        CERT_NAME_STR_REVERSE_FLAG
        CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG
        CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG
        CERT_NAME_STR_ENABLE_PUNYCODE_FLAG

   */
  int toName(
      __in const TCHAR* string, 
      __in DWORD stringType,
      __out unsigned char** encodedBytes, 
      __out size_t* encodedBytesSize)
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    /*
    The CertStrToName converts a NULL-terminated X.500 string 
    to an encoded certificate name.
    */

    if (CertStrToName(this->encodingType,
          string,
          stringType,
        NULL,
         NULL,
        &size,
        NULL)) {

      unsigned char* buffer = new unsigned char[size];
      
      if (CertStrToName(this->encodingType,
            string,
            stringType,
          NULL,
           buffer,
          &size,
          NULL)) {
        //OK
        *encodedBytes = buffer;
        *encodedBytesSize = size;
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
  /**
   *
   */
  // 2009/03/17
  int encode(__in LPCSTR szStructType,
    __in     const void *pvStructInfo,
    __out    BYTE **encodedData,
    __out  size_t *encodedDataSize) 
  {
    int rc = NO_ERROR;
    DWORD size = 0;

    if (CryptEncodeObject(this->encodingType, 
        szStructType, 
        pvStructInfo, 
        NULL, &size)) {

      BYTE* data = new BYTE[size];

      if (CryptEncodeObject(this->encodingType, 
          szStructType, 
          pvStructInfo, 
          data, &size)) {
        //OK
        *encodedData = data;
        *encodedDataSize = size;
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
   *
   */
  //2009/03/17
  int encodeX509Name(
      __in PCERT_NAME_INFO pNameInfo,
      __out BYTE** encodedData, 
      __out size_t* encodedDataSize)
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    if (CryptEncodeObject(this->encodingType, 
      X509_NAME, 
      pNameInfo, 
      NULL, &size)) {

      BYTE* data = new BYTE[size];
      if (CryptEncodeObject(this->encodingType, 
        X509_NAME, 
        pNameInfo, 
        data, &size)) {

        //OK
        *encodedData = data;
        *encodedDataSize = size;
      } else {
        delete [] data;
        rc = GetLastError();
      }
    } else {
      rc = GetLastError();
    }
    return rc;
  }

};

}

