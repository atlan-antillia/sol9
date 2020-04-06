/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  UserInfo.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/NetInfo.h>

namespace SOL {

class UserInfo: public NetInfo {

public:
  /**
   * Constructor
   */
  UserInfo(int lv=0)
  :NetInfo(lv)
  {
  }

public:
  /**
   * Destructor
   */
  ~UserInfo()
  {
  }

protected:
  const wchar_t* getPrivilege (int value)
  {
    static const ArgT<wchar_t> types[] = {
    {L"Guest",USER_PRIV_GUEST}, 
    {L"User", USER_PRIV_USER},
    {L"Administrator", USER_PRIV_ADMIN} 
    };
    int count = XtNumber(types);

    const wchar_t* name= L"";
    for (int i=0; i<count; i++) {
      if (types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

protected:
  const wchar_t* getHexString(LPBYTE bytes, size_t size, __out StringBufferT<wchar_t>& buffer)
  {

    for (size_t i = 0; i<size; i++) {
      wchar_t p[10];
      swprintf_s(p, CountOf(p), L"%02x ", (BYTE)bytes[i]);
      buffer.append(p);
    }
    return (const wchar_t*)buffer;  
  }

protected:
  const wchar_t* getFlags(DWORD value, __out StringBufferT<wchar_t>& buffer)
  {
    static const ArgT<wchar_t> types[] = {

    {L"SCRIPT", UF_SCRIPT},
      //The logon script executed. This value must be set.
    {L"ACCOUNTDISABLE", UF_ACCOUNTDISABLE},
      // The user's account is disabled.
    {L"HOMEDIR_REQUIRED", UF_HOMEDIR_REQUIRED},
      // The home directory is required. This value is ignored.
 
    {L"PASSWD_NOTREQD", UF_PASSWD_NOTREQD},
      // No password is required.
 
    {L"PASSWD_CANT_CHANGE", UF_PASSWD_CANT_CHANGE}, 
      //The user cannot change the password.
 
    {L"LOCKOUT", UF_LOCKOUT},  
      //The account is currently locked out. 
      //You can call the NetUserSetInfo function to clear this value and unlock a previously locked account. You cannot use this value to lock a previously unlocked account.
 
    {L"DONT_EXPIRE_PASSWD", UF_DONT_EXPIRE_PASSWD}, 
      //The password should never expire on the account.
 
    {L"ENCRYPTED_TEXT_PASSWORD_ALLOWED", UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED},
      // The user's password is stored under reversible encryption in the Active Directory.
 
    {L"NOT_DELEGATED", UF_NOT_DELEGATED},
      // Marks the account as "sensitive"; other users cannot act as delegates of this user account.
 
    {L"SMARTCARD_REQUIRED", UF_SMARTCARD_REQUIRED}, 
      // Requires the user to log on to the user account with a smart card.
 
    {L"USE_DES_KEY_ONLY", UF_USE_DES_KEY_ONLY},  
      //Restrict this principal to use only Data Encryption Standard (DES) encryption types for keys.
 
    {L"DONT_REQUIRE_PREAUTH", UF_DONT_REQUIRE_PREAUTH},  
      //This account does not require Kerberos preauthentication for logon.
 
    {L"TRUSTED_FOR_DELEGATION", UF_TRUSTED_FOR_DELEGATION},
      // The account is enabled for delegation. This is a security-sensitive setting; accounts with this option enabled should be tightly controlled. This setting allows a service running under the account to assume a client's identity and authenticate as that user to other remote servers on the network.
 
    {L"PASSWORD_EXPIRED", UF_PASSWORD_EXPIRED},
      // The user's password has expired.//Windows 2000:  This value is not supported. 

    {L"TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION", UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION}, 
      //The account is trusted to authenticate a user outside of the Kerberos security package and delegate that user through constrained delegation. This is a security-sensitive setting; accounts with this option enabled should be tightly controlled. This setting allows a service running under the account to assert a client's identity and authenticate as that user to specifically configured services on the network.
      //Windows XP/2000:  This value is not supported. 

    {L"NORMAL_ACCOUNT", UF_NORMAL_ACCOUNT}, 
      // This is a default account type that represents a typical user.
 
    {L"TEMP_DUPLICATE_ACCOUNT", UF_TEMP_DUPLICATE_ACCOUNT}, 
      // This is an account for users whose primary account is in another domain. This account provides user access to this domain, but not to any domain that trusts this domain. The User Manager refers to this account type as a local user account.
 
    {L"WORKSTATION_TRUST_ACCOUNT", UF_WORKSTATION_TRUST_ACCOUNT},  
      //This is a computer account for a computer that is a member of this domain.
 
    {L"SERVER_TRUST_ACCOUNT", UF_SERVER_TRUST_ACCOUNT},
      // This is a computer account for a backup domain controller that is a member of this domain.
 
    {L"INTERDOMAIN_TRUST_ACCOUNT", UF_INTERDOMAIN_TRUST_ACCOUNT},
      // This is a permit to trust account for a domain that trusts other domains.
     };

    int count = XtNumber(types);
    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (types[i].value & value) {
        if (matched>0) {
          buffer.append(L" | ");
        }
        buffer.append(types[i].name);
        matched++;
      }
    }
    return (const wchar_t*)buffer;
  }

protected:
  const wchar_t* getAuthFlags(DWORD value, __out StringBufferT<wchar_t>& buffer)
  {
    static const ArgT<wchar_t> types[] = {

    {L"OP_PRINT", AF_OP_PRINT}, //The print operator privilege is enabled.
 
    {L"OP_COMM", AF_OP_COMM}, //The communications operator privilege is enabled.
 
    {L"OP_SERVER", AF_OP_SERVER}, //The server operator privilege is enabled.
 
    {L"OP_ACCOUNTS", AF_OP_ACCOUNTS} //The accounts operator privilege is enabled.
 
    };

    int count = XtNumber(types);
    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (types[i].value & value) {
        if (matched>0) {
          buffer.append(L" | ");
        }
        buffer.append(types[i].name);
        matched++;
      }
    }
    return (const wchar_t*)buffer;
  }

};

}
