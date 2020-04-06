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
 *  TrustVerifier.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/18
// 2009/04/03 Added a method getErroMessage()

#pragma

#include <sol/Object.h>
#include <sol/Arg.h>
#include <softpub.h>
#include <wincrypt.h>
#include <wintrust.h>

#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wintrust.lib")


namespace SOL {

class TrustVerifier :public Object {

private:
  HWND hwnd;

private:
  WINTRUST_FILE_INFO fileInfo;

private:

  WINTRUST_DATA winTrustData;

public:
  /**
   * Constructor
   */
  TrustVerifier(HANDLE hw = INVALID_HANDLE_VALUE)
  :hwnd((HWND)hw) 
  {
    memset(&fileInfo, 0, sizeof(fileInfo));
    fileInfo.cbStruct   = sizeof(fileInfo);

    memset(&winTrustData, 0, sizeof(winTrustData));
    winTrustData.cbStruct = sizeof(winTrustData);
  }


public:
  /**
    * @param fileName  A file name to verify Authenticode.

    * @param revocationChecks
    WTD_REVOKE_NONE
    WTD_REVOKE_WHOLECHAIN

   * @param provFlags 
    WTD_PROV_FLAGS_MASK
    WTD_USE_IE4_TRUST_FLAG
    WTD_NO_IE4_CHAIN_FLAG
    WTD_NO_POLICY_USAGE_FLAG
    WTD_REVOCATION_CHECK_NONE
    WTD_REVOCATION_CHECK_END_CERT
    WTD_REVOCATION_CHECK_CHAIN
    WTD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT
    WTD_SAFER_FLAG
    WTD_HASH_ONLY_FLAG
    WTD_USE_DEFAULT_OSVER_CHECK
    WTD_LIFETIME_SIGNING_FLAG
    WTD_CACHE_ONLY_URL_RETRIEVAL
    
  @*@param actionID
    WINTRUST_ACTION_GENERIC_VERIFY_V2
    WINTRUST_ACTION_TRUSTPROVIDER_TEST
    WINTRUST_ACTION_GENERIC_CERT_VERIFY
    WINTRUST_ACTION_GENERIC_CHAIN_VERIFY
    HTTPSPROV_ACTION
    OFFICESIGN_ACTION_VERIFY
    DRIVER_ACTION_VERIFY

   * @param uiChoice
    WTD_UI_ALL
    WTD_UI_NONE    
    WTD_UI_NOBAD    
    WTD_UI_NOGOOD
 
   * @param unionChoice
    WTD_CHOICE_FILE
    WTD_CHOICE_CATALOG
    WTD_CHOICE_BLOB
    WTD_CHOICE_SIGNER
    WTD_CHOICE_CERT

   * @param stateAction 
    WTD_STATEACTION_IGNORE
    WTD_STATEACTION_VERIFY
    WTD_STATEACTION_CLOSE
    WTD_STATEACTION_AUTO_CACHE
    WTD_STATEACTION_AUTO_CACHE_FLUSH
 
   * @return HRESULT
   */

  HRESULT verify(
    __in const char* fileName,
    __in DWORD revocationChecks = WTD_REVOKE_NONE,      //Revokation none
    __in DWORD provFlags = WTD_REVOCATION_CHECK_NONE,    //Revokation none
    //__in GUID  actionID = (WINTRUST_ACTION_GENERIC_VERIFY_V2),
    __in_opt DWORD uiChoice = WTD_UI_NONE,
    __in_opt DWORD unionChoice = WTD_CHOICE_FILE,
    __in_opt DWORD stateAction =  WTD_STATEACTION_IGNORE) 

