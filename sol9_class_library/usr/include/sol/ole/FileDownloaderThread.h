/******************************************************************************
 *
 * Copyright (c) 2012  Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileDownloaderThread.h
 *
 *****************************************************************************/

// SOL9 
// 2012/04/07
// Please create an instance of this class by new operator.

#pragma once

#include <sol\Thread.h>
#include <sol\String.h>
#include <sol\ole\FileDownloader.h>

namespace SOL {

class FileDownloaderThread :public Thread {

private:
  String url;
  String fileName;
  bool   cacheDelete;
  HWND   hwnd;
  DWORD  threadId;

public:
  static const UINT WM_FILEDOWNLOADED = (WM_USER + 2012); 

public:
  //Constructor
  FileDownloaderThread(const TCHAR* downloadUrl, const TCHAR* saveFileName, 
      HWND notifieeWindow, bool deleteFromCache=true)
  :Thread(), hwnd(NULL), threadId(0)
  {
    this->url      = downloadUrl;
    this->fileName = saveFileName;
    this->hwnd     = notifieeWindow;
    this->cacheDelete = deleteFromCache;
  }

public:
  //Constructor
  FileDownloaderThread(const TCHAR* downloadUrl, const TCHAR* saveFileName, 
      DWORD notifieeThreadId, bool deleteFromCache=true)
  :Thread(), hwnd(NULL), threadId(0)
  {
    this->url      = downloadUrl;
    this->fileName = saveFileName;
    this->threadId = notifieeThreadId;
    this->cacheDelete = deleteFromCache;
  }

public:
  ~FileDownloaderThread() 
  {
  }

private:
  void postResult(UINT msg, WPARAM wParam, LPARAM lParam)
  {
    if (hwnd) {
      PostMessage(hwnd, msg, wParam, lParam);
    }
    if (threadId>0) {
      PostThreadMessage(threadId,  msg, wParam, lParam);
    }
  }

public:
  // Thread main loop
  virtual void run() 
  {
    try {
      FileDownloader downloader;
      HRESULT hr = downloader.download((const TCHAR*)url, (const TCHAR*)fileName, cacheDelete);
      if (SUCCEEDED(hr)) {
        postResult(WM_FILEDOWNLOADED, TRUE, 0);
      } else {
        postResult(WM_FILEDOWNLOADED, FALSE, 0);
      }
    } catch (...) {
      postResult(WM_FILEDOWNLOADED, FALSE, 0);
    }
    //
    // We assume that this instance of this class has been created by new operator.
    delete this;
  }
};

}
