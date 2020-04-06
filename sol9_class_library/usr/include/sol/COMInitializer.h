
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
 *  COMInitializer.h
 *
 *****************************************************************************/


#pragma once

#define _WIN32_DCOM

#include <sol\Object.h>

namespace SOL 
{
class COMInitializer :public Object {

public:
  /**
   * Constructor
   */
  COMInitializer() { 
    HRESULT hr = S_OK;
    if (FAILED(hr = CoInitialize(NULL))) {
      throw hr; 
    }
  }

public:
  /**
   * Constructor
   *
   * @param dwCoInit  COM initializer parameter
   * // Example: dwCoInit = COINIT_MULTITHREADED
   */
  COMInitializer(DWORD dwCoInit) { 
    HRESULT hr = S_OK;
    if (FAILED(hr = CoInitializeEx(NULL, dwCoInit))) {
      throw hr; 
    }
  }

public:
  /**
   * Destructor
   */
  ~COMInitializer() {
    CoUninitialize();
  }

public:
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
      RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
      RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
      NULL,                        // Authentication info
      EOAC_NONE,                   // Additional capabilities 
      NULL                         // Reserved
      ))) {
      throw hr; 
    }
  }
/*
 */
};


}
