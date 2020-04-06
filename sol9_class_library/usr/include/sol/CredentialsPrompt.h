/******************************************************************************
 *
 * Copyright (c) 2009-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  CredentialsPrompt.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/10
// 2012/06/22

#pragma once

#include <sol/Object.h>
#include <sol/String.h>

#include <wincred.h> 

#pragma comment (lib, "credui.lib")

namespace SOL {

class CredentialsPrompt :public Object {

  
public:
  /**
   * Constructor
   */
  CredentialsPrompt()
  {
  }  

public:
  /**
   * Input username and password from a command line(console).
   */
  int  show(__inout String& username, 
        __inout String& password, 
        __in_opt const TCHAR* targetForCredentials = _T("Server"),
        __in_opt BOOL fSave= FALSE, 
        __in_opt DWORD dwFlags = (CREDUI_FLAGS_DO_NOT_PERSIST|
          CREDUI_FLAGS_EXCLUDE_CERTIFICATES) )
  {
    int rc = -1;
    TCHAR name[CREDUI_MAX_USERNAME_LENGTH+1];

    TCHAR passwd[CREDUI_MAX_PASSWORD_LENGTH+1];
    SecureZeroMemory(name, CountOf(name));
    SecureZeroMemory(passwd, CountOf(passwd));

    // If username parameter has been set, copy the string from username String to name buffer.
    int ulen = username.getLength();
    int plen = password.getLength();
    if (ulen >CREDUI_MAX_USERNAME_LENGTH) {
      //Trimming username
      ulen = CREDUI_MAX_USERNAME_LENGTH;
    }
    if (ulen> 0) {
      strncpy_s(name, CountOf(name), (const TCHAR*)username, ulen);
    }

    // If password parameter has been set, copy the string from password String to passwd buffer.
    if (plen >CREDUI_MAX_PASSWORD_LENGTH) {
      //Trimming
      plen = CREDUI_MAX_PASSWORD_LENGTH;
    }
    if (plen> 0) {
      strncpy_s(passwd, CountOf(passwd), (const TCHAR*)password, plen);
    }

    if ((rc = CredUICmdLinePromptForCredentials( 
        targetForCredentials,
        NULL,         // Reserved
        0,            // Reason
        name,  
        CREDUI_MAX_USERNAME_LENGTH+1, 
        passwd,
        CREDUI_MAX_PASSWORD_LENGTH+1,
        &fSave,  
        dwFlags))== NO_ERROR) {

      //OK
      username = name;
      password = passwd;

      SecureZeroMemory(name, CountOf(name));
      SecureZeroMemory(passwd, CountOf(passwd));
    } else {
      // May be Cancelled
      username = "";
      password = "";
    }
    return rc;
  }
};

}
