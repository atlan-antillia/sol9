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
 *  NetUser.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol/nm/NetManager.h>
#include <sol/nm/GroupInfo.h>

#include <sol/nm/UserInfo.h>

namespace SOL {

class NetUser :public NetManager {

public:
  /**
   * Constructor
   */
  NetUser(const wchar_t* server=NULL)
    :NetManager(server)
  {
    
  }

public:
  int getLocalGroups(__in const wchar_t* userName,
    __in DWORD flags,
    __inout GroupInfo& groupInfo)
  {
    const wchar_t* serverName = getServerName();

    LPBYTE pbuffer = NULL;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    
    DWORD level = groupInfo.getLevel();

    NET_API_STATUS rc = NetUserGetLocalGroups((wchar_t*)serverName, (wchar_t*)userName,
        level, flags, 
        &pbuffer, 
        MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries);
    if (rc == NERR_Success) {
      groupInfo.setInfo(pbuffer, entriesRead, totalEntries);
    } else {
      throw (int)rc;
    }
    return rc;
  }

public:
  int getGroups(__in const wchar_t* userName,
    __inout GroupInfo& groupInfo)
  {
    const wchar_t* serverName = getServerName();

    LPBYTE pbuffer = NULL;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    
    DWORD level = groupInfo.getLevel();
    NET_API_STATUS rc = NetUserGetGroups((wchar_t*)serverName, (wchar_t*)userName, level,
        &pbuffer,
        MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries);
    if (rc == NERR_Success) {

      groupInfo.setInfo(pbuffer, entriesRead, totalEntries);

    } else {
      throw (int)rc;
    }

    return rc;
  }


public:
  /**
  @param filter  Specifies a filter of account types to enumerate. A value of zero implies all account types. 
    Allowable values are: 
 
    FILTER_TEMP_DUPLICATE_ACCOUNTS: Enumerates local user account data on a domain controller. 
    FILTER_NORMAL_ACCOUNT: Enumerates global user account data on a computer. 
    FILTER_INTERDOMAIN_TRUST_ACCOUNT: Enumerates domain trust account data on a domain controller. 
    FILTER_WORKSTATION_TRUST_ACCOUNT: Enumerates workstation or member server account data on a domain controller. 
    FILTER_SERVER_TRUST_ACCOUNT: Enumerates domain controller account data on a domain controller. 
  */
  int enumerate(__in DWORD filter,
    __inout UserInfo& userInfo)
  {
    const wchar_t* serverName = getServerName();

    LPBYTE pbuffer = NULL;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    
    DWORD level = userInfo.getLevel();
    NET_API_STATUS rc =  NetUserEnum((wchar_t*)serverName, level,
        filter,
        &pbuffer,
        MAX_PREFERRED_LENGTH, &entriesRead,&totalEntries, NULL);
    if (rc == NERR_Success) {

      userInfo.setInfo(pbuffer, entriesRead, totalEntries);

    } else {
      throw (int)rc;
    }

    return rc;
  }

public:
  int enumerateAll(__inout UserInfo& userInfo)
  {

    //Specify 0 to the second ffilter parameter

    DWORD filter = 0;
    return enumerate(filter, userInfo);
  }

};

}
