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
 *  CertContextDialog.h
 *
 *****************************************************************************/

#pragma once

#include <sol/crypt/CertDialog.h>


namespace SOL {

class CertContextDialog :public CertDialog {

private:

  DWORD dwContextType;

public:
  /**
   * Constructor
   *
   * @param hwnd Handle of the window for the display. If NULL, it's the desktop window.
   
   * @param contextType;
    CERT_STORE_CERTIFICATE_CONTEXT 
    CERT_STORE_CRL_CONTEXT PCCRL_CONTEXT
    CERT_STORE_CTL_CONTEXT PCCTL_CONTEXT
  
   */
  CertContextDialog(HWND hParent=NULL, 
    DWORD contextType=CERT_STORE_CERTIFICATE_CONTEXT)
  :CertDialog(hParent),
   dwContextType(contextType) 
  {


  }

public:
  /**
   * @param  pvContext For example, this takes a pointer(PCCERT_CONTEXT) to CERT_CONTEXT 
   */
  int show(__in const void* pvContext, 
       __in const wchar_t* title=NULL, 
       __in DWORD dwFlags=0) 
  {
    int rc = NO_ERROR;
    HWND hParent = getParent();
    if (!CryptUIDlgViewContext(
       this->dwContextType,
       pvContext,
      hParent,
      title,
      dwFlags,
      NULL)) {
      //Error
      rc = GetLastError();
    }
    return rc;  
  }
  
};

}
