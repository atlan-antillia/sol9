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
 *  MessageDigest.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/17

#pragma once

#include <sol/crypt/CryptServiceProvider.h>
#include <sol/crypt/CryptHash.h>

#include <sol/Arg.h>

namespace SOL {

class MessageDigest :public CryptHash {

public:
  /**
   *
   */
  MessageDigest()
    :CryptHash()
  {
  }

public:
  /**
   * Constructor
   * @param algId CALG_MD2, CALG_MD4, CALG_MD5, CALG_SHA, CALG_SHA1, CALG_SHA_256, CALG_SHA_384, CALG_SHA_512 
   */
  MessageDigest(CryptServiceProvider& csp, ALG_ID algId)
    :CryptHash() {

    if (create(csp.getProviderHandle(), 
      algId, NULL, 0) != NO_ERROR) {
      
      throw Exception(GetLastError(), 
        "MessageDigest#MessageDigest,1,CryptCreateHash failed");
    }
  }


public:
  /**
   * Destructor
   */
  ~MessageDigest() {
  }

};

}

