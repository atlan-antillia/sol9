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
 *  MessageVerifier.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/13

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>

namespace SOL {

class MessageVerifier :public Object {

private:
  CRYPT_VERIFY_MESSAGE_PARA params;
private:
  DWORD encodingType;

public:
  MessageVerifier(DWORD encType = (X509_ASN_ENCODING|PKCS_7_ASN_ENCODING))
    :encodingType(encType) 
  {
    memset(&params, 0, sizeof(params));
    params.cbSize = sizeof(params);

    //
    params.dwMsgAndCertEncodingType = encodingType;    // Default: X509_ASN_ENCODING|PKCS_7_ASN_ENCODING;
  }

public:
  ~MessageVerifier() 
  {

  }


public:
  int verify(__in Bytes& signedBytes, __out Bytes& decodedBytes)
  {
    int rc =NO_ERROR;

    unsigned char* buffer = NULL;
    unsigned int   size = 0;
    if ((rc = verify(signedBytes.getData(), signedBytes.getSize(), &buffer,  &size)) == NO_ERROR) {
      decodedBytes.shallowCopy(buffer, size);
    }
    return rc;
  }


public:
  int verify(__in const BYTE *signedBytes,
        __in unsigned int signedBytesSize,
        __out BYTE **decodedBytes,
        __out unsigned int *decodedBytesSize,
        __in  PCCERT_CONTEXT *ppSignerCert =NULL) 
  {  
    int rc = NO_ERROR;
    DWORD signerIndex = 0;
    DWORD decSize = 0;

    if (CryptVerifyMessageSignature(
        &params,
        signerIndex,
        signedBytes,
        signedBytesSize,
        NULL,
         &decSize,
        ppSignerCert) == TRUE) {
        // OK
    } else {
      //Failed
      return GetLastError();
    }

    unsigned char* decoded = new unsigned char[decSize];

    if (CryptVerifyMessageSignature(
        &params,
        signerIndex,
        signedBytes,
        signedBytesSize,    
        decoded,
        &decSize,
        ppSignerCert) == TRUE) {
      //OK
      *decodedBytes = decoded;
      *decodedBytesSize = decSize;

    } else {
      delete [] decoded;
      rc = GetLastError();
    }
    return rc;
  }
};

}
