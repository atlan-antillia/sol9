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
 *  ProcessGroups.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/12

#pragma once
#include <sol/Object.h>
#include <sol/String.h>
#include <sol/StringBuffer.h>
#include <sol/Arg.h>
#include <sol/AccountSid.h>

#include <psapi.h>
#include <sddl.h>

namespace SOL {

class ProcessGroups :public Object {


/*
typedef struct _TOKEN_GROUPS {
  DWORD              GroupCount;
  SID_AND_ATTRIBUTES Groups[ANYSIZE_ARRAY];
}TOKEN_GROUPS, *PTOKEN_GROUPS;

typedef struct _SID_AND_ATTRIBUTES {
  PSID  Sid;
  DWORD Attributes;
}SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

The Attributes members of the SID_AND_ATTRIBUTES 

SE_GROUP_ENABLED 
SE_GROUP_ENABLED_BY_DEFAULT
SE_GROUP_INTEGRITY
SE_GROUP_INTEGRITY_ENABLED
SE_GROUP_LOGON_ID
SE_GROUP_MANDATORY
SE_GROUP_OWNER
SE_GROUP_RESOURCE
SE_GROUP_USE_FOR_DENY_ONLY
*/


private:
  PTOKEN_GROUPS pToken;

public:
  ProcessGroups()
    :pToken(NULL)
  {

  }

public:
  ~ProcessGroups()
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

    GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS)TokenGroups, NULL, dwSize, &dwSize);
        
    pToken = (TOKEN_GROUPS*)new char[dwSize];


    if (GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS)TokenGroups, pToken, dwSize, &dwSize) ) {
      rc = true;    
    }
    
    return rc;
  }


private:
  int  getAttributes(int value, String& attrs)
  {
    static const Arg types[] = {
    {_T("GROUP_ENABLED"),            SE_GROUP_ENABLED},
    {_T("GROUP_ENABLED_BY_DEFAULT"), SE_GROUP_ENABLED_BY_DEFAULT},
    {_T("GROUP_INTEGRITY"),          SE_GROUP_INTEGRITY },
    {_T("GROUP_INTEGRITY_ENABLED"),  SE_GROUP_INTEGRITY_ENABLED},
    {_T("GROUP_LOGON_ID"),           SE_GROUP_LOGON_ID},
    {_T("GROUP_MANDATORY"),          SE_GROUP_MANDATORY},
    {_T("GROUP_OWNER"),              SE_GROUP_OWNER}
    };
    int num = 0;
    int count = XtNumber(types);
    StringBuffer buffer;
    const TCHAR* name = _T("");
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value & value) {
        name = types[i].name;
        buffer.append(name);
        buffer.append(_T(","));
        num++;
      }
    }
    attrs= (const TCHAR*)buffer;

    return num;
  }

public:
  void display(SID_AND_ATTRIBUTES& attr) 
  {
    AccountSid accountSid;

    String user = "";
    String domain = "";
    String type  = "";
    if (accountSid.lookup(attr.Sid, user, domain, type)) {
      _tprintf(_T("ProcessGroups Name:%s Attributes:%lu\n"), (const TCHAR*)user, 
          attr.Attributes);

    }    
  }
public:
  void display()
  {
    if (pToken) {

      for (size_t i = 0; i<pToken->GroupCount; i++) {
        display(pToken->Groups[i]);
      }
    }
  }

};

}
