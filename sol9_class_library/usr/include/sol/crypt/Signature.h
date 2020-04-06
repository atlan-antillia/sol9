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
 *  Signature.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/03
// 2009/03/05 Added sign and verify methods taking Bytes parameter.

#pragma once

#include <sol/crypt/MessageDigest.h>

namespace SOL {

class Signature :public MessageDigest {


public:
  /**
   * Constructor
   */
  Signature(CryptServiceProvider& csp, ALG_ID algId)
  :MessageDigest(csp, algId) {
     
  }

public:
  /**
   * Destructor
   */
  ~Signature() {
  }

public:
  /**
   * Sign to the bytes.
   */
  // 2009/03/05
  int sign(Bytes& bytes) {
    int rc = NO_ERROR;
    unsigned char* sig = NULL;
    unsigned int   len = 0;
    if (sign(&sig, &len) == NO_ERROR) {
      bytes.shallowCopy(sig, len);
    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   * Sign
   */
  int sign(unsigned char** signature, unsigned int* length) {
    int rc = NO_ERROR;

    //1. Determine the size of the signature.
    DWORD len= 0;

    if (CryptSignHash(
        getHashHandle(), 
        AT_SIGNATURE, 
        NULL, 
        0, 
        NULL, 
        &len)) {
      // OK
      *length = len;    
      unsigned char* buffer =  new unsigned char[len];

      //2. Sign the hash object.
      if (CryptSignHash(
        getHashHandle(), 
        AT_SIGNATURE, 
        NULL, 
        0, 
        buffer, 
        &len)) {
        // OK
        *signature = buffer;
      } else {
        // Failed
        delete[] buffer;
        rc = GetLastError();
      }
    } else {
      //Failed
      rc = GetLastError();
    }  
    return rc;
  }

public:
  /**
   * Verify signature for bytes.
   */
  // 2009/03/05
  int verify(HCRYPTKEY hPubKey, Bytes& bytes) {
  
    return verify(hPubKey, bytes.getData(), bytes.getSize());
  }


public:
  /**
   * Verify signature for signature.
   *
   */
  int verify(HCRYPTKEY hPubKey, 
      unsigned char* signature, unsigned int length) {

    int rc = NO_ERROR;

    // Validate the digital signature.
    if (!CryptVerifySignature(
         getHashHandle(), 
         signature, 
         length, 
         hPubKey,
         NULL, 0)) {
      rc = GetLastError();
    }
    return rc;
  }
};

}
