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
 *  NetUse.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol/nm/NetManager.h>

#include <sol/nm/UseInfo.h>

namespace SOL {

class NetUse :public NetManager {

public:
  /**
   * Constructor
   */
  NetUse(const wchar_t* uncServer=NULL)
    :NetManager(uncServer)
  {
    
  }


public:
  /**
  */
  int enumerate(__inout UseInfo& useInfo)
  {
    const wchar_t* serverName = getServerName();

    LPBYTE pbuffer = NULL;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    
    DWORD level = useInfo.getLevel();
    NET_API_STATUS rc =  NetUseEnum((wchar_t*)serverName, level,
        &pbuffer,
        MAX_PREFERRED_LENGTH, &entriesRead,&totalEntries, NULL);
    if (rc == NERR_Success) {
      useInfo.setInfo(pbuffer, entriesRead, totalEntries);

    } else {
      throw (int)rc;
    }

    return rc;
  }
};

}
