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
 *  DSASignatureKey.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/05

#pragma once

#include <sol/crypt/DSACryptServiceProvider.h>
#include <sol/crypt/KeyPair.h>

/**
  try {
  DSACryptServiceProvider csp("FOO");

  DSASignatureKey  signKey(csp);

  } catch (Exception& ex) {

  }
 */

namespace SOL {

class DSASignatureKey: public KeyPair {

public:
  /**
   * Constructor
   */
  DSASignatureKey(DSACryptServiceProvider& csp)
  :KeyPair(csp, AT_SIGNATURE) {
    //  
  }

public:
  /**
   * Destructor
   */
  ~DSASignatureKey() {
    //
  }
};

}

