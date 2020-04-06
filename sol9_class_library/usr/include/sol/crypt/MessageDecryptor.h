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
 *  MessageDecryptor.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/24
#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>

/*
C++
typedef struct _CRYPT_DECRYPT_MESSAGE_PARA {
  DWORD      cbSize;
  DWORD      dwMsgAndCertEncodingType;
  DWORD      cCertStore;
  HCERTSTORE *rghCertStore;
  DWORD      dwFlags;  //Not support in Windows 2000
} CRYPT_DECRYPT_MESSAGE_PARA, *PCRYPT_DECRYPT_MESSAGE_PARA;Members
 */

namespace SOL {

class MessageDecryptor :public Object {

private:

  CRYPT_DECRYPT_MESSAGE_PARA  decryptMessagePara;

  DWORD encodingType;

  DWORD dwFlags;
public:
  /**
   * Constrcutor
   */
  MessageDecryptor(DWORD encType=(PKCS_7_ASN_ENCODING|X509_ASN_ENCODING),
      DWORD flags=CRYPT_MESSAGE_SILENT_KEYSET_FLAG)
  :encodingType(encType),
  dwFlags(flags)
  {
    memset(&decryptMessagePara, 0, sizeof(decryptMessagePara));
  }


public:
  /**
   *
   */
  int decrypt(
    __in HCERTSTORE hCertStore,

    __in Bytes& encryptedMessage,  //Encrypted message to be decrypted
    __out Bytes& decryptedMessage,  //Decrypted message
    __out_opt PCCERT_CONTEXT *ppXchgCert = NULL)
  {
    int rc = NO_ERROR;

    BYTE* decData = NULL;
    DWORD decDataSize = 0;
    if ((rc = decrypt(hCertStore, encryptedMessage.getData(), encryptedMessage.getSize(),
      &decData, &decDataSize)) == NO_ERROR) {
      decryptedMessage.shallowCopy(decData, decDataSize);
    } 
    return rc;
  }

public:
  /**
   *
   */
  int decrypt(
    __in HCERTSTORE hCertStore,

    __in const BYTE* encData,  //Ecrypted message to be decrypted
    __in DWORD  encDataSize,  //Byte size of encrypted message

    __out BYTE** ppDecData,   //Decrypted message
    __out DWORD* pDecDataSize,   //Byte siz of decrypted message 
    __out_opt PCCERT_CONTEXT *ppXchgCert = NULL)

  {
    int rc = NO_ERROR;

    memset(&decryptMessagePara, 0, sizeof(decryptMessagePara));
    decryptMessagePara.cbSize = sizeof(decryptMessagePara);
    decryptMessagePara.dwMsgAndCertEncodingType = this->encodingType;

     decryptMessagePara.cCertStore = 1;

    HCERTSTORE certStoreArray[1];
    certStoreArray[0] = hCertStore;
     decryptMessagePara.rghCertStore = certStoreArray;

    //decryptMessagePara.dwFlags = this->dwFlags;//CRYPT_MESSAGE_SILENT_KEYSET_FLAG 

    DWORD bufferSize = 0;
    if (!CryptDecryptMessage(
        &decryptMessagePara,
        encData,
        encDataSize,
        NULL,
        &bufferSize,
        ppXchgCert)) {

      return GetLastError();
    }

    BYTE* buffer = new BYTE [bufferSize];

    if (CryptDecryptMessage(
        &decryptMessagePara,
        encData,
        encDataSize,
        buffer,
        &bufferSize,
        ppXchgCert)) {
      //OK
      *ppDecData = buffer;
      *pDecDataSize = bufferSize;
    } else {
      delete [] buffer;
      rc = GetLastError();
    }
    return rc;

  }
};

}
