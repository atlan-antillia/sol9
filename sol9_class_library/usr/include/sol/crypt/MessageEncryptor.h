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
 *  MessageEncryptor.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/24
#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>

namespace SOL {

class MessageEncryptor :public Object {

private:

  //CRYPT_ENCRYPT_MESSAGE_PARA  encryptMessagePara;
  CRYPT_ENCRYPT_MESSAGE_PARA encryptMessagePara;

  DWORD encodingType;
   const char* encAlgorithm;

public:
  /**
   * Constrcutor
   * @param encType    Default encodingType(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING).
   * @param objId      Default encoding algorithm (szOID_RSA_RC4)
   */
  MessageEncryptor(DWORD encType=(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING),
    const char* objId=szOID_RSA_RC4)
  :encodingType(encType),
  encAlgorithm(objId)
  {
    memset(&encryptMessagePara, 0, sizeof(encryptMessagePara));
  }


public:
  /**
   * Encrypt a message parameter by using a pCert certificate passed 
   * by parameter by encAlgorihthm of this class,
   * and return an encrypted message to a parameter encrypteMessage
   */
  int encrypt(
    __in HCRYPTPROV hProv,
    __in PCCERT_CONTEXT pRecipCert, 

    __in Bytes& message,    //Message to be encrypted
    __out Bytes& encryptedMessage)  //Encrypted message
  {
    int rc = NO_ERROR;

    BYTE* encData = NULL;
    DWORD encDataSize = 0;
    if ((rc = encrypt(hProv, pRecipCert, message.getData(), message.getSize(),
      &encData, &encDataSize)) == NO_ERROR) {
      encryptedMessage.shallowCopy(encData, encDataSize);
    } 
    return rc;
  }

public:
  /**
   * Encrypt a data by a certifiate pCert and return a encData
   */
  int encrypt(
    __in HCRYPTPROV hProv,
    __in PCCERT_CONTEXT pRecipCert, 

    __in const BYTE* data,    //Message to be encrypted
    __in DWORD  dataSize,    //Byte size of the message

    __out BYTE** ppEncData,   //Encrypted message
    __out DWORD* pEncDataSize)   //Byte siz of encrypted message 
  {
    int rc = NO_ERROR;

    PCCERT_CONTEXT  recipients[1];
    recipients[0] = pRecipCert;

    CRYPT_ALGORITHM_IDENTIFIER algorithmID;
    memset(&algorithmID, 0, sizeof(algorithmID));
    algorithmID.pszObjId = (char*)this->encAlgorithm;  //szOID_RSA_RC4;


    memset(&encryptMessagePara, 0, sizeof(encryptMessagePara));
    encryptMessagePara.cbSize = sizeof(encryptMessagePara);
    encryptMessagePara.dwMsgEncodingType = this->encodingType;
    encryptMessagePara.hCryptProv = hProv;
    encryptMessagePara.ContentEncryptionAlgorithm = algorithmID;  

    DWORD bufferSize = 0;
    if (!CryptEncryptMessage(
        &encryptMessagePara,
        1,
        recipients,
        data,
        dataSize,
        NULL,
        &bufferSize)) {

      return GetLastError();
    }

    BYTE* buffer = new BYTE [bufferSize];

    if (CryptEncryptMessage(
        &encryptMessagePara,
        1,
        recipients,
        data,
        dataSize,
        buffer,
        &bufferSize)) {
      //OK
      *ppEncData = buffer;
      *pEncDataSize = bufferSize;
    } else {
      delete [] buffer;
      rc = GetLastError();
    }
    return rc;

  }
};

}
