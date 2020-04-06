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
 *  CertChainContext.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/17

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>


namespace SOL {

class CertChainContext :public Object {

private:
  PCCERT_CHAIN_CONTEXT  pChainContext

public:
  /**
   * @param  context  PCCERT_CONTEXT
   *      option parameter.
   */
  //2009/03/15 context=NULL
  CertChainContext(PCCERT_CHAIN_CONTEXT context=NULL)
  :pChainContext(context)
  {
    //Simple shallow copy for the pointer context;
  }

public:
  /**
   * Destructor
   */
  ~CertChainContext() {
    if (pContext) {
      CertFreeCertificateChain(pChainContext);

      pContext = NULL;
    }
  }

};

}
