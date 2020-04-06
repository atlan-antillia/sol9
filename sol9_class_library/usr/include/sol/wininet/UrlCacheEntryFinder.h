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
 *  UrlCacheEntryFinder.h
 *
 *****************************************************************************/

// SOL9
// 2012/01/10

#pragma once

#include <sol/wininet/UrlCacheEntry.h>


namespace SOL {

class UrlCacheEntryFinder :public UrlCache
{
private:
  GROUPID groupId;

private:
  static const DWORD ALL_CACHE_ENTRY = 
    NORMAL_CACHE_ENTRY|COOKIE_CACHE_ENTRY|URLHISTORY_CACHE_ENTRY |SPARSE_CACHE_ENTRY|STICKY_CACHE_ENTRY;

public:
  UrlCacheEntryFinder(GROUPID id=0)
    :groupId(id)
  {
    //If groupId is 0, then it indicates search all non-grouped cache entries.
  }

public:
  GROUPID getGroupId()
  {
    return groupId;
  }

public:
  virtual bool findCookie(Writer& writer)
  {
    return find(COOKIE_CACHE_ENTRY, _T("cookie"), writer);
  }

public:
  virtual bool findVisited(Writer& writer)
  {
    return find(URLHISTORY_CACHE_ENTRY, _T("visited"), writer);
  }

public:
  virtual bool findAll(Writer& writer)
  {
    return find(ALL_CACHE_ENTRY, _T("all"), writer);
  }

public:
  virtual bool find(const String& type, Writer& writer)
  {
    DWORD  entryType = 0;
    if (type.equalsIgnoreCase(_T("cookie")) ) {
      //Find cookies
      entryType = COOKIE_CACHE_ENTRY;
    }
    else if (type.equalsIgnoreCase(_T("visited")) ) {
      //Find visited urls
      entryType = URLHISTORY_CACHE_ENTRY;
    }
    else if (type.equalsIgnoreCase(_T("all")) ) {
      //Find all cache entries
      entryType = ALL_CACHE_ENTRY;
    } else {
      return false;
    }
    return find(entryType, type, writer);
  }

public:
  virtual bool find(DWORD entryType, const String& type, Writer& writer)
  {
    DWORD cacheEntrySize = 0;

    DWORD filters = ALL_CACHE_ENTRY;
    //NORMAL_CACHE_ENTRY|COOKIE_CACHE_ENTRY|URLHISTORY_CACHE_ENTRY |SPARSE_CACHE_ENTRY|STICKY_CACHE_ENTRY;
    
    HANDLE hFind = FindFirstUrlCacheEntryEx(
          NULL, 0, filters,
          groupId, NULL, &cacheEntrySize,
          NULL, NULL, NULL);

    if(cacheEntrySize == 0) {
      if(hFind) {
        FindCloseUrlCache(hFind);
      }
      return  false;
    }
    writer.write(L"<UrlCacheEntryFinder EntryType=\"%s\">\r\n", (const TCHAR*)type);

    INTERNET_CACHE_ENTRY_INFO* entryInfo= (INTERNET_CACHE_ENTRY_INFO*) new BYTE[cacheEntrySize];
    //Specify NULL for the first parameter to the API FindFirstUrlCacheEntryEx to listup all entries.
    hFind = FindFirstUrlCacheEntryEx(
          NULL, 0, filters,
          groupId, entryInfo,  &cacheEntrySize,
          NULL, NULL, NULL);

    UrlCacheEntry cacheEntry = entryInfo;
    if (hFind) {
      cacheEntry.write(entryType, writer);
    }

    while (hFind) {

      cacheEntrySize = 0;
      
      BOOL rc = FindNextUrlCacheEntryEx(hFind, NULL, &cacheEntrySize, NULL, NULL, NULL);
      if (rc == FALSE) {
        DWORD err = GetLastError();
        if (err == ERROR_NO_MORE_ITEMS) {
          break;
        }
        if (err == ERROR_INSUFFICIENT_BUFFER) {
          entryInfo = (INTERNET_CACHE_ENTRY_INFO*) new BYTE[cacheEntrySize];
          rc = FindNextUrlCacheEntryEx(hFind, entryInfo, &cacheEntrySize, NULL, NULL, NULL);
          UrlCacheEntry cacheEntry = entryInfo;
          if (rc) {
            cacheEntry.write(entryType, writer);
          }
        }
      }
    }

    FindCloseUrlCache(hFind);
    writer.write(L"</UrlCacheEntryFinder>\r\n");

    return  true;
  }


};

}
