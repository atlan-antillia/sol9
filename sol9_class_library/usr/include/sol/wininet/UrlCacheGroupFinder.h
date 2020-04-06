/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  UrlCacheGroupFinder.h
 *
 *****************************************************************************/

// SOL9
// 2012/01/10

#pragma once

#include <sol/wininet/UrlCacheGroup.h>


namespace SOL {

class UrlCacheGroupFinder :public UrlCache 
{

public:
  UrlCacheGroupFinder()
  {
  }

public:
  virtual bool find(Writer& writer)
  {
    GROUPID  groupId = 0;
    HANDLE hFind = FindFirstUrlCacheGroup(0, CACHEGROUP_SEARCH_ALL, NULL, 0,
        &groupId, NULL);

    if(hFind == NULL) {
      return  false;
    }
  
    writer.write(L"<UrlCacheGroupFinder>\r\n");

    UrlCacheGroup cacheGroup = groupId;
    cacheGroup.write(writer);
    bool looping = true;
    while(looping) {
      BOOL rc = FindNextUrlCacheGroup(hFind,&groupId, NULL);
      if (rc == FALSE) {
        break;
      }
      UrlCacheGroup cacheGroup =groupId;
      cacheGroup.write(writer);
    }

    FindCloseUrlCache(hFind);
    writer.write(L"</UrlCacheGroupFinder>\r\n");

    return  true;
  }

};

}
