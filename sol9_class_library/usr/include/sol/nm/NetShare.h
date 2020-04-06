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
 *  NetShare.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol/nm/NetManager.h>
#include <sol/nm/ShareInfo.h>

namespace SOL {

class NetShare :public NetManager {

public:
  /**
   * Constructor
   */
  NetShare(const wchar_t* server=NULL)
    :NetManager(server)
  {
    
  }

public:
  int enumerate(__inout ShareInfo& shareInfo)
  {
    const wchar_t* serverName= getServerName();
    LPBYTE pbuffer;  
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    DWORD resumeHandle = 0;
    
    DWORD level = shareInfo.getLevel();

    NET_API_STATUS rc = NetShareEnum((wchar_t*)serverName,
      level,
        &pbuffer,
        MAX_PREFERRED_LENGTH,
        &entriesRead,
        &totalEntries,
       NULL);//&resumeHandle);

    if (rc == NERR_Success) {    
      shareInfo.setInfo(pbuffer, entriesRead, totalEntries);
    } else {
      printf("Failed to call NetShareEnum: %d\n", rc);
      throw (int)rc;
    }
    return rc;
  }

public:
  int add(__in ShareInfo& shareInfo)
  {
    const wchar_t* serverName= getServerName();

    DWORD level    = shareInfo.getLevel();
    LPBYTE pbuffer = shareInfo.getBuffer();

    NET_API_STATUS rc = NetShareAdd((wchar_t*)serverName, level,
          pbuffer, NULL);

    if (rc == NERR_Success) {
      ;//OK
    } else {
      printf("Failed to call NetShareAdd: %d\n", rc);
      throw (int)rc;
    }
    return rc;

  }

public:
  int setInfo(__in const wchar_t* netName, __in ShareInfo& shareInfo)
  {
    const wchar_t* serverName = getServerName();

    DWORD level    = shareInfo.getLevel();
    LPBYTE pbuffer = shareInfo.getBuffer();

    NET_API_STATUS rc = NetShareSetInfo((wchar_t*)serverName, (wchar_t*)netName, level,
          pbuffer, NULL);

    if (rc == NERR_Success) {
      ;//OK
    } else {
      printf("Failed to call NetShareSetInfo: %d\n", rc);
      throw (int)rc;
    }
    return rc;

  }

public:
  int remove(__in const wchar_t* netName)
  {
    const wchar_t* serverName = getServerName();

    NET_API_STATUS rc = NetShareDel((wchar_t*)serverName, (wchar_t*)netName, NULL);

    if (rc == NERR_Success) {
      ;//OK
    } else {
      printf("Failed to call NetShareDel: %d\n", rc);
      throw (int)rc;
    }
    return rc;

  }

};

}
