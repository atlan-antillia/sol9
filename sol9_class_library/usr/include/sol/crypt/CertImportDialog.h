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
 *  CertImportDialog.h
 *
 *****************************************************************************/

// SOL9 
// 2009/03/31

#pragma once

#include <sol/crypt/CertDialog.h>


namespace SOL {

class CertImportDialog :public CertDialog {

private:
  CRYPTUI_WIZ_IMPORT_SRC_INFO importSrcInfo;

public:
  /**
    * Constructor
   */
  CertImportDialog(HWND hParent = NULL) 
  :CertDialog(hParent)
  {
    memset(&importSrcInfo, 0, sizeof(importSrcInfo));
    importSrcInfo.dwSize = sizeof(importSrcInfo);

  }  

public:
  /**
   *
   */
  //Import a certfile to a certstore without UI (CRYPTUI_WIZ_NO_UINO_UI).
  int doImport(
    __in const wchar_t* importFileName,
    __in const wchar_t* password,
    __in_opt const wchar_t* wizardTitle = NULL,
    __in_opt HCERTSTORE hDestCertStore = NULL)
  {
    int rc = NO_ERROR;

    HWND hwndParent = getParent();        
    importSrcInfo.dwSubjectChoice = CRYPTUI_WIZ_IMPORT_SUBJECT_FILE;
    importSrcInfo.pwszFileName    = importFileName;
    importSrcInfo.dwFlags         = CRYPT_EXPORTABLE | CRYPT_USER_PROTECTED;
    importSrcInfo.pwszPassword    = password;
      
    if (!CryptUIWizImport(
       CRYPTUI_WIZ_NO_UI,
       hwndParent,
        wizardTitle,
        &importSrcInfo,
        hDestCertStore)) {

      rc = GetLastError();  
    }


    return rc;
  }


public:
  /**
   *
   */
  int doImport(
    __in_opt const wchar_t* wizardTitle = NULL,
    __in_opt HCERTSTORE hDestCertStore = NULL)
  {
    int rc = NO_ERROR;

    HWND hwndParent = getParent();        
      
    if (!CryptUIWizImport(
       0,
       hwndParent,
        wizardTitle,
        NULL,
        hDestCertStore)) {

      rc = GetLastError();  
    }

    return rc;
  }
/**
 * @param dwFlags
 *
  CRYPTUI_WIZ_NO_UI (0x0001) 
  CRYPTUI_WIZ_IGNORE_NO_UI_FLAG_FOR_CSPS (0x0002) 
  CRYPTUI_WIZ_NO_UI_EXCEPT_CSP (0x0003)
  CRYPTUI_WIZ_IMPORT_ALLOW_CERT (0x00020000)
  CRYPTUI_WIZ_IMPORT_ALLOW_CRL (0x00040000)
  CRYPTUI_WIZ_IMPORT_ALLOW_CTL (0x00080000)
  CRYPTUI_WIZ_IMPORT_NO_CHANGE_DEST_STORE (0x00010000)
  CRYPTUI_WIZ_IMPORT_TO_LOCALMACHINE (0x00100000)
  CRYPTUI_WIZ_IMPORT_TO_CURRENTUSER (0x00200000)
  CRYPTUI_WIZ_IMPORT_REMOTE_DEST_STORE (0x00400000) 
 */

};

}
