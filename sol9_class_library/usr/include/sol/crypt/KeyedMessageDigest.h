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
 *  KeyedMessageDigest.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/17

#pragma once

#include <sol/crypt/CryptServiceProvider.h>
#include <sol/crypt/CryptHash.h>
#include <sol/crypt/CryptKey.h>
#include <sol/crypt/MessageDigest.h>
#include <sol/crypt/SymmetricKey.h>


namespace SOL {

class KeyedMessageDigest :public CryptHash {


private:
  MessageDigest md;
  SymmetricKey  key;

public:
  /**
   * algId: Hash algorithm
      CALG_HMAC       Keyed hash alogoritm  
      CALG_MAC        MessageAuth keyed hash algorithm
   */
  KeyedMessageDigest(CryptServiceProvider& csp, ALG_ID algId, CryptKey& key)
  :CryptHash() {

    if (create(csp.getProviderHandle(), 
      algId, key.getKeyHandle(), 0) != NO_ERROR) {
      
      throw Exception(GetLastError(), 
        "KeyedMessageDigest#KeyedMessageDigest,1,CryptCreateHash failed");
    }
  }

public:
  /**
   * algId: Hash algorithm
      CALG_HMAC       Keyed hash alogoritm  
      CALG_MAC        MessageAuth keyed hash algorithm
  */
  KeyedMessageDigest(CryptServiceProvider& csp, ALG_ID algId, 
    ALG_ID mdAlgId = CALG_SHA1, ALG_ID keyAlgId = CALG_RC2,
    const char* password="")

  :CryptHash() {

    md.create(csp.getProviderHandle(), mdAlgId);  //SHA1
    md.hashString(password);  //Dummy string
  
    //Derive a default rc2 key from the above message-digest of sha1
    key.derive(csp, md, keyAlgId, 0);  //RC2

    if (create(csp.getProviderHandle(), 
      algId, key.getKeyHandle(), 0) != NO_ERROR) {
      
      throw Exception(GetLastError(), 
        "KeyedMessageDigest#KeyedMessageDigest,1,CryptCreateHash failed");
    }
  }

public:
  /**
   * Destructor
   */
  ~KeyedMessageDigest() {
  }

};

}

