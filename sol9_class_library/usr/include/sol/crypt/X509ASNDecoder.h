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
 *  X509ASNDecoder.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/17
// 2009/03/25 Added a new method toString with a stringType CERT_SIMPLE_NAME_STR.

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>
//2009/03/17
#include <sol/String.h>


namespace SOL {


class X509ASNDecoder :public Object {

private:
  DWORD encodingType;

public:
  /**
   * Constructor
   */
  X509ASNDecoder(DWORD encoding = (X509_ASN_ENCODING|PKCS_7_ASN_ENCODING))
  :encodingType(encoding)
  {

  }
public:
  /**
   * Convert a binary X509 name to NULL-terminate string. 
   */
  int toString(
      __in Bytes& name,
      __in DWORD stringType,
      __out String& string) 
  {
      int rc = NO_ERROR;

      TCHAR* str = NULL;
      size_t strSize = 0;

      if ( (rc = toString(name.getData(), name.getSize(), 
          stringType,
          &str, &strSize)) == NO_ERROR) {
        //str is a NULL-terminated string.
        string.shallowCopy(str);
  
      }
      return rc;
  }

public:
  /**
   * Convert a binary X509 name to NULL-terminate string 
   * with a stringType CERT_SIMPLE_NAME_STR
   */
  //2009/03/25
  int toString(
      __in CERT_NAME_BLOB& certName,
      __out String& string) 
  {
      int rc = NO_ERROR;

      TCHAR* str = NULL;
      size_t strSize = 0;

      if ( (rc = toString(certName.pbData, certName.cbData, 
          CERT_SIMPLE_NAME_STR,
          &str, &strSize)) == NO_ERROR) {
        //str is a NULL-terminated string.
        string.shallowCopy(str);
    
      }
      return rc;
  }

public:
  /**
   * Convert PCERT_NAME_BLOB to NULL-terminated string.
   @param pName  A pointer to the CERT_NAME_BLOB structure to be converted.

   @param stringType This takes the following value
        CERT_SIMPLE_NAME_STR 
        CERT_OID_NAME_STR 
        CERT_X500_NAME_STR 

    This value can be combined the following value;
        CERT_NAME_STR_SEMICOLON_FLAG  
        CERT_NAME_STR_CRLF_FLAG 
        CERT_NAME_STR_NO_PLUS_FLAG 
        CERT_NAME_STR_NO_QUOTING_FLAG 
        CERT_NAME_STR_REVERSE_FLAG 
        CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG 
        CERT_NAME_STR_ENABLE_PUNYCODE_FLAG 
  */
  int toString(
      __in const BYTE* data,
      __in size_t dataSize,
      __in DWORD stringType,

      __inout TCHAR** string,
      __in   size_t* stringSize)
  {
    int rc = NO_ERROR;

    CERT_NAME_BLOB name;
    name.pbData = (BYTE*)data;
    name.cbData = dataSize;

    /*
    The CertNameToStr converts an encoded name in a CERT_NAME_BLOB structure 
    to a NULL-terminated character string.
    */
    /*
    typedef struct _CRYPTOAPI_BLOB {
      DWORD    cbData;
      BYTE*    pbData;
    }  CERT_NAME_BLOB,     
    */
    
    //This returns the number of characters converted, including the terminating NULL character. 
    //If psz is NULL or csz is zero, returns the required size of the destination string. 

    DWORD size = CertNameToStr(this->encodingType,
        &name,
        stringType,
        NULL,
        0);
    if (size>0) {
      //
      TCHAR* buffer = new TCHAR[size];
      if (CertNameToStr(this->encodingType,
          &name,
          stringType,
          buffer,
          size)>0) {
        //OK
        *string = buffer;
        *stringSize = size;
      } else {
        delete [] buffer;
        rc = GetLastError();
      }

    } else {      //Failed
      rc = GetLastError();
    }
    return rc;
  }  

public:
  /**
   *
   */
  //2009/03/15
  int decode(
      __in LPCSTR szStructType,
      __in const BYTE* data, 
      __in size_t dataSize,
      __out void** ppStructInfo,
      __out size_t* structInfoSize)
  
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    if (CryptDecodeObject(this->encodingType, 
        szStructType, 
        data, 
        dataSize, 
        0, 
        NULL, &size)) {

      //
      
      BYTE* decData= new BYTE[size];
  
      if (CryptDecodeObject(this->encodingType, 
          szStructType, 
          data, 
          dataSize, 
          0, 
          decData, &size)) {

        //OK
        *ppStructInfo = decData;
        *structInfoSize = size; 
      } else {
        delete [] decData;
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
  //2009/03/15
  int decodeX509Name(
      __in const BYTE* data, 
      __in size_t dataSize,
      __out PCERT_NAME_INFO*  ppNameInfo)
  
  {
    int rc = NO_ERROR;

    DWORD size = 0;
    if (CryptDecodeObject(this->encodingType, 
      X509_NAME, 
      data, 
      dataSize, 
      0, 
      NULL, &size)) {

      //
      PCERT_NAME_INFO pNameInfo = (PCERT_NAME_INFO)new BYTE[size];
  
      if (CryptDecodeObject(this->encodingType, 
        X509_NAME, 
        data, 
        dataSize, 
        0, 
        pNameInfo, &size)) {

        //OK
        *ppNameInfo = pNameInfo;
      } else {
        delete [] pNameInfo;
        rc = GetLastError();
      }
    } else {
      rc = GetLastError();
    }
    return rc;
  }
};


}
