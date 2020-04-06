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
 *  ProcessUser.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/12

#pragma once
#include <sol/Object.h>
#include <sol/String.h>
#include <sol/Arg.h>
#include <sol/AccountSid.h>

#include <psapi.h>
#include <sddl.h>

namespace SOL {

class ProcessUser :public Object {

/*
typedef struct _TOKEN_USER {
  SID_AND_ATTRIBUTES User;
}TOKEN_USER, *PTOKEN_USER;

typedef struct _SID_AND_ATTRIBUTES {
  PSID  Sid;
  DWORD Attributes;
}SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

*/

private:
  PTOKEN_USER pToken;

public:
  ProcessUser()
    :pToken(NULL)
  {

  }

public:
  ~ProcessUser()
  {
    clear();
  }

private:
  void clear()
  {
    if (pToken) {
      delete [] (char*)pToken;
      pToken = NULL;
    }
  }

public:
  bool getInformation(HANDLE hToken) 
  {
    bool rc = false;

    clear();
    DWORD dwSize = 0;

    GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS)TokenUser, NULL, dwSize, &dwSize);
      
    pToken = (TOKEN_USER*)new char[dwSize];

    if (GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS)TokenUser, pToken, dwSize, &dwSize)) {
      rc = true;    
    }
    return rc;
  }


public:
  void display()
  {
    if (pToken) {
      AccountSid accountSid;
      String user;
      String domain;
      String type;
      if (accountSid.lookup(pToken->User.Sid, user, domain, type)) {
        _tprintf(_T("ProcessUser Domain: %s\n"), (const TCHAR*)domain);
        _tprintf(_T("ProcessUser User: %s\n"), (const TCHAR*)user);
        _tprintf(_T("ProcessUser Type: %s\n"), (const TCHAR*)type);

      }
    }
  }

};

}
