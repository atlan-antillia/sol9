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
 *  CertExportDialog.h
 *
 *****************************************************************************/

// SOL9 
// 2009/03/31

#pragma once

#include <sol/crypt/CertDialog.h>


namespace SOL {

class CertExportDialog :public CertDialog {

private:
  CRYPTUI_WIZ_EXPORT_INFO exportInfo;

public:
  /**
    * Constructor
   */
  CertExportDialog(HWND hParent = NULL) 
  :CertDialog(hParent)
  {
    memset(&exportInfo, 0, sizeof(exportInfo));
    exportInfo.dwSize = sizeof(exportInfo);

  }  

public:

  /**
   * @param pCertContext A pointer to CERT_CONEXT for a certficate to export.
   * @param 
   */
  //Export a ceriticate of PCERT_CONTEXT to a file of exportFileName without UI .

  int doExport(__in PCCERT_CONTEXT pCertContext,
    __in_opt const wchar_t* exportFileName,
    __in_opt const wchar_t* wizardTitle = NULL
    )
  {
    int rc = NO_ERROR;

    HWND hwndParent = getParent();        
      exportInfo.pwszExportFileName = exportFileName;
      exportInfo.dwSubjectChoice  = CRYPTUI_WIZ_EXPORT_CERT_CONTEXT; 
  
       exportInfo.pCertContext = pCertContext;
  
    if (!CryptUIWizExport(
       CRYPTUI_WIZ_NO_UI,
       hwndParent,
        wizardTitle,
        &exportInfo,
        NULL)) {

      rc = GetLastError();  
    }
    return rc;
  }


public:
  //Export a ceriticate of PCERT_CONTEXT with UI.
  int doExport(__in PCCERT_CONTEXT pCertContext,
    __in_opt const wchar_t* wizardTitle = NULL
    )
  {
    int rc = NO_ERROR;

    HWND hwndParent = getParent();        
      exportInfo.pwszExportFileName = NULL;//
      exportInfo.dwSubjectChoice  = CRYPTUI_WIZ_EXPORT_CERT_CONTEXT; 
  
       exportInfo.pCertContext = pCertContext;
  
    if (!CryptUIWizExport(
       0,
       hwndParent,
        wizardTitle,
        &exportInfo,
        NULL)) {

      rc = GetLastError();  
    }
    return rc;
  }

};

/*
typedef struct _CRYPTUI_WIZ_EXPORT_INFO {
  DWORD dwSize;
  LPCWSTR pwszExportFileName;
  DWORD dwSubjectChoice;
  union {
    PCCERT_CONTEXT pCertContext;
    PCCTL_CONTEXT pCTLContext;
    PCCRL_CONTEXT pCRLContext;
    HCERTSTORE hCertStore;
  };
  DWORD cStores;
  HCERTSTORE* rghStores;
} CRYPTUI_WIZ_EXPORT_INFO,  *PCRYPTUI_WIZ_EXPORT_INFO;

 dwSubjectChoice:
  CRYPTUI_WIZ_EXPORT_CERT_CONTEXT
  CRYPTUI_WIZ_EXPORT_CTL_CONTEXT
  CRYPTUI_WIZ_EXPORT_CRL_CONTEXT
  CRYPTUI_WIZ_EXPORT_CERT_STORE
  CRYPTUI_WIZ_EXPORT_CERT_STORE_CERTIFICATES_ONLY 
 */

}
