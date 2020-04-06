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
 *  UrlCacheGroup.h
 *
 *****************************************************************************/

// SOL9
// 2012/01/10

#pragma once

#include <sol/wininet/UrlCache.h>

namespace SOL {

class UrlCacheGroup :public UrlCache {
private:
  INTERNET_CACHE_GROUP_INFO* groupInfo;

private:
  GROUPID groupId;

public:

  UrlCacheGroup(GROUPID id)
  :groupInfo(NULL),
  groupId(id)
  {
    getUrlCacheGroupAttribute();

  }

public:
  ~UrlCacheGroup()
  {
    if (groupInfo) {
      delete [] groupInfo;
      groupInfo = NULL;
    }
  }

public:
/*
  The attributes parameter takes a one of the following values:

  CACHEGROUP_ATTRIBUTE_BASIC :Retrieves the flags, type, and disk quota attributes of the cache group. 
  CACHEGROUP_ATTRIBUTE_FLAG :Sets or retrieves the flags associated with the cache group.
  CACHEGROUP_ATTRIBUTE_GET_ALL :Retrieves all the attributes of the cache group.
   CACHEGROUP_ATTRIBUTE_GROUPNAME :Sets or retrieves the group name of the cache group.
   CACHEGROUP_ATTRIBUTE_QUOTA :Sets or retrieves the disk quota associated with the cache group.
   CACHEGROUP_ATTRIBUTE_STORAGE :Sets or retrieves the group owner storage associated with the cache group.
   CACHEGROUP_ATTRIBUTE_TYPE :Sets or retrieves the cache group type.
*/


  BOOL getUrlCacheGroupAttribute(__in  DWORD attributes=CACHEGROUP_ATTRIBUTE_GET_ALL)
  {
    DWORD groupInfoBytes = 0;
  
    BOOL rc = GetUrlCacheGroupAttribute(
      this->groupId,
        0, 
      attributes,
      NULL,
      &groupInfoBytes,
      NULL);
    if (groupInfoBytes > 0) {
      groupInfo = (INTERNET_CACHE_GROUP_INFO*)new BYTE[groupInfoBytes];
      if (groupInfo) {
        rc = GetUrlCacheGroupAttribute(
          this->groupId,
            0, 
          attributes,
          groupInfo,
          &groupInfoBytes,
          NULL);
      }
    }
    return rc;
  }

public:
  virtual void write(Writer& writer)
  {

    if (groupInfo) {
      writer.write(L"<UrlCacheGroup>\r\n");

      writer.write(L"<GroupName>%s</GroupName>\n", groupInfo->szGroupName);
      writer.write(L"<GroupId>%d</GroupId>\n", groupId);

      const wchar_t* flags = L"";
      if (groupInfo->dwGroupFlags == CACHEGROUP_FLAG_NONPURGEABLE) {
        flags = L"CACHEGROUP_FLAG_NONPURGEABLE";
      }
      writer.write(L"<GroupFlag>%s</GroupFlag>\n", flags);

      const wchar_t* type = L"";
      if (groupInfo->dwGroupType == CACHEGROUP_TYPE_INVALID) {
        type = L"CACHEGROUP_TYPE_INVALI";
      }

      writer.write(L"<GroupType>%d</GroupType>\r\n", groupInfo->dwGroupType );
      writer.write(L"<DiskUsage>%d KB</DiskUsage>\r\n", groupInfo->dwDiskUsage);
      writer.write(L"<DiskQuota>%d</DiskQuota>\r\n", groupInfo->dwDiskQuota);
        //DWORD dwOwnerStorage[GROUP_OWNER_STORAGE_SIZE];
      writer.write(L"</UrlCacheGroup>\r\n");
    }
  }

};

/*
typedef struct _INTERNET_CACHE_GROUP_INFO {
  DWORD dwGroupSize;
  DWORD dwGroupFlags;
  DWORD dwGroupType;
  DWORD dwDiskUsage;
  DWORD dwDiskQuota;
  DWORD dwOwnerStorage[GROUP_OWNER_STORAGE_SIZE];
  TCHAR szGroupName[GROUPNAME_MAX_LENGTH];
} INTERNET_CACHE_GROUP_INFO, *LPINTERNET_CACHE_GROUP_INFO;
*/

}
