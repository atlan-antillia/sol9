/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SecurityAuthIdentity.h
 *
 *****************************************************************************/

// SOL9 2.0

// 2011/1/11

#pragma once
#include <sol/Object.h>
#include <sol/Exception.h>
#include <rpc.h>

/*
typedef struct _SEC_WINNT_AUTH_IDENTITY {
  unsigned short __RPC_FAR *User;
  unsigned long            UserLength;
  unsigned short __RPC_FAR *Domain;
  unsigned long            DomainLength;
  unsigned short __RPC_FAR *Password;
  unsigned long            PasswordLength;
  unsigned long            Flags;
} SEC_WINNT_AUTH_IDENTITY, *PSEC_WINNT_AUTH_IDENTITY;

*/

namespace SOL {

class SecurityAuthIdentity :public Object {

private:
  SEC_WINNT_AUTH_IDENTITY* credentials;

public:
  SecurityAuthIdentity(const TCHAR* user=NULL, const TCHAR* password=NULL, const TCHAR* domain=NULL)
  :credentials(NULL)
  {  
    if (user || password || domain) {
      credentials = (SEC_WINNT_AUTH_IDENTITY*) new BYTE[sizeof(SEC_WINNT_AUTH_IDENTITY)]; //credentials)];

      memset(credentials, '\0', sizeof(SEC_WINNT_AUTH_IDENTITY)); //credentials));
#ifdef UNICODE
      credentials->Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
      credentials->Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;   
#endif
      set(user, password, domain);
    }
  }


public:
  ~SecurityAuthIdentity()
  {
    if (credentials) {
      delete [] (BYTE*)credentials;
    }
  }

public:
  void set(const TCHAR* user=NULL, const TCHAR* password=NULL, const TCHAR* domain=NULL)
  {
    if (credentials) {
      if (user) {
#ifdef UNICODE
        credentials->User = (unsigned short*)user;
#else
        credentials->User = (unsigned char*)(void*)user; 
#endif
        credentials->UserLength = strlen(user);
      }
      if (password) {
#ifdef UNICODE
        credentials->Password = (unsigned short*) password;
#else
        credentials->Password = (unsigned char*) password;

#endif
        credentials->PasswordLength = strlen(password);

      }
      if (domain) {
#ifdef UNICODE
        credentials->Domain =(unsigned short*) domain;
#else
        credentials->Domain =(unsigned char*) domain;
#endif
        credentials->DomainLength = strlen(domain);
      }
    }
  }

public:
  bool hasUserName() 
  {
    bool rc = false;

    if (credentials->User && credentials->UserLength>0) {
      rc = true;
    }
    return rc;
  }

public:
  const TCHAR* getUser() 
  {
    const TCHAR* user=NULL;
    if (credentials) {
      user = (const TCHAR*)credentials->User;
    }
    return user;
  }

public:
  const TCHAR* getPassword() 
  {
    const TCHAR* password=NULL;
    if (credentials) {
      password = (const TCHAR*)credentials->Password;
    }
    return password;
  }

public:
  const TCHAR* getDomain() 
  {
    const TCHAR* domain=NULL;
    if (credentials) {
      domain = (const TCHAR*)credentials->Domain;
    }
    return domain;
  }

public:
  operator const SEC_WINNT_AUTH_IDENTITY*() const 
  {
    return credentials;
  }

public:
  const SEC_WINNT_AUTH_IDENTITY* getCredentials() const 
  {
    return credentials;
  }

public:
  void display()
  {
    _tprintf(_T("User    =%s\n"), getUser());
    _tprintf(_T("Password=%s\n"), getPassword());
    _tprintf(_T("Domain  =%s\n"), getDomain());

  }

};

}
