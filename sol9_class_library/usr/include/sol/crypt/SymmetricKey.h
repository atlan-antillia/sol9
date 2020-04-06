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
 *  KeyPair.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/03

#pragma once

#include <sol/crypt/CryptServiceProvider.h>

#include <sol/crypt/CryptKey.h>
#include <sol/crypt/CryptHash.h>

/**
  try {
  CryptServiceProvider csp;

  SymmetricKey aes256Ecb(csp, CALG_AES_256, CRYPT_MODE_ECB);

  } catch (Exception& ex) {

  }
 */

namespace SOL {

class SymmetricKey: public CryptKey {

public:
  SymmetricKey()
    :CryptKey()
  {
  }

public:
  /**
   * Constructor
   *
   * @param  algId CALG_RC2, CALG_RC4, CALG_DES, CALG_3DES, CALG_AES_128, CALG_AES_192, CALG_AES_256,
     *
   * @param mode CRYPT_MODE_ECB, CRYPT_MODE_CBC, CRYPT_MODE_FCB
   *
   * Usage:
    CryptoServiceProvider csp;
    SymmetricKey aesKey128(csp, CALG_AES_128, DCRYPT_MODE_ECB)
    SymmetricKey rc2Key;
    rc2Key.create(csp, CALG_RC2, 0);
   */
  SymmetricKey(CryptServiceProvider &csp,
    ALG_ID algId, DWORD mode=0)
  :CryptKey() {
    //
    generate(csp, algId, mode);
  }

public:
  /**
   * Constructor
   *
   * @param  algId CALG_RC2, CALG_RC4, CALG_DES, CALG_3DES, CALG_AES_128, CALG_AES_192, CALG_AES_256,
     *
   * @param mode CRYPT_MODE_ECB, CRYPT_MODE_CBC, CRYPT_MODE_FCB
   *
   */
  SymmetricKey(CryptServiceProvider &csp,
    CryptHash& hash,
    ALG_ID algId, DWORD mode=0)
  :CryptKey() {
    //
    derive(csp, hash, algId, mode);
  }


public:
  /*
   * Generate a key from the parameters given.
   *
   * @param  algId CALG_RC2, CALG_RC4, CALG_DES, CALG_3DES, CALG_AES_128, CALG_AES_192, CALG_AES_256,
     *
   * @param mode CRYPT_MODE_ECB, CRYPT_MODE_CBC, CRYPT_MODE_FCB
   *
   */
  int generate(CryptServiceProvider &csp,
    ALG_ID algId, DWORD mode=0){
    int rc = NO_ERROR;
    if ((rc = CryptKey::generate(csp.getProviderHandle(), 
        algId, CRYPT_EXPORTABLE)) !=NO_ERROR) {

        throw Exception(GetLastError(), 
            "SymmetricKey::generate,1,Failed to genKey.");
    }

    if (mode !=0) {
      if ((rc=setKeyParam(KP_MODE, (unsigned char*)mode,  0)) !=NO_ERROR) {

        throw Exception(GetLastError(),
          "SymmetricKey::generate,1,Failed to setKeyParam.");
      }
    }
    return rc;
  }
public:
  /*
   * Derive a key from the parameters given.
   *
   * @param  algId CALG_RC2, CALG_RC4, CALG_DES, CALG_3DES, CALG_AES_128, CALG_AES_192, CALG_AES_256,
     *
   * @param mode CRYPT_MODE_ECB, CRYPT_MODE_CBC, CRYPT_MODE_FCB
   *
   */

  int derive(CryptServiceProvider &csp,
      CryptHash& hash,
      ALG_ID algId, DWORD mode=0) {
    int rc = NO_ERROR;
    if ((rc = CryptKey::derive(csp.getProviderHandle(), 
        algId, hash.getHashHandle(), CRYPT_EXPORTABLE
        )) !=NO_ERROR) {
        throw Exception(GetLastError(), 
            "SymmetricKey::generate,1,Failed to genKey.");
    }

    if (mode !=0) {
      if ((rc = setKeyParam(KP_MODE, (unsigned char*)mode,  0)) !=NO_ERROR) {

        throw Exception(GetLastError(),
          "SymmetricKey::generate,1,Failed to setKeyParam.");
      }
    }
    return rc;
  }

public:
  ~SymmetricKey() {
  }

public:
  int setIV(unsigned char* iv, unsigned int size) {
    int rc = 0;
    if (iv != NULL && size >0) {
      if (!setKeyParam(
           KP_IV,
           iv,
        0)) {
         rc = GetLastError();
      }
    }
    return rc;
  }

public:
  int getIV(unsigned char** iv, unsigned int* size) {
    int rc = 0;
    //  Get the length of the new initialization vector.
    DWORD dwCount = 0;
    if (getKeyParam(KP_IV, 
            NULL,     
        &dwCount, 0))  {

      *size = dwCount;

      // Get the IV, itself
      unsigned char* data = new unsigned char[dwCount];
      if (getKeyParam(KP_IV, 
        data, 
        &dwCount, 0)) {

        *iv = data;
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

