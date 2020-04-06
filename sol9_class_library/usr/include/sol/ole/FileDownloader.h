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
 *  FileDownloader.h
 *
 *****************************************************************************/

// SOL9 
// 2012/02/15

#pragma once

#include <sol/Object.h>

#include <sol/com/ComIDispatch.h>
#include <urlmon.h>
#include <wininet.h>

#pragma comment (lib, "urlmon.lib")
#pragma  comment(lib,"wininet.lib")

namespace SOL {

class FileDownloader :public Object {

public:
  FileDownloader()
  {
  }

public:
  ~FileDownloader()
  {

  }

public:
  HRESULT download(const TCHAR* url, const TCHAR* saveFileName, bool deleteFromCache=true)
  {
    if (deleteFromCache) {
      //Try to delete a cache entry for the url, even if there were no cache entry for the url. 
      //BOOL rc = 
      DeleteUrlCacheEntry(url);
      //Don't care the return-value of rc.
    }
    // Download the content of the url to a local file of saveFileName.
    HRESULT hr = URLDownloadToFile(NULL, url, saveFileName, 0, NULL);
    if (FAILED(hr)) {
      throw Exception(0, _T("Failed to download %s to %s"), url, saveFileName) ;
    }
    return hr;
  }

};

}
