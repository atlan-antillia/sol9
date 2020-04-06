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
 *  UrlCacheEntryStream.h
 *
 *****************************************************************************/

// SOL9
// 2012/01/20

#pragma once

#include <sol/wininet/UrlCacheEntry.h>
#include <sol/File.h>

namespace SOL {

class UrlCacheEntryStream :public UrlCacheEntry{

private:
  HANDLE hStream;
  DWORD  streamSize;

public:
  UrlCacheEntryStream(const TCHAR* urlName)
  :UrlCacheEntry(urlName),
  hStream(NULL), streamSize(0)
  {
    if (urlName) {
      open(urlName);
    }
  }

private:
  bool open(const TCHAR* urlName)
  {
    bool rc = false;

    DWORD size = 0;

    hStream = RetrieveUrlCacheEntryStream(urlName, NULL, &size, FALSE, 0);

    DWORD err = GetLastError();
    if (err == ERROR_FILE_NOT_FOUND) {
      throw Exception(0, _T("RetrieveUrlCacheEntryStream FileNotFound:%s"), urlName);
    }
    if (err == ERROR_INSUFFICIENT_BUFFER) {
      
      INTERNET_CACHE_ENTRY_INFO* cacheEntryInfo = (INTERNET_CACHE_ENTRY_INFO*)new BYTE[size];
      if (cacheEntryInfo) {    
        hStream = RetrieveUrlCacheEntryStream(urlName, cacheEntryInfo, &size, FALSE, 0);
        streamSize  = cacheEntryInfo->dwSizeLow;
        delete [] cacheEntryInfo;

        if (hStream== NULL) {
          throw Exception("Failed to call RetrieveUrlCacheEntryStream");
        }
        rc = true;
      }
    }
    return rc;
  }

public:
  bool read(__out Bytes& bytes)
  { 
    bool rc = false;

    if (streamSize >0) {
    
      BYTE* buffer = new BYTE[streamSize];
      if (ReadUrlCacheEntryStream(hStream, 0, (void*)buffer, &streamSize, 0)) {
        bytes.shallowCopy(buffer, streamSize);
        rc = true;
      } else {
        delete [] buffer;
      }
    }
    return rc;
  }


public:
  DWORD read(DWORD position, BYTE* buffer, DWORD& bsize)
  { 
    DWORD rc = 0;

    if (streamSize >0) {
      if (position >=0 && position < streamSize && bsize >0) {
        if (ReadUrlCacheEntryStream(hStream, position, (void*)buffer, &bsize, 0)) {
          rc = bsize;
        }
      }
    }
    return rc;
  }

public:
  bool copy(const TCHAR* dest) 
  {
    bool rc = false;
    if (dest == NULL) {
      return rc;
    }

    if (hStream) {
      File file;
      if (file.create(dest)) {
        const DWORD bsize = 1024;

        BYTE buffer[bsize];
        size_t rest = streamSize;
        DWORD position = 0;
        DWORD size = 0;
        while (rest>0) {
          size = bsize;
          if (rest < bsize) {
            size = rest;
          }
          int rsize = read(position, buffer, size);
          position += rsize;
          file.write(buffer, rsize);
          rest -= rsize;
        }
        file.close();
        rc = true;
      }
    }
    return rc;
  }

public:
  ~UrlCacheEntryStream()
  {
    close();
  }

public:
  void close()
  {
    if (hStream) {
      UnlockUrlCacheEntryStream(hStream, 0);
      hStream = NULL;
      streamSize = 0;
    }
  }


};

}
