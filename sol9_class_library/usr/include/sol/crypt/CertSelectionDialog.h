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
 *  CertSelectionDialog.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/17
// 2009/03/23 Modiied to inherit CertDialog class.


#pragma once

#include <sol/crypt/CertDialog.h>
#pragma comment (lib, "cryptui.lib")

namespace SOL {

class CertSelectionDialog :public CertDialog {

private:
  HCERTSTORE hCertStore;  

public:
  /**
   *
   */
  CertSelectionDialog(CertStore& certStore, HWND hwnd=NULL)
  :CertDialog(hwnd),
  hCertStore(certStore.getStoreHandle())

  {
  }

public:
  /**
   * @param dwDontUseColumn 
      CRYPTUI_SELECT_ISSUEDTO_COLUMN 
      CRYPTUI_SELECT_ISSUEDBY_COLUMN
      CRYPTUI_SELECT_INTENDEDUSE_COLUMN 
      CRYPTUI_SELECT_FRIENDLYNAME_COLUMN  
      CRYPTUI_SELECT_LOCATION_COLUMN
      CRYPTUI_SELECT_EXPIRATION_COLUMN
   */

  PCCERT_CONTEXT show(
    __in_opt  LPCWSTR pwszTitle=NULL,
    __in_opt  LPCWSTR pwszDisplayString=NULL,
    __in_opt  DWORD dwDontUseColumn = CRYPTUI_SELECT_LOCATION_COLUMN)
  {
    HWND hParent = getParent();
    return CryptUIDlgSelectCertificateFromStore(
        hCertStore,
        hParent,
        pwszTitle,  
        pwszDisplayString,
        dwDontUseColumn,
        0,
        NULL);      
  }

};

}

