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
 *  CryptError.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/05
// 2015/12/21 Updated to remove compilation warnings on errors in getMessage method,

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>
#include <wincrypt.h>


namespace SOL {

class CryptError :public Object {

public:
  static const TCHAR* getMessage(DWORD errId) {
    const TCHAR* message = _T("Unknown");

    static const Arg errors[] = {

    {_T("NTE_BAD_UID: Bad UID."),
      (LONG_PTR)NTE_BAD_UID},
    {_T("NTE_BAD_HASH: Bad Hash."),  
      (LONG_PTR)NTE_BAD_HASH},
    {_T("NTE_BAD_KEY: Bad Key."), 
      (LONG_PTR)NTE_BAD_KEY},
    {_T("NTE_BAD_LEN: Bad Length."),  
      (LONG_PTR)NTE_BAD_LEN},
    {_T("NTE_BAD_DATA: Bad Data."),  
      (LONG_PTR)NTE_BAD_DATA},
    {_T("NTE_BAD_SIGNATURE: Invalid Signature."), 
      (LONG_PTR)NTE_BAD_SIGNATURE},
    {_T("NTE_BAD_VER: Bad Version of provider."),
      (LONG_PTR)NTE_BAD_VER},
    {_T("NTE_BAD_ALGID: Invalid algorithm specified."),
      (LONG_PTR)NTE_BAD_ALGID},
    {_T("NTE_BAD_FLAGS: Invalid flags specified."),
      (LONG_PTR)NTE_BAD_FLAGS},
    {_T("NTE_BAD_TYPE: Invalid type specified."),
      (LONG_PTR)NTE_BAD_TYPE},
    {_T("NTE_BAD_KEY_STATE: Key not valid for use in specified state."),
      (LONG_PTR)NTE_BAD_KEY_STATE},
    {_T("NTE_BAD_HASH_STATE: Hash not valid for use in specified state."),
      (LONG_PTR)NTE_BAD_HASH_STATE},
    {_T("NTE_NO_KEY: Key does not exist."), 
      (LONG_PTR)NTE_NO_KEY},
    {_T("NTE_NO_MEMORY: Insufficient memory available for the operation."),
      (LONG_PTR)NTE_NO_MEMORY},
    {_T("NTE_EXISTS: Object already exists."),
      (LONG_PTR)NTE_EXISTS},
    {_T("NTE_PERM: Access denied."),
      (LONG_PTR)NTE_PERM},
    {_T("NTE_NOT_FOUND: Object was not found."),
      (LONG_PTR)NTE_NOT_FOUND},
    {_T("NTE_DOUBLE_ENCRYPT: Data already encrypted."),
      (LONG_PTR)NTE_DOUBLE_ENCRYPT},
    {_T("NTE_BAD_PROVIDER: Invalid provider specified."),
      (LONG_PTR)NTE_BAD_PROVIDER},
    {_T("NTE_BAD_PROV_TYPE: Invalid provider type specified."),
      (LONG_PTR)NTE_BAD_PROV_TYPE},
    {_T("NTE_BAD_PUBLIC_KEY: Provider's public key is invalid."),
      (LONG_PTR)NTE_BAD_PUBLIC_KEY},
    {_T("NTE_BAD_KEYSET: Keyset does not exist."),
      (LONG_PTR)NTE_BAD_KEYSET},
    {_T("NTE_PROV_TYPE_NOT_DEF: Provider type not defined."),
      (LONG_PTR)NTE_PROV_TYPE_NOT_DEF},
    {_T("NTE_PROV_TYPE_ENTRY_BAD: Provider type as registered is invalid."),
      (LONG_PTR)NTE_PROV_TYPE_ENTRY_BAD},
    {_T("NTE_KEYSET_NOT_DEF: The keyset is not defined."),
      (LONG_PTR)NTE_KEYSET_NOT_DEF},
    {_T("NTE_KEYSET_ENTRY_BAD: Keyset as registered is invalid."),
      (LONG_PTR)NTE_KEYSET_ENTRY_BAD},
    {_T("NTE_PROV_TYPE_NO_MATCH: Provider type does not match registered value."),
      (LONG_PTR)NTE_PROV_TYPE_NO_MATCH},
    {_T("NTE_SIGNATURE_FILE_BAD: The digital signature file is corrupt."),
      (LONG_PTR)NTE_SIGNATURE_FILE_BAD},
    {_T("NTE_PROVIDER_DLL_FAIL: Provider DLL failed to initialize correctly."),
      (LONG_PTR)NTE_PROVIDER_DLL_FAIL},
    {_T("NTE_PROV_DLL_NOT_FOUND: Provider DLL could not be found."),
      (LONG_PTR)NTE_PROV_DLL_NOT_FOUND},
    {_T("NTE_BAD_KEYSET_PARAM: The Keyset parameter is invalid."),
      (LONG_PTR)NTE_BAD_KEYSET_PARAM},
    {_T("NTE_FAIL: An internal error occurred."),
      (LONG_PTR)NTE_FAIL},
    {_T("NTE_SYS_ERR: A base error occurred."),
      (LONG_PTR)NTE_SYS_ERR},
    {_T("NTE_SILENT_CONTEXT: Provider could not perform the action since the context was acquired as silent."),
      (LONG_PTR)NTE_SILENT_CONTEXT},
    {_T("NTE_TOKEN_KEYSET_STORAGE_FULL: The security token does not have storage space available for an additional container."),
      (LONG_PTR)NTE_TOKEN_KEYSET_STORAGE_FULL},
    {_T("NTE_TEMPORARY_PROFILE: The profile for the user is a temporary profile."),
      (LONG_PTR)NTE_TEMPORARY_PROFILE},
    {_T("NTE_FIXEDPARAMETER: The key parameters could not be set because the CSP uses fixed parameters."),
       (LONG_PTR)NTE_FIXEDPARAMETER},
    {_T("NTE_INVALID_HANDLE: The supplied handle is invalid."),
      (LONG_PTR)NTE_INVALID_HANDLE},
    {_T("NTE_INVALID_PARAMETER: The parameter is incorrect."),
      (LONG_PTR)NTE_INVALID_PARAMETER},
    {_T("NTE_BUFFER_TOO_SMALL: The buffer supplied to a function was too small."),
      (LONG_PTR)NTE_BUFFER_TOO_SMALL},
    {_T("NTE_NOT_SUPPORTED: The requested operation is not supported."),
      (LONG_PTR)NTE_NOT_SUPPORTED},
    {_T("NTE_NO_MORE_ITEMS: No more data is available."),
      (LONG_PTR)NTE_NO_MORE_ITEMS},
    {_T("NTE_BUFFERS_OVERLAP: The supplied buffers overlap incorrectly."),
      (LONG_PTR)NTE_BUFFERS_OVERLAP},
    {_T("NTE_DECRYPTION_FAILURE: The specified data could not be decrypted."),
      (LONG_PTR)NTE_DECRYPTION_FAILURE},
    {_T("NTE_INTERNAL_ERROR: An internal consistency check failed."),
      (LONG_PTR)NTE_INTERNAL_ERROR},
    {_T("NTE_UI_REQUIRED: This operation requires input from the user."),
      (LONG_PTR)NTE_UI_REQUIRED},
    {_T("NTE_HMAC_NOT_SUPPORTED: The cryptographic provider does not support HMAC."),
      (LONG_PTR)NTE_HMAC_NOT_SUPPORTED},
    };

    int num = XtNumber(errors);
    for (int i = 0; i<num; i++) {
      if (errors[i].value == errId) {
        message = errors[i].name;
        break;
      }

    }
    return message;
  }
};

}
