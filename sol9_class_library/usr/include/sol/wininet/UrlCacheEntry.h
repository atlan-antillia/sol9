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
 *  UrlCacheEntry.h
 *
 *****************************************************************************/

// SOL9
// 2012/01/20
// 2012/07/03

#pragma once

#include <sol/wininet/UrlCache.h>

namespace SOL {


class UrlCacheEntry :public UrlCache 
{

private:
  _bstr_t sourceUrlName;

  INTERNET_CACHE_ENTRY_INFO* cacheEntry;

public:
  UrlCacheEntry()
  :cacheEntry(NULL)
  {
  }

public:
  UrlCacheEntry(INTERNET_CACHE_ENTRY_INFO* info)
  :cacheEntry(info)
  {
    if (info == NULL) {
      throw NullPointerException("INTERNET_CACHE_ENTRY_INFO pointer is NULL");
    }
  }

public:
  UrlCacheEntry(__in const TCHAR* url)
  :cacheEntry(NULL)
  {
    DWORD entrySize = 0;

    BOOL rc = GetUrlCacheEntryInfo((const TCHAR*)url, NULL, &entrySize);

    DWORD err = GetLastError();
    if (err == ERROR_FILE_NOT_FOUND ) {
      throw Exception(err, _T("FileNotFound: %s"), url);
    }

    if (entrySize > 0) {
      cacheEntry = (INTERNET_CACHE_ENTRY_INFO*) new BYTE[entrySize];
      if (cacheEntry){
        memset(cacheEntry, (TCHAR)0, entrySize);

        if ((rc = GetUrlCacheEntryInfo(url, cacheEntry, &entrySize)) == FALSE) {
          throw rc;
        }
      }
    }
  }


public:
  ~UrlCacheEntry()
  {
    if (cacheEntry) {
      delete [] cacheEntry;
      cacheEntry = NULL;
    }    
  }

public:

