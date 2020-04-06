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
 *  MessageSigner.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/13

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>

namespace SOL {


class MessageSigner :public Object {

private:
  CRYPT_SIGN_MESSAGE_PARA  signParam;

private:
  DWORD encodingType;
   const char* hashAlgorithm;

public:
  /**
   * Constructor
   */
  MessageSigner(DWORD encType=(PKCS_7_ASN_ENCODING|X509_ASN_ENCODING),
      const char* objId=szOID_RSA_MD5)
    :encodingType(encType),
    hashAlgorithm(objId)
  {
    memset(&signParam, 0, sizeof(signParam));
    signParam.cbSize = sizeof(signParam);
  }


public:
  /**
   * Destructor
   */
  ~MessageSigner()
  {
  }


public:
  int sign(__in PCCERT_CONTEXT certContext, 
       __in Bytes& message,
       __out Bytes& signedMessage)
  {
    int rc = NO_ERROR;

    unsigned char* enc = NULL;
    size_t         encSize = 0;
    if ((rc = sign(certContext, message.getData(), message.getSize(),
      &enc,
      &encSize)) !=NO_ERROR) {
      signedMessage.shallowCopy(enc, encSize);
    }
    return rc;
  }
  
public:
  /**
   * @param certContext  Certificate context to be used to sign
   * @param message    BYTES array to be signed.
   * @param messageSize  BYTES length of message.
   * @param signedMessage  Pointe to Pointer to BYTE to return signed bytes.
   * @param signedMessageSize Pointer to size_t to return the size of signed bytes.
   */
  int sign(__in PCCERT_CONTEXT certContext, 
      __in const BYTE* message, 
      __in size_t messageSize,
      __out BYTE** signedMessage,
      __out size_t* signedMessageSize) {

    int rc = NO_ERROR;

    const BYTE* messageArray[1] = {message};  
    DWORD messageSizeArray[1]   = {messageSize};


    signParam.cbSize = sizeof(signParam);
    signParam.dwMsgEncodingType = encodingType;    //
    signParam.pSigningCert = certContext;
    signParam.HashAlgorithm.pszObjId = (char*)hashAlgorithm;//szOID_RSA_MD5;
    signParam.HashAlgorithm.Parameters.cbData = NULL;
    signParam.cMsgCert = 1;
    signParam.rgpMsgCert = &certContext;
    /*
    signParam.cAuthAttr = 0;
    signParam.dwInnerContentType = 0;
    signParam.cMsgCrl = 0;
    signParam.cUnauthAttr = 0;
    signParam.dwFlags = 0;
    signParam.pvHashAuxInfo = NULL;
    signParam.rgAuthAttr = NULL;
    */

    DWORD bufferSize = 0;

    if (CryptSignMessage(
          &signParam,            // signature parameters
        FALSE,                 // not detached
        1,                     // number of messages
        messageArray,          // messages to be signed
        messageSizeArray,      // size of messages
        NULL,                  // buffer for signed message
          &bufferSize) == TRUE ) {
      //OK

    } else {
      //Failed
      return GetLastError();
    }

    BYTE* buffer = new BYTE[bufferSize];
  
    if (CryptSignMessage(
          &signParam, 
      FALSE,
      1,    
      messageArray,
      messageSizeArray,
      buffer,
          &bufferSize) == TRUE) {

      //OK
      *signedMessage = buffer;
      *signedMessageSize = bufferSize;
    } else {
      //Failed
      delete [] buffer;
      return GetLastError();
    }
    return rc;
  }
};

}

