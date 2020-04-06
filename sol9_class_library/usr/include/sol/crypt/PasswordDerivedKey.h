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
 *  PasswordDerivedKey.h
 *
 *****************************************************************************/

// SOL9 2009/02/22

#pragma once

#include <sol/crypt/CryptServiceProvider.h>
#include <sol/crypt/MessageDigest.h>
#include <sol/crypt/SymmetricKey.h>

 

namespace SOL {

class PasswordDerivedKey :public SymmetricKey {

private:
  MessageDigestÅ@md;

public:
  /**
   * Constructor
   * @param csp  CryptServiceProvider
   * @param algId  Encryption key algorithm Id(CALG_RC2, CALG_RC4, CALG_DES...,CALG_AES_128) 
   * @param password NULL-terminated string.
   * @param hashAlgId   Hash algorithm for the password.
   */
  PasswordDerivedKey(CryptServiceProvicer& csp, ALG_ID algId, 
      const char* password, ALG_ID hashAlgId=CALG_SHA1)
  :SymmetricKey()
  {
    // 1 Generate a MessageDigest specified by hashAlgId
    md.generate(csp, hashAlgId, 0);

    // 2 
    md.hashString(password);

    generate(csp, md, algid, 0);
  }

public:
  /**
   * Destructor
   */
  ~PasswordDerivedKey()
  {

  }
};

}

