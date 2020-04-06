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
 *  CertSignerInfoDialog.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/02
// Modified show method;the second parameter hMsg not to take a default NULL value.

#pragma once

#include <sol/crypt/CertDialog.h>

namespace SOL {

typedef struct tagCRYPTUI_VIEWSIGNERINFO_STRUCT {
  DWORD            dwSize;
  HWND             hwndParent;
  DWORD            dwFlags;
  LPCTSTR          szTitle;
  CMSG_SIGNER_INFO *pSignerInfo;
  HCRYPTMSG        hMsg;
  LPCSTR           pszOID;
  DWORD_PTR        dwReserved;
  DWORD            cStores;
  HCERTSTORE *      rghStores;
  DWORD            cPropSheetPages;
  LPCPROPSHEETPAGE rgPropSheetPages;
} CRYPTUI_VIEWSIGNERINFO_STRUCT;

BOOL WINAPI CryptUIDlgViewSignerInfo(
  __in  CRYPTUI_VIEWSIGNERINFO_STRUCT *pcvsi
);

typedef BOOL (WINAPI *FNCryptUIDlgViewSignerInfo)(CRYPTUI_VIEWSIGNERINFO_STRUCT *);

class CertSignerInfoDialog :public CertDialog {

private:
  CRYPTUI_VIEWSIGNERINFO_STRUCT signerInfo;
  HMODULE   hModule;
  FNCryptUIDlgViewSignerInfo cryptUIDlgViewSignerInfo;

public:
  /**
   * Constructor
   */
  CertSignerInfoDialog(HWND hParent = NULL)
  :CertDialog(hParent),
  hModule(NULL),
  cryptUIDlgViewSignerInfo(NULL)
  {
    memset(&signerInfo, 0, sizeof(signerInfo));
    signerInfo.dwSize = sizeof(signerInfo);
    this->hModule = LoadLibrary(_T("cryptui.dll"));
    if (this->hModule) {
      this->cryptUIDlgViewSignerInfo = 
          (FNCryptUIDlgViewSignerInfo)GetProcAddress(this->hModule,  "CryptUIDlgViewSignerInfoW");
      if (this->cryptUIDlgViewSignerInfo == NULL) {
        FreeLibrary(this->hModule);
        throw GetLastError();
      } else {
        ;//OK
      }
    } else {
      throw GetLastError();
    }
  }  


public:
  /**
   * Destructor
   */
  ~CertSignerInfoDialog()
  {
    if (this->hModule) {
      FreeLibrary(this->hModule);
      this->hModule = NULL;
    }
  }

public:

  // 2009/04/02
  // Modified the second parameter hMsg not to take a default NULL value.
  int show(
      __in CMSG_SIGNER_INFO *pSignerInfo,
      __in HCRYPTMSG        hMsg,
      __in LPCSTR           pszOID = NULL,
      __in DWORD dwFlags=0)
  {
    int rc = NO_ERROR;

    HWND hParent = getParent();
    signerInfo.hwndParent = hParent;
    signerInfo.dwFlags = dwFlags;
    signerInfo.pSignerInfo = pSignerInfo;
    signerInfo.hMsg        = hMsg;
    signerInfo.pszOID      = pszOID;

    if (!cryptUIDlgViewSignerInfo(&signerInfo)) {
      rc = GetLastError();
    }
    return rc;
  }
};

}

