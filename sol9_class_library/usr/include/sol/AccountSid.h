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
 *  AccountSid.h
 *
 *****************************************************************************/

// 2009/09/14

#pragma once
#include <sol/Object.h>
#include <sol/String.h>
#include <sol/Arg.h>
#include <psapi.h>
#include <sddl.h>


namespace SOL {

class AccountSid :public Object {

private:
  String computerName;

public:
  AccountSid(const TCHAR* computer=_T("\\\\."))
  :computerName(computer)
  {

  }


private:
  const TCHAR* getSidNameUse(int value)
  {
    static const Arg types[] = {
    {_T("User"),           SidTypeUser}, 
    {_T("Group"),          SidTypeGroup},
    {_T("Domain"),         SidTypeDomain}, 
    {_T("Alias"),          SidTypeAlias}, 
    {_T("WellKnownGroup"), SidTypeWellKnownGroup}, 
    {_T("DeletedAccount"), SidTypeDeletedAccount}, 
    {_T("TypeInvalid"),    SidTypeInvalid}, 
    {_T("Unknown"),        SidTypeUnknown}, 
    {_T("Computer"),       SidTypeComputer}, 
    {_T("Label"),          SidTypeLabel}
    };

    int count = XtNumber(types);
    const TCHAR* name = _T("");

    for (int i = 0; i<count; i++) {

      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }

    return name;
  }


public:
  bool lookup(__in PSID pSID,
    __out String& user,
    __out String& domain,
    __out String& type)
  {
    bool rc = false;
      
    TCHAR userId[1024];   //2012/06/25
    TCHAR domainId[1024]; //2012/06/25
        
    DWORD cbUserId = CountOf(userId);     //2012/06/22        
    DWORD cbDomainId = CountOf(domainId); //2012/06/22

    SID_NAME_USE snu; 

    if (LookupAccountSid((const TCHAR*)computerName, // name of local or remote computer
        pSID,               // security identifier
        userId,                // account name buffer
        &cbUserId,             // size of account name buffer
         domainId,              // domain name
        &cbDomainId,           // size of domain name buffer
        &snu                // SID type
        )) {

      rc     = true;
      user   = userId;
      domain = domainId;
      type   = getSidNameUse(snu);

      //printf("SAM account form of %s %s %d\n", domainId, userId, snu);
    }
    else {
      printf("Could not locate SID %d\n", GetLastError());
    }
    return rc;
  }

};

}