  {
    wchar_t wFileName[MAX_PATH];
    size_t rsize = 0;
    //if (mbstowcs(wFileName, fileName, MAX_PATH) == -1) {
    if (mbstowcs_s(&rsize, wFileName, CountOf(wFileName), fileName, MAX_PATH ) != 0) {
      throw GetLastError();
    }
    return verify(
      wFileName,
      revocationChecks,      //Revokation none
      provFlags,    //Revokation none
    //__in GUID  actionID = (WINTRUST_ACTION_GENERIC_VERIFY_V2),
      uiChoice,
      unionChoice,
      stateAction); 

  }

public:
  /**
    * @param fileName  A file name to verify Authenticode.
   */
  HRESULT verify(
    __in const wchar_t* wFileName,
    __in DWORD revocationChecks = WTD_REVOKE_NONE,      //Revokation none
    __in DWORD provFlags = WTD_REVOCATION_CHECK_NONE,    //Revokation none
    //__in GUID  actionID = (WINTRUST_ACTION_GENERIC_VERIFY_V2),
    __in_opt DWORD uiChoice = WTD_UI_NONE,
    __in_opt DWORD unionChoice = WTD_CHOICE_FILE,
    __in_opt DWORD stateAction =  WTD_STATEACTION_IGNORE) 

  {

    GUID  actionID = WINTRUST_ACTION_GENERIC_VERIFY_V2;

    memset(&fileInfo, 0, sizeof(fileInfo));
    fileInfo.cbStruct   = sizeof(fileInfo);
    fileInfo.pcwszFilePath  = wFileName;

    memset(&winTrustData, 0, sizeof(winTrustData));
    winTrustData.cbStruct    = sizeof(winTrustData);

    winTrustData.dwUIChoice    = uiChoice;//WTD_UI_NONE;
    winTrustData.fdwRevocationChecks = revocationChecks;
    winTrustData.dwUnionChoice   = unionChoice;  //WTD_CHOICE_FILE;
    winTrustData.pFile     = &fileInfo;
    winTrustData.dwStateAction   = stateAction;  //WTD_STATEACTION_IGNORE;
    winTrustData.dwProvFlags   = provFlags;

    HWND hwindow = this->hwnd;
    if (uiChoice == WTD_UI_NONE) {
      //To ggnore user interface, 
      //set INVALID_... to HWND eveif hwnd is valid window.
      hwindow = (HWND)INVALID_HANDLE_VALUE;
    }
    return WinVerifyTrust(hwindow, &actionID, &winTrustData);
  }

public:
  // 2009/04/03
  const TCHAR* getErroMessage(HRESULT hr)
  {
    const TCHAR* FILE_SIGNED = _T("The file is signed");
    if (SUCCEEDED(hr)) {
      // if SUCCEEDED
      return FILE_SIGNED;
    }

    // else
    const TCHAR* message = _T("Unknown error");

    static const Arg error[] = {
      {_T("The file is not signed"),  
        (LONG_PTR)TRUST_E_NOSIGNATURE},
      {_T("The file is signed, but the signature not verified"), 
        (LONG_PTR)CERT_E_CHAINING},
      {_T("The file type is not supported"), 
        (LONG_PTR)TRUST_E_SUBJECT_FORM_UNKNOWN }
    };
 
    for (size_t i = 0; i < XtNumber(error); i++) {
      if (error[i].value == (LONG_PTR)hr) {
        message = error[i].name;
        break;
      }
    }
    return message;
  }
  
/*
typedef struct _WINTRUST_DATA {
  DWORD  cbStruct;
  LPVOID pPolicyCallbackData;
  LPVOID pSIPClientData;
  DWORD  dwUIChoice;
  DWORD  fdwRevocationChecks;
  DWORD  dwUnionChoice;
  union {    struct WINTRUST_FILE_INFO_ *pFile;
    struct WINTRUST_CATALOG_INFO_ *pCatalog;
    struct WINTRUST_BLOB_INFO_ *pBlob;
    struct WINTRUST_SGNR_INFO_ *pSgnr;
    struct WINTRUST_CERT_INFO_ *pCert;  
 }  ;
  DWORD  dwStateAction;
  HANDLE hWVTStateData;
  WCHAR * pwszURLReference;
  DWORD  dwProvFlags;
  DWORD  dwUIContext;
} WINTRUST_DATA, *PWINTRUST_DATA;
*/

};

}
