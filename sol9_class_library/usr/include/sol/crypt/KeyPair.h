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

#pragma once

// SOL9
// 2009/02/03
// 2009/03/03

#include <sol/crypt/CryptServiceProvider.h>
#include <sol/crypt/CryptKey.h>

namespace SOL {

class KeyPair :public CryptKey {

public:
  /**
   * Constructor
   *
   * @param csp    Reference to CryptServiceProvider 
   * @param keySpec  AT_KEYEXCHANGE or AT_SIGNATURE.
   */
  //2009/03/05 Mofied to call generate method if getUserKey failed in NTE_NO_KEY
  KeyPair(CryptServiceProvider& csp, DWORD keySpec) 
    :CryptKey() {

    if (getUserKey(   
         csp.getProviderHandle(),    
         keySpec  
      ) !=NO_ERROR) {

      DWORD err = GetLastError();
      if (err == NTE_NO_KEY) {
        if (generate(   
          csp.getProviderHandle(),    
           keySpec,
          0) != NO_ERROR) {
          throw Exception(GetLastError(), 
            "KeyPair#KeyPair,1,Failed to generate");
        }
      }
      else {
        throw Exception(GetLastError(), 
          "KeyPair#KeyPair,2,Failed to getUserKey");
      }
    }
  }

public:
  /**
   * Constructor
   *
   * @param csp    Reference to CryptServiceProvider 
   * @param algId    CALG_RSA_SIGN or CALG_RSA_KEYX.
   * @param flags  0 or CRYPT_EXPORTABLE
   */
  KeyPair(CryptServiceProvider& csp, ALG_ID algId, DWORD flags) 
    :CryptKey() {

    if (generate(   
      csp.getProviderHandle(),    
       algId,
      flags  
      ) != NO_ERROR) {

        throw Exception(GetLastError(), 
          "KeyPair#KeyPair,1,Failed to getUserKey");
    }
  }
public:
  /**
   * Destructor
   */
  ~KeyPair() {
  }



public:
  /**
   */ 
  // 2009/02/28
  int getPublicKey(Bytes& bytes) {
    int rc = NO_ERROR;
    
    unsigned char* key = NULL;
    unsigned int  length = 0;
    if (getPublicKey(&key, &length, 0) == NO_ERROR) {
       bytes.shallowCopy(key, length);
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  int getPublicKey(unsigned char** key, unsigned int* length, DWORD flags=0) {
     int rc = NO_ERROR;
    if (key && length){
      rc = exportKey(PUBLICKEYBLOB, key, length, flags);
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  /**
   */ 
  // 2009/02/28
  int getPrivateKey(Bytes& bytes) {
    int rc = NO_ERROR;
    
    unsigned char* key = NULL;
    unsigned int  length = 0;
    if (getPrivateKey(&key, &length, 0) == NO_ERROR) {
       bytes.shallowCopy(key, length);
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  int getPrivateKey(unsigned char** key, unsigned int* length, DWORD flags=0) {
     int rc = NO_ERROR;
    if (key && length) {
      rc = exportKey(PRIVATEKEYBLOB, key, length, flags);
    } else {
      rc = -1;
    }
    return rc;

  }

};

}
