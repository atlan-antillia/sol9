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
 *  ComThreadModel.h
 *
 *****************************************************************************/

// 2009/12/24 Modified to catch an IException from setDefaultSecurityLevel
//

#pragma once

#define _WIN32_DCOM

#include <sol\Object.h>
#include <sol/Exception.h>

namespace SOL {

class ComThreadModel :public Object {

public:
  ComThreadModel(DWORD threadModel, bool initializeCom, bool setDefaultSecurity=true)
  {
    HRESULT hr = E_FAIL;
    if (initializeCom ) {
      if (FAILED(hr = CoInitializeEx(NULL, threadModel))) {
        printf("Failed CoIntialize %0x\n", hr);
        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
      }
  
      if (setDefaultSecurity) {
        //2009/12/24
        try {
          setDefaultSecurityLevels();
        } catch (...) {
          ;//
        }
      }
    }
  }


public:
  /**
   * Destructor
   */
  ~ComThreadModel() {
    CoUninitialize();
  }

  /**
   * Set Default COM security levels with default authentication and Impersonation.
   */
  void setDefaultSecurityLevels() {
    HRESULT hr = S_OK;
    if (FAILED (hr=  CoInitializeSecurity(
      NULL, 
      -1,                          // COM negotiates service
      NULL,                        // Authentication services
      NULL,                        // Reserved
      RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication, RPC_C_AUTHN_LEVEL_PKT_INTEGRITY,  
      RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
      NULL,                        // Authentication info
      EOAC_NONE,                   // Additional capabilities 
      NULL                         // Reserved
      ))) {
      printf("Failed to setDefaultSecurityLevel %0x\n", hr);
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__); 
    }
  }

};


}
