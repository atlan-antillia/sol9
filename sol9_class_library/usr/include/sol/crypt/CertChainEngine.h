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
 *  CertChainEngine.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/17
// 2011/09/04 Modified the contructor of CertChainEngine.

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

#include <sol/Bytes.h>


namespace SOL {

class CertChainEngine: public Object {
private:

  HCERTCHAINENGINE    hChainEngine;
  CERT_CHAIN_ENGINE_CONFIG chainConfig;

public:
  /**
   * Constructor
   */
  CertChainEngine()
    :hChainEngine(NULL) 
  {

    //chainPara.cbSize = sizeof(CERT_CHAIN_PARA);
    //chainPara.RequestedUsage=certUsage;
    // 2011/09/04 Added the following line.
    memset(&chainConfig, 0, sizeof(CERT_CHAIN_ENGINE_CONFIG));

    chainConfig.cbSize = sizeof(CERT_CHAIN_ENGINE_CONFIG);
    chainConfig.hRestrictedRoot= NULL ;
    chainConfig.hRestrictedTrust= NULL;  
    chainConfig.hRestrictedOther= NULL ;
    chainConfig.cAdditionalStore=0 ;
    chainConfig.rghAdditionalStore = NULL ;
    chainConfig.dwFlags = CERT_CHAIN_CACHE_END_CERT;
    chainConfig.dwUrlRetrievalTimeout= 0 ;
    chainConfig.MaximumCachedCertificates=0 ;
    chainConfig.CycleDetectionModulus = 0;

    // Create a certificate chain engine.
    if(CertCreateCertificateChainEngine(
      &chainConfig,
      &hChainEngine) != TRUE) {

        printf("Engine creation failed.\n");

      throw GetLastError();
    }
    // Open the My system store.
  
  }

public:
  /**
   * Destructor
   */
  ~CertChainEngine()
  {
    if (hChainEngine) {
      CertFreeCertificateChainEngine(hChainEngine);
      hChainEngine = NULL;
    }
  }

public:
  HCERTCHAINENGINE getChainEngineHandle() {
    return hChainEngine;
  }

public:
  /**
   * Get a chain (ppChainContext) of certificate for a certificate pCertContext.
   *
   */
  int getCertificateChain(__in PCCERT_CONTEXT pCertContext,
              __out PCCERT_CHAIN_CONTEXT*  ppChainContext)
  {
    int rc = NO_ERROR;

    CERT_ENHKEY_USAGE  enhkeyUsage;
    CERT_USAGE_MATCH  certUsage;  
    CERT_CHAIN_PARA    chainPara;
    
    memset(&enhkeyUsage, 0, sizeof(enhkeyUsage));
    memset(&certUsage, 0, sizeof(certUsage));
    memset(&chainPara, 0, sizeof(chainPara));
    
    enhkeyUsage.cUsageIdentifier = 0;
    enhkeyUsage.rgpszUsageIdentifier=NULL;

    certUsage.dwType = USAGE_MATCH_TYPE_AND;
    certUsage.Usage  = enhkeyUsage;

    chainPara.cbSize = sizeof(CERT_CHAIN_PARA);
    chainPara.RequestedUsage=certUsage;

    DWORD dwFlags = 0;

    // Get a chain of certificates by using CertGetCertificateChain
    // 
    if(CertGetCertificateChain(
      this->hChainEngine, // chain engine
      pCertContext,       
      NULL,               // default time
      NULL,               // no additional stores
      &chainPara,         
  
      dwFlags,
      NULL,                  
      ppChainContext) !=TRUE) {

       printf("Failed to get a chain of certifiates.\n");
       return GetLastError();

    } else {
      //OK
    }
    return rc;
  }
};

}