  BOOL create(__in const TCHAR* sourceUrl,
      __in DWORD expectedFileSize,
        __in const TCHAR* fileExtension,
      __out _bstr_t& localFileName)
  {
    this->sourceUrlName = "";

    TCHAR buffer[1024];    

    BOOL rc = CreateUrlCacheEntry(sourceUrl,
        expectedFileSize,
        fileExtension,
        buffer, 0);
    if (rc) {
      this->sourceUrlName = sourceUrl;
      localFileName = buffer;
    }
    return rc;
  }

public:
  BOOL commit(const TCHAR* localFileName,
        FILETIME expireTime,
        FILETIME lastModifiedTime,
        DWORD  cacheEntryType,
        BYTE* headerInfo=NULL,   //2012/07/03
        DWORD headerSize = 0,
        const TCHAR* fileExtension=NULL)
  {
    return CommitUrlCacheEntry(
        sourceUrlName,
        localFileName,
        expireTime,
        lastModifiedTime,
        cacheEntryType,
        headerInfo,
        headerSize,
        fileExtension,
        0);

  }
/*
COOKIE_CACHE_ENTRY  
NORMAL_CACHE_ENTRY  
OCX_CACHE_ENTRY  
SPARSE_CACHE_ENTRY  
STABLE_CACHE_ENTRY  
STICKY_CACHE_ENTRY  
TRACK_CACHE_ENTRY  
TRACK_OFFLINE_CACHE_ENTRY  
TRACK_ONLINE_CACHE_ENTRY  
URLHISTORY_CACHE_ENTRY  
*/

public:
  BOOL remove(__in const TCHAR* url)
  {
    BOOL rc = DeleteUrlCacheEntry(url);
    if (rc == FALSE) {
      DWORD err = GetLastError();
      if (err == ERROR_FILE_NOT_FOUND ) {
        throw Exception(err, _T("UrlCacheEntry::remove(), FileNotFound: %s"), url);
      }
      if (err == ERROR_ACCESS_DENIED ) {
        throw Exception(err, _T("UrlCacheEntry::remove(), AccessDenied to %s"), url);
      }
    }
    return rc;
  }


protected:
  INTERNET_CACHE_ENTRY_INFO* getCacheEntry()
  {
      return cacheEntry;
  }

public:
  bool getLocalFileName(__out _bstr_t& localFileName)
  {
    bool rc = false;

    localFileName = "";

    if (cacheEntry){
      localFileName = cacheEntry->lpszLocalFileName;
      rc = true;
    }    
    return rc;
  }


public:
  bool hasLocalFileName()
  {
    bool rc = false;
    if (cacheEntry){
      if (cacheEntry->lpszLocalFileName) {
        rc = true;
      }
    }    
    return rc;
  }

public:
  bool getLocalFileName(__out _bstr_t& fullPath, __out _bstr_t& fileName, __out _bstr_t& extension)
  {
    bool rc = false;
    fullPath = "";
    fileName = "";
    extension = "";

    if (cacheEntry){
      // 
      if (cacheEntry->lpszLocalFileName) {
        //OK
        fullPath = cacheEntry->lpszLocalFileName;
        const wchar_t* w= (const wchar_t*)fullPath;
        if (w) {
          const wchar_t* bslash = strrchr(w, (wchar_t)'\\');
          //Get file name only
          if (bslash) {
            fileName = ++bslash;
          }

          //Get file extension by finding '.'. 
          const wchar_t* dot = strrchr(w, (wchar_t)'.');
          if (dot) {
            extension = ++dot;
          }
        }
        rc = true;
      }
    }    
    return rc;
  }


public:
  bool getHTMLEncodedSourceUrl(__out _bstr_t& bsourceUrlName)
  {
    bool rc = false;
    if (cacheEntry) {
      HTMLEncoder encoder;
      encoder.encode(cacheEntry->lpszSourceUrlName, bsourceUrlName);
      rc = true;
    }
    return rc;
  }

public:
  bool getSourceUrlName(__out _bstr_t& sourceUrlName)
  {
    bool rc = false;

    sourceUrlName = "";

    if (cacheEntry){
      sourceUrlName = cacheEntry->lpszSourceUrlName;
      rc = true;
    }
    return rc;
  }


public:
  bool isCookieEntry() 
  {
    bool rc = false;
    if (getCacheEntryType() & COOKIE_CACHE_ENTRY) {
      rc = true;
    }
    return rc;
  }

public:
  bool isUrlHistryEntry() 
  {
    bool rc = false;
    if (getCacheEntryType() & URLHISTORY_CACHE_ENTRY) {
      rc = true;
    }
    return rc;
  }

  

public:
  DWORD getCacheEntryType()
  {
    DWORD type = 0;
    if (cacheEntry) {
      type = cacheEntry->CacheEntryType;
    }
    return type;
  }

public:
  DWORD getHitRate()
  {
    DWORD hitRate = 0;
    if (cacheEntry){
      hitRate = cacheEntry->dwHitRate;
    }
    return hitRate;
  }

public:
  virtual void write(DWORD type, Writer& writer)
  {
    if (cacheEntry) {
      if (cacheEntry->CacheEntryType & type) {
        //If cacheEntry's CacheEntryType has a valid bitmask for type parameter, 
        //then show all properties of the cacheEntry.
        write(writer);
      }
    }
  }

public:
  //show all properties of the cacheEntry.
  virtual void write(Writer& writer)
  {
    writer.writeln(L"<UrlCacheEntry>");

    HTMLEncoder encoder;

    _bstr_t bsourceUrlName;
    _bstr_t bfileName;
    encoder.encode(cacheEntry->lpszSourceUrlName, bsourceUrlName);
    encoder.encode(cacheEntry->lpszLocalFileName, bfileName);

    //_tprintf(_T("<StructSize>%ld</StructSize>\r\n"),  cacheEntry->dwStructSize);
    writer.writeln(L"<SourceUrlName>%s</SourceUrlName>",  (const wchar_t*)bsourceUrlName);
    writer.writeln(L"<LocalFileName>%s</LocalFileName>",  (const wchar_t*)bfileName);

    StringT<TCHAR> type;

    writer.writeln(L"<CacheEntryType>%s</CacheEntryType>",  getCacheEntryType(cacheEntry->CacheEntryType, type) );
    writer.writeln(L"<UseCount>%d</UseCount>",  cacheEntry->dwUseCount);
    writer.writeln(L"<HitRate>%d</HitRate>",  cacheEntry->dwHitRate);

    __int64 fileSizeHigh = cacheEntry->dwSizeHigh;
    __int64 fileSizeLow  = cacheEntry->dwSizeLow;
    __int64 fileSize = fileSizeHigh<<32 | fileSizeLow;
    
    TCHAR buffer[256];
    int bsize = sizeof(buffer)/sizeof(buffer[0]);
    memset(buffer, (TCHAR)0, bsize);
    StrFormatKBSize(fileSize, buffer, bsize);
    writer.writeln(L"<FileSize>%s</FileSize>", buffer);
    
    _bstr_t lastModifiedTime;
    _bstr_t expireTime;
    _bstr_t lastAccessTime;
    _bstr_t lastSyncTime;

    FileTime fileTime1(cacheEntry->LastModifiedTime);
    FileTime fileTime2(cacheEntry->ExpireTime);
    FileTime fileTime3(cacheEntry->LastAccessTime);
    FileTime fileTime4(cacheEntry->LastSyncTime);

    writer.writeln(L"<LastModifiedTime>%s</LastModifiedTime>",  fileTime1.toString(lastModifiedTime));
    writer.writeln(L"<ExpireTime>%s</ExpireTime>",  fileTime2.toString(expireTime));
    writer.writeln(L"<LastAccessTime>%s</LastAccessTime>",  fileTime3.toString(lastAccessTime));
    writer.writeln(L"<LastSyncTime>%s</LastSyncTime>",  fileTime4.toString(lastSyncTime));

    writer.writeln(L"<HeaderInfoSize>%d</HeaderInfoSize>", cacheEntry->dwHeaderInfoSize);
    
    if (cacheEntry->dwHeaderInfoSize>0) {
      WideCharArray warray;
      warray.shallowCopy((wchar_t*)cacheEntry->lpHeaderInfo, cacheEntry->dwHeaderInfoSize);
      if (warray.isString()) {
        writer.writeln(L"<HeaderInfo>%s</HeaderInfo>", cacheEntry->lpHeaderInfo);
      } else {
        Bytes bytes;
        bytes.shallowCopy((unsigned char*)cacheEntry->lpHeaderInfo, cacheEntry->dwHeaderInfoSize);
        _bstr_t header;
        writer.writeln(L"<HeaderInfo>%s</HeaderInfo>", bytes.toHexString(header));
        bytes.nullify();
      }    
      warray.nullify();
    }
    
    writer.writeln(L"<FileExtension>%s</FileExtension>",  cacheEntry->lpszFileExtension);
    writer.writeln(L"</UrlCacheEntry>");
  }

public:
  virtual void writeSourceUrl(DWORD type, Writer& writer)
  {
    if (cacheEntry) {
      if (cacheEntry->CacheEntryType & type) {
        //If cacheEntry's CacheEntryType has a valid bitmask for type parameter, then display the cacheEntry.
        writeSourceUrl(writer);
      }
    }
  }

public:
  virtual void writeSourceUrl(Writer& writer)
  {
    HTMLEncoder encoder;

    _bstr_t bsourceUrlName;
    encoder.encode(cacheEntry->lpszSourceUrlName, bsourceUrlName);
    writer.writeln(L"<SourceUrlName>%s</SourceUrlName>",  (const wchar_t*)bsourceUrlName);
  }

protected:
  const TCHAR* getCacheEntryType(DWORD type, StringT<TCHAR>& string)
  {
    static const ArgT<TCHAR> types[] = {
      {_T("EditedCacheEntry"),     EDITED_CACHE_ENTRY},
      {_T("SparseCacheEntry"),     SPARSE_CACHE_ENTRY}, 
      {_T("StickyCacheEntry"),     STICKY_CACHE_ENTRY}, 
      {_T("TrackOfflineCacheEntry"),   TRACK_OFFLINE_CACHE_ENTRY}, 
      {_T("TrackOnlineCacheEntry"),   TRACK_ONLINE_CACHE_ENTRY},
      {_T("CookieCacheEntry"),     COOKIE_CACHE_ENTRY }, 
      {_T("NormalCacheEntry"),     NORMAL_CACHE_ENTRY }, 
      {_T("UrlHistoryCacheEntry"),   URLHISTORY_CACHE_ENTRY }, 
    };

    StringBufferT<TCHAR> buffer;
    int c = 0;

    for (int i = 0; i<CountOf(types); i++) {
      if (type & types[i].value) {
        if (c > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(types[i].name);
        c++;
      }
    }
    string = buffer.getBuffer();
    return (const TCHAR*)string;
  }

};

/*
typedef struct _INTERNET_CACHE_ENTRY_INFO {
  DWORD    dwStructSize;
  LPTSTR   lpszSourceUrlName;
  LPTSTR   lpszLocalFileName;
  DWORD    CacheEntryType;
  DWORD    dwUseCount;
  DWORD    dwHitRate;
  DWORD    dwSizeLow;
  DWORD    dwSizeHigh;
  FILETIME LastModifiedTime;
  FILETIME ExpireTime;
  FILETIME LastAccessTime;
  FILETIME LastSyncTime;
  LPBYTE   lpHeaderInfo;
  DWORD    dwHeaderInfoSize;
  LPTSTR   lpszFileExtension;
  union {
    DWORD dwReserved;
    DWORD dwExemptDelta;
  };
} INTERNET_CACHE_ENTRY_INFO, *LPINTERNET_CACHE_ENTRY_INFO;

*/

}
