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
 *  DataUnprotector.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/16

#pragma once

#include <sol/crypt/DataProtection.h>

namespace SOL {
  
class DataUnprotector :public DataProtection {

public:
  /**
   * Constructor
   */
  DataUnprotector(HWND hParent=NULL, const wchar_t* prompt=NULL)
  :DataProtection(hParent, prompt) 
  {

  }

public:
  /**
   * Decrypt an protectedData and return it for a outputData.
   * If ui parameter is true, a prompt dialog will be displayed.  
   *
   * @param dwFlags Takes 0 or one of the following values. 
    CRYPTPROTECT_UI_FORBIDDEN
    CRYPTPROTECT_VERIFY_PROTECTION
   */
  
  int unprotect(
    __in DATA_BLOB& protectedData, 
    __out DATA_BLOB& outputData, 
    __out_opt wchar_t**  description=NULL,
    __in_opt bool ui = false,
    __in_opt DATA_BLOB* entropy = NULL,
    __in_opt DWORD dwFlags = 0)
  {
    int rc = NO_ERROR;

    CRYPTPROTECT_PROMPTSTRUCT* pPrompter = NULL;
    if (ui) {
      pPrompter = getPrompter();
    }

    if(!CryptUnprotectData(
           &protectedData,
      description,
      entropy,                  
      NULL,      // Reserved.
           pPrompter,
      dwFlags,
      &outputData)) {
  
      rc = GetLastError();
    }
    return rc;
  } 
};

}
