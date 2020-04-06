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
 *  Stream.h
 *
 *****************************************************************************/

// SOL9
// 2012/08/08

#pragma once

#include <sol/com/SequentialStream.h>

#pragma comment(lib, "shlwapi.lib")

namespace SOL {

class Stream :public SequentialStream {


public:
  Stream(IUnknown* pUnknown=NULL)
  :SequentialStream(pUnknown)
  {
  }

public:
  Stream(__in  const TCHAR* fileName)
  :SequentialStream()
  {
    open(_bstr_t(fileName));
  }

public:
  HRESULT open(__in  const _bstr_t fileName)
  {
    return create(fileName);
  }

public:
  HRESULT create(__in  const _bstr_t fileName,
      __in DWORD grfMode = STGM_READ|STGM_SHARE_DENY_WRITE,
      __in DWORD dwAttributes = GENERIC_READ,
      __in BOOL fCreate = FALSE)
  {
    clear();
    IStream* pStream = NULL;
    HRESULT hr = SHCreateStreamOnFileEx(
      (const wchar_t*)fileName,
      grfMode,
      dwAttributes,
      fCreate,
      NULL,
      &pStream);
    if (FAILED(hr)) {
      throw Exception(hr, _T("Failed to create a stream:%s"), (const TCHAR*)fileName);
    }

    set(pStream);
    return hr;
  }

public:
  HRESULT create(__in HGLOBAL hMemory, __in BOOL fDeleteOnRelease = FALSE)
  {
    IStream* pStream = NULL;
    HRESULT hr = CreateStreamOnHGlobal(hMemory, fDeleteOnRelease, &pStream);
    if (FAILED(hr)) {
      throw Exception(hr, "Failed to create a stream"); 
    }

    set(pStream);
    return hr;
  }

public:
  ~Stream()
  {
  }

public:
  operator IStream*() {
    return getStream();
  }

public:
  IStream* getStream()
  {
    IUnknown* pUnknown = getIUnknown();
    if (pUnknown == NULL) {
      throw Exception(0, "IStream pointer is NULL");
    }
    return (IStream*)pUnknown;
  }

public:
  HRESULT seek( 
    __in LARGE_INTEGER dlibMove,
    __in DWORD dwOrigin,
    __out ULARGE_INTEGER *plibNewPosition)
  {
    HRESULT hr = getStream() -> Seek( 
      dlibMove,
      dwOrigin,
       plibNewPosition);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::seek failed");
    }
    return hr;
  }
        
  HRESULT setSize(__in ULARGE_INTEGER libNewSize)
  {
    HRESULT hr = getStream()->SetSize( 
      libNewSize);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::setSize failed");
    }
    return hr;
  }
        
  HRESULT copyTo( 
    __in IStream *pstm,
    __in ULARGE_INTEGER cb,
    __in ULARGE_INTEGER *pcbRead,
    __in ULARGE_INTEGER *pcbWritten)
  {
    HRESULT hr = getStream() -> CopyTo( 
      pstm,
      cb,
      pcbRead,
      pcbWritten);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::copyTo failed");
    }
    return hr;
  }

  HRESULT commit( 
    __in DWORD grfCommitFlags)
  {
    HRESULT hr = getStream() -> Commit( 
      grfCommitFlags);

    if (FAILED(hr)) {
      throw Exception(hr, "Stream::commit failed");
    }
    return hr;
  }
        
  HRESULT revert()
  {
    HRESULT hr = getStream()-> Revert();
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::revert failed");
    }
    return hr;
  }
        
  HRESULT lockRegion( 
    __in ULARGE_INTEGER libOffset,
    __in ULARGE_INTEGER cb,
    __in DWORD dwLockType)
        {
    HRESULT hr = getStream() -> LockRegion( 
      libOffset,
      cb,
      dwLockType);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::lockRegion failed");
    }
    return hr;
  }

  HRESULT unlockRegion( 
    __in ULARGE_INTEGER libOffset,
    __in ULARGE_INTEGER cb,
    __in DWORD dwLockType)
  {
    HRESULT hr = getStream() -> UnlockRegion( 
      libOffset,
      cb,
      dwLockType);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::unlock failed");
    }
    return hr;
  }
        
  HRESULT stat( 
            __out STATSTG *pstatstg,
            __in DWORD grfStatFlag)
  {
    HRESULT hr = getStream() -> Stat( 
      pstatstg,
      grfStatFlag);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::stat failed");
    }
    return hr;
  }

  HRESULT clone( 
              __out IStream **ppstm)
  {
    HRESULT hr = getStream() -> Clone( 
      ppstm);
    if (FAILED(hr)) {
      throw Exception(hr, "Stream::clone failed");
    }
    return hr;
  }        
};
    
}



