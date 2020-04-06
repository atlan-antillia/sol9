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
 *  NetServer.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol/nm/NetManager.h>
#include <sol/nm/ServerInfo.h>

namespace SOL {

class NetServer :public NetManager {

public:
  /**
   * Constructor
   */
  NetServer(const wchar_t* server=NULL)
    :NetManager(server)
  {
    
  }


public:
  int enumerate(__in const wchar_t* domain, __inout ServerInfo& shareInfo)
  {
    const wchar_t* serverName = getServerName();
    LPBYTE pbuffer;  
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    DWORD resumeHandle = 0;
    
    DWORD serverType  =  SV_TYPE_ALL;

    NET_API_STATUS rc = NetServerEnum((wchar_t*)serverName, shareInfo.getLevel(),
        &pbuffer,
        MAX_PREFERRED_LENGTH,
        &entriesRead,
        &totalEntries,
      serverType,
      (wchar_t*)domain,
       NULL);//&resumeHandle);

    if (rc == NERR_Success) {    
      shareInfo.setInfo(pbuffer, entriesRead, totalEntries);
    } else {
      printf("Failed to call NetServerEnum: %d\n", rc);
      throw (int)rc;
    }
    return rc;
  }

};

}
